import functools


def once(f):
    called = False

    @functools.wraps(f)
    def inner(*args, **kwargs):
        nonlocal called
        if called:
            return
        called = True
        res = f(*args, **kwargs)
        assert res is None

    return inner


LOGGER = None


@once
def init_logger():
    global LOGGER
    print("initializing logger")
    LOGGER = ...


init_logger()
init_logger()
