




k1, k2 = map(int, input().split())
n = int(input())
xs = []
ys = []


def hi_square():
	Ex = [0 for _ in range(k1)]
	Ey = [0 for _ in range(k2)]
	exper = {}
	n = len(xs)
	
	for x, y in zip(xs, ys):
		Ex[x] += 1
		Ey[y] += 1
		if (x, y) in exper:
			exper[(x, y)] += 1
		else:
			exper[(x, y)] = 1
	
	for i in range(k1):
		Ex[i] /= n
	for i in range(k2):
		Ey[i] /= n

	res = float(n)
	for (x, y), mu in exper.items():
		Ek = n * Ex[x] * Ey[y]
		res -= Ek
		
		res += (mu - Ek) * (mu - Ek) / Ek;
	return res


for i in range(n):
	x, y = map(int, input().split())
	xs.append(x - 1)
	ys.append(y - 1)

print(hi_square())
