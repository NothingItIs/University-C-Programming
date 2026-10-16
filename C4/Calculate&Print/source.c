#include <stdio.h>
#include <ctype.h>

void calculateHistogram(char * fileName, int alphabets[26]);
void printHistogram(const int alphabets[26]);

int main(void) {
    int alphabetCounts[26] = {0};
    calculateHistogram("/workspaces/University-C-Programming/C4/file.txt", alphabetCounts);
    printHistogram(alphabetCounts);
}

void calculateHistogram(char * fileName, int alphabets[26]){
    FILE *openedFile = fopen(fileName, "r");
    if (!openedFile){
        printf("Error opening file\n");
    }
    int c;
    while ((c = fgetc(openedFile)) != EOF){
        if (isalpha(c)){
            alphabets[toupper(c) - 'A']++;
        }
    }
    fclose(openedFile);
}

void printHistogram(const int alphabets[26]){
    for (int i = 0; i < 26; i++) {
        printf("%c: %d\n", 'A' + i, alphabets[i]);
    }
    putchar('\n');
}