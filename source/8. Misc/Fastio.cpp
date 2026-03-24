/**
 * [Metadata]
 * Original Author : jinhan814
 * Source : https://infossm.github.io/blog/2025/04/25/fastio-1/
 * [Tested on]
 * 
 */
#include <unistd.h>
constexpr int rbuf_sz = 1 << 20, wbuf_sz = 1 << 20;
int main() {
	char r[rbuf_sz], *pr = r; int rsz = read(0, r, rbuf_sz);
	auto read_char = [&] {
		if (pr - r == rsz) rsz = read(0, pr = r, rbuf_sz);
		return *pr++;
	};
	auto read_int = [&] {
		ll ret = 0, flag = 0; char c = read_char();
		while (c == ' ' || c == '\n') c = read_char();
		if (c == '-') flag = 1, c = read_char();
		while (c != ' ' && c != '\n') ret = 10 * ret + c - '0', c = read_char();
		if (flag) ret = -ret;
		return ret;
	};
	char w[wbuf_sz], *pw = w;
	auto write_char = [&](char c) {
		if (pw-w == wbuf_sz) write(1, w, pw-w), pw = w;
		*pw++ = c;
	};
	auto write_int = [&](ll x) {
		if (pw-w+40 > wbuf_sz) write(1, w, pw-w), pw = w;
		if (x < 0) *pw++ = '-', x = -x;
		char t[20], *pt = t;
		do *pt++ = x % 10 + '0'; while (x /= 10);
		do *pw++ = *--pt; while (pt != t);
	};
	auto write_str = [&](string s) {
		for (auto c : s) write_char(c);
	};
  int n = read_int(); char c = read_char();
  write_int(n); write_char(c);
  write(1, w, pw - w);
}