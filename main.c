#include <string.h>
#include <stdio.h>
#include <dir.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define limit 1000

int Atrs[limit][limit]={0}, end=0, commandLength, dastoor=0, fileNu=0,err[limit]={0};

//Atrs 0= file
//1= str

struct WWL{
    char *word;
    int length;
};

// file syntax
//fopen("name", "mode")
//fwrite("phrase", bytes of phrase, 1, what file);
/* test that dir exists (1 success, -1 does not exist, -2 not dir) */
int xis_dir (const char *d)
{
    DIR *dirptr;

    if (access ( d, F_OK ) != -1 ) {
        // file exists
        if ((dirptr = opendir (d)) != NULL) {
            closedir (dirptr); /* d exists and is a directory */
        } else {
            return -2; /* d exists but is not a directory */
        }
    } else {
        return -1;     /* d does not exist */
    }

    return 1;
}

void goNextLine(void){
    char c;
    do {
        c=getchar();
    } while (c!='\n');
}

char *rest(int , char*);

void checkForAtrs(char *);

int whatcommand(char *word);

struct WWL restTillBksl(int i, char *word);

void create(char *address, int , int );

char *restWithSp(int i, char *word);


int strToNum(char *num);

int main(){
    mkdir("root");
    do {
        for (int i = 0; i < limit; ++i) {
            memset(Atrs[i], 0, sizeof(Atrs[i]));
        }

        char command[limit]={0};
        scanf("%[^\n]s", command);
        getchar();
        if(command[0]!=0) {
            dastoor = whatcommand(command);
            commandLength = strlen(command);
            checkForAtrs(command);
//            printf("%d\n", dastoor);
            switch (dastoor) {
                case -1:
                    printf("invalid command\n");
                    break;
                case 1:
                    if(Atrs[fileNu][0]){
                        Atrs[fileNu][0]=0;
                        int length=0;
                        for (int i = 1;Atrs[fileNu][i]!='\0'; ++i) {
                            length++;
                        }
                        char path[length];
                        for (int i = 0; i < length; ++i) {
                            path[i]=Atrs[fileNu][i+1];
                        }
                        create(path, length, 0);
                    }
                    else
                        printf("invalid command\n");
                    break;
                case limit:
                    break;
            }
        }
    }while(!end);

    return 0;
}

char *rest(int i, char *word){
    int l=0;
    char c;
    do{
        l++;
        c= word[++i];
    }while(c != ' ' && c!=0 &&c!='\n');
    char *check= malloc(l+1);
    for (int j = 0; j < l; ++j) {
        check[j] = word[j+i-l];
    }
    check[l] = '\0';
    return check;
}

int whatcommand(char *word) {
//    printf("%s", word);
    if(!(strcmp(word, "quit"))){
        end++;
        return limit;
    }
    int i =0;
//    printf("  %c  ", word[i]);
    switch(word[i++]){
        case 'c':
//            printf("%c", word[i]);
            switch (word[i++]) {
                case 'r': {
//                    printf("%s", rest(i, word));
                    if (!(strcmp(rest(i, word), "eate")))
                        return 1;
                }
                default:
                    return -1;
            }
            break;
        case 'p':
            break;
        case 'r':
            break;
        case 'i':
            if (!(strcmp(rest(i, word), "nsert")))
                return 2;
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
            goNextLine();
            return -1;

    }
}

