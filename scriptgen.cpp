#include<iostream>
#include<fstream>
using namespace std;
int main()
{
	ofstream f("cse_grades.sql");
	ifstream fin("cse_grades.csv");
	//f<<"create table cse_marks ( Rollno int(8),Name varchar(255)";
f<<"create table cse_grades ( rollno INT,name varchar(255),sgpa FLOAT,cgpa FLOAT)";
//rollno INT,name varchar(255),sub char,m1 FLOAT,mid FLOAT,m2 FLOAT,end FLOAT	
/*for(int i=1;i<=31;i++)
	f<<",Feb_"<<i<<" int(3)";
	f<<");"<<endl;
*/
	while(!fin.eof())
{

	string line(" ");
f<<"INSERT INTO cse_grades values(";
	getline(fin,line);
	f<<line;
	f<<");"<<endl;
}
fin.close();
f.close();
return 0;
}
