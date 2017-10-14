/*
	@roottraveller
	Coded - May 2013
	
	All right reserved. 
*/


#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
#include<stdio.h>
#include<stdlib.h>
//#include<conio>
using namespace std;
//#include<sys/stdc++.h>
//***************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************
class product {
private:
	unsigned int slno; //serial number of product
	char name[50];
	float price;
	char details[100];
	
public:
        product(); //constructor
	void create_entry();	//function to get data from user
	void show_entry() const;	//function to show data on screen
	void modify_entry();
        void delete_entry();
	void modify();	//function to add new data
	void display() const;	//function to show data in tabular format
        void clean_display();
        int return_slno() const ;
}; //class ends here

product::product(){
    char ch;
    do	{
		//system("cls");
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. NEW PURCHASE";
		cout<<"\n\n\t02. MODIFY PURCHASE ITEM";
		cout<<"\n\n\t03. DISPLAY DATABASE";
		cout<<"\n\n\t04. DELETE ENTRY";
		cout<<"\n\n\t05. EXIT";
		cout<<"\n\n\tSelect Your Option (1-4) ";
	    
		cin>>ch;
		//system("cls");
	    
		switch(ch) {
			case '1':
				create_entry(); 
				break;
			case '2':
				modify_entry(); 
				break;
			case '3':
			        show_entry(); 
				break;
			case '4':
			   	delete_entry();
				break;
			case '5':
			   	exit(0);
				break;
			 default : cout<<"Invalid Input...";   cout<<"\a";
		}
	    
		cin.ignore(); cin.get();
    }while(ch!='5');
}

void product::create_entry(){
        product ac;
	ofstream outFile;
	
	outFile.open("data.dat",ios::binary|ios::app);
	cout<<"\nEnter The serial no. of Item : "; cin>>slno;
	cout<<"\nEnter The Name of Item : "; cin.ignore(); cin.getline(name,50);
	cout<<"\nEnter The Price of Item : "; cin>>price;
	cout<<"\nEnter Item Details : "; cin.ignore(); cin.getline(details,100);
	
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(product));
	outFile.close();
	
	cout << "\n\nentry successful" <<endl;
}

void product::show_entry() const{
	product ac;
	ifstream inFile;
	
	inFile.open("data.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	
	cout<<"\n\n\t\tDATABASE ITEMS LIST \n\n";
	cout<<"====================================================\n";
	cout<<"Sr no.    NAME       PRICE      DETAILS\n";
	cout<<"====================================================\n";
	
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(product)))
	{
		ac.clean_display();
	}
	inFile.close();
}

void product::modify_entry() {
	bool found=false;
	unsigned int n;
	
	cout << "Enter the serial number ??  " ; 
	cin >> n;
	
	product ac;
 	fstream File;
        File.open("data.dat",ios::binary|ios::in|ios::out);
 	if(!File)
 	{
 		cout<<"File could not be open !! Press any Key...";
 		return;
 	}
	
 	while(!File.eof() && found==false)
 	{
 		File.read(reinterpret_cast<char *> (&ac), sizeof(product));
		
 		if(ac.return_slno()==n){
 		    cout << "details found ..." <<endl;
 			ac.clean_display();
 			cout<<"\n\nEnter The New Details of Item "<<n<<endl;
 			ac.modify();
 			int pos=(-1)*static_cast<int>(sizeof(product));
 			File.seekp(pos,ios::cur);
 		    File.write(reinterpret_cast<char *> (&ac), sizeof(product));
 		    cout<<"\n\n\t Record Updated";
 		    found=true;
 	       }
		
		File.close();
		if(found==false)
 		cout<<"\n\n Record Not Found ";
      }
 }
 
 void product::delete_entry() {
 	product ac;
 	unsigned int n;
	 
 	cout << "Enter the serial number of Item ??  "; cin >> n;
 	ifstream inFile;
 	ofstream outFile;
 	inFile.open("data.dat",ios::binary);
	 
 	if(!inFile)
 	{
 		cout<<"File could not be open !! Press any Key...";
 		return;
 	}
	 
 	outFile.open("temp.dat",ios::binary);
 	inFile.seekg(0,ios::beg);
	 
 	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(product)))
 	{
 		if(ac.return_slno()!=n)
 		{
 			outFile.write(reinterpret_cast<char *> (&ac), sizeof(product));
 		}
 	}
	 
        inFile.close();
 	outFile.close();
 	remove("data.dat");
 	rename("temp.dat","data.dat");
 	cout<<"\n\n\tRecord Deleted ...";
 }
 
 void product::modify() {
 	cout<<"\nEnter The serial no. of Item : "; cin>>slno;
 	cout<<"\nEnter The Name of Item : "; cin.ignore(); cin.getline(name,50);
 	cout<<"\nEnter The Price of Item : "; cin>>price;
 	cout<<"\nEnter Item Details : "; cin.ignore(); cin.getline(details,100);
 }
 
 void product::clean_display() {
 	cout<<slno<<setw(10)<<" "<<name<<setw(6)<<price<<setw(10)<<" "<<details<<endl;
 }
 
 int product::return_slno() const
 {
 	return slno;
 }
 
 //************************************************************************************
 //    	THE MAIN FUNCTION OF PROGRAM
 //**********************************************************************************
 void welcome() {
    cout <<"TATA POWER IT ASSET SOFTWARE" <<endl;
     cout <<"\tdesign and developed by \nrishikesh maurya nit jamshedpur as summer project."<<endl;
    cout << "copyright TATA POWER, all right reserved" <<endl;
 }
 int main() {
         welcome();
         new product();
 return 0;
 }
