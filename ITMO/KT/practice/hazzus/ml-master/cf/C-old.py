import math


# DISTANCES

def distance(x, y, ival, f1, f2):
    assert (len(x) == len(y))
    res = ival
    # print(x)
    for a, b in zip(x[:-1], y[:-1]):
        res += f1(a, b)
    return f2(res)


def euclidian(x, y):
    return distance(x, y, 0.0,
                    lambda x, y: (x - y) ** 2,
                    math.sqrt)


def manhattan(x, y):
    return distance(x, y, 0.0,
                    lambda x, y: abs(x - y),
                    lambda x: x)


def chebyshev(x, y):
    return distance(x, y, [],
                    lambda x, y: [abs(x - y)],
                    max)


distances = {
    'euclidean': euclidian,
    'manhattan': manhattan,
    'chebyshev': chebyshev
}


# KERNELS

def kernel(f, dist, param):
    x = dist / param
    return 1 - f(x) if x < 1 else 0


def uniform(dist, param):
    return kernel(lambda x: 1 / 2, dist, param)


def triangular(dist, param):
    return kernel(lambda x: x, dist, param)


def epanechnikov(dist, param):
    return kernel(lambda x: x ** 2, dist, param) * (3 / 4)


def quartic(dist, param):
    return (epanechnikov(dist, param) ** 2) * (15 / 16)


def triweight(dist, param):
    return (epanechnikov(dist, param) ** 3) * (35 / 32)


def tricube(dist, param):
    return (kernel(lambda x: x ** 3, dist, param) ** 3) * (70 / 81)


def gaussian(dist, param):
    return 1 / (math.sqrt(2 * math.pi)) * math.exp((-1 / 2) * ((dist / param) ** 2))


def cosine(dist, param):
    x = dist / param
    return math.pi / 4 * math.cos(math.pi * x / 2) if x < 1 else 0


def logistic(dist, param):
    x = dist / param
    return 1 / (math.exp(x) + 2 + math.exp(-x))


def sigmoid(dist, param):
    x = dist / param
    return (2 / math.pi) / (math.exp(x) + math.exp(-x))


kernels = {
    'uniform': uniform,
    'triangular': triangular,
    'epanechnikov': epanechnikov,
    'quartic': quartic,
    'triweight': triweight,
    'tricube': tricube,
    'gaussian': gaussian,
    'cosine': cosine,
    'logistic': logistic,
    'sigmoid': sigmoid
}


# WINDOWS

def window_fixed(param):
    return lambda nbs: param


def window_variable(param):
    return lambda nbs: nbs[param][0]


windows = {
    'fixed': window_fixed,
    'variable': window_variable
}

# MAIN

n, m = list(map(int, input().split()))
ds = [None for i in range(n)]
for i in range(n):
    ds[i] = list(map(int, input().split()))
target = list(map(int, input().split()))
target.append(None)

df = distances[input()]
kf = kernels[input()]
wf = windows[input()]
wp = int(input())
wfp = wf(wp)


dists = sorted(
    [(df(row, target), int(row[-1]), row[:-1]) for row in ds],
    key=lambda x: x[0]
)


def fallback():
    print(sum([x[0] for x in dists]) / n)


param = wfp(dists)
if param == 0:
    dists = list(filter(lambda y: y[2] == target[:-1], dists))
    n = len(dists)
    fallback()
else:
    sum_kernels = sum(map(lambda x: kf(x[0], param), dists))
    if sum_kernels == 0:
        fallback()
    else:
        sum_kernels_by_dists = sum(map(lambda x: x[1] * kf(x[0], param), dists))
        print(sum_kernels_by_dists / sum_kernels)

