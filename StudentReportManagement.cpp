#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

class student
{
	private:
		
	int rollno;
	char name[50];
	int oop_marks, ds_marks, ca_marks, eng_marks, cs_marks;
	double per;    //stores average mark
	char grade;    //stores grade obtained by the student
	
	public:
		
	void calculate();	          // function to calculate grade
	void getdata();		         // function to get data from user
	void showdata() const;	    // function to display the data 
	void show_tabular() const;  //function to display student details in tabular form
	int retrollno() const;      //function to return roll number
	
}; 

void student::calculate()
{
	per = (oop_marks + ds_marks + ca_marks + eng_marks + cs_marks) / 5.0;
	
	if(per>=80)
		grade='A';
	else if(per>=70)
		grade='B';
	else if(per>=50)
		grade='C';
	else
		grade='F';
}

void student::getdata()
{
	cout<<"\nEnter the Roll number of student "<<"\t"<< ":";
	cin>>rollno;
	
	cout<<"\n\nEnter the Name of student "<<"\t\t"<< ":";
	cin.ignore();
	cin.getline(name,50);
	
	cout<<"\nEnter the marks scored in Object Oriented Programming "<<"\t"<< ":" ;
	cin>>oop_marks;
	
	cout<<"\nEnter the marks scored in Data Structures "<<"\t\t"<< ":" ;
	cin>>ds_marks;
	
	cout<<"\nEnter the marks scored in Computer Architecture "<<"\t"<< ":" ;
	cin>>ca_marks;
	
	cout<<"\nEnter the marks scored in English  "<<"\t\t\t"<< ":" ;
	cin>>eng_marks;
	
	cout<<"\nEnter the marks scored in Computer Science "<<"\t\t"<< ":" ;
	cin>>cs_marks;
	calculate();
}

void student::showdata() const
{
	cout<<"\n Student Roll number "<<"\t"<< ":" <<rollno;
	cout<<"\n Student Name "<<"\t\t"<< ":"<<name;
	
	cout<<"\n\n MARKS SCORED BY THE STUDENT: \n";
	cout<<"----- ------ -- --- --------\n";
	
	cout<<"\n Object Oriented Programming    :"<<oop_marks;
	cout<<"\n Data Structures  "<<"\t\t"<< ":" <<ds_marks;
	cout<<"\n Computer Architecture  "<<"\t"<< ":" <<ca_marks;
	cout<<"\n English "<<"\t\t\t"<< ":"<<eng_marks;
	cout<<"\n Computer Science "<<"\t\t"<< ":"<<cs_marks;
	
	cout<<"\n\n Percentage     :"<<per;
	cout<<"\n Grade  "<<"\t"<< ":"<<grade;
}

void student::show_tabular() const
{
	cout<<rollno<<setw(6)<<"\t"<<name<<setw(10)<<"\t"<<oop_marks<<setw(4)<<"\t"<<ds_marks<<setw(4)<<"\t"<<ca_marks<<setw(4)<<"\t"
		<<eng_marks<<setw(4)<<"\t"<<cs_marks<<setw(8)<<""<<per<<setw(6)<<"\t"<<grade<<endl;
}

int  student::retrollno() const
{
	return rollno;
}

/* function declaration */

void write_student();	        // function to write the record in binary file
void display_all();	           // function to read records from binary file
void display_sp(int);	      // function to display specific record from binary file
void modify_student(int);    // function to update record of binary file
void delete_student(int);	//function to delete selected records from binary file
void class_result();	   //function to display all records in tabular format 
void result();		      //function to display result 
void intro();		     //function to display welcome screen
void entry_menu();	    //function to display entry menu on screen



int main()
{
	char ch;
	cout.setf(ios::fixed|ios::showpoint);
	cout<<setprecision(2);      // program outputs decimal number to two decimal places
	intro();
	do
	{
		system("cls");
		cout<<"\n\n\n\t MAIN MENU";
		cout<<"\n\t ---- -----";
		
		cout<<"\n\n\t 1. ENTRY/EDIT MENU ";
		cout<<"\n\n\t 2. RESULT MENU ";
		cout<<"\n\n\t 3. EXIT ";
		cout<<"\n\n\n\t Please Select Your Option  ";
		cin>>ch;
		switch(ch)
		{
			case '1': entry_menu();
				break;
			case '2': result();
				break;
			case '3':
				break;
			default :cout<<"\a";
		}
    }while(ch!='3');
	return 0;
}


/*  function to write in file  */

void write_student()
{
	student st;
	ofstream outFile;
	outFile.open("student.dat",ios::binary|ios::app);
	st.getdata();
	outFile.write(reinterpret_cast<char *> (&st), sizeof(student));
	outFile.close();
    cout<<"\n\nStudent record Has Been Created ";
	cin.ignore();
	cin.get();
}


/*  function to read all records from file  */

void display_all()
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\n\t\t ALL STUDENTS RECORD. \n\n";
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		st.showdata();
		cout<<"\n\n_________\n";
	}
	inFile.close();
	cin.ignore();
	cin.get();
}


