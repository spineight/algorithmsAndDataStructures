errors = 2 
b = 12
# powers = [25, 24, 16, 20, 25, 1, 27, 24, 2, 1, 10, 16, 20, 28, 8, 2, 9, 21, 3, 29, -1, 18, 30, 2, 29, 8, 23, 15, 1, 23, 25]
powers = [12, 8, 1, 24, 4, 5, 4, 8, 17, 14, 18, 18, 9, 10, 4, 4, 9, 24, 30, 1, 10, 13, 13, 11, 17, 16, 11, 22, 2, 1, 12]
# powers = [24, 23, 8, 1, -1, 4, 13, 21, 21, 3, 6, 22, 5, 15, 8, 16, 26, 14, 9, 3, 20, 5, 29, 25, 2, 19, 9, 18, 27, -1, 1]

# b = 9
# powers = [29, 6, 13, 12, 24, 15, 16, 21, 0, 11, 0, 16, 18, 29, 16, 13, 30, 8, 30, -1, 25, 2, 5, 23, 19, 9, -1, 29, 25, 7, 6]
# [5, 24, 4, 22, -1, 30, 29, 12, 0, 30, 23, 0, 17, 24, 0, 19, 0, 7, 10, 17, 28, 0, 19, 19, -1, 17, 29, 19, 17, 13, 28] 

n = 31
k = 21
d = n - k + 1

F.<x> = GF(2)[]
K.<a> = GF(2^5, name='a', modulus=x^5 +x^2 + 1)
Q.<z> = PolynomialRing(K)

v = 0
for i, ei in enumerate(powers):
  if ei != -1:
    v = v + a ^ ei * z ^ i

sj = vector([v(a ^ j) for j in range(b, b + d - 1)])
M = Matrix([sj[i:i+errors] for i in range(0, errors)])
Mres = sj[errors:errors*2]
Lam = M.solve_right(Mres)
Lampoly = z^errors
for i in range(0, errors):
    Lampoly += z ^ i * Lam[i]
X_locations = list(filter(lambda i: Lampoly(a^i) == 0, range(n)))
X = vector(list(map(lambda i : a^i, X_locations)))
Lmu = Matrix([X.apply_map(lambda y : y ^ (b + i)) for i in range(0, errors)])
Y = Lmu.solve_right(sj[0:errors])
Y_powers = []
for elem in Y:
    for i in range(n):
        if (a ^ i == elem):
            Y_powers.append(i)
print("Error_locations:")
print(' '.join(map(str, X_locations)))
print("Error_values:")
print(' '.join(map(str, Y_powers)))
