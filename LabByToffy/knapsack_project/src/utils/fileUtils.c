#include "fileUtils.h"

int readItemsFromFile(const char *filename, Item items[]) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return -1;
    }

    int i = 0;
    while (fscanf(file, "%d %d %d", &items[i].id, &items[i].weight, &items[i].value) == 3) {
        i++;
        if (i >= MAX_ITEMS) {
            fprintf(stderr, "Exceeded maximum number of items (%d).\n", MAX_ITEMS);
            break;
        }
    }

    fclose(file);
    return i; // Returns the number of items read
}

void writeSolutionToFile(const char *filename, const Solution *solution, int size) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error opening file");
        return;
    }

    fprintf(file, "Total Value: %d\n", solution->totalValue);
    fprintf(file, "Total Weight: %d\n", solution->totalWeight);
    fprintf(file, "Included Items:\n");
    for (int i = 0; i < size; i++) {
        if (solution->included[i]) {
            fprintf(file, "%d ", i);
        }
    }
    fprintf(file, "\n");

    fclose(file);
}
