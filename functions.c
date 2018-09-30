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

/*
Function: void main_menu(void)
Date Created: April 1, 2018
Date Last Modified: April 4, 2018
Description: This function prints a menu and
			 clears the screen when enter is
			 pressed.
Input parameters: void
Returns: n/a
Preconditions: n/a
Postconditions: menu is printed
*/
void main_menu(void)
{
	char start = '\0';
	do
	{
		printf("***** Welcome to Battleship! *****\n\n");
		printf("Rules of the Game:\n");
		printf("1. Two players have boards that they place their battleships on.\n2. \
One player selects a coordinate to use to fire at the other board.\n3. The winner is the\
 player that sinks all the other players ships.\n4. For this game in particular, once the game ends\
 player statistics are outputted to a log file.\n5. Have fun!\n\n");
		printf("Hit enter to start the game!\n");
		start = getchar();
	} while (start != '\n');
	system("cls");
}

/*
Function: int position_choice(void)
Date Created: April 1, 2018
Date Last Modified: April 4, 2018
Description: This function asks the user to
			 enter ships randomly or manually.
Input parameters: void
Returns: choice
Preconditions: n/a
Postconditions: choice is returned.
*/
int position_choice(void)
{
	int choice = 0;
	do
	{
		printf("1. Enter position of ships manually\n2. \
Allow the program to randomly select the positions of ships\n\n\
Please select the following from the menu: ");
		scanf("%d", &choice);
	} while ((choice != 1) && (choice != 2));
	return choice;
}

/*
Function: void init_board(char board[][MAX_COLS], int num_rows, int num_cols)
Date Created: April 1, 2018
Date Last Modified: April 4, 2018
Description: This function initializes the
			 game boards to the '~' symbol.
Input parameters: char board[][MAX_COLS], int num_rows, int num_cols
Returns: n/a
Preconditions: board, num_rows, num_cols are intialized
Postconditions: board is intialized
*/
void init_board(char board[][MAX_COLS], int num_rows, int num_cols) // given by Andy
{
	int row_index = 0, col_index = 0;

	for (row_index = 0; row_index < num_rows; ++row_index)
	{
		for (col_index = 0; col_index < num_cols; ++col_index)
		{
			board[row_index][col_index] = '~';
		}
	}
}

/*
Function: void print_board(char board[][MAX_COLS], int num_rows, int num_cols, int player)
Date Created: April 1, 2018
Date Last Modified: April 4, 2018
Description: This function prints the game
			 board.
Input parameters: char board[][MAX_COLS], int num_rows, int num_cols, int player
Returns: n/a
Preconditions: board, num_rows, num_cols, player are intialized
Postconditions: board is printed
*/
void print_board(char board[][MAX_COLS], int num_rows, int num_cols, int player)
{
	int row_index = 0, col_index = 0;
	printf("Player%d's Board:\n", player);
	putchar(' ');
	for (col_index = 0; col_index < num_cols; ++col_index)
	{
		putchar(' ');
		printf("%d", col_index);
	}
	putchar('\n');
	for (row_index = 0; row_index < num_rows; ++row_index) 
	{
		printf("%d ", row_index);
		for (col_index = 0; col_index < num_cols; ++col_index)  // fix once done
		{
			if (((board[row_index][col_index] == 'c') || (board[row_index][col_index] == 'b')
				|| (board[row_index][col_index] == 'r') || (board[row_index][col_index] == 's')
				|| (board[row_index][col_index] == 'd')) && (player == 2))
			{
				printf("~ ", board[row_index][col_index]);
			}
			else
			{
				printf("%c ", board[row_index][col_index]);
			}
		}
		putchar('\n');
	}
}

/*
Function: int gen_player_start(void)
Date Created: April 1, 2018
Date Last Modified: April 4, 2018
Description: This function prints a randomly chosen
			 player.
Input parameters: void
Returns: random_player
Preconditions: n/a
Postconditions: board is printed
*/
int gen_player_start(void)
{
	int random_player = 0;
	random_player = rand() % 2 + 1;
	if (random_player == 1)
	{
		printf("Player 1 has been randomly chosen to go first!\n\n");
	}
	else if (random_player == 2)
	{
		printf("Player 2 has been randomly chosen to go first!\n\n");
	}
	return random_player;
}

