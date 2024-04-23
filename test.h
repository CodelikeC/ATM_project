#include <iostream>
#include <vector>
#pragma once 
using namespace std;

class Account
{
public:
    void Register();
    void login();

private:
    string Id;
    string Pin;
    int Balance;
    string LoginId;

    void info(); // thông tin tài khoản // 
    void withdraw(); // rút tiền //
    void deposit(); // nạp tiền // 
    void transfer(); // chuyển tiền // 

    void loginMenu(); // menu phần login 
    void edit(float x); // phần này là sau khi rút tiền. Mỗi lần rút tiền thì edit() có nhiệm vụ ghi đè lên balance cũ
    void override(); // ghi đè 1 file mới// 
    void setData(); // cài đặt dữ liệu : tạo thêm 1 file mới mà nó sẽ in ra balance và pin sau khi thay đổi // 

    float transferProcess(); // quá trình chuyển tiền : số tiền mình muốn chuyển // 
    vector<string> List; // một cái array tên list chứa kiểu kí tự string // 
};