// alias gpp='g++ -std=c++20 -Wall -Wextra -O2 -fsanitize=address,undefined -DLOCAL'
#ifdef LOCAL
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]: ", __dbg(__VA_ARGS__)
#else
#define debug(...)
#endif
template<typename T, typename U> ostream& operator<<(ostream& os, const pair<T, U>& p) {
  return os << "{" << p.first << ", " << p.second << "}";
}
template<typename T> concept Iter = ranges::range<T> && !convertible_to<T, string_view>;
template<Iter T> ostream& operator<<(ostream& os, const T& v) {
  os << "["; string s;
  for (auto& x : v) os << s << x, s = ", ";
  return os << "]";
}
void __dbg() { cerr << endl; }
template<typename T, typename... V> void __dbg(T t, V... v) {
  cerr << t << (sizeof...(v) ? ", " : ""); __dbg(v...);
}