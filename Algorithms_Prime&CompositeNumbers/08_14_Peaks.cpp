////////// CHALLENGE DESCRIPTION

// A non-empty array A consisting of N integers is given.

// A peak is an array element which is larger than its neighbors. More precisely, it is an index P such that 0 < P < N − 1,  A[P − 1] < A[P] and A[P] > A[P + 1].

// For example, the following array A:

//     A[0] = 1
//     A[1] = 2
//     A[2] = 3
//     A[3] = 4
//     A[4] = 3
//     A[5] = 4
//     A[6] = 1
//     A[7] = 2
//     A[8] = 3
//     A[9] = 4
//     A[10] = 6
//     A[11] = 2

// has exactly three peaks: 3, 5, 10.

// We want to divide this array into blocks containing the same number of elements. More precisely, we want to choose a number K that will yield the following blocks:

// A[0], A[1], ..., A[K − 1],
// A[K], A[K + 1], ..., A[2K − 1],
// ...
// A[N − K], A[N − K + 1], ..., A[N − 1].
// What's more, every block should contain at least one peak. Notice that extreme elements of the blocks (for example A[K − 1] or A[K]) can also be peaks, but only if they have both neighbors (including one in an adjacent blocks).

// The goal is to find the maximum number of blocks into which the array A can be divided.

// Array A can be divided into blocks as follows:

// one block (1, 2, 3, 4, 3, 4, 1, 2, 3, 4, 6, 2). This block contains three peaks.
// two blocks (1, 2, 3, 4, 3, 4) and (1, 2, 3, 4, 6, 2). Every block has a peak.
// three blocks (1, 2, 3, 4), (3, 4, 1, 2), (3, 4, 6, 2). Every block has a peak. Notice in particular that the first block (1, 2, 3, 4) has a peak at A[3], because A[2] < A[3] > A[4], even though A[4] is in the adjacent block.
// However, array A cannot be divided into four blocks, (1, 2, 3), (4, 3, 4), (1, 2, 3) and (4, 6, 2), because the (1, 2, 3) blocks do not contain a peak. Notice in particular that the (4, 3, 4) block contains two peaks: A[3] and A[5].

// The maximum number of blocks that array A can be divided into is three.

// Write a function:

// int solution(vector<int> &A);

// that, given a non-empty array A consisting of N integers, returns the maximum number of blocks into which A can be divided.

// If A cannot be divided into some number of blocks, the function should return 0.

// For example, given:

//     A[0] = 1
//     A[1] = 2
//     A[2] = 3
//     A[3] = 4
//     A[4] = 3
//     A[5] = 4
//     A[6] = 1
//     A[7] = 2
//     A[8] = 3
//     A[9] = 4
//     A[10] = 6
//     A[11] = 2

// the function should return 3, as explained above.

// Write an efficient algorithm for the following assumptions:

// N is an integer within the range [1..100,000];
// each element of array A is an integer within the range [0..1,000,000,000].


////////// SOLUTION

#include <vector>
#include <algorithm>

int solution(std::vector<int> &A)
{
    std::vector<int> peaks, blocks;
    int elements = A.end() - A.begin();
    int lowLimit = 0, topLimit = 0, maxBlocks = 1;

    if (A.size() < 3)
        return 0;

    for (auto it = (A.begin() + 1); it != (A.end() - 1); ++it)
    {
        if (*(it - 1) < *it && *it > *(it + 1))
            peaks.push_back(it - A.begin());
    }

    if (peaks.empty())
        return 0;

    for (long int i = 1; i * i <= elements; i++)
    {
        if (elements % i == 0)
        {
            blocks.push_back(i);
        }
    }

    for (int i = blocks.size() - 1; i >= 0; --i)
    {
        blocks.push_back(elements / blocks[i]);
    }

    std::reverse(blocks.begin(), blocks.end());
    
    for (auto it = blocks.begin(); it != blocks.end(); ++it)
    {
        lowLimit = 0;
        topLimit = *it;
        for (int p : peaks)
        {
            if (lowLimit <= p && p < topLimit)
            {
                lowLimit += *it;
                topLimit += *it;
            }
            if (lowLimit == elements)
            {
                maxBlocks = elements / (*it);
            }
        }
    }

    return maxBlocks;
}

////////// CORRECT BEHAVIOUR
////////// TIME COMPLEXITY:
////////// MAX ~ O(Nlog(logN))
////////// AVG ~ 0(Nlog(logN))