/**
 * [Metadata]
 * Author : ychangseok(https://github.com/ychangseok/PS-template/blob/main/Geometry/manhattan_mst.cpp)
 * [Tested on]
 * 
 */
vector<array<ll,3>> manhattan_mst(vector<P> v) {
  vector<int> idx(sz(v));
  for (int i = 0; i < sz(idx); i++) idx[i] = i;
  vector<array<ll,3>> ev;
  for (int rot = 0; rot < 4; rot++) {
    sort(all(idx), [&v](int i, int j){ return (v[i].x+v[i].y) < (v[j].x+v[j].y); });
    map<ll,int,greater<ll>> act;
    for (auto i : idx) {
      for (auto it = act.lower_bound(v[i].x); it != act.end(); act.erase(it++)) {
        int j = it->second;
        if (v[i].x-v[i].y > v[j].x-v[j].y) break;
        ev.push_back({(v[i].x-v[j].x) + (v[i].y-v[j].y), i+1, j+1});
      }
      act[v[i].x] = i;
    }
    for (auto &p : v) {
      if (rot & 1) p.x *= -1;
      else swap(p.x, p.y);
    }
  }
  sort(all(ev));
  return ev;
}