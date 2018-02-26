
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

#define TRUE 1
#define __NR_cs1550_down 325 //down() is syscall 325
#define __NR_cs1550_up 326 //up() is syscall 326

struct cs1550_sem{
    int value;
    struct node* head;
    struct node* tail;
};

void up(struct cs1550_sem* semaphore){
    syscall(__NR_cs1550_up, semaphore);
}

void down(struct cs1550_sem* semaphore){
    syscall(__NR_cs1550_down, semaphore);
}

int main(int argc, char* argv[]){
    int producers = 0;
    int consumers = 0;
    int size_of_buffer = 0;
    
    if(argc != 4){
        printf("Illegal number of arguments; 3 is required!\n");
        return 1;
    } else{
        consumers = strtol(argv[1], NULL, 10);
        producers = strtol(argv[2], NULL, 10);
        size_of_buffer = strtol(argv[3], NULL, 10);
        
        if(consumers == 0 || producers == 0 || size_of_buffer == 0){
            printf("One of the arguments is the value 0; ILLEGAL.\n");
            return 1;
        }
    }
    struct cs1550_sem* semaphore_memory = (struct cs1550_sem*) mmap(NULL, sizeof(struct cs1550_sem)*3, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0, 0);
    
    int* shared_memory = (int*) mmap(NULL, (size_of_buffer+2)*sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0, 0);
    
    int curr_producers = 0;
    int curr_consumers = 0;
    
    struct cs1550_sem* full;
    full = semaphore_memory + 1;
    full->value = 0;
    full->head = NULL;
    full->tail = NULL;
 
    struct cs1550_sem* empty;
    empty = semaphore_memory;
    empty->value = size_of_buffer;
    full->head = NULL;
    full->tail = NULL;
    
    struct cs1550_sem* mutex;
    mutex = semaphore_memory + 2;
    mutex->value = 1;
    mutex->head = NULL;
    mutex->tail = NULL;
   
    int* curr_produced = shared_memory;
    *curr_produced = 0;
   
    int* curr_consumed = shared_memory + 1;
    *curr_consumed = 0;
    int* buffer_ptr = shared_memory + 2;
    int i;
    
    for(i = 0; i < producers; i++){
        if(fork() == 0){
            int item;
            while(TRUE){
                down(empty);
                down(mutex);
                item = *curr_produced;
                buffer_ptr[*curr_produced % size_of_buffer] = item;
                printf("Producer %c produced: %d\n", (i+65), item);
                *curr_produced += 1;
                up(mutex);
                up(full);
            }
        }
    }
    
    for(i = 0; i < consumers; i++){
        if(fork() == 0){
            int item;
            while(TRUE){
                down(full);
                down(mutex);
                item = buffer_ptr[*curr_consumed % size_of_buffer];
                printf("Consumer %c consumed: %d\n", (i+65), item);
                *curr_consumed += 1;
                up(mutex);
                up(empty);
            }
        }
    }
    int status;
    wait(&status);
    
    return 0;
}
