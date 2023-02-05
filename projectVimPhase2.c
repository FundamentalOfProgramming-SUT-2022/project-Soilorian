#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
//#include <dir.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>
#include <errno.h>
#include <ncurses.h>

#define limit 1000

char *Atrs[limit]={0}, *clipboard= NULL;
bool whatAtrs[limit]={false},end=false, err[limit]={false}, success=false, existFile=false;
long long commandLength;
int dastoor=0, posx=6, posy=0;

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

void doCommand(char *com);

void checkForAtrs(char *command);

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


int main(void){
    initscr();
    start_color();
    noecho();
    keypad(stdscr , TRUE);
    char *name=calloc(limit,sizeof(char));
    strcpy(name, "test");
    char mode[10];
    strcpy(mode, " NORMAL ");
    char *command=calloc(limit, sizeof(char));
    char c='o';
    int i=0, t=0, lin=1, modei=3, saveds=7;
    bool insert=false, visual=false;
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_WHITE);
    init_pair(3, COLOR_BLACK, COLOR_GREEN);
    init_pair(4, COLOR_CYAN, COLOR_BLUE);
    init_pair(5, COLOR_RED, COLOR_YELLOW);
    init_pair(6, COLOR_GREEN, COLOR_WHITE);
    init_pair(7, COLOR_RED, COLOR_WHITE);
    init_pair(8, COLOR_WHITE, COLOR_RED);
    while(c!='q'){
        int WTS=0;
        if(existFile){
            struct WWL fileAddress=pathMaker();
            int temsah;
            FILE *f= fopen(fileAddress.word, "r");
            if(f!=NULL){
            struct linkedlist* things = fileToList(f);
            int lines=0, colus=6;
            fseek(f, 0,SEEK_END);
            int loop=ftell(f);
            fseek(f, 0, SEEK_SET);
            for(int i=0 ; i< loop; i++){
                if(things->death){
                    if(things->next==NULL){
                        break;
                    }
                    t=0;
                    things=things->next;
                }
                temsah=things->c[t++];
                if(temsah=='\n'){
                    if(things->next==NULL){
                        break;
                    }
                    t=0;
                    colus=6;
                    if(things->next==NULL)
                        break;
                    things=things->next;
                    lines++;
                }
                else{
                    mvprintw(lines, colus++, "%c", temsah);
                    refresh();
                    move(0, 6);
                }
            }
            WTS=count_line(f);
            }
            for(int j=0; j<WTS; j++){
                mvprintw(j, 0, "%4d", j+1);
            }
        }
        attron(COLOR_PAIR(1));
        for(int i=WTS; i<LINES-2; i++){
            mvprintw(i ,0 , "~");
        }
        attroff(COLOR_PAIR(1));
        attron(COLOR_PAIR(modei));
        mvprintw(LINES-2, 0, "%s", mode);
        refresh();
        attroff(COLOR_PAIR(modei));
        attron(COLOR_PAIR(saveds));
        if(saveds==7)
            strcat(name, "   -");
        else
            strcat(name, "   +");
        mvprintw(LINES-2, 8, "%s", name);
        attroff(COLOR_PAIR(saveds));
        name[strlen(name)-4]='\0';
        c=getch();
        if(c==':'){
            for(int j=0; j<COLS; j++){
                    mvprintw(LINES-1, j, " ");
                }
            while(c!='\n'){
                command[i++]=c;
                command[i]='\0';
                attron(COLOR_PAIR(2));
                mvprintw(LINES-1, 0,"%s", command);
                refresh();
                attroff(COLOR_PAIR(2));
                c=getch();
            }
            i=0;
            for(int j=0; j<COLS; j++){
                    mvprintw(LINES-1, j, " ");
                }
            checkForAtrs(command+1);
            doCommand(command+1);
                command[0]='\0';
                refresh();
        }
        if(c=='v'){
            modei=4;
            strcpy(mode, " VISUAL ");
        }
        if(c=='m'){
            modei=3;
            strcpy(mode, " NORMAL ");
        }
        if(c=='i'){
            modei=5;
            strcpy(mode, " INSERT ");
            attron(COLOR_PAIR(modei));
            mvprintw(LINES-2, 0, "%s", mode);
            refresh();
            attroff(COLOR_PAIR(modei));
            while(c!=27){
                c=getch();
                if(c=='\n'){
                    posy++;
                    posx=6;
                }
                else
                    posx++;
                mvprintw(posy, posx, "%c", c);
            }
        }
        if(c=='s'){
            saveds=6;
        }
    }
    endwin();
}

void doCommand(char *com){
        char *test= rest(0, com);
        if(!(strcmp(test, "open"))){
            if(whatAtrs[0]){
                whatAtrs[0]=false;
            struct WWL fileAddress=pathMaker();
            if(pathChecker(fileAddress.word, fileAddress.length, 0))
                existFile=true;
                return;
            }
        }
            attron(COLOR_PAIR(8));
            mvprintw(LINES-1, 0,"Invalid command");
            attroff(COLOR_PAIR(8));
            refresh();
    }

void checkForAtrs(char *command){
    char temperory;
    for (int i = 0; i < strlen(command); ++i) {
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
                    attron(COLOR_PAIR(8));
                        mvprintw(LINES-1, 20, "invalid Atribute!");
                        attroff(COLOR_PAIR(8));
                        refresh();
                        return;
            }
    }
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
    for (int i = 0;Atrs[0][i]!='\0'; ++i) {
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
                attron(COLOR_PAIR(7));
                mvprintw(LINES-1, 0,"Wrong answer!\n");
                attroff(COLOR_PAIR(7));
                refresh();
                fclose(t);
                return 1;
            }
            else{
                attron(COLOR_PAIR(7));
                mvprintw(LINES-1, 0,"file dosen't exist!\n");
                attroff(COLOR_PAIR(7));
                refresh();
                return 0;
            }
        }
        else{
            attron(COLOR_PAIR(7));
            mvprintw(LINES-1, 0,"no such directory!\n");
            attroff(COLOR_PAIR(7));
            refresh();
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