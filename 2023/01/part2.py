# Day 01 - Part 2

NUMBERS = {
    "one": "1",
    "two": "2",
    "three": "3",
    "four": "4",
    "five": "5",
    "six": "6",
    "seven": "7",
    "eight": "8",
    "nine": "9",
}


def process_line(line: str) -> int:
    first_letters: set = {c[0] for c in NUMBERS}
    numbers_only: str = ""
    for i in range(len(line)):
        if line[i].isdigit():
            numbers_only += line[i]
            continue
        if line[i] in first_letters:
            if line[i : i + 3] in NUMBERS:
                numbers_only += NUMBERS[line[i : i + 3]]
            if line[i : i + 4] in NUMBERS:
                numbers_only += NUMBERS[line[i : i + 4]]
            if line[i : i + 5] in NUMBERS:
                numbers_only += NUMBERS[line[i : i + 5]]
    return int(numbers_only[0] + numbers_only[-1])


def main() -> int:
    total: int = 0
    with open("input", "r") as f:
        for line in f:
            total += process_line(line)
    return total


if __name__ == "__main__":
    print(main())
