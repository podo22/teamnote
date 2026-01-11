#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/trie_policy.hpp>
using namespace __gnu_pbds;
typedef trie<string, null_type, trie_string_access_traits<>, pat_trie_tag, trie_prefix_search_node_update> trie_set;
int main() {
  trie_set t; t.insert("apple"); t.insert("app"); t.insert("banana");
  if (t.find("app") != t.end()) { /* found app */ }
  auto [st, en] = t.prefix_range("ba");
  for (auto it = st; it != en; it++) { cout << *it << "\n"; /* banana */ }
  *t.lower_bound("app"); // app
  *t.upper_bound("app"); // apple
  t.split("b", t2); // t: {app, apple}, t2: {banana}
  t.erase("apple");
}