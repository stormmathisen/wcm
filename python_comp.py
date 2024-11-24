import numpy as np


def read_data():
    # Read data from file
    data = np.loadtxt('waveform.csv', delimiter=',')
    return data

def calculate_baseline(vector, center, width):
    baseline = 0
    for i in range(center-width//2, center+width//2):
        baseline += vector[i]
    return baseline/width

def calculate_dark_charge(vector, center, width, a, baseline):
    dark_charge = 0
    for i in range(center-width//2, center+width//2):
        dark_charge += (vector[i]-baseline)*a
    return dark_charge

def calculcate_bunch_charge(vector, base, peak, width, a):
    peak_value = 0
    base_value = 0
    start = peak-width//2
    end = peak+width//2
    for i in range(start, end):
        peak_value += vector[i]
    peak_value /= width
    start = base-width//2
    end = base+width//2
    for i in range(start, end):
        base_value += vector[i]
    base_value /= width
    return (peak_value-base_value)*a


if __name__ == '__main__':
    vector = read_data()
    baseline = calculate_baseline(vector, 300, 200)
    dark_charge = calculate_dark_charge(vector, 900, 200, 2, baseline)
    bunch_charge = calculcate_bunch_charge(vector, 935, 950, 10, 2)
    print("Baseline: ", baseline)
    print("Dark Charge: ", dark_charge)
    print("Bunch Charge: ", bunch_charge)