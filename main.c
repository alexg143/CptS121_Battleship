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

#include "header.h"

int main(void)
{

	// Variable Declarations --------------------------------------------------------------------
	int choice = 0, player = 1, player_start = 0, turn = 0, win = 0, alt_player = 0,
		p1_hit = 0, p2_hit = 0, p1_hit_count = 0, p2_hit_count = 0,
		*p1_hit_count_ptr = &p1_hit_count, *p2_hit_count_ptr = &p2_hit_count,
		p1_shots[100][2] = { 10 }, p2_shots[100][2] = { 10 },
		p1_sink_array[5] = { 0 }, p2_sink_array[5] = { 0 },
		p1_sink_repeat_array[5] = { 0 }, p2_sink_repeat_array[5] = { 0 };

	char p1_board[MAX_ROWS][MAX_COLS] = { '\0' }, 
		p2_board[MAX_ROWS][MAX_COLS] = { '\0' };

	Coordinate start_pt = { -1, -1 }, *start_pt_ptr = &start_pt,
	p1_carrier[5], p1_battleship[4], p1_cruiser[3], p1_submarine[3], p1_destroyer[2],
	p2_carrier[5], p2_battleship[4], p2_cruiser[3], p2_submarine[3], p2_destroyer[2];

	Dir direction = HORIZONTAL;
	Stats p1_stats = { 0, 0, 0, 0.0 }, p2_stats = { 0, 0, 0, 0.0 };

	FILE *infile = NULL;

	srand((unsigned int)time(NULL));
	//-------------------------------------------------------------------------------------------

	infile = fopen("battleship.log", "w");

	// Game start/Board Intialization/Ship Placement --------------------------------------------
	init_board(p1_board, MAX_ROWS, MAX_COLS); 
	init_board(p2_board, MAX_ROWS, MAX_COLS);

	main_menu();
	choice = position_choice();
	
	if (choice == 1)
	{
		manual_placement(p1_carrier, p1_battleship, p1_cruiser, p1_submarine, p1_destroyer, p1_board);
	}
	else if (choice == 2)
	{
		random_placement(direction, &start_pt, p1_board, p1_carrier, p1_battleship, p1_cruiser, p1_submarine, p1_destroyer);
	}
	random_placement(direction, &start_pt, p2_board, p2_carrier, p2_battleship, p2_cruiser, p2_submarine, p2_destroyer);
	//-------------------------------------------------------------------------------------------

	player_start = gen_player_start();

	if (player_start == 1) // Game loops until player or AI wins
	{
		do {
			print_board(p1_board, MAX_ROWS, MAX_COLS, player);
			++player;
			print_board(p2_board, MAX_ROWS, MAX_COLS, player);
			--player;

			get_target(p1_shots, turn);
			p1_hit = hit_or_miss(p1_shots, p2_board, turn);
			update_board(p1_shots, p1_hit, p2_board, turn);
			system("cls");
			print_hit_or_miss(p1_shots, p1_hit, turn);
			has_sunk(p2_board, p1_sink_array);
			output_current_move(infile, turn, alt_player, p1_hit, p2_hit, p1_shots,
				p2_shots, player_start, p1_sink_array, p2_sink_array, p1_sink_repeat_array);
			++alt_player;

			print_board(p1_board, MAX_ROWS, MAX_COLS, player);
			++player;
			print_board(p2_board, MAX_ROWS, MAX_COLS, player);
			--player;

			random_target(p2_shots, turn);
			p2_hit = hit_or_miss(p2_shots, p1_board, turn);
			print_hit_or_miss(p2_shots, p2_hit, turn);
			update_board(p2_shots, p2_hit, p1_board, turn);
			has_sunk(p1_board, p2_sink_array);
			output_current_move(infile, turn, alt_player, p1_hit, p2_hit, p1_shots,
				p2_shots, player_start, p1_sink_array, p2_sink_array, p2_sink_repeat_array);
			++alt_player;
			system("pause");
			system("cls");

			++turn;
			get_num_hits(p1_hit, p2_hit, &p1_hit_count, &p2_hit_count);
			win = has_won(p1_hit_count, p2_hit_count);
		} while (win == 0);
	}
	else
	{
		do {
			print_board(p1_board, MAX_ROWS, MAX_COLS, player);
			++player;
			print_board(p2_board, MAX_ROWS, MAX_COLS, player);
			--player;

			random_target(p2_shots, turn);
			p2_hit = hit_or_miss(p2_shots, p1_board, turn);
			print_hit_or_miss(p2_shots, p2_hit, turn);
			update_board(p2_shots, p2_hit, p1_board, turn);
			has_sunk(p1_board, p2_sink_array);
			++alt_player;
			output_current_move(infile, turn, alt_player, p1_hit, p2_hit, p1_shots,
				p2_shots, player_start, p1_sink_array, p2_sink_array, p2_sink_repeat_array);
			system("pause");
			system("cls");

			print_board(p1_board, MAX_ROWS, MAX_COLS, player);
			++player;
			print_board(p2_board, MAX_ROWS, MAX_COLS, player);
			--player;

			get_target(p1_shots, turn);
			p1_hit = hit_or_miss(p1_shots, p2_board, turn);
			update_board(p1_shots, p1_hit, p2_board, turn);
			system("cls");
			print_hit_or_miss(p1_shots, p1_hit, turn);
			has_sunk(p2_board, p1_sink_array);
			++alt_player;
			output_current_move(infile, turn, alt_player, p1_hit, p2_hit, p1_shots,
				p2_shots, player_start, p1_sink_array, p2_sink_array, p1_sink_repeat_array);

			++turn;
			get_num_hits(p1_hit, p2_hit, &p1_hit_count, &p2_hit_count);
			win = has_won(p1_hit_count, p2_hit_count);
		} while (win == 0);
	}

	output_stats(infile, p1_hit_count, p2_hit_count, p1_stats, p2_stats, turn);
	fclose(infile);

	return 0;
}