ll ternary_search(ll lo, ll hi, auto f) {
    while (hi - lo >= 3) {
        ll p = lo + (hi-lo) / 3, q = hi - (hi-lo) / 3;
        if (f(p) < f(q)) hi = q; // for max: f(p) > f(q)
        else lo = p;
    }
    ll res = lo;
    for (ll i = lo+1; i <= hi; i++) if (f(i) < f(res)) res = i;
    return idx;
}
double ternary_search(double lo, double hi, auto f, int it=100) {
    while (it--) {
        double p = (lo*2 + hi) / 3., q = (lo + hi*2) / 3.;
        if (f(p) < f(q)) hi = q; // for max: f(p) > f(q)
        else lo = p;
    }
    return (lo+hi) / 2.;
}