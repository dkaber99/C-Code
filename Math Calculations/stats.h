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
 * @file <stats.h> 
 * @brief <Header file that holds functions for stats >
 * @author <Dylan Kaber>
 * @date <7/15/2024 >
 *
 */
#ifndef __STATS_H__
#define __STATS_H__

/* Add Your Declarations and Function Comments here */ 


unsigned char find_min(unsigned char data[], const int arr_size){
unsigned char minimum  = data[0];//Pick first value to ensure accuracy
	for(int i = 0; i < arr_size; i++){ //Check every single location
		if(minimum > data[i]){ //Finds minimum by updating the minimum variable if larger than the current element being checked
		minimum = data[i];
		}
	}
	
	return minimum;	
}
unsigned char find_max(unsigned char data[], const int arr_size){
int maximum  = 0;
	for(int i = 0; i < arr_size; i++){
		if(maximum < data[i]){
		maximum = data[i]; //Finds maximum by updating the maximum variable if smaller than the current element being checked
		}
	}
	return (unsigned char)maximum;	
}
unsigned char find_mean(unsigned char data[], const int arr_size){ //Adds up every element in the array and divides by size to find mean
        int sum = 0;
	for(int i = 0; i < arr_size; i++){
	sum = sum + data[i];
	}
	int average = sum / arr_size;

	return (unsigned char)average;	
}
void print_stats(unsigned char median, unsigned char average, unsigned char minimum, unsigned char maximum){ //import every data point calculated outside and print
 	printf("The Mean Is %d\n", average);
	printf("The Max Is %d\n", maximum);
	printf("The Min Is %d\n", minimum);	
	printf("The Median Is %d\n", median);

}
void print_array(unsigned char data[], const int arr_size){
	printf("Array = [ " );
for(int i =0;i<arr_size;i++){ //increments through every element in the array and prints it
	printf("%d ", data[i]);
}
	printf("]");
}
void sort_array(unsigned char data[], const int arr_size){ //Uses two arrays, one for the current position being checked, the other for when checking others for a higher number. If higher, the numbers are swapped so in the end the array is highest to lowest
	for(int i=0;i < arr_size;i++){

	for(int j=i; j<arr_size;j++){
	if(i == j){
	//skips current location to avoid checking itself
	}
	else{
	if(data[i] < data[j]){
	unsigned char temp;
	temp = data[i]; //Store one value in temp var so values can be copied directly. One element overrides the other, then the location copied from is overriden with the temp
	data[i] = data[j];
	data[j] = temp;
	}
	}

		}
}
		printf("\n Array Sorted = [ " );
for(int i =0;i<arr_size;i++){
	printf("%d ", data[i]);
}
	printf("]");
	
}
unsigned char find_median(unsigned char data[], const int arr_size){ 
	for(int i=0;i < arr_size;i++){

	for(int j=i; j<arr_size;j++){
	if(i == j){
	//skips current location 
	}
	else{
	if(data[i] < data[j]){ //Sorts array first from highest to lowest
	unsigned char temp;
	temp = data[i];
	data[i] = data[j];
	data[j] = temp;
	}
	}

		}
}

if(arr_size % 2 == 1){ //if odd
return data[arr_size/2];

}

else{
unsigned char leftmedian = data[(arr_size/2 -1)];
unsigned char rightmedian = data[arr_size/2];
return ((leftmedian + rightmedian) / 2);
}
	
}




#endif /* __STATS_H__ */
