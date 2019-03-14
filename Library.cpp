#include <iostream>
#include<string>
#include<fstream>
using namespace std;

class date
{ friend ostream& operator <<(ostream & ,date); //friends
friend istream& operator >>(istream &, date&);
	private:
		int day, month, year;	
	public:
		date():day(0),month(0), year(0)   //default ctor
		{//cout<<"default date ctor"<<endl;
		}
		date(int a, int b, int c)	   //parametrized ctor
		{
		{if ((a<1)||(a>31))
		{cout<<"Invalid day. Re-enter."<<endl;
		exit(0);}
		else
			day=a;
		}
		
		if ((b<1)||(b>12))
		{cout<<"Invalid month. Re-enter."<<endl;
		exit (0);}
		else
			month=b;
		
		if (c<2000)
		{cout<<"Invalid year. Re-enter."<<endl;
		exit (0);}
		else
			year=c;
		}

		void setdate()
		{
		int a=0,b=0,c=0;   
		cin>>a>>b>>c;
		
		if ((a<1)||(a>31))
		{cout<<"Invalid day. Re-enter date."<<endl; exit(0);}
		else
		{day=a;}
		
		
		if ((b<1)||(b>12))
		{cout<<"Invalid month. Re-enter date."<<endl; exit(0);}
		else
		{month=b;}
		
		if (c<2000)
		{cout<<"Invalid year. Re-enter date."<<endl; exit(0);}
		else
		{year=c;}
		}
				
	int operator - (const date &right) //operator overloading
{
	int jDate1;
	int jDate2;
	int newDate;
	jDate1 = (1461 * (year + 4800 + (month - 14)/12))/4 +(367 * (month - 2 - 12 * ((month - 14)/12)))/12 - (3 * ((year + 4900 + (month - 14)/12)/100))/4 + day - 32075;
	jDate2 = (1461 * (right.year + 4800 + (right.month - 14)/12))/4 +(367 * (right.month - 2 - 12 * ((right.month - 14)/12)))/12 - (3 * ((right.year + 4900 + (right.month - 14)/12)/100))/4 + right.day - 32075;
	newDate = jDate1 - jDate2;
	return newDate;
	}

	int difference(date&a, date&b)
	{int c;
	c=a-b;
	return c;}

};

ostream& operator <<(ostream &out, date d)
{out<<d.day<<"-"<<d.month<<"-"<<d.year;
return out;}

istream& operator >>(istream &in, date& d)
{in>>d.day>>d.month>>d.year;
return in;}



class book
{
friend ostream& operator <<(ostream & ,book);
static int totalissued;								//static members
private: 
 string name, author;
 int Refno;
 date issued;
 date returned;

public:
	 bool i;
book():name("a"),author("a"),Refno(0),i(false)
	{//cout<<"default book ctor"<<endl;
}

	book(string a, string b, int c):name(a),author(b),Refno(c),i(false)
	{
		//cout<<"parametrized librarymember ctor"<<endl;
	}

	void setissued()
		{	 i=true;
			cout<<"Enter the issue date: "<<endl;
			issued.setdate();
					
		}
	string getname()
	{return name;}

	string getauthor()
	{return author;}

	int getrefno()
	{return Refno;}

	date getissue()
	{return issued;}
	
	void setreturned()
	{ 	i=false;
		cout<<"Enter the return date: "<<endl;
		returned.setdate();
	}

	static void totalissue()
	{totalissued++;}

	static void returnissue()
	{totalissued--;}

	date getreturned()
	{return returned;}

	int gettotalissued()
	{return totalissued;}

		
 };

ostream& operator <<(ostream &out, book b)
{out<<b.name<<","<<b.author<<","<<b.Refno<<","<<b.issued<<","<<b.returned<<"\nTotal Books currently issued by Library: "<<b.totalissued<<endl;
return out;}

int book::totalissued=0;

class librarymember
{friend void clearfine(librarymember &);

protected:
	string name;
	char gender;
	int issuedbooks;
	int fine;
	
	librarymember():name("a"),gender('M'),issuedbooks(0),fine(0)
	{
		//cout<<"default librarymember ctor"<<endl;
	}

	librarymember(string a, char g, int b):name(a),gender(g),issuedbooks(b),fine(0)
	{//cout<<"parametrized librarymember ctor"<<endl;
	}
public:
	virtual void show()=0;
	

