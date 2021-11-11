# Parallel Merge Sort
## C++ Program using pthreads that implements merge sort in parallel.

### Features:
- Reads in the size of the input, n
    - Allocates an array of strings of size n
- Reads in strings into the array (each string on its own line)
- Recursively splits the array in parallel
- Merges the array back together in parallel.
- ## Runs in O(lg<sup>2</sup> n) time