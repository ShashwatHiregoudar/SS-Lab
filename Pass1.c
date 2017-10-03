#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
struct ASMS{
    char Label[7];
    char Operand[7];
    char Operator[7];
};
struct symboltable{
    int lno;
    char lab[7];
};
typedef struct symboltable symboltable;
typedef struct ASMS ASMS;
symboltable stab[10];
int stab_size = 0;
int LOCATION_COUNTER = 0;
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
int processing_of_start(ASMS *asms){
    if(strcmp(asms[0].Operand,"START")==0 || strcmp(asms[0].Operand,"start")==0){
        ///printf("We are now going to process start\n");
        ///LOCATION_COUNTER = atoi(asms[0].Operator);
        LOCATION_COUNTER = toDeci(asms[0].Operator,16);
        ///printf("The location counter vale is : %d",LOCATION_COUNTER);
    }
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
int creation_of_symbol_table_array(ASMS *asms,int size){
    int i,j=0;
    for(i=0;i<size;i++){
        if(strcmp(asms[i].Operand,"WORD")==0){
            stab[stab_size].lno = i+1;
            sscanf(asms[i].Label,"%s",stab[stab_size].lab);
            stab_size++;
        }
        if(strcmp(asms[i].Operand,"RESW")==0){
            stab[stab_size].lno = i+1;
            sscanf(asms[i].Label,"%s",stab[stab_size].lab);
            stab_size++;
        }
        if(strcmp(asms[i].Operand,"BYTE")==0){
            stab[stab_size].lno = i+1;
            sscanf(asms[i].Label,"%s",stab[stab_size].lab);
            stab_size++;
        }
        if(strcmp(asms[i].Operand,"RESB")==0){
            stab[stab_size].lno = i+1;
            sscanf(asms[i].Label,"%s",stab[stab_size].lab);
            stab_size++;
        }
    }
    ///Check for repetitions
    char *c;
    FILE *errfile = fopen("ErrorsFile.txt","w+");
    for(;j<stab_size;j++){
        strcpy(c,stab[j].lab);
        int k;
        for(k=j;k<stab_size;k++){
            if(strcmp(stab[k].lab,c)==0 && j != k){
                printf("Repetition occured\n");
                fprintf(errfile,"Repetition : %s  \t  Line No : %d\n",stab[k].lab,stab[k].lno);
            }
        }
    }
    fclose(errfile);
    return 1;
}
int writing_to_intermediate_file(ASMS *asms,int size){
    FILE *fp2 = fopen("intermediateFile.txt","w+");
    FILE *symfile = fopen("symboltable.txt","w+");
    FILE *errfile = fopen("ErrorsFile.txt","a");
    int i=0;
    symboltable symtbl[10];
    int j=0;
    //printf("\n\nOk now we are writing to the file\n\n");
    for(i=0;i<size;i++){
        char *label = asms[i].Label;
        char *operand = asms[i].Operand;
        char *opperator = asms[i].Operator;
        int locctr = LOCATION_COUNTER;
        if(strcmp(asms[i].Operand,"START")==0){
            //printf("START : %X %s %s %s\n",LOCATION_COUNTER,asms[i].Label,asms[i].Operand,asms[i].Operator);
            fprintf(fp2,"%X  %s %s %s\n",LOCATION_COUNTER,asms[i].Label,asms[i].Operand,asms[i].Operator);
            LOCATION_COUNTER+=0;
            continue;
        }
        if(strcmp(asms[i].Operand,"END")==0){
            //printf("END : %X %s %s %s\n",LOCATION_COUNTER,asms[i].Label,asms[i].Operand,asms[i].Operator);
            fprintf(fp2,"%X %s %s %s\n",LOCATION_COUNTER,asms[i].Label,asms[i].Operand,asms[i].Operator);
            LOCATION_COUNTER+=0;
            continue;
        }
        if(checking_for_Valid_operand(asms[i].Operand)){
            //printf("Valid : %X %s %s %s\n",LOCATION_COUNTER,asms[i].Label,asms[i].Operand,asms[i].Operator);
            if(asms[i].Operator[0]=='='){
                if(asms[i].Operator[1]=='C'){
                    fprintf(fp2,"%X %s %s %s\n",LOCATION_COUNTER,asms[i].Label,asms[i].Operand,asms[i].Operator);
                    LOCATION_COUNTER+=strlen(asms[i].Operator)-3;
                    continue;
                }
                else if(asms[i].Operator[1]=='X'){
                    fprintf(fp2,"%X %s %s %s\n",LOCATION_COUNTER,asms[i].Label,asms[i].Operand,asms[i].Operator);
                    LOCATION_COUNTER+=(strlen(asms[i].Operator)-3)/2;
                    continue;
                }
            }

            fprintf(fp2,"%X %s %s %s\n",LOCATION_COUNTER,asms[i].Label,asms[i].Operand,asms[i].Operator);
            LOCATION_COUNTER+=3;
            continue;
        }
        if(strcmp(asms[i].Operand,"WORD")==0){
            //printf("WORD : %X %s %s %s\n",LOCATION_COUNTER,asms[i].Label,asms[i].Operand,asms[i].Operator);
            fprintf(fp2,"%X  %s %s %s\n",LOCATION_COUNTER,asms[i].Label,asms[i].Operand,asms[i].Operator);
            fprintf(symfile,"%X %s\n",LOCATION_COUNTER,asms[i].Label);
            LOCATION_COUNTER+=3;
            continue;
        }
        if(strcmp(asms[i].Operand,"BYTE")==0){
            //printf("RESW : %X %s %s %s\n",LOCATION_COUNTER,asms[i].Label,asms[i].Operand,asms[i].Operator);
            fprintf(fp2,"%X %s %s %s\n",LOCATION_COUNTER,asms[i].Label,asms[i].Operand,asms[i].Operator);
            fprintf(symfile,"%X %s\n",LOCATION_COUNTER,asms[i].Label);
            LOCATION_COUNTER+=1;
        }   
        if(strcmp(asms[i].Operand,"RESW")==0){
            //printf("RESW : %X %s %s %s\n",LOCATION_COUNTER,asms[i].Label,asms[i].Operand,asms[i].Operator);
            fprintf(fp2,"%X %s %s %s\n",LOCATION_COUNTER,asms[i].Label,asms[i].Operand,asms[i].Operator);
            fprintf(symfile,"%X %s\n",LOCATION_COUNTER,asms[i].Label);
            LOCATION_COUNTER+=3*atoi(asms[i].Operator);
            continue;
        }
        if(strcmp(asms[i].Operand,"RESB")==0){
            //printf("RESB : %X %s %s %s\n",LOCATION_COUNTER,asms[i].Label,asms[i].Operand,asms[i].Operator);
            fprintf(fp2,"%X %s %s %s\n",LOCATION_COUNTER,asms[i].Label,asms[i].Operand,asms[i].Operator);
            fprintf(symfile,"%X %s\n",LOCATION_COUNTER,asms[i].Label);
            LOCATION_COUNTER+=atoi(asms[i].Operator);
            continue;
        }
        else{
            //printf("ELSE : %X %s %s %s\n",LOCATION_COUNTER,asms[i].Label,asms[i].Operand,asms[i].Operator);
            fprintf(fp2,"%X %s %s %s\n",LOCATION_COUNTER,asms[i].Label,asms[i].Operand,asms[i].Operator);
            fprintf(errfile,"Invalid Operation : %X %s %s %s\t at line no %d\n",LOCATION_COUNTER,asms[i].Label,asms[i].Operand,asms[i].Operator,(i+1));
            LOCATION_COUNTER+=1;
            continue;
        }
    }
}
int main(){
    FILE *fp1 = fopen("input.txt","r");
    char statement[444];
    int no_of_lines = no_of_lines_in_file(fp1);
    fp1 = fopen("input.txt","r");
    ASMS asms[no_of_lines];
    int i=0;
    while(fgets(statement,444,fp1)){
        if(no_of_words(statement)==3){
            //printf("Statement %d    =    %s\n",i,statement);
            sscanf(statement,"%s %s %s", asms[i].Label, asms[i].Operand, asms[i].Operator);
        }
        if(no_of_words(statement)==2){
            //printf("Statement %d    =    %s\n",i,statement);
            sscanf(statement,"%s %s", asms[i].Operand, asms[i].Operator);
            strcpy(asms[i].Label,"     ");
        }
        if(no_of_words(statement)==1){
            //printf("Statement %d    =    %s\n",i,statement);
            sscanf(statement,"%s", asms[i].Operand);
            strcpy(asms[i].Label,"     ");
            strcpy(asms[i].Operator,"     ");
        }
        i++;
    }
    processing_of_start(asms);
    creation_of_symbol_table_array(asms,no_of_lines);
    writing_to_intermediate_file(asms,no_of_lines);
    /*
    for(i=0;i<no_of_lines;i++){
        printf(" ---------------------Statement %d -----------------------\n",i);
        printf("The label is : %s\n",asms[i].Label);
        printf("The operand is : %s\n",asms[i].Operand);
        printf("The operator is : %s\n",asms[i].Operator);
    }*/
    return 1;
}
