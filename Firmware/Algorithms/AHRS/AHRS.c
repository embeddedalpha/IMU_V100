/* =============================================================
 *  ahrs_filters.c — Implementation
 * ============================================================ */

#include "AHRS.h"
#include "math.h"


/* -------------------------------------------------------------
 * Quaternion helpers (static)
 * ----------------------------------------------------------- */
static inline quatf_t q_mult(quatf_t a, quatf_t b){
    return (quatf_t){
        a.w*b.w - a.x*b.x - a.y*b.y - a.z*b.z,
        a.w*b.x + a.x*b.w + a.y*b.z - a.z*b.y,
        a.w*b.y - a.x*b.z + a.y*b.w + a.z*b.x,
        a.w*b.z + a.x*b.y - a.y*b.x + a.z*b.w };
}
static inline quatf_t q_scale(quatf_t q, float s){
    return (quatf_t){q.w*s, q.x*s, q.y*s, q.z*s};
}
static inline quatf_t q_add(quatf_t a, quatf_t b){
    return (quatf_t){a.w+b.w, a.x+b.x, a.y+b.y, a.z+b.z};
}
static inline quatf_t q_normalize(quatf_t q){
    float n = 1.0f/sqrtf(q.w*q.w + q.x*q.x + q.y*q.y + q.z*q.z);
    return q_scale(q, n);
}

/* -------------------------------------------------------------
 *  Public functions
 * ----------------------------------------------------------- */
void ahrs_init(ahrs_t *s)
{
    s->q.w = 1.0f; s->q.x = s->q.y = s->q.z = 0.0f;
    s->exInt = s->eyInt = s->ezInt = 0.0f;
}

void ahrs_get_quat(const ahrs_t *s, quatf_t *q_out)
{ *q_out = s->q; }

void ahrs_get_euler(const ahrs_t *s, float *roll, float *pitch, float *yaw)
{
    const quatf_t q = s->q;
    if(roll)  *roll  = atan2f(2.0f*(q.w*q.x + q.y*q.z), 1.0f - 2.0f*(q.x*q.x + q.y*q.y));
    if(pitch) *pitch = asinf (2.0f*(q.w*q.y - q.z*q.x));
    if(yaw)   *yaw   = atan2f(2.0f*(q.w*q.z + q.x*q.y), 1.0f - 2.0f*(q.y*q.y + q.z*q.z));
}

static inline void normalize_vec3(float *x, float *y, float *z)
{
    float norm = 1.0f/sqrtf((*x)*(*x) + (*y)*(*y) + (*z)*(*z));
    *x *= norm; *y *= norm; *z *= norm;
}

void ahrs_update_mahony(ahrs_t *s, float gx, float gy, float gz,
                        float ax, float ay, float az,
                        float mx, float my, float mz,
                        float dt)
{
    /* Normalize sensors */
    normalize_vec3(&ax,&ay,&az);
    normalize_vec3(&mx,&my,&mz);

    /* Short name local var for readability */
    float q0=s->q.w, q1=s->q.x, q2=s->q.y, q3=s->q.z;

    /* Estimated direction of gravity & magnetic field (body frame) */
    float vx = 2*(q1*q3 - q0*q2);
    float vy = 2*(q0*q1 + q2*q3);
    float vz = q0*q0 - q1*q1 - q2*q2 + q3*q3;

    float wx = 2*(0.5f - q2*q2 - q3*q3);
    float wy = 2*(q1*q2 - q0*q3);
    float wz = 2*(q1*q3 + q0*q2);

    /* Error is cross product between measured and estimated dirs */
    float ex = (ay*vz - az*vy) + (my*wz - mz*wy);
    float ey = (az*vx - ax*vz) + (mz*wx - mx*wz);
    float ez = (ax*vy - ay*vx) + (mx*wy - my*wx);

    /* Integrate error (bias) */
    s->exInt += MAHONY_KI * ex * dt;
    s->eyInt += MAHONY_KI * ey * dt;
    s->ezInt += MAHONY_KI * ez * dt;

    /* Apply PI feedback */
    gx += MAHONY_KP * ex + s->exInt;
    gy += MAHONY_KP * ey + s->eyInt;
    gz += MAHONY_KP * ez + s->ezInt;

    /* Integrate rate to quaternion */
    quatf_t qDot = {0,
        0.5f*(-q1*gx - q2*gy - q3*gz),
        0.5f*( q0*gx + q2*gz - q3*gy),
        0.5f*( q0*gy - q1*gz + q3*gx)};

    s->q = q_add(s->q, q_scale(qDot, dt));
    s->q = q_normalize(s->q);
}

void ahrs_update_madgwick(ahrs_t *s, float gx, float gy, float gz,
                          float ax, float ay, float az,
                          float mx, float my, float mz,
                          float dt)
{
    normalize_vec3(&ax,&ay,&az);
    normalize_vec3(&mx,&my,&mz);

    float q0=s->q.w, q1=s->q.x, q2=s->q.y, q3=s->q.z;

    /* Compute objective function & Jacobian (only accel for brevity) */
    float f1 = 2*(q1*q3 - q0*q2) - ax;
    float f2 = 2*(q0*q1 + q2*q3) - ay;
    float f3 = 2*(0.5f - q1*q1 - q2*q2) - az;

    float g1 = -2*q2*f1 + 2*q1*f2;
    float g2 =  2*q3*f1 + 2*q0*f2 - 4*q1*f3;
    float g3 = -2*q0*f1 + 2*q3*f2 - 4*q2*f3;
    float g4 =  2*q1*f1 + 2*q2*f2;

    /* Normalize gradient */
    float norm = 1.0f/sqrtf(g1*g1 + g2*g2 + g3*g3 + g4*g4);
    g1 *= norm; g2 *= norm; g3 *= norm; g4 *= norm;

    /* Compute qDot */
    quatf_t qDot = {
        0.5f*(-q1*gx - q2*gy - q3*gz) - MADG_BETA * g1,
        0.5f*( q0*gx + q2*gz - q3*gy) - MADG_BETA * g2,
        0.5f*( q0*gy - q1*gz + q3*gx) - MADG_BETA * g3,
        0.5f*( q0*gz + q1*gy - q2*gx) - MADG_BETA * g4 };

    s->q = q_add(s->q, q_scale(qDot, dt));
    s->q = q_normalize(s->q);
}

