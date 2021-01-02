#!/usr/bin/env python3
from typing import List

################################################################################
# https://leetcode.com/problems/set-matrix-zeroes/ 
#
# 1. Use the first row and col of the first zero as a flag row to populate all
#    0 indices (Use '#')
# 2. Remember to overwrite '#' values last
################################################################################

class Solution:
    def setZeroes(self, matrix: List[List[int]]) -> None:
        """
        Do not return anything, modify matrix in-place instead.
        """
        
        M = len(matrix)
        N = len(matrix[0])
        
        flag_row = -1
        flag_col = -1
        
        for i in range(M):
            for j in range(N):
                if matrix[i][j] == 0:
                    if flag_row == -1 and flag_col == -1:
                        flag_row,flag_col = i,j
                        matrix[i][j] = '#'
                    else:
                        matrix[flag_row][j] = '#'
                        matrix[i][flag_col] = '#'
        
        for i in range(M):
            for j in range(N):
                if (matrix[i][flag_col] == '#' or matrix[flag_row][j] == '#') and (matrix[i][j] !='#'):
                    matrix[i][j] = 0
                    
        # Overwrite '#' fields last
        for i in range(M):
            for j in range(N):
                if matrix[i][j] == '#':
                    matrix[i][j] = 0

if __name__ == "__main__":

    input = [
        [1,1,1],
        [1,0,1],
        [1,1,1],
    ]
    Solution().setZeroes(input)
    print(input)