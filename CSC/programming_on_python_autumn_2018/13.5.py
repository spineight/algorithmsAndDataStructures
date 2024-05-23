import warnings


def deprecated(f):
    def inner(*args, **kwargs):
        warnings.warn(f"{f.__name__} is deprecated",
                      category=DeprecationWarning)
        return f(*args, **kwargs)

    return inner


@deprecated
def foo():
    return 1


foo()
foo()
foo()
