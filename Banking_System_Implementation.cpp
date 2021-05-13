#include<bits/stdc++.h>
using namespace :: std;

int AccountNumber=0;

class bankAccount{
	
	
	public:
		int accNo;
		char name[50];
		int amount;
		//string type;
	
		void create();
		
		void modify();
		
		void show();
		
		void deposit();
		
		void withdraw();
};

void bankAccount:: create(){
		cout<<"Enter the name of the Account Holder: ";
		cin.ignore();                                  //cin.ignore() is used to clear the input buffer so that getline can work after a cin
		cin.getline(name, 100);
		cout<<"Enter amount to be deposited(in rupees): ";
		cin>>amount;
		if(amount<5000){
			cout<<"Amount less than minimum account balance(5000 Rs)\n";
			cout<<"Account could not be created. Try again.";
			amount=0;
			accNo=-1;
			return;
		}
		else{
			accNo=AccountNumber;
			AccountNumber++;
		}
		cout<<"Account Created!"<<endl;
		cout<<"Your Account Number is "<<accNo<<endl;
	}
	
void bankAccount:: modify(){
		cout<<"Account Number: "<<accNo;
		cout<<"Enter modified name: ";
		cin.ignore();
		cin.getline(name, 100);
		cout<<"Enter modified balance amount: ";
		cin>>amount;
		cout<<"Account is succesfully modified!\n";
		return;
}

void bankAccount:: show(){
		cout<<"Account Number: "<<accNo<<endl;
		cout<<"Name of Account Holder: "<<name<<endl;
		cout<<"Account Balance: "<<amount<<endl;
}

void bankAccount:: deposit(){
	cout<<"Enter amount to be deposited: ";
	int deposit;
	cin>>deposit;
	amount+=deposit;
	cout<<"Transaction successful!";
}

void bankAccount:: withdraw(){
	int withdraw;
	cout<<"Enter amount to be withdrawn: ";
	cin>>withdraw;
	if((amount-5000-withdraw)<0){
		cout<<"Not allowed/n";
		cout<<"Current Balance: "<<amount<<"Rs"<<endl;
		cout<<"Maximum allowed withdrawal: "<<(amount-5000)<<"Rs"<<endl;
	}
	else{
		amount=amount-withdraw;
		cout<<"Transaction successful!\n";
	}
}


void writeAccount();

void modifyAccount(int );

void display_single(int );

void deposit_withdraw(int, int);

void deleteAccount(int );



int main(){
	int flag=0;
	int users=0;
	
	bankAccount t;
	ifstream inFile;
	inFile.open("data.txt", ios::binary);
	while(inFile.read(reinterpret_cast<char*> (&t), sizeof(bankAccount))){
		AccountNumber=t.accNo;
	}
	AccountNumber++;

	inFile.close();
	

	
	while(flag==0){
		cout<<"WELCOME TO ADITYA'S BANK\n";
		cout<<"Select an option(1-6)"<<endl;
		cout<<"\t1. New Account"<<endl<<"\t2. Modify Existing Account"<<endl<<"\t3. Show Existing Account Details\n"<<"\t4. Deposit\n"<<"\t5. Withdraw\n"<<"\t6. Delete Existing Account\n"<<"\t7. Exit\n";
	
		//bankAccount V[10000];
	
		int option;
		cin>>option;
	
		int n=0;
		int i=0;
		switch(option){
			case 1: 
			
				//V[users].create();
				writeAccount();
				users++;
				break;
			case 2:
				cout<<"Enter Account Number: ";
			
				cin>>n;
			
				if(n>=10000){
					cout<<"Account does not exist";
					break;
				}
				//V[n-1].modify();
				modifyAccount(n);
				break;
			case 3:
				cout<<"Enter Account Number: ";
				cin>>n;
			
				if(n>=10000){
					cout<<"Account does not exist";
					break;
				}
				//V[n-1].show();
				display_single(n);
				break;
			case 4:
				cout<<"Enter Account Number: ";
				
				cin>>n;
			
				if(n>=10000){
					cout<<"Account does not exist";
					break;
				}
				//V[n-1].deposit();
				deposit_withdraw(n, 1);
				break;
			case 5:
				cout<<"Enter Account Number: ";
			
				cin>>n;
			
				if(n>=10000){
					cout<<"Account does not exist";
					break;
				}
				//V[n-1].withdraw();
				deposit_withdraw(n, 2);
				break;
			case 6:
				cout<<"Enter Account Number: ";
				
				cin>>n;
				deleteAccount(n);
				break;
			case 7:
				break;
		}
		cout<<"Do you want to exit(Y/N): ";
		char response;
		cin>>response;
		if(response=='Y'){
			flag=1;
		}
	}
	return 0;
}

