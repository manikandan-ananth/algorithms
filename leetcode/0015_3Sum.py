#!/usr/bin/env python3

def threeSum(self, n: List[int]) -> List[List[int]]:
    
    n.sort()
    N = len(n)
    
    triplets = []
    
    for i in range(N-2):
        
        if (i > 0 and n[i]==n[i-1]):
            continue
                       
        t = n[i]            
        l,r = i+1, N-1
        while l<r:
            s = (n[l]+n[r]+t)
            if s == 0:
                triplets.append([t,n[l],n[r]])
                while l<r and n[l] == n[l+1]:
                    l += 1
                while l<r and n[r] == n[r-1]:
                    r -= 1
                l += 1
                r -= 1
            elif s > 0:
                r -= 1
            else:
                l += 1
            
   
    return triplets
        
