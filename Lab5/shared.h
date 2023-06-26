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

#ifndef SHARED_H
#define SHARED_H

// Below 3 required for shm_open shared memory usage
#include <sys/mman.h> // For using mmap to map shared memory to process virt mem
#include <sys/stat.h> // particularly to allow file "mode" specifying in shm_open
#include <fcntl.h> // For specifying what mode shared memory should be opened in
// Below needed to parse input string
#include <string.h>
// Below needed to allow I/O
#include <stdio.h>
// To allow access to EXIT_ values
#include <stdlib.h>


// Size of shared memory, in bytes, to allocate
#define SHRD_MEM_SIZE 100
// Name of shared memory
#define SHRD_MEM_NAME "OS"

#endif

// Above makes sure this is not double included
// Idea came from reading example source files in The Linux Programming Interface
// by Michael Kerrisk pg 51