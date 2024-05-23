def max(*args):
    """Finds the largest argument."""
    print(f"max{args} = ...")
    ret = 0
    for x in args:
        ret = ret if x < ret else x
    print(f"max{args} = {ret}")
    return ret


def foo():
    max(-10, -1, -3)


foo()
