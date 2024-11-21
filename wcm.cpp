#include <math.h>
#include <stdlib.h>

// Slice the source array from start to end and copy it to the destination array
void slice(int *source, int start, int end, int *destination) {
    for (int i = start; i < end; i++) { 
        destination[i - start] = source[i]; 
    } 
}

// Calculate the dark charge of the vector from center - width/2 to center + width/2
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
float_t baseline_correction(int vector[2048], int center, int width, int a) {
    float_t baseline = 0;
    int start = center - width / 2;
    int end = center + width / 2;
    int *cropped_vector = (int *)malloc(width * sizeof(int));
    slice(vector, start, end, cropped_vector);
    for (int i = 0; i < width; i++) {
        baseline += cropped_vector[i];
    }
    baseline /= width;
    for (int i = 0; i < width; i++) {
        cropped_vector[i] -= baseline;
    }
    free(cropped_vector);
    return baseline;
}