/* 
 * Author: Sandeep Singh
 * Date  : Oct 2, 2012
 * 
 * Copyright 2012 Sandeep Singh (sandeepsinghmails@gmail.com)
 *
 * This file is part of  Tic-Tac-Toe--Human-Vs-Computer.
 * Tic-Tac-Toe--Human-Vs-Computer is free software: you can redistribute it
 * and/or modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Tic-Tac-Toe--Human-Vs-Computer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with Tic-Tac-Toe--Human-Vs-Computer. If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VICTORY 	  1
#define NO_VICTORY 	  0

#define NO 			  0
#define YES 		  1

#define DEF_DEFEAT   -1
#define KEEP_PLAYING -2

void print_tic_tac_toe 	 (char **matrix);
void computer_play 		 (char **matrix);
void user_play 			 (char **matrix);
int  update_stats 		 (char **matrix);
void print_stats 		 (char **matrix);
void reset_stats 		 (char **array);
int  validate_def_defeat (char **matrix);
void draw_line(void);

/* Global Statistics: 
 *  Each Row   			: How many: 'X', 'Y', 'O's are present
 *  Each Column			: How many: 'X', 'Y', 'O's are present
 *  Left Body Diagonal	: How many: 'X', 'Y', 'O's are present
 *  Right Body Diagonal	: How many: 'X', 'Y', 'O's are present
 */

typedef struct 
{
	int *row_stats;
	int *col_stats;
	int ldiagonal_stats;
	int rdiagonal_stats;
} global_stats;

global_stats *p_global_stats;

int rowsize = 0;
int colsize = 0;

/* p_global_stats contains 3 arrays: index 0 -> For User Stats ('X')
 *								   : index 1 -> For Computer Stats ('Y')
 *								   : index 2 -> For Vacant Positions Stats ('O')
 */

int main()
{
	int rowindex = 0;

	int victory_flag = NO_VICTORY; 

	int num_choices; /* No. of Free Positions -- available to be filled by the User/Computer */

	int counter = 0;

	char **matrix = NULL;

	/* Request the User to Choose the Type of Matrix */
	printf("\nWelcome to the Game: Tic-Tac-Toe--Human Vs Computer!\n\n");
	printf("\nPlease Select the Order of Matrix (Example: Choose 4 for a 4x4 Matrix):\n\n");
	scanf ("%d", &rowsize);
	colsize = rowsize;
	
	num_choices = rowsize*colsize; /* No. of Positions to be filled-in by User */

	/* Initialize MatriX */

	/* Allocate Memory for Rows */
	matrix = malloc(rowsize*sizeof(char*));
	if (NULL==matrix)
	{
		printf("\nMemory Allocation failed\n");
		exit (EXIT_FAILURE);
	}

	/* Now, allocate memory for Columns */
	for (rowindex=0; rowindex<rowsize; rowindex++)
	{
		*(matrix+rowindex) = malloc(colsize*sizeof(char));
		if (NULL==*(matrix+rowindex))
		{
			printf("\nMemory Allocation failed\n");
			exit (EXIT_FAILURE);
		}
		memset (*(matrix+rowindex), 'O', colsize*sizeof(char));
	}

	/* Initialize the Global Stats Structure */
	p_global_stats = malloc(3*sizeof(global_stats));      /* For User:0, Computer:1 and Vacant Positions:2 */
	if (NULL==p_global_stats)
	{
		printf("\nMemory Allocation failed\n");
		exit (EXIT_FAILURE);
	}

	for (counter=0; counter<3; counter++)
	{
		p_global_stats[counter].row_stats = calloc(rowsize, sizeof(int));
		p_global_stats[counter].col_stats = calloc(colsize, sizeof(int));
	}

	/* Print the Tic-Tac-Toe Array */
	print_tic_tac_toe(matrix);

	while (num_choices)
	{
		printf ("\n\nYour Turn: \n\n");
		user_play(matrix);
		num_choices--;

		/* Print the Tic-Tac-Toe Array */
		print_tic_tac_toe(matrix);

		victory_flag = update_stats(matrix);
		/* print_stats(matrix); */
		/* Check if the User has Won */
		if (victory_flag == VICTORY)
		{
			printf ("\nCongratulations, you are a Winner!!!\n\n");
			print_tic_tac_toe(matrix);
			break;
		} 
		else if (victory_flag == DEF_DEFEAT)
		{
			printf ("\nGame Over, You are Defeated !!!\n\n");
			return 0;
		}
	
		/* Select Computer Choice */
		if (num_choices)
		{
			printf ("\n\nComputer's Turn: \n\n");
			computer_play(matrix);
			num_choices--;
			/* Print the Tic-Tac-Toe Matrix */
			print_tic_tac_toe(matrix);
		}
	}

	if (victory_flag == NO_VICTORY)
	{
		printf ("\nGame Over, You are Defeated !!!\n\n");
	}
	
	return 0;
}

