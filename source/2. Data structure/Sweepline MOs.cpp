const int MAXN = 200005, BSIZ = 450;
struct SqrtDecomp {
    ll lz_v[BSIZ+5], lz_c[BSIZ+5], v_arr[MAXN], c_arr[MAXN];
    ll total_v = 0, total_c = 0;
    void clear() { memset(this, 0, sizeof(*this)); }
    void update(int idx, ll v) { // O(sqrt N)
        total_v += v; total_c++;
        int b = idx / BSIZ;
        for (int i = idx; i < (b + 1) * BSIZ && i < MAXN; i++) {
            v_arr[i] += v; c_arr[i]++;
        }
        for (int i = b + 1; i <= BSIZ; i++) {
            lz_v[i] += v; lz_c[i]++;
        }
    }
    ll query(int idx, ll v) { // O(1)
        if (idx < 0) return (total_c * v - total_v); // 필요 시 수정
        ll cur_v = lz_v[idx / BSIZ] + v_arr[idx];
        ll cur_c = lz_c[idx / BSIZ] + c_arr[idx];
        return (cur_c * v - cur_v) + ((total_v - cur_v) - (total_c - cur_c) * v);
    }
} sd;
struct MoSweep {
    struct Query {
        int l, r, id; ll ans;
        bool operator<(const Query& o) const {
            if (l / BSIZ != o.l / BSIZ) return l < o.l;
            return (l / BSIZ) & 1 ? r < o.r : r > o.r;
        }
    };
    struct Delta { int q_idx, l, r; bool is_sub; };
    int n, q;
    ll A[MAXN], pref[MAXN], result[MAXN], rnk[MAXN];
    vector<Query> queries, sweep[MAXN];
    void init(int _n) {
        n = _n; queries.clear();
        for(int i = 0; i<=n; i++) sweep[i].clear();
    }
    void add_query(int l, int r, int id) { queries.push_back({l, r, id, 0}); }
    void build() {
        sort(queries.begin(), queries.end());
        sd.clear();
        for (int i = 1; i <= n; i++) {
            pref[i] = sd.query(rnk[i], A[i]);
            sd.update(rnk[i], A[i]);
        }
        int s = 1, e = 0;
        for (int i = 0; i < (int)queries.size(); i++) {
            int nl = queries[i].l, nr = queries[i].r;
            if (e < nr) sweep[s - 1].push_back({i, e + 1, nr, true}), e = nr;
            if (s > nl) sweep[e].push_back({i, nl, s - 1, false}), s = nl;
            if (e > nr) sweep[s - 1].push_back({i, nr + 1, e, false}), e = nr;
            if (s < nl) sweep[e].push_back({i, s, nl - 1, true}), s = nl;
        }
    }
    void solve() {
        sd.clear();
        for (int i = 1; i <= n; i++) {
            sd.update(rnk[i], A[i]);
            for (auto& d : sweep[i]) {
                ll tmp = 0;
                for (int k = d.l; k <= d.r; k++) tmp += sd.query(rnk[k], A[k]);
                queries[d.q_idx].ans += (d.is_sub ? -tmp : tmp);
            }
        }
        int s = 1, e = 0;
        for (int i = 0; i < (int)queries.size(); i++) {
            while (e < queries[i].r) queries[i].ans += pref[++e];
            while (s > queries[i].l) queries[i].ans -= pref[--s];
            while (e > queries[i].r) queries[i].ans -= pref[e--];
            while (s < queries[i].l) queries[i].ans += pref[s++];
            if (i > 0) queries[i].ans += queries[i - 1].ans;
            result[queries[i].id] = queries[i].ans;
        }
    }
} engine;
int main() {
    int n, q; cin >> n >> q;
    engine.init(n);
    vector<pair<ll,int>> v(n);
    for (int i = 1; i <= n; i++) {
        cin >> engine.A[i];
        v[i - 1] = {engine.A[i], i};
    }
    sort(v.begin(), v.end());
    for (int i = 0; i < n; i++) engine.rnk[v[i].second] = i;
    for (int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        engine.add_query(l, r, i);
    }
    engine.build();
    engine.solve();
    for (int i = 0; i < q; i++) cout << engine.result[i] << "\n";
    return 0;
}