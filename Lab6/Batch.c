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
*  Assignment : Lab 6
*/


#include <stdio.h>
#include <stdlib.h>
#include "shared.c"

// Create Job type
typedef struct Job {
	int Process_ID; // Of process in Job
	int Time; // Needed from CPU for job to execute
	// Idea for below line from example code here:
	// https://www.tutorialspoint.com/data_structures_algorithms/linked_list_program_in_c.htm
	Job *next; // pointer to next Job
} Job;

// Thread routines
void *FCFS(void *);
void *SJF(void *);

int main(void){
	
	// Create 2 thread objects for handling each algorithm
	pthread_t FCFS_Thread, SJF_Thread;
	// linked list to hold jobs
	Job *jobs = NULL; // initially empty
	// Idea for below line from:
	// https://www.tutorialspoint.com/data_structures_algorithms/linked_list_program_in_c.htm
	Job *firstJob = jobs; // keep track of first job for knowing where to start
						  // processing
	
	int tmp_id = 0; // pid of process to store in job
	int tmp_time = 0; // time to process
	
	// Get jobs from user until '-1 -1' entered
	while (tmp_id != -1 && tmp_time != -1) {
		// Get input of jobs from user
		printf("Enter an ID and a value for a node to add to the list, Enter -1 -1 to stop: ");
		scanf("%i ", &tmp_id); // get pid
		scanf("%i", &tmp_time); // get time
		
		// Allocate space for Job
		jobs = malloc(sizeof(Job));
		
		// Store entered info into created job
		jobs.Process_ID = tmp_id;
		jobs.Time = tmp_time;
		
		// Make jobs point to next job in list
		jobs = job.next;
	}
	
	// Run threads with jobs
	// Start FCFS thread
	// 1: thread to start
	// 2: attributes = default
	// 3: FCFS routine
	// 4: NULL args to FCFS routine
	pthread_create(&FCFS_Thread, NULL, &FCFS, NULL);
	
	// Start SJF thread
	// 1: thread to start
	// 2: attributes = default
	// 3: SJF routine
	// 4: NULL args to SJF routine
	pthread_create(&SJF_Thread, NULL, &SJF, NULL);
	
	// Wait for FCFS to finish
	pthread_join(FCFS_Thread, NULL);
	
	// Wait for SJF to finish
	pthread_join(SJF_Thread, NULL);
	
	// Indicate all threads are done before exiting
	printf("All Threads completed\n");

	// Successfully executed
	return EXIT_SUCCESS;
}

// FCFS algorithm
void *FCFS(void *) {
	// Boiler plate prints
	printf ("FCFS Job order:\n");
	printf("FCFS Jobs will be executed in the order they arrived:\n");
	printf("Linked List Contain the following values :\n");
	Job *curr = firstJob; // to keep track of current point in list
	while (curr.next != NULL) { // Go through list until end of list found
		// Print current node id and value
		printf("Node ID %i with value %i\n", curr.Process_ID, curr.Time);
	}
	// indicate we're done with FCFS
	printf("FCFS Done\n");
}

// To protect against changing original list
void copyLinkedList(Job *orig, Job *newl) {
	// orig = original list
	// newl = new linked list
	// Set newl to point to start of list using startNewl, at end of procedure
	Job *startNewl = malloc(sizeof(Job)); // allocate space for first Job
	// Store first job attributes
	startNewl.Process_ID = orig.Process_ID;
	startNewl.Time = orig.Time;
	// Move pointer to next element in original list
	orig = orig.next;
	// Set newl to point to next open space
	// startNewl still points to head of list
	newl = startNewl.next;
	// Copy all remaining original list items
	while(orig.next != NULL) {
		// allocate space for next list item
		newl = malloc(sizeof(Job));
		// Copy orig list attributes into new list
		newl.Process_ID = orig.Process_ID;
		newl.Time = orig.Time;
		orig = orig.next; // Move pointer to next Job in original list
		newl = newl.next; // Move pointer to next Job in new list
	}
	// Reset pointer to newl to head of list
	newl = startNewl;
	// Since we pass pointer to newl it will be filled, no need to return it
}

void deallocateList(Job *list) {
	Job *currItem = list; // point to original list locally
	Job *nextItem = list.next; // set next item to second Job before we delete first
								// Job from memory
	while (nextItem != NULL) {
		free(currItem); // Delete job from memory
		currItem = nextItem; // Move pointer to next Job to free
		nextItem = currItem.next; // Set next item to next Job before we delete
			// this one on the next run through loop
	}
	free(currItem); // To correct off by 1 error that will happen
		// because we're checking the next item value before performing free
		// so last element in linked list will be skipped by while condition
}

// SJF algorithm
void *SJF(void *) {
	// Boilerplate
	printf("SJF Jobs Order:\n");
	// To hold sorted jobs
	Job *jobListCopy;
	// Create a copy of the original Jobs list inside sortedJobs
	copyLinkedList(firstJob, jobListCopy);
	
	// Only need to create space one time for these because
	// we'll reuse the space here inside while loop
	Job *currJob = malloc(sizeof(Job));
	Job *nextJob = malloc(sizeof(Job));
	Job *prevJob = malloc(sizeof(Job));
	
	// Initial values of above vars: head of list copy
	currJob = jobListCopy;
	nextJob = jobListCopy;
	prevJob = jobListCopy;
	
	// Output shortest jobs in ascending .Time order
	while(jobListCopy.next != NULL) { // num Jobs > 1
		
	}
	
	
	// Sort list of jobs
	Job *sortedJobs; // to hold sorted list of jobs
	
	// Store head of toSort
	Job *headToSort = toSort;
	while(toSort != NULL) { // this loop keeps track of original list
								// to see if we've evaluated all jobs
		// Store shortest job, previous job, and current job
		// Allocate new space for them each time we check for next job to store
		//  in sorted list so we don't overwrite originals
		Job *shortestJob = malloc(sizeof(Job)); // To store shortest job
		// Set currJob to start at current start of list
		currJob = toSort;
		shortestJob = currJob; // start shortestJob at start of list
		prevJob = currJob; // start prevJob at start of list
		nextJob = currJob.next; // start nextJob pointing to second Job in list
		// Find shortest job
		while(currJob.next != NULL) { // Haven't searched whole list
			if (currJob.Time < shortestJob.Time) { // Found a shorter job
				shortestJob = currJob; // Update shortest job found
				nextJob = currJob.next; // Update next job so we can remove job
					// if it ends up being shortest in remaining list
			}
			// move to check next job in list
			currJob = currJob.next;
		}
		// Create space for new job in sorted list
		sortedJobs = malloc(sizeof(Job));
		// Store shortest job information ("copy")
		sortedJobs.Process_ID = shortestJob.Process_ID;
		sortedJobs.Time = shortestJob.Time;
		// Move pointer to next available place in sorted list
		sortedJobs = sortedJobs.next;
		// Remove job found, from original list
		prevJob.next = nextJob; // we point next pointer of job before shortest
			// found to point to the job after the shortest job we found
			// This skips over shortestJob effectively removing it from the list
		toSort = prevJob;
	}
	// Store shortest job (longest)
	sortedJobs.next = currJob;
	
	// Print jobs out in order
	while (sortedJobs.next != NULL) { // haven't found last job
		// Print out required info
		printf("Shortest Job to Run next is with ID: %i and Time %i", sortedJobs.Process_ID, sortedJobs.Time);
	}

	// Notify that we're done processing all jobs according to SJF
	printf("SJF : All Jobs Completed\n");
}
