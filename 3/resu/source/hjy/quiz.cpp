#include<iostream>
#include<cstdio>
#define LL long long
using namespace std;
int n;
LL dict[]={
0,1,
10,
11,
100,
101,
110,
111,
1000,
1001,
1100,
1101,
10000,
10001,
10100,
10101,
11000,
11001,
11100,
11101,
100000,
100001,
101100,
101101,
110000,
110001,
111100,
111101,
1000000,
1000001,
1010000,
1010001,
1100000,
1100001,
1110000,
1110001,
10000000,
10000001,
10010000,
10010001,
11000000,
11000001,
11010000,
11010001,
100000000,
100000001,
101000000,
101000001,
110000000,
110000001,
111000000,
111000001,
1000000000,
1000000001,
1011000000,
1011000001,
1100000000,
1100000001,
1111000000,
1111000001,
10000000000,
10000000001,
10011000000,
10011000001,
10100000000,
10100000001,
10111000000,
10111000001,
11000000000,
11000000001,
11011000000,
11011000001,
11100000000,
11100000001,
11111000000,
11111000001,
100000000000,
100000000001,
100100000000,
100100000001,
101011000000,
101011000001,
101111000000,
101111000001,
110000000000,
110000000001,
110100000000,
110100000001,
111011000000,
111011000001,
111111000000,
111111000001,
1000000000000,
1000000000001,
1000100000000,
1000100000001,
1001011000000,
1001011000001,
1001111000000,
1001111000001,
1010000000000,
1010000000001,
1010100000000,
1010100000001,
1011011000000,
1011011000001,
1011111000000,
1011111000001,
1100000000000,
1100000000001,
1100100000000,
1100100000001,
1101011000000,
1101011000001,
1101111000000,
1101111000001,
1110000000000,
1110000000001,
1110100000000,
1110100000001,
1111011000000,
1111011000001,
1111111000000,
1111111000001,
10000000000000,
10000000000001,
10001111000000,
10001111000001,
10010100000000,
10010100000001,
10011011000000,
10011011000001,
10100100000000,
10100100000001,
10101011000000,
10101011000001,
10110000000000,
10110000000001,
10111111000000,
10111111000001,
11000000000000,
11000000000001,
11001111000000,
11001111000001,
11010100000000,
11010100000001,
11011011000000,
11011011000001,
11100100000000,
11100100000001,
11101011000000,
11101011000001,
11110000000000,
11110000000001,
11111111000000,
11111111000001,
100000000000000,
100000000000001,
100001111000000,
100001111000001,
100011011000000,
100011011000001,
100101011000000,
100101011000001,
101000000000000,
101000000000001,
101001111000000,
101001111000001,
101011011000000,
101011011000001,
101101011000000,
101101011000001,
110000000000000,
110000000000001,
110001111000000,
110001111000001,
110011011000000,
110011011000001,
110101011000000,
110101011000001,
111000000000000,
111000000000001,
111001111000000,
111001111000001,
111011011000000,
111011011000001,
111101011000000,
111101011000001,
1000000000000000,
1000000000000001,
1001000000000000,
1001000000000001,
1010001111000000,
1010001111000001,
1010011011000000,
1010011011000001,
1010101011000000,
1010101011000001,
1011001111000000,
1011001111000001,
1011011011000000,
1011011011000001,
1011101011000000,
1011101011000001,
1100000000000000,
1100000000000001,
1101000000000000,
1101000000000001,
1110001111000000,
1110001111000001,
1110011011000000,
1110011011000001,
1110101011000000,
1110101011000001,
1111001111000000,
1111001111000001,
1111011011000000,
1111011011000001,
1111101011000000,
1111101011000001,
10000000000000000,
10000000000000001,
10010101011000000,
10010101011000001,
10011001111000000,
10011001111000001,
10011011011000000,
10011011011000001,
10100000000000000,
10100000000000001,
10110101011000000,
10110101011000001,
10111001111000000,
10111001111000001,
10111011011000000,
10111011011000001,
11000000000000000,
11000000000000001,
11010101011000000,
11010101011000001,
11011001111000000,
11011001111000001,
11011011011000000,
11011011011000001,
11100000000000000,
11100000000000001,
11110101011000000,
11110101011000001,
11111001111000000,
11111001111000001,
11111011011000000,
11111011011000001,
100000000000000000,
100000000000000001,
100010101011000000,
100010101011000001,
100011001111000000,
100011001111000001,
100111011011000000,
100111011011000001,
101011011011000000,
101011011011000001,
101100000000000000,
101100000000000001,
101110101011000000,
101110101011000001,
101111001111000000,
101111001111000001,
110000000000000000,
110000000000000001,
110010101011000000,
110010101011000001,
110011001111000000,
110011001111000001,
110111011011000000,
110111011011000001,
111011011011000000,
111011011011000001,
111100000000000000,
111100000000000001,
111110101011000000,
111110101011000001,
111111001111000000,
111111001111000001};
int main(void)
{
	freopen("quiz.in","r",stdin);
	freopen("quiz.out","w",stdout);
	scanf("%d",&n);
	printf("%lld",dict[n]);
	return 0;
}