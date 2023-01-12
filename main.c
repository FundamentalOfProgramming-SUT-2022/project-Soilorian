#include <string.h>
#include <stdio.h>
#include <dir.h>

#define limit 1000

int assets[limit];

// file syntax
//fopen("name", "mode")
//fwrite("phrase", bytes of phrase, 1, what file);

int whatcommand(char *word);

int main(){
    char command[limit];
    scanf("%[^\n]s", command);
    switch (whatcommand(command)) {
        case -1:
            printf("invalid command");

    }
    return 0;
}

int whatcommand(char *word) {
    int i =0;
    char c=word[i++];
    switch(c){
        case 'c':
            break;
        case 'p':
            break;
        case 'r':
            break;
        case 'i':
            break;
        case 'f':
            break;
        case 'g':
            break;
        case 'u':
            break;
        case 't':
            break;
        case 'd':
            break;
        case 'a':
            break;
        case '-':
            break;
        default:
            return -1;
    }

}
