# Day 01 - Part 1

total: int = 0
with open("input", "r") as f:
    for line in f:
        numbers_only = [c for c in line if c.isdigit()]
        total += int(numbers_only[0] + numbers_only[-1])

print(total)
