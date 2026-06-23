def discrete_log(p, g, h):
    # return x in [0, p) s.t. g^x = h (mod p)
    from math import isqrt
    m = dict()
    b = isqrt(p-1)+1
    for v in range(b):
        tmp = pow(g, p-2, p)
        m[h*pow(g, v*(p-2), p)%p] = v
    ans = p
    g = pow(g, b, p)
    for u in range(b):
        tmp = pow(g, u, p)
        if tmp in m.keys():
            ans = u*b + m[tmp]
            break
    return ans