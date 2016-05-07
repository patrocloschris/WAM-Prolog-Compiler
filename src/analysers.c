#include<stdio.h>
#include"errors.h"
#include"analysers.h"






/*Analyzer checks for mistakes in the source program or the query and returns a negative number if there is
 * or zero if it's OK!!!
 * The mistakes that checks is:
 * more brackets
 * none right symbols
 * right functional form
 * every sentence ends with "."
 * checks the length of the program or query
 * and checks if the first symbol is a functional symbol
 */





int analysers(char *buffer,int number){

	int i,calc1=0,calc2=0,flag=0,flag2=0;


	for(i=0;(buffer[i]!='\0') && (buffer[i]!='\n');i++){

		if(number==1){
			if(flag==1){
				if((buffer[i]=='('))
					flag=0;
				else{
					if(buffer[i+1]<'a'||buffer[i+1]>'z' ){
						printf("Wrong function format\n");
						return SYNTACT;
					}
				}
			}
		}
		if(buffer[i]=='(')
			calc1++;
		if(buffer[i]==')')
			calc2++;

		if((buffer[i]<'a' || buffer[i]>'z') && (buffer[i]<'A' || buffer[i]>'Z') && buffer[i]!='(' && buffer[i] != ')' && buffer[i]!= ',' && buffer[i]!='\t' && buffer[i]!= '.' && buffer[i]!= ' '){
			printf("Unknown Symbols\n");
			return SYNTACT;
		}
		if(((buffer[i]>='a') && (buffer[i]<='z'))||((buffer[i]>='A') && (buffer[i]<='Z'))){
			flag2++;
			if(((buffer[i]>='A') && (buffer[i]<='Z'))&&flag2==1){
				/*it the first symbol and it's not function symbol*/
				printf("Check your first symbol\n");
				return SYMBOLERROR;
			}

		}
		if((buffer[i]>='a') && (buffer[i]<='z')){
				flag++;
		}
	}
	if(i<=4){
		printf("Very short program or query\n");
		return SHORTERROR;
	}
	if(buffer[i-1]!='.'){
		printf("Sentence does not end with ""."" \n");
		return SYNTACT;
	}


	if(calc1!=calc2){
		printf("number of brackets is not right\n");
		return SYNTACT;
	}
	return OK;


}
