#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "wcm.h"

// Slice the source array from start to end and copy it to the destination array
//Internal use only
void slice(int *source, int start, int end, int *destination) {
    for (int i = start; i < end; i++) { 
        destination[i - start] = source[i]; 
    } 
}

// Calculate the dark charge of the vector from center - width/2 to center + width/2
//Vector: EBT-B03-IOC-CS-04:FMC1:CHX-COUNTS
//Center: CLA-S01-DIA-WCM-01:DARK_CHARGE:WINDOW-CENTER
//Width: CLA-S01-DIA-WCM-01:DARK_CHARGE:WINDOW-WIDTH
//a: CLA-S01-DIA-WCM-01:DARK_CHARGE:CALIBRATION-FACTOR
//b: CLA-S01-DIA-WCM-01:DARK_CHARGE:BASELINE
//dark_charge: CLA-S01-DIA-WCM-01:DARK_CHARGE
float_t calculate_dark_charge(int vector[2048], int center, int width, float_t a, float_t b) {
    float_t dark_charge = 0;
    int start = center - width / 2;
    int end = center + width / 2;
    int *cropped_vector = (int *)malloc(width * sizeof(int));
    slice(vector, start, end, cropped_vector);
    for (int i = 0; i < width; i++) {
        dark_charge += (cropped_vector[i]-b)*a;
    }
    free(cropped_vector);
    return dark_charge;
}

// Calculate average value in window and subtract it from the vector
//Vector: EBT-B03-IOC-CS-04:FMC1:CHX-COUNTS
//Center: CLA-S01-DIA-WCM-01:DARK_CHARGE:BASELINE-CENTER
//Width: CLA-S01-DIA-WCM-01:DARK_CHARGE:BASELINE-WIDTH
//baseline: CLA-S01-DIA-WCM-01:DARK_CHARGE:BASELINE
float_t baseline_correction(int vector[2048], int center, int width) {
    float_t baseline = 0;
    int start = center - width / 2;
    int end = center + width / 2;
    int *cropped_vector = (int *)malloc(width * sizeof(int));
    slice(vector, start, end, cropped_vector);
    for (int i = 0; i < width; i++) {
        baseline += cropped_vector[i];
    }
    baseline /= width;
    free(cropped_vector);
    return baseline;
}

//Calculate the bunch charge, by taking the average of values at the peak, and at the base, and subtracting the base from the peak. A is calibration factor
//Vector: EBT-B03-IOC-CS-04:FMC1:CHX-COUNTS
//Base: CLA-S01-DIA-WCM-01:Q:BASE
//Peak: CLA-S01-DIA-WCM-01:Q:PEAK
//Width: CLA-S01-DIA-WCM-01:Q:WIDTH
//a: CLA-S01-DIA-WCM-01:Q:A
//bunch_charge: CLA-S01-DIA-WCM-01:Q
float_t calculate_bunch_charge(int vector[2048], int base, int peak, int width, float_t a) {
    float_t peak_value = 0;
    float_t baseline = 0;
    int start = peak - width / 2;
    int end = peak + width / 2;
    int *cropped_vector = (int *)malloc(width * sizeof(int));
    slice(vector, start, end, cropped_vector);
    for (int i = 0; i < width; i++) {
        peak_value += cropped_vector[i];
    }
    peak_value /= width;
    free(cropped_vector);
    start = base - width / 2;
    end = base + width / 2;
    cropped_vector = (int *)malloc(width * sizeof(int));
    slice(vector, start, end, cropped_vector);
    for (int i = 0; i < width; i++) {
        baseline += cropped_vector[i];
    }
    baseline /= width;
    free(cropped_vector);
    return (peak_value - baseline)*a;
}