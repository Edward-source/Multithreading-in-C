#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> /* For working with POSIX threads*/
#include <unistd.h> /* For pause() and sleep() */



void* fn(void* arg)
{  
    char* input = (char*)arg;
    while (1)
    {
        /* code */
        printf("Input string = %s\n", input);
        sleep(1);
    }
    
    return NULL;
}


void create_thread_1()
{
    pthread_t pthread_1;
    static char* thread_input1 = "I am thread no 1";

    void *fn_ptr = fn;
    

    int rc = pthread_create(&pthread_1, NULL, (void*)fn_ptr, (void*)thread_input1);
    if(rc ==0)
    {
        printf("The thread 1 created succuss\n");
    }
    else{
        printf("Error creating a thread 1\n");
    }
}


int main(int argc, char **argv)
{
    create_thread_1();
    printf("main fn paused\n");
    sleep(10);
    return 0;
}