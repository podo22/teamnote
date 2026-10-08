/**
 * [Metadata]
 * Author : alreadysolved
 * [Tested on]
 * 
 */
sort(all(v)); // Permutation
do {
  // process v
} while (next_permutation(all(v)));
vector<int> mask(n, 0); // Combination(nCk)
fill(mask.end()-r, mask.end(), 1); // pick r
do {
  for (int i = 0; i < n; i++) if (mask[i]) {
    /* v[i] is selected */ }
} while (next_permutation(all(mask)));
sort(all(v)); // Partial Permutation (nPk)
do {
  for(int i = 0; i < k; i++) { /* use v[i] */ }
  reverse(v.begin()+k, v.end());
} while (next_permutation(all(v)));