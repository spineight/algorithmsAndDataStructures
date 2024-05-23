DEBUG = True


def trace(f):
    if not DEBUG:
        return f

    def inner(*args, **kwargs):
        call = ", ".join(
            [str(a) for a in args] + [f"{k}={v}" for k, v in kwargs]
        )
        print(f"{f.__name__}({call}) = ...")
        ret = f(*args, **kwargs)
        print(f"{f.__name__}({call}) = {ret}")
        return ret

    inner.__name__ = f.__name__
    inner.__doc__ = f.__doc__
    inner.__module__ = f.__module__

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
