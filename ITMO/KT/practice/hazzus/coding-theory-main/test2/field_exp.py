import numpy as np
import sympy as sy

# task 1
poly = [1, 0, 2, 1]
deg = 3  # max number of elements in remainder poly

# task 2
end = 26  # experimental, when table starts giving 1 as remainder again
s1 = 60 % end
s2 = 52 % end
s3 = 125 % end
s4 = 107 % end
s5 = 290 % end

# task 5
poly5 = [1, 0, 1]


def pretty(pol):
    a = sy.Symbol('a')
    s = 0
    w = len(pol) - 1
    for c in pol:
        s += int(c) * a ** w
        w -= 1
    return str(s).replace("**", "^").replace("*", "")


if __name__ == "__main__":
    table = {}
    revtable = {}
    print('Polynom to check:', pretty(poly))
    # Task 1
    for i in range(0, end):
        div = np.polydiv([1] + [0] * i, poly)
        # remainder is in 1 of div and need to be mod by 3 each coef
        rem = list(np.mod(div[1], 3))
        # filling leading zeroes
        rem = [0] * max(0, deg - len(rem)) + rem

        res = pretty(rem)
        if i != 0:
            print(i, '|', res)
        table[i] = rem
        revtable[tuple(rem)] = i

    # Task 2
    print('Equation from: (a^{} + a^{}) * a^{} / (a^{} + a^{})'.format(s1, s2, s3, s4, s5))
    sumres = np.mod(np.polydiv(np.polyadd(table[s1], table[s2]), poly)[1], 3)
    print(
        'First step: a^{} + a^{} = ({} + {}) mod ({}) = {} = a^{}'.format(s1, s2, pretty(table[s1]), pretty(table[s2]),
                                                                          pretty(poly), pretty(sumres),
                                                                          revtable[tuple(sumres)]))

    mulres = (s3 + revtable[tuple(sumres)]) % end
    print('Second step: a^{} * a^{} = a^{}'.format(revtable[tuple(sumres)], s3, mulres))

    sumres1 = np.mod(np.polydiv(np.polyadd(table[s4], table[s5]), poly)[1], 3)
    print(
        'Third step: a^{} + a^{} = ({} + {}) mod ({}) = {} = a^{}'.format(s4, s5, pretty(table[s4]), pretty(table[s5]),
                                                                          pretty(poly), pretty(sumres1),
                                                                          revtable[tuple(sumres1)]))

    divres = (mulres - revtable[tuple(sumres1)]) % end
    print('Last step: a^{} / a^{} = a^{}'.format(mulres, revtable[tuple(sumres1)], divres))
    print('Equation: x^{}'.format(divres))

    # Task 3
    start = [0, 1]
    els = []
    while start <= [2, 2]:
        # print(start)

        current = start.copy()
        # print('---')
        for p in range(1, 8):
            current = [0] * (2 - len(current)) + current
            if list(current) == [0, 1]:
                # pass
                # print('SOBAKA')
                print(pretty(start), '| power:', p)
                els.append(pretty(start))
                break
            # print(p, startc)
            current = list(np.mod(np.polydiv(np.polymul(current, start), poly5)[1], 3))
        # print('---')

        # inc start
        start[1] += 1
        if start[1] > 2:
            start[1] = 0
            start[0] += 1

    print('Elements:', *els)
