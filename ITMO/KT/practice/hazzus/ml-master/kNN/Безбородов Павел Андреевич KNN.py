import numpy as np
import pandas as pd
import math
from tqdm.notebook import tqdm as log_progress
import itertools
import matplotlib.pyplot as plt

def distance(x, y, ival, f1, f2):
    assert(len(x) == len(y))
    res = ival
    # print(x)
    for a, b in zip(x, y):
        res += f1(a, b)
    return f2(res)

def euclidian(x, y):
    return distance(x[:-1], y[:-1], 0.0,
                   lambda x, y: (x - y) ** 2,
                   math.sqrt)

def manhattan(x, y):
    return distance(x[:-1], y[:-1], 0.0,
                   lambda x, y: abs(x - y),
                   lambda x: x)

def chebyshev(x, y):
    return distance(x[:-1], y[:-1], [],
                   lambda x, y: [abs(x - y)],
                   max)


def kernel(f, dist, param):
    x = dist / param
    return 1 - f(x) if x < 1 else 0

# we do max on summing results, so we can throw away constant multipliers

def uniform(dist, param):
    return kernel(lambda x: 0, dist, param)

def triangular(dist, param):
    return kernel(lambda x: x, dist, param)

def epanechnikov(dist, param):
    return kernel(lambda x: x ** 2, dist, param)

def quartic(dist, param):
    return epanechnikov(dist, param) ** 2

def triweight(dist, param):
    return epanechnikov(dist, param) ** 3

def tricube(dist, param):
    return kernel(lambda x: x ** 3, dist, param) ** 3

def gaussian(dist, param):
    return math.exp((-1 / 2) * ((dist / param) ** 2))

def cosine(dist, param):
    x = dist / param
    return math.cos(math.pi * x / 2) if x < 1 else 0

def logistic(dist, param):
    x = dist / param
    return 1 / (math.exp(x) + 2 + math.exp(-x))

def sigmoid(dist, param):
    x = dist / param
    return 1 / (math.exp(x) + math.exp(-x))



def window_fixed(param):
    return lambda nbs: param

def window_variable(param):
    return lambda nbs: nbs[param][0]

distances = [euclidian, manhattan, chebyshev]
kernels = [uniform, 
           triangular, 
           epanechnikov, 
           quartic, 
           triweight, 
           tricube, 
           gaussian, 
           cosine, 
           logistic, 
           sigmoid]
windows = [window_fixed, window_variable]


def minmax(dataset):
    result = {}
    for column in ds.columns[:-1]:
        result[column] = {'min': ds[column].min(axis=0), 'max': ds[column].max(axis=0)}
    return result

def normalize(dataset, minimax):
    for column in ds.columns[:-1]:
        mmc = minimax[column]
        ds[column] = ds[column].map(lambda val: (val - mmc['min']) / (mmc['max'] - mmc['min']))


def compute_distances(dataset, target, distance_f):
    return sorted(
        [(distance_f(row, target), int(row[-1])) for row in dataset.values],
        key=lambda x: x[0]
    )

def knn(dataset, target, distance_f, kernel_f, window_f, classes):
    dists = compute_distances(dataset, target, distance_f)
    param = window_f(dists)
    ans = [0 for i in range(classes)]
    for dist, pcls in dists:
        ans[pcls] += kernel_f(dist, param)
    return ans.index(max(ans))

def confusion(dataset, distance_f, kernel_f, window_f):
    classes = sorted(dataset['Class'].unique())
    classes_cnt = max(classes) + 1
    matrix = {name: {n: 0 for n in classes} for name in classes}
    for idx, row in dataset.iterrows():
        true = row[-1]
        dataset_m = dataset.drop([idx])
        predict = knn(dataset_m, row, distance_f, kernel_f, window_f, classes_cnt)
        matrix[true][predict] += 1
    return matrix

def f_score(matrix):
    def f(p, r):
        return 0 if p + r == 0 else 2 * p * r / (p + r)

    precision = {}
    recall = {}
    f_score = {}
    sum_cls = {}
    for cls in matrix:
        tp = matrix[cls][cls]
        tp_pls_fn = sum(matrix[cls].values())
        pos = sum([matrix[other_cls][cls] for other_cls in matrix])

        precision[cls] = 0 if pos == 0 else tp / pos
        recall[cls] = 0 if tp_pls_fn == 0 else tp / tp_pls_fn
        sum_cls[cls] = sum([matrix[cls][x] for x in matrix[cls]])

    for cls in matrix:
        f_score[cls] = f(precision[cls], recall[cls])

    total = sum([sum([matrix[x][y] for y in matrix[x]]) for x in matrix])
    macro = sum([
        f_score[cls] * sum_cls[cls] for cls in matrix
    ]) / total
    micro_p = sum([
        precision[cls] * sum_cls[cls] for cls in matrix
    ]) / total
    micro_r = sum([
        recall[cls] * sum_cls[cls] for cls in matrix
    ]) / total
    return f(micro_p, micro_r)

filename = 'wine.csv'
ds = pd.read_csv(filename)
ds.head()

# reordering
clss = ds['class']
ds.drop(['class'], axis=1, inplace=True)
ds.insert(len(ds.columns), 'Class', clss.map(lambda x: x - 1))
ds.head()

# no vectorization, no categoric columns
# normalization
normalize(ds, minmax(ds))
ds.head()

mdists = {df: -1.0 for df in distances}
for idx, row in log_progress(list(ds.iterrows())):
    for df in distances:
        mdists[df] = max(mdists[df], max(compute_distances(ds.drop([idx]), row, df), key=lambda x: x[0])[0])
mdists
# now i now that ~6.2 is max dist for fixed window

ds.shape[0]
# now I now that 178 is max k for neighbours

max_f = -1.0
best_conf = None
confs_l = [
    distances,
    kernels,
    windows
]
confs = list(itertools.product(*confs_l))
for conf in log_progress(confs):
    df, kf, wf = conf
    if wf == window_fixed:
        ks = np.linspace(0.1, 6.2, 10)
    else:
        ks = range(0, 171, 17)
    for k in ks:
        mat = confusion(ds, df, kf, wf(k))
        f_score_mat = f_score(mat)
        if f_score_mat > max_f:
            max_f = f_score_mat
            best_conf = (df, kf, wf, k)

bdf, bkf, bwf, bwpk = best_conf
(best_conf, max_f)

f_scores = []
variable_range = range(1, 171, 1)
for k in log_progress(variable_range):
    mat = confusion(ds, bdf, bkf, bwf(k))
    f_scores.append(f_score(mat))

plt.plot(variable_range, f_scores)

f_scores = []
fixed_range = np.linspace(0.05, 6.5, 80)
for wp in log_progress(fixed_range):
    mat = confusion(ds, bdf, bkf, window_fixed(wp))
    f_scores.append(f_score(mat))

plt.plot(fixed_range, f_scores)

