/**
 * [Metadata]
 * Author : alreadysolved
 * [Tested on]
 * 
 */
// k번째 원소 확인 및 x보다 작은 원소개수 확인을 O(logN)에 수행
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// ordered_set<int> os;
// os.find_by_order(k): k번째 원소의 iterator 반환 (0-indexed, 없으면 os.end())
// os.order_of_key(x) : x보다 작은 원소의 개수 반환
template <typename T>
using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
auto m_find(ordered_multiset<int> &os, int val) { // multiset 전용 find 함수
  int idx = os.order_of_key(val); auto it = os.find_by_order(idx);
  if (it != os.end() && *it == val) return it;
  return os.end();
} // os.erase(m_find(os, val))