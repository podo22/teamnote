def order(n, g):
    # return order of g in Zn
    phin = phi(n)
    fact = factorization(phin)
    ans = phin
    for [p, k] in fact:
        tmp = phin
        for i in range(k):
            tmp //= p
            if pow(g, tmp, n) != 1:
                break
            ans //= p

    return ans