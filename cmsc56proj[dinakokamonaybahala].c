#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#define MAX 100

void display(char**,int,int,int);
void path(char**,int,int,int,int);

int main() {
    FILE *ifp;
    char line[MAX];
    char** tab;
    int col,ctr=0,row=0;
    tab=(char**)malloc(MAX*sizeof(char*));
    ifp = fopen("maze.in","r");

    if (ifp == NULL)
        printf("I couldn't open results.dat for writing.\n");

    else{
        while (fgets(line, MAX, ifp) != NULL) {
            col=strlen(line);
            row++;
        }
        for (ctr = 0; ctr<row; ctr++) {
            tab[ctr] = (char *) malloc(MAX * sizeof(**tab));
        }
        ctr=0;
        ifp = fopen("maze.in","r");
        while (fgets(line, MAX, ifp) != NULL){
            strcpy(tab[ctr],line);
            tab[ctr][col]='\0';
            ctr++;
        }
        printf("EMPTY MAZE!\n\n");
        display(tab,row,col,0);
        printf("\n\nSOLVED MAZE!\n\n");
        display(tab,row,col,1);
        fclose(ifp);
    }

    return 0;
}

void display(char **ta,int a,int b,int yy){
    char** taa;
    int ctr=0,x=b,col=0,x1,y1;
    taa=(char**)malloc(MAX*sizeof(char*));
    for (ctr = 0; ctr<a; ctr++) {
        taa[ctr] = (char *) malloc(MAX * sizeof(**taa));
    }

    ctr=0;
    while(ctr<a){
        if(ctr==0){
            printf("%c",201);
            while(x>1){
                printf("%c%c%c%c",205,205,205,203);
                x--;
            }
            printf("%c%c%c%c\n",205,205,205,187);
            x=b;
            printf("%c",186);
            while(x>0){
                if(ta[ctr][col]==';') printf("   %c",186);
                else if(ta[ctr][col]=='x')printf(" %c %c",254,186);
                else if(ta[ctr][col]=='S'){x1=ctr;y1=col;printf(" %c %c",ta[ctr][col],186);}
                else printf(" %c %c",ta[ctr][col],186);
                col++;
                x--;
            }
            printf("\n");
            x=b;col=0;
        }
        else{
            printf("%c",204);
            while(x>1){
                printf("%c%c%c%c",205,205,205,206);
                x--;
            }
            printf("%c%c%c%c\n",205,205,205,185);
            x=b;
            printf("%c",186);
            while(x>0){
                if(ta[ctr][col]==';') printf("   %c",186);
                else if(ta[ctr][col]=='x')printf(" %c %c",254,186);
                else if(ta[ctr][col]=='S'){x1=ctr;y1=col;printf(" %c %c",ta[ctr][col],186);}
                else printf(" %c %c",ta[ctr][col],186);
                col++;
                x--;
            }
            printf("\n");
            x=b;col=0;
        }
        ctr++;
    }
        x=b;col=0;
        printf("%c",200);
        while(x>1){
            printf("%c%c%c%c",205,205,205,202);
            x--;
        }
        printf("%c%c%c%c\n",205,205,205,188);
        x=b;
        printf("\n");
        ctr=0;
        while (ctr<a){
            strcpy(taa[ctr],ta[ctr]);
            taa[ctr][b]='\0';
            ctr++;
        }

        if(yy==0)path(taa,x1,y1,a,b);
        for(ctr=0;ctr<a;ctr++)
            for(x=0;x<b;x++)
                if(taa[ctr][x]=='.'&&ta[ctr][x]!='S') ta[ctr][x]=248;
}

void path(char** ta,int x,int y,int a,int b){

    if(x+1<a&&ta[x+1][y]=='L') {ta[x][y]='.';}
    else
    if(y+1<b&&ta[x][y+1]=='L') {ta[x][y]='.';}
    else
    if(y-1>=0&&ta[x][y-1]=='L') {ta[x][y]='.';}
    else
    if(x-1>=0&&ta[x-1][y]=='L') {ta[x][y]='.';}

    else{

        if(y+1<b&&ta[x][y+1]==';') {
            ta[x][y]='.';
            if(y+2==b&&ta[x-1][y+1]=='x'&&ta[x+1][y+1]=='x'){
                ta[x][y+1]='x';
                return path(ta,x,y,a,b);
            }
            else return path(ta,x,y+1,a,b);
        }

        if(ta[x+1][y]==';'&&x+1<a) {
            ta[x][y]='.';
            if(x+2==a&&ta[x+1][y+1]=='x'&&ta[x+1][y-1]=='x'){
                ta[x+1][y]='x';
                return path(ta,x,y,a,b);
            }
            else return path(ta,x+1,y,a,b);
        }

        if(ta[x][y-1]==';'&&y-1>0) {
            ta[x][y]='.';
            if(y-2==0&&ta[x-1][y-1]=='x'&&ta[x+1][y-1]=='x'){
                ta[x][y-1]='x';
                return path(ta,x,y,a,b);
            }
            else return path(ta,x,y-1,a,b);
        }

        if(ta[x-1][y]==';'&&x-1>0) {
            ta[x][y]='.';
            if(x-2==0&&ta[x-1][y+1]=='x'&&ta[x-1][y-1]=='x'){
                ta[x-1][y]='x';
                return path(ta,x,y,a,b);
            }
            else return path(ta,x-1,y,a,b);
        }
        if(ta[x][y-1]=='.'&&y-1>0){
            ta[x][y]='x';
            return path(ta,x,y-1,a,b);
        }
        if(ta[x-1][y]=='.'&&x-1>0) {
            ta[x][y]='x';
            return path(ta,x-1,y,a,b);
        }
        if(y+1<b&&ta[x][y+1]=='.') {
            ta[x][y]='x';
            return path(ta,x,y+1,a,b);
        }
        if(ta[x+1][y]=='.'&&x+1<a) {
            ta[x][y]='x';
            return path(ta,x+1,y,a,b);

        }
    }
}
