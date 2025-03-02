#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MSG_SIZE 64

struct msg {
    long int type;
    char txt[MSG_SIZE];
};

void initialize_msg_queue(int *msgid);
void handle_otp_generator_process(int msgid);
void handle_login_process(int msgid);
void clean_up(int msgid);

int main() {
    int msgid;
    pid_t pid;

    initialize_msg_queue(&msgid);

    printf("Please enter the workspace name: ");
    fflush(stdout);

    char workspace[20];
    scanf("%s", workspace);

    if (strcmp(workspace, "cse321") != 0) {
        printf("Invalid workspace name\n");
        clean_up(msgid);
        exit(0);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        clean_up(msgid);
        exit(1);
    }

    if (pid == 0) {  
        handle_otp_generator_process(msgid);
    } else {  
        wait(NULL);  
        handle_login_process(msgid);
        clean_up(msgid);
    }

    return 0;
}

void initialize_msg_queue(int *msgid) {
    key_t key = ftok("msgq", 65);
    *msgid = msgget(key, 0666 | IPC_CREAT);
    if (*msgid == -1) {
        perror("msgget");
        exit(1);
    }
}

void handle_otp_generator_process(int msgid) {
    struct msg message;
    msgrcv(msgid, &message, sizeof(message), 1, 0);
    printf("OTP generator received workspace name: %s\n", message.txt);

    sprintf(message.txt, "%d", getpid());
    message.type = 2;
    msgsnd(msgid, &message, sizeof(message), 0);
    printf("OTP sent: %s\n", message.txt);

    message.type = 3;
    msgsnd(msgid, &message, sizeof(message), 0);
    printf("OTP sent to mail: %s\n", message.txt);

    exit(0);
}

void handle_login_process(int msgid) {
    struct msg message;

    msgrcv(msgid, &message, sizeof(message), 2, 0);
    printf("Log in received OTP: %s\n", message.txt);

    strcpy(message.txt, message.txt);
    message.type = 4;
    msgsnd(msgid, &message, sizeof(message), 0);

    msgrcv(msgid, &message, sizeof(message), 4, 0);
    printf("OTP verification result: %s\n", strcmp(message.txt, "expected_otp") == 0 ? "Verified" : "Incorrect");
}

void clean_up(int msgid) {
    msgctl(msgid, IPC_RMID, NULL);
}

