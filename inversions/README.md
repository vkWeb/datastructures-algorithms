## Problem statement

Find number of inversion pairs in a `n` element array `A` in Θ(nlog<sub>2</sub>(n)) time complexity at worst case scenario. 

A inversion pair `(i, j)` is defined as when `A[i] > A[j] && i < j`. 

## Explanation via example

Input array: `A[2, 5, 8, 3, 4]`. 
Output: `4`.

There are `4` inversion pairs. The values of inversion pairs are `(5, 3)`, `(5, 4)`, `(8, 3)` and `(8, 4)`.
