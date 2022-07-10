// gcc not_isolated.c -o not_isolated -no-pie
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#define true 1
#define false 0

typedef struct x64_VM{
    int stack[0x500];
    int rsp;
    int rip;
    int rax;
    int zeroFlag;
    int logFlag;
} x64_VM;

x64_VM VM;

enum {PUSH, POP, CLEAN, LOG};

void alarm_handler() {
    exit(-1);
}

void banner(){
    puts("            ______    ______         __     __  __       __ ");
    puts("           /      \\  /      \\       /  |   /  |/  \\     /  |");
    puts(" __    __ /$$$$$$  |/$$$$$$  |      $$ |   $$ |$$  \\   /$$ |");
    puts("/  \\  /  |$$ \\__$$ |$$ \\__$$/       $$ |   $$ |$$$  \\ /$$$ |");
    puts("$$  \\/$$/ $$    $$< $$      \\       $$  \\ /$$/ $$$$  /$$$$ |");
    puts(" $$  $$<   $$$$$$  |$$$$$$$  |       $$  /$$/  $$ $$ $$/$$ |");
    puts(" /$$$$  \\ $$ \\__$$ |$$ \\__$$ |        $$ $$/   $$ |$$$/ $$ |");
    puts("/$$/ $$  |$$    $$/ $$    $$/          $$$/    $$ | $/  $$ |");
    puts("$$/   $$/  $$$$$$/   $$$$$$/            $/     $$/      $$/ ");
    printf("\nsimple VM, but not isolated\n\n");
}

void init(){
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
    signal(SIGALRM, alarm_handler);
    alarm(30);
}

void push(){
    if (VM.rsp <= 0x500 * 4){
        if(VM.logFlag)
            printf("[*] PUSH stack[0x%x] = 0x%x\n", VM.rsp, VM.rax);
        VM.stack[VM.rsp++] = VM.rax;
    }
}

void pop(){
    if(VM.rsp){
        if(VM.logFlag)
            printf("[*] POP stack[0x%x] == 0x%x\n", VM.rsp - 1, VM.stack[VM.rsp - 1]);
        VM.rax = VM.stack[--VM.rsp];
    }
}

void clean(){
    if(VM.logFlag)
        puts("[*] CLEAN STACK");
    VM.stack[0] = 0LL;
    VM.rsp = 0LL;
}

void log(){
    puts("[!] I prepared log feature for you :)");
    VM.logFlag = VM.rax;
}

void exec(int command, int arg){
    VM.rax = arg;

    switch(command){
        case PUSH:
            push();
            break;
        case POP:
            pop();
            break;
        case CLEAN:
            clean();
            break;
        case LOG:
            log();
            break;
        default:
            exit(-1);
    }
}