void checkForAtrs(char *command){
    for (int i = 0; i < commandLength; ++i) {
        if(command[i]=='-')
            switch(command[++i]){
            case 'f': {
                char *test = rest(++i, command);
                if((!(strcmp(test, "ile")))&&(dastoor<12)){
                        Atrs[++fileNu][0]=1;
                    char* test2;
                        if(*(command+i+4)=='\"')
                            test2= restWithSp(i+4, command);
                        else
                            test2= rest(i+4, command);
                        int l= strlen(test2);
                        for(int j = 1; j <= l; ++j) {
                            Atrs[fileNu][j]= test2[j-1];
                        }
                        Atrs[fileNu][l+1]='\0';
                    return;
                }
                }
                case 's': {
                    char *test = rest(++i, command);
                    if((!(strcmp(test, "tr")))&&(dastoor=2)||((dastoor<=10)&&(dastoor>=8))){
                        Atrs[++fileNu][1]=1;
                        char* test2;
                        if(*(command+i+3)=='\"')
                            test2= restWithSp(i+3, command);
                        else
                            test2= rest(i+3, command);
                        int l= strlen(test2);
                        for(int j = 1; j <= l; ++j) {
                            Atrs[fileNu][j]= test2[j-1];
                        }
                        Atrs[fileNu][l+1]='\0';
                        return;
                    }
                }
                case 'p': {
                    char *test = rest(++i, command);
                    if((!(strcmp(test, "os")))&&(dastoor=2)||((dastoor<=7)&&(dastoor>=4))){
                        int l=0;
                        char c;
                        do{
                            l++;
                            c= command[++i];
                        }while(c != ':');
                        Atrs[fileNu][1]=strToNum(command[i-l]);
                        Atrs[fileNu][2]=strToNum(command[++i]);
                        return;
                    }
                }
                default:
                    printf("invalid Atribute!\n");
                    goNextLine();
                    return;
        }
    }
}

void create(char *path, int l, int where){
    if(!(isalpha(*path))){
        path++;
    }
    struct WWL folfile = restTillBksl(where, path);
    char P[where+folfile.length+1];
    char temp=path[where+folfile.length];
    path[where+folfile.length]='\0';
    strcpy(P, path);
    path[where+folfile.length]=temp;
    if(xis_dir(P)==1){
        create(path, l, where+folfile.length);
    }
    else if(xis_dir(folfile.word)==-2){
        printf("file already exists!\n");
    }
    else{
        if(l<=where+folfile.length+3){
            if(fopen(path, "r")!='\0'){
                printf("file already exists!\n");
                return;
            }
            FILE *s=fopen(path, "w");
            fclose(s);
        }
        else{
            mkdir(P);
            create(path, l, where+folfile.length);
        }
    }
}

struct WWL restTillBksl(int i, char *word) {
    int l=0;
    char c;
    do{
        l++;
        c= word[++i];
    }while(c != '/' && c!=0 && c!='"');
    char *check= malloc(l+1);
    for (int j = 0; j < l; ++j) {
        check[j] = word[j+i-l];
    }
    check[l] = '\0';
    struct WWL ans;
    ans.word=check;
    ans.length=l;
    return ans;
}

char *restWithSp(int i, char *word) {
    int l=0;
    char c;
    do{
        l++;
        c= word[++i];
    }while(c!=0 &&c!='\n');
    char *check= malloc(l+1);
    for (int j = 0; j < l; ++j) {
        check[j] = word[j+i-l];
    }
    check[l] = '\0';
    return check;
}

int strToNum(char *num) {
    int l= strlen(num);
    int ans=0;
    for (int i = 0; i < l; ++i) {
        switch (num[i]) {
            case '0':
                continue;
            case '1':
                ans+=1* pow(10, l-i-1);
                continue;
            case '2':
                ans+=2* pow(10, l-i-1);
                continue;
            case '3':
                ans+=3* pow(10, l-i-1);
                continue;
            case '4':
                ans+=4* pow(10, l-i-1);
                continue;
            case '5':
                ans+=5* pow(10, l-i-1);
                continue;
            case '6':
                ans+=6* pow(10, l-i-1);
                continue;
            case '7':
                ans+=7* pow(10, l-i-1);
                continue;
            case '8':
                ans+=8* pow(10, l-i-1);
                continue;
            case '9':
                ans+=9* pow(10, l-i-1);
                continue;
            default:
                return -1;
        }
    }
}
