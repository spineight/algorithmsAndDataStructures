from itertools import combinations


def is_dependend(lists):
    sum = 0
    for i in range(len(lists[0])):
        count = 0
        for j in range(len(lists)):
            count ^= lists[j][i]
        sum += count
    return sum == 0


def transpose(matrix, rows, cols):
    res = [[0 for _ in range(rows)] for _ in range(cols)]
    for i in range(rows):
        for j in range(cols):
            res[j][i] = matrix[i][j]
    return res


def find_distance(matrix, rows, cols):
    for l in range(1, cols + 1):
        for subset in combinations(transpose(matrix, rows, cols), l):
            if is_dependend(subset):
                print("dependend cols: " + str(subset))
                return l
    raise ValueError("No dependend rows found")


if __name__ == "__main__":
    G = [
        [1, 0, 0, 0, 0, 0, 1, 1, 1],
        [0, 1, 0, 0, 1, 0, 1, 1, 0],
        [0, 0, 1, 0, 1, 1, 0, 0, 1],
        [0, 0, 0, 1, 1, 0, 1, 0, 1]
    ]
    H = [
        [0, 1, 1, 1, 1, 0, 0, 0, 0],
        [0, 0, 1, 0, 0, 1, 0, 0, 0],
        [1, 1, 0, 1, 0, 0, 1, 0, 0],
        [1, 1, 0, 0, 0, 0, 0, 1, 0],
        [1, 0, 1, 1, 0, 0, 0, 0, 1]
    ]
    print("dual min dist:", find_distance(G, 4, 9))
    print("straight min dist:", find_distance(H, 5, 9))
