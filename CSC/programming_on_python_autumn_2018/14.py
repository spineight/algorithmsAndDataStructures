import time
import functools


def profile(f):
    @functools.wraps(f)
    def inner(*args, **kwargs):
        start = time.perf_counter()
        ret = f(*args, **kwargs)
        elapsed = time.perf_counter() - start

        inner.__total_time__ += elapsed
        inner.__n_calls__ += 1

        return ret

    inner.__total_time__ = 0
    inner.__n_calls__ = 0
    return inner


@profile
def max(*args):
    """Finds the largest argument."""
    ret = 0
    for x in args:
        ret = ret if x < ret else x
    return ret


def foo():
    max(-10, -1, -3)


foo()

print(max.__total_time__)
print(max.__n_calls__)