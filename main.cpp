/*
Project C++
Bank 
By: Naushik Ravikrindi
*/


#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include <cstring>
using namespace std;

//customised data structure to store account type
enum AccountType {CURRENT,SAVINGS};


class Bank{
  
  private:
    static long count;
    const static long ACCOUNT_NUMBER_BEGIN = 271020210000045;
    string depositer_name_;
    AccountType account_Type_;
    long account_no_;
    long balance_amount_;
    string address_;
    char phone_no_[10];

  public:
  Bank(){

  }
  //this stores customers' details in the file
    void createCustomerRecord(Bank bank){
      string file_name = depositer_name_+"_"+getPhoneNumber()+".txt";
      ofstream fwrite(file_name);fwrite.write((char *)&bank ,sizeof(bank));

      fwrite.close();

      //fwrite.write((char *)& *this,sizeof(this));
      // fwrite<<depositer_name_<<"\n";
      // fwrite<<account_Type_<<"\n";
      // fwrite<<account_no_<<"\n";
      // fwrite<<address_<<"\n";
      // fwrite<<phone_no_<<"\n";
      // fwrite.close();
      
    }
    //reads cutomer details from the file created while initialising.. 
    void readCustomerRecord(){
      string file_name = depositer_name_+"_"+getPhoneNumber()+".txt";
      ifstream fread(file_name);
      Bank bank;
      fread.read((char *)&bank ,sizeof(bank));
      bank.showData();
      cout<<endl;
      
      fread.close();
      
      // char readName[30];
      // ifstream ReadFromFile("harmantraining.txt");
      // while(fread)
      // {
      //   fread.getline(readName,30);
      //   cout<<"\n\n"<<readName;
      // }
      
    }

    //constructor to initialise data
    Bank(string name,AccountType acc_type,string add,char ph_no[]){
      depositer_name_ = name;
      account_Type_ = acc_type;
      account_no_ = ACCOUNT_NUMBER_BEGIN + count;
      //balance_amount_ = 
      address_ = add;
      strcpy(phone_no_, ph_no);
      count++;
      balance_amount_ = 100;
      
      
     
    }
    //displaying the customer data
     void showData(){
       cout<<"***********************\n";
      cout<<"Displaying user data\n";
      cout<<"Account Holder's Name : "<<depositer_name_<<"\n";
      cout<<"Account Number : "<<account_no_<<"\n";
      cout<<"Account Type : "<<(account_Type_==SAVINGS?"SAVINGS":"CURRENT")<<"\n";
      cout<<"Phone number : "<<phone_no_<<"\n";
      cout<<"Address :"<<address_<<"\n";
      cout<<"Balance Amount :"<<balance_amount_<<"\n";
      cout<<"************************\n";

    }
    string getDepositerName(){
      return depositer_name_;
    }
    long getAccountNumber(){
      return account_no_;
    }
    string getPhoneNumber(){
      return phone_no_;
    }
    string getAddress(){
      return address_;
    }
    void displayBalance(){
      cout<<"Balance Amount: "<<balance_amount_<<"\n";
    }
    //reading the customer transactions from the file
    void showCustomerBankStatement(){
      string file_name = depositer_name_+"_"+getPhoneNumber()+"_bankstatement"+".txt";
      ifstream cust_file(file_name);
      cout<<"Bank Statement\n";
      char transaction[30];
      cust_file.seekg(0);
      while(cust_file)
      {
          cust_file.getline(transaction,30);
          cout<<"\n"<<transaction;
      }
      cust_file.close();
    }
    //storting the customer transactions into the file
    void EnterTransactionIntoCustFile(long amount){
      string file_name = depositer_name_+"_"+phone_no_+"_bankstatement"+".txt";
      fstream cust_file(file_name, ios::in | ios::out | ios::app);
      
      string transaction = to_string(amount);
      for(char c : transaction){
        cust_file.put(c);
      }
      cust_file.put('\n');
      cout<<"Bank Statement\n";
      cust_file.seekg(0);

      char c;
      cust_file.get(c);
      cout<<c;
      while(cust_file)
      {
        cust_file.get(c);
        cout<<c;
      }
      cust_file.close();
    }
    void assignInitialBalance(){
      
    }
    void depositAmount(long deposited_amount){
      displayBalance();
      balance_amount_+=deposited_amount;
      cout<<deposited_amount<<" Amount Deposited\n";
      displayBalance();
      EnterTransactionIntoCustFile(deposited_amount);
    }

    void withdrawAmount(long withdraw_amount){
      displayBalance();
      if(withdraw_amount <= balance_amount_){
        balance_amount_ -=withdraw_amount;
        cout<<withdraw_amount<<" Amount deducted\n";
      }
      else{
        cout<<"Balance amount is less than withrawal amount.\nPlease check the amount to withdraw.\n";
        displayBalance();
        return;
      }
      displayBalance();
      EnterTransactionIntoCustFile(-1*withdraw_amount);
    }


    static long getCount(){
      return count;
    }

};
long Bank::count;
vector<Bank> AccountHolders;


int getSize(vector<Bank> AccountHolders){
  return AccountHolders.empty() ? 0 : AccountHolders.size();
}

