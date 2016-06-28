const int BUF_SIZE = (int) 1e4 + 10;
struct fastIO {
	char buf[BUF_SIZE];
	int cur;
	FILE *in;
	fastIO () {
		cur = BUF_SIZE;
		in = stdin;
	}
	inline char nextChar () {
		if (cur == BUF_SIZE) {
			fread (buf, BUF_SIZE, 1, in);
			cur = 0;
		}
		return buf[cur++];
	}
	inline int nextInt () {
		int x = 0;
		char c = nextChar ();
		while (!('0' <= c && c <= '9')) c = nextChar ();
		while ('0' <= c && c <= '9') {
			x = x * 10 + c - '0';
			c = nextChar ();
		}
		return x;
	}
} IO;
