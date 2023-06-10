#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>

using namespace std;

class Account{
public:
    Account(string accountNumber, double balance) : accountNumber_(accountNumber), balance_(balance){
        //
    }

    void deposit(double amount){
        balance_ = balance_ + amount;
        std::cout << "Account number: " << getAccountNumber() << ": " << "Deposit successful. New balance: " << balance_ << std::endl;
    }

    void withdraw(double amount){
        balance_ = balance_ - amount;
        std::cout << "Account number: " << getAccountNumber() << ": " << "Withdraw successful. New balance: " << balance_ << std::endl;
    }

    double getBalance(){
        return balance_;
    }

    string getAccountNumber(){
        return accountNumber_;
    }
protected:
    string accountNumber_;
    double balance_;

};

class CheckingAccount : public Account{
public:
    CheckingAccount(string accountNumber, double balance) : Account("C10002", 4000.0){
        accountNumber_ = accountNumber;
        balance_ = balance;
    }

    void withdraw(double amount){
        balance_ = balance_ - amount - 1.5;
        std::cout << "Account number: " << getAccountNumber() << ": " << "Withdraw successful. New balance: " << balance_ << std::endl;
    }
};

class SavingsAccount : public Account{
public:
    SavingsAccount(string accountNumber, double balance, double interestRate) : Account("C20003", 5000){
        accountNumber_ = accountNumber;
        balance_ = balance;
        interestRate_ = interestRate;
    }

    void addInterest(){
        balance_ = balance_ + balance_*(interestRate_/100.0);
        std::cout << "Account number: " << getAccountNumber() << ": " << "Interest credited. New balance: " << balance_ << std::endl;
        //std::cout << balance_;
    }

    double getInterestRate(){
        return interestRate_;
    }
protected:
    double interestRate_;
};

class Client{
public:
    Client(string name) : name_(name){
        //
    }

    void addAccount(Account* account){
        accounts.emplace_back(account);
    }

    void printAccount(){
        for (Account *value : accounts){
            std::cout << value->getAccountNumber() << " --- $" << value->getBalance() << "\n";
        }
    }

    string getName(){
        return name_;
    }

private:
    string name_;
    vector <Account*> accounts;
};

class Bank{
public:
    void addClient(Client* client){
        clients.emplace_back(client);
    }

    void printClients(){
        for (auto * value : clients){
            std::cout << "\nAccounts for "<< value->getName() << ":\n";
            value->printAccount();
            std::cout << endl;
            sleep (2);
        }
    }

private:
    vector <Client *> clients;
};

int main()
{
    // Create accounts
    Account account1("A10001", 5000);
    SavingsAccount account2("S10001", 10000, 2.5);
    CheckingAccount account3("C10001", 2000);

    // Deposit and withdraw from accounts
    account1.deposit(1000);
    sleep (2);
    account1.withdraw(2000);
    sleep (2);
    account2.deposit(500);
    sleep (2);
    account2.addInterest();
    sleep (2);
    account3.withdraw(500);
    sleep (2);

    // Create clients and add accounts to them
    Client client1("John Doe");
    client1.addAccount(&account1);
    client1.addAccount(&account2);
    //client1.printAccount();

    Client client2("Jane Smith");
    client2.addAccount(&account3);
    //client2.printAccount();

    // Create bank and add clients to it
    Bank bank;
    bank.addClient(&client1);
    bank.addClient(&client2);

    // Print bank clients and their accounts
    bank.printClients();
    return 0;
}
