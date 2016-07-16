#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

int n, m, x;
set< pair<int, int> > events;

inline void work() {
	printf("%d %d\n", n, m);
	events.clear();
	for (int i = 1; i <= m; i++) {
		int x, y;
		for (;;) {
			x = rand() * rand() % n + 1;
			y = rand() * rand() % n + 1;
			if (x > y) swap(x, y); 
			if (x != y && events.find(make_pair(x, y)) == events.end()) 
				break;
		}
		events.insert(make_pair(x, y));
		printf("%d %d %d\n", x, y, rand() * rand() % (x + 1));
	}
	printf("%d %d\n", rand() * rand() % n + 1, rand() * rand() % n + 1);
}

int main() {
	n = 10; m = 10; x = 30;	
	freopen("shortest0.in", "w", stdout); work();
	n = 100; m = 101; x = 30;	
	freopen("shortest1.in", "w", stdout); work(); 
	n = 1000; m = 1000; x = 30;	
	freopen("shortest2.in", "w", stdout); work();
	n = 100000; m = 100000; x = 30;	
	freopen("shortest3.in", "w", stdout); work();
	n = 100000; m = 100000; x = 30;	
	freopen("shortest4.in", "w", stdout); work();
	n = 100000; m = 100000; x = 30;	
	freopen("shortest5.in", "w", stdout); work();
	n = 100000; m = 100000; x = 100000;	
	freopen("shortest6.in", "w", stdout); work();
	n = 100000; m = 100000; x = 100000;	
	freopen("shortest7.in", "w", stdout); work();
	n = 100000; m = 100000; x = 100000;	
	freopen("shortest8.in", "w", stdout); work();
	n = 100000; m = 100000; x = 100000;	
	freopen("shortest9.in", "w", stdout); work();
	n = 100000; m = 100000; x = 100000;	
	freopen("shortest10.in", "w", stdout); work();
	n = 100000; m = 100000; x = 100000;	
	freopen("shortest11.in", "w", stdout); work();
	n = 100000; m = 100000; x = 100000;	
	freopen("shortest12.in", "w", stdout); work();
	n = 100000; m = 100000; x = 100000;	
	freopen("shortest13.in", "w", stdout); work();
	n = 100000; m = 100000; x = 100000;	
	freopen("shortest14.in", "w", stdout); work();
	n = 100000; m = 100000; x = 100000;	
	freopen("shortest15.in", "w", stdout); work();
	n = 100000; m = 100000; x = 100000;	
	freopen("shortest16.in", "w", stdout); work();
	n = 100000; m = 100000; x = 100000;	
	freopen("shortest17.in", "w", stdout); work();
	n = 100000; m = 100000; x = 100000;	
	freopen("shortest18.in", "w", stdout); work();
	n = 100000; m = 100000; x = 100000;	
	freopen("shortest19.in", "w", stdout); work();
}
