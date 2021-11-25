#include <iostream>
using namespace std;

class Type
{
public:
  Type(){}
  void setNumType(string s, int n){
    type = s;
    number = n;
  }
  void setType(string s){
    type = s;
  }
  void setVisit(int n){
    visit = n;
  }
  string getType() const{
    return type;
  }
  int getNum() const{
    return number;
  }
  int getVisit() const{
    return visit;
  }
private:
  string type;
  int number, visit=0;
};

class Nurikabe
{
public:
  /*
  n is the size of the Nurikabe, n >= 5, n <= 20
  game is the result from some player
  here is one example
  n: 5
  game = {  {'W', 'W', 'W', '1', 'W'},
            {'W', '.', 'W', 'W', 'W'},
            {'W', '2', 'W', '.', '3'},
            {'3', 'W', 'W', '.', 'W'},
            {'.', '.', 'W', 'W', 'W'} };
  W represent wall
  */
  Nurikabe(char game[20][20], int n)
  {
    for(int i=0;i<n;i++){
      for(int j=0;j<n;j++){
        if(game[i][j]=='W' || game[i][j]=='w'){
          result[i][j].setType("wall");
          count++;
        }
        if(game[i][j]=='.'){
          result[i][j].setType("dot");
        }
        if(game[i][j]>=49 && game[i][j]<=57){
          result[i][j].setNumType("num", game[i][j]-48);
        }
      }
    }
    if(checkWall(n) && checkDot(n)){
      accept = 1;
    }
  }

  int checkWall(int n){
    int x = find_start(n, 1);
    int y = find_start(n, 2);
    move_wall(x, y, n);
    int temp = 0;
    for(int i=0;i<n;i++){
      for(int j=0;j<n;j++){
        if(result[i][j].getVisit()==1){
          temp++;
        }
      }
    }
    if(temp==count){
      continuous = true;
    }
    if(continuous && check2x2(n)){
      return 1;
    }
    else{
      return 0;
    }
  }

  int find_start(int n, int get){
    for(int i=0;i<n;i++){
      for(int j=0;j<n;j++){
        if(result[i][j].getType()=="wall"){
          if(get==1){
            return i;
          }
          else{
            return j;
          }
        }
      }
    }
  }

  void move_wall(int x, int y, int n){
    if(result[x][y].getType()!="wall"){return;}
    result[x][y].setVisit(1);
    int dirx[4] = {0, 1, 0, -1}; //right,down,left,up
    int diry[4] = {1, 0, -1, 0};
    for(int i=0;i<4;i++){
      int nx = x + dirx[i];
      int ny = y + diry[i];
      if(nx<=n-1 && ny<=n-1 && nx>=0 && ny>=0 && result[nx][ny].getVisit()==0){
        move_wall(nx, ny, n);
      }
    }
    return;
  }

  int check2x2(int n){
    int temp = 0;
    int dirx[3] = {0, 1, 1}; //right,rightdown,down
    int diry[3] = {1, 1, 0};
    for(int i=0;i<n;i++){
      for(int j=0;j<n;j++){
        if(result[i][j].getType()=="wall"){
            temp++;
          for(int k=0;k<3;k++){
            if(i+dirx[k]<n && j+diry[k]<n && result[i+dirx[k]][j+diry[k]].getType()=="wall"){
                temp++;
            }
          }
        }
        if(temp==4){
            return 0;
        }
        temp = 0;
      }
    }
    return 1;
  }

  int checkDot(int n){
    for(int i=0;i<n;i++){
      for(int j=0;j<n;j++){
        if(result[i][j].getType()=="num"){
          move_dot(i, j, n, 0);
          init_dot(n);
          if(dot_count!=result[i][j].getNum()){
            return 0;
          }
        }
        dot_count = 0;
      }
    }
    return 1;
  }

  void move_dot(int x, int y, int n, int not_first){
    if(not_first){
      if(result[x][y].getType()!="dot"){return;}
    }
    result[x][y].setVisit(2);
    dot_count++;
    int dirx[4] = {0, 1, 0, -1}; //right,down,left,up
    int diry[4] = {1, 0, -1, 0};
    for(int i=0;i<4;i++){
      int nx = x + dirx[i];
      int ny = y + diry[i];
      if(nx<n && ny<n && nx>=0 && ny>=0 && result[nx][ny].getVisit()==0){
        move_dot(nx, ny, n, 1);
      }
    }
    return;
  }

  void init_dot(int n){
    for(int i=0;i<n;i++){
      for(int j=0;j<n;j++){
        if(result[i][j].getVisit()==2){
          result[i][j].setVisit(0);
        }
      }
    }
  }
  /*
  return 1 if result fit the rule.
  return 0 if result not fit the rule.
  */
  int isCorrect()
  {
    return accept;
  }
private:
  Type result[20][20];
  int count=0, accept=0, dot_count;
  bool continuous = false;
};

int main() {
  int n, j, l, k;
  char game[20][20] = { {'W', 'W', 'W', '1', 'W'},
                        {'W', '.', 'W', 'W', 'W'},
                        {'W', '2', 'W', '.', '3'},
                        {'3', 'W', 'W', '.', 'W'},
                        {'.', '.', 'W', 'W', 'W'} };
  cin>>n;
  for(j = 0;j < n;j ++)
    for(k = 0;k < n;k ++)
      cin>>game[j][k];
  Nurikabe *a = new Nurikabe(game, n);
  cout<<a->isCorrect();
  return 0;
}
