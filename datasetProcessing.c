/*
	Program:	Dataset processing
	Author:		Veli Aytug Ozcan
	Date: 		19/05/2022
*/

#include <stdio.h>
#include <string.h>
#include <math.h>

int main(){
	FILE *fRead, *fWrite;
	fRead = fopen("sampleDataset.txt", "r");						// The file opens in read mode.
	fWrite = fopen("sampleDataset2.txt", "w+");						// The file opens in write mode.
	if((fRead == NULL) && (fWrite == NULL)){
		printf("File not found!"); 									// If the file is not found, the file not found will be written.
	}
	else{															// If the file is found, the process will continue.
		char lineHold[200], *array[11], *data, *category[1];		// Variables and arrays are defined.
		double avg[] = {230.12, 224.36, 40.02, 215.04, 12.73, 1.29, 0.70, 0.24, 0.11}; // Average array is defined.
		double dist[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};				// Distance array is defined.
		double total = 0.0;											// The total variable is defined.
		fscanf(fRead, "%s", lineHold);								// The first line in the file has been read.
		fprintf(fWrite, "%s,category", lineHold);					// The first line in the file was written to the output file.
		printf("%s,category", lineHold);							// The first line is written to the screen.
		
		while(!feof(fRead)){										// If the end of the file is not reached, continue the process.
			printf("\n");											// Skip the next line
			fprintf(fWrite, "\n");									// Skip the next line
			fscanf(fRead, "%s", lineHold);							// The lines began to be read in order.
			data = strtok(lineHold, ",");							// The comma-separated word is put into the data variable.
			
			int i = 0;												// The variable i is defined.
			while (data != NULL){									// If the data is not empty, continue processing.
		        array[i] = data;									// The value in the data variable is passed to the index of the array.
		        data = strtok(NULL, ",");
		        fprintf(fWrite, "%s,", array[i]);					// Print the index of the array to the output file.
		        printf("%s,", array[i]);							// Print the index of the array to the screen.
		        i++;												// Increase the index by one.
		    }
		    
		    int j;													// The variable j is defined.
			for (j = 0; j < 9; j++){								// Cycles 0 to 9 will run.
				dist[j] = atoi(array[j+2]) - avg[j];				// The value in the average index was subtracted from the value in the array index and put into the distance index.
				dist[j] = pow(dist[j],2);							// The value in the distance index was squared and put back into the distance index.
				total += dist[j];									// The value in the distance index has been thrown into the total variable.
			}
			total = sqrt(total);									// The square root of the value in the total variable was taken and put back into the total variable.
			
			if (total > 592){										// If the total is greater than 592, do the operation.
				if (strcmp(array[1], "video") == 0 || strcmp(array[1],"photo") == 0){
					category[0] = "very_interesting.";				//If the status type is video or photo, add the value very interesting to the category array.
				}
				else if (strcmp(array[1], "link") == 0 || strcmp(array[1],"status") == 0){
					category[0] = "interesting.";					//If the status type is link or status, add the value interesting to the category array.
				}
			}
			else{													// If the total is smaller than 593, do the operation.
				if (strcmp(array[1], "video") == 0 || strcmp(array[1],"photo") == 0){
					category[0] = "ordinary.";						//If the status type is video or photo, add the value ordinary to the category array.
				}
				else if (strcmp(array[1], "link") == 0 || strcmp(array[1],"status") == 0){
					category[0] = "boring.";						//If the status type is link or status, add the boring to the category array.
				}
			}
			
			fprintf(fWrite, "%s", category[0]);						// Print the value in Category to output file.
		    printf("%s", category[0]);								// Print the value in Category to the screen.
		}
		
		fclose(fRead);												// The read file has been closed.
		fclose(fWrite);												// The write file has been closed.
		fRead = fopen("sampleDataset2.txt", "r");					// The read file has been opened.
		fWrite = fopen("sampleDataset.txt", "w+");					// The write file has been opened.
		
		while(!feof(fRead)){										// If the end of the file is not reached, continue the process.
			fscanf(fRead, "%s", lineHold);							// The lines began to be read in order.
			fprintf(fWrite, "%s", lineHold);						// The lines read in order are written to the output file.
			if(!feof(fRead)){
				fprintf(fWrite, "\n");								// If the end of the file is not reached, skip the next line
			}
		}
		
		fclose(fRead);												// The read file has been closed.
		fclose(fWrite);												// The write file has been closed.
		remove("sampleDataset2.txt");								// Delete the output file.
	}
	return 0;														// The program is finished.
}
