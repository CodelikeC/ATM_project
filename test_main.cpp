#include <iostream>
#include "test.cpp"
using namespace std;

int main()
{
    Account acc;
    while (true)
    {
        int x;
        cout << "1. Login" << endl;
        cout << "2. Create new account" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> x;
        if (x == 1)
        {
            acc.login();
        }
        else if (x == 2)
        {
            acc.Register();
        }
        else if (x == 3)
            break;
        else
        {
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }
    return 0;
}