#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#define MXN 10007
using namespace std;

int fail[MXN];
void initNext(char raw[]) {
    memset(fail, 0, sizeof(fail));
    int len = strlen(raw);
    for (int i = 1; i < len; ++i) {
        int j = i; {
            while (j > 0) {
                j = fail[j];
                if (raw[i] == raw[j]) {
                    fail[i + 1] = j + 1;
                    break;
                }
            }
        }
    }
}
char input[1007];
int main() {
    while (1) {
        scanf("%s", input);
        int len = strlen(input);
        initNext(input);
        for (int i = 0; i <= len; ++i) {
            printf("%d\t%d\n", i, fail[i]);
        }
        printf("%d\n", len - fail[len]);
    }
    return 0;
}
