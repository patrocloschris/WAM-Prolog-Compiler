/*List with all the information of program*/


typedef struct dict *dict1;

struct dict{
	char vname[10];/*first name*/
	char nname[10];/*last name*/
	int  depth;		/*function depth*/
	char fsvar[20];	/*array with the functions or other symbols that has the function symbol*/
	int  nofvalues;	/*number of values*/
	int type; /*zero for functional symbol , one for values*/
	dict1 next;
};