void user_play (char **matrix)
{
	int user_rowno = 0;
	int user_colno = 0;

	
	/* Request for User I/P */
	printf ("\nUsage: To Select the Position: Row 1, Column 2:: Type on Terminal: 1 2 (enter)\n");
	printf ("\nSelect Your Choice: (ROWNO COLNO)\n\n");
	scanf  ("%d %d", &user_rowno, &user_colno);

	/* Validate User I/P */
	if ((*(*(matrix+user_rowno)+user_colno) != 'O'))
	{
		printf ("\nInvalid User I/P, Try Again\n");
		user_play(matrix);
	}
	else
	{
		/* Store User I/P */
		*(*(matrix+user_rowno)+user_colno) = 'X';
	}

}

void computer_play (char **matrix)
{
	int rowindex = 0;
	int colindex = 0;

	int row_minimum = 0;
	int col_minimum = 0;

	int row_min_index = 0;
	int col_min_index = 0;
	
	int destroyed_rdiagonal = NO;

	static int num_step = 1; /* To Track Steps 1 & 2 */
		

	/* Step-1: Destroy the Left Diagonal */
	if (num_step==1)
	{
		/* Find a Vacant Position on the Left Body Diagonal */
		while (*(*(matrix+rowindex)+colindex)!= 'O')
		{
			rowindex++;
			colindex = rowindex;
		}
		
		*(*(matrix+rowindex)+colindex) = 'Y';

		num_step++;
	
		reset_stats(matrix);

		return;
	}
	


	/* Further Steps: Target the Positions with Minimum No. of 'O's
	 *                provided that there is NO 'Y' in the same Column
	 */
	if (num_step>1)
	{
		/* No need to worry about Left Body Diagonal Now :) */

		/* Find out the Row which is getting Completed at the Highest Pace */
		row_minimum = rowsize;
		for (rowindex=0; rowindex<rowsize; rowindex++)
		{
			if (row_minimum > p_global_stats[2].row_stats[rowindex])
			{
				/* Update row_minimum & Note rowindex */
				if ((p_global_stats[1].row_stats[rowindex]==0)&&(p_global_stats[2].row_stats[rowindex]))
				{
					row_minimum 	= p_global_stats[2].row_stats[rowindex];
					row_min_index 	= rowindex;
				}
			}
		}

		/* Find out the Column which is getting Completed at the Highest Pace */
		col_minimum = colsize;
		for (colindex=0; colindex<colsize; colindex++)
		{
			if (col_minimum > p_global_stats[2].col_stats[colindex])
			{
				/* Update col_minimum & Note colindex */
				if ((p_global_stats[1].col_stats[colindex]==0)&&(p_global_stats[2].col_stats[colindex]))
				{
					col_minimum 	= p_global_stats[2].col_stats[colindex];
					col_min_index 	= colindex;
				}
			}
		}

		/* If Time is NOT Very Critical, I would like to Destroy the Right Diagonal */
		if ((destroyed_rdiagonal == NO) &&
			(p_global_stats[1].rdiagonal_stats==0) &&
			(row_minimum!=1)&&
			(col_minimum!=1))
		{
			/* Destroy the Right Body Diagonal */
			rowindex=0;
			colindex = rowsize-1-rowindex;

			/* Find a Vacant Position on the Right Body Diagonal */
			while (*(*(matrix+rowindex)+colindex)!= 'O')
			{
				rowindex++;
				colindex = rowsize-1-rowindex;
			}
		
			*(*(matrix+rowindex)+colindex) = 'Y';

			destroyed_rdiagonal = YES;
		}
		else
		{
			/* Destroy the Rows/Columns */
			if (col_minimum<=row_minimum)
			{
				if (col_min_index<colsize)
				{
					colindex = col_min_index;
					rowindex = 0;
					while ((rowindex<rowsize)&&(*(*(matrix+rowindex)+colindex)!= 'O'))
					{
						rowindex++;
					}
				}
			}
			else 
			{
				if (row_min_index<rowsize)
				{
					rowindex = row_min_index;
					colindex = 0;
					while ((colindex<colsize)&&(*(*(matrix+rowindex)+colindex)!= 'O'))
					{
						colindex++;
					}
				}
			}
			
			if ((rowindex<rowsize) && (colindex<colsize) && (*(*(matrix+rowindex)+colindex) == 'O'))
			{
				*(*(matrix+rowindex)+colindex) = 'Y';
			}
		}
		
		reset_stats(matrix);
	}
}

