#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "fcup.h"

// Slice the source array from start to end and copy it to the destination array
//Internal use only
void slice(int *source, int start, int end, int *destination) {
    for (int i = start; i < end; i++) { 
        destination[i - start] = source[i]; 
    } 
}

// Calculate bunch charge for faraday cup
//Vector: EBT-B03-IOC-CS-04:FMC1:CHX-COUNTS
//Base: CLA-SP1-DIA-FCUP-01:Q:BASE
//Peak: CLA-SP1-DIA-FCUP-01:Q:PEAK
//Width: CLA-SP1-DIA-FCUP-01:Q:WIDTH
//a: CLA-SP1-DIA-FCUP-01:Q:A
//bunch_charge: CLA-SP1-DIA-FCUP-01:Q
float_t calculate_bunch_charge(int vector[2048], int base, int peak, int width, float_t a){
    float_t peak_value = 0;
    float_t base_value = 0;
    int start = peak - width / 2;
    int end = peak + width / 2;
    int *cropped_vector = (int *)malloc(width * sizeof(int));
    slice(vector, start, end, cropped_vector);
    for (int i = 0; i < width; i++) {
        peak_value += cropped_vector[i];
    }
    peak_value /= width;
    start = base - width / 2;
    end = base + width / 2;
    slice(vector, start, end, cropped_vector);
    for (int i = 0; i < width; i++) {
        base_value += cropped_vector[i];
    }
    base_value /= width;
    free(cropped_vector);
    return (peak_value - base_value) * a;
}