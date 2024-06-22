//parses the input file into Process and event
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void update_state(char arr[][20], int arr_size, char* element, char* new_state);

int main()
{
	int i;
	char* rch;
	char str[200];
	char LineInFile[40][300];
	int lineP, lineQ;
	char* sch;
	char tokenizedLine[10][10];
	

	FILE* fp1;
	FILE* fp2;
	fp1 = fopen("inp1.txt", "r");			//open the original input file
	fp2 = fopen("inp1_parsed.txt", "w");	//output the Process ID and event to another file. 
											//You can store in variables instead of printing to file
	lineP = 0;
	i = 0;

	//Initialize process_state_array using first line in file
	char process_state_array[20][20];
	int process_state_arr_end_index = 0;

	char printer_array[20][3];
	int printer_end_index = 0;
	char keyboard_array[20][3];
	int keyboard_end_index = 0;
	char disk_array[20][3];
	int disk_end_index = 0;

	char* token;


	if (fgets(str, sizeof(str), fp1) != NULL) {
		token = strtok(str, " ");					// use strtok to break up the line by " " This would separate each line into the different processes
		while (token != NULL) {
			strcpy(process_state_array[process_state_arr_end_index], token);			//copy the events into an array of strings
			process_state_arr_end_index++;								//keep track of how many elements are in array
			token = strtok(NULL, " ");				//needed for strtok to continue in the while loop
		} 
		process_state_arr_end_index -=1;	//"Remove" string "end" from array
	}

	//Print First line to terminal
	for(i = 0; i < process_state_arr_end_index; i++){
		printf("%s ", process_state_array[i]);
	}
	printf("\n");
	
	//parse each remaining line into Process event
	//while loop with fgets reads each line
	while (fgets(str, sizeof(str), fp1) != NULL)
	{
		printf("%s", str);
		lineP = 0;
		rch = strtok(str, ":;.");					// use strtok to break up the line by : or . or ; This would separate each line into the different events
		while (rch != NULL)
		{
			strcpy(LineInFile[lineP], rch);			//copy the events into an array of strings
			lineP++;								//keep track of how many events are in that line
			rch = strtok(NULL, ":;.");				//needed for strtok to continue in the while loop
		} 

		//for each event (e.g. Time slice for P7 expires) pull out process number and event
		for (i = 1; i < lineP - 1; i++)
		{
			lineQ = 0;
			sch = strtok(LineInFile[i], " ");
			while (sch != NULL)
			{
				strcpy(tokenizedLine[lineQ], sch);		//use strtok to break up each line into separate words and put the words in the array of strings
				lineQ++;								//count number of valid elements
				sch = strtok(NULL, " ");
			}

			//tokenizedLine has the event separated by spaces (e.g. Time slice for P7 expires)
			if (strcmp(tokenizedLine[1], "requests") == 0)						//Process requests an I/O device
			{
				//Process Becomes blocked
				update_state(process_state_array, process_state_arr_end_index, tokenizedLine[0], "Blocked");
				
				//Process added to IO Queue
				if (strcmp(tokenizedLine[3], "disk") == 0){
					strcpy(disk_array[disk_end_index], tokenizedLine[0]);
					disk_end_index += 1;
				}
				else if (strcmp(tokenizedLine[3], "keyboard") == 0){
					strcpy(keyboard_array[keyboard_end_index], tokenizedLine[0]);
					keyboard_end_index += 1;
				}
				else if (strcmp(tokenizedLine[3], "printer") == 0){
					strcpy(printer_array[printer_end_index], tokenizedLine[0]);
					printer_end_index += 1;
				}
				fprintf(fp2, "%s %s %s ", tokenizedLine[0], tokenizedLine[1], tokenizedLine[3]);
			}
			else if ((strcmp(tokenizedLine[2], "dispatched") == 0))				//Process is dispatched
			{
				//Process becomes Running
				update_state(process_state_array, process_state_arr_end_index, tokenizedLine[0], "Running");
				fprintf(fp2, "%s %s ", tokenizedLine[0], tokenizedLine[2]);
			}
			else if (strcmp(tokenizedLine[0], "Time") == 0)						//Process has timed off
			{
				//Process becomes Ready
				update_state(process_state_array, process_state_arr_end_index, tokenizedLine[3], "Ready");
				fprintf(fp2, "%s %s ", tokenizedLine[3], tokenizedLine[4]);
			}
			else if (strcmp(tokenizedLine[3], "out") == 0)						//Process is swapped out
			{
				//Process becomes suspended
				update_state(process_state_array, process_state_arr_end_index, tokenizedLine[0], "Suspend");
				fprintf(fp2, "%s %s ", tokenizedLine[0], tokenizedLine[3]);
			}
			else if (strcmp(tokenizedLine[3], "in") == 0)						//Process is swapped in
			{
				//Process becomes available
				update_state(process_state_array, process_state_arr_end_index, tokenizedLine[0], "Available");
				fprintf(fp2, "%s %s ", tokenizedLine[0], tokenizedLine[3]);
			}
			else if (strcmp(tokenizedLine[1], "interrupt") == 0)				//An interrupt has occured
			{
				//Process becomes ready
				update_state(process_state_array, process_state_arr_end_index, tokenizedLine[4], "Interrupt");
				
				//Process removed from I/O queue
				for (i = 0; i < disk_end_index; i++){
					if(strcmp(disk_array[i], tokenizedLine[4]) == 0){
						for (int j = i; j < disk_end_index -1; j++){
							strcpy(disk_array[j], disk_array[j+1]);
						}  
						disk_end_index--;
						break;
					}
				}
				for (i = 0; i < printer_end_index; i++){
					if(strcmp(printer_array[i], tokenizedLine[4]) == 0){
						for (int j = i; j < printer_end_index -1; j++){
							strcpy(printer_array[j], printer_array[j+1]);
						}  
						printer_end_index--;
						break;
					}
				}
				for (i = 0; i < keyboard_end_index; i++){
					if(strcmp(keyboard_array[i], tokenizedLine[4]) == 0){
						for (int j = i; j < keyboard_end_index -1; j++){
							strcpy(keyboard_array[j], keyboard_array[j+1]);
						}
						keyboard_end_index--;
						break;
					}
				}

				printf("Test");
				fprintf(fp2, "%s %s ", tokenizedLine[4], tokenizedLine[1]);
			}
			else																//Process has been terminated
			{
				//Process state terminated
				update_state(process_state_array, process_state_arr_end_index, tokenizedLine[0], "Terminated");
				fprintf(fp2, "%s %s ", tokenizedLine[0], tokenizedLine[2]);
			}
			
		}

		//Print Arrays
		for(i = 0; i < process_state_arr_end_index; i++){
			printf("%s ", process_state_array[i]);
		}
		printf("\n");
		printf("Printer(%d): ", printer_end_index);
		for(i = 0; i < printer_end_index; i++){
			printf("%s ", printer_array[i]);
		}
		printf("\n");
		printf("Keyboard(%d): ", keyboard_end_index);
		for(i = 0; i < keyboard_end_index; i++){
			printf("%s ", keyboard_array[i]);
		}
		printf("\n");
		printf("Disk(%d): ", disk_end_index);
		for(i = 0; i < disk_end_index; i++){
			printf("%s ", disk_array[i]);
		}
		printf("\n\n");
		fprintf(fp2, "\n");
	}

	fclose(fp1);
	fclose(fp2);

	return 0;
}

void update_state(char arr[][20], int arr_size, char* element, char* new_state) {
	for(int i = 0; i < arr_size; i = i + 2){
		if(strcmp(arr[i], element) == 0){
			//Check if state is Suspended
			if (strcmp(new_state, "Suspend") == 0){
				if (strcmp(arr[i + 1], "Ready") == 0){
					strcpy(arr[i + 1], "Ready Suspend");
				}
				else if (strcmp(arr[i + 1], "Blocked") == 0){
					strcpy(arr[i + 1], "Blocked Suspend");
				}
			}
			else if (strcmp(new_state, "Available") == 0){
				if (strcmp(arr[i + 1], "Ready Suspend") == 0){
					strcpy(arr[i + 1], "Ready");
				}
				else if (strcmp(arr[i + 1], "Blocked Suspend") == 0){
					strcpy(arr[i + 1], "Blocked");
				}
			}
			else if (strcmp(new_state, "Interrupt") == 0){
				if (strcmp(arr[i + 1], "Blocked Suspend") == 0){
					strcpy(arr[i + 1], "Ready Suspend");
				}
			}
			else{
				strcpy(arr[i + 1], new_state);
			}
			return;
		}
	}
}