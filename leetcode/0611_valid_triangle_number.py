#!/usr/bin/env python3
import sys
from typing import List

def triangleNumber(n: List[int]) -> int:
    
    N = len(n)
    n.sort()
    count = 0
    
    for i in range(N-2):
        if n[i] == 0:
            continue
        k = i + 2
        for j in range(i+1, N-1):
            while k<N and ((n[i]+n[j]) > n[k]):
                k = k + 1
            count += (k-j-1)
    
    return count

def main():
    input_file = sys.argv[1]

    with open(input_file, "r") as f:
        lines = f.readlines()
        
    nums = [ int(l) for l in lines ]
    c = triangleNumber(nums)
    print (c)

main()