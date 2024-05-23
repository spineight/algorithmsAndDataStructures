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
@functools.lru_cache(maxsize=None)
def fib(n):
    return 1 if n <= 1 else fib(n - 1) + fib(n - 2)


print(fib(20))
print(fib.__total_time__)
print(fib.__n_calls__)
