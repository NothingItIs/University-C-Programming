#include <stdio.h>
#include <ctype.h>

int main(void) {
    FILE *openedFile = fopen("/workspaces/University-C-Programming/C4/file.txt", "r");
    if (!openedFile){
        printf("Error opening file\n");
        return 1;
    }
    int c;
    while ((c = fgetc(openedFile)) != EOF){
        putchar(c);        
    }
    fclose(openedFile);
}