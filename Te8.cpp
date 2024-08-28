#include <iostream>
#include <fstream>
#include <memory>
#include <ctime>

template <typename T>
class Log_Ptr {
public:
    // Konstruktori
    explicit Log_Ptr(T* ptr) : ptr_(ptr) {
        log("Ownership transferred", ptr_);
    }

    // Destruktori
    ~Log_Ptr() {
        log("Object destroyed", ptr_);
        delete ptr_;
    }

    // Kopiointikielto
    Log_Ptr(const Log_Ptr&) = delete;
    Log_Ptr& operator=(const Log_Ptr&) = delete;

    // Liikkuvuuden hallinta
    Log_Ptr(Log_Ptr&& other) noexcept : ptr_(other.ptr_) {
        other.ptr_ = nullptr;
        log("Ownership transferred (move)", ptr_);
    }

    Log_Ptr& operator=(Log_Ptr&& other) noexcept {
        if (this != &other) {
            delete ptr_;
            ptr_ = other.ptr_;
            other.ptr_ = nullptr;
            log("Ownership transferred (move)", ptr_);
        }
        return *this;
    }

    // Osoittimen operaatio
    T& operator*() const {
        return *ptr_;
    }

    T* operator->() const {
        return ptr_;
    }

private:
    T* ptr_;

    void log(const char* message, T* ptr) const {
        std::ofstream log_file("log_ptr.txt", std::ios_base::app);
        std::time_t t = std::time(nullptr);
        char timestamp[100];
        struct tm time_info;
        localtime_s(&time_info, &t);  // Using the safer localtime_s
        std::strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", &time_info);
        log_file << "[" << timestamp << "] " << message << " (" << ptr << ")\n";
        log_file.close();
    }
};

// Testiohjelma
class TestClass {
public:
    TestClass(int value) : value_(value) {
        std::cout << "TestClass constructor (" << value_ << ")\n";
    }
    ~TestClass() {
        std::cout << "TestClass destructor (" << value_ << ")\n";
    }
    int getValue() const { return value_; }
private:
    int value_;
};

int main() {
    {
        Log_Ptr<TestClass> logPtr1(new TestClass(42));
        std::cout << "Value: " << logPtr1->getValue() << std::endl;

        Log_Ptr<TestClass> logPtr2(new TestClass(100));
        logPtr2 = std::move(logPtr1);
    } // logPtr2:n ja logPtr1:n destruktorit kutsutaan automaattisesti tässä

    return 0;
}
