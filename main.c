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
bool whatAtrs[limit]={false},end=false, err[limit]={false}, success=false, wildecard;
long long commandLength;
//Atrs 0= file
//1= str1
//2= pos Line
//3= pos char
//4= backward(0) or forward(1)
//5= size
//6= str2
//7= find->at
//8= depth
//10= num of file
//15
// |
// V
//WhatAtrs 0= file
//1= str1
//2= pos
//3= forward of backward
//4= size
//5= files
//6= find-> count
//7= find-> at
//8= find-> byword
void indenting(char contents[]);








int dastoor=0, wildecount=0;

// n= file addresses

//9= find-> all

//10= depth

struct WWL strMaker2(void);

struct WWL{
    char *word;
    int length;
};

struct WWL restTillBksl(int i, char *word);

struct WWL pathMaker(int );

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

long long get(int a, struct linkedlist * list);

void remove_with_char(char *c, struct linkedlist * list);

void printList(struct linkedlist* list);

void removeWithPosF(struct linkedlist* list, long long Lines, long long c);

void removeWithPosB(struct linkedlist* list, long long Lines, long long c);

char copyF(struct linkedlist* list, long long Lines, long long c);

void list_to_file(struct linkedlist* list, FILE* f);

void listFilesRecursively(char *basePath, int depth);

int xis_dir(const char *d);

int pathChecker(char *path, int l, int where);

void TreeWithDepth(char *Address, int maxdepth,int currentdepth);

void char_fixer(char *smt);

void goNextLine(void);

int count_line(FILE* file);

char *rest(int , char*);

char *restWithSp(int i, char *word);

char *restWithSpFixed(int i, char *word);

void AllTree(char *Address);

void intpos(long long a, struct linkedlist *list){
    Atrs[2]=0;
    Atrs[3]=0;
    while(a>=list->length){
        a-=list->length;
        list=list->next;
        Atrs[2]++;
    }
    Atrs[3]=a;
}

long long strToNum(char *num);

int whatcommand(char *word);

void checkForAtrs(char *);

char *fileToArr(FILE * f);

void create(char *address, int , int );

void insert(char *path, int l, int where, char * str, long long Line, long long c );

void cat(char *path, int l, int where);

void indent(char path[]);

void removeFile(char *path, int l, int where, long long Lines, long long c, int direction, long long size);

void copy(char *path, int l, int where, long long Lines, long long c, int direction, long long size);

void cut(char *path, int l, int where, long long Lines, long long c, int direction, long long size);

void paste(char *path, int l, int where, long long Line, long long c );

void find(char *path, int l, int where, char *str);

void comp(char *path, int l, int where, char *path2, int l2, int where2);

void Tree(char *info);

