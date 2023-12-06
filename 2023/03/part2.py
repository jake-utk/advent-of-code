# Day 3 - Part 2
from collections import deque
from typing import Generator
from dataclasses import dataclass, field

WINDOW_SIZE = 3
INPUT_FILEPATH = "input"


@dataclass()
class Number:
    number_str: str = ""
    line: int = -1
    starting_idx: int = -1
    ending_idx: int = field(init=False)

    def __post_init__(self):
        self.ending_idx = self.starting_idx + len(self.number_str) - 1


@dataclass()
class Gear:
    adjacent_values: list[int] = field(default_factory=list)
    idx: int = -1
    line: int = -1


def read_file_with_sliding_window(
    file_path: str, window_size: int
) -> Generator[list[str], None, None]:
    with open(file_path, "r") as file:
        window = deque(maxlen=window_size)
        for line in file:
            window.append(line.rstrip())
            if len(window) == window_size:
                yield list(window)
        window.popleft()
        yield list(window)


def print_numbers(numbers: list[Number]) -> None:
    for number in numbers:
        print(number)


def get_numbers(lines: list[str]) -> list[Number]:
    numbers: list[Number] = []
    is_number_in_progress: bool = False
    in_progress_number: str = ""
    in_prog_starting_idx: int = -1
    for n in range(0, len(lines)):
        for i, char in enumerate(lines[n]):
            if not char.isdigit():
                if is_number_in_progress:
                    numbers.append(
                        Number(
                            number_str=in_progress_number,
                            starting_idx=in_prog_starting_idx,
                            line=n,
                        )
                    )
                    in_progress_number = ""
                    in_prog_starting_idx = -1
                is_number_in_progress = False
                continue
            if char.isdigit():
                if not is_number_in_progress:
                    is_number_in_progress = True
                    in_prog_starting_idx = i
                in_progress_number += char
            if is_number_in_progress and (i == len(lines[n]) - 1):
                numbers.append(
                    Number(
                        number_str=in_progress_number,
                        starting_idx=in_prog_starting_idx,
                        line=n,
                    )
                )
                in_progress_number = ""
                in_prog_starting_idx = -1
    return numbers


def get_gears(lines: list[str], line_number: int, numbers: list[Number]) -> list[Gear]:
    gears = [
        Gear(idx=i, line=line_number)
        for i in range(0, len(lines[line_number]))
        if lines[line_number][i] == "*"
    ]
    for gear in gears:
        perimeter_starting_idx = gear.idx - 1 if gear.idx > 0 else 0
        perimeter_ending_idx = (
            gear.idx + 1 if gear.idx < len(lines[0]) - 1 else len(lines[0]) - 1
        )
        # print("gear perimeter start:", perimeter_starting_idx)
        # print("gear perimeter end:", perimeter_ending_idx)
        for number in numbers:
            if any(
                [
                    number.starting_idx >= perimeter_starting_idx
                    and number.starting_idx <= perimeter_ending_idx,
                    number.ending_idx >= perimeter_starting_idx
                    and number.ending_idx <= perimeter_ending_idx,
                ]
            ):
                gear.adjacent_values.append(int(number.number_str))
    return gears


def get_total_gear_ratios(gears: list[Gear]) -> int:
    return sum(
        [
            gear.adjacent_values[0] * gear.adjacent_values[-1]
            for gear in gears
            if len(gear.adjacent_values) == 2
        ]
    )


def print_gears(gears: list[Gear]) -> None:
    for gear in gears:
        print(gear)


def process_line(lines: list[str], first_line: bool = False) -> int:
    numbers = get_numbers(lines)
    print_numbers(numbers)
    if first_line and len(lines) == 2:
        # process first line
        print(lines[0], "<--")
        print(lines[1])
        # print_numbers(numbers)
        gears = get_gears(lines, 0, numbers)
        print_gears(gears)
        print()
        return get_total_gear_ratios(gears)

    if len(lines) == 2:
        # process last line
        print(lines[0])
        print(lines[1], "<--")
        # print_numbers(numbers)
        gears = get_gears(lines, 1, numbers)
        print_gears(gears)
        print()
        return get_total_gear_ratios(gears)

    # process middle lines
    print(lines[0])
    print(lines[1], "<--")
    print(lines[2])
    # print_numbers(numbers)
    gears = get_gears(lines, 1, numbers)
    print_gears(gears)
    print()
    return get_total_gear_ratios(gears)


def main() -> int:
    total: int = 0
    first_line = True
    for lines in read_file_with_sliding_window(INPUT_FILEPATH, WINDOW_SIZE):
        if first_line:
            total += process_line(lines[:2], first_line)
            first_line = False
        total += process_line(lines)
    return total


if __name__ == "__main__":
    print(main())