void simpleVM(char* opcode, unsigned int len){
    char type;
    int arg1;
    int arg2;

    exec(2, 0);

    while(VM.rip < len){
        switch (opcode[VM.rip++])
        {
        case 0:
            arg1 = *(int*)(opcode + VM.rip);
            VM.rip += 4;
            exec(PUSH, arg1);
            break;
        case 1:
            exec(POP, 0);
            break;
        case 2:
            type = *(char*)(opcode + VM.rip);
            VM.rip++;
            if (type == 'f'){
                arg1 = *(int*)(opcode + VM.rip);
                VM.rip += 4;
            }
            else {
                if (type != 'U')
                    exit(-1);
                exec(POP, 0);
                arg1 = VM.rax;
            }

            type = *(char*)(opcode + VM.rip);
            VM.rip++;
            if (type == 'f'){
                arg2 = *(int*)(opcode + VM.rip);
                VM.rip += 4;
            }
            else {
                if (type != 'U')
                    exit(-1);
                exec(POP, 0);
                arg2 = VM.rax;
            }
            exec(PUSH, arg1 + arg2);
            break;
        case 3:
            type = *(char*)(opcode + VM.rip);
            VM.rip++;
            if (type == 'f'){
                arg1 = *(int*)(opcode + VM.rip);
                VM.rip += 4;
            }
            else {
                if (type != 'U')
                    exit(-1);
                exec(POP, 0);
                arg1 = VM.rax;
            }

            type = *(char*)(opcode + VM.rip);
            VM.rip++;
            if (type == 'f'){
                arg2 = *(int*)(opcode + VM.rip);
                VM.rip += 4;
            }
            else {
                if (type != 'U')
                    exit(-1);
                exec(POP, 0);
                arg2 = VM.rax;
            }
            exec(PUSH, arg1 - arg2);
            break;
        case 4:
            type = *(char*)(opcode + VM.rip);
            VM.rip++;
            if (type == 'f'){
                arg1 = *(int*)(opcode + VM.rip);
                VM.rip += 4;
            }
            else {
                if (type != 'U')
                    exit(-1);
                exec(POP, 0);
                arg1 = VM.rax;
            }

            type = *(char*)(opcode + VM.rip);
            VM.rip++;
            if (type == 'f'){
                arg2 = *(int*)(opcode + VM.rip);
                VM.rip += 4;
            }
            else {
                if (type != 'U')
                    exit(-1);
                exec(POP, 0);
                arg2 = VM.rax;
            }
            exec(PUSH, arg1 * arg2);
            break;
        case 5:
            type = *(char*)(opcode + VM.rip);
            VM.rip++;
            if (type == 'f'){
                arg1 = *(int*)(opcode + VM.rip);
                VM.rip += 4;
            }
            else {
                if (type != 'U')
                    exit(-1);
                exec(POP, 0);
                arg1 = VM.rax;
            }

            type = *(char*)(opcode + VM.rip);
            VM.rip++;
            if (type == 'f'){
                arg2 = *(int*)(opcode + VM.rip);
                VM.rip += 4;
            }
            else {
                if (type != 'U')
                    exit(-1);
                exec(POP, 0);
                arg2 = VM.rax;
            }
            exec(PUSH, arg1 / arg2);
            break;
        case 6:
            type = *(char*)(opcode + VM.rip);
            VM.rip++;
            if (type == 'f'){
                arg1 = *(int*)(opcode + VM.rip);
                VM.rip += 4;
            }
            else {
                if (type != 'U')
                    exit(-1);
                exec(POP, 0);
                arg1 = VM.rax;
            }

            type = *(char*)(opcode + VM.rip);
            VM.rip++;
            if (type == 'f'){
                arg2 = *(int*)(opcode + VM.rip);
                VM.rip += 4;
            }
            else {
                if (type != 'U')
                    exit(-1);
                exec(POP, 0);
                arg2 = VM.rax;
            }
            if(arg1 == arg2)
                VM.zeroFlag = true;
            else
                VM.zeroFlag = false;
            break;
        case 7:
            type = *(char*)(opcode + VM.rip);
            VM.rip++;
            if (type == 'f'){
                arg1 = *(int*)(opcode + VM.rip);
                VM.rip += 4;
            }
            else {
                if (type != 'U')
                    exit(-1);
                exec(POP, 0);
                arg1 = VM.rax;
            }
            VM.rip = arg1;
            break;
        case 8:
            type = *(char*)(opcode + VM.rip);
            VM.rip++;
            if (type == 'f'){
                arg1 = *(int*)(opcode + VM.rip);
                VM.rip += 4;
            }
            else {
                if (type != 'U')
                    exit(-1);
                exec(POP, 0);
                arg1 = VM.rax;
            }
            if (VM.zeroFlag)
                VM.rip = arg1;
            break;
        case 9:
            exec(CLEAN, 0);
            break;
        case 10:
            type = *(char*)(opcode + VM.rip);
            VM.rip++;
            if (type == 'f'){
                arg1 = *(int*)(opcode + VM.rip);
                VM.rip += 4;
            }
            else {
                if (type != 'U')
                    exit(-1);
                exec(POP, 0);
                arg1 = VM.rax;
            }
            exec(LOG, arg1);
            break;
        default:
            exit(-1);
            break;
        }
    }
}

int main(){
    unsigned int len;
    char opcode[0x300];

    init();
    banner();

    printf("opcode> ");
    len = read(STDIN_FILENO, opcode, sizeof(opcode));
    simpleVM(opcode, len);

    return 0;
}