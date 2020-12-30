
def twoSum(self, n: List[int], target: int) -> List[int]:
    
    N = len(n)
    l = 0
    r = N-1
    
    while l<r:
        s = n[l] + n[r]
        if s == target:
            return [l+1,r+1]
        elif s < target:
            l += 1
        else:
            r -= 1
        