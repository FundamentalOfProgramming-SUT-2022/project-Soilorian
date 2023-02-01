#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <dir.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>
#include <errno.h>

#define limit 1000

char *Atrs[limit]={0}, *clipboard= NULL;
bool whatAtrs[limit]={false},end=false, err[limit]={false}, success=false;
long long commandLength;
int dastoor=0;

//Atrs 0= file
//1= str1
//2= pos Line
//3= pos char
//4= backward(0) or forward(1)
//5= size
//6= str2

//WhatAtrs 0= file
//1= str1
//2= pos
//3= forward of backward
//4= size


struct WWL{
    char *word;
    int length;
};

struct WWL restTillBksl(int i, char *word);

struct WWL pathMaker(void);

struct WWL strMaker(void);

struct linkedlist{
    char *c;
    bool death;
    int length;
    struct linkedlist* next;
    struct linkedlist* prev;
};

struct linkedlist* create_linkedlist(void);

struct linkedlist* fileToList(FILE *f);

void delete_linkedList(struct linkedlist *list);

void remove_with_index(int n, struct linkedlist * list);

void add(struct linkedlist* list, char *c, int l);

void add_with_index(struct linkedlist* list, char *c, int , int l, int index);

int size(struct linkedlist *list);

char *get(int a, struct linkedlist * list);

void remove_with_char(char *c, struct linkedlist * list);

void list_to_file(struct linkedlist* list, FILE* f);

void printList(struct linkedlist* list);

void removeWithPosF(struct linkedlist* list, long long Lines, long long c);

void removeWithPosB(struct linkedlist* list, long long Lines, long long c);

char copyF(struct linkedlist* list, long long Lines, long long c);

int xis_dir(const char *d);

int pathChecker(char *path, int l, int where);

void char_fixer(char *smt);

void goNextLine(void);

int count_line(FILE* file);

char *rest(int , char*);

char *restWithSp(int i, char *word);

char *restWithSpFixed(int i, char *word);

long long strToNum(char *num);

int whatcommand(char *word);

void checkForAtrs(char *);

void create(char *address, int , int );

void insert(char *path, int l, int where, char * str, long long Line, long long c );

void cat(char *path, int l, int where);

void removeFile(char *path, int l, int where, long long Lines, long long c, int direction, long long size);

void copy(char *path, int l, int where, long long Lines, long long c, int direction, long long size);

int main(){
    mkdir("root");
    do {
            memset(Atrs, 0, sizeof(Atrs));
        memset(whatAtrs, 0, sizeof(whatAtrs));
        struct WWL path, str1;
        path.word=NULL, str1.word=NULL;
        path.length=0, str1.length=0;
        char command[limit]={0};
        scanf("%[^\n]s", command);
        getchar();
        if(command[0]!=0) {
            dastoor = whatcommand(command);
            commandLength = strlen(command);
            checkForAtrs(command);
            switch (dastoor) {
                case -1:
                    printf("invalid command\n");
                    break;
                case 1:
                    //
                    if(whatAtrs[0]){
                        whatAtrs[0]=0;
                        path=pathMaker();
                        create(path.word, path.length, 0);
                        free(path.word);

                    }
                    else
                        printf("invalid command\n");
                    break;
                    //
                case 2:
                    //
                    if(whatAtrs[0] && whatAtrs[1] && whatAtrs[2]){
                        for (int i = 0; i < 3; ++i) {
                            whatAtrs[i]=0;
                        }
                        path=pathMaker();
                        str1=strMaker();
                        insert(path.word, path.length, 0, str1.word, (long long)Atrs[2], (long long)Atrs[3]);
                        free(path.word);
                        free(str1.word);
                    }
                    else
                        printf("invalid command\n");
                    break;
                    //
                case 3:
                    //
                    if(whatAtrs[0]){
                        whatAtrs[2]=0;
                        path=pathMaker();
                        cat(path.word, path.length, 0);
                        printf("\n");
                        free(path.word);
                    }
                    else
                        printf("invalid command\n");
                    break;
                    //
                case 4:
                    //
                    if( whatAtrs[0] && whatAtrs[2] && whatAtrs[3] && whatAtrs[4] ){
                        whatAtrs[0]=false;
                        for (int i = 2; i < 5; ++i) {
                            whatAtrs[i]=false;
                        }
                        path=pathMaker();
                        removeFile(path.word, path.length, 0, (long long)Atrs[2],
                                   (long long)Atrs[3], (long long)Atrs[4], (long long)Atrs[5]);
                        free(path.word);
                    }
                    //
                case 5:
                    if( whatAtrs[0] && whatAtrs[2] && whatAtrs[3] && whatAtrs[4] ){
                        whatAtrs[0]=false;
                        for (int i = 2; i < 5; ++i) {
                            whatAtrs[i]=false;
                        }
                        path=pathMaker();
                        copy(path.word, path.length, 0, (long long)Atrs[2],
                                   (long long)Atrs[3], (long long)Atrs[4], (long long)Atrs[5]);
                        free(path.word);
                    }

                default:
                    break;
            }
        }
    }while(!end);

    return 0;
}

