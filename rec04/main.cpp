// rec02.cpp
// 2124 21S
// David Chang
// Rec04 is a conglomeration of functions to show how to use classes,
// incorporate data hiding, and scope of functions.
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

// Account structure holds two fields: name and account number.
struct Account{
  string name;
  int accNumber;
};

// Account_Class class holds the same values as structure but uses a constructor
// keeping its variables private.
class Account_Class {
  friend ostream& operator<<(ostream& os, const Account_Class& account);
public:
	Account_Class(const string& newName, int newNumber) : name(newName), accNumber(newNumber) {}
  // getter methods for account name and number.
  int getAccountNumber() const{  //what
    return accNumber;
  }
  const string& getAccountName() const{ //what
    return name;
  }

private:
	string name;
  int accNumber;
};

class Transaction{
  friend ostream& operator<<(ostream& os,const Transaction& transaction);
public:
  Transaction(const string& type, int amount) : transType(type), amountTransferred(amount) {}
private:
  string transType;
  int amountTransferred;
};

class Transaction_Account {
  friend ostream& operator<<(ostream& os, const Transaction_Account& account);
public:
  Transaction_Account(const string& accName, int accAmount) : name(accName), accNum(accAmount) {}

  // methods
  void deposit(int amount_deposited){
    balance = amount_deposited + balance;
    transactions.emplace_back("Deposit",amount_deposited);
  }
  void withdraw(int amount_withdrawn){
    if(balance - amount_withdrawn < 0){
      cerr << "Cannot withdraw " << amount_withdrawn << ". Insufficient Funds." << endl;
    }
    else{
      balance = balance - amount_withdrawn;
      transactions.emplace_back("Withdrawal",amount_withdrawn);
    }
  }
  int getAccountNumber() const {
    return accNum;
  }

  private:
  vector<Transaction> transactions;
  string name;
  int accNum;
  int balance = 0;
};

class Nested_Transaction_Account_Public{
  friend ostream& operator<<(ostream& os, const Nested_Transaction_Account_Public& account);
public:
  class Transaction{
    friend ostream& operator<<(ostream& os,const Transaction& transaction);
  public:
    Transaction(const string& type, int amount) : transType(type), amountTransferred(amount) {}
  private:
      string transType;
      int amountTransferred;
  };

  Nested_Transaction_Account_Public(const string& accName, int accAmount) : name(accName), accNum(accAmount) {}

  // methods
  void deposit(int amount_deposited){
    balance = amount_deposited + balance;
    transactions.emplace_back("Deposit",amount_deposited);
  }

  void withdraw(int amount_withdrawn){
    if(balance - amount_withdrawn < 0){
      cerr << "Cannot withdraw " << amount_withdrawn << ". Insufficient Funds." << endl;
    }
    else{
      balance = balance - amount_withdrawn;
      transactions.emplace_back("Withdrawal",amount_withdrawn);
    }
  }
  int getAccountNumber() const {
    return accNum;
  }
private:
  vector<Transaction> transactions;
  string name;
  int accNum;
  int balance = 0;
};

class Nested_Transaction_Account_Private{
  friend ostream& operator<<(ostream& os, const Nested_Transaction_Account_Private& account);

public:
  Nested_Transaction_Account_Private(const string& accName, int accAmount) : name(accName), accNum(accAmount) {}
  // methods
  void deposit(int amount_deposited){
    balance = amount_deposited + balance;
    transactions.emplace_back("Deposit",amount_deposited);
  }
  void withdraw(int amount_withdrawn){
    if(balance - amount_withdrawn < 0){
      cerr << "Cannot withdraw " << amount_withdrawn << ". Insufficient Funds." << endl;
    }
    else{
      balance = balance - amount_withdrawn;
      transactions.emplace_back("Withdrawal",amount_withdrawn);
    }
  }
  //required for search function.
  int getAccountNumber() const {
    return accNum;
  }
private:
  class Transaction{
    friend ostream& operator<<(ostream& os, 
      const Nested_Transaction_Account_Private::Transaction& transaction){
      os << "Type: " << transaction.transType << endl;
      os << "Amount: " << transaction.amountTransferred << endl;
      return os;
    }
  public:
    Transaction(const string& type, int amount) : transType(type), amountTransferred(amount) {}
  private:
    string transType;
    int amountTransferred;
  };

  vector<Transaction> transactions;
  string name;
  int accNum;
  int balance = 0;
};

//method prototype for searching accounts.
size_t searchAccount(int lookingNum, const vector<Transaction_Account>& accounts);
size_t searchAccount2(int lookingNum, 
  const vector<Nested_Transaction_Account_Public>& accounts);
size_t searchAccount3(int lookingNum, 
  const vector<Nested_Transaction_Account_Private>& accounts);  
