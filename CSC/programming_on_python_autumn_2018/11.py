import functools
import sys

DEBUG = True


def trace(stream=sys.stdout):
    def decorator(f):
        if not DEBUG:
            return f

        @functools.wraps(f)
        def inner(*args, **kwargs):
            call = ", ".join(
                [str(a) for a in args] + [f"{k}={v}" for k, v in kwargs]
            )
            print(f"{f.__name__}({call}) = ...", file=stream)
            ret = f(*args, **kwargs)
            print(f"{f.__name__}({call}) = {ret}", file=stream)
            return ret

        return inner
    return decorator


@trace(sys.stderr)
def max(*args):
    """Finds the largest argument."""
    ret = 0
    for x in args:
        ret = ret if x < ret else x
    return ret

def foo():
    max(-10, -1, -3)


foo()
