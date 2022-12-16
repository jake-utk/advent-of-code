// Advent of Code 2022
// Day 2 - Problem 1
#include <stdio.h>
#include <stdlib.h>
/*#include <string.h>*/
#include "read_file.h"

typedef struct {
    char choice; // r, p, s
    int points; // 0-6
} Move;


int main(int argc, char **argv)
{
    File *file = read_file(argc > 1 ? fopen(argv[1], "r") : stdin);
    int total_score = 0, // sum of scores for all rounds
        round_score = 0; // (1 rock, 2 paper, 3 scissors) + (0 loss, 3 draw,
                         // 6 win)
    char elf_move, player_move; // left and right char from each line


    // for each line,
    // determine each players move
    for (size_t i = 0; i < file->used; i++) {
        printf("%s\n", file->lines[i]);
        
    }


    /*// Data Structures*/
    /*// moves = {*/
    /*// "a": "rock",*/
    /*// "x": "rock",*/
    /*// "b": "paper",*/
    /*// "y": "paper",*/
    /*// "c": "scissors",*/
    /*// "z": "scissors"*/
    /*// }*/
    /*// points = {*/
    /*// "rock": 1,*/
    /*// "paper": 2,*/
    /*// "scissors": 3,*/
    /*// "win": 6,*/
    /*// "draw": 3,*/
    /*// "loss": 0*/
    /*// }*/

    /*// Game Logic*/
    /*// if moves[elf] == moves[player]*/
    /*//   draw*/
    /*//   single_round_score += points[draw]*/
    /*//   single_round_score += points[moves[player]]*/
    /*// else if elf-rock, player-paper*/
    /*//   player win*/
    /*//   single_round_score += points[win]*/
    /*//   single_round_score += points[moves[player]]*/
    /*// else if elf-rock, player-scissors*/
    /*//   player loss*/
    /*//   single_round_score += points[loss]*/
    /*//   single_round_score += points[moves[player]]*/
    /*// else if elf-paper, player-rock*/
    /*//   player loss*/
    /*//   single_round_score += points[loss]*/
    /*//   single_round_score += points[moves[player]]*/
    /*// else if elf-paper, player-scissors*/
    /*//   player win*/
    /*//   single_round_score += points[win]*/
    /*//   single_round_score += points[moves[player]]*/
    /*// else if elf-scissors, player-paper*/
    /*//   player loss*/
    /*//   single_round_score += points[loss]*/
    /*//   single_round_score += points[moves[player]]*/
    /*// else if elf-scissors, player-rock*/
    /*//   player win*/
    /*//   single_round_score += points[win]*/
    /*//   single_round_score += points[moves[player]]*/

    close_file(file);
    exit(EXIT_SUCCESS);
}