/*
Function: int * get_target(int p1_shots[][2], int turn)
Date Created: April 1, 2018
Date Last Modified: April 4, 2018
Description: This function gets coordinates
			 from the user and checks if they
			 were already used.
Input parameters: int p1_shots[][2], int turn
Returns: p1_shots[][2]
Preconditions: n/a
Postconditions: array updated
*/
int * get_target(int p1_shots[][2], int turn)
{
	int index = 0, coordinate[2] = { 0 }, success = 0;
	do
	{
		printf("Enter a target (add a space between each number): ");
		for (index = 0; index < 2; ++index)
		{
			scanf("%d", &coordinate[index]);
		}
		if (turn > 0)
		{
			for (index = 0; index < turn; ++index)
			{
				if ((p1_shots[index][0] == coordinate[0]) && (p1_shots[index][1] == coordinate[1]))
				{
					success = 1;
					printf("These coordinates were previously used, select new ones.\n");
				}
				else
				{
					success = 0;
				}
			}
		}
	} while (success == 1);
	p1_shots[turn][0] = coordinate[0];
	p1_shots[turn][1] = coordinate[1];
}

/*
Function: int * random_target(int p2_shots[][2], int turn)
Date Created: April 1, 2018
Date Last Modified: April 4, 2018
Description: This function selects a random
			 target.
Input parameters: int p2_shots[][2], int turn
Returns: p2_shots[][2]
Preconditions: n/a
Postconditions: array updated
*/
int * random_target(int p2_shots[][2], int turn)
{
	int rand_row = 0, rand_col = 0, index = 0, success = 0;
	do
	{
		rand_row = rand() % MAX_ROWS;
		rand_col = rand() % MAX_COLS;
		if (turn > 0)
		{
			for (index = 0; index < turn; ++index)
			{
				if ((p2_shots[index][0] == rand_row) && (p2_shots[index][1] == rand_col))
				{
					success = 1;
				}
				else
				{
					success = 0;
				}
			}
		}
	} while (success > 0);
	p2_shots[turn][0] = rand_row;
	p2_shots[turn][1] = rand_col;
	printf("Player selects: %d %d\n", p2_shots[turn][0], p2_shots[turn][1]);
}

/*
Function: int hit_or_miss(int shots[][2], char board[][MAX_COLS], int turn)
Date Created: April 1, 2018
Date Last Modified: April 4, 2018
Description: This function indicates if a shot
			 was a hit or a miss.
Input parameters: int shots[][2], char board[][MAX_COLS], int turn
Returns: hit
Preconditions: variables initialized
Postconditions: hit returned
*/
int hit_or_miss(int shots[][2], char board[][MAX_COLS], int turn)
{
	int hit = 0;
	if (board[shots[turn][0]][shots[turn][1]] == '~')
	{
		hit = 0;
	}
	else
	{
		hit = 1;
	}
	return hit;
}

/*
Function: void print_hit_or_miss(int shots[][2], int hit, int turn)
Date Created: April 1, 2018
Date Last Modified: April 4, 2018
Description: This function prints if a shot
			 was a hit or a miss.
Input parameters: int shots[][2], int hit, int turn
Returns: n/a
Preconditions: variables initialized
Postconditions: statement printed
*/
void print_hit_or_miss(int shots[][2], int hit, int turn)
{
	if (hit == 1)
	{
		printf("%d,%d is a hit!\n", shots[turn][0], shots[turn][1]);
	}
	else if (hit == 0)
	{
		printf("%d,%d is a miss!\n", shots[turn][0], shots[turn][1]);
	}
}

/*
Function: int has_won(int p1_hits, int p2_hits)
Date Created: April 1, 2018
Date Last Modified: April 4, 2018
Description: This function prints which player
			 has won.
Input parameters: int p1_hits, int p2_hits
Returns: win
Preconditions: variables initialized
Postconditions: statement printed
*/
int has_won(int p1_hits, int p2_hits)
{
	int win = 0;
	if (p1_hits == 17)
	{
		printf("Player 1 has won!\n");
		++win;
	}
	if (p2_hits == 17)
	{
		printf("Player 2 has won!\n");
		++win;
	}
	return win;
}

