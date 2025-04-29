// Madhavan Deshmukh
// Project 10
// Lab section 1104

#include <stdio.h>

// declaring macros fro 2-D array and the word length in the file
#define wordlen 5
#define maxtries 6
#define strsize 6

// declaring function prototypes
int countletters(char input[]);
int comparewords(char input1[], char input2[]);
void loadword(char word[]);
void getguess(char guess[], int tries);
void evaluate(char guess[], char word[], char display[][strsize], char marks[][strsize], int tries);

int main() {
	// declaring all the needed arrays and variables
    char word[strsize];
    char guess[strsize];
    char display[maxtries][strsize];
    char marks[maxtries][strsize];
    int tries = 0;

    loadword(word);
   // loops for all the guesses the user gets the answer correct
    while (tries < maxtries) {
        getguess(guess, tries + 1);
        evaluate(guess, word, display, marks, tries);
        if (comparewords(guess, word) == 0) {
            printf("                %s\n", display[tries]);
            printf("        You won in %d guess%s!\n", tries + 1, (tries == 0) ? "" : "es");
           
            if (tries == 0) {
                printf("                GOATED!\n");
            } else if (tries == 1 || tries == 2) {
                printf("                Amazing!\n");
            } else if (tries == 3 || tries == 4) {
                printf("                Nice!\n");
            }
            return 0;
        }
        tries = tries + 1;
    }

    // displaying the losing prompt if the user doesnt get the answer right and uses all the guesses
    printf("You lost, better luck next time!\n");
    
    return 0;
}

// function for counting the letters
int countletters(char input[]) {
    int count = 0;
    while (input[count] != '\0') {
        count++;
    }
    return count;
}

// function for comparing the two arrays
int comparewords(char input1[], char input2[]) {
    int i = 0;
    while (input1[i] != '\0' && input2[i] != '\0') {
        if (input1[i] != input2[i]) {
            return 1;
        }
        i++;
    }
    if (input1[i] == '\0' && input2[i] == '\0') {
        return 0;
    }
    return 1;
}

// function for fileIO and to change the capital lettes into lowercase ones
void loadword(char word[]) {
    FILE *file;
    file = fopen("mystery.txt", "r");
    if (file == NULL) {
        printf("Error: cannot open mystery.txt\n");
        word[0] = '\0';
    } else {
        fscanf(file, "%5s", word);
        fclose(file);

        int i = 0;
        while (word[i] != '\0') {
            if (word[i] >= 'A' && word[i] <= 'Z') {
                word[i] = word[i] + 32;
            }
            i++;
        }
    }
}

// function made if the guess inputted by the user isnt 5 characters long
void getguess(char guess[], int tries) {
    char temp[100];
    int valid = 0;

    while (valid == 0) {
        printf("GUESS %d! Enter your guess: ", tries);
        scanf("%s", temp);

        int len = countletters(temp);

        if (len != wordlen) {
            printf("Your guess must be 5 letters long.\n");
            printf("Please try again: ");
            scanf("%s", temp);
            len = countletters(temp);
        }

        int okay = 1;
        int i = 0;
        while (i < wordlen) {
            if (!((temp[i] >= 'a' && temp[i] <= 'z') || (temp[i] >= 'A' && temp[i] <= 'Z'))) {
                okay = 0;
            }
            i++;
        }

        if (okay == 1) {
            for (i = 0; i < wordlen; i++) {
                if (temp[i] >= 'A' && temp[i] <= 'Z') {
                    guess[i] = temp[i] + 32;
                } else {
                    guess[i] = temp[i];
                }
            }
            guess[wordlen] = '\0';
            valid = 1;
        }
    }

    printf("=====================================\n");
}

// function to give the amount of blank spaces and '^' character
void evaluate(char guess[], char word[], char display[][strsize], char marks[][strsize], int tries) {
    int used[wordlen];
    int i;
    for (i = 0; i < wordlen; i++) {
        used[i] = 0;
    }

    for (i = 0; i < wordlen; i++) {
        display[tries][i] = guess[i];
        marks[tries][i] = ' ';
    }

    display[tries][wordlen] = '\0';
    marks[tries][wordlen] = '\0';

    for (i = 0; i < wordlen; i++) {
        if (guess[i] == word[i]) {
            if (display[tries][i] >= 'a' && display[tries][i] <= 'z') {
                display[tries][i] = display[tries][i] - 32;
            }
            used[i] = 1;
        }
    }

    for (i = 0; i < wordlen; i++) {
        if (guess[i] != word[i]) {
            int j;
            for (j = 0; j < wordlen; j++) {
                if (used[j] == 0 && guess[i] == word[j]) {
                    marks[tries][i] = '^';
                    used[j] = 1;
                    j = wordlen; 
                 }
             }
         } 
    }

    int r;
    if (comparewords(guess, word) == 0) {
        
        for (r = 0; r < tries; r++) {
            printf("%s\n", display[r]);
            printf("%s\n", marks[r]);
        }
    } else {
 
        for (r = 0; r <= tries; r++) {
            printf("%s\n", display[r]);
            printf("%s\n", marks[r]);
        }
    }
}