void writeAccount(){
	
	bankAccount a;
	ofstream outFile;
	outFile.open("data.txt", ios::binary|ios::app);
	a.create();
	outFile.write(reinterpret_cast<char *> (&a), sizeof(bankAccount));
	outFile.close();
	

}

void modifyAccount(int ANo){
	bool found=false;
	bankAccount a;
	fstream File;
	File.open("data.txt", ios::binary|ios::in|ios::out);
	if(!File){
		cout<<"File could not be opened! Press any key..."<<endl;
		return;
	}
	while(!File.eof() && found==false){
		File.read(reinterpret_cast<char*> (&a), sizeof(bankAccount));
		if(a.accNo==ANo){
			found=true;
			a.modify();
			int pos=(-1)*static_cast<int>(sizeof(bankAccount));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char*> (&a), sizeof(bankAccount));
			cout<<"Record Updated.";
		}
	}
	File.close();
	if(found==false){
		cout<<"Record Not Found"<<endl;
	}
	return;
}

void display_single(int ANo){
	bool found=false;
	bankAccount a;
	ifstream inFile;
	inFile.open("data.txt", ios::binary);
	if(!inFile){
		cout<<"File could not be opened. Press any key..."<<endl;
		return;
	}
	
	while(inFile.read(reinterpret_cast<char*> (&a), sizeof(bankAccount))&& !found){
		if(a.accNo==ANo){
			found=true;
			a.show();
		}
	}
	
	inFile.close();
	if(found==false){
		cout<<"Record not found."<<endl;
	}
	return;
}

void deposit_withdraw(int n, int temp){
	bool found=false;
	bankAccount a;
	fstream File;
	File.open("data.txt", ios::binary|ios::in|ios::out);
	if(!File){
		cout<<"File could not be opened. Press any key..."<<endl;
		return;
	}
	while(!File.eof() && !found){
		File.read(reinterpret_cast<char*> (&a), sizeof(bankAccount));
		if(a.accNo==n && temp==1){
			a.deposit();
			found=true;
		}
		if(a.accNo==n && temp==2){
			a.withdraw();
			found=true;
		}
		
	}
	
	int pos=(-1)*static_cast<int>(sizeof(bankAccount));
	File.seekp(pos, ios::cur);
	File.write(reinterpret_cast<char*> (&a), sizeof(bankAccount));
	cout<<"Record Updated."<<endl;
	
	if(found==false){
		cout<<"Record not found."<<endl;
		return;
	}
}

void deleteAccount(int ANo){
	bankAccount a;
	ifstream inFile;
	ofstream outFile;
	inFile.open("data.txt", ios::binary);
	if(!inFile){
		cout<<"File could not be opened. Press any key... "<<endl;
		return;
	}
	
	outFile.open("temp.txt", ios::binary);
	inFile.seekg(0, ios::beg);
	
	while(!inFile.eof()){
		inFile.read(reinterpret_cast<char*> (&a), sizeof(bankAccount));
		if(a.accNo!=ANo){
			outFile.write(reinterpret_cast<char*> (&a), sizeof(bankAccount));
		}
	}
	
	inFile.close();
	outFile.close();
	remove("data.txt");
	rename("temp.txt","data.txt");
	cout<<"Record deleted successfully"<<endl;
}
