import re
s = open('numbers.txt').read()          # save your pasted block to numbers.txt
nums = list(map(int, re.findall(r'\d+', s)))
print(sum(nums))
