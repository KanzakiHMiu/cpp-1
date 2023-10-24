#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <ctime>
#include <cstring>
#include <sstream>
#include <map>
using namespace std;

// 获取当前时间的字符串表示
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

// 账户类的定义
class account {
public:
    account(string carid_, string name_, string id_)
        :carid(carid_), name(name_), id(id_) {
            account::accountCount[name]++;
        }
     // 存款函数
    void save(int);

    // 取款函数
    void takeOut(int);

    // 显示账户余额
    void showBalance() {
        cout << balance << endl;
    }

    // 静态函数，显示所有账户的总余额
    static void showAllBalance() {
        for (const auto& pair : account::balances) {
            cout << "Total balance for " << pair.first << ": " << pair.second << endl;
        }
    }

    // 静态函数，显示账户的总数
    static void showAccountCount() {
        for (const auto& pair : account::accountCount) {
            cout << "Total accounts for " << pair.first << ": " << pair.second << endl;
        }
    }

    // 嵌套类：日志类
    class Log {
    public:
        // 日志类的默认构造函数
        Log(){}

        // 重载运算符函数，将值赋给日志类的成员变量
        void operator()(string time_, int amount_, string operations_, string owner_) {
            time = time_;
            amount = amount_;
            operations = operations_;
            owner = owner_;
        }

        // 显示日志信息
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

// 存款函数
void account::save(int x) {
    balance += x;
    balances[name] += x;
    L[i++](getTime(), x, "Save", name);
}

// 取款函数
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

// 主函数
int main()
{
    // 创建账户实例
    account a1("0001", "张三", "123");
    account a2("0002", "张三", "456");
    account b1("0011", "李四", "1111");
    account b2("0012", "李四", "2222");
    account a3("0004", "李四", "133");

    // 添加用户操作
    a1.save(1000);
    a2.save(300);
    a2.takeOut(1000);
    a2.takeOut(200);
    a1.save(1000);
    a1.takeOut(110);
    b1.save(1);

    // 显示账户余额
    a1.showBalance();
    a2.showBalance();

    // 显示日志
    for (int x = 0; x < i; x++) {
        L[x].showLog();
    }

    // 显示每个人名下所有账户的总余额
    account::showAllBalance();

    // 显示每个人账户的总数
    account::showAccountCount();
    return 0;
}
