#ifndef LOGGING_H
#define LOGGING_H

#include <stdio.h>

// Logging utilities

/**
 * Logs a message to the console.
 * @param message The message to log.
 */
void logMessage(const char *message);

/**
 * Logs an error to the console.
 * @param message The error message to log.
 */
void logError(const char *message);

#endif // LOGGING_H
