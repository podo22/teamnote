ll ternary_search(ll lo, ll hi, auto f) {
    while (hi - lo >= 3) {
        ll p = lo + (hi - lo) / 3, q = hi - (hi - lo) / 3;
        if (f(p) < f(q)) hi = q;
        else lo = p;
    }
    ll idx = lo; auto minv = f(lo);
    for (ll i = lo+1; i <= hi; i++) {
        auto v = f(i);
        if (v < minv) {
            minv = v; idx = i;
        }
    }
    return idx;
}
double ternary_search(double lo, double hi, auto f, int iter = 100) {
    for (int i = 0; i < iter; i++) {
        double p = (lo*2 + hi) / 3., q = (lo + hi*2) / 3.;
        if (f(p) < f(q)) hi = q;
        else lo = p;
    }
    return (lo+hi) / 2.;
}