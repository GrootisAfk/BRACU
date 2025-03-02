#include <stdio.h>
#include <string.h>

void emailUpdateChecker(char email[]) {
    char old_domain[] = "@kaaj.com";
    char new_domain[] = "@sheba.xyz";

    if (strcmp(email + strlen(email) - strlen(old_domain), old_domain) == 0) {
        printf("Email address is outdated\n");

    
        strcpy(email + strlen(email) - strlen(old_domain), new_domain);
        printf("Updated email address: %s\n", email);
    } else if (strcmp(email + strlen(email) - strlen(new_domain), new_domain) == 0) {
        printf("Email address is okay\n");
    } else {
        printf("Invalid email address format\n");
    }
}

int main() {
    char email[100];

    printf("Enter your email address: ");
    scanf("%s", email);

    emailUpdateChecker(email);

    return 0;
}