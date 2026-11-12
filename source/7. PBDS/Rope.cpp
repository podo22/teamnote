/**
 * [Metadata]
 * Author : alreadysolved
 * [Tested on]
 * 
 */
#include <ext/rope>
using namespace __gnu_cxx;
int main() {
  string str; crope r(str.c_str()); // vector<T> v(N); rope<T> r(v.data(), N);
  r.insert(pos, str.c_str()); r.erase(pos, len);
  r.replace(pos, len, str.c_str());
  crope r2 = r; // O(1)
  r2 = r.substr(pos, len); // O(logN)
  r += r2; // Append O(logN)
  r[idx]; // O(logN), but for(auto i : r) is O(N)
  cout << r; // O(N)
}