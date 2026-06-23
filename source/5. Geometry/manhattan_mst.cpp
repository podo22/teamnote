/**
 * [Metadata]
 * Author : ychangseok(https://github.com/ychangseok/PS-template/blob/main/Geometry/manhattan_mst.cpp)
 * [Tested on]
 * 
 */
vector<array<ll, 3>> manhattan_mst(polygon v) {
  vector<int> idx(v.size());
  for (int i = 0; i < idx.size(); i++) idx[i] = i;
  vector<array<ll, 3>> edges;
  for (int rot = 0; rot < 4; rot++) {
    sort(idx.begin(), idx.end(), [&v](int i, int j){
      return (v[i].x + v[i].y) < (v[j].x + v[j].y);
    });
    map<int, int, greater<int>> active;
    for (auto i : idx) {
      for (auto it = active.lower_bound(v[i].x); it != active.end(); active.erase(it++)) {
        int j = it->second;
        if (v[i].x - v[i].y > v[j].x - v[j].y) break;
        edges.push_back({(v[i].x - v[j].x) + (v[i].y - v[j].y), i+1, j+1});
      }
      active[v[i].x] = i;
    }
    for (auto &p : v) {
      if (rot & 1) p.x *= -1;
      else swap(p.x, p.y);
    }
  }
  sort(all(edges));
  return edges;
}