#!/usr/bin/env python3

def solution(n: list) -> int:
    n.sort()
    N = len(n)
    
    for i in range(N-2):
        
        t = n[i]            
        l,r = i+1, N-1
        while l<r:
            s = (n[l]+n[r]+t)
            if s == 2020:
                return (n[l]*n[r]*t)
            elif s > 2020:
                r -= 1
            else:
                l += 1

with open("input.txt", "r") as f:
    x = [ int(i) for i in f.readlines() ] 
print(solution(x))
