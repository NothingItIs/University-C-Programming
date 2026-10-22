// #include <stdio.h>
// #include <ctype.h>
// #include <stdlib.h>
// #include <time.h>
// #include <string.h>


// // #define DEBUG 1

// void calculateHistogram(char * fileName, int alphabets[26]);
// void printHistogram(const int alphabets[26]);
// void encipher(const char *p, char *c, const unsigned int offset);
// void decipher(const char *c, char *p, const unsigned int offset);

// int main(void) {
//     // int alphabetCounts[26] = {0};
//     // calculateHistogram("/University-C-Programming/C4/file.txt", alphabetCounts);
//     // printHistogram(alphabetCounts);
//     // char *x = "interjectaaaaaaa\naaaaaactfvygbuhnij";
//     // char y[100];
//     // encipher(x, y, 3);
//     // printf("%s\n", y);
//     // char z[100];
//     // decipher(y, z, 3);
//     // printf("%s\n", z);
//     srand(time(NULL));
//     FILE *openedFile = fopen("/University-C-Programming/C4/file.txt", "r");
//     FILE *openedFileCapital = fopen("/University-C-Programming/C4/file_cap.txt", "w+");
//     FILE *openedFileEnciphered = fopen("/University-C-Programming/C4/file_enc.txt", "w+");
//     FILE *openedFileDeciphered = fopen("/University-C-Programming/C4/file_dec.txt", "w+");
//     if (!openedFile || !openedFileCapital || !openedFileEnciphered || !openedFileDeciphered){
//         printf("Error opening file\n");
//         return 0;
//     }
//     char p[74764];
//     char c[74764];
//     char buffer;
//     for (int i = 0; (buffer = fgetc(openedFile)) != EOF; i++){
//         p[i] = toupper(buffer);
//     }
//     p[strlen(p)] = '\0';
//     fputs(p, openedFileCapital);
//     encipher(p, c, ((rand()/RAND_MAX)*26));
//     fputs(c, openedFileEnciphered);
//     fclose(openedFile);
//     fclose(openedFileCapital);
//     fclose(openedFileEnciphered);
    
//     int x[26]={0};
//     calculateHistogram("/University-C-Programming/C4/file_cap.txt", x);
//     int y[26] = {0};
//     calculateHistogram("/University-C-Programming/C4/file_enc.txt", y);
//     printHistogram(x);
//     putchar('\n');
//     printHistogram(y);

//     int max = 0;
//     for (int i = 0; i < 26; i++){
//         if (y[i] > y[max]){
//             max = i;
//         }
//     }
    
//     char o[74764];

//     decipher(c,o,((max - ('E' - 'A') + 26)%26));
//     fputs(o, openedFileDeciphered);
//     fclose(openedFileDeciphered);
// }

// void calculateHistogram(char * fileName, int alphabets[26]){
//     FILE *openedFile = fopen(fileName, "r");
//     if (!openedFile){
//         printf("Error opening file\n");
//     }
//     int c;
//     while ((c = fgetc(openedFile)) != EOF){
//         if (isalpha(c)){
//             alphabets[toupper(c) - 'A']++;
//         }
//     }
//     fclose(openedFile);
// }

// void printHistogram(const int alphabets[26]){
//     for (int i = 0; i < 26; i++) {
//         printf("%c: %2d ", 'A' + i, alphabets[i]);
//         for (int j = 0; j < alphabets[i]; j++) {
//             putchar('*');
//         }
//         putchar('\n');
//     }
// }

// void encipher(const char *p, char *c, const unsigned int offset){
//     for (int i = 0; p[i] != '\0'; i++){
//         if (isalpha(p[i])){
//             c[i] = p[i] + offset;
//             if (c[i] > 'Z') {
//                 c[i] -= 26;
//             }
//         } else {
//             c[i] = p[i];
//         }
//     }
//     c[strlen(p)] = '\0';
//     #ifdef DEBUG
//     printf("reached encipher\n");
//     printf("%s\n", c);
//     #endif
// }

// void decipher(const char *c, char *p, const unsigned int offset){
//     for (int i = 0; c[i] != '\0'; i++){
//         if (isalpha(c[i])){
//             p[i] = c[i] - offset;
//             if (p[i] < 'A') {
//                 p[i] += 26;
//             }
//         } else {
//             p[i] = c[i];
//         }
//     }
//     p[strlen(c)] = '\0';
// }