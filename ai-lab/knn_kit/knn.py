import numpy as np
import math

def calc_distance(v1, v2):
    dim = v1.shape[0]
    sum = 0.0
    for j in range(0, dim):
        sum += (v1[j] - v2[j]) * (v1[j] - v2[j])
    distance = math.sqrt(sum)
    return distance

def classify(k, x_test_one, x_train, y_train):
    n = x_train.shape[0]
    min_distance = calc_distance(x_test_one, x_train[0, :])
    min_i = 0
    for i in range(1, n):
        distance = calc_distance(x_test_one, x_train[i, :])
        if distance < min_distance:
            min_distance = distance
            min_i = i
    return y_train[min_i]

def classify_all(k, x_test, x_train, y_train):
    n_test = x_test.shape[0]
    y_predict = np.empty(n_test, dtype=int)
    for i in range(0, n_test):
        y_predict_one = classify(k, x_test[i, :], x_train, y_train)
        y_predict[i] = y_predict_one
    return y_predict
