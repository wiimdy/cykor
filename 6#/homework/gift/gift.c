#include<stdio.h>
#include<stdio.h>
#include<string.h>

unsigned long long int address;

void start_menu(void){
    puts("Hello, It is the practice challenge for Easy ROP");
    puts("H00RAY Let's start :)\n");
    puts("If you solve this chall, plz send kakaotalk message");
    puts("***** kakao ID : pk2861 *****");
    puts("I will give you some present if you solve fast ~~\n\n");
}

extern char _start;
void print_name(){
    char in[16];
    memset(in,'\x00',16);
    read(0,in,17);
    printf("Your name : %s",in);
}

unsigned long long int abs(unsigned long long int x){
    if(x > 0)   return x;
    else    return -1 * x;
}
void magic_function(unsigned int x){

    switch(x){
        case 0x12345678:
            printf(" == MAGIC FUNCTION == \n");
            scanf("%llu", &address);
            if (abs(address - (unsigned long long int)&_start) < 0x10000){
                printf("*address = %p\n",*(unsigned long long int *)address);
            }
            else{
                printf("No,,, it's not valid address\n");
            }
            break;
    }

}


int getInt(){
    char buf_local[0x20];

    read(0,buf_local,0x10);
    return atoi(buf_local);
}
void sub_main(){
    int secret = 0x12345678;
    int secret2 = 0xaabbccdd;
    int token = 0;
    int rep = 1;
    char array[20];
    while(1){
        puts("Input :");
        switch(getInt()){
            case 0:
                puts("NOT VALID");
                break;
            case 1:
                print_name();
                break;
            case -1: 
                if (token == 0x12345678){
                    magic_function(token);
                }
                else{
                    puts("Is the secret token is right? please set 0x12345678");
                }
                break;
            case -2:
                if(secret2 == 0xaabbccdd){
                    secret2 = 0;
                    printf("I WILL TELL YOU ONLY ONE ADDRESS!!\n");
                    scanf("%llu",&address);
                    unsigned long long int value = *(unsigned long long int *)address;
                    if(abs(value - (unsigned long long int)&_start) < 0x10000){
                        printf("*address = %p\n",*(unsigned long long int *)address);
                    }
                    else{
                        printf("NONO ~\n");
                    }
                }
                break;
            case 123:
                return ;
        }
    }
}
int main(int argc, char ** argv){
    start_menu();
    sub_main();
    puts("I will give you one BOF ^__^");
    char buffer[0x20];
    read(0,buffer,0x100);
    return 0;
}