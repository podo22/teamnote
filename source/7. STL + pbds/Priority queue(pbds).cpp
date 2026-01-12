/**
 * [Metadata]
 * Author : alreadysolved
 * [Tested on]
 * 
 */
// 큐 병합, 임의 값 수정 및 삭제 가능
#include <ext/pb_ds/priority_queue.hpp>
using namespace __gnu_pbds;
template <typename T>
using pbds_pq = __gnu_pbds::priority_queue<T, less<T>, pairing_heap_tag>;
int main() {
  pbds_pq<int> pq1, pq2;
  auto it = pq1.push(10); pq2.push(100);
  pq1.join(pq2); // O(1), pq1: {10, 100}, pq2: {}
  pq1.modify(it, 50); // O(logN), pq1 : {50, 100}
  pq1.erase(it); // O(logN), pq1: {100}
  pq1.top(); pq1.empty(); pq1.size(); pq1.pop(); // same
}