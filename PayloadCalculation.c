//I attest to the originality of my work
#include <stdio.h> //input & output functions
#include <string.h> //string functions
#include <stdlib.h>  //standard library

int main () { //takes input from a file and analyzes, sorts and outputs a data sheet including the ore value
    int payloads = 0; //base payloads,
    int size = 3; //columns
    int lineCounter = 0; //stores the number of lines
    int swapMade; //variable stores swaps made value
    float goldUnitPrice = 8500; //set price of gold in $ per kg
    float temp; //temporary variable used in bubble sort
    char character; //character used to iterate through data and determine lines
    FILE *fp1;

    fp1 = fopen("payloads.txt", "r"); //opens file containing data, read only (for line counting process)
    if(fp1 == NULL){ //if file cannot be opened print below
        printf("File not found.\n");
    } else {
        character = (char) getc(fp1); //deals with first character because the initial line is irrelevant
        while (character != EOF) { //runs as long as more characters exist in the data file
            if (character == '\n') { //if new line character discovered
                lineCounter++; //increase the line count by one
            }
            character = (char) getc(fp1); //go to the next character
        }
    }
    fclose(fp1); //closes the data sheet and frees up dynamic memory

    fp1 = fopen("payloads.txt", "r"); //opens file containing data, read only, reopens file to start iterating at the beginning, file has already been checked to see if it can be opened
    fscanf(fp1, "%d", &payloads); //scans the first value in the data sheet which is an integer constant representing number of payloads
    if(payloads == 0) { //if payloads is 0 then print the following
        printf("No payloads in file.");
    }
    float **pointerToData = (float**) malloc(size*sizeof(float*)); //creation of the pointer 2D float array using dynamic memory
        if(pointerToData == NULL) { //if memory could not be allocated print the following
            printf("Memory could not be allocated.\n");
        } else {
            for (int i = 0; i < size; i++) { //else assign the memory for each of the columns within the 2D pointer array of floats
                pointerToData[i] = (float*) malloc(lineCounter*sizeof(float));
                if (pointerToData[i] == NULL) { //if memory could not be allocated print the following
                    printf("Memory could not be allocated.\n");
                }
            }
        }
    int i = 0;
        do { //scans the data sheet for floats
            fscanf(fp1, "%f %f", &pointerToData[0][i], &pointerToData[1][i]);
            pointerToData[2][i] = pointerToData[0][i] * pointerToData[1][i] * goldUnitPrice; //proceeds to calculate the ore value with provided equations
            i++; //allows iteration until stop condition is met
        } while  (pointerToData[0][i-1] != 0 && pointerToData[1][i-1] != 0); //stop condition states that once a value of 0 is discovered the loop will break
   fclose(fp1); //closes the data sheet and frees up dynamic memory

    while(1) { //while loop that preforms the bubble sort of the ore value data and its adjacent values
        swapMade = 0;
        for (int j = 0; j < lineCounter; j++) { //compares each ore value to the following ore value and switches their positions if the value is lower
            if (pointerToData[2][j] < pointerToData[2][j + 1]) {
                for(int k = 0; k < 3; k++) {
                    temp = pointerToData[k][j];
                    pointerToData[k][j] = pointerToData[k][j + 1];
                    pointerToData[k][j + 1] = temp;
                    swapMade = 1;
                }
            }
        }
        if (!swapMade) { //if no more swaps available the while loop will end, this sort leaves the largest value at the lowest index
            break;
        }
    }
    FILE *fp2;
    fp2 = fopen("ores.txt", "w+"); //creates a file where writing and reading is possible to store the sorted values
    fprintf(fp2, "Sorted Payload Data:\nTotal Mass / Grade / Ore Value\n"); //print to the file the headers for the columns
    printf("Sorted Payload Data:\nTotal Mass / Grade / Ore Value\n"); //print to the file the headers for the columns
        for(int l = 0; l < lineCounter; l++) {
            fprintf(fp2,"   %.f      %.2f    $%.f\n", pointerToData[0][l], pointerToData[1][l], pointerToData[2][l]); //loops through the lines and prints the data
            printf("   %.f      %.2f    $%.f\n", pointerToData[0][l], pointerToData[1][l], pointerToData[2][l]); //loops through the lines and prints the data
        }
       free(pointerToData); //closes the 2D pointer array of floats
       fclose(fp2); //closes the document where the new data has been printed
}