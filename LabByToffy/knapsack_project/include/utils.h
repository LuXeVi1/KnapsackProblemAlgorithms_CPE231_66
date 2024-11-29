#ifndef UTILS_H
#define UTILS_H

// Function declarations for file handling
void readInputFromFile(const char *filename, int *n, int *capacity, int **weights, int **values);
void writeOutputToFile(const char *filename, int result);

// Function declarations for test case generator
void generateRandomTestCase(const char *filename, int n, int capacity);

// Function declarations for logger
void logExecution(const char *filename, const char *algorithmName, int capacity, int n, int *weights, int *values, int result);

// Function declaration for device info
void getDeviceInfo();

#endif // UTILS_H
