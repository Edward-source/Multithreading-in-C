#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> /* For working with POSIX threads*/
#include <unistd.h> /* For pause() and sleep() */
#include <time.h>

#define GETTING_VALUES 1
#define  __WAIT(x)   sleep(x);


typedef struct 
{
    /* data */
    float landitude;  // x direction
    float longitude;  // y direction
    time_t timestamp; // all  with respect to time
}gps_data;

static
void* get_temperature_thread(void* arg)
{  
    int* current_temperature = (int*)arg;
    while (GETTING_VALUES)
    {
        /* printing updated temp values */
        printf("Temperature Value = %d\n", current_temperature);
        __WAIT(1)
    }
    
    return NULL;
}

static
void* get_gps_data_thread(void* args)
{
      gps_data* _gps_data = (gps_data*)args;
      
      while(GETTING_VALUES)
      {
          // start to print the values
           check_data:
           if(_gps_data !=NULL)
           {
              printf("Landitude : %f\n", _gps_data->landitude);
              printf("Logitude  : %f\n", _gps_data->longitude);
              printf("Timestamp : %d\n", _gps_data->timestamp);
              __WAIT(1)

           }
           else
           {
            printf("No GPS data found ...\n");
            pthread_exit(0);
            __WAIT(1)

            //goto  check_data;
           }
      }

      return NULL;
}


void main_thread()
{

    /* Threads ....*/
    pthread_t temperature_thread;
    pthread_t gps_thread;
    
    // setting data ...
    static int *current_temperature = 0;
    static gps_data *location = NULL; //{.landitude =23.9, .longitude = 9.1, .timestamp = 1};
    
    /* creation of threads */
    int rc     = pthread_create(&temperature_thread, NULL, get_temperature_thread, (void*)current_temperature);
    int gps_rc = pthread_create(&gps_thread, NULL, get_gps_data_thread , (void*)location);

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
    main_thread();
    
   // __WAIT(10)
   pthread_exit(0);
   return 0;
}