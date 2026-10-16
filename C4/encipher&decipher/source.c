#include <stdio.h>
#include <ctype.h>

void calculateHistogram(char * fileName, int alphabets[26]);
void printHistogram(const int alphabets[26]);
void encipher(const char *p, char *c, const unsigned int offset);
void decipher(const char *c, char *p, const unsigned int offset);

int main(void) {
    // int alphabetCounts[26] = {0};
    // calculateHistogram("/workspaces/University-C-Programming/C4/file.txt", alphabetCounts);
    // printHistogram(alphabetCounts);
    char *x = "ADAM";
    char y[100];
    encipher(x, y, 3);
    printf("%s\n", y);
    char z[100];
    decipher(y, z, 3);
    printf("%s\n", z);
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
        printf("%c: %d ", 'A' + i, alphabets[i]);
        for (int j = 0; j < alphabets[i]; j++) {
            putchar('*');
        }
        putchar('\n');
    }
}

void encipher(const char *p, char *c, const unsigned int offset){
    for (int i = 0; p[i] != '\0'; i++){
        if (isalpha(p[i])){
            c[i] = p[i] + offset;
            if (c[i] > 'Z') {
                c[i] -= 26;
            }
        }
    }
    c[strlen(p)] = '\0';
}

void decipher(const char *c, char *p, const unsigned int offset){
    for (int i = 0; c[i] != '\0'; i++){
        if (isalpha(c[i])){
            p[i] = c[i] - offset;
            if (p[i] < 'A') {
                p[i] += 26;
            }
        }
    }
    p[strlen(c)] = '\0';
}