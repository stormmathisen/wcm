#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "ict.h"

// Slice the source array from start to end and copy it to the destination array
//Internal use only
void slice(int *source, int start, int end, int *destination) {
    for (int i = start; i < end; i++) { 
        destination[i - start] = source[i]; 
    } 
}

// Calculate bunch charge for ICT
//Vector: EBT-B03-IOC-CS-04:FMC1:CHX-COUNTS
//q_cal: CLA-S01-DIA-ICT-01:Q:Q_CALIBRATION
//u_cal: CLA-S01-DIA-ICT-01:Q:U_CALIBRATION
//loc: CLA-S01-DIA-ICT-01:Q:LOC
//Width: CLA-S01-DIA-ICT-01:Q:WIDTH
float_t calculate_bunch_charge(int vector[2048], float_t q_cal, float_t u_cal, int loc, int width){
    float_t u_bcm = 0;
    int start = loc - width / 2;
    int end = loc + width / 2;
    int *cropped_vector = (int *)malloc(width * sizeof(int));
    slice(vector, start, end, cropped_vector);
    for (int i = 0; i < width; i++) {
        u_bcm += cropped_vector[i];
    }
    u_bcm /= width;
    free(cropped_vector);
    float_t q_in = 0;
    q_in = q_cal*powf(10.0, (u_bcm)/(u_cal));
    return q_in;
}