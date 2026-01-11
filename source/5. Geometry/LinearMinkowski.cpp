// Minkowski Sum of Convex Polygons (CCW only), O(N + M)
vector<P> Minkowski(vector<P> p, vector<P> q) {
  if (p.empty() || q.empty()) return {};
  rotate(p.begin(), min_element(all(p)), p.end());
  rotate(q.begin(), min_element(all(q)), q.end());
  p.push_back(p[0]); p.push_back(p[1]);
  q.push_back(q[0]); q.push_back(q[1]);
  vector<P> res; int i = 0, j = 0;
  while (i < p.size() - 2 || j < q.size() - 2) {
    res.push_back(p[i] + q[j]);
    ll cp = (p[i + 1] - p[i]) / (q[j + 1] - q[j]);
    if (cp >= 0 && i < p.size() - 2) i++;
    if (cp <= 0 && j < q.size() - 2) j++;
  }
  return res;
}