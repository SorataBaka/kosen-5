import numpy as np
import math

def train(x_train, y_train, rho, init_aug_w):
    n = x_train.shape[0]
    dim = x_train.shape[1]
    aug_w = init_aug_w
    log = [ aug_w.copy() ]
    while True:
        err_count = 0
        for i in range(0, n):
            y_predict = classify(aug_w, x_train[i, :])
            if y_train[i] == 0 and y_predict == 1:
                aug_x = to_aug_vector(x_train[i, :])
                aug_w += rho * aug_x
                log.append(aug_w.copy())
                err_count += 1
            elif y_train[i] == 1 and y_predict == 0:
                aug_x = to_aug_vector(x_train[i, :])
                aug_w -= rho * aug_x
                log.append(aug_w.copy())
                err_count += 1
        if err_count == 0:
            break
    return aug_w, log

def to_aug_vector(x):
    dim = x.shape[0]
    aug_x = np.empty([dim + 1, ], dtype=float)
    aug_x[0] = 1.0
    for j in range(0, dim):
        aug_x[j + 1] = x[j]
    return aug_x

def classify(aug_w, x_test_one):
    aug_x = to_aug_vector(x_test_one)
    ip = np.dot(aug_w, aug_x)
    if ip > 0:
        return 0
    elif ip < 0:
        return 1
    else:
        return -1

def classify_all(aug_w, x_test):
    n_test = x_test.shape[0]
    y_predict = np.empty(n_test, dtype=int)
    for i in range(0, n_test):
        y_predict_one = classify(aug_w, x_test[i, :])
        y_predict[i] = y_predict_one
    return y_predict