int AccountExists( long acc_no){
  int i;
  for(i=0;i<AccountHolders.size();i++){
    if(AccountHolders[i].getAccountNumber() == acc_no){
      return i;
    }
  }
  return -1;
}
void addNewUser(){
  char ph_no[10];
  string address,name;
  char account_type[7];
  AccountType AccType;
  cout<<"Enter your name: \n";
  cin.ignore();
  getline(cin,name);
  cout<<"Enter type of account to be created Current/Savings\n";
  cin.ignore();         
  cin>>account_type;
  for(int i=0; i<strlen(account_type);i++){
    account_type[i]=toupper(account_type[i]);
  }
  if(strcmp(account_type,"SAVINGS")){
    AccType =  SAVINGS;
  }
  else if(strcmp(account_type,"CURRENT")){
    AccType =CURRENT;
  }
  
  cout<<"Enter your Address:\n";
  cin.ignore();
  getline(cin,address);
  cout<<"Enter your Phone number :\n";
    
  cin>>ph_no;
  
  AccountHolders.push_back(  Bank(name,AccType,address,ph_no));
  int sz = getSize(AccountHolders);
  AccountHolders[sz-1].createCustomerRecord(AccountHolders[sz-1]);
  AccountHolders[sz-1].readCustomerRecord();
  cout<<"Your account is created\n";
}

void retrieveData(){

}

int main() {
  retrieveData();
  while(1){
     cout<<"Welcome to NASH BANK\n";
     cout<<"********************\n";
     
    cout<<"1.New User\n";
    cout<<"2.Existing User\n";
    cout<<"Choose 1 or 2\n";
    int option1;    
    //cin.ignore();
    cin>>option1;
    if(option1 == 1){
      addNewUser();
    }
    else if(option1 == 2){
    cout<<"1.Display entire data\n";
    cout<<"2.Delete account\n";
    cout<<"3.Deposit\n";
    cout<<"4.Withdrawal\n";
    cout<<"5.Check Account exists or not\n";
    cout<<"6.Get account holder name\n";
    cout<<"7.Get Address of the holder\n";
    cout<<"8.Get Balance\n";
    cout<<"9.Get bank statement\n";
    cout<<"10.Get Complete details\n";
    cout<<"11.Interest \n";
    cout<<"12.Display account number of last\n";
      int option2;
      cin>>option2;
      cout<<"Choose 1-12\n";
      cin.ignore();
      long acc_no;
      if(option2!=1){
        cout<<"Enter Account Number\n";
        
        cin>>acc_no;
      }
      
      switch(option2){
        case 1 :{
          cout<<"Displaying Entire data:\n";
          for(int i=0;i<AccountHolders.size();i++){
          AccountHolders[i].readCustomerRecord();
          
        }

        }
        break;
        case 2:{
          cout<<"Displaying Entire data:\n";
        }
        break;
        case 3:{
          cout<<"Amount deposit\n";          
          long amount;
          int idx = AccountExists(acc_no);
          if(idx>=0){
            cout<<"Enter amount you want to deposit\n";
            cin.ignore();
            cin>>amount;
            AccountHolders[idx].depositAmount(amount);
          }
          else{
            cout<<"Account not found\n";
          }
         
          
        }
        break;
        case 4:{
          cout<<"Amount withdraw\n";          
          long amount;
          int idx = AccountExists(acc_no);
          if(idx>=0){
            cout<<"Enter amount you want to withdraw\n";
            cin.ignore();
            cin>>amount;
            AccountHolders[idx].withdrawAmount(amount);
          }
          else{
            cout<<"Account not found\n";
          }
        }
        break;
        case 5:{
          cout<<"Checking account exists or not\n";
           int idx = AccountExists(acc_no);
          if(idx>=0){
            cout<<"Account exists\n";
            AccountHolders[idx].readCustomerRecord();
          }
          else{
            cout<<"Account does not exist\n";
          }
        }
        break;
        case 6:{
          
          int idx = AccountExists(acc_no);
          if(idx>=0){          
            cout<<"Account Holder Name: "<<AccountHolders[idx].getDepositerName();
          }
          else{
            cout<<"Account does not exist\n";
          }
        }
        break;
        case 7:{
          int idx = AccountExists(acc_no);
          if(idx>=0){          
            cout<<"Account Holder Name: "<<AccountHolders[idx].getAddress();
          }
          else{
            cout<<"Account does not exist\n";
          }
        }
        break;
        case 8:{
          int idx = AccountExists(acc_no);
          if(idx>=0){          
            cout<<"Account Holder address: ";
            AccountHolders[idx].displayBalance();
          }
          else{
            cout<<"Account does not exist\n";
          }
        }
        break;
        case 9:{
          int idx = AccountExists(acc_no);
          if(idx>=0){       
            AccountHolders[idx].showCustomerBankStatement();
          }
          else{
            cout<<"Account does not exist\n";
          }
        }
        break;
        case 10:{
          int idx = AccountExists(acc_no);
          if(idx>=0){       
          AccountHolders[idx].readCustomerRecord();
          AccountHolders[idx].showCustomerBankStatement();
          }
          else{
            cout<<"Account does not exist\n";
          }
        }
        break;
        case 11:{

        }
        break;
        case 12:{
          cout<<"Account number of Last entry: "<<AccountHolders.end()->getAccountNumber();
        } 
        break;
        default:{
          cout<<"Please choose from 1-12 options\n";
        }
        break;
        }
      
    }

  }
        
        
} 