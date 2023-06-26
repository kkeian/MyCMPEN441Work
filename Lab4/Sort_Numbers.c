/*
*  PLAGIARISM STATEMENT
*    I certify that this assignment/report is my own work, based on my personal
*    study and/or research and that I have acknowledged all material and sources
*    used in its preparation, whether they be books, articles, reports, lecture notes, online sources
*    and any other kind of document, electronic or personal communication. I also
*    certify that this assignment/report has not previously been submitted for
*    assessment in any other unit, except where specific permission has been granted
*    from all unit coordinators involved, or at any other time in this unit, and that I
*    have not copied in part or whole or otherwise plagiarised the work of other
*    students and/or persons.
*
*  Name       : Keian Kaserman 
*  PSU Email  : knk5281@psu.edu
*  Assignment : Lab 4
*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

// Function prototype for compiler to know this exists for sorting numbers
void *sortNums(void *);

int main(void) { // We don't accept arguments to this command program
    // This is the main thread
    
    int cont = 0; // Default value to keep taking in input
    int result_t; // To hold result of thread creation and joining
    int scanres; // hold result of scan of input
    
    while (cont == 0) { // Determine if we should continue reading input.
                            // 1 means stop program
                            // 0 means continue
        // Store 5 numbers here
        int input[5]; 
        
        // Prompt user to enter 5 numbers
        printf("Enter 5 numbers : ");
        for (int i = 0; i < 5; i++) {
            scanres = scanf("%i", &input[i]);
        
            if (scanres == EOF) {
                perror("Read error or input not integers");
                return EXIT_FAILURE; // Exit prematurely to avoid freeing unallocated memory
            }
        }
        
        // Create thread to sort input.
        pthread_t Sort_Display;
        result_t = pthread_create(&Sort_Display, NULL, sortNums, input);
        
        // Ensure thread successfully created
        if (result_t != 0) {
            perror("Sorting thread create failure");
        }
        
        // Wait for Sort and Display thread to finish
        result_t = pthread_join(Sort_Display, NULL);
        
        // Ensure we successfully waited for thread to finish sorting and
        // printing sorted output
        if (result_t != 0) {
            perror("Thread join failed");
        }
        
        // Ask if we should continue
        printf("Would you like to continue ? Enter (0) Yes, Enter (1) No : ");
        scanres = scanf("%i", &cont);
        if (scanres == EOF) {
            perror("Read error or input not integer. Exiting program");
            cont = 1; // Set continue value to exit program
        }
    }
    
    return EXIT_SUCCESS; // Successful execution
}

// Function to compare numbers using qsort
// return of < 0 means num1 < num2
// return of 0 means num1 == num 2
// return of > 0 means num1 > num2
int cmpnum(const void *num1, const void *num2) {
    return (*(int *)num1 - *(int *)num2);
    // (int *) explicit cast of arguments to integer pointer
    // *() dereferences pointer to get at casted value
    // Subtracts both casted values and returns result
}

// Function for thread to run for sorting numbers.
void *sortNums(void *args) {
    // void *args is an array of integers of length 5
    // Need to explicitly cast input args to int array
    int *sorted;
    sorted = (int (*))args; // to hold 5 integers sorted in ascending order
    
    // Use qsort from stdlib to sort input
    // Args:
    // 1: start of array to sort
    // 2: size of array to sort
    // 3: size of each element in array in bytes
    // 4: comparison function to compare elements
    // Note: sorts in-place
    qsort(&sorted[0], 5, sizeof(int), cmpnum);
    
    // Print sorted input
    printf("Sort Array: ");
    for (int i = 0; i < 5; i++) {
        printf("%i, ", sorted[i]);
    }
    printf("\n"); // Ensure newline printed after list of sorted numbers
    
    return 0; // Successfully sorted input and printed it
}