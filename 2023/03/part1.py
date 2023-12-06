# Day 3 - Part 1
from collections import deque
from typing import Generator
from dataclasses import dataclass

WINDOW_SIZE = 3
INPUT_FILEPATH = "input"


@dataclass()
class Number:
    number_str: str = ""
    starting_index: int = -1


def get_numbers(line: str) -> list[Number]:
    numbers: list[Number] = []
    is_number_in_progress: bool = False
    in_progress_number: str = ""
    in_prog_starting_idx: int = -1
    for i, char in enumerate(line):
        if not char.isdigit():
            if is_number_in_progress:
                numbers.append(
                    Number(
                        number_str=in_progress_number,
                        starting_index=in_prog_starting_idx,
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
        if is_number_in_progress and (i == len(line) - 1):
            numbers.append(
                Number(
                    number_str=in_progress_number,
                    starting_index=in_prog_starting_idx,
                )
            )
    return numbers


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


def left_bounds(number: Number) -> int:
    if not number.starting_index:
        return number.starting_index
    return number.starting_index - 1


def right_bounds(number: Number, line_length: int) -> int:
    adjacent_index = number.starting_index + len(number.number_str) + 2
    if adjacent_index >= line_length:
        return number.starting_index + len(number.number_str) + 1
    return adjacent_index


def process_first_or_last_line(lines: list[str], line_to_process: int) -> int:
    if line_to_process:  # last line
        other_line, target_line = lines
        print(other_line)
        print(target_line, "<--")
    else:  # first line
        target_line, other_line = lines
        print(target_line, "<--")
        print(other_line)
    numbers = get_numbers(target_line)
    numbers_total = 0
    for number in numbers:
        print(number)
        perimeter_starting_idx = left_bounds(number)
        perimeter_end_idx = right_bounds(number, len(number.number_str))
        if line_to_process:
            print(other_line[perimeter_starting_idx:perimeter_end_idx])
            print(target_line[perimeter_starting_idx:perimeter_end_idx])
        else:
            print(target_line[perimeter_starting_idx:perimeter_end_idx])
            print(other_line[perimeter_starting_idx:perimeter_end_idx])
        perimeter_values = [
            c
            for c in "".join(
                [
                    other_line[perimeter_starting_idx:perimeter_end_idx],
                    target_line[perimeter_starting_idx:perimeter_end_idx],
                ]
            )
            if not c.isdigit() and c != "."
        ]
        print(perimeter_values)
        if len(perimeter_values):
            numbers_total += int(number.number_str)
    return numbers_total


def process_middle_line(lines: list[str]) -> int:
    previous_line, target_line, next_line = lines
    print(previous_line)
    print(target_line, "<--")
    print(next_line)
    numbers = get_numbers(target_line)
    numbers_total = 0
    for number in numbers:
        print(number)
        perimeter_starting_idx = left_bounds(number)
        perimeter_end_idx = right_bounds(number, len(number.number_str))
        print(
            previous_line[perimeter_starting_idx:perimeter_end_idx],
        )
        print(
            target_line[perimeter_starting_idx:perimeter_end_idx],
        )
        print(
            next_line[perimeter_starting_idx:perimeter_end_idx],
        )
        perimeter_values = [
            c
            for c in "".join(
                [
                    previous_line[perimeter_starting_idx:perimeter_end_idx],
                    target_line[perimeter_starting_idx:perimeter_end_idx],
                    next_line[perimeter_starting_idx:perimeter_end_idx],
                ]
            )
            if not c.isdigit() and c != "."
        ]
        print(perimeter_values)
        if len(perimeter_values):
            numbers_total += int(number.number_str)
    return numbers_total


def main() -> int:
    total: int = 0
    first_line = True
    for lines in read_file_with_sliding_window(INPUT_FILEPATH, WINDOW_SIZE):
        if len(lines) == 2:
            total += process_first_or_last_line(lines[-2:], 1)
            break
        if first_line:
            total += process_first_or_last_line(lines[:2], 0)
            first_line = False
            print()
            # break
        total += process_middle_line(lines)
        print()
    return total


if __name__ == "__main__":
    print(main())
