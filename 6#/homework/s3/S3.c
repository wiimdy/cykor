// gcc S3.c -o S3 -no-pie -z relro -z now 
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

#define MAX_COUNT 0x10
#define MAX_SIZE 0x100
#define true 1
#define false 0

typedef struct {
    unsigned int size;
    int isused;
    char data[MAX_SIZE];
} GLOBAL_STORAGE;

typedef struct {
    unsigned int size;
    int isused;
    char data[MAX_SIZE];
} LOCAL_STORAGE;

GLOBAL_STORAGE global_storage;

void alarm_handler() {
    exit(-1);
}

void init(){
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
    signal(SIGALRM, alarm_handler);
    alarm(30);
}

// strcpy can cause one byte overflow. so I made a safer strcpy.
void my_strcpy(char* dest, char* src){
    for (int i = 0; src[i]; i++){
        dest[i] = src[i];
    }
}

void storage_init(LOCAL_STORAGE local_storage[]){
    for (int i = 0; i < MAX_COUNT; i++){
        local_storage[i].size = 0;
        local_storage[i].isused = false;
        memset(local_storage[i].data, 0, MAX_SIZE);
    }
}

void local_add(LOCAL_STORAGE local_storage[]){
    unsigned int idx, size;

    for (idx = 0; idx < MAX_COUNT; idx++){
        if (!local_storage[idx].isused) {
            printf("size : ");
            scanf("%u", &size);

            if (size <= MAX_SIZE){
                local_storage[idx].isused = true;
                local_storage[idx].size = size;

                printf("data : ");
                read(STDIN_FILENO, local_storage[idx].data, size);
                break;
            }
            else{
                puts("invalid size :(");
                exit(-1);
            }          
        }
    }
    
    if (idx == MAX_COUNT)
        puts("all storage is in use");
}

void local_edit(LOCAL_STORAGE local_storage[]){
    unsigned int idx, size;

    printf("index : ");
    scanf("%u", &idx);

    if (idx < MAX_COUNT && local_storage[idx].isused){
        printf("size : ");
        scanf("%u", &size);

        if(size <= local_storage[idx].size){
            local_storage[idx].size = size;

            printf("new data : ");
            read(STDIN_FILENO, local_storage[idx].data, size);
        }
        else{
            puts("invalid size :(");
            exit(-1);
        }
    }
    else{
        puts("invalid index :(");
        exit(-1);
    }
}

void local2global(LOCAL_STORAGE local_storage[]){
    unsigned int idx;

    printf("index : ");
    scanf("%u", &idx);

    if (idx < MAX_COUNT && local_storage[idx].isused){
        global_storage.isused = true;
        global_storage.size = local_storage[idx].size;
        my_strcpy(global_storage.data, local_storage[idx].data);

        local_storage[idx].isused = false;
        local_storage[idx].size = 0;
        memset(local_storage[idx].data, 0, MAX_SIZE);
    }
    else{
        puts("invalid index :(");
        exit(-1);
    }
}

void global2local(LOCAL_STORAGE local_storage[]){
    unsigned int idx;

    printf("index : ");
    scanf("%u", &idx);

    if (idx < MAX_COUNT){
        local_storage[idx].isused = true;
        local_storage[idx].size = global_storage.size;
        my_strcpy(local_storage[idx].data, global_storage.data);

        global_storage.isused = false;
        global_storage.size = 0;
        memset(global_storage.data, 0, MAX_SIZE);
    }
    else{
        puts("invalid index :(");
        exit(-1);
    }
}

void show(LOCAL_STORAGE local_storage[]){
    int select;
    unsigned int idx, size;

    puts("what do you want to see");
    puts("1. global storage");
    puts("2. local storage");
    printf("> ");
    scanf("%d", &select);

    if (select == 1) {
        printf("size : ");
        scanf("%u", &size);
        if (size <= global_storage.size){
            printf("global data : ");
            write(STDOUT_FILENO, global_storage.data, size);
        } else{
            puts("invalid size :(");
            exit(-1);
        }
    }
    else if (select == 2){
        printf("index : ");
        scanf("%u", &idx);

        if (idx < MAX_COUNT && local_storage[idx].isused){
            printf("size : ");
            scanf("%u", &size);

            if(size <= local_storage[idx].size){
                printf("local[%u] data : ", idx);
                write(STDOUT_FILENO, local_storage[idx].data, size);
            }
            else{
                puts("invalid size :(");
                exit(-1);
            }
        }
        else{
            puts("invalid index :(");
            exit(-1);
        }
    }
    else {
        puts("invalid choice :(");
        exit(-1);
    }
}

void menu(){
    puts("1. local add");
    puts("2. local edit");
    puts("3. local2global");
    puts("4. global2local");
    puts("5. show");
    puts("6. exit");
    printf("> ");
}

int main(){
    int select;
    LOCAL_STORAGE local_storage[0x10];

    init();
    storage_init(local_storage);
    puts("Simple Storage Service :)");
    
    while (true) {
        menu();
        scanf("%d", &select);

        switch (select){
            case 1:
                local_add(local_storage);
                break;
            case 2:
                local_edit(local_storage);
                break;
            case 3:
                local2global(local_storage);
                break;
            case 4:
                global2local(local_storage);
                break;
            case 5:
                show(local_storage);
                break;
            case 6:
                puts("bye~");
                return 0;
            default:
                puts("invalid command :(");
                exit(-1);
        }
    }

    return 0;
}