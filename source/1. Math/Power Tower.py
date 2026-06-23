def power_tower_solve(a, n, mod):
    # calculate a[0]^(a[1]^...) % mod
    # n = len(a)
    # mod < 2**30
    if mod == 1:
        return 0
    if n == 0:
        return 1 % mod
    if n == 1:
        return a[0] % mod
    if n == 2:
        return power(a[0], a[1], mod)
    if n == 3 and (a[1:] in [[2, 2], [2, 3], [2, 4], [3, 2], [3, 3], [4, 2], [5, 2]]):
        return power(a[0], a[1] ** a[2], mod)
    if n == 4 and a[1:] == [2, 2, 2]:
        return power(a[0], 16, mod)
    pmod = phi(mod)
    return power(a[0], power_tower_solve(a[1:], n - 1, pmod) + 30 * pmod, mod)