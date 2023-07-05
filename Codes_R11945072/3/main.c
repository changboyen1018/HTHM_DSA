#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUM 1000

int greater_or_equal(int *num1, int *num2, int len1, int len2) {
    if (len1 > len2) {
        return 1;
    } else if (len1 < len2) {
        return 0;
    }
    for (int i = len1 - 1; i >= 0; i--) {
        if (num1[i] > num2[i]) {
            return 1;
        } else if (num1[i] < num2[i]) {
            return 0;
        }
    }
    return 1;
}

void subtract(int *num1, int *num2, int len1, int len2) {
    for (int i = 0; i < len2; i++) {
        if (num1[i] < num2[i]) {
            num1[i + 1] -= 1;
            num1[i] += 10;
        }
        num1[i] -= num2[i];
    }
    for (int i = len2; i < len1; i++) {
        if (num1[i] < 0) {
            num1[i] += 10;
            num1[i + 1] -= 1;
        } else {
            break;
        }
    }
}

void binary_gcd(int *num1, int *num2, int len1, int len2) {
    int shift = 0;

    while (!(len1 == 1 && num1[0] == 0) && !(len2 == 1 && num2[0] == 0)) {
        while ((num1[0] % 2 == 0) && (num2[0] % 2 == 0)) {
            for (int i = len1 - 1; i > 0; i--) {
                num1[i - 1] += (num1[i] % 2) * 10;
                num1[i] /= 2;
            }
            num1[0] /= 2;
            while (len1 > 1 && num1[len1 - 1] == 0) {
                len1--;
            }

            for (int i = len2 - 1; i > 0; i--) {
                num2[i - 1] += (num2[i] % 2) * 10;
                num2[i] /= 2;
            }
            num2[0] /= 2;
            while (len2 > 1 && num2[len2 - 1] == 0) {
                len2--;
            }

            shift++;
        }

        while (num1[0] % 2 == 0) {
            for (int i = len1 - 1; i > 0; i--) {
                num1[i - 1] += (num1[i] % 2) * 10;
                num1[i] /= 2;
            }
            num1[0] /= 2;
            while (len1 > 1 && num1[len1 - 1] == 0) {
                len1--;
            }
        }

        while (num2[0] % 2 == 0) {
            for (int i = len2 - 1; i > 0; i--) {
                num2[i - 1] += (num2[i] % 2) * 10;
                num2[i] /= 2;
            }
            num2[0] /= 2;
            while (len2 > 1 && num2[len2 - 1] == 0) {
                len2--;
            }
        }

        if (greater_or_equal(num1, num2, len1, len2)) {
            subtract(num1, num2, len1, len2);
            while (len1 > 1 && num1[len1 - 1] == 0) {
                len1--;
            }
        } else {
            subtract(num2, num1, len2, len1);
            while (len2 > 1 && num2[len2 - 1] == 0) {
                len2--;
            }
        }
    }

    for (int i = 0; i < len2; i++) {
        num1[i] = num2[i];
    }
    len1 = len2;

    for (int i = 0; i < shift; i++) {
        for (int j = len1 - 1; j >= 1; j--) {
            num1[j] = num1[j] * 2 + num1[j - 1] / 5;
            num1[j - 1] %= 5;
        }
        num1[0] *= 2;
        if (num1[len1 - 1] >= 10) {
            num1[len1++] = num1[len1 - 1] / 10;
            num1[len1 - 2] %= 10;
        }
    }
}

int main() {
    char num1_str[MAX_NUM], num2_str[MAX_NUM];
    int num1[MAX_NUM], num2[MAX_NUM];
    scanf("%s %s", num1_str, num2_str);

    int len1 = strlen(num1_str);
    int len2 = strlen(num2_str);
    for (int i = 0; i < len1; i++) {
        num1[len1 - 1 - i] = num1_str[i] - '0';
    }
    for (int i = 0; i < len2; i++) {
        num2[len2 - 1 - i] = num2_str[i] - '0';
    }

    binary_gcd(num1, num2, len1, len2);

    int start_index = len1 - 1;
    while (start_index > 0 && num1[start_index] == 0) {
        start_index--;
    }
    
    for (int i = start_index; i >= 0; i--) {
        printf("%d", num1[i]);
    }
    printf("\n");

    return 0;
}