int validate_def_defeat (char **matrix)
{
	int rowindex = 0;
	int colindex = 0;

	int def_defeat_row_flag = 0;
	int def_defeat_col_flag = 0;

	int ret_val = KEEP_PLAYING;

	/* Check if the User has No Chances to Win further */
	/* No scope for Left Diagonal Completion */
	/* No scope for Right Diagonal Completion */
	if ((p_global_stats[1].ldiagonal_stats)&&(p_global_stats[1].rdiagonal_stats))
	{
		/* Every Row has atleast one 'Y' Entry */
		for (rowindex=0; rowindex<rowsize; rowindex++)
		{
			if (p_global_stats[1].row_stats[rowindex]>0)
			{
				def_defeat_row_flag = 1;
			}
			else
			{
				def_defeat_row_flag = 0;
				break;
			}
		}	
		
		/* Every Column has atleast one 'Y' Entry */
		for (colindex=0; colindex<colsize; colindex++)
		{
			if (p_global_stats[1].col_stats[colindex]>0)
			{
				def_defeat_col_flag = 1;
			}
			else
			{
				def_defeat_col_flag = 0;
				break;
			}
		}

		if (def_defeat_row_flag&&def_defeat_col_flag)
		{
			ret_val = DEF_DEFEAT;
		}
	}

	return ret_val;
}

void print_tic_tac_toe (char **matrix)
{
	int rowindex = 0;
	int colindex = 0;

	int counter = 0;

	printf ("\n");
	printf("\033[31m");
	draw_line();
	printf("   | ");
	for (counter=0; counter<rowsize; counter++)
	{
		printf("  %d ", counter);
	}
	printf(" |");

	printf ("\n");
	draw_line();
	printf("\033[39m"); 
	for (rowindex=0,counter=0; (rowindex<rowsize && counter<rowsize); rowindex++, counter++)
	{
		printf("\033[31m");
		printf(" %d | ", counter);
		printf("\033[39m"); 
		for (colindex=0; colindex<colsize; colindex++)
		{
			switch (*(*(matrix+rowindex)+colindex))
			{
				case 'O':
				{
					printf("  \033[37m%c ", *(*(matrix+rowindex)+colindex));
					break;
				}
				case 'X':
				{
					printf("  \033[34m%c ", *(*(matrix+rowindex)+colindex));
					break;
				}

				case 'Y':
				{
					printf("  \033[32m%c ", *(*(matrix+rowindex)+colindex));
					break;
				}
			}
		}
		printf("\033[39m"); 
		printf("\033[31m");
		printf (" |\n");
		printf("\033[39m"); 
	}	
	printf("\033[31m");
	draw_line();
	printf("\033[39m"); 
	printf("\n");
}	

void draw_line(void)
{
	int counter = 0;

	for (counter=0; counter<rowsize; counter++)
	{
		printf("------");
	}
	printf("\n");
}

int update_stats (char **matrix)
{
	int rowindex = 0;
	int colindex = 0;

	int ret_val = NO_VICTORY;
	

	/* ROW-STATS */
	for (rowindex=0; rowindex<rowsize; rowindex++)
	{
		for (colindex=0; colindex<colsize; colindex++)
		{
			if (*(*(matrix+rowindex)+colindex) == 'X')
			{
				p_global_stats[0].row_stats[rowindex]++;
				
				/* LEFT-DIAGONAL STATS */
				if (rowindex==colindex)
				{
					p_global_stats[0].ldiagonal_stats++;
				}
				
				/* RIGHT-DIAGONAL STATS */
				if (rowindex+colindex==(rowsize-1))
				{
					p_global_stats[0].rdiagonal_stats++;
				}
			}		/* if (*(*(matrix+rowindex)+colindex) == 'X') */
			else if (*(*(matrix+rowindex)+colindex) == 'Y')
			{
				p_global_stats[1].row_stats[rowindex]++;
				
				/* LEFT-DIAGONAL STATS */
				if (rowindex==colindex)
				{
					p_global_stats[1].ldiagonal_stats++;
				}

				/* RIGHT-DIAGONAL STATS */
				if (rowindex+colindex==(rowsize-1))
				{
					p_global_stats[1].rdiagonal_stats++;
				}
			}		/* if (*(*(matrix+rowindex)+colindex) == 'Y') */
			else if (*(*(matrix+rowindex)+colindex) == 'O')
			{
				p_global_stats[2].row_stats[rowindex]++;
				
				/* LEFT-DIAGONAL STATS */
				if (rowindex==colindex)
				{
					p_global_stats[2].ldiagonal_stats++;
				}

				/* RIGHT-DIAGONAL STATS */
				if (rowindex+colindex==(rowsize-1))
				{
					p_global_stats[2].rdiagonal_stats++;
				}
			}

			/* Check for User's Victory */
			if (p_global_stats[0].row_stats[rowindex]==rowsize)
			{
				printf ("\nRow %d is Complete !\n", rowindex);
				ret_val = VICTORY;
			}
			else if(p_global_stats[0].ldiagonal_stats==rowsize)
			{
				printf ("\nLeft Diagonal is Complete !\n");
				ret_val = VICTORY;
			}
			else if(p_global_stats[0].rdiagonal_stats==rowsize)
			{
				printf ("\nRight Diagonal is Complete !\n");
				ret_val = VICTORY;
			}

		}		/* Inner for() loop -- for colindex */
	}			/* Outer for() loop -- for rowindex */

	/* COLUMN-STATS */
	for (colindex=0; colindex<colsize; colindex++)
	{
		for (rowindex=0; rowindex<rowsize; rowindex++)
		{
			if (*(*(matrix+rowindex)+colindex) == 'X')
			{
				p_global_stats[0].col_stats[colindex]++;
			}
			else if (*(*(matrix+rowindex)+colindex) == 'Y')
			{
				p_global_stats[1].col_stats[colindex]++;
			}
			else if (*(*(matrix+rowindex)+colindex) == 'O')
			{
				p_global_stats[2].col_stats[colindex]++;
			}
		}

		/* Check for User's Victory */
		if (p_global_stats[0].col_stats[colindex]==colsize)
		{
			printf ("\nColumn %d is Complete !\n", colindex);
			ret_val = VICTORY;
		}
	}
	
	if (ret_val == NO_VICTORY)
	{
		ret_val = validate_def_defeat(matrix);
	}

	return ret_val;
}

