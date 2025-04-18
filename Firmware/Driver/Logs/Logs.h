/*
 * Logs.h
 *
 *  Created on: Oct 10, 2024
 *      Author: kunal
 */

#ifndef LOGS_LOGS_H_
#define LOGS_LOGS_H_

#include "main.h"


typedef enum
{
    LOG_LEVEL_ERROR,
    LOG_LEVEL_INFORMATION,
    LOG_LEVEL_DEBUG
} LogLevel;

/// The global variable `system_log_level` should be defined and given the desired log level.
extern LogLevel system_log_level;

void log_error(char const * const format, ...);
void log_info(char const * const format, ...);
void log_debug(char const * const format, ...);
void log_debug_array(char const * const label, void const *array, uint16_t const len);


#endif /* LOGS_LOGS_H_ */
