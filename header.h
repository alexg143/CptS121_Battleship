/*
Programmer: Alexander Glenn
Class: CptS 121; Lab Section 6
Programming Assignment: Programming Assignment 6
Date: April 4, 2018
Description: This program plays a game of battleship with a
			 user against a computer AI. The user is allowed to
			 choose between placing ships randomly or by entering 
			 coordinates.The game ends when either the user or
			 AI fires upon and sinks all the ships of the other
			 player by entering coordinates. User statistics and 
			 a game log are then outputted to a battleship.log file.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef enum dir // Given by Andy
{
	HORIZONTAL = 0, VERTICAL = 1
} Dir;

typedef struct coordinate // Given by Andy
{
	int row;
	int col;
} Coordinate;

typedef struct stats // Given by Andy
{
	int total_shots;
	int total_misses;
	int total_hits;
	double hits_misses_ratio;
}Stats;

#define MAX_ROWS 10
#define MAX_COLS 10
#define DESTROYER 2
#define CRUISER 3
#define SUBMARINE 3
#define BATTLESHIP 4
#define CARRIER 5

void main_menu(void);
int position_choice(void);
void init_board(char board[][MAX_COLS], int num_rows, int num_cols);
void print_board(char board[][MAX_COLS], int num_rows, int num_cols, int player);
int gen_player_start(void);
int * get_target(int p1_shots[][2], int turn);
int * random_target(int p2_shots[][2], int turn);
int hit_or_miss(int shots[][2], char board[][MAX_COLS], int turn);
void print_hit_or_miss(int shots[][2], int hit, int turn);
int has_won(int p1_hits, int p2_hits);
int * has_sunk(char p_board[][MAX_COLS], int p_sink_array[]);
int get_num_hits(int p1_hits, int p2_hits, int *p1_hit_count_ptr, int *p2_hit_count_ptr);
char * update_board(int shots[][2], int hit, char p_board[][MAX_COLS], int turn);
Dir gen_dir(void);
void gen_start_pt(Coordinate *start_pt_ptr, Dir direction, int length);
char * rand_ship_placement(int length, char symbol, Dir direction, Coordinate *start_pt_ptr, char p_board[][MAX_COLS], Coordinate n[]);
int overlap_check(Coordinate c[], Coordinate b[], Coordinate r[], Coordinate s[], Coordinate d[]);
char * random_placement(Dir direction, Coordinate *start_pt_ptr, char p_board[][MAX_COLS],
	Coordinate c[], Coordinate b[], Coordinate r[], Coordinate s[], Coordinate d[]);
char * manual_placement(Coordinate c[], Coordinate b[], Coordinate r[], Coordinate s[], Coordinate d[], char p_board[][MAX_COLS]);
int * output_current_move(FILE *infile, int turn, int alt_player, int p1_hit, int p2_hit, int p1_shots[][2], int p2_shots[][2], int player_start,
	int p1sink_array[], int p2sink_array[], int sink_array_repeat[]);
void output_stats(FILE *infile, int p1_hit_count, int p2_hit_count, Stats p1_stats, Stats p2_stats, int turn);