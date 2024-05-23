import functools


@functools.singledispatch
def json(obj):
    assert False, f"{type(obj)} not supported: {obj}"


@json.register(int)
def _(i):
    return str(i)


@json.register(str)
def _(s):
    return f'"{s}"'  # TODO: escape


@json.register(list)
def _(l):
    elements = ", ".join(map(json, l))
    return f"[{elements}]"


@json.register(dict)
def _(d):
    elements = ", ".join(f'"{k}": {json(v)}' for k, v in d.items())
    return f"{{{elements}}}"


xs = [1, 2, "hello", {'foo': []}]

print(json(xs))
