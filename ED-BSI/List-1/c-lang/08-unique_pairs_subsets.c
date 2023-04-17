/* This exercise involves finding pairs {a, b} for each subsequence of the sequence S = 1..N, 
 * where a is the highest number and b is the second largest number in the subsequence.
 * Since each subsequence of S is ordered, the largest numbers will always be at the end of the subsequence. 
 * Thus, for any subsequence S1 from n to m (where n < m and n >= 1 and m <= N), the pair will be {m, m-1}.
 * While it may seem like there are ((N+1)*N)/2 possible pairs to consider, 
 * iterating through all subsequences will eventually result in pairs {N, N-1}, {N-1, N-2}, ..., {2, 1}. 
 * Even if these pairs appear more than once, we only want the count of unique pairs, which is N - 2 + 1 = N - 1. 
 * So the real solution and the fastest is just N - 1.
 * PS.: It took a long to realize this. I'm still not sure if it is correct. But I do think so.
 * */

#include <stdio.h>
#include "stack.h"

int calculate_unique_pairs(int maximum);

int main()
{
    int maximum;
    scanf("%d", &maximum);

    int result = calculate_unique_pairs(maximum);
    printf("result: %d\n", result);
    
    return 0;
}

// This is (probably) the correct solution, based on the reasoning explained at the top.
int calculate_unique_pairs(int maximum)
{
    return maximum - 1;
}
