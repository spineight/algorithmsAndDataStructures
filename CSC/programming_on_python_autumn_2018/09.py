import functools

DEBUG = True


def trace(f):
    if not DEBUG:
        return f

    @functools.wraps(f)
    def inner(*args, **kwargs):
        call = ", ".join(
            [str(a) for a in args] + [f"{k}={v}" for k, v in kwargs]
        )
        print(f"{f.__name__}({call}) = ...")
        ret = f(*args, **kwargs)
        print(f"{f.__name__}({call}) = {ret}")
        return ret

    return inner


@trace
def max(*args):
    """Finds the largest argument."""
    ret = 0
    for x in args:
        ret = ret if x < ret else x
    return ret


def foo():
    max(-10, -1, -3)


foo()
