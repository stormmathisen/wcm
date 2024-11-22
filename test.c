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
    printf("Waveform: %d\n", waveform[1024]);
    float_t baseline = baseline_correction(waveform, 1000, 100, 0.1);
    printf("Baseline: %f\n", baseline);
    float_t dark_charge = calculate_dark_charge(waveform, 1000, 100, 0.1, baseline);
    printf("Dark charge: %f\n", dark_charge);
    return 0;
}