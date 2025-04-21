/* =============================================================
 *  ahrs_filters.h — Minimal Mahony & Madgwick AHRS driver
 *  Target: C99‑compatible embedded MCUs (e.g. STM32, ESP32, AVR)
 *  Copyright: Public Domain / CC0
 *  -------------------------------------------------------------
 *  API OVERVIEW
 *    • Call ahrs_init() once.
 *    • Feed scaled sensor data each sample period to one of:
 *        ahrs_update_mahony()   // PI complementary filter
 *        ahrs_update_madgwick() // Gradient‑descent filter
 *    • Read attitude via ahrs_get_euler() or ahrs_get_quat().
 *
 *  Units
 *    Gyro   rad s⁻¹ (convert dps → rad s⁻¹ with *DEG2RAD)
 *    Accel  g (normalize raw / 8192 for ±4 g, etc.)
 *    Mag    µT (after factory sensitivity adj.)
 *    dt     seconds
 * ============================================================ */
#ifndef AHRS_FILTERS_H
#define AHRS_FILTERS_H

#include <stdint.h>

/* ---------------- User‑tunable gains ---------------- */
#define MAHONY_KP  2.0f   /* proportional gain  (β = 2ζω₀) */
#define MAHONY_KI  0.05f  /* integral gain      (bias drift) */
#define MADG_BETA  0.1f   /* 2ζω₀ in Madgwick thesis       */

#ifndef DEG2RAD
#define DEG2RAD 0.017453292519943295769236907f
#endif

/* ---------------- Data structures ---------------- */
typedef struct { float w, x, y, z; } quatf_t;

typedef struct {
    quatf_t q;      /* Attitude estimate            */
    float   exInt;  /* Integral error (Mahony)      */
    float   eyInt;
    float   ezInt;
} ahrs_t;

/* ---------------- Public API ---------------- */
#ifdef __cplusplus
extern "C" {
#endif

void  ahrs_init(ahrs_t *s);
void  ahrs_update_mahony(ahrs_t *s, float gx, float gy, float gz,
                         float ax, float ay, float az,
                         float mx, float my, float mz,
                         float dt);
void  ahrs_update_madgwick(ahrs_t *s, float gx, float gy, float gz,
                           float ax, float ay, float az,
                           float mx, float my, float mz,
                           float dt);
/* Euler output (rad) */
void  ahrs_get_euler(const ahrs_t *s, float *roll, float *pitch, float *yaw);
/* Quaternion copy */
void  ahrs_get_quat (const ahrs_t *s, quatf_t *q_out);

#ifdef __cplusplus
}
#endif

#endif /* AHRS_FILTERS_H */
