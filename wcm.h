#include <math.h>
#include <stdlib.h>

void slice(int *source, int start, int end, int *destination);

float_t calculate_dark_charge(int vector[2048], int center, int width, float_t a, float_t b);

float_t baseline_correction(int vector[2048], int center, int width);

float_t calculate_bunch_charge(int vector[2048], int base, int peak, int width, float_t a);