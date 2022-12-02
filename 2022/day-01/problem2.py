# Advent of Code 2022
# Day 1 - Problem 2 


def main():

    current_total = 0
    totals = []

    with open("2022/day-01/input.txt", "r") as f:
        for line in f:
            line = line.rstrip()
            if line == "":
                totals.append(current_total)
                current_total = 0
            else:
                current_total += int(line)

    sorted_counts = sorted(totals)
    
    return sum(sorted_counts[-3:])


if __name__ == "__main__":
    print(main())
