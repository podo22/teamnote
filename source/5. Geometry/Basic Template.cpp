const double EPS = 1e-9;
template<typename T>
struct Point {
  T x, y;
  bool operator<(const Point& p) const { return x==p.x ? y<p.y : x<p.x; }
  bool operator==(const Point& p) const { return x==p.x && y==p.y; }
  Point operator+(const Point& p) const { return {x+p.x, y+p.y}; }
  Point operator-(const Point& p) const { return {x-p.x, y-p.y}; }
  Point operator*(T n) const { return {x*n, y*n}; }
  Point operator/(T n) const { return {x/n, y/n}; }
  T operator*(const Point& p) const { return x*p.x + y*p.y; }
  T operator/(const Point& p) const { return x*p.y - y*p.x; }
  /* 3D dot, cross
  T operator*(const Point& p) const { return x*p.x + y*p.y + z*p.z; }
  Point operator/(const Point& p) const { 
    return {y*p.z - z*p.y, z*p.x - x*p.z, x*p.y - y*p.x}; 
  } */
  T dist2() const { return x*x + y*y; }
  Point<double> d() const { return {(double)x, (double)y}; }
  Point rot90() const { return {-y, x}; }
};
using P = Point<ll>;
using Pd = Point<double>;
int ccw(P a, P b, P c) {
  ll res = (b - a) / (c - a);
  return (res > 0) - (res < 0);
}
bool isInter(P a, P b, P c, P d) {
  int ab = ccw(a, b, c) * ccw(a, b, d), cd = ccw(c, d, a) * ccw(c, d, b);
  if (ab == 0 && cd == 0) {
    if (b < a) swap(a, b); if (d < c) swap(c, d);
    return !(b < c || d < a);
  }
  return ab <= 0 && cd <= 0;
}