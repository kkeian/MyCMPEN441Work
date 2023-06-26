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

// Include the shared headers and constants
#include "shared.h"

int main(void) { // Accept no input to this cmdline program
    
    int shrd_fd; // To hold fd returned from shm_open for shared memory
    
    // Name of the shared memory object should be SHRD_MEM_NAME
    // Using O_RDONLY - to only allow reading from shared memory location
    // File permissions are: 444; i.e. user - r, grp - r, oth - r
    shrd_fd = shm_open(SHRD_MEM_NAME, O_RDONLY, S_IRUSR | S_IRGRP | S_IROTH);
    
    // Check that shared memory was able to be allocated successfully
    if (shrd_fd == -1) {
        perror("Unable to allocate shared memory for reading.");
        exit(EXIT_FAILURE);
    }
    
    // For holding memory mapped to shared memory
    void *loc_shrd_mem;
    // Arg 1: NULL for address to map memory to
    // Arg 2: size of memory to map (entire length of shared mem)
    // Arg 3: allow reading from mapped shared memory
    // Arg 4: ensure changes to memory are immediately visible to all processes
    //        sharing this memory
    // Arg 5: shared memory fd received from shm_open
    // Arg 6: 0 because we want to start mem mapping at beginning of shared mem
    loc_shrd_mem = mmap(NULL, SHRD_MEM_SIZE, PROT_READ, MAP_SHARED, shrd_fd, 0);
    
    // Check we were able to map memory successfully
    if (*(int *)loc_shrd_mem == -1) {
        perror("Unable to map shared memory to virtual memory of process.");
        exit(EXIT_FAILURE);
    }
    
    // Read from shared memory
    printf("%s", (char *)loc_shrd_mem);
    
    // "Mark shared memory for deallocation by OS"
    if (shm_unlink(SHRD_MEM_NAME) == -1) {
        perror("Problem in unlinking shared memory.");
        exit(EXIT_FAILURE);
    }
    
    exit(EXIT_SUCCESS);
}