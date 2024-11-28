#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <errno.h>
int main(){

    FILE* fptr;

    fptr=fopen("text.txt","w");
    if(fptr==NULL){
        perror("File open unsuccessful");
        exit(1);
    }
    fputs("C is a fun programming language.\n",fptr);
    fputs("And,I love using C language",fptr);
    
    fptr=fopen("text.txt","r");
    if(fptr==NULL){
        perror("File open unsuccessful");
        exit(1);
    }
    char content[1000];

    fgets(content,1000,fptr);

    printf("The content contained in the file is:%s",content);

    return 0;
}