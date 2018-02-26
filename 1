
#include <sys/types.h>
#include <linux/unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <stdio.h>

struct cs1550_sem
{
    int value;
    struct Node *start;
    struct Node *end;
};

void up(struct cs1550_sem *sem) {
    syscall(__NR_cs1550_up, sem);
}

void down(struct cs1550_sem *sem) {
    syscall(__NR_cs1550_down, sem);
}

int main(int argc, char *argv[])
{
    if(argc != 4)
    {
        printf("Usage: %s [numProducers] [numConsumers] [bufferSize]\n",argv[0]);
        exit(-1);
    }
    
  
    int numProducers = atoi(argv[1]);
    int numConsumers = atoi(argv[2]);
    int bufferSize = atoi(argv[3]);
    
   
    void * sem_ptr = mmap(NULL, sizeof(struct cs1550_sem)*3, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, 0, 0);
    
    struct cs1550_sem * empty  = (struct cs1550_sem*)sem_ptr;
    struct cs1550_sem * full = (struct cs1550_sem*)sem_ptr + 1;
    struct cs1550_sem * mutex = (struct cs1550_sem*)sem_ptr + 2;
    
 
    void * intMem = mmap(NULL, sizeof(int)*(bufferSize + 3), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, 0, 0);
    
    int * buffSizePointer = (int*)intMem;
    int * producerPointer = (int*)intMem + 1;
    int * consumerPointer = (int*)intMem + 2;
    int * bufferPointer = (int*)intMem + 3;
    
    *buffSizePointer = bufferSize;
    *producerPointer = 0;
    *consumerPointer = 0;

    full->value = 0;
    full->start = NULL;
    full->end = NULL;
    mutex->value = 1;
    mutex->start = NULL;
    mutex->end = NULL;
    empty->value = bufferSize;
    empty->start = NULL;
    empty->end = NULL;
    
    int i;
    for(i = 0; i < bufferSize; i++)
        bufferPointer[i] = 0;
    
    for(i = 0; i < numProducers; i++)
    {
        if(fork() == 0)
        {
            int item;
            while(1)
            {
                down(empty);
                down(mutex);
                
                item = *producerPointer;
                bufferPointer[*producerPointer] = item;
                printf("Producer %c Produced: %d\n", i+65, item);
                *producerPointer = (*producerPointer+1) % *buffSizePointer;
                
                up(mutex);
                up(full);
            }
        }
    }
    
    for(i = 0; i < numConsumers; i++)
    {
        if(fork() == 0)
        {
            int item;
            
            while(1)
            {
                down(full);
                down(mutex);
                
                item = bufferPointer[*consumerPointer];
                printf("Consumer %c Consumed: %d\n", i+65, item);
                *consumerPointer = (*consumerPointer+1) % *buffSizePointer;
                
                up(mutex);
                up(empty);
            }
        }
    }
    
    int status;
    wait(&status);
    return 0;
}
