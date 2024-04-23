#include <iostream>
#include <ctime>
#include <fstream>
#include <vector>
#include "test.h"

using namespace std;

void Account::Register()
{
    Id = "";
    srand(time(0));
    for (int i = 0; i <= 9; i++)
    {
        int x = rand() % 2;
        char y = (1 - x) * (rand() % 10 + 48) + x * (rand() % 26 + 65);
        Id += y;
    }
    cout << Id << endl;
    cout << "Set your 6-digit passwords: ";
    cin >> Pin;
    if (Pin.size() != 6)
    {
        cout << "Failed to register !" << endl;
        Id = "";
        return;
    }
    Balance = 0;
    ofstream Create("account_list/" + Id + ".txt");
    Create << Pin << " " << Balance << endl;
    Create.close();
    Id = "";
}
void Account::login()
{
    string data;
    cout << "Enter username: ";
    cin >> Id;
    cout << "Enter your passwords: ";
    cin >> data;
    ifstream Check;
    Check.open("account_list/" + Id + ".txt");
    if (Check.is_open())
    {
        Check >> Pin;
        Check >> Balance;
        if (data != Pin)
        {
            Check.close();
            cout << "Wrong username or passwords !" << endl;
            Id = "";
            return;
        }
        Check.close();
        LoginId = Id;
        loginMenu();
    }
    else
    {
        Check.close();
        cout << "Wrong username or passwords !" << endl;
        Id = "";
        return;
    }
}
void Account::info()
{
    cout << "Account ID: " << Id << endl;
    cout << "Account balance: " << Balance << endl;
    cout << "List of friendly account IDs: " << endl;
    for (int i = 0; i < List.size(); i++)
        cout << List[i] << endl;
}
void Account::withdraw()
{
    if (Balance == 0)
    return;
    cout << "1. 10" << endl;
    cout << "2. 20" << endl;
    cout << "3. 50" << endl;
    cout << "4. 100" << endl;
    cout << "5. other" << endl;
    float x;
    cout << "Enter your choice: ";
    cin >> x;
    if (x == 1)
    {
        edit(10);
    }
    else if (x == 2)
    {
        edit(20);
    }
    else if (x == 3)
    {
        edit(50);
    }
    else if (x == 4)
    {
        edit(100);
    }
    else if (x == 5)
    {
        float y;
        cout << "Amount: ";
        cin >> y;
        if (!(y > 0))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            return;
        }
        edit(y);
    }
    else
    {
        cin.clear();
        cin.ignore(1000, '\n');
    }
}
void Account::deposit()
{
    float x;
    cout << "Amount: ";
    cin >> x;
    if (!(x > 0))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }
    edit(-x);
}
void Account::transfer()
{
    cout << "1. Choose an account from friendly list" << endl;
    cout << "2. Input an account" << endl;
    cout << "3. Return to menu" << endl;
    float x;
    cout << "Enter your choice: ";
    cin >> x;
    if (x == 1)
    {
        float i, transVal1;
        if (List.size() == 0)
        {
            cout << "Empty list !" << endl;
            return;
        }
        for (i = 0; i < List.size(); i++)
            cout << i + 1 << ". " << List[i] << endl;
        cout << "Enter your choice: ";
        cin >> i;
        if (!(i > 0 && i <= List.size()))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            return;
        }
        transVal1 = transferProcess();
        Id = List[i - 1];
        setData();
        edit(-transVal1);
        Id = LoginId;
        setData();
    }
    else if (x == 2)
    {
        string name, answer;
        cout << "Enter ID: ";
        cin >> name;
        ifstream CheckList("account_list/" + name + ".txt");
        if (!CheckList.is_open())
        {
            CheckList.close();
            return;
        }
        CheckList.close();
        cout << "Do you want to save this account in friendly list ? (Y/N)" << endl;
        cin >> answer;
        if (answer == "Y" || answer == "y")
        {
            for (int i = 0; i < List.size(); i++)
            {
                if (name == List[i])
                    return;
            }
            List.push_back(name);
            override();
        }
        else if (answer == "N" || answer == "n")
        {
        }
        else
            cout << "Failed to save !" << endl;
        float transVal2;
        transVal2 = transferProcess();
        Id = name;
        setData();
        edit(-transVal2);
        Id = LoginId;
        setData();
        cout << "Executed successfully !" << endl;
        cout << "Remaining balance: " << Balance << endl;
        return;
    }
    else if (x == 3)
        return;
    else
    {
        cin.clear();
        cin.ignore(1000, '\n');
    }
}
void Account::loginMenu()
{
    while (true)
    {
        List.clear();
        Id = LoginId;
        setData();
        float x;
        cout << "1. Account information" << endl;
        cout << "2. Withdraw money" << endl;
        cout << "3. Deposit money" << endl;
        cout << "4. Transfer money" << endl;
        cout << "5. Logout" << endl;
        cout << "Enter your choice: ";
        cin >> x;
        if (x == 1)
        {
            info();
        }
        else if (x == 2)
        {
            withdraw();
        }
        else if (x == 3)
        {
            deposit();
        }
        else if (x == 4)
        {
            transfer();
        }
        else if (x == 5)
            break;
        else
        {
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }
}
void Account::edit(float amount)
{
    if (amount == 0 || amount > Balance)
    return;
    Balance -= amount; // giảm giá trị của balance đi để bằng với Amount 
    cout << "Executed successfully !" << endl;
    cout << "Remaining balance: " << Balance << endl;
    override();                
}
void Account::override()
{
    ofstream Over("account_list/" + Id + ".txt");
    Over << Pin << " " << Balance << endl;
    for (int i = 0; i < List.size(); i++)
    Over << List[i] << endl;
    Over.close();
}
void Account::setData()
{
    string x;
    ifstream Insert("account_list/" + Id + ".txt");
    Insert >> Pin;
    Insert >> Balance;
    while (Insert >> x)
    List.push_back(x);
    Insert.close();
}
float Account::transferProcess()
{
    float transMoney;
    cout << "Amount to transfer: ";
    cin >> transMoney;
    if (!(transMoney > 0))
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Transference failed !" << endl;
        return 0;
    }
    edit(transMoney);
    List.clear();
    return transMoney;
}