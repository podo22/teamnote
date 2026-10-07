/**
 * [Metadata]
 * Original Author : DeobureoMinkyuParty & JusticeHui
 * Reference : https://github.com/justiceHui/icpc-teamnote/blob/master/code/Geometry/HPI.cpp
 * Modified by : alreadysolved
 * [Tested on]
 * 
 */
// Line(p1,p2): p1 -> p2의 오른쪽 반평면, 경계 포함. p1 != p2.
// 유효 영역: a*x + b*y <= c.
// CCW 다각형 내부를 취하려면 Line(다음 정점, 현재 정점).
struct Line {
  double a, b, c; // ax + by <= c
  Line(Pd p1, Pd p2) {
    a = p1.y - p2.y; // -dy
    b = p2.x - p1.x; // dx
    c = a * p1.x + b * p1.y;
  }
  Pd slope() const { return {a, b}; }
};
Pd intersect(Line u, Line v) { // 평행하지 않은 두 직선의 교점
  double det = u.a * v.b - u.b * v.a;
  return {(u.c * v.b - u.b * v.c) / det, (u.a * v.c - u.c * v.a) / det};
}
bool bad(Line l, Pd p) {
  return l.a * p.x + l.b * p.y > l.c + EPS;
}
// 유계·양의 면적 교집합의 꼭짓점을 구함. O(N log N).
// 빈 영역/점/선분/무계 영역의 판별은 보장하지 않음.
// EPS 정렬 조건: 비평행 법선 간 외적의 절댓값이 EPS보다 커야 함.
vector<Pd> HPI(vector<Line> lines) {
  sort(all(lines), [&](const Line& u, const Line& v) {
    Pd p1 = u.slope(), p2 = v.slope();
    bool f1 = p1.y > 0 || (p1.y == 0 && p1.x > 0);
    bool f2 = p2.y > 0 || (p2.y == 0 && p2.x > 0);
    if (f1 != f2) return f1 > f2;
    if (abs(p1 / p2) > EPS) return (p1 / p2) > 0;
    return u.c < v.c; // 같은 방향 평행선은 법선 길이가 같아야 c 비교가 유효
  });
  deque<Line> dq;
  for (auto& l : lines) {
    if (!dq.empty() && abs(dq.back().slope() / l.slope()) < EPS) continue;
    while (sz(dq) >= 2 && bad(l, intersect(dq.back(), dq[sz(dq)-2]))) dq.pop_back();
    while (sz(dq) >= 2 && bad(l, intersect(dq[0], dq[1]))) dq.pop_front();
    dq.push_back(l);
  }
  while (sz(dq) > 2 && bad(dq[0], intersect(dq.back(), dq[sz(dq)-2]))) dq.pop_back();
  while (sz(dq) > 2 && bad(dq.back(), intersect(dq[0], dq[1]))) dq.pop_front();
  vector<Pd> res; if (sz(dq) < 3) return {};
  for (int i = 0; i < sz(dq); i++) {
    res.push_back(intersect(dq[i], dq[(i + 1) % sz(dq)]));
  }
  return res;
}