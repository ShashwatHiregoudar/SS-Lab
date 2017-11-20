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
    FILE *fp1 = fopen("objectfile.o","r");
    
    printf("Enter the location to load program\n");

}