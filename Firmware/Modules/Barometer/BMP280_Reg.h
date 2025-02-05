/*
 * BMP280_Reg.h
 *
 *  Created on: Feb 3, 2025
 *      Author: kunal
 */

#ifndef BAROMETER_BMP280_REG_H_
#define BAROMETER_BMP280_REG_H_

// Example: A single struct containing all BMP280 register addresses in ascending order.
// Some registers in the range 0xA0–0xCF are reserved or not typically accessed by user code.

static const struct BMP280_Registers {
    // --- Calibration Registers (Temperature) ---
    uint8_t DIG_T1_LSB;  // 0x88
    uint8_t DIG_T1_MSB;  // 0x89
    uint8_t DIG_T2_LSB;  // 0x8A
    uint8_t DIG_T2_MSB;  // 0x8B
    uint8_t DIG_T3_LSB;  // 0x8C
    uint8_t DIG_T3_MSB;  // 0x8D

    // --- Calibration Registers (Pressure) ---
    uint8_t DIG_P1_LSB;  // 0x8E
    uint8_t DIG_P1_MSB;  // 0x8F
    uint8_t DIG_P2_LSB;  // 0x90
    uint8_t DIG_P2_MSB;  // 0x91
    uint8_t DIG_P3_LSB;  // 0x92
    uint8_t DIG_P3_MSB;  // 0x93
    uint8_t DIG_P4_LSB;  // 0x94
    uint8_t DIG_P4_MSB;  // 0x95
    uint8_t DIG_P5_LSB;  // 0x96
    uint8_t DIG_P5_MSB;  // 0x97
    uint8_t DIG_P6_LSB;  // 0x98
    uint8_t DIG_P6_MSB;  // 0x99
    uint8_t DIG_P7_LSB;  // 0x9A
    uint8_t DIG_P7_MSB;  // 0x9B
    uint8_t DIG_P8_LSB;  // 0x9C
    uint8_t DIG_P8_MSB;  // 0x9D
    uint8_t DIG_P9_LSB;  // 0x9E
    uint8_t DIG_P9_MSB;  // 0x9F

    // (0xA0–0xCF reserved/not typically used directly)

    // --- Chip ID / Version / Soft Reset ---
    uint8_t CHIP_ID;     // 0xD0 (expected value = 0x58 for BMP280)
    uint8_t VERSION;     // 0xD1 (sometimes called "revision" or "ML version")
    uint8_t SOFTRESET;   // 0xE0 (write 0xB6 to trigger a soft reset)

    // (0xE1–0xF2 reserved or used by calibration in some variants)

    // --- Status & Configuration ---
    uint8_t STATUS;      // 0xF3
    uint8_t CTRL_MEAS;   // 0xF4
    uint8_t CONFIG;      // 0xF5

    // --- Data Registers (pressure + temperature) ---
    // Pressure: [MSB 0xF7, LSB 0xF8, XLSB 0xF9]
    // Temperature: [MSB 0xFA, LSB 0xFB, XLSB 0xFC]
    uint8_t PRESS_MSB;   // 0xF7
    uint8_t PRESS_LSB;   // 0xF8
    uint8_t PRESS_XLSB;  // 0xF9
    uint8_t TEMP_MSB;    // 0xFA
    uint8_t TEMP_LSB;    // 0xFB
    uint8_t TEMP_XLSB;   // 0xFC

    // (0xFD, 0xFE, 0xFF — reserved/not used for BMP280)
} BMP280_Registers = {
    // --- Calibration Registers (Temperature) ---
    .DIG_T1_LSB  = 0x88,
    .DIG_T1_MSB  = 0x89,
    .DIG_T2_LSB  = 0x8A,
    .DIG_T2_MSB  = 0x8B,
    .DIG_T3_LSB  = 0x8C,
    .DIG_T3_MSB  = 0x8D,

    // --- Calibration Registers (Pressure) ---
    .DIG_P1_LSB  = 0x8E,
    .DIG_P1_MSB  = 0x8F,
    .DIG_P2_LSB  = 0x90,
    .DIG_P2_MSB  = 0x91,
    .DIG_P3_LSB  = 0x92,
    .DIG_P3_MSB  = 0x93,
    .DIG_P4_LSB  = 0x94,
    .DIG_P4_MSB  = 0x95,
    .DIG_P5_LSB  = 0x96,
    .DIG_P5_MSB  = 0x97,
    .DIG_P6_LSB  = 0x98,
    .DIG_P6_MSB  = 0x99,
    .DIG_P7_LSB  = 0x9A,
    .DIG_P7_MSB  = 0x9B,
    .DIG_P8_LSB  = 0x9C,
    .DIG_P8_MSB  = 0x9D,
    .DIG_P9_LSB  = 0x9E,
    .DIG_P9_MSB  = 0x9F,

    // --- Chip ID / Version / Soft Reset ---
    .CHIP_ID     = 0xD0,
    .VERSION     = 0xD1,
    .SOFTRESET   = 0xE0,

    // --- Status & Configuration ---
    .STATUS      = 0xF3,
    .CTRL_MEAS   = 0xF4,
    .CONFIG      = 0xF5,

    // --- Data Registers ---
    .PRESS_MSB   = 0xF7,
    .PRESS_LSB   = 0xF8,
    .PRESS_XLSB  = 0xF9,
    .TEMP_MSB    = 0xFA,
    .TEMP_LSB    = 0xFB,
    .TEMP_XLSB   = 0xFC
};


#endif /* BAROMETER_BMP280_REG_H_ */
