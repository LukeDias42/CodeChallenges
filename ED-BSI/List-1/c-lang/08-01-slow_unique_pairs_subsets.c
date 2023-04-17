/* The same exercise, but I use the very slow algorithm 
 * to actually iterate through every possible pair.
 * This is definetely not the best solution, but it helps
 * when trying to understand the problem.
 * */

#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

int slow_calculate_unique_pairs(int num);

int main()
{
    int maximum;
    scanf("%d", &maximum);

    int result = slow_calculate_unique_pairs(maximum);
    printf("result: %d\n", result);
    
    return 0;
}

// This solution is very slow, it just iterates through every possible subsequence and adds a pair.
int slow_calculate_unique_pairs(int num)
{
    int max, secondMax;
    int **pairs = (int **)malloc(sizeof(int)*num*num*num*2); 
    int pair = -1;
    for (int i = 1; i <= num; i++) {
        for (int j = i; j <= num; j++) {
            max = secondMax = i;
            for (int k = i; k <= j; k++) {
                if (k > max) {
                    secondMax = max;
                    max = k;
                }
                else if (k > secondMax && k != max) {
                    secondMax = k;
                }
            }
            if (max != secondMax) {
                int *new_pair = (int *)malloc(sizeof(int)*2);
                new_pair[0] = max;
                new_pair[1] = secondMax;
                pairs[++pair] = new_pair;
            }
        }
    }

    int uniquePairs = 0;
    for (int i = 0; i <= pair; i++) {
        bool isUnique = true;
        for (int j = i + 1; j <= pair; j++) {
            if (pairs[i][0] == pairs[j][0] && pairs[i][1] == pairs[j][1]) {
                isUnique = false;
                break;
            }
        }
        if (isUnique) {
            uniquePairs++;
            printf("%d unique: {%d, %d}\n", uniquePairs, pairs[i][0], pairs[i][1]);
        }
        free(pairs[i]);
    }

    free(pairs);
    return uniquePairs;
}