/*  function to read specific record from file  */

void display_sp(int n)
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	bool flag=false;
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		if(st.retrollno()==n)
		{
	  		 st.showdata();
			 flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nrecord not exist";
	cin.ignore();
	cin.get();
}


/*  function to modify the records  */

void modify_student(int n)
{
	bool found=false;
	student st;
	fstream File;
	File.open("student.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
    	while(!File.eof() && found==false)
	{

		File.read(reinterpret_cast<char *> (&st), sizeof(student));
		if(st.retrollno()==n)
		{
			st.showdata();
			cout<<"\n\nPlease enter the new Details of Student"<<endl;
			st.getdata();
		    	int pos=(-1)*static_cast<int>(sizeof(st));
		    	File.seekp(pos,ios::cur);
		    	File.write(reinterpret_cast<char *> (&st), sizeof(student));
		    	cout<<"\n\n\t Record Updated";
		    	found=true;
		}
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
	cin.ignore();
	cin.get();
}


/* function to delete a record  */

void delete_student(int n)
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	ofstream outFile;
	outFile.open("Temp.dat",ios::out);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		if(st.retrollno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&st), sizeof(student));
		}
	}
	outFile.close();
	inFile.close();
	remove("student.dat");
	rename("Temp.dat","student.dat");
	cout<<"\n\n\tRecord Deleted ..";
	cin.ignore();
	cin.get();
}


/* function to display all students grade report  */

void class_result()
{
	student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\t\tALL STUDENTS RESULT \n\n";
	cout<<"___________\n";
	cout<<"R.No"<<"\t"<<"Name"<<"\t"<<"\t"<<"OOP"<<"\t"<<"DS"<<"\t"<<"CA"<<"\t"<<"ENG"<<"\t"<<"CS"<<"\t"<<"PERCENT"<<"\t\t"<<"GRADE"<<endl;
	cout<<"___________\n";
	while(inFile.read(reinterpret_cast<char *> (&st), sizeof(student)))
	{
		st.show_tabular();
	}
	cin.ignore();
	cin.get();
	inFile.close();
}
    

/*  function to display result  */


void result()
{
	char ch;
	int rno;
	system("cls");
	cout<<"\n\n\n\t RESULT MENU";
	cout<<"\n\t ------ -----\n";
	cout<<"\n\n\t   1. CLASS RESULT ";
	cout<<"\n\n\t   2. STUDENT REPORT CARD ";
	cout<<"\n\n\t   3. BACK TO MAIN MENU ";
	cout<<"\n\n\n\t Enter Choice : ";
	cin>>ch;
	system("cls");
	switch(ch)
	{
	case '1' :	class_result(); break;
	case '2' :	cout<<"\n\n\t Enter the Roll Number of Student : "; cin>>rno;
				display_sp(rno); break;
	case '3' :	break;
	default:	cout<<"\a";
	}
}


/*  INTRODUCTION FUNCTION (WELCOME SCREEN) */

void intro()
{
	cout<<"\n\n\n\n\n\n\n\t\t\t\t\t _________"<<endl;
	cout<<"\t\t\t\t\t -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-"<<endl;
	
	cout<<"\n\n\n\t\t\t\t\t\t\t  STUDENT REPORT MANAGEMENT";
	cout<<"\n\n\t\t\t\t\t\t\t  DONE BY:";
	cout<<"\n\n\t\t\t\t\t\t\t\t DIVYASREE S.V";
	
	cout<<"\n\n\n\t\t\t\t\t .......................................\n";
	cout<<"\t\t\t\t\t _________"<<endl;
	cin.get();
}


/*   ENTRY / EDIT MENU FUNCTION  */

void entry_menu()
{
	char ch;
	int num;
	system("cls");
	cout<<"\n\n\n\t ENTRY MENU";
	cout<<"\n\t ----- -----";
	cout<<"\n\n\t 1.CREATE STUDENT RECORD";
	cout<<"\n\n\t 2.DISPLAY ALL STUDENTS RECORDS";
	cout<<"\n\n\t 3.SEARCH STUDENT RECORD ";
	cout<<"\n\n\t 4.MODIFY STUDENT RECORD";
	cout<<"\n\n\t 5.DELETE STUDENT RECORD";
	cout<<"\n\n\t 6.BACK TO MAIN MENU";
	cout<<"\n\n\n\t Please Enter Your Choice : ";
	cin>>ch;
	system("cls");
	switch(ch)
	{
	case '1':	write_student(); break;
	case '2':	display_all(); break;
	case '3':	cout<<"\n\n\t Please enter the roll number "; cin>>num;
			display_sp(num); break;
	case '4':	cout<<"\n\n\t Please enter the roll number "; cin>>num;
			modify_student(num);break;
	case '5':	cout<<"\n\n\t Please enter the roll number "; cin>>num;
			delete_student(num);break;
	case '6':	break;
	default:	cout<<"\a"; entry_menu();
	}
}
