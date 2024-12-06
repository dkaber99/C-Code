#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#

// Structure for passing data to threads
 typedef struct
{
	// starting row 
	int row;
	// starting column
	int col;
	// Pointer to the board 
	int(*puzzle)[9];
}parameters;
//
// 
// 
 void* walkrows(void* params);
 void* walkcols(void* params);
 void* checkbox(void* params);
// Sudoku Puzzle
int main(void)
{
	int puzzle[9][9] =
	{
	{5,3,4,6,6,8,9,1,2},
	{6,7,2,1,9,5,3,4,8},
	{1,9,8,3,4,2,5,6,7},
	{8,5,9,7,6,1,4,2,3},
	{4,2,6,8,5,3,7,9,1},
	{7,1,3,9,2,4,8,5,6},
	{9,6,1,5,3,7,2,8,4},
	{2,8,7,4,1,9,6,3,5},
	{3,4,5,2,8,6,1,7,9}
	};
	// Create parameters for the column and rows check
	parameters* param_0 = (parameters*)malloc(sizeof(parameters));
	param_0->row = 0;
	param_0->col = 0;
	param_0->puzzle = puzzle;
	// Create parameters for the 3x3 wprker threads 

	// Box 1 
	parameters* param_1 = (parameters*)malloc(sizeof(parameters)); // creates a struct of a type parameter called param_n
	param_1->row = 0;
	param_1->col = 0;
	param_1->puzzle = puzzle;

	// Box 2 
	parameters* param_2 = (parameters*)malloc(sizeof(parameters)); // creates a struct of a type parameter called param_n
	param_2->row = 0;
	param_2->col = 3;
	param_2->puzzle = puzzle;

	// Box 3 
	parameters* param_3 = (parameters*)malloc(sizeof(parameters)); // creates a struct of a type parameter called param_n
	param_3->row = 0;
	param_3->col = 6;
	param_3->puzzle = puzzle;

	// Box 4 
	parameters* param_4 = (parameters*)malloc(sizeof(parameters)); // creates a struct of a type parameter called param_n
	param_4->row = 3;
	param_4->col = 0;
	param_4->puzzle = puzzle;

	// Box 5 
	parameters* param_5 = (parameters*)malloc(sizeof(parameters)); // creates a struct of a type parameter called param_n
	param_5->row = 3;
	param_5->col = 3;
	param_5->puzzle = puzzle;

	// Box 6 
	parameters* param_6 = (parameters*)malloc(sizeof(parameters)); // creates a struct of a type parameter called param_n
	param_6->row = 3;
	param_6->col = 6;
	param_6->puzzle = puzzle;

	// Box 7 
	parameters* param_7 = (parameters*)malloc(sizeof(parameters)); // creates a struct of a type parameter called param_n
	param_7->row = 6;
	param_7->col = 0;
	param_7->puzzle = puzzle;

	// Box 8 
	parameters* param_8 = (parameters*)malloc(sizeof(parameters)); // creates a struct of a type parameter called param_n
	param_8->row = 6;
	param_8->col = 3;
	param_8->puzzle = puzzle;

	// Box 9  
	parameters* param_9 = (parameters*)malloc(sizeof(parameters)); // creates a struct of a type parameter called param_n
	param_9->row = 6;
	param_9->col = 6;
	param_9->puzzle = puzzle;

	// Creating the threads
	pthread_t thread_rows, thread_cols, thread1, thread2, thread3, thread4, thread5, thread6, thread7, thread8, thread9;
	
	// Create return values for the threads 
	void* allrows;
	void* allcols;
	void* box1;
	void* box2;
	void* box3;
	void* box4;
	void* box5;
	void* box6;
	void* box7;
	void* box8;
	void* box9;
	
	// Initialze the threads (11 in total) 
	pthread_create(&thread_rows, NULL, walkrows, (void *)param_0);
	pthread_create(&thread_cols, NULL, walkcols, (void *)param_0);
	pthread_create(&thread1, NULL, checkbox, (void *)param_1);
	pthread_create(&thread2, NULL, checkbox, (void *)param_2);
	pthread_create(&thread3, NULL, checkbox, (void *)param_3);
	pthread_create(&thread4, NULL, checkbox, (void *)param_4);
	pthread_create(&thread5, NULL, checkbox, (void *)param_5);
	pthread_create(&thread6, NULL, checkbox, (void *)param_6);
	pthread_create(&thread7, NULL, checkbox, (void *)param_7);
	pthread_create(&thread8, NULL, checkbox, (void *)param_8);
	pthread_create(&thread9, NULL, checkbox, (void *)param_9);
	


	// Waiting for threads to finish jobs 
	pthread_join(thread_rows, &allrows);
	pthread_join(thread_cols, &allcols);
	pthread_join(thread1, &box1);
	pthread_join(thread2, &box2);
	pthread_join(thread3, &box3);
	pthread_join(thread4, &box4);
	pthread_join(thread5, &box5);
	pthread_join(thread6, &box6);
	pthread_join(thread7, &box7);
	pthread_join(thread9, &box9); //should be an 8 for both. Will cause an incorrect result.
	pthread_join(thread9, &box9);

if((unsigned long) allrows ==1 &&
            (unsigned long) allcols == 1 &&
            (unsigned long) box1 == 1 &&
            (unsigned long) box2 == 1 &&
            (unsigned long) box3 == 1 &&
            (unsigned long) box4 == 1 &&
            (unsigned long) box5 == 1 &&
            (unsigned long) box6 == 1 &&
            (unsigned long) box7 == 1 &&
            (unsigned long) box8 == 1 &&
            (unsigned long) box9 == 1 )
{
  printf("The Sudoku Puzzle is solved!\n");
}
else
{
	printf("The Sudoku Puzzle is NOT Solved.\n");
}
return 0;
}