	virtual void issue(book &b)
	{issuedbooks++;
	book::totalissue();
	cout<<"Book Issued. Issued books by member: "<<issuedbooks<<endl;}

	virtual int calculatefine(date &d1, date&d2, int finerate)
	{	int due=d2-d1;
		if (due>30)
			{ fine=finerate*(due-30);
			cout<<"fine charged: "<<fine<<" rupees"<<endl;}
		else 
		{}
	return fine;}


	virtual void returned(book &a)
	{issuedbooks--;
	book::returnissue();
	
	cout<<"Book returned. number of issued books remaining: "<<issuedbooks<<endl;
	}

virtual ~librarymember()
{//cout<<"librarymember dtor"<<endl;
}
};

class student:public librarymember 
{
private:
	int degree;
	int regno;

protected:
	student():degree(0),regno(0)
	{//cout<<"default student ctor"<<endl;
	}

	student(string c, char e, int f, int a,int b):librarymember(c,e,f),degree(a),regno(b)
	{//cout<<"parametrized student ctor"<<endl;
	}
public:
	void show()
	{cout<<"name: "<<librarymember::name<<"\ngender: "<<librarymember::gender<<"\nNo of Issued Books: "<<librarymember::issuedbooks<<"\nFine: "<<librarymember::fine<<"\ndegree: "<<degree<<"\nReg no: "<<regno<<endl;}
	

~student()
{//cout<<"student dtor"<<endl;
}	

};																					


class UG:public student
{
private:
	const int allowedbooks;
	const int finerate;
	
public:
	UG():allowedbooks(4),finerate(6)
	{//cout<<"default UG ctor"<<endl;
	}
	UG(string c, char e, int f, int a, int b):student(c,e,f,a,b),allowedbooks(4),finerate(6)
	{
		//cout<<"parametrized UG ctor"<<endl;
	}

	void show()
	{student::show();
	cout<<"allowed books: "<<allowedbooks<<endl<<"finerate: "<<finerate<<" rupees"<<endl;}

	void issue(book &b)
	{
		int check=issuedbooks+1;
	if (b.i==false)
		{if (check<=allowedbooks)
		{	b.setissued();
			librarymember::issue(b);
		}
		else
			cout<<"Total number of issued books exceed limit"<<endl;
	}
	else 
	{cout<<"Book is already issued."<<endl;}
	}
	
	void returned(book &a)
	{if (a.i==true)
		{a.setreturned();
	 date D1, D2;
	D1=a.getissue();
	D2=a.getreturned();
	fine=librarymember::calculatefine(D1,D2,finerate);
	librarymember::returned(a);}
	else
		cout<<"Error: Cannot enter return date as book is not issued"<<endl;
	ofstream outrecord("record.txt",ios::app);
	if(!outrecord)
	{cout<<"Error: File could not be opened"<<endl;
	exit(1);
	}
	outrecord<<a.getname()<<" "<<a.getauthor()<<" "<<a.getrefno()<<" "<<a.getissue()<<" "<<a.getreturned()<<endl;
	outrecord.close();
	cout<<"Book Record Entered"<<endl;
	}

~UG()
{//cout<<"UG dtor"<<endl;
}
};

class PG:public student
{
private:
	const int allowedbooks;
	const int finerate;
public:
	PG():allowedbooks(5),finerate(4)
	{//cout<<"default PG ctor"<<endl;
	}
	PG(string c, char e, int f, int a,int b):student(c,e,f,a,b),allowedbooks(5),finerate(4)
	{//cout<<"parametrized PG ctor"<<endl;
	}

	void show()
	{student::show();
	cout<<"allowed books: "<<allowedbooks<<endl<<"finerate: "<<finerate<<" rupees"<<endl;}

	void issue(book &b)
	{
		int check=issuedbooks+1;
	if (b.i==false)
		{if (check<=allowedbooks)
		{	b.setissued();
			librarymember::issue(b);
		}
		else
			cout<<"Total number of issued books exceed limit"<<endl;
	}
	else 
	{cout<<"Book is already issued."<<endl;}
	}

