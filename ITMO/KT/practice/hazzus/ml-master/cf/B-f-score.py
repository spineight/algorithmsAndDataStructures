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
    return macro, f(micro_p, micro_r)

k = int(input())
classes = list(range(k))
mat = {name: {n: 0 for n in classes} for name in classes}
for cls in classes:
    r = list(map(int, input().split()))
    mat[cls] = {i: r[i] for i in range(k)}

macro, micro = f_score(mat)
print(micro)
print(macro)



