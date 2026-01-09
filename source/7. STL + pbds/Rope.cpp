#include<ext/rope>
using namespace __gnu_cxx;
int main() {
    string str; cin >> str;
    crope r(str.c_str());
    // vector<T> v; rope<T> r(v);
    r.insert(pos, str); // Insert O(logN)
    r.erase(pos, len); // Erase O(logN)
    r.replace(pos, len, str); // Replace O(logN)
    crope r2 = r; // O(1)
    r2 = r.substr(pos, len); // O(logN + len)
    r += r2; // Append O(logN + len(r2))
    r[idx]; // O(logN)
    for (auto i : r) // Traversal O(N)?
    cout << r;
}