
def str_to_exponent(s: str):
    if s == "p":
        return 10 ** -12
    elif s == "n":
        return 10 ** -9
    elif s == "u":
        return 10 ** -6
    elif s == "K":
        return 10 ** 3
    elif s == "M":
        return 10 ** 6
    else:
        return 1

def in_range(val: float, min: int, max: int):
    return val >= min and val <= max