/*
Function: int * has_sunk(char p_board[][MAX_COLS], int p_sink_array[])
Date Created: April 1, 2018
Date Last Modified: April 4, 2018
Description: This function determines if a ship has
			 been sunk and prints a statement if it
			 has.
Input parameters: char p_board[][MAX_COLS], int p_sink_array[]
Returns: p_sink_array[]
Preconditions: variables initialized
Postconditions: p_sink_array[] updated
*/
int * has_sunk(char p_board[][MAX_COLS], int p_sink_array[])
{
	int row_index = 0, col_index = 0, c_index = 0, b_index = 0, r_index = 0, s_index = 0, d_index = 0;

	for (; row_index < MAX_ROWS; ++row_index)
	{
		for (col_index = 0; col_index < MAX_COLS; ++col_index)
		{
			if (p_board[row_index][col_index] == 'c')
			{
				++c_index;
			}
			if (p_board[row_index][col_index] == 'b')
			{
				++b_index;
			}
			if (p_board[row_index][col_index] == 'r')
			{
				++r_index;
			}
			if (p_board[row_index][col_index] == 's')
			{
				++s_index;
			}
			if (p_board[row_index][col_index] == 'd')
			{
				++d_index;
			}
		}
	}
	if ((c_index == 0) && (p_sink_array[0] == 0))
	{
		p_sink_array[0] = 1;
		printf("Carrier sunk.\n");
	}
	else if ((b_index == 0) && (p_sink_array[1] == 0))
	{
		p_sink_array[1] = 1;
		printf("Battleship sunk.\n");
	}
	else if ((r_index == 0) && (p_sink_array[2] == 0))
	{
		p_sink_array[2] = 1;
		printf("Cruiser sunk.\n");
	}
	else if ((s_index == 0) && (p_sink_array[3] == 0))
	{
		p_sink_array[3] = 1;
		printf("Submarine sunk.\n");
	}
	else if ((d_index == 0) && (p_sink_array[4] == 0))
	{
		p_sink_array[4] = 1;
		printf("Destroyer sunk.\n");
	}
	return p_sink_array;
}

/*
Function: int get_num_hits(int p1_hits, int p2_hits, int *p1_hit_count_ptr, int *p2_hit_count_ptr)
Date Created: April 1, 2018
Date Last Modified: April 4, 2018
Description: This function adds to a hit counter
			 if the user or AI gets a hit on the 
			 board.
Input parameters: int p1_hits, int p2_hits, int *p1_hit_count_ptr, int *p2_hit_count_ptr
Returns: hit counter pointers are returned
Preconditions: variables initialized
Postconditions: pointers returned
*/
int get_num_hits(int p1_hits, int p2_hits, int *p1_hit_count_ptr, int *p2_hit_count_ptr)
{
	if (p1_hits == 1)
	{
		++*p1_hit_count_ptr;
	}
	if (p2_hits == 1)
	{
		++*p2_hit_count_ptr;
	}
}

/*
Function: char * update_board(int shots[][2], int hit, char p_board[][MAX_COLS], int turn)
Date Created: April 1, 2018
Date Last Modified: April 4, 2018
Description: This function updates the board based
			 on hits or misses.
Input parameters: int shots[][2], int hit, char p_board[][MAX_COLS], int turn
Returns: updated board returned
Preconditions: variables initialized
Postconditions: pointer returned
*/
char * update_board(int shots[][2], int hit, char p_board[][MAX_COLS], int turn)
{
	int row = 0, col = 0;
	row = shots[turn][0];
	col = shots[turn][1];
	if (hit == 1)
	{
		p_board[row][col] = '*';
	}
	else
	{
		p_board[row][col] = 'm';
	}
}

/*
Function: void gen_start_pt(Coordinate *start_pt_ptr, Dir direction, int length)
Date Created: April 1, 2018
Date Last Modified: April 4, 2018
Description: This function generates a random
			 start point for a ship.
Input parameters: Coordinate *start_pt_ptr, Dir direction, int length
Returns: *start_pt_ptr
Preconditions: variables initialized
Postconditions: pointer returned
*/
void gen_start_pt(Coordinate *start_pt_ptr, Dir direction, int length) // partly given by Andy
{
	if (direction == HORIZONTAL)
	{
		start_pt_ptr->row = rand() % MAX_ROWS;
		start_pt_ptr->col = rand() % (MAX_COLS - length + 1);
	}
	else if (direction == VERTICAL)
	{
		start_pt_ptr->row = rand() % (MAX_ROWS - length + 1);
		start_pt_ptr->col = rand() % MAX_COLS;
	}
}

/*
Function: Dir gen_dir(void)
Date Created: April 1, 2018
Date Last Modified: April 4, 2018
Description: This function generates a random
			 direction (horizontal or vertical).
Input parameters: void
Returns: direction
Preconditions: variables initialized
Postconditions: direction returned
*/
Dir gen_dir(void) // andy
{
	Dir direction = HORIZONTAL;

	direction = (Dir)rand() % 2;

	return direction;
}

