#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

class id
{
private:
    vector<string> user;
    vector<string> password;
    int count;
public:
    id()
    {
        count = 0;
    }
    int setid()
    {
        cout<<"Please input your username"<<endl;
        string u, p;
        cin>>u;
        if(search(u))
        {
            user.push_back(u);
            cout<<"Please input your password"<<endl;
            cin>>p;
            password.push_back(p);
            ofstream file;
            file.open("myaccount.txt", ios::app);
            file<<"User:"<<u<<"|"<<"Password:"<<p<<endl;
            file<<"--------------------------------------------------"<<endl;
            file.close();
            count++;
            return 1;
        }
        else{return 0;}
    }
    int login(string u, string p)
    {
        ifstream file;
        file.open("myaccount.txt");
        if(file.fail())
        {
            cout<<"File can not open"<<endl;
        }
        else
        {
            string temp;
            while(getline(file, temp))
            {
                string name, pw;
                name.clear();
                pw.clear();
                size_t pos;
                pos = temp.find('|', 5);
                name.assign(temp, 5, pos-5);
                pw.assign(temp, pos+10, temp.size()-pos-9);
                if(u==name && p==pw)
                {
                    file.close();
                    return 1;
                }
            }
            file.close();
            return 0;
        }
    }
    int search(string name)
    {
        ifstream file;
        file.open("myaccount.txt");
        string temp;
        while(getline(file, temp))
        {
            string u;
            u.clear();
            size_t pos;
            pos = temp.find('|', 5);
            u.assign(temp, 5, pos-5);
            if(name==u)
            {
                file.close();
                return 0;
            }
        }
        file.close();
        return 1;
    }
    void forgetpw(string name)
    {
        ifstream file;
        file.open("myaccount.txt");
        if(file.fail())
        {
            cout<<"File can not open"<<endl;
        }
        else
        {
            string temp;
            while(getline(file, temp))
            {
                string u;
                u.clear();
                size_t pos;
                pos = temp.find('|', 5);
                u.assign(temp, 5, pos-5);
                if(name==u)
                {
                    string pw;
                    pw.clear();
                    pw.assign(temp, pos+10, temp.size()-pos-9);
                    cout<<"Your password is:"<<pw<<endl;
                    file.close();
                }
            }
        }
    }
    void display()
    {
        ifstream file;
        file.open("myaccount.txt");
        if(file.fail())
        {
            cout<<"File can not open"<<endl;
        }
        else
        {
            string account;
            while(getline(file, account))
            {
                cout<<account<<endl;
            }
        }
    }
};

int main()
{
    id inf;
    cout<<"Welcone to register ang login system"<<endl;
    cout<<"[Username and password can only be inputed in English or numbers.]"<<endl;
    while(1)
    {
        cout<<"---------------------------------"<<endl;
        cout<<"1:Register"<<endl;
        cout<<"2:Login"<<endl;
        cout<<"3:Diplay all of account"<<endl;
        cout<<"4:Forget password"<<endl;
        cout<<"5:Exit"<<endl;
        cout<<"---------------------------------"<<endl;
        int i, j, cmd, c, temp=0;
        string username, passwords;
        cin>>cmd;
        if(cmd==1)
        {
            while(1)
            {
                int state = inf.setid();
                if(state==1)
                {
                    cout<<"Set up successfully!"<<endl;
                    temp++;
                    break;
                }
                else
                {
                    cout<<"The user is already exit, plese input again"<<endl;
                }
            }
        }
        if(cmd==2)
        {
            while(1)
            {
                cout<<"Please input your username"<<endl;
                cin>>username;
                cout<<"Please input your password"<<endl;
                cin>>passwords;
                int state = inf.login(username, passwords);
                if(state==1)
                {
                    cout<<"Login sucessfully!"<<endl;
                    break;
                }
                else
                {
                    cout<<"The user is not exist or the password is wrong."<<endl;
                    cout<<"Please input again"<<endl;
                }
            }
        }
        if(cmd==3)
        {
            inf.display();
        }
        if(cmd==4)
        {
            cout<<"Please input your username"<<endl;
            cin>>username;
            inf.forgetpw(username);
        }
        if(cmd==5)
        {
            break;
        }
    }
    return 0;
}
