/**
 * [Metadata]
 * Author : ychangseok(https://github.com/ychangseok/PS-template/blob/main/Geometry/convex_hull_3d.cpp)
 * [Tested on]
 * 
 */
struct face{ int a, b, c; PT d; };
vector<face> convex_hull_3d(vector<PT> &p) {
  // https://codeforces.com/blog/entry/81768
  // -1. 중복 점 제거 (normalize 등하면 중복 점이 생길 수도 있다)
  // 0. size <= 3 -> exit
  // 1. 전부 한 직선 위에 있는지 판정 yes -> exit
  // 2. first 3 points are not on the same line일 때까지 셔플하고 전부 한 평면 위에 있는 지 판정 yes -> exit
  int n = p.size();
  if (n <= 3) exit(1);
  while (true) {
    // shuffle until first 4 points are not on the same plane
    shuffle(all(p), mt19937(random_device{}()));
    if (((p[1]-p[0])^(p[2]-p[0])) * (p[3]-p[0]) != 0) break;
  }
  vector<face> f;
  vector<vector<bool>> dead(n, vector<bool>(n, true));
  auto add_face = [&](int a, int b, int c) {
    f.push_back({a, b, c, (p[b]-p[a])^(p[c]-p[a])});
    dead[a][b] = dead[b][c] = dead[c][a] = false;
  };
  add_face(0, 1, 2); add_face(0, 2, 1);
  for (int i = 3; i < n; i++) {
    vector<face> nf;
    for (face &F : f){
      if ((p[i] - p[F.a]) * F.d > 0) {
        dead[F.a][F.b] = dead[F.b][F.c] = dead[F.c][F.a] = true;
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