void replace(char *path, int l, int where, char *str1, char *str2);

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
            wildecard=false;
            wildecount=0;
            dastoor = whatcommand(command);
            commandLength = strlen(command);
            checkForAtrs(command);
            switch (dastoor) {
                case 1:
                    //
                    if(whatAtrs[0]){
                        whatAtrs[0]=0;
                        path=pathMaker(0);
                        create(path.word, path.length, 0);
                        free(path.word);
                        break;
                    }
                    //
                case 2:
                    //
                    if(whatAtrs[0] && whatAtrs[1] && whatAtrs[2]){
                        for (int i = 0; i < 3; ++i) {
                            whatAtrs[i]=0;
                        }
                        path=pathMaker(0);
                        str1=strMaker();
                        insert(path.word, path.length, 0, str1.word, (long long)Atrs[2], (long long)Atrs[3]);
                        free(path.word);
                        free(str1.word);
                        break;
                    }
                    //
                case 3:
                    //
                    if(whatAtrs[0]){
                        whatAtrs[2]=0;
                        path=pathMaker(0);
                        cat(path.word, path.length, 0);
                        printf("\n");
                        free(path.word);
                        break;
                    }
                    //
                case 4:
                    //
                    if( whatAtrs[0] && whatAtrs[2] && whatAtrs[3] && whatAtrs[4] ){
                        whatAtrs[0]=false;
                        for (int i = 2; i < 5; ++i) {
                            whatAtrs[i]=false;
                        }
                        path=pathMaker(0);
                        removeFile(path.word, path.length, 0, (long long)Atrs[2],
                                   (long long)Atrs[3], (long long)Atrs[4], (long long)Atrs[5]);
                        free(path.word);
                        break;
                    }
                    //
                case 5:
                    //
                    if( whatAtrs[0] && whatAtrs[2] && whatAtrs[3] && whatAtrs[4] ){
                        whatAtrs[0]=false;
                        for (int i = 2; i < 5; ++i) {
                            whatAtrs[i]=false;
                        }
                        path=pathMaker(0);
                        copy(path.word, path.length, 0, (long long)Atrs[2],
                                   (long long)Atrs[3], (long long)Atrs[4], (long long)Atrs[5]);
                        free(path.word);
                        break;
                    }
                    //
                case 6:
                    //
                    if( whatAtrs[0] && whatAtrs[2] && whatAtrs[3] && whatAtrs[4] ){
                        whatAtrs[0]=false;
                        for (int i = 2; i < 5; ++i) {
                            whatAtrs[i]=false;
                        }
                        path=pathMaker(0);
                        cut(path.word, path.length, 0, (long long)Atrs[2],
                             (long long)Atrs[3], (long long)Atrs[4], (long long)Atrs[5]);
                        free(path.word);
                        break;
                    }
                    //
                case 7:
                    //
                    if(whatAtrs[0] && whatAtrs[2]){
                        for (int i = 0; i < 3; ++i) {
                            whatAtrs[i]=0;
                        }
                        path=pathMaker(0);
                        paste(path.word, path.length, 0, (long long)Atrs[2], (long long)Atrs[3]);
                        free(path.word);
                        break;
                    }
                    //
                case 8:
                    //
                    if(whatAtrs[0] && whatAtrs[1]) {
                        for (int i = 0; i < 2; ++i) {
                            whatAtrs[i] = 0;
                        }
                        path = pathMaker(0);
                        str1 = strMaker();
                        find(path.word, path.length, 0, str1.word);
                        free(path.word);
                        free(str1.word);
                        break;
                    }
                    //
                case 9:
                    //
                    if(whatAtrs[5]){
                        whatAtrs[0]=0;
                        struct WWL masir[(long long)Atrs[9]];
                        for (int i = 0; i < (long long)Atrs[9]; ++i) {
                            masir[i]= pathMaker(i+15);
                        }
                        comp(masir[0].word,masir[0].length, 0, masir[1].word, masir[1].length, 0);
                        free(masir[0].word);
                        free(masir[1].word);
                        break;
                    }
                    //
                case 10:{
                    //
                    /*if(whatAtrs[10]){
                        whatAtrs[10]=0;*/
                        Tree(command);
                        printf("\n");
                        break;
                    }
                case 11:{
                    path = pathMaker(0);
                    str1 = strMaker();
                    struct WWL str2 = strMaker2();
                    replace(path.word, path.length, 0, str1.word, str2.word);
                }

                default:
                    printf("invalid command\n");
            }
        }
        memset(whatAtrs, 0, sizeof(whatAtrs));
    }while(!end);

    return 0;
}

