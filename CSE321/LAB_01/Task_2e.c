#include <stdio.h>
#include <string.h>
#include <ctype.h>

int topClassPalindromeChecker(char *str) {
    char *start = str;
    char *end = str + strlen(str) - 1;

    while (start < end) {
        if (tolower(*start++) != tolower(*end--)) {
            return 0;
        }
    }
    return 1;
}

int main() {
    char input[100];

    printf("Enter a string: ");
    scanf("%s", input);

    if (topClassPalindromeChecker(input)) {
        printf("Palindrome\n");
    } else {
        printf("Not Palindrome\n");
    }

    return 0;
}