ostream& operator<<(ostream& os, const Account_Class& account) {
  //os << "Account name: " << account.getAccountName() << endl; 
  //os << "Account number: " << account.getAccountNumber() << endl;
  os << "Account name: " << account.name << endl;
  os << "Account number: " << account.accNumber << endl;
  os << endl;
  return os;
}
ostream& operator<<(ostream& os, const Nested_Transaction_Account_Public::Transaction& transaction){
  os << "Type: " << transaction.transType << endl;
  os << "Amount: " << transaction.amountTransferred << endl;
  return os;
}
ostream& operator<<(ostream& os, const Transaction_Account& account){
  os << "Account Name: " << account.name << endl;
  os << "Account balance: " << account.balance << endl;
  os << "Account number: " << account.accNum << endl;
  for(size_t index = 0; index < account.transactions.size(); index++){
    os << account.transactions[index] << endl;
  }
  return os;
}
ostream& operator<<(ostream& os, const Nested_Transaction_Account_Public& account){
  os << "Account Name: " << account.name << endl;
  os << "Account balance: " << account.balance << endl;
  os << "Account number: " << account.accNum << endl;
  for(size_t index = 0; index < account.transactions.size(); index++){
    os << account.transactions[index] << endl;
  }
  return os;
}
ostream& operator<<(ostream& os, const Nested_Transaction_Account_Private& account){
  os << "Account Name: " << account.name << endl;
  os << "Account balance: " << account.balance << endl;
  os << "Account number: " << account.accNum << endl;
  for(size_t index = 0; index < account.transactions.size(); index++){
    os << account.transactions[index] << endl;
  }
  return os;
}
ostream& operator<<(ostream& os, const Transaction& transaction){
  os << "Type: " << transaction.transType << endl;
  os << "Amount: " << transaction.amountTransferred << endl;
  return os;
}

