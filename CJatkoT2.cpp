#include <iostream>
#include <thread>
#include <mutex>

class BankAccount {
public:
    BankAccount(int balance) : balance(balance) {}

    void deposit(int amount) {
        balance += amount;
    }

    void withdraw(int amount) {
        if (balance >= amount) {
            balance -= amount;
        }
        else {
            std::cerr << "Insufficient funds!" << std::endl;
        }
    }

    int getBalance() const {
        return balance;
    }

private:
    int balance;
};

std::mutex mtx;

void depositMoney(BankAccount& account, int amount, int times) {
    for (int i = 0; i < times; ++i) {
        std::lock_guard<std::mutex> lock(mtx);
        account.deposit(amount);
    }
}

void withdrawMoney(BankAccount& account, int amount, int times) {
    for (int i = 0; i < times; ++i) {
        std::lock_guard<std::mutex> lock(mtx);
        account.withdraw(amount);
    }
}

int main() {
    BankAccount account(1000);

    const int numTransactions = 10000;
    const int amount = 1;

    std::thread t1(depositMoney, std::ref(account), amount, numTransactions);
    std::thread t2(withdrawMoney, std::ref(account), amount, numTransactions);

    t1.join();
    t2.join();

    int expectedBalance = 1000; // Initial balance
    std::cout << "Final balance: " << account.getBalance() << std::endl;

    if (account.getBalance() == expectedBalance) {
        std::cout << "Balance is correct." << std::endl;
    }
    else {
        std::cout << "Balance is incorrect." << std::endl;
    }

    return 0;
}
