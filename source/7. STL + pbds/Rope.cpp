#include<ext/rope>
using namespace __gnu_cxx;
int main() {
  string str; crope r(str.c_str()); // vector<T> v; rope<T> r(all(v));
  r.insert(pos, str); r.erase(pos, len); // Insert & Erase O(logN)
  r.replace(pos, len, str); // Replace O(logN)
  crope r2 = r; // O(1)
  r2 = r.substr(pos, len); // O(logN)
  r += r2; // Append O(logN)
  r[idx]; // O(logN), but for(auto i : r) is O(N)
  cout << r; // O(N)
}