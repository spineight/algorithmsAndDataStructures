from itertools import combinations
from functools import reduce


def transpose(matrix, rows, cols):
    res = [[0 for _ in range(rows)] for _ in range(cols)]
    for i in range(rows):
        for j in range(cols):
            res[j][i] = matrix[i][j]
    return res


def all_combinations(lst):
    list_with_tags = list(enumerate(lst))
    for l in range(0, len(list_with_tags) + 1):
        for subset in combinations(list_with_tags, l):
            yield subset


def xor_vectors(a, b):
    return [p1 ^ p2 for (p1, p2) in zip(a, b)]


def get_syndrome_table(matrix, rows, cols):
    p = 2 ** cols
    table = [[0 for _ in range(rows + cols)] for _ in range(p)]
    for i in range(p):
        bin_form = bin(i)[2:].zfill(cols)
        for (j, c) in enumerate(bin_form):
            table[i][j] = c
        for subset in all_combinations(matrix):
            sum = reduce(lambda x, y: xor_vectors(x, y[1]), subset, [0] * cols)
            num = int("".join(list(map(str, sum))), 2)
            if num == i:
                for v in subset:
                    table[i][cols + v[0]] = 1
                break
    return table


def pr_print(matrix, rows, cols):
    for i in range(2 ** cols):
        for j in range(cols):
            print(matrix[i][j], end='')
        print(' ', end='')
        for j in range(rows):
            print(matrix[i][cols + j], end='')
        print('')


if __name__ == "__main__":
    H = [
        [1, 0, 1, 0, 1, 0, 1, 0, 0],
        [0, 0, 0, 0, 1, 0, 0, 1, 1],
        [1, 0, 1, 1, 1, 0, 0, 1, 0],
        [0, 1, 0, 1, 1, 1, 0, 0, 0],
        [1, 0, 0, 1, 1, 1, 0, 0, 0]
    ]
    Ht = transpose(H, 5, 9)
    pr_print(get_syndrome_table(Ht, 9, 5), 9, 5)
