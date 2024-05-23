import math

import numpy as np
import pandas as pd

from sklearn import tree
from sklearn import ensemble

from tqdm.notebook import tqdm as log_progress

import matplotlib.pyplot as plt

def load_dataset(filepath):
    ds_tmp = pd.read_csv(filepath)
    Y = ds_tmp[['y']]
    X = ds_tmp.loc[:, ds_tmp.columns != 'y']
    return X, Y

def build_and_fit(X, Y, criterion, splitter, max_depth):
    clf = tree.DecisionTreeClassifier(criterion=criterion, splitter=splitter, max_depth=max_depth)
    clf = clf.fit(X, Y.values.T[0])
    return clf

def count_accuracy(clf, tX, tY):
    true_count = 0
    total = tX.shape[0]
    predict_Y = clf.predict(tX)
    for predict, target in zip(predict_Y, tY.values.T[0]):
        if predict == target:
            true_count += 1
    return true_count / total

params = []
for h in range(3, 25):
    for c in ['gini', 'entropy']:
        for s in ['best', 'random']:
            params.append((h, c, s))
results = {i: {} for i in range(1, 22)}

for i in log_progress(range(1, 22)):
    prefix = 'data/{:02d}'.format(i)
    X, Y = load_dataset(prefix + '_train.csv')
    tX, tY = load_dataset(prefix + '_test.csv')
    for ps in params:
        if ps in results[i]:
            continue
        (height, cr, spl) = ps
        clf = build_and_fit(X, Y, cr, spl, height)
        acc = count_accuracy(clf, tX, tY)
        
        results[i][ps] = (acc, clf.get_depth())

sorted_results = list(map(lambda r: (r[0], sorted(r[1].items(), key=lambda e: -e[1][0])), results.items()))
best_results = list(map(lambda r: (r[0], r[1][0]), sorted_results))
best_results

def draw_accuracy(results, params):
    (_, cr, spl) = params
    filtered = list(filter(lambda x: x[0][1] == cr and x[0][2] == spl, results))
    sorted_by_h = list(map(lambda x: (x[0][0], x[1][0]), sorted(filtered, key=lambda x: x[0][0])))
    xd = [x for x, _ in sorted_by_h]
    yd = [y for _, y in sorted_by_h]
    
    plt.figure(figsize=(10, 7))
    plt.xlabel('requested tree depth')
    plt.ylabel('accuracy')
    plt.plot(xd, yd, label=str((cr, spl)))
    plt.legend()
    plt.show()
    
    
    sorted_by_th = list(map(lambda x: (x[0][0], x[1][1]), sorted(filtered, key=lambda x: x[0][0])))
    xd = [x for x, _ in sorted_by_th]
    yd = [y for _, y in sorted_by_th]
    
    plt.figure(figsize=(10, 7))
    plt.xlabel('requested tree depth')
    plt.ylabel('real average tree depth')
    plt.plot(xd, yd, label=str((cr, spl)))
    plt.legend()
    plt.show()

draw_accuracy(sorted_results[0][1], sorted_results[0][1][0][0])

draw_accuracy(sorted_results[1][1], sorted_results[1][1][0][0])

draw_accuracy(sorted_results[12][1], sorted_results[12][1][0][0])

draw_accuracy(sorted_results[20][1], sorted_results[20][1][0][0])

class ForrestClassificator:
    cls = []
    
    def __init__(self, reps, cr, spl, full=False):
        self.repititions = reps
        self.criterion = cr
        self.splitter = spl
        self.clfs = []
        self.full_columns = full
        
    def fit(self, X, Y):
        l, n = X.shape
        for i in range(self.repititions):
            rows = np.random.choice(X.index.values, l)
            X1 = X.loc[rows, :]
            Y2 = Y.loc[rows, :]
            
            X2 = None
            if self.full_columns:
                X2 = X1
            else:
                X2 = X1.sample(n=int(math.sqrt(n)), axis='columns') # random sqrt(n) columns
            # print(X.shape, X2.drop_duplicates().shape)
            
            self.clfs.append((X2.columns, build_and_fit(X2, Y2, self.criterion, self.splitter, None)))
            
    def predict(self, tX):
        results = np.empty((len(self.clfs), tX.shape[0]), dtype=np.int64)
        for i in range(len(self.clfs)):
            cols, clf = self.clfs[i]
            results[i] = clf.predict(tX[cols])
        results = results.T
        result = np.empty(len(results))
        for i in range(len(results)):
            result[i] = np.bincount(results[i]).argmax()
        return result

fresults = {}

for i in range(1, 22):
    prefix = 'data/{:02d}'.format(i)
    X, Y = load_dataset(prefix + '_train.csv')
    tX, tY = load_dataset(prefix + '_test.csv')
    
    fclf = ForrestClassificator(100, 'gini', 'random')
    fclf.fit(X, Y)

    acc_train = count_accuracy(fclf, X, Y)
    acc_test  = count_accuracy(fclf, tX, tY)
    
    
    fclf = ForrestClassificator(100, 'gini', 'random', True)
    fclf.fit(X, Y)

    acc_train_f = count_accuracy(fclf, X, Y)
    acc_test_f  = count_accuracy(fclf, tX, tY)


    fclf_sklrn = ensemble.RandomForestClassifier(n_estimators=100, criterion='gini')
    fclf_sklrn.fit(X, Y.values.T[0])

    acc_train_sk = count_accuracy(fclf_sklrn, X, Y)
    acc_test_sk  = count_accuracy(fclf_sklrn, tX, tY)

    fresults[i] = ((acc_train, acc_test), (acc_train_f, acc_test_f), (acc_train_sk, acc_test_sk))

fresults


