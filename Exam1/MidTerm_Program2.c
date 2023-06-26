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
*  Assignment : MidTerm_Program2.c
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int fact(int x){
	//__________________________________________________________
	//##########################################################
	//  Complete the following section : 
	//##########################################################
	// Write the code that will calculate factorial of x
	// Base Case: x = 0 or 1
	if (x == 0 || x == 1) {
	    return 1; // Return initial return value = 1
	} else {
	   return x * fact(x-1); // recursive definition of factorial function for
	                         // x > 1
	}
  	//##########################################################
	//  End of section
	//##########################################################
    //__________________________________________________________
}
void main() {
    int p_c[2];
    int c_p[2];
    int x;
    int tmp;
    
    pipe(p_c);
    pipe(c_p);
    
    pid_t pid = fork();
   
   
       
		
	//__________________________________________________________
	//##########################################################
	//  Complete the statements in following section : 
	//##########################################################
    //Check if the process is the child process. 
		// if it is the child process, read the number sent from  
		//    the parent process into the pipe .
		
		if(pid == 0){		//Child 
		    close(p_c[0]); //close the read end in p_c
            close(c_p[1]); //close the write end in c_p
   
            do{
                // Read from child read end of pipe c_p[0],
                // the number sent from parent process
                // Read into x variable (send address of x to read)
                // requires casting x to int* type
                // Read in number of bytes that int type is b/c x is int type
                read(c_p[0], &x, sizeof(x));
                
                if(x!=-1){
                    tmp = fact(x); // pass in read x value to fact function
                                   // return result in tmp variable
                    write(p_c[1], &tmp, sizeof(int)); // write to the parent pipe write
                                                // fd p_c[1], tmp (result of fact)
                                                // requires casting tmp to int* type
                                                // write number of bytes that int
                                                // type is b/c tmp is int type
                }
            }while(x!= -1);
            close(c_p[0]); //close the read end  in c_p
            close(p_c[1]); //close the write end in p_c
    		
    		
	//##########################################################
	//  End of section
	//##########################################################
    //__________________________________________________________
    
    }else if(pid > 0){
        
		//__________________________________________________________
		//##########################################################
		//  Complete the statements in following section : 
		//##########################################################
		//parent
		
        close(p_c[1]); //close the write end in p_c
        close(c_p[0]); //close the read end  in c_p
        
        do{
            printf("Enter a number to calculate factorial:");
            scanf("%d",&x);
           
           // Write to child process write end of pipe
           // requires casting x to int* type
            write(c_p[1], &x, sizeof(int));
            
        
            if(x == -1) // End of input reached
                break;
                
            // Read the factorial result from the p_c pipe in tmp variable
            // requires casting x to int* type
            read(p_c[0], &tmp, sizeof(int));
            
            printf("Result = %d\n", tmp);
            
        } while(x != -1);
        
        close(p_c[0]); //close the read end in p_c
        close(c_p[1]); //close the write end in c_p
        wait(NULL);         // wait for the child to exit
    }else{
        printf("Error Forking\n");
    }
    
    
}