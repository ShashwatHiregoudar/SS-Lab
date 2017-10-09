#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
struct ASMS{
    char LocCTR[5];
    char Label[7];
    char Operand[7];
    char Operator[7];
};
typedef struct ASMS ASMS;
struct SYMBOLTABLE{
    char locCTR[5];
    char Label[7];
};
typedef struct SYMBOLTABLE SYMBOLTABLE;
struct OPTAB{
    char Operand[7];
    char Opcode[3];    
};
typedef struct OPTAB OPTAB;

int val(char c){
    if (c >= '0' && c <= '9')
        return (int)c - '0';
    else
        return (int)c - 'A' + 10;
}
int toDeci(char *str, int base){
    int len = strlen(str);
    int power = 1;
    int num = 0;
    int i;
    for (i = len - 1; i >= 0; i--)
    {
        if (val(str[i]) >= base)
        {
           printf("Invalid Number");
           return -1;
        }
        num += val(str[i]) * power;
        power = power * base;
    }
    return num;
}
int no_of_words(char *statement){
    int i=0;
    int count=0;
    char c;
    while(statement[i]!='\n'){
        if(statement[i]==' '){
            count++;
        }
        i++;
    }
    return ++count;
}
int no_of_lines_in_file(FILE *fp){
    int count=0;
    char ss[66];
    while(fgets(ss,55,fp)){
        count++;
    }
    return count;
}
int checking_for_Valid_operand(char *op){
    FILE *fp = fopen("optab.txt","r");
    char statement[15];
    char a[8],b[8];
    while(fgets(statement,15,fp)){
        sscanf(statement,"%s %s",a,b);
        if(strcmp(a,op)==0){
            return 1;
        }
    }
    return 0;
}
int main(){
    /*
        FILE *fp1 = fopen("intermediateFile.txt","r");
        int no_of_lines = no_of_lines_in_file(fp1);
        FILE *fp1 = fopen("intermediateFile.txt","r");
        ASMS asms[no_of_lines];
        char statement[20];
        while(fgets(statement,20,fp1)){
            if(no_of_words(statement)==4){
                //printf("Statement %d    =    %s\n",i,statement);
                sscanf(statement,"%s %s %s %s", asms[i].LocCTR, asms[i].Label, asms[i].Operand, asms[i].Operator);
            }
            if(no_of_words(statement)==3){
                //printf("Statement %d    =    %s\n",i,statement);
                sscanf(statement,"%s       %s %s", asms[i].LocCTR, asms[i].Operand, asms[i].Operator);
                strcpy(asms[i].Label,"     ");
            }
            if(no_of_words(statement)==2){
                //printf("Statement %d    =    %s\n",i,statement);
                sscanf(statement,"%s       %s       ", asms[i].LocCTR, asms[i].Operand);
                strcpy(asms[i].Label,"     ");
                strcpy(asms[i].Operator,"     ");
            }
        }
*/
    FILE *fp1 = fopen("intermediateFile.txt","r");
    char statement[35];
    while(fgets(statement,35,fp1)){
        printf("%s",statement);
        int x = no_of_words(statement);
        printf("%d\n",x);
    }
    return 1;
}