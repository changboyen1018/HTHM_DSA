#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Cat {
    int appetite;
    int color;
} Cat;

int count_cats_by_color_and_range(Cat *cats, int n, int color, int lower_bound, int upper_bound) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (cats[i].color == color && lower_bound <= cats[i].appetite && cats[i].appetite <= upper_bound) {
            count++;
        }
    }
    return count;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    Cat cats[n];

    for (int i = 0; i < n; i++) {
        scanf("%d", &cats[i].appetite);
    }

    for (int i = 0; i < n; i++) {
        scanf("%d", &cats[i].color);
    }

    for (int step = 0; step < m; step++) {
        int type;
        scanf("%d", &type);

        if (type == 1) {
            int color, lower_bound, upper_bound;
            scanf("%d %d %d", &color, &lower_bound, &upper_bound);
            printf("%d\n", count_cats_by_color_and_range(cats, n, color, lower_bound, upper_bound));
        } else if (type == 2) {
            int greedy_cat_idx;
            scanf("%d", &greedy_cat_idx);
            int min_diff = INT_MAX;
            int swap_cat_idx = -1;

            for (int i = 0; i < n; i++) {
                if (cats[i].color == cats[greedy_cat_idx].color && cats[i].appetite > cats[greedy_cat_idx].appetite && abs(cats[i].appetite - cats[greedy_cat_idx].appetite) < min_diff) {
                    min_diff = abs(cats[i].appetite - cats[greedy_cat_idx].appetite);
                    swap_cat_idx = i;
                }
            }
            if (swap_cat_idx != -1) {
                int temp = cats[greedy_cat_idx].appetite;
                cats[greedy_cat_idx].appetite = cats[swap_cat_idx].appetite;
                cats[swap_cat_idx].appetite = temp;
            }
        } else if (type == 3) {
            int color, direction, success;
            scanf("%d %d %d", &color, &direction, &success);

            int target_idx = -1;
            int min_appetite = INT_MAX;
            int max_appetite = INT_MIN;

            for (int i = 0; i < n; i++) {
                if (cats[i].color == color) {
                    if (direction == 0 && (target_idx == -1 || cats[i].appetite < cats[target_idx].appetite)) {
                        target_idx = i;
                    } else if (direction == 1 && (target_idx == -1 || cats[i].appetite > cats[target_idx].appetite)) {
                        target_idx = i;
                    }
                }
                if (cats[i].appetite < min_appetite) {
                    min_appetite = cats[i].appetite;
                }
                if (cats[i].appetite > max_appetite) {
                    max_appetite = cats[i].appetite;
                }
            }
            if (target_idx != -1) {
                if (success == 1) {
                    cats[target_idx].appetite = max_appetite + 1;
                } else {
                    cats[target_idx].appetite = min_appetite - 1;
                }
            }
        }
    }
    return 0;
}