/*
Function: char * rand_ship_placement(int length, char symbol, Dir direction, Coordinate *start_pt_ptr, char p_board[][MAX_COLS], Coordinate n[])
Date Created: April 1, 2018
Date Last Modified: April 4, 2018
Description: This function randomly places ships on
			 the board.
Input parameters: int length, char symbol, Dir direction, Coordinate *start_pt_ptr, char p_board[][MAX_COLS], Coordinate n[]
Returns: n/a
Preconditions: variables initialized
Postconditions: random ships placed
*/
char * rand_ship_placement(int length, char symbol, Dir direction, Coordinate *start_pt_ptr, char p_board[][MAX_COLS], Coordinate n[])
{
	int index = 0;
	p_board[start_pt_ptr->row][start_pt_ptr->col] = symbol; // do for each ship:
	for (; index < length; ++index)
	{
		if (direction == VERTICAL)
		{
			p_board[start_pt_ptr->row + index][start_pt_ptr->col] = symbol;
			n[length - index - 1].row = start_pt_ptr->row + index;
			n[length - index - 1].col = start_pt_ptr->col;
		}
		else if (direction == HORIZONTAL)
		{
			p_board[start_pt_ptr->row][start_pt_ptr->col + index] = symbol;
			n[length - index - 1].row = start_pt_ptr->row;
			n[length - index - 1].col = start_pt_ptr->col + index;
		}
	}
}

/*
Function: int overlap_check(Coordinate c[], Coordinate b[], Coordinate r[], Coordinate s[], Coordinate d[])
Date Created: April 1, 2018
Date Last Modified: April 4, 2018
Description: This function checks if the coordinates
			 of each ship are the same.
Input parameters: Coordinate c[], Coordinate b[], Coordinate r[], Coordinate s[], Coordinate d[]
Returns: success
Preconditions: variables initialized
Postconditions: success returned
*/
int overlap_check(Coordinate c[], Coordinate b[], Coordinate r[], Coordinate s[], Coordinate d[])
{
	int index_c = 0, index_b = 0, index_r = 0, index_s = 0, index_d = 0, success = 1;
	for (index_c = 0; index_c < CARRIER; ++index_c)
	{
		for (index_b = 0; index_b < BATTLESHIP; ++index_b)
		{
			if ((c[index_c].row == b[index_b].row) && (c[index_c].col == b[index_b].col))
			{
				success = 0;
			}
		}
		for (index_d = 0; index_d < DESTROYER; ++index_d)
		{
			if ((c[index_c].row == d[index_d].row) && (c[index_c].col == d[index_d].col))
			{
				success = 0;
			}
		}
		for (index_d = 0; index_r < CRUISER; ++index_r)
		{
			if ((c[index_c].row == r[index_r].row) && (c[index_c].col == r[index_r].col))
			{
				success = 0;
			}
		}
		for (index_d = 0; index_s < SUBMARINE; ++index_s)
		{
			if ((c[index_c].row == s[index_s].row) && (c[index_c].col == s[index_s].col))
			{
				success = 0;
			}
		}
	}
	for (index_b = 0; index_b < BATTLESHIP; ++index_b)
	{
		for (index_c = 0; index_c < CARRIER; ++index_c)
		{
			if ((b[index_b].row == c[index_c].row) && (b[index_b].col == c[index_c].col))
			{
				success = 0;
			}
		}
		for (index_d = 0; index_d < DESTROYER; ++index_d)
		{
			if ((b[index_b].row == d[index_d].row) && (b[index_b].col == d[index_d].col))
			{
				success = 0;
			}
		}
		for (index_r = 0; index_r < CRUISER; ++index_r)
		{
			if ((b[index_b].row == r[index_r].row) && (b[index_b].col == r[index_r].col))
			{
				success = 0;
			}
		}
		for (index_s = 0; index_s < SUBMARINE; ++index_s)
		{
			if ((b[index_b].row == s[index_s].row) && (b[index_b].col == s[index_s].col))
			{
				success = 0;
			}
		}
	}
	for (index_s = 0; index_s < SUBMARINE; ++index_s)
	{
		for (index_b = 0; index_b < BATTLESHIP; ++index_b)
		{
			if ((s[index_s].row == b[index_b].row) && (s[index_s].col == b[index_b].col))
			{
				success = 0;
			}
		}
		for (index_d = 0; index_d < DESTROYER; ++index_d)
		{
			if ((s[index_s].row == d[index_d].row) && (s[index_s].col == d[index_d].col))
			{
				success = 0;
			}
		}
		for (index_r = 0; index_r < CRUISER; ++index_r)
		{
			if ((s[index_s].row == r[index_r].row) && (s[index_s].col == r[index_r].col))
			{
				success = 0;
			}
		}
		for (index_c = 0; index_c < CARRIER; ++index_c)
		{
			if ((s[index_s].row == c[index_c].row) && (s[index_s].col == c[index_c].col))
			{
				success = 0;
			}
		}
	}
	for (index_r = 0; index_r < CRUISER; ++index_r)
	{
		for (index_c = 0; index_c < CARRIER; ++index_c)
		{
			if ((r[index_r].row == c[index_c].row) && (r[index_r].col == c[index_c].col))
			{
				success = 0;
			}
		}
		for (index_d = 0; index_d < DESTROYER; ++index_d)
		{
			if ((r[index_r].row == d[index_d].row) && (r[index_r].col == d[index_d].col))
			{
				success = 0;
			}
		}
		for (index_s = 0; index_s < SUBMARINE; ++index_s)
		{
			if ((r[index_r].row == s[index_s].row) && (r[index_r].col == s[index_s].col))
			{
				success = 0;
			}
		}
		for (index_b = 0; index_b < BATTLESHIP; ++index_b)
		{
			if ((r[index_r].row == b[index_b].row) && (r[index_r].col == b[index_b].col))
			{
				success = 0;
			}
		}
	}
	for (index_d = 0; index_d < DESTROYER; ++index_d)
	{
		for (index_c = 0; index_c < CARRIER; ++index_c)
		{
			if ((d[index_d].row == c[index_c].row) && (d[index_d].col == c[index_c].col))
			{
				success = 0;
			}
		}
		for (index_r = 0; index_r < CRUISER; ++index_r)
		{
			if ((d[index_d].row == r[index_r].row) && (d[index_d].col == r[index_r].col))
			{
				success = 0;
			}
		}
		for (index_s = 0; index_s < SUBMARINE; ++index_s)
		{
			if ((d[index_d].row == s[index_s].row) && (d[index_d].col == s[index_s].col))
			{
				success = 0;
			}
		}
		for (index_b = 0; index_b < BATTLESHIP; ++index_b)
		{
			if ((d[index_d].row == b[index_b].row) && (d[index_d].col == b[index_b].col))
			{
				success = 0;
			}
		}
	}
	return success;
}

