%option noyywrap
%{
#include <stdio.h>
char str[10],e[30],s[3],o[5],cl[10],gpa[4],q,o1[30],branch[10],op[5];
int st,ro;
//int j,r,e=0,o=-1;
//char s[3];
%}
 
%% 
start {
printf(" 1.To search for a book -- type 'search'\n2.To get the details of students who borrowed a book --type 'details'\n");
}

 attendance {strcpy(o,"attendance");}
CSE|cse|Cse {strcpy(branch,"cse");}
ECE|ece|Ece {strcpy(branch,"ece");}
done {printf("Input received..!!!\n");}
[%\t]+ ;          
a {
//show marks of a subject
printf("\nFor marks in subject type the following details : \n 'exam'\n");
q='a';
}

b {
printf("\nType the following details : \n 'avg/max/min' \n'exam' \n");
q='b';
}

c {
//printf("\nenter 'cg' / 'sg'\n");
q='c';
}

d {
printf("\nstudents with back logs \n");
q='d';
}


e {
printf("\nenter cgpa  'cg' / sgpa  'sg'\n");
q='e';
}


f {
//printf("\nrequested details are: \n");
q='f';
}


g {
//printf("\nrequested details are: \n");

q='g';
}


h {
printf("\nenter cgpa  'cg' / sgpa  'sg'\n");
q='h';
}

cg {
strcpy(gpa,"cgpa");
}

sg {
strcpy(gpa,"sgpa");
}
DS {
strcpy(s,"DS");
}

OS {
strcpy(s,"OS");
}

m1 {
strcpy(e,"m1");
}
mid {
strcpy(e,"mid");
}

m2 {
strcpy(e,"m2");
}

end {
strcpy(e,"end");
}
marks {
printf("you selected 'marks'\n enter choice\n");
strcpy(cl,"cse_marks");
}

grades {
printf("you selected 'grades'\nenter choice\n");
strcpy(cl,"cse_grades");
}

max {
strcpy(o,"max");
}

min {
strcpy(o,"min");
}

avg {
strcpy(o,"avg");
}
hru {
printf("I am fine..thank you\n what about you?");
}

fine {
printf("ok..let's start");
}

time {printf("1. time table for week ---'week' \n2. today's time table -- type 'today'\n3. WANT TO KNOW YOUR CLASS NOW? --type 'now'\n");}
week {strcpy(op, "w");}
today {strcpy(op, "t");}
now {strcpy(op,"n");}
exam {strcpy(op, "e");}

search {printf("1.To search book by title --type 'title' \n2. To list the books by subject --type 'subject'\n"); 
	}
title {strcpy(op, "t");}
subject { strcpy(op, "b");}
details {printf("1.To see the  details of all borrowers -- type 'all' \n 2.To see details of borrowers of a book -- type 'book'\n");}
all {strcpy(op,"a");}
book {strcpy(op,"o");}


. {
return 0;
}

st {
st=1;
//printf("%d",st);
}


%%

void start()
{
yylex();
//return 0;
}



