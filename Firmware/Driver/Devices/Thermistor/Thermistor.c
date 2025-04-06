/*
 * Thermistor.c
 *
 *  Created on: Dec 4, 2024
 *      Author: kunal
 */

#include "Thermistor.h"

#define VREF 3.3          // Reference voltage in volts
#define ADC_RESOLUTION 12 // 12-bit ADC, so 2^12 = 4096
#define R_REF 10000       // Reference resistor value in ohms (10KΩ)


const float temperatures[] = {
    -39.44, -38.33, -37.22, -36.11, -35.00, -33.89, -32.78, -31.67, -30.56, -29.44, -28.33, -27.22, -26.11, -25.00,
    -23.89, -22.78, -21.67, -20.56, -19.44, -18.33, -17.22, -16.11, -15.00, -13.89, -12.78, -11.67, -10.56, -9.44,
    -8.33, -7.22, -6.11, -5.00, -3.89, -2.78, -1.67, -0.56, 0.56, 1.67, 2.78, 3.89, 5.00, 6.11, 7.22, 8.33, 9.44, 10.56,
    11.67, 12.78, 13.89, 15.00, 16.11, 17.22, 18.33, 19.44, 20.56, 21.67, 22.78, 23.89, 25.00, 26.11, 27.22, 28.33, 29.44,
    30.56, 31.67, 32.78, 33.89, 35.00, 36.14, 37.22, 38.33, 39.44, 40.56, 41.67, 42.78, 43.89, 45.00, 46.11, 47.22, 48.33,
    49.44, 50.56, 51.67, 52.78, 53.89, 55.00, 56.14, 57.22, 58.33, 59.44, 60.56, 61.67, 62.78, 63.89, 65.00, 66.14, 67.22,
    68.33, 69.44, 70.56, 71.67, 72.78, 73.89, 75.00, 76.14, 77.22, 78.33, 79.44, 80.56, 81.67, 82.78, 83.89, 85.00, 86.11
};


const float resistances[] = {
    323839, 300974, 279880, 260410, 242427, 225809, 210443, 196227, 183068, 170775, 159488, 149024, 139316, 130306,
    121939, 114165, 106939, 100218, 93909, 88090, 82670, 77620, 72914, 68518, 64419, 60592, 57017, 53647, 50526, 47606,
    44874, 42317, 39921, 37676, 35573, 33599, 31732, 29996, 28365, 26834, 25395, 24042, 22770, 21573, 20446, 19376, 18378,
    17437, 16550, 15714, 14925, 14180, 13478, 12814, 12182, 11590, 11030, 10501, 10000, 9526, 9078, 8653, 8251, 7866, 7505,
    7163, 6838, 6530, 6238, 5960, 5697, 5447, 5207, 4981, 4766, 4561, 4367, 4182, 4006, 3838, 3679, 3525, 3380, 3242, 3114,
    2985, 2865, 2751, 2642, 2538, 2438, 2343, 2252, 2165, 2082, 2003, 1927, 1855, 1785, 1718, 1655, 1594, 1536, 1480, 1427,
    1375, 1326, 1279, 1234, 1190, 1149, 1109, 1070, 1034
};


const int table_size = sizeof(temperatures) / sizeof(temperatures[0]);



// Function to calculate thermistor resistance
static float calculate_thermistor_resistance(int adc_value) {
    if (adc_value == 0) {
        // Prevent division by zero
        return -1.0; // Return an error value
    }

    // Calculate the voltage ratio
    float v_out_ratio = (float)adc_value / (pow(2,ADC_RESOLUTION) - 1);

    // Calculate the thermistor resistance using the voltage divider formula
    float r_thermistor = R_REF * (v_out_ratio / (1.0 - v_out_ratio));

    return r_thermistor;
}

static float interpolate_temperature(float input_resistance) {
    // Check if the resistance is out of bounds
    if (input_resistance > resistances[0] || input_resistance < resistances[table_size - 1]) {
        // printf("Resistance out of range!\n");
        return -1; // Return an error value
    }

    // Find the interval where the input resistance fits
    for (int i = 0; i < table_size - 1; i++) {
        if (input_resistance <= resistances[i] && input_resistance >= resistances[i + 1]) {
            // Perform linear interpolation
            float r1 = resistances[i];
            float r2 = resistances[i + 1];
            float t1 = temperatures[i];
            float t2 = temperatures[i + 1];

            // Interpolation formula
            float temperature = t1 + (input_resistance - r1) * (t2 - t1) / (r2 - r1);
            return temperature;
        }
    }

    // Should not reach here
    return -1; // Return an error value
}


float Get_Temperature(uint16_t adc_value)
{
	float resistance = calculate_thermistor_resistance(adc_value);
	float temperature = interpolate_temperature(resistance) * (9/5) + 32;
	return temperature;
}
