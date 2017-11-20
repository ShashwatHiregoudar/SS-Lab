#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

struct estab
{
char csname[10];
char extsym[10];
int address;
int length;
}es[15];

int main(){
    char statement[50];
    FILE *fp1 = fopen("objectfile.o","r");
    while(strcmp(fgets(statement,444,fp1),"END")!=0){
        if(statement[0]=='H'){
            printf("");
        }

    }
    printf("Enter the location to load program\n");

}