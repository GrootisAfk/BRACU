#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SHM_SIZE sizeof(struct shared)

struct shared {
    char sel[100];
    int balance;
};

void init_shared_memory(key_t key, int *shmid, struct shared **shm);
void create_pipe(int *pipefd);
void handle_child_process(int *pipefd);
void handle_parent_process(int *pipefd, struct shared *shm, int shmid);

int main() {
    int shmid, pipefd[2];
    struct shared *shm;
    key_t key = ftok("banking_app", 'A');

    init_shared_memory(key, &shmid, &shm);
    create_pipe(pipefd);

    pid_t child_pid = fork();
    if (child_pid == -1) {
        perror("fork");
        exit(1);
    }

    if (child_pid == 0) {
        handle_child_process(pipefd);
    } else {
        handle_parent_process(pipefd, shm, shmid);
    }

    return 0;
}

void init_shared_memory(key_t key, int *shmid, struct shared **shm) {
    *shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (*shmid == -1) {
        perror("shmget");
        exit(1);
    }

    *shm = (struct shared *)shmat(*shmid, NULL, 0);
    if (*shm == (struct shared *)-1) {
        perror("shmat");
        exit(1);
    }

    (*shm)->balance = 1000;
}

void create_pipe(int *pipefd) {
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }
}

void handle_child_process(int *pipefd) {
    close(pipefd[1]); 

    char message[100];
    read(pipefd[0], message, sizeof(message));
    printf("%s", message);

    close(pipefd[0]);
    exit(0);
}

void handle_parent_process(int *pipefd, struct shared *shm, int shmid) {
    close(pipefd[0]);

    printf("Provide Your Input From Given Options:\n");
    printf("1. Type 'a' to Add Money\n");
    printf("2. Type 'w' to Withdraw Money\n");
    printf("3. Type 'c' to Check Balance\n");
    scanf("%s", shm->sel);

    if (strcmp(shm->sel, "a") == 0) {
        printf("Your selection: a\nEnter amount to be added:\n");
        int amount;
        scanf("%d", &amount);
        if (amount > 0) {
            shm->balance += amount;
            printf("Balance added successfully\nUpdated balance after addition: %d\n", shm->balance);
        } else {
            printf("Adding failed, Invalid amount\n");
        }
    } else if (strcmp(shm->sel, "w") == 0) {
        printf("Your selection: w\nEnter amount to be withdrawn:\n");
        int amount;
        scanf("%d", &amount);
        if (amount > 0 && amount <= shm->balance) {
            shm->balance -= amount;
            printf("Balance withdrawn successfully\nUpdated balance after withdrawal: %d\n", shm->balance);
        } else {
            printf("Withdrawal failed, Invalid amount\n");
        }
    } else if (strcmp(shm->sel, "c") == 0) {
        printf("Your selection: c\nCurrent balance: %d\n", shm->balance);
    } else {
        printf("Invalid selection\n");
    }

    write(pipefd[1], "Thank you for using\n", sizeof("Thank you for using\n"));
    close(pipefd[1]);

    shmdt(shm);
    shmctl(shmid, IPC_RMID, NULL);
    exit(0);
}

