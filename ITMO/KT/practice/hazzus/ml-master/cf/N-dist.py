def in_dist(data):
	distance = 0
	data_by_c = {}
	for x, c in data:
		if c not in data_by_c:
			data_by_c[c] = []
		data_by_c[c].append(x)
	for c in data_by_c:
		x = data_by_c[c]
		x.sort()

		suffix = sum(x)
		prefix = 0
		for i in range(len(x)):
			suffix -= x[i]

			distance += (x[i] * i - prefix) + (suffix - x[i] * (len(x) - i - 1))

			prefix += x[i]
	return distance

def ex_dist(data):
	distance = 0
	prefixes = {}
	suffixes = {}
	data.sort()
	
	prefix_total = 0
	suffix_total = 0
	for x, c in data:
		if c not in suffixes:
			suffixes[c] = (0, 0)
			prefixes[c] = (0, 0)
		suffixes[c] = (suffixes[c][0] + x, suffixes[c][1] + 1)
		suffix_total += x

	for i in range(len(data)):
		x, c = data[i]

		suffix_total -= x
		suffixes[c] = (suffixes[c][0] - x, suffixes[c][1] - 1)
		
		suf_sum, suf_cnt = suffixes[c]
		pre_sum, pre_cnt = prefixes[c]

		pd = (i - pre_cnt) * x - (prefix_total - pre_sum)
		sd = (suffix_total - suf_sum) - ((len(data) - i - 1) - suf_cnt) * x;

		distance += pd + sd

		prefixes[c] = (prefixes[c][0] + x, prefixes[c][1] + 1)
		prefix_total += x
		
	return distance

k = int(input())
n = int(input())
data = []
for i in range(n):
	x, y = map(int, input().split())
	data.append((x, y))
	
print(in_dist(data))
print(ex_dist(data))
