typedef long long ll;
ll modmul(ll a, ll b, ll m) {
    return (__int128)a * b % m;
}
ll modpow(ll b, ll e, ll m) {
	ll ans = 1;
	for (; e; b = modmul(b, b, m), e /= 2)
		if (e & 1) ans = modmul(ans, b, m);
	return ans;
}
ll xgcd(ll a, ll b, ll &x, ll &y) {
    if (!b) return x = 1, y = 0, a;
    ll x1, y1, g = xgcd(b, a % b, x1, y1);
    return x = y1, y = x1 - a / b * y1, g;
}
ll modinv(ll a, ll m) {
    ll x, y;
    ll g = xgcd(a, m, x, y);
    if (g != 1) return -1;
    return (x%m + m) % m;
}