/**
 * [Metadata]
 * Author : alreadysolved
 * [Tested on]
 * 
 */
// 1. Subset Sum: f[mask] = sum of a[sub] where sub & mask == sub
for (int i = 0; i < n; ++i)
    for (int mask = 0; mask < (1 << n); ++mask)
        if (mask & (1 << i)) f[mask] += f[mask ^ (1 << i)];

// 2. Superset Sum: f[mask] = sum of a[sup] where sup & mask == mask
for (int i = 0; i < n; ++i)
    for (int mask = (1 << n) - 1; mask >= 0; --mask)
        if (!(mask & (1 << i))) f[mask] += f[mask ^ (1 << i)];