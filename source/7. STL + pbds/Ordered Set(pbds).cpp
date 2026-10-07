/**
 * [Metadata]
 * Author : alreadysolved
 * [Tested on]
 * 
 */
// k번째 원소확인 및 x보다 작은 원소개수확인 O(logN)
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// ordered_set<int> os;
// os.find_by_order(k): k번째 원소 iter(0-idx, 없으면 os.end())
// os.order_of_key(x) : x  미만 개수
template <typename T>
using ordered_mset = ordered_set<pair<T, int>>;
template <typename T>
auto m_find(ordered_mset<T>& os, T x) {
  auto it = os.lower_bound({x, 0});
  return it != os.end() && it->first == x ? it : os.end();
}
// ordered_mset<int> oms; int id = 0;
// oms.insert({x, id++}); auto it = m_find(oms, x);
// if (it != oms.end()) oms.erase(it);
// oms.find_by_order(k): k번째 값 (0-idx), k < size
// oms.order_of_key({x, 0} or {x, INF}) : x 미만 or 이하 개수