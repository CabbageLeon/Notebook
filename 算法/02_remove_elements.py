class Solution:
    def removeElement(self, nums: list[int], val: int) -> int:
        slowIndex = 0
        fastIndex = 0
        for i in nums:
            if(nums[fastIndex] != val):
                nums[slowIndex] = nums[fastIndex]
                slowIndex+=1
            fastIndex+=1
                
        return slowIndex