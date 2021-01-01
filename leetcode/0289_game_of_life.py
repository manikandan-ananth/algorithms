#!/usr/bin/env python3
from typing import List

################################################################################
# https://leetcode.com/problems/game-of-life/  
#
# 1. Trick to perform it in-place is to use 2 bits in the input for current and
#    future state since input is int (no extra storage)
# 2. Minor mistake: Forgot j2>=0 in neighbors check, otherwise simple to code
################################################################################

class Solution:
    def gameOfLife(self, grid: List[List[int]]) -> None:
        """
        Do not return anything, modify board in-place instead.
        """
        m = len(grid)
        n = len(grid[0])
        
        for i in range(m):
            for j in range(n):
                
                neighbors = [ (-1,-1), (-1,0), (-1,1), (0,-1), (0,1), (1,-1), (1,0), (1,1) ]
                count = 0 
                for nnn in neighbors:
                    i2,j2 = i+nnn[0],j+nnn[1]
                    
                    if i2>=0 and i2<m and j2>=0 and j2<n and (grid[i2][j2] & 1):
                        #print (i2,j2)
                        count += 1
                #print (i,j,count)
                if (grid[i][j] == 1 and count in [2,3]) or \
                    (grid[i][j] == 0 and count == 3):
                    
                    grid[i][j] |= 2
                
                
        for i in range(m):
            for j in range(n):
                grid[i][j] >>= 1

if __name__ == "__main__":

    input = [
        [0,1,0],
        [0,0,1],
        [1,1,1],
        [0,0,0]
    ]

    Solution().gameOfLife(input)
    print(input)