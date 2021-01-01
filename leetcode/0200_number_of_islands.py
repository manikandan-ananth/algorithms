#!/usr/bin/env python3
from typing import List
import sys
import ast

################################################################################
# https://leetcode.com/problems/number-of-islands
#
# Mistakes to watch out for:
# 1. In BFS, forgot to check for grid[i][j] == "1"
# 2. Assumed square grid, but problem states m x n grid
# 3. Tracking visited nodes using a separate visited[m][n] passed around
#    by reference didn't work. Something was causing an entire column to get
#    updated when updating only one element of the column. Switched to 
#    grid[i][j] = '#' notation for tracking visited nodes
################################################################################

class Solution:
    def DFS(self, grid, i, j, M, N):
        if i<0 or j<0 or i>=M or j>=N:
            return 
        if grid[i][j] != "1":
            return
        grid[i][j] = '#'        
        for n in [ (-1,0), (0,-1), (0,1), (1,0) ]:
            self.DFS(grid, i+n[0], j+n[1], M, N)

    def numIslands(self, grid: List[List[str]]) -> int:

        M = len(grid)
        N = len(grid[0])

        count = 0

        for i in range(M):
            for j in range(N):
                if grid[i][j] == "1":  
                    self.DFS(grid, i, j, M, N)
                    count += 1

        return count
        
if __name__ == "__main__":

    grid = [
        ["0","1","0"],
        ["1","0","1"],
        ["0","1","0"]
    ]

    print(Solution().numIslands(grid))