/*
Function: char * random_placement(Dir direction, Coordinate *start_pt_ptr, char p_board[][MAX_COLS],
	Coordinate c[], Coordinate b[], Coordinate r[], Coordinate s[], Coordinate d[])
Date Created: April 1, 2018
Date Last Modified: April 4, 2018
Description: This function checks if the coordinates
			 of each ship are the same and will replace
			 the ships if they are.
Input parameters: Dir direction, Coordinate *start_pt_ptr, char p_board[][MAX_COLS],
	Coordinate c[], Coordinate b[], Coordinate r[], Coordinate s[], Coordinate d[]
Returns: updated board
Preconditions: variables initialized
Postconditions: board updated
*/
char * random_placement(Dir direction, Coordinate *start_pt_ptr, char p_board[][MAX_COLS],
	Coordinate c[], Coordinate b[], Coordinate r[], Coordinate s[], Coordinate d[])
{
	char c_symbol = 'c', b_symbol = 'b', r_symbol = 'r', s_symbol = 's', d_symbol = 'd';
	int success = 0;
	do
	{
		init_board(p_board, MAX_ROWS, MAX_COLS);

		direction = gen_dir();
		gen_start_pt(start_pt_ptr, direction, CARRIER);
		rand_ship_placement(CARRIER, c_symbol, direction, start_pt_ptr, p_board, c);

		direction = gen_dir();
		gen_start_pt(start_pt_ptr, direction, BATTLESHIP);
		rand_ship_placement(BATTLESHIP, b_symbol, direction, start_pt_ptr, p_board, b);

		direction = gen_dir();
		gen_start_pt(start_pt_ptr, direction, CRUISER);
		rand_ship_placement(CRUISER, r_symbol, direction, start_pt_ptr, p_board, r);

		direction = gen_dir();
		gen_start_pt(start_pt_ptr, direction, SUBMARINE);
		rand_ship_placement(SUBMARINE, s_symbol, direction, start_pt_ptr, p_board, s);

		direction = gen_dir();
		gen_start_pt(start_pt_ptr, direction, DESTROYER);
		rand_ship_placement(DESTROYER, d_symbol, direction, start_pt_ptr, p_board, d);

		success = overlap_check(c, b, r, s, d);
	} while (success == 0);
}

