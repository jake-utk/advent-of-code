# Day 02 - Part 1


def is_game_valid(game: str) -> bool:
    cubes = {
        "red": 0,
        "green": 0,
        "blue": 0,
    }
    cubes_shown = [e for e in game.replace(",", "").split(" ") if e != ""]
    for i in range(0, len(cubes_shown) - 1, 2):
        cubes[cubes_shown[i + 1]] += int(cubes_shown[i])

    return all(
        [
            cubes["red"] <= 12,
            cubes["green"] <= 13,
            cubes["blue"] <= 14,
        ]
    )


def process_line(line: str) -> int:
    game_id, games = line.replace("\n", "").split(":")
    game_id = game_id.split(" ")[-1]
    games = games.strip().split(";")

    for game in games:
        if not is_game_valid(game):
            return 0
    return int(game_id)


def main() -> int:
    with open("input", "r") as f:
        return sum(process_line(line) for line in f)


if __name__ == "__main__":
    print(main())
