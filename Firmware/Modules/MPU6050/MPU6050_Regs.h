/*
 * MPU6050_Regs.h
 *
 *  Created on: Jan 25, 2025
 *      Author: kunal
 */

#ifndef MPU6050_MPU6050_REGS_H_
#define MPU6050_MPU6050_REGS_H_

#include "main.h"

/*
 * MPU9250_Reg.h
 *
 *  Created on: 18-Jan-2022
 *      Author: Kunal
 */

#ifndef MPU9250_MPU9250_REG_H_
#define MPU9250_MPU9250_REG_H_



// Example: A single struct containing all register addresses of the MPU6050
// in ascending order. Note that some registers are "internal" or reserved.
// You can remove or rename fields as you see fit for your application.

static const struct MPU6050_Registers {
    // ---- Gyro Offset & Fine Gain (internal offset registers) ----
    uint8_t XG_OFFS_TC;         // 0x00
    uint8_t YG_OFFS_TC;         // 0x01
    uint8_t ZG_OFFS_TC;         // 0x02
    uint8_t X_FINE_GAIN;        // 0x03
    uint8_t Y_FINE_GAIN;        // 0x04
    uint8_t Z_FINE_GAIN;        // 0x05
    uint8_t XA_OFFS_H;          // 0x06
    uint8_t XA_OFFS_L_TC;       // 0x07
    uint8_t YA_OFFS_H;          // 0x08
    uint8_t YA_OFFS_L_TC;       // 0x09
    uint8_t ZA_OFFS_H;          // 0x0A
    uint8_t ZA_OFFS_L_TC;       // 0x0B
    // 0x0C is Reserved
    uint8_t SELF_TEST_X;        // 0x0D
    uint8_t SELF_TEST_Y;        // 0x0E
    uint8_t SELF_TEST_Z;        // 0x0F
    uint8_t SELF_TEST_A;        // 0x10
    // 0x11, 0x12 are Reserved

    // ---- Offset Registers (high/low) ----
    uint8_t XG_OFFS_USRH;       // 0x13
    uint8_t XG_OFFS_USRL;       // 0x14
    uint8_t YG_OFFS_USRH;       // 0x15
    uint8_t YG_OFFS_USRL;       // 0x16
    uint8_t ZG_OFFS_USRH;       // 0x17
    uint8_t ZG_OFFS_USRL;       // 0x18

    // ---- Sample Rate, Configuration & Sensor Config ----
    uint8_t SMPLRT_DIV;         // 0x19
    uint8_t CONFIG;             // 0x1A
    uint8_t GYRO_CONFIG;        // 0x1B
    uint8_t ACCEL_CONFIG;       // 0x1C

    // ---- Motion / Free-Fall Detection Thresholds ----
    uint8_t FF_THR;             // 0x1D
    uint8_t FF_DUR;             // 0x1E
    uint8_t MOT_THR;            // 0x1F
    uint8_t MOT_DUR;            // 0x20
    uint8_t ZRMOT_THR;          // 0x21
    uint8_t ZRMOT_DUR;          // 0x22

    // ---- FIFO & I2C Master Controls ----
    uint8_t FIFO_EN;            // 0x23
    uint8_t I2C_MST_CTRL;       // 0x24
    uint8_t I2C_SLV0_ADDR;      // 0x25
    uint8_t I2C_SLV0_REG;       // 0x26
    uint8_t I2C_SLV0_CTRL;      // 0x27
    uint8_t I2C_SLV1_ADDR;      // 0x28
    uint8_t I2C_SLV1_REG;       // 0x29
    uint8_t I2C_SLV1_CTRL;      // 0x2A
    uint8_t I2C_SLV2_ADDR;      // 0x2B
    uint8_t I2C_SLV2_REG;       // 0x2C
    uint8_t I2C_SLV2_CTRL;      // 0x2D
    uint8_t I2C_SLV3_ADDR;      // 0x2E
    uint8_t I2C_SLV3_REG;       // 0x2F
    uint8_t I2C_SLV3_CTRL;      // 0x30
    uint8_t I2C_SLV4_ADDR;      // 0x31
    uint8_t I2C_SLV4_REG;       // 0x32
    uint8_t I2C_SLV4_DO;        // 0x33
    uint8_t I2C_SLV4_CTRL;      // 0x34
    uint8_t I2C_SLV4_DI;        // 0x35
    uint8_t I2C_MST_STATUS;     // 0x36

    // ---- Interrupt Configuration ----
    uint8_t INT_PIN_CFG;        // 0x37
    uint8_t INT_ENABLE;         // 0x38
    uint8_t DMP_INT_STATUS;      // 0x39 (Often not used if DMP is disabled)
    uint8_t INT_STATUS;         // 0x3A

    // ---- Sensor Measurements (High/Low) ----
    uint8_t ACCEL_XOUT_H;       // 0x3B
    uint8_t ACCEL_XOUT_L;       // 0x3C
    uint8_t ACCEL_YOUT_H;       // 0x3D
    uint8_t ACCEL_YOUT_L;       // 0x3E
    uint8_t ACCEL_ZOUT_H;       // 0x3F
    uint8_t ACCEL_ZOUT_L;       // 0x40
    uint8_t TEMP_OUT_H;         // 0x41
    uint8_t TEMP_OUT_L;         // 0x42
    uint8_t GYRO_XOUT_H;        // 0x43
    uint8_t GYRO_XOUT_L;        // 0x44
    uint8_t GYRO_YOUT_H;        // 0x45
    uint8_t GYRO_YOUT_L;        // 0x46
    uint8_t GYRO_ZOUT_H;        // 0x47
    uint8_t GYRO_ZOUT_L;        // 0x48

    // ---- External Sensor Data (When using MPU as Master to external sensors) ----
    uint8_t EXT_SENS_DATA_00;   // 0x49
    uint8_t EXT_SENS_DATA_01;   // 0x4A
    uint8_t EXT_SENS_DATA_02;   // 0x4B
    uint8_t EXT_SENS_DATA_03;   // 0x4C
    uint8_t EXT_SENS_DATA_04;   // 0x4D
    uint8_t EXT_SENS_DATA_05;   // 0x4E
    uint8_t EXT_SENS_DATA_06;   // 0x4F
    uint8_t EXT_SENS_DATA_07;   // 0x50
    uint8_t EXT_SENS_DATA_08;   // 0x51
    uint8_t EXT_SENS_DATA_09;   // 0x52
    uint8_t EXT_SENS_DATA_10;   // 0x53
    uint8_t EXT_SENS_DATA_11;   // 0x54
    uint8_t EXT_SENS_DATA_12;   // 0x55
    uint8_t EXT_SENS_DATA_13;   // 0x56
    uint8_t EXT_SENS_DATA_14;   // 0x57
    uint8_t EXT_SENS_DATA_15;   // 0x58
    uint8_t EXT_SENS_DATA_16;   // 0x59
    uint8_t EXT_SENS_DATA_17;   // 0x5A
    uint8_t EXT_SENS_DATA_18;   // 0x5B
    uint8_t EXT_SENS_DATA_19;   // 0x5C
    uint8_t EXT_SENS_DATA_20;   // 0x5D
    uint8_t EXT_SENS_DATA_21;   // 0x5E
    uint8_t EXT_SENS_DATA_22;   // 0x5F
    uint8_t EXT_SENS_DATA_23;   // 0x60

    // ---- Motion Detection Status ----
    uint8_t MOT_DETECT_STATUS;  // 0x61
    // 0x62, 0x63 (Reserved in some docs, or internal for i2cdevlib usage)

    // ---- I2C Slave Data Out ----
    uint8_t I2C_SLV0_DO;        // 0x63 (Some docs put this at 0x63 or 0x64)
    uint8_t I2C_SLV1_DO;        // 0x64
    uint8_t I2C_SLV2_DO;        // 0x65
    uint8_t I2C_SLV3_DO;        // 0x66

    // ---- I2C & Signal Path Reset ----
    uint8_t I2C_MST_DELAY_CTRL; // 0x67
    uint8_t SIGNAL_PATH_RESET;  // 0x68
    uint8_t MOT_DETECT_CTRL;    // 0x69

    // ---- User & Power Management ----
    uint8_t USER_CTRL;          // 0x6A
    uint8_t PWR_MGMT_1;         // 0x6B
    uint8_t PWR_MGMT_2;         // 0x6C

    // ---- Memory Bank & DMP Configuration ----
    uint8_t BANK_SEL;           // 0x6D
    uint8_t MEM_START_ADDR;     // 0x6E
    uint8_t MEM_R_W;            // 0x6F
    uint8_t DMP_CFG_1;          // 0x70
    uint8_t DMP_CFG_2;          // 0x71

    // ---- FIFO Count & Data ----
    uint8_t FIFO_COUNTH;        // 0x72
    uint8_t FIFO_COUNTL;        // 0x73
    uint8_t FIFO_R_W;           // 0x74

    // ---- Identification ----
    uint8_t WHO_AM_I;           // 0x75
} MPU6050_Registers = {
    // ---- Gyro Offset & Fine Gain ----
    .XG_OFFS_TC         = 0x00,
    .YG_OFFS_TC         = 0x01,
    .ZG_OFFS_TC         = 0x02,
    .X_FINE_GAIN        = 0x03,
    .Y_FINE_GAIN        = 0x04,
    .Z_FINE_GAIN        = 0x05,
    .XA_OFFS_H          = 0x06,
    .XA_OFFS_L_TC       = 0x07,
    .YA_OFFS_H          = 0x08,
    .YA_OFFS_L_TC       = 0x09,
    .ZA_OFFS_H          = 0x0A,
    .ZA_OFFS_L_TC       = 0x0B,
    // 0x0C (Reserved)
    .SELF_TEST_X        = 0x0D,
    .SELF_TEST_Y        = 0x0E,
    .SELF_TEST_Z        = 0x0F,
    .SELF_TEST_A        = 0x10,
    // 0x11, 0x12 (Reserved)

    // ---- Offset Registers ----
    .XG_OFFS_USRH       = 0x13,
    .XG_OFFS_USRL       = 0x14,
    .YG_OFFS_USRH       = 0x15,
    .YG_OFFS_USRL       = 0x16,
    .ZG_OFFS_USRH       = 0x17,
    .ZG_OFFS_USRL       = 0x18,

    // ---- Sample Rate & Config ----
    .SMPLRT_DIV         = 0x19,
    .CONFIG             = 0x1A,
    .GYRO_CONFIG        = 0x1B,
    .ACCEL_CONFIG       = 0x1C,

    // ---- Motion Detection Thresholds ----
    .FF_THR             = 0x1D,
    .FF_DUR             = 0x1E,
    .MOT_THR            = 0x1F,
    .MOT_DUR            = 0x20,
    .ZRMOT_THR          = 0x21,
    .ZRMOT_DUR          = 0x22,

    // ---- FIFO & I2C Master ----
    .FIFO_EN            = 0x23,
    .I2C_MST_CTRL       = 0x24,
    .I2C_SLV0_ADDR      = 0x25,
    .I2C_SLV0_REG       = 0x26,
    .I2C_SLV0_CTRL      = 0x27,
    .I2C_SLV1_ADDR      = 0x28,
    .I2C_SLV1_REG       = 0x29,
    .I2C_SLV1_CTRL      = 0x2A,
    .I2C_SLV2_ADDR      = 0x2B,
    .I2C_SLV2_REG       = 0x2C,
    .I2C_SLV2_CTRL      = 0x2D,
    .I2C_SLV3_ADDR      = 0x2E,
    .I2C_SLV3_REG       = 0x2F,
    .I2C_SLV3_CTRL      = 0x30,
    .I2C_SLV4_ADDR      = 0x31,
    .I2C_SLV4_REG       = 0x32,
    .I2C_SLV4_DO        = 0x33,
    .I2C_SLV4_CTRL      = 0x34,
    .I2C_SLV4_DI        = 0x35,
    .I2C_MST_STATUS     = 0x36,

    // ---- Interrupt Configuration ----
    .INT_PIN_CFG        = 0x37,
    .INT_ENABLE         = 0x38,
    .DMP_INT_STATUS     = 0x39,  // (Optional / DMP-related)
    .INT_STATUS         = 0x3A,

    // ---- Sensor Measurements ----
    .ACCEL_XOUT_H       = 0x3B,
    .ACCEL_XOUT_L       = 0x3C,
    .ACCEL_YOUT_H       = 0x3D,
    .ACCEL_YOUT_L       = 0x3E,
    .ACCEL_ZOUT_H       = 0x3F,
    .ACCEL_ZOUT_L       = 0x40,
    .TEMP_OUT_H         = 0x41,
    .TEMP_OUT_L         = 0x42,
    .GYRO_XOUT_H        = 0x43,
    .GYRO_XOUT_L        = 0x44,
    .GYRO_YOUT_H        = 0x45,
    .GYRO_YOUT_L        = 0x46,
    .GYRO_ZOUT_H        = 0x47,
    .GYRO_ZOUT_L        = 0x48,

    // ---- External Sensor Data ----
    .EXT_SENS_DATA_00   = 0x49,
    .EXT_SENS_DATA_01   = 0x4A,
    .EXT_SENS_DATA_02   = 0x4B,
    .EXT_SENS_DATA_03   = 0x4C,
    .EXT_SENS_DATA_04   = 0x4D,
    .EXT_SENS_DATA_05   = 0x4E,
    .EXT_SENS_DATA_06   = 0x4F,
    .EXT_SENS_DATA_07   = 0x50,
    .EXT_SENS_DATA_08   = 0x51,
    .EXT_SENS_DATA_09   = 0x52,
    .EXT_SENS_DATA_10   = 0x53,
    .EXT_SENS_DATA_11   = 0x54,
    .EXT_SENS_DATA_12   = 0x55,
    .EXT_SENS_DATA_13   = 0x56,
    .EXT_SENS_DATA_14   = 0x57,
    .EXT_SENS_DATA_15   = 0x58,
    .EXT_SENS_DATA_16   = 0x59,
    .EXT_SENS_DATA_17   = 0x5A,
    .EXT_SENS_DATA_18   = 0x5B,
    .EXT_SENS_DATA_19   = 0x5C,
    .EXT_SENS_DATA_20   = 0x5D,
    .EXT_SENS_DATA_21   = 0x5E,
    .EXT_SENS_DATA_22   = 0x5F,
    .EXT_SENS_DATA_23   = 0x60,

    // ---- Motion Detection Status ----
    .MOT_DETECT_STATUS  = 0x61,
    // 0x62, 0x63 often reserved or used differently in some docs

    // ---- I2C Slave Data Out ----
    .I2C_SLV0_DO        = 0x63, // Some references list this at 0x63 or 0x64
    .I2C_SLV1_DO        = 0x64,
    .I2C_SLV2_DO        = 0x65,
    .I2C_SLV3_DO        = 0x66,

    // ---- I2C & Signal Path Reset ----
    .I2C_MST_DELAY_CTRL = 0x67,
    .SIGNAL_PATH_RESET  = 0x68,
    .MOT_DETECT_CTRL    = 0x69,

    // ---- User & Power Management ----
    .USER_CTRL          = 0x6A,
    .PWR_MGMT_1         = 0x6B,
    .PWR_MGMT_2         = 0x6C,

    // ---- Memory Bank & DMP Config ----
    .BANK_SEL           = 0x6D,
    .MEM_START_ADDR     = 0x6E,
    .MEM_R_W            = 0x6F,
    .DMP_CFG_1          = 0x70,
    .DMP_CFG_2          = 0x71,

    // ---- FIFO Count & Data ----
    .FIFO_COUNTH        = 0x72,
    .FIFO_COUNTL        = 0x73,
    .FIFO_R_W           = 0x74,

    // ---- Identification ----
    .WHO_AM_I           = 0x75
};


#define MPU9250_ADDRESS 0x68

#endif /* MPU9250_MPU9250_REG_H_ */

#endif /* MPU6050_MPU6050_REGS_H_ */