// Checks each row for nums 1-9
//param void* The parameter --> pointer 
//return void* 1 if all rows contain nums 1-9, 0 if not 
void* walkrows(void* params)
{
	parameters* data = (parameters*)params;
	int startrow = data->row;
	int startcol = data->col;
	
	for (int i = startrow; i < 9; ++i) 
	{
		int row[10] = { 0 };
		for (int j = startcol; j < 9; ++j) 
		{
			int value = data->puzzle[i][j];
			if (row[value] != 0) 
			{
				return (void*)0;
			}
			else 
			{
				row[value] = 1;
			}
		}
	}
	return (void*)1;
}

// Checks each column for nums 1-9
// param void* The parameter ---> pointer 
// return void* 1 if all rows contains nums 1-9, 0 if not 
void* walkcols(void* params)
{
	parameters* data = (parameters*)params;
	int startrow = data->row;
	int startcol = data->col;
	for (int i = startcol; i < 9; ++i) 
	{
		int col[10] = { 0 };
		for (int j = startrow; j < 9; ++j) 
		{
			int value = data->puzzle[j][i];
			if (col[value] != 0) 
			{
				return (void*)0;
			}
			else 
			{
				col[value] = 1;
			}
		}
	}
	return (void*)1;
}
// Checks if a box of size 3x3 contains nums 1-9
// param void* The parameter ---> pointer 
// return void* 1 if all rows contains nums 1-9, 0 otherwise 

void* checkbox(void* params) 
{
	parameters* data = (parameters*)params;
	int startrow = data->row;
	int startcol = data->col;
	int saved[10] = { 0 };
	for (int i = startrow; i < startrow + 3; ++i) 
	{
		for (int j = startcol; j < startcol + 3; ++j) 
		{
			int value = data->puzzle[i][j];
			if (saved[value] != 0) 
			{
				return (void*)0;
			}
			else 
			{
				saved[value] = 1;
			}
		}
	}
	return (void*)1;
}
