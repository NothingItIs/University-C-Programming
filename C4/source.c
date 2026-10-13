#include <stdio.h>

int main(void) {
    FILE *openedFile = fopen("file.txt", "are");
    int c;
    while ((c = fgetc(openedFile)) != EOF){
        putchar(c);        
    }
    fclose(openedFile);
}