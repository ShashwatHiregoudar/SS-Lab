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
struct OPCODES{
    char o[6];
};
typedef struct OPCODES OPCODES;
int optab_size;
int symboltable_size;
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
    while(statement[i]!='\n'){
        char c = statement[i];
        if(statement[i]==' '){
            count++;

        }
        if(statement[i]=='\t'){
            count--;
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
void read_optab(OPTAB *op){
    FILE *fp = fopen("optab.txt","r");
    char statement[10];
    int i=0;
    while(fgets(statement,10,fp)){
        ///printf("\n%s %d\n",statement,no_of_words(statement));
        sscanf(statement,"%s %s",op[i].Operand, op[i].Opcode);
        //printf("\nOperand : %s\nOpcode : %s\n",op[i].Operand, op[i].Opcode);
        i++;
    }
    fclose(fp);
}
void read_symbol_table(SYMBOLTABLE *s){
    FILE *fp = fopen("symboltable.txt","r");
    char ss[15];
    int i=0;
    while(fgets(ss,15,fp)){
        sscanf(ss,"%s %s",s[i].locCTR,s[i].Label);
        i++;
    }
}
void get_opcode(OPTAB *op,char *key,char *value){
    int i;
    for(i=0;i<optab_size;i++){
        if(strcmp(op[i].Operand,key)==0){
            strcpy(value,op[i].Opcode);
        }
    }
}
void get_symbol(SYMBOLTABLE *stab,char *key,char *value){
    int i;
    for(i=0;i<symboltable_size;i++){
        if(strcmp(stab[i].Label,key)==0){
            strcpy(value,stab[i].locCTR);
        }
    }
}
void rev(char *str){
    int i = 0;
    int j = strlen(str) - 1;
    char temp;
    while (i < j) {
       temp = str[i];
       str[i] = str[j];
       str[j] = temp;
       i++;
       j--;
    }
}
int generate_opcodes(OPCODES *opcodes,int opcodes_size,ASMS *asms,int asms_size,OPTAB *otab,SYMBOLTABLE *stab){
    int i,j=0;
    for(i=0;i<asms_size;i++){
        printf("\n");
        if(strcmp(asms[i].Operand,"WORD")==0){
            sscanf(asms[i].Operator,"%s",opcodes[j].o);
            strcat(opcodes[j].o,"00000");
            rev(opcodes[j].o);
            printf("--  word  --\nLoc : %s\nLabel : %s\nOperand : %s\nOperator : %s\n",asms[i].LocCTR,asms[i].Label,asms[i].Operand,asms[i].Operator);
            //opcodes[j].o = strrev(opcodes[j].o);
            printf("opcode : %s\n",opcodes[j].o);
            j++;
            continue;
        }
        if(checking_for_Valid_operand(asms[i].Operand)){
            //printf("Valid : %X %s %s %s\n",LOCATION_COUNTER,asms[i].Label,asms[i].Operand,asms[i].Operator);
            if(asms[i].Operator[0]=='='){
                if(asms[i].Operator[1]=='C'){
                    strcpy(opcodes[j].o,"------");

                    printf("Loc : %s\nLabel : %s\nOperand : %s\nOperator : %s\n",asms[i].LocCTR,asms[i].Label,asms[i].Operand,asms[i].Operator);
                    printf("opcode : ------\n");
                    j++;
                    continue;
                }
                if(asms[i].Operator[1]=='X'){
                    strcpy(opcodes[j].o,"------");

                    printf("Loc : %s\nLabel : %s\nOperand : %s\nOperator : %s\n",asms[i].LocCTR,asms[i].Label,asms[i].Operand,asms[i].Operator);
                    printf("opcode ; ------\n");
                    j++;
                    continue;
                }
            }

            char f2[2],l4[4] = "0000";
            get_opcode(otab,asms[i].Operand,f2);
            get_symbol(stab,asms[i].Operator,l4);
            strcpy(opcodes[j].o,strcat(f2,l4));
            printf("Loc : %s\nLabel : %s\nOperand : %s\nOperator : %s\n",asms[i].LocCTR,asms[i].Label,asms[i].Operand,asms[i].Operator);
            printf("opcode : %s\n",opcodes[j].o);
            j++;

            continue;
        }
        else{
            printf("Loc : %s\nLabel : %s\nOperand : %s\nOperator : %s\n",asms[i].LocCTR,asms[i].Label,asms[i].Operand,asms[i].Operator);
            printf("error\n");
            strcpy(opcodes[j].o,"------");
        }
    }
}

int main(){
    system("cc Pass1.c");
    system("./a.out");
    FILE *fpa = fopen("intermediateFile.txt","r");
    int no_of_lines = no_of_lines_in_file(fpa);
    FILE *fp1 = fopen("intermediateFile.txt","r");
    ASMS asms[no_of_lines];
    char statement[30];
    int i=0;
    while(fgets(statement,50,fp1)){
        if(no_of_words(statement)==4){
            //printf("Statement %d    =    %s\n",i,statement);
            sscanf(statement,"%s %s %s %s", asms[i].LocCTR, asms[i].Label, asms[i].Operand, asms[i].Operator);
            //printf("\nLocctr : %s\nLabel : %s\nOperand : %s\nOperator : %s\n", asms[i].LocCTR, asms[i].Label, asms[i].Operand, asms[i].Operator);
            i++;
        }
        if(no_of_words(statement)==3){
            //printf("Statement %d    =    %s\n",i,statement);
            sscanf(statement,"%s \t %s %s", asms[i].LocCTR, asms[i].Operand, asms[i].Operator);
            strcpy(asms[i].Label,"\t");
            //printf("\nLocctr : %s\nLabel : %s\nOperand : %s\nOperator : %s\n", asms[i].LocCTR, asms[i].Label, asms[i].Operand, asms[i].Operator);
            i++;
        }
        if(no_of_words(statement)==2){
            //printf("Statement %d    =    %s\n",i,statement);
            sscanf(statement,"%s \t %s \t", asms[i].LocCTR, asms[i].Operand);
            strcpy(asms[i].Label,"\t");
            strcpy(asms[i].Operator,"\t");
            //printf("\nLocctr : %s\nLabel : %s\nOperand : %s\nOperator : %s\n", asms[i].LocCTR, asms[i].Label, asms[i].Operand, asms[i].Operator);
            i++;
        }
    }
    ///for reading otpab
    FILE *foptab = fopen("optab.txt","r");
    optab_size = no_of_lines_in_file(foptab);
    OPTAB optab[optab_size];
    read_optab(optab);
    fclose(foptab);
    //printf("\n\n\n\n\n\n");
    ///for reading symboltable
    FILE *fstab = fopen("symboltable.txt","r");
    symboltable_size = no_of_lines_in_file(fstab);
    SYMBOLTABLE stab[symboltable_size];
    read_symbol_table(stab);
    fclose(fstab);
    OPCODES op[no_of_lines];
    generate_opcodes(op,no_of_lines,asms,no_of_lines,optab,stab);
    return 1;
}
