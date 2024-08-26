#include <iostream>
#include <future>
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

    int initialBalance = 50000;
    int depositAmount = 100;
    int withdrawAmount = 50;
    int numTransactions = 10000;

    BankAccount account(initialBalance);

    auto depositFuture = std::async(std::launch::async, depositMoney, std::ref(account), depositAmount, numTransactions);
    auto withdrawFuture = std::async(std::launch::async, withdrawMoney, std::ref(account), withdrawAmount, numTransactions);

    depositFuture.get();
    withdrawFuture.get();

    int expectedBalance = initialBalance + (depositAmount * numTransactions) - (withdrawAmount * numTransactions);

    std::cout << "Final balance: " << account.getBalance() << std::endl;

    if (account.getBalance() == expectedBalance) {
        std::cout << "Balance is correct." << std::endl;
    }
    else {
        std::cout << "Balance is incorrect." << std::endl;
    }

    return 0;
}
