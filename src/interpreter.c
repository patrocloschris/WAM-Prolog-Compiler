#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "interpreter.h"



struct heap h[100];
struct x n[100];
int heapc = 0;
char mode[4];
int  S, fail;
struct stack PDL;
int ft = 1;

void put_structure(char *function, int xi){
    char tx[4];
    strcpy(h[heapc].s1, "STR");
    sprintf(tx, "%d", heapc + 1);
    strcpy(h[heapc].s2, tx);
    h[heapc].totals = 2;
    strcpy(h[heapc + 1].s1, function);
    h[heapc + 1].totals = 1;
    strcpy(n[xi - 1].value1, h[heapc].s1);
    strcpy(n[xi - 1].value2, h[heapc].s2);
    n[xi - 1].ok = 1;
    heapc += 2;
}


void set_variable(int xi){
    char th[4];
    sprintf(th, "%d", heapc);
    strcpy(h[heapc].s1, "REF");
    strcpy(h[heapc].s2, th);
    h[heapc].totals = 2;
    strcpy(n[xi - 1].value1, h[heapc].s1);
    strcpy(n[xi - 1].value2, h[heapc].s2);
    n[xi - 1].ok = 1;
    heapc++;
}

void set_value(int xi) {
    strcpy(h[heapc].s1, n[xi - 1].value1);
    strcpy(h[heapc].s2, n[xi - 1].value2);
    h[heapc].totals = 2;
    heapc++;
}

int deref(int xi) {
    char tag[4];
    char value[4];
    strcpy(tag, h[xi].s1);
    strcpy(value, h[xi].s2);
    if ((strcmp(tag, "REF") == 0) && (atoi(value) != xi)) {
	return deref(atoi(value));
    } else {
	return xi;
    }
}

void unify(int xi, int s) {
    int  i, d1, d2;
    char t1[4];
    char u1[4];
    char t2[4];
    char u2[4];
    char tx[4];
    char function1[4];
    char function2[4];
    char n1[4];
    char n2[4];
    if (ft == 1) {
	ft = 0;
	PDL.current_pos = 0;
    }
    PDL.st[PDL.current_pos] = xi;
    PDL.current_pos++;
    PDL.st[PDL.current_pos] = s;
    PDL.current_pos++;
    fail = 0;
    while (PDL.current_pos != 0 && !fail) {
	d1 = deref(PDL.st[PDL.current_pos]);
	PDL.current_pos--;
	d2 = deref(PDL.st[PDL.current_pos]);
	PDL.current_pos--;
	if (d1 != d2) {
	    strcpy(t1, h[d1].s1);
	    strcpy(u1, h[d1].s2);
	    strcpy(t2, h[d2].s1);
	    strcpy(u2, h[d2].s2);
	    if ((strcmp(t1, "REF") == 0) || (strcmp(t2, "REF") == 0)) {
		strcpy(h[d1].s1, "REF");
		sprintf(tx, "%d", d2);
		strcpy(h[d1].s1, tx);
		h[d1].totals = 2;
	    } else {
		function1[0] = h[atoi(u1)].s1[0];
		function1[1] = h[atoi(u1)].s1[1];
		function1[2] = '\0';
		n1[0] = h[atoi(u1)].s1[3];
		n1[1] = '\0';
		function2[0] = h[atoi(u2)].s1[0];
		function2[1] = h[atoi(u2)].s1[1];
		function2[2] = '\0';
		n2[0] = h[atoi(u2)].s1[3];
		n2[1] = '\0';
		if ((strcmp(function1, function2) == 0)
		    && (strcmp(n1, n2) == 0)) {
		    for (i = 1; i <= atoi(n1); i++) {
			PDL.st[PDL.current_pos] = atoi(u1) + i;
			PDL.current_pos++;
			PDL.st[PDL.current_pos] = atoi(u2) + i;
			PDL.current_pos++;
		    }
		} else {
		    fail = 1;
		}
	    }
	}
    }
}

void get_structure(char *function, int xi) {
    int addr = deref(xi - 1);
    char th[4];
    if (strcmp(h[addr].s1, "REF") == 0) {
	strcpy(h[heapc].s1, "STR");
	sprintf(th, "%d", heapc + 1);
	strcpy(h[heapc].s2, th);
	h[heapc].totals = 2;
	strcpy(h[heapc + 1].s1, function);
	h[heapc + 1].totals = 1;
	strcpy(h[addr].s1, "REF");
	sprintf(th, "%d", heapc);
	strcpy(h[addr].s2, th);
	h[addr].totals = 2;
	heapc += 2;
	strcpy(mode, "write");
    } else if (strcmp(h[addr].s1, "STR") == 0) {
	if (strcmp(h[atoi(h[addr].s2)].s1, function) == 0) {
	    S = atoi(h[addr].s2) + 1;
	    strcpy(mode, "read");
	} else {
	    fail = 1;
	}
    } else {
	fail = 1;
    }
}

void unify_variable(int xi) {
    char tx[4];
    if (strcmp(mode, "read") == 0) {
	strcpy(n[xi - 1].value1, h[S].s1);
	strcpy(n[xi - 1].value2, h[S].s2);
	n[xi - 1].ok = 1;
    } else if (strcmp(mode, "write") == 0) {
	strcpy(h[heapc].s1, "REF");
	sprintf(tx, "%d", heapc);
	strcpy(h[heapc].s2, tx);
	h[heapc].totals = 2;
	strcpy(n[xi - 1].value1, h[heapc].s1);
	strcpy(n[xi - 1].value2, h[heapc].s2);
	n[xi - 1].ok = 1;
	heapc++;
    }
    S++;
}

void unify_value(int xi) {
    char tx[4];
    if (strcmp(mode, "read") == 0) {
	unify(xi - 1, S);
    } else if (strcmp(mode, "write") == 0) {
	strcpy(h[heapc].s1, n[xi - 1].value1);
	strcpy(h[heapc].s2, n[xi - 1].value2);
	h[heapc].totals = 2;
	heapc++;
    }
    S++;
}

void check() {
    int i;
    if (fail == 1) {
	printf("no\n");
	return;
    } else {
	for (i = 0; i < 100; i++) {
	    if (n[i].ok == 1) {
		printf("X%d = %s,%s\n", i, n[i].value1, n[i].value2);
	    }
	}
	return;
    }
}

