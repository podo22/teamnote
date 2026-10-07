/**
 * [Metadata]
 * Original Author : jinhan814
 * Source : https://blog.naver.com/jinhan814/222689836982
 * Edited by : alreadysolved
 * [Tested on]
 * 
 */
using i128 = __int128;
// 기본: max, 기울기 a 단조증가, 쿼리 x 단조증가
// max: a↑ x↑ 그대로 / a↓ x↓ add의 교점 비교 양변 교환
// min: a↓ x↑ 그대로 / a↑ x↓ add의 교점 비교 양변 교환
// min은 추가로 같은 기울기 처리 >=를 <=로, query의 <=를 >=로 변경
// add/query 각각 amortized O(1)
struct PLL { ll x, y;
  PLL(const ll x = 0, const ll y = 0) : x(x), y(y) {}
  bool operator<= (const PLL& i) const {
    return (i128)x * i.y <= (i128)i.x * y; }
};
struct ConvexHull {
  static i128 F(const PLL& i, const ll x) { return (i128)i.x * x + i.y; }
  static PLL C(const PLL& a, const PLL& b) { return { a.y - b.y, b.x - a.x }; }
  deque<PLL> S;
  void add(const ll a, const ll b) {
    if (!S.empty() && S.back().x == a) {
      if (S.back().y >= b) return; // min: <=
      S.pop_back();
    }
    // max a↓ / min a↑: 아래 <=의 양변 교환
    while ( S.size() > 1 && C(S.back(), PLL(a, b)) <= C(S[S.size() - 2], S.back()) ) S.pop_back();
    S.push_back(PLL(a, b));
  }
  ll query(const ll x) {
    assert(!S.empty());
    while (S.size() > 1 && F(S[0], x) <= F(S[1], x)) // min: >=
      S.pop_front();
    return F(S[0], x);
  }
} CHT;