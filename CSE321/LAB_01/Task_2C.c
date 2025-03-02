#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char password[100];

    printf("Enter your password: ");
    scanf("%s", password);

    int hasLower = 0, hasUpper = 0, hasDigit = 0, hasSpecial = 0;

    for (int i = 0; i < strlen(password); i++) {
        if (islower(password[i])) {
            hasLower = 1;
        } else if (isupper(password[i])) {
            hasUpper = 1;
        } else if (isdigit(password[i])) {
            hasDigit = 1;
        } else if (strchr("_,$#@", password[i]) != NULL) {
            hasSpecial = 1;
        }
    }

    if (!hasLower) {
        printf("Lowercase character missing\n");
    }
    if (!hasUpper) {
        printf("Uppercase character missing\n");
    }
    if (!hasDigit) {
        printf("Digit missing\n");
    }
    if (!hasSpecial) {
        printf("Special character missing\n");
    }

    if (hasLower && hasUpper && hasDigit && hasSpecial) {
        printf("OK\n");
    }

    return 0;
}