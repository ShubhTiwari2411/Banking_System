#include<iostream>
#include<fstream>
#include<cstdlib>
#include<vector>
#include<map>
using namespace std;

#define Min_Balance 500
class Insufficient_Funds:exception{};

class Account
{
  private:
  long accountNumber;
  string firstName;
  string lastName;
  float balance;
  static long NextAccountNumber;

  public:
  Account(){}
  Account(string fn,string ln,float bl)
  {
    NextAccountNumber++;
    accountNumber=NextAccountNumber;
    firstName=fn;
    lastName=ln;
    balance=bl;
  }
  long getAccNo()
  {
    return accountNumber;
  }
  string getFirstName()
  {
    return firstName;
  }
  string getLastName()
  {
    return lastName;
  }
  float getBalance()
  {
    return balance;
  }

  void Deposit(float amount)
  {
    balance+=amount;
  }
  
void Withdraw(float amount)
  {
    if(balance-amount<Min_Balance)
    throw Insufficient_Funds();

    else
    balance-=amount;
  }
  
  
  static void setLastAccountNumber(long accountNumber)
  {
    NextAccountNumber=accountNumber;
  }
  static long getLastAccountNumber()
  {
    return NextAccountNumber;
  }

  friend ofstream & operator <<(ofstream &ofs,Account &acc);
  friend ifstream & operator >>(ifstream &ifs,Account &acc);
  friend ostream & operator <<(ostream &os,Account &acc);

};

long Account::NextAccountNumber=0;

class Bank
{
  private:
  map<long,Account> accounts;
  public:
  Bank();
  Account openAccount(string fname,string lname,float balance);
  Account Balance_Enquiry(long accountNumber);
  Account Deposit(long accountNumber,float amount);
  Account Withdraw(long accountNumber,float amount);
  void CloseAccount(long accountNumber);
  void ShowAllAccounts();
  ~Bank();
};

int main()
{
  Bank b;
  Account acc;
  int choice;
  string fname,lname;
  long accountNumber;
  float balance,amount;
  cout<<"\n\t***Banking System***"<<endl;
  try{
do
  {
    cout<<"\n\tSelect One Option Below";
    cout<<"\n\t 1)Open An Account";
    cout<<"\n\t 2)Balance Enquiry";
    cout<<"\n\t 3)Deposit";
    cout<<"\n\t 4)Withdraw";
    cout<<"\n\t 5)Close An Account";
    cout<<"\n\t 6)Show All Accounts";
    cout<<"\n\t 7)Quit";
    cout<<"\n\t Enter Your Choice: ";
    cin>>choice;
    switch(choice)
    {
      case 1:
      cout<<"Enter First Name: "<<endl;
      cin>>fname;
      cout<<"Enter Last Name: "<<endl;
      cin>>lname;
      cout<<"Enter initil Balance: "<<endl;
      cin>>balance;
      acc=b.openAccount(fname,lname,balance);
      cout<<"Congratulations Account is Created"<<endl;
      break;

      case 2:
      cout<<"Enter Account Number: "<<endl;
      cin>>accountNumber;
      acc=b.Balance_Enquiry(accountNumber);
      cout<<"Your Account Details: "<<endl;
      cout<<acc<<endl;
      break;

      case 3:
      cout<<"Enter Account Number: "<<endl;
      cin>>accountNumber;
      cout<<"Enter Balance: "<<endl;
      cin>>amount;
      acc=b.Deposit(accountNumber,amount);
      cout<<"Amount is Deposited"<<endl;
      cout<<acc<<endl;
      break;

      case 4:
      cout<<"Enter Account Number: "<<endl;
      cin>>accountNumber;
      cout<<"Enter Balance: "<<endl;
      cin>>amount;
      acc=b.Withdraw(accountNumber,amount);
      cout<<"Amount withdrawn"<<endl;
      cout<<acc<<endl;
      break;

      case 5:
      cout<<"Enter Account Number: "<<endl;
      cin>>accountNumber;
      b.CloseAccount(accountNumber);
      cout<<"Account is Closed"<<endl;
      cout<<acc<<endl;
      
      case 6:
      b.ShowAllAccounts();

      case 7:
      break;

      default:
      cout<<"Enter Correct Choice"<<endl;
      exit(0);
    }
  } while (choice!=7);

  }
  

  catch(Insufficient_Funds inf)
  {
    cout<<"Insufficient Funds"<<endl;
  }
  return 0;
  
}

ofstream & operator <<(ofstream &ofs,Account &acc)
{
  ofs<<acc.accountNumber<<endl;
  ofs<<acc.firstName<<endl;
  ofs<<acc.lastName<<endl;
  ofs<<acc.balance<<endl;
  return ofs;
}


ifstream & operator >>(ifstream &ifs,Account &acc)
{
  ifs>>acc.accountNumber>>acc.firstName>>acc.lastName>>acc.balance;
  return ifs;
}

ostream & operator <<(ostream &os,Account &acc)
{
  os<<"Account Number: "<<acc.getAccNo()<<endl;
  os<<"First Name: "<<acc.getFirstName()<<endl;
  os<<"Last Name: "<<acc.getLastName()<<endl;
  os<<"Balance: "<<acc.getBalance()<<endl;
  return os;
}

Bank::Bank()
{
  Account account;
  ifstream infile;
  infile.open("Bank.data");
  if(!infile)
  {
    cout<<"Error in Opening! File Not Found!!"<<endl;
    return;
  }
  while(!infile.eof())
  {
    infile>>account;
    accounts.insert(pair<long,Account>(account.getAccNo(),account));
  }
  Account ::setLastAccountNumber(account.getAccNo());
  infile.close();


}

Account Bank::openAccount(string fname,string lname,float balance)
{
  ofstream outfile;
  Account account(fname,lname,balance);
  accounts.insert(pair<long,Account>(account.getAccNo(),account));
  outfile.open("Bank.data",ios::trunc);

  map<long,Account>::iterator itr;
  for(itr=accounts.begin();itr!=accounts.end();itr++)
  {
    outfile<<itr->second;
  }
  outfile.close();
  return account;
}


Account Bank::Balance_Enquiry(long accountNumber)
{
  map<long,Account>::iterator itr;
  itr=accounts.find(accountNumber);
  return itr->second;


}
  Account Bank::Deposit(long accountNumber,float amount)
  {
    map<long,Account>::iterator itr;
  itr=accounts.find(accountNumber);
  itr->second.Deposit(amount);
  return itr->second;


  }
  Account Bank::Withdraw(long accountNumber,float amount)
  {
     map<long,Account>::iterator itr;
  itr=accounts.find(accountNumber);
  itr->second.Withdraw(amount);
  return itr->second;
  }
  void Bank::CloseAccount(long accountNumber)
  {
    map<long,Account>::iterator itr;
  itr=accounts.find(accountNumber);
  cout<<"Account Deleted "<<endl;
  accounts.erase(accountNumber);
  }
  void Bank::ShowAllAccounts()
  {
    map<long,Account>::iterator itr;
    for(itr=accounts.begin();itr!=accounts.end();itr++)
    {
      cout<<"Account "<<itr->first<<endl;
      cout<<itr->second<<endl;
    }
  }
  Bank::~Bank()
  {
    ofstream outfile;
    outfile.open("Bank.data",ios::trunc);

    map<long,Account>::iterator itr;
  for(itr=accounts.begin();itr!=accounts.end();itr++)
  {
    outfile<<itr->second;
  }
  outfile.close();

  }