/*
Function: Coordinate c[], Coordinate b[], Coordinate r[], Coordinate s[], Coordinate d[], char p_board[][MAX_COLS]
Date Created: April 1, 2018
Date Last Modified: April 4, 2018
Description: This function allows the user to manually enter
			 coordinates and checks if they have already been
			 entered or are off the board.
Input parameters: Coordinate c[], Coordinate b[], Coordinate r[], Coordinate s[], Coordinate d[], char p_board[][MAX_COLS]
Returns: player coordinates
Preconditions: variables initialized
Postconditions: player coordinates returned
*/
char * manual_placement(Coordinate c[], Coordinate b[], Coordinate r[], Coordinate s[], Coordinate d[], char p_board[][MAX_COLS]) 
{
	int c_num[10] = { 0 }, b_num[8] = { 0 }, r_num[6] = { 0 }, s_num[6] = { 0 }, d_num[4] = { 0 }, index = 0, index2 = 0, 
		success = 0, success2 = 0;
	do
	{
	init_board(p_board, MAX_ROWS, MAX_COLS);
		do
		{
			success = 0;
			printf("\nPlease enter the five cells to place the carrier across (add a space between each number): ");
			for (index = 0; index < 10; ++index)
			{
				scanf("%d", &c_num[index]);
				if ((0 <= c_num[index]) && (c_num[index] <= 9))
				{
					success++;
				}
			}
			for (index = 0, index2 = 0; index < 5; ++index, ++index2)
			{
				c[index].col = c_num[index2];
				++index2;
				c[index].row = c_num[index2];
			}
			if (success != 10)
			{
				printf("Invalid entry, please try again.\n");
			}
		} while (success != 10);
		do
		{
			success = 0;
			printf("Please enter the four cells to place the battleship across (add a space between each number): ");
			for (index = 0; index < 8; ++index)
			{
				scanf("%d", &b_num[index]);
				if ((0 <= b_num[index]) && (b_num[index] <= 9))
				{
					success++;
				}
			}
			for (index = 0, index2 = 0; index < 4; ++index, ++index2)
			{
				b[index].col = b_num[index2];
				++index2;
				b[index].row = b_num[index2];
			}
			if (success != 8)
			{
				printf("Invalid entry, please try again.\n");
			}
		} while (success != 8);
		do
		{
			success = 0;
			printf("Please enter the three cells to place the cruiser across (add a space between each number): ");
			for (index = 0; index < 6; ++index)
			{
				scanf("%d", &r_num[index]);
				if ((0 <= r_num[index]) && (r_num[index] <= 9))
				{
					success++;
				}
			}
			for (index = 0, index2 = 0; index < 3; ++index, ++index2)
			{
				r[index].col = r_num[index2];
				++index2;
				r[index].row = r_num[index2];
			}
			if (success != 6)
			{
				printf("Invalid entry, please try again.\n");
			}
		} while (success != 6);
		do
		{
			success = 0;
			printf("Please enter the three cells to place the submarine across (add a space between each number): ");
			for (index = 0; index < 6; ++index)
			{
				scanf("%d", &s_num[index]);
				if ((0 <= s_num[index]) && (s_num[index] <= 9))
				{
					success++;
				}
			}
			for (index = 0, index2 = 0; index < 3; ++index, ++index2)
			{
				s[index].col = s_num[index2];
				++index2;
				s[index].row = s_num[index2];
			}
			if (success != 6)
			{
				printf("Invalid entry, please try again.\n");
			}
		} while (success != 6);
		do
		{
			success = 0;
			printf("Please enter the two cells to place the cruiser across (add a space between each number): ");
			for (index = 0; index < 4; ++index)
			{
				scanf("%d", &d_num[index]);
				if ((0 <= d_num[index]) && (d_num[index] <= 9))
				{
					success++;
				}
			}
			for (index = 0, index2 = 0; index < 2; ++index, ++index2)
			{
				d[index].col = d_num[index2];
				++index2;
				d[index].row = d_num[index2];
			}
			if (success != 4)
			{
				printf("Invalid entry, please try again.\n");
			}
		} while (success != 4);
		success2 = overlap_check(c, b, r, s, d);
		if (success2 == 0)
		{
			printf("\nSome ships overlap or have multiple of the same coordinates, please enter new coordinates.\n");
		}
	} while (success2 == 0);
	for (index = 0; index < 5; ++index)
	{
		p_board[c[index].col][c[index].row] = 'c';
	}
	for (index = 0; index < 4; ++index)
	{
		p_board[b[index].col][b[index].row] = 'b';
	}
	for (index = 0; index < 3; ++index)
	{
		p_board[r[index].col][r[index].row] = 'r';
	}
	for (index = 0; index < 3; ++index)
	{
		p_board[s[index].col][s[index].row] = 's';
	}
	for (index = 0; index < 2; ++index)
	{
		p_board[d[index].col][d[index].row] = 'd';
	}
}