void print_stats (char **matrix)
{
	int counter  = 0;
	int rowindex = 0;
	int colindex = 0;

	for (counter=0; counter<3; counter++)
	{
		switch (counter)
		{
			/* Player Statistics */
			case 0:
			{	
				printf ("\n#####################################################################################\n");
				printf ("\nPlayer Statistics:\n\n");
				for (rowindex=0; rowindex<rowsize; rowindex++)
				{
					printf("\nRow No. %d: count = %d\n", rowindex, p_global_stats[counter].row_stats[rowindex]);
				}
				for (colindex=0; colindex<colsize; colindex++)
				{
					printf("\nColumn No. %d: count = %d\n", colindex, p_global_stats[counter].col_stats[colindex]);
				}
				printf("\nLeft Diagonal count = %d\n",  p_global_stats[counter].ldiagonal_stats);
				printf("\nRight Diagonal count = %d\n", p_global_stats[counter].rdiagonal_stats);
				printf ("\n#####################################################################################\n");
				break;
			}
			/* Computer Statistics */
			case 1:
			{	
				printf ("\n#####################################################################################\n");
				printf ("\nComputer Statistics:\n\n");
				for (rowindex=0; rowindex<rowsize; rowindex++)
				{
					printf("\nRow No. %d: count = %d\n", rowindex, p_global_stats[counter].row_stats[rowindex]);
				}
				for (colindex=0; colindex<colsize; colindex++)
				{
					printf("\nColumn No. %d: count = %d\n", colindex, p_global_stats[counter].col_stats[colindex]);
				}
				printf("\nLeft Diagonal count = %d\n",  p_global_stats[counter].ldiagonal_stats);
				printf("\nRight Diagonal count = %d\n", p_global_stats[counter].rdiagonal_stats);
				printf ("\n#####################################################################################\n");
				break;
			}
			/* Vacant-Slot Statistics */
			case 2:
			{	
				printf ("\n#####################################################################################\n");
				printf ("\nVacant Slot Statistics:\n\n");
				for (rowindex=0; rowindex<rowsize; rowindex++)
				{
					printf("\nRow No. %d: count = %d\n", rowindex, p_global_stats[counter].row_stats[rowindex]);
				}
				for (colindex=0; colindex<colsize; colindex++)
				{
					printf("\nColumn No. %d: count = %d\n", colindex, p_global_stats[counter].col_stats[colindex]);
				}
				printf("\nLeft Diagonal count = %d\n",  p_global_stats[counter].ldiagonal_stats);
				printf("\nRight Diagonal count = %d\n", p_global_stats[counter].rdiagonal_stats);
				printf ("\n#####################################################################################\n");
				break;
			}
		}
	}
}

void reset_stats (char **array)
{
	int counter = 0;

	for (counter=0; counter<3; counter++)
	{
		memset (p_global_stats[counter].row_stats, 0, rowsize*sizeof(int));
		memset (p_global_stats[counter].col_stats, 0, colsize*sizeof(int));
		p_global_stats[counter].ldiagonal_stats = 0;
		p_global_stats[counter].rdiagonal_stats = 0;
	}
}
	
