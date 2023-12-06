# Day 4 - Part 1

INPUT_FILEPATH = "input"


def prep_line_for_processing(line: str) -> str:
    return line.rstrip().split(": ")[-1]


def split_numbers(line: str) -> tuple[list[str], list[str]]:
    winning_numbers, card_numbers = line.split("|")
    winning_numbers = [e for e in winning_numbers.split(" ") if e]
    card_numbers = [e for e in card_numbers.split(" ") if e]
    return winning_numbers, card_numbers


def process_line(line: str) -> int:
    line = prep_line_for_processing(line)
    winning_numbers, card_numbers = split_numbers(line)
    matches = 0
    point_value = 0
    for num in card_numbers:
        if num in winning_numbers:
            matches += 1
    for n in range(matches):
        if n == 0:
            point_value = 1
            continue
        point_value *= 2
    return point_value


def main():
    total = 0
    with open(INPUT_FILEPATH, "r") as f:
        for line in f:
            total += process_line(line.rstrip())
    return total


if __name__ == "__main__":
    print(main())