int whatcommand(char *word) {
    if(!(strcmp(word, "quit"))){
        end++;
        return limit;
    }
    int i =0;
    switch(word[i++]){
        case 'c':
            switch (word[i++]) {
                case 'r':
                    if (!(strcmp(rest(i, word), "eate")))
                        return 1;
                case 'a':
                    if(word[i]=='t')
                        return 3;
                case 'o':
                    if(!(strcmp(rest(i, word), "py")))
                        return 5;
                default:
                    return -1;
            }
            break;
        case 'p':
            break;
        case 'r':
            if(!(strcmp(rest(i, word), "emove")))
                return 4;
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
            return -1;

    }
    return -1;
}

void checkForAtrs(char *command){
    char temperory;
    for (int i = 0; i < commandLength; ++i) {
        if(command[i]=='-')
            switch(command[++i]){
                case 'f': {
                    //
                    if(((command[++i]==' ')||(command[i]=='\0')||(command[i]=='\n'))&&((dastoor >= 4) && (dastoor <= 6))){
                        whatAtrs[3]=true;
                        Atrs[4]=((long long)1);
                        break;
                    }
                    char *test = rest(i, command);
                    if((!(strcmp(test, "ile")))&&(dastoor<12)){
                            whatAtrs[0]=1;
                        char* test2;
                            if(*(command+i+4)=='\"')
                                test2= restWithSp(i+4, command);
                            else
                                test2= rest(i+4, command);
                        if (!(isalpha(*test2))) {
                            test2++;
                            test2[strlen(test2)] = '\0';
                        }
                            *Atrs=test2;
                            break;
                        }
                    }
                    //
                    case 's': {
                        //
                        char *test = rest(++i, command);
                        if ((!(strcmp(test, "tr"))) && ((dastoor == 2) || ((dastoor <= 10) && (dastoor >= 8)))) {
                            whatAtrs[1] = 1;
                            char *test2;
                            if (*(command + i + 3) == '\"')
                                test2 = restWithSp(i, command);
                            else
                                test2 = rest(i + 2, command);
                            if (!(isalpha(*test2))) {
                                test2++;
                                test2[strlen(test2)] = '\0';
                            }
                            Atrs[1] = test2;
                            break;
                        } else if ((!(strcmp(test, "ize"))) && ((dastoor >= 4) && (dastoor <= 6))) {
                            whatAtrs[4] = true;
                            i += 4;
                            temperory=command[++i];
                            command[i]='\0';
                            Atrs[5] = strToNum(command + i-1);
                            command[i]=temperory;
                            break;
                        }
                    }
                    //
                    case 'p': {
                    //
                        char *test = rest(++i, command);
                        if((!(strcmp(test, "os")))&&(dastoor==2)||((dastoor<=7)&&(dastoor>=4))){
                            whatAtrs[2]=true;
                            int l=0;
                            char c;
                            i+=3;
                            do{
                                l++;
                                c= command[++i];
                            }while(c != ':');
                            temperory=command[i];
                            command[i]='\0';
                            Atrs[2]=strToNum(command+i - l);
                            Atrs[3]=strToNum(command+i+1);
                            command[i]=temperory;
                            break;
                        }
                    }
                    //
                case 'b':
                    if((command[i+1]==' ')||(command[i+1]==0)&&((dastoor >= 4) && (dastoor <= 6))){
                        whatAtrs[3]=true;
                        Atrs[4]=NULL;
                        break;
                    }


                    default:
                        printf("invalid Atribute!\n");
                        return;
            }
    }
}

void create(char *path, int l, int where){
    int counter=0;
    if(!(isalpha(*path) || counter)){
        if(*path=='\"')
            path[l-1]='\0';
        path++;
        counter++;
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
            if(fopen(path, "r")!=(void *)0){
                printf("file already exists!\n");
                return;
            }
            FILE *s=fopen(path, "w");
            if(s==(void *)0) {
                printf("unexpected error: %s,%d\n", __FUNCTION__, __LINE__);
                return;
            }
            else
                printf("done!\n");
            fclose(s);
        }
        else{
            mkdir(P);
            create(path, l, where+folfile.length);
        }
    }
}

