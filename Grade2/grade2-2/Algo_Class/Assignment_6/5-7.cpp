#include <bits/stdc++.h>
using namespace std;
const int n = 4; //The size of the chess board n*n
typedef pair<int, int> P;

bool checkValid(char board[n][n], int curRow, int curCol){
    //check cur row
    for(int i=0; i < curCol; i++){
        if(board[curRow][i] == 'Q'){
            return false;
        }
    }
    //check left up
    for(int i = curRow, j = curCol; i >= 0 && j >= 0; i--, j--){
        if(board[i][j] == 'Q'){
            return false;
        }
    }
    //check left down
    for(int i = curRow, j = curCol; i < n && j >= 0; i++, j--){
        if(board[i][j] == 'Q'){
            return false;
        }
    }
    return true;
}

bool solve(char board[n][n], int col){
    //terminal conditions
    if(col >= n) return true;

    //Go through all the elements in current col
    for(int i=0; i < n; i++){
        if(checkValid(board, i, col)){
            board[i][col] = 'Q';
            if(solve(board, col + 1)){
                return true;
            }
        }
        board[i][col] = '.';
    }
    return false;
}

void promising(char board[n][n], vector<P> area[n], int row, int col){
    for(int i=0; i < n; i++){ //row
        if(board[row][i] == '.'){
            board[row][i] = 'x';
            area[row].push_back({row, i});
        }
    }
    for(int i=0; i < n; i++){ //col
        if(board[i][col] == '.'){
            board[i][col] = 'x';
            area[row].push_back({i, col});
        }
    }
    for(int i=1; row - i >=0 && col - i >= 0 && board[row - i][col - i] == '.'; i++){ //left up
        board[row - i][col - i] = 'x';
        area[row].push_back({row - i, col - i});
    }
    for(int i=1; row + i < n && col - i >= 0 && board[row + i][col - i] == '.'; i++){ //left down
        board[row + i][col - i] = 'x';
        area[row].push_back({row + i, col - i});
    }
    for(int i=1; row + i < n && col + i < n && board[row + i][col + i] == '.'; i++){ //right down
        board[row + i][col + i] = 'x';
        area[row].push_back({row + i, col + i});
    }
    for(int i=1; row - i >= 0 && col + i < n && board[row - i][col + i] == '.'; i++){ //right up
        board[row - i][col + i] = 'x';
        area[row].push_back({row - i, col + i});
    }
}

int main(){
    char board[n][n];
    vector<P> area[n];
    area->clear();
    for(int i=0; i < n; i++){
        for(int j=0; j < n; j++){
            board[i][j] = '.';
        }
    }
    cout << "The size of the chess board is : " << n << endl;
    if(solve(board, 0)){
        for(int i=0; i < n; i++){
            for(int j=0; j < n; j++){
                if(board[i][j] == 'Q'){
                    promising(board, area, i, j);
                }
            }
            for(int r=0; r < n; r++){
                for(int c=0; c < n; c++){
                    cout << board[r][c] << " ";
                }
                cout << endl;
            }
            for(int k=0; k < 2 * n; k++){
                cout << "-";
            }
            cout << endl;
        }
        vector<P>::iterator it;
        for(int i=0; i < n; i++){
            cout << "Queen " << i + 1 << " controll: ";
            for(it = area[i].begin(); it != area[i].end(); it++){
                cout << "(" << it->first << ", " << it->second << ")" << " ";
            }
            cout << endl;
        }
    }
    else{
        cout << "No solution." << endl;
    }

    return 0;
}