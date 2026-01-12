/**
 * [Metadata]
 * Author : alreadysolved
 * [Tested on]
 * 
 */
struct custom_hash {
  template <class T>
  void combine(size_t& seed, const T& v) const {
    seed ^= hash<T>{}(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
  }
  template <class T1, class T2>
  size_t operator()(const pair<T1, T2>& p) const {
    size_t seed = 0; combine(seed, p.first); combine(seed, p.second);
    return seed;
  }
  template <class T>
  size_t operator()(const vector<T>& v) const {
    size_t seed = 0; for (const auto& i : v) combine(seed, i);
    return seed;
  }
};