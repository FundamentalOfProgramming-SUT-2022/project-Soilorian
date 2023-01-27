#include <stdio.h>
#include <string.h>


int main() {
    int d;
    scanf("%d", &d);
    for (int i = 0; i < d; ++i) {
        char buff[1000], buff2[1000];
        scanf("%s", buff);
        strcpy(buff2, buff);
        strcat(buff2, ".html");
        strcat(buff, ".txt");
        FILE *f= fopen(buff, "r+");
        fseek(f, 0, SEEK_SET);
        char buffstr[1000000], buffstr2[1000000]={"<!DOCTYPE html>\n"};
        int z=-1;
        do {
            buffstr[++z]= fgetc(f);
        } while (buffstr[z]!=EOF);
        buffstr[z]='\0';
        strcat(buffstr2, buffstr);
        FILE *ans= fopen(buff2, "w");
        fprintf(ans, "%s", buffstr2);
        fclose(f);
        fclose(ans);
        remove(buff);
    }
}

