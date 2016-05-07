#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include"compiler.h"
#include"heap.h"
#include"errors.h"


struct map2 {
	char name[10];
	int depth;
};

int compiler(char *buffer,  char *fname, int number){

	int te=0,z,depthmeter=1,i=0,counter=1,k=0,maxdepth=0,length=0,flag=0,l,counter2=0,depth;
	FILE *ofp;
	char name[10],values[50],values2[76],name2[10],map[100][10],map3[100][10];
	dict1 dictionary=NULL,temp,temp1,temp2,temp3,temp4;
	struct map2 map1[100];

	/*find the end of the string and change the last 2 characters to wm etc prolog.pl => prolog.wm*/
	while (fname[te]!='\0'){
			te++;
	}
	fname[te-2]='w';
	fname[te-1]='m';




	/*===========QUERY-PROGRAMM BUFFER COMPILING===================*/

	/*Starts to create the dictionary of values,variables and facts*/
	dictionary=malloc(sizeof(struct dict));
	dictionary->next=NULL;
	temp=dictionary;

	for(te=0;buffer[te]!='\0'&&buffer[te]!='\n';te++){
		/*everytime keeps a depth meter to give the suitable name to each one*/
		if(buffer[te]=='(')
			depthmeter++;
		/*if the read value is an alphabetic character ,starts to finds his name*/
		if(((buffer[te]>='a')&&(buffer[te]<='z'))||((buffer[te]>='A')&&(buffer[te]<='Z'))){
			if(((buffer[te]>='a')&&(buffer[te]<='z'))||((buffer[te]>='A')&&(buffer[te]<='Z'))){
				i=0;
				while(((buffer[te]>='a')&&(buffer[te]<='z'))||((buffer[te]>='A')&&(buffer[te]<='Z'))){
					name[i]=buffer[te];
					te++;
					i++;
				}
				te--;
				name[i]='\0';
			}
			/*we keep one more map to know the characters that we have read and do not puth them into dicitonary*/
			for(l=0;l<(counter-1);l++){
				if((strcmp(map1[l].name,name)==0)){
					flag=1;
					break;
				}
			}
			/*if we don't have read them we puth them into dictionary and initilaze some of their values*/
			if((flag!=1)){
				dictionary->nofvalues=0;
				strcpy(dictionary->vname,name);
				map1[counter-1].name[0]='\0';
				strcpy(map1[counter-1].name,dictionary->vname);
				map1[counter-1].depth=depthmeter;
				dictionary->depth=depthmeter;
				counter++;
				/*type '0'or '3' is for facts*/

				if((buffer[te]>='a')&&(buffer[te]<='z')){
					if((buffer[te+2]>='a')&&(buffer[te+2]<='z'))
						dictionary->type=3;
					else
						dictionary->type=0;

				}
					else
					/*type '1' is for values-variable*/

					dictionary->type=1;


				dictionary->next=malloc(sizeof(struct dict));
				dictionary->next->next=NULL;
				dictionary=dictionary->next;
			}
			else{
				/*if found the same character in a smaller depth that is the previews , it changes it*/
				if(map1[l].depth>depthmeter){
					temp4=temp;
					while(temp4!=NULL){
						if(strcmp(temp4->vname,map1[l].name)==0){
							temp4->depth=depthmeter;
							break;
						}
						temp4=temp4->next;
					}
				}
				/*if the same fact has only another fact in his brackets , we must know that is another fact and we will give in it another value*/
				if((buffer[te+1]=='(')&&(buffer[te+2]>='a'&& buffer[te+2]<='z')&&(buffer[te+3]==')')){
					dictionary->nofvalues=0;
					strcpy(dictionary->vname,name);
					dictionary->depth=depthmeter;
					counter++;
					dictionary->type=3;

					dictionary->next=malloc(sizeof(struct dict));
					dictionary->next->next=NULL;
					dictionary=dictionary->next;
				}
				flag=0;

			}
		}
		if(buffer[te]==')')
			depthmeter--;

	}


	dictionary=temp;
	temp4=temp;


	/*basis of depth we give the right name in each value in the dictionary*/
	/*first we find the maxdepth to know how much we must search*/
	while(temp4!=NULL){
		if(temp4->depth>maxdepth)
			maxdepth=temp4->depth;
		temp4=temp4->next;
	}
	counter=1;
	for(te=1;te<=maxdepth;te++){
		dictionary=temp;
		while(dictionary!=NULL){
			if(dictionary->depth==te){
				sprintf(dictionary->nname,"X%d",counter);
				counter++;
			}
			dictionary=dictionary->next;
		}
	}

	dictionary=temp;



	depthmeter=1;
	/*starts to check what have each fact in it's brackets*/
	for(te=0;((buffer[te]!='\0')&&(buffer[te]!='\n'));te++){

		/*every time it calculate a depthmeter*/
		if(buffer[te]=='(')
			depthmeter++;
		if(buffer[te]==')')
			depthmeter--;
		/*it find a fact*/
		if((buffer[te]>='a')&&(buffer[te]<='z')){
			i=te+2;
			depth=depthmeter+1;
			counter=0;
			values[0]='\0';
			while((buffer[i]!='\0')&&(buffer[i]!='\n')){
				name[0]='\0';

				if(buffer[i]=='('){
					counter++;
					depth++;
				}
				if(buffer[i]==')'){
					counter--;
					depth--;
				}
				/*look for values or fact and push them into "values" array*/
				if((((buffer[i]>='a')&&(buffer[i]<='z'))||((buffer[i]>='A')&&(buffer[i]<='Z')))){

					if((counter==0)&&(depthmeter==(depth-1))) {
							z=0;
							while(((buffer[i]>='a')&&(buffer[i]<='z'))||((buffer[i]>='A')&&(buffer[i]<='Z'))){
									name[z]=buffer[i];
									z++;
									i++;
							}
							i--;
							name[z]='\0';
							if((buffer[i+1]=='(') && (buffer[i+2]>='a' && buffer[i+2]<'z') &&(buffer[i+3]==')')){
								strcat(name,"!");
							}
							strcat(name,",");
							strcat(values,name);
					}
					else{
						if(counter!=0 ){
							if((buffer[i+2]<'a'||buffer[i+2]>'z')&&(buffer[i+1]=='(')&&(depthmeter==depth))
								break;
						}
					}

				}
				i++;
			}
			/*next try to find the new name of the fact that it take*/
			values2[0]='\0';
			temp1=temp;
			z=0;
			name2[z]=buffer[te];

			while(((buffer[te+z+1]>='a')&&(buffer[te+z+1]<='z'))||((buffer[te+z+1]>='A')&&(buffer[te+z+1]<='Z'))){
				z++;
				name2[z]=buffer[te+z];
			}
			name2[z+1]='\0';
			counter2=z=0;
			while(values[z]!='\0'){
				if(values[z]==',')
					counter2++;
				z++;
			}

			if(counter2==1 && values[0]>='a' && values[0] <= 'z'){
				while((temp1!=NULL)){
					if(temp1->type==3 && (strcmp(temp1->vname,name2)==0))
						break;
					temp1=temp1->next;
				}
			}
			else{
				while((temp1!=NULL)&&(strcmp(temp1->vname,name2)!=0)){
					temp1=temp1->next;
				}

			}
			if(temp1==NULL){
				printf("1:Unusual error in list to find the right symbol\n");
				return STRANGERROR;
			}
			/*we found the position of function symbol in dictionary list*/
			/*now we must change the format of symbols in in in function*/
			/*for this element in list we change it's array*/
			counter=0;
			z=0;
			temp2=temp;
			k=0;
			temp1->fsvar[0]='\0';
			name[0]='\0';
			for(z=0;values[z]!='\0';z++){
				if(values[z]!=','){
						name[k]=values[z];
						name[k+1]='\0';
						k++;
				}
				else{
					counter++;
					while((temp2!=NULL)&&(strcmp(temp2->vname,name)!=0))
						temp2=temp2->next;
					if(temp2==NULL){
						temp2=temp;
						name[k-1]='\0';
						while(temp2!=NULL){
							if((temp2->type==3)&&(strcmp(temp2->vname,name)==0))
									break;
							temp2=temp2->next;
						}
					}

					if(temp2==NULL){
						printf("2:Unusual error in list to find the right symbol\n");
						return STRANGERROR;
					}
					else {
						strcat(temp1->fsvar,temp2->nname);
						strcat(temp1->fsvar,",");
						temp2=temp;
						k=0;
					}
				}
			}
			temp1->nofvalues=counter;
		}
	}

	/*compiling dictionary to wam machine*/
	maxdepth=0;
	temp3=temp;
	/*we find again tha maxdepth*/
	while(temp3!=NULL){
		if(temp3->depth>maxdepth)
			maxdepth=temp3->depth;
		temp3=temp3->next;
	}
	if(number==1){
		/*if we have compile a query*/
		/*we create a new document*/
		ofp=fopen(fname,"w");
		if (ofp==NULL){
			printf("No memory to create the compiling file!!!\n");
			return NOMEMORY;
		}
		/*until the depth is more tha zero*/
		while(maxdepth>0){
			temp3=temp;
			while(temp3!=NULL){
				/*if dictionary value has the same depth and is fact  */
				if((temp3->depth==maxdepth)&&(temp3->type==0)){

					map[length][0]='\0';
					strcat(map[length],temp3->nname);
					length++;
					/*we print it*/
					fprintf(ofp,"put_structure %s/%d,%s\n",temp3->vname,temp3->nofvalues,temp3->nname);
					z=0;
					te=0;
					name[0]='\0';
					/*and we print it's values-variables*/
					while(temp3->fsvar[z]!='\0'){
						if(temp3->fsvar[z]==','){
							/*and everytime we check if the value that we print is in a map
							 * (we have the values that we print in there)
							 * if there is , the output is 'set_value'
							 * else is 'set_variable'
							 */
							for(i=0;i<=length;i++){
								if(strcmp(map[i],name)==0){
									flag=1;
									fprintf(ofp,"set_value %s\n",name);
									te=0;
									name[0]='\0';
									break;
								}
							}
							if(flag==0){
								fprintf(ofp,"set_variable %s\n",name);
								te=0;
								map[length][0]='\0';
								strcat(map[length],name);
								length++;
								name[0]='\0';
							}
							flag=0;
						}
						else{
							name[te]=temp3->fsvar[z];
							te++;
						}
						z++;
					}
				}
				temp3=temp3->next;
			}
			maxdepth--;
		}
		fprintf(ofp,";;;\n");
		fclose(ofp);
	}

	if(number==0){
		/*if is programm compile we do the same work but we read in the end of the previews file*/
		ofp=fopen(fname,"a+");
		if (ofp==NULL){
			printf("No memory to create the compiling file!!!\n");
			return NOMEMORY;
		}
		for(l=1;l<=maxdepth;l++){
			temp3=temp;
			while(temp3!=NULL){
				if((temp3->depth==l)&&((temp3->type==0)||(temp3->type==3))){

					map3[length][0]='\0';
					strcat(map3[length],temp3->nname);
					length++;
					fprintf(ofp,"get_structure %s/%d,%s\n",temp3->vname,temp3->nofvalues,temp3->nname);
					z=0;
					te=0;
					name[0]='\0';
					while(temp3->fsvar[z]!='\0'){
						if(temp3->fsvar[z]==','){
							for(i=0;i<=length;i++){
								if(strcmp(map3[i],name)==0){
									flag=1;
									fprintf(ofp,"unify_value %s\n",name);
									te=0;
									name[0]='\0';
									break;
								}
							}
							if(flag==0){
								fprintf(ofp,"unify_variable %s\n",name);
								te=0;
								map3[length][0]='\0';
								strcat(map3[length],name);
								length++;
								name[0]='\0';
							}
							flag=0;
						}
						else{
							name[te]=temp3->fsvar[z];
							te++;
							name[te]='\0';
						}
						z++;
					}
				}
				temp3=temp3->next;
			}
		}
		fclose(ofp);
	}
	return OK;
}

