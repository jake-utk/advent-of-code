# Advent of Code 2022
# Day 1 - Problem 1


def main():

    current_total = 0
    highest_total = 0

    with open("2022/day-01/input.txt", "r") as f:
        for line in f:
            line = line.rstrip()
            if line == "":
                if current_total > highest_total:
                    highest_total = current_total
                current_total = 0
            else:
                current_total += int(line)
    
    return highest_total


if __name__ == "__main__":
    print(main())
