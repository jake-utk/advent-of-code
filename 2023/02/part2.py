# Day 02 - Part 2


def get_max_colors(games: list[tuple[str, str]]) -> tuple[int, int, int]:
    cubes = {
        "red": 0,
        "green": 0,
        "blue": 0,
    }

    for game in games:
        if cubes[game[1]] < int(game[0]):
            cubes[game[1]] = int(game[0])

    return cubes["red"], cubes["green"], cubes["blue"]


def process_line(line: str) -> int:
    rounds_in_line = line.replace("\n", "").split(":")[-1].strip().split(";")
    flattened_rounds = [
        tuple(item.strip().split())
        for single_round in rounds_in_line
        for item in single_round.split(",")
    ]

    red, green, blue = get_max_colors(flattened_rounds)
    return red * green * blue


def main() -> int:
    with open("input", "r") as f:
        return sum(process_line(line) for line in f)


if __name__ == "__main__":
    print(main())
