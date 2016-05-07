#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"fcall.h"
#include"interpreter.h"
#include"errors.h"




int fcall(char *fname){

	int flag=0,number1;
	FILE *efp;
	char command[30],buffer[60],function[15];


	efp=fopen(fname,"r");

	if(efp==NULL){
		printf("Wrong filename!!!\n");
		return WRONGINPUT;
	}
	while(!feof(efp)){
		fgets(buffer,60,efp);

		/*looks if is the query or program space*/
		if(flag==0){
			memcpy(command,buffer,3);
			if(strcmp(command,";;;")==0){
				memset(command,'\0',30);
				flag=1;
				continue;
			}
			/*call set_value command*/
			memcpy(command,buffer,9);
			if(strcmp(command,"set_value")==0){
				memcpy(function,&buffer[11],2);
				number1=atoi(function);
				set_value(number1);
				memset(command,'\0',16);
				continue;
			}
			/*call set_variable command*/
			memcpy(command,buffer,12);
			if(strcmp(command,"set_variable")==0){
				memcpy(function,&buffer[14],2);
				number1=atoi(function);
				set_variable(number1);
				memset(command,'\0',30);
				continue;
			}
			/*call put_structure command*/
			memcpy(command,buffer,13);
			if(strcmp(command,"put_structure")==0){
				memcpy(function,&buffer[14],3);
				memset(command,'\0',30);
				memcpy(command,&buffer[19],3);
				number1=atoi(command);
				put_structure(function,number1);
				memset(command,'\0',30);
				continue;
			}
		}
		else{
			/*call get_structure command*/
			memcpy(command,buffer,13);
			if(strcmp(command,"get_structure")==0){
				memcpy(function,&buffer[14],3);
				memset(command,'\0',30);
				memcpy(command,&buffer[19],3);
				number1=atoi(command);
				get_structure(function,number1);
				memset(command,'\0',30);
				continue;
			}
			/*call unify_variable command*/
			memcpy(command,buffer,14);
			if(strcmp(command,"unify_variable")==0){
				memcpy(function,&buffer[16],2);
				number1=atoi(function);
				unify_variable(number1);
				memset(command,'\0',30);
				continue;
			}
			/*call unify_value command*/
			memcpy(command,buffer,11);
			if(strcmp(command,"unify_value")==0){
				memset(command,'\0',30);
				memcpy(function,&buffer[16],2);
				number1=atoi(function);
				unify_value(number1);
				continue;
			}
		}
	}
	check();
	return OK;
}
