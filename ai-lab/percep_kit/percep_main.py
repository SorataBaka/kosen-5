import sys
import numpy as np
import percep

if len(sys.argv) != 9:
    print('引数に 学習パターンのファイル名 未知パターンのファイル名 ρ w0の初期値 w1の初期値 w2の初期値 重みのファイル名 ログのファイル名 を与えてください.', file=sys.stderr)
    exit()

train_file = sys.argv[1]
test_file  = sys.argv[2]
rho =float(sys.argv[3]) 
w0 = float(sys.argv[4])
w1 = float(sys.argv[5])
w2 = float(sys.argv[6])
aug_w_file = sys.argv[7]
log_file   = sys.argv[8]

x_train = np.loadtxt(train_file, usecols=[1, 2])
y_train = np.loadtxt(train_file, usecols=[0], dtype=int)

x_test  = np.loadtxt(test_file,  usecols=[1, 2])

aug_w, log = percep.train(x_train, y_train, rho, [w0, w1, w2])

np.savetxt(aug_w_file, aug_w)
np.savetxt(log_file, log)

n_test  = x_test.shape[0]
for i in range(0, n_test):
    y_predict = percep.classify(aug_w, x_test[i, :])
    print(y_predict)
