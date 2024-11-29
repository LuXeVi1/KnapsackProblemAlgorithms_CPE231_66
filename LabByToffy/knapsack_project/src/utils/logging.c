#include "logging.h"

void logMessage(const char *message) {
    printf("LOG: %s\n", message);
}

void logError(const char *message) {
    fprintf(stderr, "ERROR: %s\n", message);
}
