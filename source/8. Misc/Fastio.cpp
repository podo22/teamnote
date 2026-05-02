/**
 * [Metadata]
 * Author : alreadysolved
 * [Tested on]
 * 
 */
struct FastIO {
  static constexpr int SZ = 1 << 16;
  char rb[SZ], wb[SZ];
  char *p1 = rb, *p2 = rb, *pp = wb;
  inline char getc() {
    return p1 == p2 && (p2 = (p1 = rb) + fread(rb, 1, SZ, stdin), p1 == p2) ? -1 : *p1++;
  }
  inline void putc(char c) {
    if (pp == wb + SZ) fwrite(wb, 1, SZ, stdout), pp = wb;
    *pp++ = c;
  }
  void read(auto &x) {
    x = 0; char c = getc(); bool f = 0;
    while (c != -1 && (c < '0' || c > '9')) { if (c == '-') f = 1; c = getc(); }
    while (c >= '0' && c <= '9') x = x * 10 + (c ^ 48), c = getc();
    if (f) x = -x;
  }
  void write(auto x) {
    if (x < 0) putc('-'), x = -x;
    static char t[20]; int ti = 0;
    do t[ti++] = (x % 10) ^ 48; while (x /= 10);
    while (ti) putc(t[--ti]);
  }
  ~FastIO() { fwrite(wb, 1, pp - wb, stdout); }
} io;