void insert(char *path, int l, int where, char *str, long long int Line, long long int c) {
    if(!pathChecker(path, l, where))
        return;
    FILE *f=fopen(path, "r+");
    if(f==NULL){
        printf("unexpected error: %s,%d\n",__FUNCTION__ ,__LINE__);
        return;
    }
    struct linkedlist *Lines= fileToList(f);
    fseek(f, 0, SEEK_SET);
    add_with_index(Lines, str, strlen(str),Line, c);
    list_to_file(Lines, f);
    fclose(f);
    if(success){
        success=false;
        printf("done!\n");
        return;
    }
    else{
        printf("unexpected error: %s,%d\n",__FUNCTION__ ,__LINE__);
        return;
    }
}

void cat(char *path, int l, int where) {
    if(!pathChecker(path, l, where))
        return;
    FILE * f= fopen(path, "r");
    struct linkedlist* toPrint= fileToList(f);
    printList(toPrint);
}

void removeFile(char *path, int l, int where, long long Lines, long long c, int direction, long long size){
    if(!pathChecker(path, l, where))
        return;
    FILE * f=fopen(path, "r+");
    struct linkedlist* target = fileToList(f);
    if(direction){
        for (int i = 0; i < size; ++i) {
            removeWithPosF(target, Lines, c);
        }
    }
    else{
        for (int i = 0; i < size; ++i) {
            removeWithPosB(target, Lines, c-i);
        }
    }
    fclose(f);
    f= fopen(path, "w");
    fseek(f, 0, SEEK_SET);
    list_to_file(target, f);
    if(success)
        printf("done!\n");
    success=false;
    fclose(f);
}

void copy(char *path, int l, int where, long long int Lines, long long int c, int direction, long long int size) {
    if(!pathChecker(path, l, where))
        return;
    FILE * f=fopen(path, "r");
    struct linkedlist* target = fileToList(f);
    if(!direction){
        for (int i = 0; i < size; ++i) {
            if(c!=0)
                c--;
            else{
                if(Lines==1){
                    printf("reached the beginning!\n");
                    break;
                }
                Lines--;
            }
        }
    }
    clipboard=realloc(clipboard, size+1);
    for (int i = 0; i < size; ++i) {
        clipboard[i]=copyF(target, Lines, c+i);
    }
    clipboard[size]='\0';
    if(success)
        printf("done!\n");
    success=false;
    fclose(f);
//    printf("%s", clipboard);
}

char *rest(int i, char *word){
    int l=0;
    char c;
    do{
        l++;
        c= word[++i];
        if(c=='\\'&&word[i+1]=='n'){
            word[i++]='\n';
            word[i-1]='~';
        }
        if(c=='\\'&&word[i+1]=='\\') {
            word[i++] = '\\';
            word[i - 1] = '~';
        }
    }while(c != ' ' && c!=0 &&c!='\n');
    char *check= malloc(l+1);
    for (int j = 0; j < l; ++j) {
        check[j] = word[j+i-l];
    }
    check[l] = '\0';
    return check;
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
        if(c=='\\'&&word[i+1]=='n'){
            word[++i]='\n';
            word[i-1]='~';
        }
        if(c=='\\'&&word[i+1]=='\\'){
            word[++i]='\\';
            word[i-1]='~';
        }
    }while(c!=0 &&c!='\n' && (c!='\"' || ((word[i+1]!=' ' || word[i+2]!='-')&&(word[i+1]!=0))));
    char *check= calloc(l+1, sizeof(char));
    for (int j = 0; j < l; ++j) {
        if(word[j+i-l]=='\0')
            i++;
        check[j] = word[j+i-l+1];
    }
    check[l-1] = '\0';
    return check;
}

long long strToNum(char *num) {
    num= rest(0 ,num);
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
                return ans;
        }
    }
    return ans;
}

void add_with_index(struct linkedlist *list, char *c, int length ,int l, int index) {
    if(list->death)
        add_with_index(list->next, c, length, l, index);
    if(l==1){
        for (int i = 0; i < list->length; ++i) {
            if(i==index){
                char_fixer(c);
                char *temp= restWithSpFixed(i-2, list->c);
                *((list->c)+i-1)='\0';
                strcat(list->c, c);
                strcat(list->c, temp);
                list->length= strlen(list->c);
                break;
            }
        }
    }
    else
        add_with_index(list->next, c, length,l-1, index);
}

