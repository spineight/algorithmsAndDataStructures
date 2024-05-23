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
    return kernel(abs, dist, param)


def epanechnikov(dist, param):
    return kernel(lambda x: x ** 2, dist, param) * (3 / 4)


def quartic(dist, param):
    return (kernel(lambda x: x ** 2, dist, param) ** 2) * (15 / 16)


def triweight(dist, param):
    return (kernel(lambda x: x ** 2, dist, param) ** 3) * (35 / 32)


def tricube(dist, param):
    return (kernel(lambda x: abs(x) ** 3, dist, param) ** 3) * (70 / 81)


def gaussian(dist, param):
	x = dist / param
	return math.exp(-0.5 * x ** 2) / math.sqrt(2 * math.pi)


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


def window_variable(param, df, target):
    return lambda nbs: df(nbs[param], target)


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

if wf == window_fixed:
	wfp = wf(wp)
else:
	wfp = wf(wp, df, target)

ds.sort(key=lambda x: df(x, target))

h = wfp(ds)
predicted = sum(map(lambda x: x[-1], ds)) / len(ds)

if h == 0:
	f = list(filter(lambda x: df(x, target) == 0, ds))
	if len(f) != 0:
		print(sum(map(lambda x: x[-1], f)) / len(f))
		exit(0)

	print(predicted)
	exit(0)

first = sum(map(lambda x: x[-1] * kf(df(x, target), h), ds))
second = sum(map(lambda x: kf(df(x, target), h), ds))

print(first / second if second != 0 else predicted)

