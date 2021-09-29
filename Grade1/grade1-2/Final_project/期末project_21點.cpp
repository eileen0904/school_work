#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int card()
{
    srand(time(NULL));
    int min=1, max=10;
    int c = rand() % (max-min+1) + min;
    return c;
}

int main()
{
    cout<<"Black Jack"<<endl;
    cout<<"1:Play"<<endl;
    cout<<"2:Exit"<<endl;
    cout<<"----------------"<<endl;
    int a;
    while(cin>>a)
    {
        if(a==2)
        {
            break;
        }
        int com = card();
        int player = card();
        cout<<"Your points:"<<player<<endl;
        cout<<"Do you need to add a card?"<<endl;
        cout<<"y:Yes"<<endl;
        cout<<"n:No"<<endl;
        while(com<21)
        {
            if(com<=15)
            {
                com = com + card();
            }
            else
            {
                break;
            }
        }
        char b;
        while(cin>>b)
        {
            if(b=='n')
            {
                cout<<"Your points:"<<player<<endl;
                break;
            }
            if(b=='y')
            {
                player = player + card();
            }
            if(player>=21)
            {
                cout<<"Your points:"<<player<<endl;
                break;
            }
            cout<<"Your points:"<<player<<endl;
            cout<<"Do you need to add a card?"<<endl;
            cout<<"y:Yes"<<endl;
            cout<<"n:No"<<endl;
        }
        cout<<"Computer's points:"<<com<<endl;
        if((player>com && player<=21) || (com>21 && player<21))
        {
            cout<<"You win!"<<endl;
        }
        else if((player<com && com<=21) || (player>21 && com<21))
        {
            cout<<"You lose QQ"<<endl;
        }
        else if(player==com || (palyer>21 && com>21)) 
        {
            cout<<"Tie"<<endl;
        }
        cout<<"1:Play"<<endl;
        cout<<"2:Exit"<<endl;
    }
    return 0;
}