	void returned(book &a)
	{if (a.i==true)
		{a.setreturned();
	 date D1, D2;
	D1=a.getissue();
	D2=a.getreturned();
	fine=librarymember::calculatefine(D1,D2,finerate);
	librarymember::returned(a);}
	else
		cout<<"Error: Cannot enter return date as book is not issued"<<endl;
	ofstream outrecord("record.txt",ios::app);
	if(!outrecord)
	{cout<<"Error: File could not be opened"<<endl;
	exit(1);
	}
	outrecord<<a.getname()<<" "<<a.getauthor()<<" "<<a.getrefno()<<" "<<a.getissue()<<" "<<a.getreturned()<<endl;
	outrecord.close();
	cout<<"Book Record Entered"<<endl;
	}


~PG()
{//cout<<"PG dtor"<<endl;
}
};

class faculty:public librarymember
{ private:
	
	int IDno;
	const int allowedbooks;
	const int finerate;
public:
	
	faculty():IDno(0), allowedbooks(6), finerate(2)
	{//cout<<"default staff ctor"<<endl;
	}

	faculty(string c, char e, int f,int b):librarymember(c,e,f),IDno(b),allowedbooks(6),finerate(2)
	{//cout<<"parametrized staff ctor"<<endl;
	}

	void show()
	{cout<<"name: "<<librarymember::name<<"\ngender: "<<librarymember::gender<<"\nNo of Issued Books: "<<librarymember::issuedbooks<<"\nFine: "<<librarymember::fine<<endl;
	cout<<"IDno: "<<IDno<<"\nallowedbooks: "<<allowedbooks<<"\nfinerate: "<<finerate<<endl;}

void issue(book &b)
	{
		int check=issuedbooks+1;
	if (b.i==false)
		{if (check<=allowedbooks)
		{	b.setissued();
			librarymember::issue(b);
		}
		else
			cout<<"Total number of issued books exceed limit"<<endl;
	}
	else 
	{cout<<"Book is already issued."<<endl;}
	}

	void returned(book &a)
	{if (a.i==true)
		{a.setreturned();
	 date D1, D2;
	D1=a.getissue();
	D2=a.getreturned();
	fine=librarymember::calculatefine(D1,D2,finerate);
	librarymember::returned(a);}
	else
		cout<<"Error: Cannot enter return date as book is not issued"<<endl;
	ofstream outrecord("record.txt",ios::app);
	if(!outrecord)
	{cout<<"Error: File could not be opened"<<endl;
	exit(1);
	}
	outrecord<<a.getname()<<" "<<a.getauthor()<<" "<<a.getrefno()<<" "<<a.getissue()<<" "<<a.getreturned()<<endl;
	outrecord.close();
	cout<<"Book Record Entered"<<endl;
	}


~faculty()
{//cout<<"staff dtor"<<endl;
}
};

void clearfine(librarymember& L)
{L.fine=0;}

void main()
{	int t=0, q=0,f=0,d=0,z=0;
	book electronics("Microelectronics","Smith",4543);
	book thermo("Thermodynamics","Cengal",3421);
	book math("Calculus","Finney",5789);
	
	UG zainab("Javed,Zainab",'F',0,33,82);
	PG hira("Irshad,Hira", 'F', 0,12,65);
	faculty ali("Ahmed,Ali",'M',0,235);
	
	book *arr[3]={&thermo,&math,&electronics};
	librarymember *ptr[3];
	ptr[0]=&zainab;
	ptr[1]=&hira; ptr[2]=&ali;
	
	while (z!=3)
	 {
	 cout<<"\nPress 0 to select UG Zainab Javed.\nPress 1 to select PG Hira Irshad.\nPress 2 to select Faculty Member Ali Ahmed."<<endl;
	 cin>>q;
	 ptr[q]->show();
	 cout<<"\nPress 0 to select Thermodynamics By Cengal.\nPress 1 to select Calculus By Kreyszig.\nPress 2 to select Microelectronics by Sedra Smith."<<endl;
	 cin>>f;
	 cout<<*arr[f];
	 cout<<"\nPress 0 to issue book.\nPress 1 to return book.\nPress 2 to clear fine.\nPress 3 to exit."<<endl;
	 
		 cin>>d;
switch (d)
{
case 0:
	{ptr[q]->issue(*arr[f]); 
	break;}
case 1:
	{ptr[q]->returned(*arr[f]); cout<<*arr[f];
	
	break;}
case 2: 
	{clearfine(*ptr[q]);
	break;}
case 3:
	{exit(0);
		break;}

}
	 }
}

