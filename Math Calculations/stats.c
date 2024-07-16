/******************************************************************************
 * Copyright (C) 2017 by Alex Fosdick - University of Colorado
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are 
 * permitted to modify this and use it to learn about the field of embedded
 * software. Alex Fosdick and the University of Colorado are not liable for any
 * misuse of this material. 
 *
 *****************************************************************************/
/**
 * @file <stats.c> 
 * @brief <File used to sort number data by various factors including max-min>
 *
 * @author <Dylan Kaber>
 * @date <7/15/24 >
 *
 */



#include <stdio.h>
#include "stats.h"

/* Size of the Data Set */
#define SIZE (40)
unsigned char average = '1';
unsigned char max = '0';
unsigned char min = '0';
unsigned char median = '0';
void main() {

  unsigned char test[SIZE] = { 34, 201, 190, 154,   8, 194,   2,   6,
                              114, 88,   45,  76, 123,  87,  25,  23,
                              200, 122, 150, 90,   92,  87, 177, 244,
                              201,   6,  12,  60,   8,   2,   5,  67,
                                7,  87, 250, 230,  99,   3, 100,  90};

  /* Other Variable Declarations Go Here */
  /* Statistics and Printing Functions Go Here */




average = find_mean(test, SIZE);
max = find_max(test, SIZE);
min = find_min(test, SIZE);
//median = find_median(test, SIZE);
print_stats(median, average, min, max);
print_array(test, SIZE);
sort_array(test, SIZE);
printf("The Median Is %d assuming a descending sort\n", median);


}

/* Add other Implementation File Code Here */
