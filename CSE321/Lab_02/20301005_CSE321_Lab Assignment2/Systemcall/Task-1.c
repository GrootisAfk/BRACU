#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

void strings_file(const char *filename) {
    FILE *file = fopen("output_file.txt", "a");  

    if (file == NULL) {
        perror("Error file");
        return 1; 
    }

    char input[100];

    printf("Please input a string (enter \"-1\" to finish):\n");


    while (1) {
        fgets(input, sizeof(input), stdin);

        
        size_t len = strlen(input);

    if (len > 0) {
            char *newline = strchr(input, '\n');
            if (newline != NULL) {
                *newline = '\0';
    }
}


      
        if (strcmp(input, "-1") == 0) {
            break;
        }

        fprintf(file, "%s\n", input);
    }

    fclose(file);
    printf("Strings written to the file.\n");
}

int main() {
    strings_file("output_file.txt");
    return 0;
}
