import math

k1, k2 = map(int, input().split())
n = int(input())
xs = []
ys = []

def cond_entropy():
	n = len(xs)
	p = [0 for _ in range(k1)]
	mapping = {}
	
	for x, y in zip(xs, ys):
		p[x] += 1 / n
		if (x, y) in mapping:
			mapping[(x, y)] += 1 / n
		else:
			mapping[(x, y)] = 1 / n

	res = 0.0
	for (x, y), py in mapping.items():
		pxy = py / p[x]
		res += -py * math.log(pxy)
	return res

for i in range(n):
	x, y = map(int, input().split())
	xs.append(x - 1)
	ys.append(y - 1)

print(cond_entropy())