/*
Function: int * output_current_move(FILE *infile, int turn, int alt_player, int p1_hit, int p2_hit, int p1_shots[][2], int p2_shots[][2], int player_start,
	int p1sink_array[], int p2sink_array[], int sink_array_repeat[])
Date Created: April 1, 2018
Date Last Modified: April 4, 2018
Description: This function outputs the current moves to the
			 battleship.log file each turn.
Input parameters: FILE *infile, int turn, int alt_player, int p1_hit, int p2_hit, int p1_shots[][2], int p2_shots[][2], int player_start,
	int p1sink_array[], int p2sink_array[], int sink_array_repeat[]
Returns: n/a
Preconditions: variables initialized
Postconditions: moves written to file
*/
int * output_current_move(FILE *infile, int turn, int alt_player, int p1_hit, int p2_hit, int p1_shots[][2], int p2_shots[][2], int player_start,
	int p1sink_array[], int p2sink_array[], int sink_array_repeat[])
{
	if (player_start == 1)
	{
		if (alt_player % 2 == 0)
		{
			if (p1_hit == 1)
			{
				fprintf(infile, "Player 1: %d,%d Hit! \n", p1_shots[turn][0], p1_shots[turn][1]);
			}
			if (p1_hit == 0)
			{
				fprintf(infile, "Player 1: %d,%d Miss! \n", p1_shots[turn][0], p1_shots[turn][1]);
			}
			if ((sink_array_repeat[0] == 0) && (p1sink_array[0] == 1))
			{
				fprintf(infile, "Carrier sunk.\n");
				sink_array_repeat[0] = 1;
			}
			if ((sink_array_repeat[1] == 0) && (p1sink_array[1] == 1))
			{
				fprintf(infile, "Battleship sunk.\n");
				sink_array_repeat[1] = 1;
			}
			if ((sink_array_repeat[2] == 0) && (p1sink_array[2] == 1))
			{
				fprintf(infile, "Cruiser sunk.\n");
				sink_array_repeat[2] = 1;
			}
			if ((sink_array_repeat[3] == 0) && (p1sink_array[3] == 1))
			{
				fprintf(infile, "Submarine sunk.\n");
				sink_array_repeat[3] = 1;
			}
			if ((sink_array_repeat[4] == 0) && (p1sink_array[4] == 1))
			{
				fprintf(infile, "Destroyer sunk.\n");
				sink_array_repeat[4] = 1;
			}
		}
		else if (alt_player % 2 != 0)
		{
			if (p2_hit == 1)
			{
				fprintf(infile, "Player 2: %d,%d Hit! \n", p2_shots[turn][0], p2_shots[turn][1]);
			}
			if (p2_hit == 0)
			{
				fprintf(infile, "Player 2: %d,%d Miss! \n", p2_shots[turn][0], p2_shots[turn][1]);
			}
			if ((sink_array_repeat[0] == 0) && (p2sink_array[0] == 1))
			{
				fprintf(infile, "Carrier sunk.\n");
				sink_array_repeat[0] = 1;
			}
			if ((sink_array_repeat[1] == 0) && (p2sink_array[1] == 1))
			{
				fprintf(infile, "Battleship sunk.\n");
				sink_array_repeat[1] = 1;
			}
			if ((sink_array_repeat[2] == 0) && (p2sink_array[2] == 1))
			{
				fprintf(infile, "Cruiser sunk.\n");
				sink_array_repeat[2] = 1;
			}
			if ((sink_array_repeat[3] == 0) && (p2sink_array[3] == 1))
			{
				fprintf(infile, "Submarine sunk.\n");
				sink_array_repeat[3] = 1;
			}
			if ((sink_array_repeat[4] == 0) && (p2sink_array[4] == 1))
			{
				fprintf(infile, "Destroyer sunk.\n");
				sink_array_repeat[4] = 1;
			}
		}
	}
	else if (player_start == 2)
	{
		if (alt_player % 2 != 0)
		{
			if (p2_hit == 1)
			{
				fprintf(infile, "Player 2: %d,%d Hit! \n", p2_shots[turn][0], p2_shots[turn][1]);
			}
			if (p2_hit == 0)
			{
				fprintf(infile, "Player 2: %d,%d Miss! \n", p2_shots[turn][0], p2_shots[turn][1]);
			}
			if ((sink_array_repeat[0] == 0) && (p2sink_array[0] == 1))
			{
				fprintf(infile, "Carrier sunk.\n");
				sink_array_repeat[0] = 1;
			}
			if ((sink_array_repeat[1] == 0) && (p2sink_array[1] == 1))
			{
				fprintf(infile, "Battleship sunk.\n");
				sink_array_repeat[1] = 1;
			}
			if ((sink_array_repeat[2] == 0) && (p2sink_array[2] == 1))
			{
				fprintf(infile, "Cruiser sunk.\n");
				sink_array_repeat[2] = 1;
			}
			if ((sink_array_repeat[3] == 0) && (p2sink_array[3] == 1))
			{
				fprintf(infile, "Submarine sunk.\n");
				sink_array_repeat[3] = 1;
			}
			if ((sink_array_repeat[4] == 0) && (p2sink_array[4] == 1))
			{
				fprintf(infile, "Destroyer sunk.\n");
				sink_array_repeat[4] = 1;
			}
		}
		else if (alt_player % 2 == 0)
		{
			if (p1_hit == 1)
			{
				fprintf(infile, "Player 1: %d,%d Hit! \n", p1_shots[turn][0], p1_shots[turn][1]);
			}
			if (p1_hit == 0)
			{
				fprintf(infile, "Player 1: %d,%d Miss! \n", p1_shots[turn][0], p1_shots[turn][1]);
			}
			if ((sink_array_repeat[0] == 0) && (p1sink_array[0] == 1))
			{
				fprintf(infile, "Carrier sunk.\n");
				sink_array_repeat[0] = 1;
			}
			if ((sink_array_repeat[1] == 0) && (p1sink_array[1] == 1))
			{
				fprintf(infile, "Battleship sunk.\n");
				sink_array_repeat[1] = 1;
			}
			if ((sink_array_repeat[2] == 0) && (p1sink_array[2] == 1))
			{
				fprintf(infile, "Cruiser sunk.\n");
				sink_array_repeat[2] = 1;
			}
			if ((sink_array_repeat[3] == 0) && (p1sink_array[3] == 1))
			{
				fprintf(infile, "Submarine sunk.\n");
				sink_array_repeat[3] = 1;
			}
			if ((sink_array_repeat[4] == 0) && (p1sink_array[4] == 1))
			{
				fprintf(infile, "Destroyer sunk.\n");
				sink_array_repeat[4] = 1;
			}
		}
	}
	return sink_array_repeat;
}