void char_fixer(char *smt) {
    int j=0, i=0;
    char c;
    do {
        if(smt[i]=='~'){
            for (int k = i; k < strlen(smt); ++k) {
                smt[k]=smt[k+1];
            }
        }
        c=smt[i];
        i++;
    } while (c!='\0');
}

struct linkedlist *create_linkedlist(void) {
    struct linkedlist *list1 = (struct linkedlist *)malloc(sizeof(struct linkedlist));
    list1->death= false;
    list1->next =NULL;
    list1->prev =NULL;
    list1->length=0;
    list1->c=NULL;
    return list1;
}

void delete_linkedList(struct linkedlist *list) {
    if(list->next!=(void *)0)
        delete_linkedList(list->next);
    free(list->c);
    free(list);
}

void remove_with_index(int n, struct linkedlist *list) {
    n--;
    if(list->death){
        if(list->next==NULL)
            return;
        remove_with_index(n, list->next);

    }if(n==0)
        list->death= true;
    if(list->next==NULL)
        return;
    else
        remove_with_index(n-1, list->next);
}

void add(struct linkedlist *list, char *c, int l) {
    if(list->death)
        add(list->next, c, l);
    if(list->next==NULL){
        list->length=l;
        list->c=c;
        list->next=(struct linkedlist *) malloc(sizeof(struct linkedlist));
        list->next->next=NULL;
        list->next->prev=list;
        list->next->death= false;
        list->next->c=NULL;
        list->next->length=0;
    }
    else
        add(list->next, c, l);
}

int size(struct linkedlist *list) {
    if(list->death){
        if(list->next==NULL)
            return 0;
        return size( list->next);
    }
    if(list->next==NULL)
        return 1;
    else
        return 1+ size( list->next);

}

char *get(int a, struct linkedlist *list) {
    if(list->death)
        return get(a, list->next);
    if(a==0)
        return list->c;
    else
        return get(a-1, list->next);
}

void remove_with_char(char *c, struct linkedlist *list) {
    if(list->death)
        remove_with_char(c, list->next);
    if(list->c==c)
        list->death= true;

    if(list->next==NULL)
        return;
    else
        remove_with_char(c, list->next);
}

int xis_dir(const char *d) {
    DIR* dir = opendir(d);
    if (dir) {
        return 1;
        closedir(dir);
    } else if (ENOENT == errno) {
        return -1;
    } else {
        return 0;
    }
}

void goNextLine(void) {
    char c;
    do {
        c=getchar();
    } while (c!='\n');
}

int count_line(FILE *file) {
    int l=1;
    int temp;
    do {
        temp= fgetc(file);
        if(temp=='\n')
            l++;
    } while (temp!=EOF);
    return l;
}

void list_to_file(struct linkedlist *list, FILE *f) {
    if(list->death) {
        if(list->next!=(void *)0)
            list_to_file(list->next, f);
        else
            return;
    }
    fputs(list->c, f);
    if(list->next->c!=(void *)0)
        list_to_file(list->next, f);
    else
        fputc('\0', f);
    success=true;
}

struct linkedlist *fileToList(FILE *f) {
    long long L=1;
    struct linkedlist* Lines=create_linkedlist();
    char **giveMeSec= (char**)calloc(count_line(f), sizeof(char *));
    int i=0, len=0;
    int tempchar;
    fseek(f,0 , SEEK_SET);
    giveMeSec[len]= calloc(INT_MAX, sizeof(char));
    do {
        tempchar = giveMeSec[len][i++]= fgetc(f);
        if(tempchar=='\n' || tempchar==EOF){
            giveMeSec[len]=realloc((void *)giveMeSec[len], i);
            if(tempchar==EOF)
                giveMeSec[len][i-1]='\0';
            else
                giveMeSec[len][i]='\0';
            add(Lines, giveMeSec[len++], i);
            if(tempchar!=EOF)
                giveMeSec[len]= malloc(INT_MAX);
            i=0;
        }
    } while (tempchar!=EOF);
    free(giveMeSec);
    return Lines;
}

struct WWL pathMaker(void) {
    int length=0;
    for (int i = 0;*(*(Atrs+0)+i)!='\0'; ++i) {
        length++;
    }
    char *path= calloc(length+1, sizeof(char));
    for (int i = 0; i < length; ++i) {
        path[i]=Atrs[0][i];
    }
    path[length]='\0';
    struct WWL ans;
    ans.word= path;
    ans.length= length;
    return ans;
}

