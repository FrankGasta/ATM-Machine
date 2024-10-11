#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <thread>
#include <chrono>

class Transaction {
private:
    int withdraw_checker(int amount, int balance);
    int withdraw_calc(int balance, int withdraw);
    int deposit_checker(int amount);
    int deposit_calc(int balance, int deposit);

public:
    void transaction_menu();
    void displayBalance();
    void transaction_withdraw();
    void transaction_deposit();
};

void Transaction::transaction_menu()
{
    Transaction trans; 

    std::string transactionMenu[4] = {"Balance Inquiry", "Withdraw", "Deposit", "Exit"};
    int pointer = 0;
    const char ENTER = 13;
    char ch = ' ';

    while(true) {
        system("cls");
        std::cout << "TRANSACTION MENU" << std::endl << std::endl;

        for(int i=0; i<4; ++i) {
            if(i==pointer){
                std::cout << transactionMenu[i] << std::endl;
            } else {
                std::cout << transactionMenu[i] << std::endl;
            }
        }

        while(true) {
            if(GetAsyncKeyState(VK_UP) != 0) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                --pointer;
                if(pointer == -1){
                    pointer = 3;
                }
                break;
            }
            else if(GetAsyncKeyState(VK_DOWN) != 0) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                ++pointer;
                if(pointer == 4){
                    pointer = 0;
                }
                break;
            }
            else if(ch=getch() == ENTER) {
                switch(pointer) {
                    case 0:
                    {
                        trans.displayBalance();
                        break;
                    }
                    case 1:
                    {
                        trans.transaction_withdraw();
                        break;
                    }
                    case 2:
                    {
                        trans.transaction_deposit();
                        break;
                    }
                    case 3:
                    {
                        exit(0);
                    }
                }
                break;
            }
        }
    }
}

void Transaction::displayBalance()
{
    int balance;
    std::ifstream infile("account.txt");
    if (infile.is_open()) {
        infile >> balance;
        infile.close();
    } else {
        std::cout << "Unable to open file";
    }

    std::cout << "========= Balance =========" << std::endl;
    std::cout << "Amount: Php. " << balance << ".00" << std::endl;
    std::cout << "Press any key to continue..." << std::endl;
    getch();
}

void Transaction::transaction_withdraw()
{ 
    int balance;
    std::ifstream infile("account.txt");
    if (infile.is_open()) {
        infile >> balance;
        infile.close();
    } else {
        std::cout << "Unable to open file";
    }

    int inputAmount;

    std::cout << "======== Withdraw ========" << std::endl;
    std::cout << "Input Amount: Php. ";
    std::cin >> inputAmount;

    if (inputAmount > balance) {
        std::cout << "Insufficient balance." << std::endl;
    } else {
        balance -= inputAmount;
        std::ofstream outfile("account.txt");
        if (outfile.is_open()) {
            outfile << balance;
            outfile.close();
        } else {
            std::cout << "Unable to open file";
        }
        std::cout << "Withdrawal successful. New balance: Php. " << balance << ".00" << std::endl;
    }

    std::cout << "Press any key to continue..." << std::endl;
    getch();
}

void Transaction::transaction_deposit()
{
    int balance;
    std::ifstream infile("account.txt");
    if (infile.is_open()) {
        infile >> balance;
        infile.close();
    } else {
        std::cout << "Unable to open file";
    }

    int inputAmount;

    std::cout << "=========== Deposit ============" << std::endl;
    std::cout << "Input Amount: Php. ";
    std::cin >> inputAmount;

    balance += inputAmount;
    std::ofstream outfile("account.txt");
    if (outfile.is_open()) {
        outfile << balance;
        outfile.close();
    } else {
        std::cout << "Unable to open file";
    }
    std::cout << "Deposit successful. New balance: Php. " << balance << ".00" << std::endl;

    std::cout << "Press any key to continue..." << std::endl;
    getch();
}

int main() {
    Transaction trans;
    trans.transaction_menu();
    return 0;
}