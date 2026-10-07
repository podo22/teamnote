/**
 * [Metadata]
 * Author : ychangseok(https://github.com/ychangseok/PS-template/blob/main/Geometry/convex_hull_3d.cpp)
 * [Tested on]
 * 
 */
struct face { int a, b, c; P d; };
vector<face> ConvexHull_3d(vector<P> &p) {
  compress(p); int n = sz(p);
  if (n <= 3) return {};
  int k = 2;
  while (k < n && ((p[1]-p[0]) / (p[k]-p[0])) == P{0, 0, 0}) k++;
  if (k == n) return {};
  swap(p[2], p[k]);
  k = 3;
  while (k < n && (((p[1]-p[0]) / (p[2]-p[0])) * (p[k]-p[0])) == 0) k++;
  if (k == n) return {};
  swap(p[3], p[k]);
  vector<face> f;
  vector<vector<bool>> dead(n, vector<bool>(n, true));
  auto add_face = [&](int a, int b, int c) {
    f.push_back({ a, b, c, (p[b]-p[a]) / (p[c]-p[a]) });
    dead[a][b] = dead[b][c] = dead[c][a] = 0;
  };
  add_face(0, 1, 2); add_face(0, 2, 1);
  for (int i = 3; i < n; i++) {
    vector<face> nf;
    for (face &F : f){
      if ((p[i] - p[F.a]) * F.d > 0) {
        dead[F.a][F.b] = dead[F.b][F.c] = dead[F.c][F.a] = 1;
      } else {
        nf.push_back(F);
      }
    }
    f = nf;
    for (face &F : nf){
      if (dead[F.b][F.a]) add_face(F.b, F.a, i);
      if (dead[F.c][F.b]) add_face(F.c, F.b, i);
      if (dead[F.a][F.c]) add_face(F.a, F.c, i);
    }
  }
  return f;
}