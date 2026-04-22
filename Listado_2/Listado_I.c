#include <stdio.h>

int main() {
    int P, dataset_num;
    scanf("%d", &P);

    while (P) {
        int heights[20] = {0};
        int total_steps = 0;
        scanf("%d", &dataset_num);
        for (int i = 0; i < 20; i++) {
            int current_height;
            scanf("%d", &current_height);
            int j = i - 1;
            while (j >= 0 && heights[j] > current_height) {
                heights[j + 1] = heights[j];
                total_steps++;
                j--;
            }
            heights[j + 1] = current_height;
        }
        P--;
        printf("%d %d\n", dataset_num, total_steps);
    }

    return 0;
}