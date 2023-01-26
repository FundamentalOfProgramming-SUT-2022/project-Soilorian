#include <string.h>
#include <stdio.h>
#include <dir.h>
#include <stdlib.h>
#include <dirent.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>

#define limit 1000

char *Atrs[limit]={0};
bool whatAtrs[limit]={false},end=false, err[limit]={false};
long long commandLength;
int dastoor=0;

//Atrs 0= file
//1= str
//2= pos Line
//3= pos char

struct WWL{
    char *word;
    int length;
};

struct linkedlist{
    char *c;
    bool death;
    int length;
    struct linkedlist* next;
    struct linkedlist* prev;
};

void char_fixer(char *smt);

struct linkedlist* create_linkedlist(void);

void delete_linkedList(struct linkedlist *list);

void remove_with_index(int n, struct linkedlist * list);

void add(struct linkedlist* list, char *c, int l);

void add_with_index(struct linkedlist* list, char *c, int l, int index);

int size(struct linkedlist *list);

char *get(int a, struct linkedlist * list);

void remove_with_char(char *c, struct linkedlist * list);
/* test that dir exists (1 success, -1 does not exist, -2 not dir) */
int xis_dir (const char *d);

void goNextLine(void);

int count_line(FILE* file);

char *rest(int , char*);

void checkForAtrs(char *);

int whatcommand(char *word);

struct WWL restTillBksl(int i, char *word);

void create(char *address, int , int );

char *restWithSp(int i, char *word);

long long strToNum(char *num);

void insert(char *path, int l, int where, char * str, long long Line, long long c );