/*
Function: void output_stats(FILE *infile, int p1_hit_count, int p2_hit_count, Stats p1_stats, Stats p2_stats, int turn)
Date Created: April 1, 2018
Date Last Modified: April 4, 2018
Description: This function outputs the stats of each
			 player to the log file.
Input parameters: FILE *infile, int p1_hit_count, int p2_hit_count, Stats p1_stats, Stats p2_stats, int turn
Returns: n/a
Preconditions: variables initialized
Postconditions: data written to file
*/
void output_stats(FILE *infile, int p1_hit_count, int p2_hit_count, Stats p1_stats, Stats p2_stats, int turn)
{
	p1_stats.total_hits = p1_hit_count;
	p1_stats.total_misses = abs(p1_hit_count - turn);
	p1_stats.total_shots = turn;
	p1_stats.hits_misses_ratio = (p1_stats.total_hits / p1_stats.total_misses) * 100;
	p2_stats.total_hits = p2_hit_count;
	p2_stats.total_misses = abs(p2_hit_count - turn);
	p2_stats.total_shots = turn;
	p2_stats.hits_misses_ratio = (((double)p2_stats.total_hits) / ((double)p2_stats.total_misses)) * 100;

	printf("Stats ouputted to log file.\n");

	if (p1_stats.total_hits == 17)
	{
		fprintf(infile, "Player 1 has won! Player 2 has lost!\n\n");
	}
	else if (p2_stats.total_hits == 17)
	{
		fprintf(infile, "Player 2 has won! Player 1 has lost!\n\n");
	}

	fprintf(infile, "***Player 1 Stats***\nNumber hits: %d\nNumber misses: %d\nTotal shots: %d\nHit/Miss ratio: %lf%%\n\n",
		p1_stats.total_hits, p1_stats.total_misses, p1_stats.total_shots, p1_stats.hits_misses_ratio);
	fprintf(infile, "***Player 2 Stats***\nNumber hits: %d\nNumber misses: %d\nTotal shots: %d\nHit/Miss ratio: %lf%%",
		p2_stats.total_hits, p2_stats.total_misses, p2_stats.total_shots, p2_stats.hits_misses_ratio);
}