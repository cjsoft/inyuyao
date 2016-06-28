#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>

using namespace std;
double A, B;
double calc(double x) {
	return sqrt((1 - x * x / A / A) * B * B);
}

double simpson(double a, double b) {
	double c = a + (b - a) / 2;
	return (calc(a) + 4 * calc(c) + calc(b)) * (b - a) / 6;
	// V = \frac{h(a+4b+c)}{6}
}

double asr(double a, double b, double eps, double smp) {
	double c = a + (b - a) / 2;
	double L = simpson(a, c), R = simpson(c, b);
	if (fabs(L + R - smp) <= 15 * eps) return L + R + (L + R - smp) / 15.;
	return asr(a, c, eps / 2, L) + asr(c, b, eps / 2, R);
}

int main() {
	int N;
	scanf("%d", &N);
	while (N--) {
		double l, r;
		scanf("%lf %lf", &A, &B);
		scanf("%lf %lf", &l, &r);
		printf("%.3lf\n", 2 * asr(l, r, 1e-5, simpson(l, r)));
	}
	return 0;
}