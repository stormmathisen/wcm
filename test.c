#include "wcm.h"
#include <stdio.h>


// Read in waveform from csv
void read_waveform(char *filename, int *waveform) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: File not found\n");
        return;
    }
    char line[2048];
    int i = 0;
    while (fgets(line, sizeof(line), file)) {
        waveform[i] = atoi(line);
        i++;
    }
    fclose(file);
}


int main() {
    int waveform[2048];
    read_waveform("waveform.csv", waveform);
    float_t dark_charge = calculate_dark_charge(waveform, 1000, 100, 0.1, 0.5);
    printf("Dark charge: %f\n", dark_charge);
    float_t baseline = baseline_correction(waveform, 1000, 100, 0.1);
    printf("Baseline: %f\n", baseline);
    return 0;
}