#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

// Function to get device info (example for Linux systems)
void getDeviceInfo() {
    // Example: Fetch CPU and memory info (Linux)
    system("lscpu | grep 'Model name'");
    system("free -h | grep 'Mem'");
}
