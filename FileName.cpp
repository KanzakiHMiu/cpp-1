#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <ctime>
#include <cstring>
#include <sstream>
#include <map>
using namespace std;

string getTime() {
    time_t t = time(0);
    struct tm* now = localtime(&t);
    stringstream timeStr;
    timeStr << now->tm_year + 1900 << "-";
    timeStr << now->tm_mon + 1 << "-";
    timeStr << now->tm_mday << " ";
    timeStr << now->tm_hour << ":";
    timeStr << now->tm_min << ":";
    timeStr << now->tm_sec;
    return timeStr.str();
}

class account {
public:
    account(string carid_, string name_, string id_)
        :carid(carid_), name(name_), id(id_) {
            account::accountCount[name]++;
        }
    void save(int);
    void takeOut(int);
    void showBalance() {
        cout << balance << endl;
    }

    static void showAllBalance() {
        for (const auto& pair : account::balances) {
            cout << "Total balance for " << pair.first << ": " << pair.second << endl;
        }
    }

    static void showAccountCount() {
        for (const auto& pair : account::accountCount) {
            cout << "Total accounts for " << pair.first << ": " << pair.second << endl;
        }
    }

    class Log {
    public:
        Log(){}
        void operator()(string time_, int amount_, string operations_, string owner_) {
            time = time_;
            amount = amount_;
            operations = operations_;
            owner = owner_;
        }
        void showLog() {
            cout << time << " " << amount << " " << operations << " " << owner << endl;
        }
    private:
        string time;
        int amount = 0;
        string operations;
        string owner;
    };
private:
    static map<string, int> balances;
    static map<string, int> accountCount;
    int balance = 0;
    string name;
    string carid;
    string id;
};

map<string, int> account::balances;
map<string, int> account::accountCount;
account::Log L[100];
int i = 0;

void account::save(int x) {
    balance += x;
    balances[name] += x;
    L[i++](getTime(), x, "Save", name);
}

void account::takeOut(int x) {
    if (balance < x) {
        return;
    }
    else {
        balance -= x;
        balances[name] -= x;
        L[i++](getTime(), x, "takeOut", name);
    }
}

int main()
{
    account a1("0001", "张三", "123");
    account a2("0002", "张三", "456");
    account b1("0011", "李四", "1111");
    account b2("0012", "李四", "2222");
    account a3("0004", "李四", "133");
    a1.save(1000);
    a2.save(300);
    a2.takeOut(1000);
    a2.takeOut(200);
    a1.save(1000);
    a1.takeOut(110);

    b1.save(1);

    a1.showBalance();
    a2.showBalance();

    for (int x = 0; x < i; x++) {
        L[x].showLog();
    }

    account::showAllBalance();
    account::showAccountCount();
    return 0;
}
