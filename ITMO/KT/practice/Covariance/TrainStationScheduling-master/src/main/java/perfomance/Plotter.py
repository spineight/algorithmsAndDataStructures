import matplotlib.pyplot as plt


def read_times(filename):
    f = open(filename, 'r', encoding='utf-8')
    content = f.read().split('\n')
    arr = [int(''.join(line.split(' ')[0].split(u'\u202f'))) for line in content]
    f.close()
    return arr


def ask(type):
    print('Enter name of file with ' + type + ' times:')
    return read_times(input() + '_performance.txt')


naiveTimes = ask('naive')
optimizedTimes = ask('optimized')
print("Enter value of step in native language:")

plt.xlabel('Количество поездов, ' + input())
plt.ylabel('Время, миллисекунды')
plt.plot(naiveTimes, 'r')
plt.plot(optimizedTimes[:len(naiveTimes)], 'b')
print('Enter name of resulting file:')
# plt.plot([(80 + x * x * 120 / (1000 * 1000)) for x in range(1, 1001)], 'g')
# plt.show()
plt.savefig(input(), quality=95, format='jpg')
