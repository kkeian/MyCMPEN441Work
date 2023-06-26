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
*  Assignment : M5 Lab
*/

// Include shared resources
#include "shared.h"

// Need below 2 headers for changing size of shared mem
#include <unistd.h>
#include <sys/types.h>


int main(void) { // We don't want to accept any input to our cmdline program

    int shrd_fd; // To hold shared memory file descriptor
    int res_t; // Holds the result of functions execution (success or failure)
    
    // Name of the shared memory object should be SHRD_MEM_NAME
    // Using O_CREAT - create obj if doesn't already exist
    // Using O_RDWR - allow reading and writing to created fd
    // File permissions are 3rd arg: 744; i.e. user - rwx, grp - r, oth - r
    shrd_fd = shm_open(SHRD_MEM_NAME, O_CREAT | O_RDWR, S_IRWXU | S_IRGRP | S_IROTH);
    
    // This changes size of shared memory
    // First arg is fd created by shm_open
    // Second arg is length of shared memory in bytes - 100 bytes
    // Since in ASCII, each character is encoded as 1 byte, this corresponds
    // to 100 characters we can input at once.
    res_t = ftruncate(shrd_fd, SHRD_MEM_SIZE);
    
    // Check if we changed size of shared memory correctly
    if (res_t == -1) {
        perror("Failed to change size of shared memory. Exiting program.");
        exit(EXIT_FAILURE);
    }
    
    // Now map shared memory fd to memory of process virtual memory
    void *loc_shrd_mem; // to hold location of memory mapped shared memory
    // Arg 1: NULL for address to map memory to
    // Arg 2: size of memory to map (entire length of shared mem)
    // Arg 3: allow reading from mapped shared memory
    // Arg 4: ensure changes to memory are immediately visible to all processes
    //        sharing this memory
    // Arg 5: shared memory fd received from shm_open
    // Arg 6: 0 because we want to start mem mapping at beginning of shared mem
    loc_shrd_mem = mmap(NULL, SHRD_MEM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shrd_fd, 0);
    
    // Check that we mapped memory successfully
    if (*(int *)loc_shrd_mem == -1) {
        perror("Was not able to map memory to process virtual memory space.");
        exit(EXIT_FAILURE);
    }
    
    // Allocate memory to store input to
    // should be 100 characters long to correspond to our shared memory size
    char *input = (char *)malloc(SHRD_MEM_SIZE);
    
    // User enters content to place in shared memory
    while ((strcmp(input, "end\n")) != 0) { // If user didn't enter "end", continue
        // Write last input, which has been checked, to shared memory
        // sprintf doesn't include '\0' when writing to stream
        sprintf(loc_shrd_mem, "%s", input);
        // Move pointer in memory mapped shared memory, to next free location
        loc_shrd_mem += strlen(input);
    
        // Prompt for input
        printf("enter line to be added to the Shared memory location (enter 'end' to stop): ");
        // Get user input, fgets grabs entire line, including the '\n' or up to
        // SHRD_MEM_SIZE characters
        fgets(input, SHRD_MEM_SIZE, stdin);
    }
    
    // Free dynamically allocated memory for input before exiting program
    free(input);
    exit(EXIT_SUCCESS);
}