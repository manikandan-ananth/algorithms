#!/usr/bin/env python3

def solution(inp: list) -> int:
    m = {}
    for x in inp:
        if (2020-x) in m:
            return x*(2020-x)
        else:
            m[x] = True
    assert False

with open("input.txt", "r") as f:
    x = [ int(i) for i in f.readlines() ] 
print(solution(x))