int whatcommand(char *word){
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
                case 'u':
                    if(word[i]=='t')
                        return 6;
                case 'm':
                    if(!(strcmp(rest(i, word), "pare")))
                        return 9;
                default:
                    return -1;
            }
            break;
        case 'p':
            if(!(strcmp(rest(i, word), "aste")))
                return 7;
            break;
        case 'r':
            if(!(strcmp(rest(i, word), "emove")))
                return 4;
            if(!(strcmp(rest(i, word), "eplace")))
                return 11;
            break;
        case 'i':
            if (!(strcmp(rest(i, word), "nsert")))
                return 2;
        case 'f':
            if (!(strcmp(rest(i, word), "ind")))
                return 8;
        case 'g':
            break;
        case 'u':
            break;
        case 't':
            if (!(strcmp(rest(i, word), "ree")))
                return 10;
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
                    if((!(strcmp(test, "iles")))&&(dastoor==9)){
                        whatAtrs[5]=1;
                        i += 5;
                        temperory=command[++i];
                        long long loopcounter = Atrs[9] =strToNum(command + i-1);
                        command[i]='\0';
                        char* test2[loopcounter];
                        command[i]=temperory;
                        for (int j = 0; j < loopcounter; ++j) {
                            if(*(command+i)=='\"')
                                test2[j]= restWithSp(i, command);
                            else
                                test2[j]= rest(i, command);
                            if (!(isalpha(*test2[j]))) {
                                test2[j]++;
                                test2[j][strlen(test2[j])] = '\0';
                            }
                            Atrs[j+15]=test2[j];
                            i+= strlen(test2[j])+1;
                        }
                        break;
                    }
                    }
                    //
                    case 's': {
                        //
                        char *test = rest(++i, command);
                        if ((!(strcmp(test, "tr"))) && ((dastoor == 2) || ((dastoor <= 11) && (dastoor >= 8)))) {
                            whatAtrs[1] = 1;
                            char *test2;
                            if (*(command + i + 3) == '\"')
                                test2 = restWithSp(i + 2, command);
                            else
                                test2 = rest(i + 2, command);
                            if (!(isalpha(*test2))) {
                                test2++;
                                test2[strlen(test2)] = '\0';
                            }
                            Atrs[1] = test2;
                            break;
                        }
                            if ((!(strcmp(test, "tr2"))) && ((dastoor == 11))) {
                                whatAtrs[1] = 1;
                                char *test2;
                                if (*(command + i + 4) == '\"')
                                    test2 = restWithSp(i + 3, command);
                                else
                                    test2 = rest(i + 3, command);
                                if (!(isalpha(*test2))) {
                                    test2++;
                                    test2[strlen(test2)] = '\0';
                                }
                                Atrs[6] = test2;
                                break;
                            } else if ((!(strcmp(test, "ize"))) && ((dastoor >= 4) && (dastoor <= 6))) {
                                whatAtrs[4] = true;
                                i += 4;
                                temperory = command[++i];
                                command[i] = '\0';
                                Atrs[5] = strToNum(command + i - 1);
                                command[i] = temperory;
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
                    //
                    if((command[i+1]==' ')||(command[i+1]==0)&&((dastoor >= 4) && (dastoor <= 6))){
                        whatAtrs[3]=true;
                        Atrs[4]=NULL;
                        break;
                    }
                    char *test = rest(++i, command);
                    if((!(strcmp(test, "yword")))&&(dastoor==8)){
                        whatAtrs[8]=true;
                        break;
                    }
                    //
            case 'c':{
                test = rest(++i, command);
                if((!(strcmp(test, "ount")))&&(dastoor==8)) {
                    whatAtrs[6] = true;
                    break;
                }
                case 'a':{
                    if((command[++i]=='t')&&(dastoor==8)) {
                        whatAtrs[7] = true;
                        i+=2;
                        temperory=command[++i];
                        command[i]='\0';
                        Atrs[7] = strToNum(command + i-1);
                        command[i]=temperory;
                        break;
                    }
                    test = rest(i, command);
                    if((!(strcmp(test, "ll")))&&(dastoor==8)){
                        whatAtrs[9]=true;
                        break;
                    }
                }
                /*case 'd':
                    test = rest(++i, command);
                    if ((!(strcmp(test, "epth"))) && ((dastoor ==10))) {
                        whatAtrs[10] = true;
                        i += 5;
                        temperory=command[++i];
                        command[i]='\0';
                        Atrs[8] = strToNum(command + i-1);
                        command[i]=temperory;
                        break;
                    }*/
                    default:
                        printf("invalid Atribute!\n");
                        return;
            }
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
                c=get(Lines, target);
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

void cut(char *path, int l, int where, long long int Lines, long long int c, int direction, long long int size) {
    copy(path, l, where, Lines, c, direction, size);
    removeFile(path, l, where, Lines, c, direction, size);
}

void paste(char *path, int l, int where, long long int Line, long long int c) {
    if(clipboard==NULL){
        printf("clipboard is empty!\n");
        return;
    }
    insert(path, l,  where, clipboard, Line, c);
}

void find(char *path, int l, int where, char *str) {
    if(!pathChecker(path, l, where))
        return;
    FILE *f=fopen(path, "r");
    if(f==NULL){
        printf("unexpected error: %s,%d\n",__FUNCTION__ ,__LINE__);
        return;
    }
    char * fileInArr=fileToArr(f);
    int tem=0,cntcnter=0, loop;
    if(wildecard){
        char *wildeParts[wildecount+1], *result[wildecount+1], looptemp;
        int counter=0, len=0;
        bool boroBaadi=true, Found=true;
        wildeParts[0]=str;
        for (int i = 1; i <= wildecount; ++i) {
            do {
                len++;
                looptemp=str[counter++];
            } while(looptemp!='`');
            wildeParts[i-1][len-1]='\0';
            len=0;
            wildeParts[i]=str+counter;
        }
        if(wildeParts[0][0]=='\0')
            result[0]= fileInArr;
        else
            result[0]= strstr(fileInArr, wildeParts[0]);
        if(result[0]==NULL){
            printf("Not found!\n");
            return;
        }
        while(1) {
            for (int i = 1; i < wildecount + 1; i++) {
                if(wildeParts[i][0]=='\0')
                    result[i] = strstr(result[i - 1] + strlen(wildeParts[i - 1]), " ");
                else
                    result[i] = strstr(result[i - 1] + strlen(wildeParts[i - 1]), wildeParts[i]);
                if (result[i] == NULL) {
                    printf("Not found!\n");
                    return;
                }
            }
            for (int i = 1; i < wildecount + 1; ++i) {
                loop=result[i]-result[i-1];
                for (int j = 0; j < loop; ++j) {
                    char hello=*(result[i-1]+strlen(wildeParts[i-1])+j);
                    if (!(isalpha(hello))) {
                        Found = false;
                        break;
                    }
                }
            }
            tem = result[0] - fileInArr;
            if(result[wildecount][strlen(wildeParts[wildecount])]!=' ' && fileInArr[tem-1]!=' ')
                Found= false;
            if (Found) {
                if(whatAtrs[6]){
                    cntcnter++;
                }
                else if(whatAtrs[7]){
                    cntcnter++;
                    if(cntcnter==(long long)Atrs[7]) {
                        printf("char Num: %d\n", tem);
                        return;
                    }
                }
                else if(whatAtrs[8]){
                    *result[wildecount]='\0';
                    char ch= fgetc(f);
                    while(ch!= EOF){
                        ch= fgetc(f);
                        if(ch==' ')
                            cntcnter++;
                    }
                    printf("word num: %d\n", cntcnter);
                    return;
                }
                else if(whatAtrs[9]){
                    tem = result[0] - fileInArr;
                    printf("%d\n", tem);
                }
                else{
                printf("char Num: %d\n", tem);
                return;
                }
            }
            result[0]= strstr(result[0]+ strlen(wildeParts[0])+loop+(wildeParts[0][0]=='\0'), wildeParts[0]);
            if(result[0]==NULL){
                if((!cntcnter)){
                    printf("Not found!\n");
                }
                else if(whatAtrs[9])
                    return;
                else
                    printf("%d\n", cntcnter);
                return;
            }
            Found=true;
        }
    }
    else {
        char *ans = strstr(fileInArr, str);
        while(1) {
            if (ans == NULL) {
                if(cntcnter)
                    printf("%d\n", cntcnter);
                else if(whatAtrs[9])
                    return;
                else
                    printf("Not found!\n");
                return;
            }
            if (whatAtrs[6]) {
                cntcnter++;
            }
            else if(whatAtrs[7]){
                cntcnter++;
                if(cntcnter==(long long)Atrs[7]) {
                    tem = ans - fileInArr;
                    printf("char Num: %d\n", tem);
                    return;
                }
            }
            else if(whatAtrs[8]){
                *ans='\0';
                int fgh=0;
                char ch= fileInArr[fgh++];
                while(ch!= '\0'){
                    ch= fileInArr[fgh++];
                    if(ch==' ')
                        cntcnter++;
                }
                printf("word num: %d\n", cntcnter);
                return;
            }
            else if(whatAtrs[9]){
                tem = ans - fileInArr;
                printf("%d\n", tem);
            }
            else {
                tem = ans - fileInArr;
                printf("char Num: %d\n", tem);
                return;
            }
            ans = strstr(ans+strlen(str), str);
        }
    }
}

void comp(char *path, int l, int where, char *path2, int l2, int where2) {
    int loop, line=1;
    if(!pathChecker(path, l, where))
        return;
    if(!pathChecker(path2, l2, where2))
        return;
    FILE * f=fopen(path, "r");
    FILE * s= fopen(path2, "r");
    struct linkedlist *first = fileToList(f);
    struct linkedlist *second = fileToList(s);
    if(size(first)>size(second))
        loop=size(second)-1;
    else if(size(first)<size(second))
        loop= size(first)-1;
    else
        loop=0;

    if(loop){
        for (int i = 0; i < loop; ++i) {
            if(strcmp(first->c, second->c)){
                printf("====== #%d ======\n", line);
                printf("%s\n", first->c);
                printf("%s\n", second->c);
            }
            line++;
            first=first->next;
            second=second->next;
        }
        if(size(first)>size(second)){
            printf(">>>>> #%d - #%d >>>>>\n", line, size(first));
            for (int i = 0; i < size(first)-line; ++i) {
                printf("%s\n", first->c);
                first=first->next;
            }
        }
        else
            printf("<<<<< #%d - #%d <<<<<\n", line, size(second));
        for (int i = 0; i < size(second)-line+1; ++i) {
            printf("%s\n", second->c);
            second=second->next;
        }
    }
    for (int i = 0; i < size(first)-1; ++i) {
        if(strcmp(first->c, second->c)){
            printf("====== #%d ======\n", line);
            printf("%s\n", first->c);
            printf("%s\n", second->c);
        }
        line++;
        first=first->next;
        second=second->next;
    }

}

void Tree(char *info) {
    char trash[5];
    int depth;
    sscanf(info,"%s %d",trash,&depth);
    if(depth<-1)
        printf("invalid depth\n");
    if(depth==-1)
    {
        AllTree("\Root");
    }
    else
    {
        TreeWithDepth("\Root",depth,0);

    }


}

void replace(char *path, int l, int where, char *str1, char *str2){
    if(!pathChecker(path, l, where))
        return;
    FILE *f=fopen(path, "r");
    if(f==NULL){
        printf("unexpected error: %s,%d\n",__FUNCTION__ ,__LINE__);
        return;
    }
    char * fileInArr=fileToArr(f);
    int tem=0,cntcnter=0, loop;
    if(wildecard){
        char *wildeParts[wildecount+1], *result[wildecount+1], looptemp;
        int counter=0, len=0;
        bool boroBaadi=true, Found=true;
        wildeParts[0]=str1;
        for (int i = 1; i <= wildecount; ++i) {
            do {
                len++;
                looptemp=str1[counter++];
            } while(looptemp!='`');
            wildeParts[i-1][len-1]='\0';
            len=0;
            wildeParts[i]=str1+counter;
        }
        if(wildeParts[0][0]=='\0')
            result[0]= fileInArr;
        else
            result[0]= strstr(fileInArr, wildeParts[0]);
        if(result[0]==NULL){
            printf("Not found!\n");
            return;
        }
        while(1) {
            for (int i = 1; i < wildecount + 1; i++) {
                if(wildeParts[i][0]=='\0')
                    result[i] = strstr(result[i - 1] + strlen(wildeParts[i - 1]), " ");
                else
                    result[i] = strstr(result[i - 1] + strlen(wildeParts[i - 1]), wildeParts[i]);
                if (result[i] == NULL) {
                    printf("Not found!\n");
                    return;
                }
            }
            for (int i = 1; i < wildecount + 1; ++i) {
                loop=result[i]-result[i-1];
                for (int j = 0; j < loop; ++j) {
                    char hello=*(result[i-1]+strlen(wildeParts[i-1])+j);
                    if (!(isalpha(hello))) {
                        Found = false;
                        break;
                    }
                }
            }
            tem = result[0] - fileInArr;
            if(result[wildecount][strlen(wildeParts[wildecount])]!=' ' && fileInArr[tem-1]!=' ')
                Found= false;
            if (Found) {
                tem = result[0] - fileInArr;
                intpos(tem, fileToList(f));
                removeFile(path, l, where, (long long)Atrs[2], (long long)Atrs[3], 1, result[wildecount]-result[0]);
                insert(path, l, where, str2, (long long)Atrs[2], (long long)Atrs[3]);
            }
            result[0]= strstr(result[0]+ strlen(wildeParts[0])+loop+(wildeParts[0][0]=='\0'), wildeParts[0]);
            if(result[0]==NULL){
                return;
            }
            Found=true;
        }
    }
    else {
        char *ans = strstr(fileInArr, str1);
        while (1){
            if (ans == NULL) {
                return;
            }
            tem = ans - fileInArr;
            intpos(tem, fileToList(f));
            removeFile(path, l, where, (long long)Atrs[2], (long long)Atrs[3], 1, strlen(str1));
            insert(path, l, where, str2, (long long)Atrs[2], (long long)Atrs[3]);
            ans = strstr(ans+strlen(str1), str1);
        }
    }
    fclose(f);
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
        if(c=='*'){
            wildecard=true;
            wildecount++;
            word[i]='`';
        }
        if(c=='\\'&&word[i+1]=='n'){
            word[++i]='*';
            word[i-1]='~';
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
        if(c=='*'){
            wildecount++;
            wildecard=true;
            word[i]='`';
        }
        if(c=='\\'&&word[i+1]=='n'){
            word[++i]='*';
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

long long get(int a, struct linkedlist *list) {
    if(list->death)
        return get(a, list->next);
    if(a==0)
        return list->length;
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

struct WWL pathMaker(int l) {
    int length=0;
    for (int i = 0;*(*(Atrs+l)+i)!='\0'; ++i) {
        length++;
    }
    char *path= calloc(length+1, sizeof(char));
    for (int i = 0; i < length; ++i) {
        path[i]=Atrs[l][i];
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
        if(list->length<=c) {
            if(list->next==NULL){
                printf("reached EOF!\n");
                return;
            }
            removeWithPosF(list->next, Lines, c-list->length);
        }
        else{
            for (int i = 0; i < list->length; ++i) {
                if(i==c){
                    for (int j = 0; j < list->length-i; ++j) {
                        list->c[i+j]=list->c[i+j+1];
                    }
                    list->length--;
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
                    list->length--;
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
            return copyF(list->next, Lines, c-list->length);
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

char *fileToArr(FILE *f) {
    int armin, lengthOfFile = -1;
    do {
        lengthOfFile++;
        armin = getc(f);
    } while (armin != EOF);
    fseek(f, 0, SEEK_SET);
    char *fileInArr = calloc(lengthOfFile, sizeof(char));
    for (int i = 0; i < lengthOfFile; ++i) {
        fileInArr[i] = getc(f);
    }
    return fileInArr;
}

void listFilesRecursively(char *basePath, int depth) {
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);
    if (!dir)

        return;
    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            int w = 0;
            strcpy(path, basePath);
            strcat(path, "\\");
            strcat(path, dp->d_name);

            for(int q = 0 ; path[q] != '\0' ;q++)
            {
                if(path[q] == '\\') {
                    w++;
                }
            }
            for(int y = 0 ; y<w-7 ;y++) {
                printf("--");
            }
            printf("%s\n", dp->d_name);
            if(w-6<=depth)
                listFilesRecursively(path, depth);
        }
    }

    closedir(dir);
}

void TreeWithDepth(char *Address, int maxdepth, int currentdepth) {
    DIR *dir;
    struct dirent *entry;
    char FilePath[1000];
    char EntryName[1000];

    dir = opendir(Address);
    if (!dir)
        return;

    while ((entry = readdir(dir)) != NULL) {
        strcpy(EntryName,entry->d_name);
        if (strcmp(entry->d_name, ".") != 0&&strcmp(entry->d_name, "..") != 0) {
            if(currentdepth<=maxdepth) {
                strcpy(FilePath, Address);
                strcat(FilePath, "\\");
                strcat(FilePath, entry->d_name);
                printf("%s\n", FilePath);
                TreeWithDepth(FilePath,maxdepth,currentdepth+1);
            }
        }
    }
    closedir(dir);
}

void AllTree(char *Address) {
    DIR *dir;
    struct dirent *entry;
    char FilePath[1000];
    char EntryName[1000];

    dir = opendir(Address);
    if (!dir)
        return;

    while ((entry = readdir(dir)) != NULL) {
        strcpy(EntryName,entry->d_name);
        if (strcmp(entry->d_name, ".") != 0&&strcmp(entry->d_name, "..") != 0) {
            strcpy(FilePath, Address);
            strcat(FilePath, "\\");
            strcat(FilePath, entry->d_name);
            printf("%s\n", FilePath);
            AllTree(FilePath);
        }
    }
    closedir(dir);
}

struct WWL strMaker2(void) {
    int length2=1;
    for (int i = 1;Atrs[6][i]!='\0'; ++i) {
        length2++;
    }
    char *insertingStr= calloc(length2, sizeof(char));
    for (int i = 0; i <= length2; ++i) {
        insertingStr[i]=Atrs[6][i];
    }
    struct WWL ans;
    ans.word= insertingStr;
    ans.length= length2;
    return ans;
}

void indent(char *path) {
    if (path[0] == '"')
    {
        path[strlen(path) - 1] = '\0';
        memmove(&path[0], &path[2], strlen(path) - 1);
    }
    else if (path[0] == '/')
    {
        memmove(&path[0], &path[1], strlen(path));
    }
    if (fopen(path, "r") == 0)
    {
        printf("File With This Name Doesn't Exist!\n");
        return;
    }
    FILE *file;
    file = fopen(path, "r");
    char c;
    int i = 0;
    char contents[10000];
    while (1)
    {
        c = fgetc(file);
        if (c == EOF)
            break;
        contents[i] = c;
        i++;
        contents[i] = '\0';
    }
    fclose(file);
    indenting(contents);
    file = fopen(path, "w");
    fprintf(file, "%s", contents);
    fclose(file);
}

void indenting(char *contents) {
    for (int i = 0; contents[i] != '\0'; i++)
    {
        if ((contents[i] == ' ' || contents[i] == '\n') && (contents[i - 1] == '{' || contents[i - 1] == '}'))
        {
            memmove(&contents[i], &contents[i + 1], strlen(contents) - i);
            i--;
        }
        else if ((contents[i] == ' ' || contents[i] == '\n') && (contents[i + 1] == '{' || contents[i + 1] == '}'))
        {
            memmove(&contents[i], &contents[i + 1], strlen(contents) - i);
            i -= 2;
        }
    }
    int curlcounter = 0;
    for (int i = 0; contents[i] != '\0'; i++)
    {
        if (contents[i] == '{')
        {
            if (i != 0 && contents[i - 1] != '\n' && contents[i - 1] != ' ')
            {
                memmove(&contents[i + 1], &contents[i], strlen(contents) - i + 1);
                contents[i] = ' ';
                i++;
            }
            curlcounter++;
            if (contents[i + 1] == '}')
            {
                memmove(&contents[4 * (curlcounter - 1) + i + 2], &contents[i + 1], strlen(contents) - i);
                contents[i + 1] = '\n';
                i++;
                for (int j = 0; j < 4 * (curlcounter - 1); j++)
                {
                    contents[i + 1] = ' ';
                    i++;
                }
            }
            else
            {
                memmove(&contents[4 * curlcounter + i + 2], &contents[i + 1], strlen(contents) - i);
                contents[i + 1] = '\n';
                i++;
                for (int j = 0; j < 4 * curlcounter; j++)
                {
                    contents[i + 1] = ' ';
                    i++;
                }
            }
        }
        else if (contents[i] == '}')
        {
            if (contents[i - 1] != '\n' && contents[i - 1] != ' ')
            {
                memmove(&contents[4 * (curlcounter - 1) + i + 1], &contents[i], strlen(contents) - i + 1);
                contents[i] = '\n';
                i++;
                for (int j = 0; j < 4 * (curlcounter - 1); j++)
                {
                    contents[i] = ' ';
                    i++;
                }
            }
            curlcounter--;
            if (contents[i + 1] == '}')
            {
                memmove(&contents[4 * (curlcounter - 1) + i + 2], &contents[i + 1], strlen(contents) - i);
                contents[i + 1] = '\n';
                i++;
                for (int j = 0; j < 4 * (curlcounter - 1); j++)
                {
                    contents[i + 1] = ' ';
                    i++;
                }
            }
            else if (contents[i + 1] == ' ' || contents[i + 1] == '\n' || contents[i + 1] == '\0')
            {
            }
            else
            {
                memmove(&contents[4 * curlcounter + i + 2], &contents[i + 1], strlen(contents) - i);
                contents[i + 1] = '\n';
                i++;
                for (int j = 0; j < 4 * curlcounter; j++)
                {
                    contents[i + 1] = ' ';
                    i++;
                }
            }
        }
    }
}
