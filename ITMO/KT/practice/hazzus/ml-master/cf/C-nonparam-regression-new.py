


def fixed(ds, param):
	return lambda x: param

def variable(ds, param):
	return lambda x: x[param][0]

functions = [
	# distances
	{
		''
	},
	# kernels
	{
		''
	},
	# windows
	{
		'fixed': fixed,
		'variable': variable
	}
]


if __name__ == '__main__':

	n, m = map(int, input().split())
	ds = [None for _ in range(n)]
	for i in range(n):
		ds[i] = list(map(int, input().split()))
	target = list(map(int, input().split()))
	
	print(n, m, ds)

	dist, kern, wind = [functions[i][input()] for i in range(3)]
	wind_param = int(input())

	
	print(dist, kern, wind)
