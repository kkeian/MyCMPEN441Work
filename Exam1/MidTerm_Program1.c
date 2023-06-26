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
*  Assignment : MidTerm_Program1.c
*/
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <math.h>
#include <sys/types.h>


typedef struct Bank_Record {
    int Account_Number;
    float Account_Value_2019;
    
}Bank_Record;

// Record to be sent to the shared memory. 
Bank_Record * Record;

    //Variable to store cuurent 1970 account balance
    float value_in_1970 =0;
    
    
//___________________________________________________________________


//Shared Memory Info
char * Shared_Memory_Name = "Import_Accounts";
int shm_fd;
void *ptr;
const int SIZE = 4096;

//___________________________________________________________________

// Turn value determine which thread will run first 
// Turn = 1 means that The main(Get user input).
// Turn = 2 means that the Calc_function needs to calculate values in Record .
// Turn = 3 means that the Send_funtion will send Record to the shared memory.
int Turn = 0;


//___________________________________________________________________
//Thread function prototype 
void *Calc_function(void *arg);
void *Send_function(void *arg);

int main(){


    int Account_Num=0;

    
    //__________________________________________________________
	//##########################################################
	//  Complete the following section : 
	//##########################################################
    //Setup The shared Memory 
    // 1. Create shared memory with read/write and permissions 'rw' for
    //    user, group, and others
    shm_fd = shm_open(Shared_Memory_Name, O_RDWR | O_CREAT, 0666);
    // check if file descriptor create success
    if (shm_fd == -1) {
        perror("Error creating shared memory.\n");
        exit(EXIT_FAILURE);
    }
    
    // 2. Expand created shared memory to SIZE of buffer desired
    int ret_val = ftruncate(shm_fd, SIZE); // give it file descriptor created with shm_open
    // handle error if unable to expand shared memory
    if (ret_val == -1) {
        perror("Error expanding shared memory to required buffer size.");
        exit(EXIT_FAILURE);
    }
    
    // 3. Create pointer to shared memory
    //    of size SIZE
    //    allow read and write
    //.   ensure all processes/threads monitoring shared memory immediately see
    //.   changes
    //.   use shm_fd file descriptor
    //.   no offset = 0
    ptr = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	//##########################################################
	//  End of section
	//##########################################################
    //__________________________________________________________
    
    pthread_t Calc_Thread, Send_Thread;
    int result=0;
	
	
	//##########################################################
	//  Complete the following section : 
	//##########################################################
    //Start the Calc_Thread and Send_Thread 
    pthread_create(&Calc_Thread, NULL, Calc_function, NULL);
    // above thread needs to know starting account value
    pthread_create(&Send_Thread, NULL, Send_function, NULL);
  
	//##########################################################
	//  End of section
	//##########################################################
    //__________________________________________________________
    

    
    //__________________________________________________________
    // First Menu and input from user, Main menu turn
    Turn = 1;
    
    printf("This is a program to get values of accounts in 1970");
    printf(" and calculate the account value in 2019 after inflation \n");
    
    // Get user input and Save into  
    while(value_in_1970 >= 0){
		//##########################################################
		//  Complete the following section : 
		//##########################################################
		// Get input from the user 
        printf("Enter the account number: ");
        // Read in account number to Account_Num variable which initally == 0
        scanf("%i", &Account_Num);
        printf("Enter the value of account in 1970: ");
        // Get the account's initial value
        scanf("%f", &value_in_1970);
		//##########################################################
		//  End of section
		//##########################################################
		//__________________________________________________________
		

       
        // Make space for the Record and Save Account_number into the Record
         Record = malloc(sizeof(Bank_Record));
         Record->Account_Number = Account_Num;

        
        Turn = 2; // Make the Calc_Thread run
        
        //Wait for Main thread Turn
        while(Turn != 1){
             sleep(.5);
        }
        

    }
    
    
    //__________________________________________________________
	//end of Main
	//__________________________________________________________

    
}

void * Calc_function (void *arg){
    

    float CV = 0;
    //Current Value = intial Cash value *  ã€–(1+ .04)ã€—^49
    
    //Wait for This thread Turn
    while(Turn != 2){
        sleep(.5);
    }
    
    
    while(value_in_1970 >= 0){
		//##########################################################
		//  Complete the following section : 
		//##########################################################
		// Calculate the new Value using pow function of Math.h
		// save and value into the Account_Value_2019 part of the record.
        CV = value_in_1970 * pow((1 + 0.04), 49);
        
        Record->Account_Value_2019 = CV;
		//##########################################################
		//  End of section
		//##########################################################
		//__________________________________________________________

    
        Turn = 3;
        //Wait for This thread Turn
        while(Turn != 2){
            sleep(.5);
        }
    
    }
    Turn = 3;
}


void * Send_function (void * arg){
    
  
    //Wait for This thread Turn
    while(Turn != 3){
        sleep(.5);
    }


    while(value_in_1970 >= 0){    
        
        ( (Bank_Record *) ptr )->Account_Number = Record->Account_Number;
		//##########################################################
		//  Complete the following section : 
		//##########################################################
		// Save the Account_Value_2019 from Record into the shared Memory 
		// Advance the pointer to point to the next available empty space
		( (Bank_Record *) ptr )->Account_Value_2019 = Record->Account_Value_2019;
		// Advance pointer to next space available to hold a Record
		ptr += sizeof(Record);
		
		
		 //Give Turn to the Main thread
        Turn = 1; // Set Turn to 1 value, telling program to run Main thread
  
		//##########################################################
		//  End of section
		//##########################################################
		//__________________________________________________________

         
     
         printf("Write %d %f\n",Record->Account_Number,Record->Account_Value_2019);
         
         //Wait this Turn again
         while(Turn != 3){
            sleep(.5);
        }
    

    }
       Turn =1 ;
    
}