int main(){
    mkdir("root");
    do {
            memset(Atrs, 0, sizeof(Atrs));
        memset(whatAtrs, 0, sizeof(whatAtrs));

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
                    if(whatAtrs[0]){
                        whatAtrs[0]=0;
                        int length=0;
                        for (int i = 0;*(*(Atrs+0)+i)!='\0'; ++i) {
                            length++;
                        }
                        char path[length];
                        for (int i = 0; i < length; ++i) {
                            path[i]=Atrs[0][i];
                        }
                        create(path, length, 0);
                    }
                    else
                        printf("invalid command\n");
                    break;
                case 2:
                    if(whatAtrs[0] && whatAtrs[1] && whatAtrs[2]){
                        for (int i = 0; i < 3; ++i) {
                            whatAtrs[i]=0;
                        }
                        int length=0;
                        for (int i = 0;Atrs[0][i]!='\0'; ++i) {
                            length++;
                        }
                        char path[length];
                        for (int i = 0; i < length; ++i) {
                            path[i]=Atrs[0][i];
                        }
                        int length2=1;
                        for (int i = 1;Atrs[1][i]!='\0'; ++i) {
                            length2++;
                        }
                        char insertingStr[length2];
                        for (int i = 0; i <= length2; ++i) {
                            insertingStr[i]=Atrs[1][i];
                        }
                        insert(path, length, 0, insertingStr, (long long)Atrs[2], (long long)Atrs[3]);
                    }
                    else
                        printf("invalid command\n");
                    break;
                default:
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
        if(c=='\\'&&word[i+1]=='n'){
            word[i++]='\n';
            word[i-2]='~';
        }
        if(c=='\\'&&word[i+1]=='\\') {
            word[i++] = '\\';
            word[i - 2] = '~';
        }
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
    return -1;
}

void checkForAtrs(char *command){
    for (int i = 0; i < commandLength; ++i) {
        if(command[i]=='-')
            switch(command[++i]){
            case 'f': {
                char *test = rest(++i, command);
                if((!(strcmp(test, "ile")))&&(dastoor<12)){
                        whatAtrs[0]=1;
                    char* test2;
                        if(*(command+i+4)=='\"')
                            test2= restWithSp(i+4, command);
                        else
                            test2= rest(i+4, command);
                        *Atrs=test2;
                    }
                }
                    break;
                case 's': {
                    char *test = rest(++i, command);
                    if((!(strcmp(test, "tr")))&&((dastoor=2)||((dastoor<=10)&&(dastoor>=8)))){
                        whatAtrs[1]=1;
                        char* test2;
                        if(*(command+i+3)=='\"')
                            test2= restWithSp(i+3, command);
                        else
                            test2= rest(i+3, command);
                        Atrs[1]=test2;
                    }
                }
                    break;
                case 'p': {
                    whatAtrs[2]=true;
                    char *test = rest(++i, command);
                    if((!(strcmp(test, "os")))&&(dastoor=2)||((dastoor<=7)&&(dastoor>=4))){
                        int l=0;
                        char c;
                        i+=3;
                        do{
                            l++;
                            c= command[++i];
                        }while(c != ':');
                        command[i]='\0';
                        long long L=strToNum(command+i - l);
                        long long C=strToNum(command+i+1);
                        Atrs[2]=L;
                        Atrs[3]=C;
                    }
                }
                    break;
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
        path[l-2]='\0';
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
            word[i++]='\n';
            word[i-2]='~';
        }
        if(c=='\\'&&word[i+1]=='\\'){
            word[i++]='\\';
            word[i-2]='~';
        }
    }while(c!=0 &&c!='\n' && (c!=' ' || word[i+1]!='-'));
    char *check= malloc(l+1);
    for (int j = 0; j < l; ++j) {
        if(word[j+i-l]=='\0')
            i++;
        check[j] = word[j+i-l];
    }
    check[l] = '\0';
    return check;
}

long long strToNum(char *num) {
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
    return ans;
}

void insert(char *path, int l, int where, char *str, long long int Line, long long int c) {
    if(!(isalpha(*path))){
        path++;
        path[l-2]='\0';
    }
    struct WWL folfile = restTillBksl(where, path);
    char P[where+folfile.length+1];
    char temp=path[where+folfile.length];
    path[where+folfile.length]='\0';
    strcpy(P, path);
    path[where+folfile.length]=temp;
    if(xis_dir(P)==1){
        insert(path, l, where+folfile.length, str, Line, c);
    }
    else if(xis_dir(folfile.word)==-2){
        printf("file already exists!\n");
    }
    else if(l<=where+folfile.length+3){

            if(fopen(path, "r")==(void *)0){
                printf("file doesn't exist!\n");
                return;
            }
            FILE *f=fopen(path, "r+");
            char buff;
            long long L=1;
            bool success=false;
            struct linkedlist* Lines=create_linkedlist();
            char **giveMeSec= (char**)malloc(count_line(f) * sizeof(char *));
            int i=0, len=0;
        char tempchar;
            do {
                tempchar = giveMeSec[len][i++]= fgetc(f);
                if(tempchar=='\n' || tempchar!=EOF){
                    realloc((void *)giveMeSec[len], i);
                    add(Lines, giveMeSec[len++], i);
                    i=0;
                }
            } while (tempchar!=EOF);


        fclose(f);
            if(success){
                printf("done!\n");
                return;
            }
            else{
                printf("unexpected error: %s,%d\n",__FUNCTION__ ,__LINE__);
                return;
            }
        }
    else{
        printf("Invalid address!\n");
        return;
    }
}

void add_with_index(struct linkedlist *list, char *c, int l, int index) {
    if(list->death)
        add_with_index(list->next, c, l, index);
    if(l==1){
        for (int i = 0; i < list->length; ++i) {
            if(i==index){
                char_fixer(c);
                char *temp= restWithSp(i, list->c);
                *((list->c)+i)='\0';
                strcat(list->c, c);
                strcat(list->c, temp);
            }
        }
    }
    else
        add_with_index(list->next, c, l-1, index);
}

void char_fixer(char *smt) {
    int j=0, i=0;
    char c;
    do {
        if(smt[i]=='~')
            j++;
        c=smt[i]=smt[i+j];
        i++;
    } while (c!='\0');
}

struct linkedlist *create_linkedlist(void) {
    struct linkedlist *list1 = (struct linkedlist *)malloc(sizeof(struct linkedlist));
    list1->death= false;
    list1->next =NULL;
    list1->prev =NULL;
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

void goNextLine(void) {
    char c;
    do {
        c=getchar();
    } while (c!='\n');
}

int count_line(FILE *file) {
    int l=1;
    char temp;
    do {
        temp= fgetc(file);
        if(temp=='\n')
            l++;
    } while (temp!=EOF);
    return l;
}

void list_to_file(struct linkedlist* list, )