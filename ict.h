#include <math.h>
#include <stdlib.h>

void slice(int *source, int start, int end, int *destination);

float_t calculate_bunch_charge(int vector[2048], float_t q_cal, float_t u_cal, int loc, int width);