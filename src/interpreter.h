struct heap /*ÄïìÞ ôïõ óùñïý*/
  { char s1[4]; /*Ðñþôç ôéìÞ ôïõ heap*/
    char s2[4]; /*Äåýôåñç ôéìÞ ôïõ heap(äåí ÷ñçóéìïðïéåßôáé ðáíôá)*/
	int totals; /*ÓõíïëéêÝò ôéìÝò ðïõ ÷ñçóéìïðïéïýíôáé*/
  };

struct x /*ÄïìÞ ôùí üñùí*/
  { char value1[4]; /*Ðñþôç ôéìÞ(STR Þ REF)*/
    char value2[4]; /*Äåýôåñç ôéìÞ(ÁñéèìçôéêÞ ôéìÞ)*/
	int ok; /*Áí Ý÷ïõí áíáôåèåß ôéìÝò óôïí üñï*/
  };

struct stack /*ÄïìÞ óôïßâáò*/
 { int st[100]; /*ÌÝãåèïò 100*/
   int current_pos; /*ÔñÝ÷ïõóá èÝóç*/
 };



void put_structure(char* , int );
void set_variable(int );
int deref(int);
void set_value(int );
void get_structure(char* , int);
void unify_variable(int);
void unify_value(int );
void unify(int ,int );
void check();
