#include<stdio.h>
#include<stdlib.h>
#include"analysers.h"
#include"compiler.h"
#include"errors.h"
#include"fcall.h"



int main(void){

	char fname[100],buffer[100],buffer1[100],answer[3];
	FILE *ifp;

	printf("Source code file to open?\n");
	scanf("%s",fname);

	/*Opens the source file and checks if it is right*/
	ifp=fopen(fname,"r");
	if (ifp==NULL){
		printf("Wrong filename!!!\n");
		return WRONGINPUT;
	}

	/*Read the program in a buffer*/
	/*for more lines it we must fix it*/
	fgets(buffer,100,ifp);
	fclose(ifp);
	if(analysers(buffer,0)!=0){
		/*"0" is for program buffer*/
		printf("You have wrongs\n");
		return SERROR;

	}

	printf("No errors found!!\n");
	printf("Give query\n");
	getchar();
	fgets(buffer1,100,stdin);

	if(analysers(buffer1,1)!=0){
		/*"1" is for query buffer*/
		printf("You have wrongs\n");
		return SERROR;

	}

	printf("No errors found!!\n");
	printf("Compiling...\n");

	/*compiling*/
	if(compiler(buffer1,fname,1)==0)
		printf("Query compile complete well!!\n");
	else{
		printf("Query compile had problems\n");
		return COMPILINGERROR;
	}
	if(compiler(buffer,fname,0)==0)
		printf("Program compile complete well!!\n");
	else{
		printf("Program compile had problems\n");
		return COMPILINGERROR;
	}

	/*runs if the user whant the interpreter*/
	printf("Do you want to run the execute program?[y/n] \n");
	scanf("%s",answer);
	if(strcmp(answer,"y")==0)
		fcall(fname);


	/*thanks message :)*/
	printf("Thanks for using!!!\n");
	return OK;

}