int main() {
  // initializes file reader and reads value to vector.
  ifstream reader("accounts.txt");
  if (!reader){
      cerr << "Could not open the file! \n";
      exit(1);
  }
  vector<Account> accounts;
  string newName;
  int newNumber;

  ///////////////////
  // formatting
  cout << endl;
  cout << "Using the structs and accessing fields directly";
  cout << endl << "-------------------------------" << endl << endl;
  ///////////////////

  while(reader >> newName >> newNumber){
    Account newAccount;
    newAccount.name = newName;
    newAccount.accNumber = newNumber;
    accounts.push_back(newAccount);
  }
  reader.close();
  // prints the contents of the newAccount vector
  for(size_t index = 0; index < accounts.size(); ++index){
    cout << "Account name: " << accounts[index].name << endl;
    cout << "Account number: " << accounts[index].accNumber << endl;
    cout << endl;
  }


  ///////////////////
  // formatting
  cout << endl;
  cout << "Using the { } operator and structs.";
  cout << endl << "-------------------------------" << endl << endl;
  ///////////////////


  // Does the same thing as above, but with the braces operator instead of
  // assigning fields manually.
  accounts.clear();
  reader.open("accounts.txt");
  if (!reader){
      cerr << "Could not open the file! \n";
      exit(1);
  }
  while(reader >> newName >> newNumber){
    Account newAccount{newName,newNumber};
    accounts.push_back(newAccount);
  }
  for(size_t index = 0; index < accounts.size(); ++index){
    cout << "Account name: " << accounts[index].name << endl;
    cout << "Account number: " << accounts[index].accNumber << endl;
    cout << endl; 
  }
  reader.close();


  ///////////////////
  // formatting
  cout << endl;
  cout << "Using the Account_Class to do the same thing. Printing with accessors.";
  cout << endl << "-------------------------------" << endl << endl;
  ///////////////////


  // Does the same thing as above but uses Account_Class and accessor methods.
  // recreated classVector as the Vector for Account_Class objects.
  reader.open("accounts.txt");
  if (!reader){
      cerr << "Could not open the file! \n";
      exit(1);
  }
  vector<Account_Class> classVector;
  while(reader >> newName >> newNumber){
    Account_Class newAccount{newName,newNumber};
    classVector.push_back(newAccount);
  }
  for(size_t index = 0; index < classVector.size();++index){
    cout << "Account name: " << classVector[index].getAccountName() << endl;
    cout << "Account number: " << classVector[index].getAccountNumber() << endl;
    cout << endl; 
  }
  reader.close();


  ///////////////////
  // formatting
  cout << endl;
  cout << "Using the Account_Class to do the same thing. Printing with operator.";
  cout << endl << "-------------------------------" << endl << endl;
  ///////////////////


  classVector.clear();
  reader.open("accounts.txt");
  if (!reader){
      cerr << "Could not open the file! \n";
      exit(1);
  }
  while(reader >> newName >> newNumber){
    Account_Class newAccount{newName,newNumber};
    classVector.push_back(newAccount);
  }
  for(size_t index = 0; index < classVector.size();++index){
    cout << classVector[index];
  }
  reader.close();


  ///////////////////
  // formatting
  cout << endl;
  cout << "Using the Account_Class to do the same thing. Printing with operator w/ friend.";
  cout << endl << "-------------------------------" << endl << endl;
  ///////////////////


  classVector.clear();
  reader.open("accounts.txt");
  if (!reader){
      cerr << "Could not open the file! \n";
      exit(1);
  }
  while(reader >> newName >> newNumber){
    //Account_Class newAccount{newName,newNumber};
    classVector.push_back(Account_Class(newName,newNumber));
  }
  for(size_t index = 0; index < classVector.size();++index){
    cout << classVector[index];
  }
  reader.close();


  ///////////////////
  // formatting
  cout << endl;
  cout << "Using the Account_Class to do the same thing. Printing with operator w/ friend.";
  cout << endl << "Using emplace_back";
  cout << endl << "-------------------------------" << endl << endl;
  ///////////////////


  classVector.clear();
  reader.open("accounts.txt");
  if (!reader){
      cerr << "Could not open the file! \n";
      exit(1);
  }
  while(reader >> newName >> newNumber){
    //Account_Class newAccount{newName,newNumber};
    classVector.emplace_back(newName,newNumber);
  }
  for(size_t index = 0; index < classVector.size();++index){
    cout << classVector[index];
  }
  reader.close();


  ///////////////////
  // formatting
  cout << endl;
  cout << "Using the Transaction Account";
  cout << endl << "-------------------------------" << endl << endl;
  ///////////////////


  reader.open("transactions.txt");
  if (!reader){
      cerr << "Could not open the file! \n";
      exit(1);
  }
  string command;
  int accNum,amt;
  vector<Transaction_Account> transactionAccounts;
  while(reader >> command){
    if(command == "Account"){
      string name;
      int balance;
      reader >> name;
      reader >> balance;
      transactionAccounts.emplace_back(name,balance);
    }
    else if(command == "Deposit"){
      reader >> accNum;
      reader >> amt;
      size_t index = searchAccount(accNum, transactionAccounts);
      transactionAccounts[index].deposit(amt);
    }
    else if(command == "Withdraw"){
      reader >> accNum;
      reader >> amt;
      size_t index = searchAccount(accNum, transactionAccounts);
      transactionAccounts[index].withdraw(amt);
    }
  }
  reader.close();
  for(size_t index = 0; index < transactionAccounts.size(); ++index){
    cout << transactionAccounts[index] << endl;
  }

  ///////////////////
  // formatting
  cout << endl;
  cout << "Using the nested transaction accounts public btw";
  cout << endl << "-------------------------------" << endl << endl;
  ///////////////////


  reader.open("transactions.txt");
  if (!reader){
      cerr << "Could not open the file! \n";
      exit(1);
  }
  vector<Nested_Transaction_Account_Public> nested_acc;
  while(reader >> command){
    if(command == "Account"){
      string name;
      int balance;
      reader >> name;
      reader >> balance;
      nested_acc.emplace_back(name,balance);
    }
    else if(command == "Deposit"){
      reader >> accNum;
      reader >> amt;
      size_t index = searchAccount2(accNum, nested_acc);
      nested_acc[index].deposit(amt);
    }
    else if(command == "Withdraw"){
      reader >> accNum;
      reader >> amt;
      size_t index = searchAccount2(accNum, nested_acc);
      nested_acc[index].withdraw(amt);
    }
  }
  reader.close();
  for(size_t index = 0; index < nested_acc.size(); ++index){
    cout << nested_acc[index] << endl;
  }


  ///////////////////
  // formatting
  cout << endl;
  cout << "Using the nested transaction accounts private btw";
  cout << endl << "-------------------------------" << endl << endl;
  ///////////////////


  reader.open("transactions.txt");
  if (!reader){
      cerr << "Could not open the file! \n";
      exit(1);
  }
  vector<Nested_Transaction_Account_Private> nested_acc_priv;
  while(reader >> command){
    if(command == "Account"){
      string name;
      int balance;
      reader >> name;
      reader >> balance;
      nested_acc_priv.emplace_back(name,balance);
    }
    else if(command == "Deposit"){
      reader >> accNum;
      reader >> amt;
      size_t index = searchAccount3(accNum, nested_acc_priv);
      nested_acc_priv[index].deposit(amt);
    }
    else if(command == "Withdraw"){
      reader >> accNum;
      reader >> amt;
      size_t index = searchAccount3(accNum, nested_acc_priv);
      nested_acc_priv[index].withdraw(amt);
    }
  }
  reader.close();
  for(size_t index = 0; index < nested_acc_priv.size(); ++index){
    cout << nested_acc_priv[index] << endl;
  }
}

size_t searchAccount(int lookingNum, const vector<Transaction_Account>& accounts){
  for(size_t index = 0; index < accounts.size(); ++index){
    if(accounts[index].getAccountNumber() == lookingNum){
      return index;
    }
  }
  return accounts.size();
}
size_t searchAccount2(int lookingNum, 
  const vector<Nested_Transaction_Account_Public>& accounts){
  for(size_t index = 0; index < accounts.size(); ++index){
    if(accounts[index].getAccountNumber() == lookingNum){
      return index;
    }
  }
  return accounts.size();
}
size_t searchAccount3(int lookingNum, 
  const vector<Nested_Transaction_Account_Private>& accounts){
  for(size_t index = 0; index < accounts.size(); ++index){
    if(accounts[index].getAccountNumber() == lookingNum){
      return index;
    }
  }
  return accounts.size();
}
