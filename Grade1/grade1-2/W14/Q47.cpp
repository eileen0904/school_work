//UVa924

#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() 
{
    int E = 0, T = 0, i, j, n = 0, a = 0;
    while (cin >> E) 
    {
        vector<int> fri[400];
        for (i = 0; i < E; i++) 
        {
            fri[i].clear();
            cin >> n;
            for (j = 0; j < n; j++) 
            {
                cin >> a;
                fri[i].push_back(a);
            }
        }
        cin >> T;
        while (T--) 
        {
            cin >> a;
            int day[400], people[400], visited[400];  //第幾天所擴散的人數, 第幾人開始執行擴散的日期(第幾天)
            memset(day, 0, sizeof(day));
            memset(people, 0, sizeof(people));
            memset(visited, 0, sizeof(visited));
            queue<int> q;
            q.push(a);
            visited[a] = 1;
            while (!q.empty()) 
            {
                int cur = q.front();
                q.pop();
                for (vector<int>::iterator i = fri[cur].begin(); i != fri[cur].end(); i++) 
                {
                    if (visited[*i] == 0) 
                    {
                        visited[*i] = 1;
                        q.push(*i);
                        people[*i] = people[cur] + 1;
                        day[people[*i]]++;
                    }
                }
            }
            int date = 0, person = 0;
            for (i = 1; i <= E; i++) 
            {
                if (day[i] > person) 
                {
                    person = day[i];
                    date = i;
                }
            }
            if (person > 0) 
            {
                cout << person << " " << date << endl;
            } 
            else 
            {
                cout << "0" << endl;
            }
        }
    }
    return 0;
}