struct WWL strMaker(void) {
    int length2=1;
    for (int i = 1;Atrs[1][i]!='\0'; ++i) {
        length2++;
    }
    char *insertingStr= calloc(length2, sizeof(char));
    for (int i = 0; i <= length2; ++i) {
        insertingStr[i]=Atrs[1][i];
    }
    struct WWL ans;
    ans.word= insertingStr;
    ans.length= length2;
    return ans;
}

int pathChecker(char *path, int l, int where) {
    int counter=0;
    if(!(isalpha(*path) || counter)){
        if(*path=='\"')
            path[l-1]='\0';
        path++;
        counter++;
    }
    struct WWL folfile = restTillBksl(where, path);
    char P[where+folfile.length+1];
    char temp=path[where+folfile.length];
    path[where+folfile.length]='\0';
    strcpy(P, path);
    path[where+folfile.length]=temp;
    if(xis_dir(P)==1){
        return pathChecker(path, l, where+folfile.length);
    }
    else{
        if(l<=where+folfile.length+3){
            FILE *t= fopen(path, "r");
            if(t!=(void *)0){
                fclose(t);
                return 1;
            }
            else{
                printf("file dosen't exist!\n");
                return 0;
            }
        }
        else{
            printf("no such directory!\n");
            return 0;
        }
    }
}

void printList(struct linkedlist *list) {
    if(list->death){
        if(list->next==NULL)
            return;
        printList( list->next);
    }
    if(list->next==NULL)
        return;
    printf("%s", list->c);
    printList( list->next);
}

void removeWithPosF(struct linkedlist* list, long long Lines, long long c){
    if(list->death){
        if(list->next==NULL){
            printf("reached EOF!\n");
            return;
        }
        removeWithPosF(list->next, Lines, c);
    }
    if(Lines==1){
        if(list->length==c) {
            if(list->next==NULL){
                printf("reached EOF!\n");
                return;
            }
            removeWithPosF(list->next, Lines, 0);
        }
        else{
            for (int i = 0; i < list->length; ++i) {
                if(i==c){
                    for (int j = 0; j < list->length-i; ++j) {
                        list->c[i+j]=list->c[i+j+1];
                    }
                    break;
                }
            }
        }
    }
    else{
    if(list->next==NULL){
        printf("reached EOF!\n");
        return;
        }
    removeWithPosF(list->next, Lines-1, c);
    }
}

void removeWithPosB(struct linkedlist* list, long long Lines, long long c){
    if(list->death) {
        if (list->next == NULL) {
            printf("reached EOF!\n");
            return;
        }
        removeWithPosB(list->next, Lines, c);
    }
        if(Lines==1){
        if(-1==c) {
            if(list->prev==NULL){
                printf("reached the beginning!\n");
                return;
            }
            removeWithPosB(list->prev, Lines, list->prev->length-1);
        }
        else{
            for (int i = 0; i < list->length; ++i) {
                if(i==c){
                    for (int j = 0; j < list->length-i; ++j) {
                        list->c[i+j]=list->c[i+j+1];
                    }
                    break;
                }
            }
        }
    }
    else{
        if(list->next==NULL){
            printf("reached EOF!\n");
            return;
        }
        removeWithPosB(list->next, Lines-1, c);
    }
}

char *restWithSpFixed(int i, char *word) {
    int l=0;
    char c;
    do{
        l++;
        c= word[++i];
    }while(c!=0 &&c!='\n' && (c!='\"' || ((word[i+1]!=' ' || word[i+2]!='-')&&(word[i+1]!=0))));
    char *check= calloc(l+1, sizeof(char));
    for (int j = 0; j < l; ++j) {
        if(word[j+i-l+1]=='\0')
            i++;
        check[j] = word[j+i-l+1];
    }
    check[l] = '\0';
    return check;
}

char copyF(struct linkedlist *list, long long int Lines, long long int c) {
    if(list->death){
        if(list->next==NULL){
            printf("reached EOF!\n");
            return '\0';
        }
        return copyF(list->next, Lines, c);
    }
    if(Lines==1){
        if(list->length<=c) {
            if(list->next==NULL){
                printf("reached EOF!\n");
                return '\0';
            }
            return copyF(list->next, Lines, c-list->next->length);
        }
        else{
            for (int i = 0; i < list->length; ++i) {
                if(i==c){
                    return list->c[i];
                }
            }
        }
    }
    else{
        if(list->next==NULL){
            printf("reached EOF!\n");
            return '\0';
        }
        return copyF(list->next, Lines-1, c);
    }
}
