#include <string.h>
#include <stdio.h>
#include <dir.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>


#define limit 1000

int Atrs[limit][limit]={0}, end=0, commandLength, dastoor=0, fileNu=0,err[limit]={0};

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

char *rest(int , char*);

void checkForAtrs(char *);

int whatcommand(char *word);

struct WWL restTillBksl(int i, char *word);

void create(char *address, int , int );

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
                    if(Atrs[fileNu][0]==1){
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

void checkForAtrs(char *command){
    for (int i = 0; i < commandLength; ++i) {
        if(command[i]=='-')
            switch(command[++i]){
            case 'f': {
                char *test = rest(++i, command);
                if((!(strcmp(test, "ile")))&&(dastoor<12)){
                        Atrs[++fileNu][0]=1;
                        char* test2= rest(i+4, command);
                        int l= strlen(test2);
                        for(int j = 1; j <= l; ++j) {
                            Atrs[fileNu][j]= test2[j-1];
                        }
                        Atrs[fileNu][l+1]='\0';
                    return;
                }
            }

        }
    }

}

void create(char *path, int l, int where){
    if(!(isalpha(*path))){
        getchar();
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
        if(l<=where+folfile.length+1){
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
