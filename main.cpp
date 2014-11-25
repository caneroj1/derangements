//
//  main.cpp
//  derangements
//
//  Created by Joseph Canero on 11/25/14.
//  Copyright (c) 2014 Joseph Canero. All rights reserved.
//

#include <iostream>

int solution_count = 1;

// checks if the current stage of the backtracking algorithm has found a solution
bool is_a_solution(int, int);

// simply prints out the permutation
void process_solution(int [], int n);

// constructs candidates for the next spot in the array by
void construct_candidates(int [], int [], int, int *, int);

// the backtracking algorithm
void backtrack(int [], int, int);

// binary search!
bool bsearch(int, int [], int, int);

// initializes the array that will hold the permutations
void init_array(int[], int);

// init_array
// accepts an array that will be filled and an int indicating the size
// this initializes a dynamically allocated array to hold -1 in each index
void init_array(int a[], int n) {
    for (int i = 0; i < n; i++) a[i] = -1;
}

// if k equals the size of permutation, then we have found a solution
// k is the current position we are getting an element for
bool is_a_solution(int k, int n) {
    return k == n;
}

// simply keeps track of the number of solutions and prints out the current solution
void process_solution(int a[], int n) {
    std::cout << "Solution " << solution_count++ << ": ";
    for (int i = 0; i < n; i++) std::cout << a[i] << " ";
    std::cout << std::endl;
}

// constructs a candidate array for the next position in the permutation as follows:
// initializes an array that will hold TRUE or FALSE for each index.
// next, the algorithm iterates through elements of the array a in order to determine what is currently
// part of the permutation. i perform a binary search on a sorted array of integers where the target is
// the current element of a. if the element is found, the search returns true, which goes in the true or
// false array.
// FALSE at location 'i' indicates that
// the number 'i + 1' is not in the permutation, thus, that number will be added to the candidates array.
// this step runs in O(nlgn) time
void construct_candidates(int a[], int candidates[], int k, int *number_of_candidates, int n) {
    int *t_f_array = new int[n], *data = new int [n];
    
    for (int i = 0; i < n; i++) {
        t_f_array[i] = false;
        data[i] = (i+ 1);
    }

    int candidates_pos = 0;
    for (int i = 0; i < k; i++) t_f_array[a[i] - 1] = bsearch(a[i], data, 0, n);
    for (int i = 0; i < n; i++) {
        if (!t_f_array[i]) candidates[candidates_pos++] = data[i];
    }
    
    *number_of_candidates = candidates_pos;
}

// binary search
bool bsearch(int target, int d[], int min, int max) {
    if (min < max) {
        int mid = (min + max) / 2;
        if (target > d[mid]) return bsearch(target, d, mid + 1, max);
        if (target < d[mid]) return bsearch(target, d, 0, mid);
        else return true;
    }
    else return false;
}

// the backtrack algorithm
// at each step, it checks to see if we have a solution. if yes, we print it out, if not, then we
// construct the candidates for the next position k and we recurse.
void backtrack(int a[], int k, int n) {
    int number_of_candidates, *candidates;
    candidates = new int[n];
    
    if (is_a_solution(k, n)) process_solution(a, n);
    else {
        construct_candidates(a, candidates, k, &number_of_candidates, n);
        for (int i = 0; i < number_of_candidates; i++) {
            if ((k + 1) != candidates[i]) {
                a[k] = candidates[i];
                backtrack(a, k + 1, n);
            }
        }
    }
}

// overall, since we are computing permutations, I believe the entire backtracking algorithm
// O(n!)
int main(int argc, const char * argv[]) {
    int n;
    std::cout << "N = ?: ";
    std::cin >> n;
    std::cout << "\n";
    
    int *a = new int[n];
    init_array(a, n);
    
    backtrack(a, 0, n);
    
    std::cout << "Done!\n";
    return 0;
}
