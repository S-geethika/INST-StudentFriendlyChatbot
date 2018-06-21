#include <mysql.h>
#include <stdio.h>
#include <my_global.h>
int main() {
	MYSQL *conn,*conn1;;
	MYSQL_RES *res,*res1;
	MYSQL_ROW row,row1;
conn1 = mysql_init(NULL);

extern char str[10],e[30],o[5],cl[10],gpa[4],q,op[5],branch[10];
extern int st,ro;
float g;
//char c;
//extern int j,e,o;
//extern char s[3];
char ex[10],c,sem,s[3],qq[90],sql1[100],sql[1200],ch,choice,o1[30];
int r,m,error=0,sm;
//char* s1;
char *server = "localhost";
	char *user = "root";
	char *password = "root"; 
	char *database = "utp";
	
	conn = mysql_init(NULL);
if (!mysql_real_connect(conn, server, user, password, 
                                      database, 0, NULL, 0)) {
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
if (!mysql_real_connect(conn1, server, user, password, 
                                      database, 0, NULL, 0)) {
		fprintf(stderr, "%s\n", mysql_error(conn1));
		exit(1);

	}


do
{
printf("select one of the below sections :\n1.attendance(a)\n2.Marks(m)\n3.Library(l)\n4.Time table(t)\n\n  enter '.' after completion\n");
scanf("%c",&choice);
if(choice=='a')
{
printf("\nenter 'attendance' to get attendance and enter the branch \n");
strcpy(o1,"att");
}
else if(choice=='m')
{
printf("\n please select one of the below query domain\n 1. Marks Queries(type 'marks') \na.show marks of subject\n b.avg/min/max marks in subject \n c.students who got above 'm' marks \n d.students with backlogs \n \n 2. Grades Queries(type 'grades') \ne.semester grades\nf.toppers in each semester\ng.branch topper \n h.students above 'g' gpa\n");
strcpy(o1,"mg");
//start();
}
else if(choice=='l')
{
printf(" 1.To search for a book -- type 'search'\n2.To get the details of students who borrowed a book --type 'details'\n");
strcpy(o1,"lib");
}
else if(choice=='t')
{
printf("1. time table for week ---'week' \n2. today's time table -- type 'today'\n3. WANT TO KNOW YOUR CLASS NOW? --type 'now'\n");
strcpy(o1,"time");
}

//MARKS,GRADES
if(strcmp(o1,"mg")==0)
{
start();
switch(q)
{
case 'a':
{
printf("to know your marks type rollno,else type 0\n");
scanf("%d",&r);
printf("'subject'(if you want all sub,type 'all')\n");
scanf("%s",s);
if(r==0&&(strcmp(s,"all"))==0)//all rno,all sub
sprintf(sql, "select rollno,%s,sub from %s",e,cl);
else if(r==0&&(strcmp(s,"all"))!=0)//all rno,s
sprintf(sql, "select rollno,%s from %s where sub='%s'",e,cl,s);
else if(r!=0&&(strcmp(s,"all"))==0)//r,all sub
sprintf(sql, "select sub,%s from %s where rollno=%d",e,cl,r);
else//r,s
sprintf(sql, "select %s from %s where rollno=%d and sub='%s'",e,cl,r,s);
break;
}
//break;
case 'b'://avg/min/max marks in subject
{
printf("'subject'(if you want all sub,type 'all')\n");
scanf("%s",s);
if((strcmp(s,"all"))!=0)
sprintf(sql, "select %s(%s) from %s where sub='%s' ",o,e,cl,s);
else
sprintf(sql, "select sub,%s(%s) from %s group by sub",o,e,cl);
}
break;

case 'c'://students who got above 'm' marks
{
printf(" m value :\n");
scanf("%d",&m);
if(m<0)
error=1;
else
sprintf(sql, "select distinct(rollno),%s from %s where %s>%d",e,cl,e,m);
}
break;

case 'd'://students with backlogs
{
sprintf(sql, "select name from %s where total<35",cl);
}
break;

case 'e'://semester grades
{
printf("to know your marks type rollno,else type 0");
scanf("%d",&r);
printf("all semesters? y/n?\n");
scanf("%c",&sem);
if(sem=='n')
{
printf("enter semester(1-5)\n");
scanf("%d",&sm);
}
if(r==0&&sem=='y')//all rno,all sem
sprintf(sql, "select rollno,sem,%s from cse_grades",gpa);
else if(r==0&&sem=='n')//all rno,s
sprintf(sql, "select rollno,%s from cse_grades where sem=%d",gpa,sm);
else if(r!=0&&sem=='y')//r,all sem
sprintf(sql, "select sem,%s from cse_grades where rollno = %d ",gpa,r);
else//r,s
sprintf(sql, "select %s from cse_grades where rollno = %d and sem=%d",gpa,r,sm);
break;
}


case 'f'://toppers in each semester
sprintf(sql, "select sem,rollno,sgpa from cse_grades where (sgpa,sem) in (select max(sgpa),sem from cse_grades group by sem)");//toppers of each sem
break;

case 'g'://branch topper
sprintf(sql, "select sem,name,cgpa from cse_grades where cgpa =(select max(cgpa) from cse_grades where sem=5)");
break;

case 'h'://students above 'g' gpa
{
printf("enter g value :\n");
scanf("%f",&g);
if(g<0)
error=1;
else
sprintf(sql, "select distinct(rollno) from cse_grades where %s > %f",gpa,g);
}
break;
}
printf("%s\n\n",sql);

mysql_query(conn, sql);
res = mysql_use_result(conn);
	while ((row = mysql_fetch_row(res)) != NULL)
		{
			printf("%s ", row[0]);
			if(row[1]!=NULL)
		printf("%s \n", row[1]);
 		//if(row[2]!=NULL)
		//printf("%s \n", row[2]);
}
//row[0]=row[1]=row[2]=NULL;
o[0]='u';
gpa[0]='u';
st=0;

mysql_query(conn, sql);
res = mysql_use_result(conn);
	while ((row = mysql_fetch_row(res)) != NULL)
		{
			printf("%s ", row[0]);
			if(row[1]!=NULL)
		printf("%s ", row[1]);
 		if(row[2]!=NULL)
		printf("%s \n", row[2]);
}
row[0]=row[1]=row[2]=NULL;
o[0]='u';
gpa[0]='u';
st=0;

}

//ATTENDANCE
if(strcmp(o1,"att")==0)
{
char qq[90];
sprintf(qq,"SELECT DATEDIFF(SYSDATE(),'2018-01-01')");
mysql_query(conn,qq);
res = mysql_store_result(conn);
row = mysql_fetch_row(res);
//printf("%s \n",row[0]);
float n=atoi(row[0]);
printf("\nTotal working days:%f \n",n);
char ch;
//ch='y';
start();
//if(ch=='n')break;
//else if(ch=='y') 
//{
char rollno[10];
printf("enter rollno:");
scanf("%s",rollno);
int mon=1;
int atten=0;
while(mon<=3)
{
char month[50];
int days;
switch(mon)
{
case 1:
if(strcmp(branch,"cse")==0)
sprintf(month,"Jan");
else if(strcmp(branch,"ece")==0)
sprintf(month,"ece_Jan");
days=33;break;
case 2:
if(strcmp(branch,"cse")==0)
sprintf(month,"Feb");
else if(strcmp(branch,"ece")==0)
sprintf(month,"ece_Feb");
days=30;break;
case 3:
if(strcmp(branch,"cse")==0)
sprintf(month,"Mar");
else if(strcmp(branch,"ece")==0)
sprintf(month,"ece_Mar");
days=33;break;
}
char query[50];
sprintf(query,"SELECT * FROM %s WHERE Rollno= %s",month,rollno);
if (mysql_query(conn, query)) {
		fprintf(stderr, "%s\n", mysql_error(conn));}
res = mysql_use_result(conn);
	/* output table name */
printf("Fetching details..\n");
printf("Absent dates\n");	
while ((row = mysql_fetch_row(res)) != NULL)
{ int i=0;	
while(i<days)
{	
if(i<2)
printf("%s ",row[i]);
else  if(i>=2)
{
int l=atoi(row[i]);
if(l==0)printf("%s %d,",month,(i-1));
atten+=l;
}
i++;
}
printf("\n");
}
mysql_free_result(res);
mon++;
}
float per;
per=atten/n;
printf("Attendance: %f percent\n",(per*100));

}

//LIBRARY

if(strcmp(o1,"lib")==0)
{
char sql[100],ch,sql1[100],t[60],s3[61],sub3[60];

int tot,bid,c;

int days= 100;
//while(ch == 'y')
t[0] = '\0';
sub3[0] = '\0';
s3[0] = '%';
s3[1] = '\0';
start();
if(op[0] =='t')//seg fault when complete tile entered 
{
	printf("please enter title of the book you want to search\n");
	scanf ("%[^\n]%*c", t);
	strcat(s,t);
	strcat(s,"%");
	sprintf(sql, "select copies,bid from bookslist where title LIKE '%s'",s);
	mysql_query(conn, sql);
	res = mysql_use_result(conn);
	while ((row = mysql_fetch_row(res)) != NULL)
	{tot = atoi(row[0]);
		bid= atoi(row[1]);
	 }
	printf("%d--total \n",tot);printf("%d--bid \n",bid);
	sprintf(sql, "select count(*) from students where b1 = %d OR b2 = %d OR b3 = %d ",bid,bid,bid);
	mysql_query(conn, sql);
	res = mysql_use_result(conn);
	while ((row = mysql_fetch_row(res)) != NULL)
	{c = atoi(row[0]);}
	printf("%d copies are available \n",(tot-c));
	if((tot-c)==0)
	{	 printf("Do you want to see the details of students who borrowed the same book?y/n \n");
	char ans = 'n';
	ans = getchar();
	if(ans == 'y') {op[0] = 'o';s[0] = '%'; s[1] = '\0';}
     

}
	
}

if(op[0]== 'b')
{
	printf("please enter subject\n");
	scanf ("%[^\n]%*c", sub3);
	sprintf(sql, "select title,copies,bid from bookslist where subject LIKE '%s'",sub3);
	//printf("%s--------\n\n",sql);
	mysql_query(conn, sql);
	res = mysql_use_result(conn);char bookname[100];
	printf("TITLE \t\t\t\t|| COPIES\n");//add dates in db
	printf("---------------------------------------------------------------------------------------\n");
	while ((row = mysql_fetch_row(res)) != NULL)
	{tot = atoi(row[1]);
		bid= atoi(row[2]);strcpy(bookname,row[0]);

		sprintf(sql1, "select count(*) from students where b1 = %d OR b2 = %d OR b3 = %d ",bid,bid,bid);
		mysql_query(conn1, sql1);
		res1 = mysql_use_result(conn1);
		while ((row1 = mysql_fetch_row(res1)) != NULL)
		{c = atoi(row1[0]);
	 	}

		printf("%s || %d  \n",bookname,(tot-c));
	 }
}

if(op[0] == 'a')
{

	sprintf(sql, "select s.sid, s.sname, b.title from students s JOIN bookslist b ON (s.b1 = b.bid OR s.b2 = b.bid OR s.b3 = b.bid) order by b.bid,s.sid;");
	//printf("%s\n\n",sql);
	mysql_query(conn, sql);
	res = mysql_use_result(conn);
	printf("SID || SNAME || TITLE OF BOOK\n");//print title once
	while ((row = mysql_fetch_row(res)) != NULL)
	{printf("%s || %s || %s \n",row[0],row[1],row[2]);
	 }
}
if(op[0] == 'o')
{
if(bid!=0) 
{
sprintf(sql,"select MIN(dif) from ((select MIN(DATEDIFF(CURDATE(),bd1)) AS dif from students where b1 = %d) UNION (select MIN(DATEDIFF(CURDATE(),bd2)) from students where b2 = %d) UNION (select MIN(DATEDIFF(CURDATE(),bd3)) from students where b3 = %d)) AS d",bid,bid,bid);
//printf("%s",sql);
mysql_query(conn1, sql);
	res1 = mysql_use_result(conn1);
	while ((row1 = mysql_fetch_row(res1)) != NULL)
	{days = atoi(row1[0]);	 }
}	
	if(t[0] == '\0') {printf("please enter title of the book \n");
	scanf ("%[^\n]%*c", t);}
	strcat(s,t);
	strcat(s,"%");
	sprintf(sql, "select st.sid, st.sname from students st JOIN bookslist b ON (st.b1 = b.bid OR st.b2 = b.bid OR st.b3 = b.bid) WHERE b.title LIKE '%s' order by st.sid;",s3);
	//printf("%s\n\n",sql);
	mysql_query(conn, sql);
	res = mysql_use_result(conn);
	printf("BOOK: %s\n",t);
	printf("SID || SNAME \n");
	while ((row = mysql_fetch_row(res)) != NULL)
	{printf("%s || %s \n",row[0],row[1]);
	 }
printf("\nyou can get one in %d days\n",days);
	
}

}
//TIME TABLE
if(strcmp(o1,"time")==0)
{
start();
if(op[0] == 'w')
{
sprintf(sql, "select * from timetable");
mysql_query(conn, sql);
	res = mysql_use_result(conn);
printf("DAY \t|| \t7:30-8:00\t || \t8:00-9:00\t || \t9:00- 10:00\t || \t10:15 - 11:15\t ||\t 11:15 - 12:15\t || \t12:15 - 1:00\t ||\t1:00 - 2:00\t || \t2:00 - 3:00\t \n");//print title once

	while ((row = mysql_fetch_row(res)) != NULL)
	{printf("%s || %s || %s || %s || %s || %s ||%s || %s || %s  \n",row[0],row[1],row[2],row[3],row[4],row[5],row[6],row[7],row[8]);
	 }	
}

if(op[0] == 't')
{
sprintf(sql, "select * from timetable where day = (select DAYNAME(CURDATE())) ");
mysql_query(conn, sql);
	res = mysql_use_result(conn);
printf("DAY \t|| \t7:30-8:00\t || \t8:00-9:00\t || \t9:00- 10:00\t || \t10:15 - 11:15\t ||\t 11:15 - 12:15\t || \t12:15 - 1:00\t ||\t1:00 - 2:00\t || \t2:00 - 3:00\t \n");//print title once

	while ((row = mysql_fetch_row(res)) != NULL)
	{printf("%s || %s || %s || %s || %s || %s ||%s || %s || %s  \n",row[0],row[1],row[2],row[3],row[4],row[5],row[6],row[7],row[8]);
	 }	
}
if(op[0] == 'n')
{
sprintf(sql,"select t1 from (select * from timetable where day = (select DAYNAME(CURDATE()))) AS t where CURTIME() BETWEEN '07:30:00' AND '08:00:00' UNION select t2 from (select * from timetable where day = (select DAYNAME(CURDATE()))) AS t where CURTIME() BETWEEN '08:00:00' AND '09:00:00' UNION select t3 from (select * from timetable where day = (select DAYNAME(CURDATE()))) AS t where CURTIME() BETWEEN '09:00:00' AND '10:00:00' UNION select t4 from (select * from timetable where day = (select DAYNAME(CURDATE()))) AS t where CURTIME() BETWEEN '10:15:00' AND '11:15:00' UNION select t5 from (select * from timetable where day = (select DAYNAME(CURDATE()))) AS t where CURTIME() BETWEEN '11:15:00' AND '12:15:00' UNION select t6 from (select * from timetable where day = (select DAYNAME(CURDATE()))) AS t where CURTIME() BETWEEN '12:15:00' AND '13:00:00' UNION select t7 from (select * from timetable where day = (select DAYNAME(CURDATE()))) AS t where CURTIME() BETWEEN '13:00:00' AND '14:00:00' UNION select t8 from (select * from timetable where day = (select DAYNAME(CURDATE()))) AS t where CURTIME() BETWEEN '14:00:00' AND '15:00:00'");
mysql_query(conn, sql);
	res = mysql_use_result(conn);
printf("Don't you know that its ");//print title once

	while ((row = mysql_fetch_row(res)) != NULL)
	{printf(" %s class now!!\n",row[0]);
	 }

}
if(op[0] == 'e')
{
int roll;
printf("enter your rollno\n");
scanf("%d",&roll);

sprintf(sql, "select room from seating where rollno = %d",roll);

mysql_query(conn, sql);
	res = mysql_use_result(conn);
printf("roomnumber:");//print title once

	while ((row = mysql_fetch_row(res)) != NULL)
	{printf(" %s",row[0]);
	 }
	
}

printf("continue? y/n?");
scanf("%c",&c);

}while(c=='y');

mysql_close(conn);
return 0;
}

