import sys
import numpy as np
import knn

if len(sys.argv) != 3:
    print('引数に 学習パターンのファイル名 未知パターンのファイル名 を与えてください.', file=sys.stderr)
    exit()

train_file = sys.argv[1]
test_file  = sys.argv[2]

x_train = np.loadtxt(train_file, usecols=[1, 2])
y_train = np.loadtxt(train_file, usecols=[0], dtype=int)

x_test  = np.loadtxt(test_file,  usecols=[1, 2])

n_test  = x_test.shape[0]
for i in range(0, n_test):
    y_predict = knn.classify(1, x_test[i, :], x_train, y_train)
    print(y_predict)

# y_predicts = knn.classify_all(1, x_test, x_train, y_train)
# print(y_predicts)
