#include <iostream>
#include <string>
#include <iomanip>
#define WIN 3

using namespace std;

enum field {player1, player2, empty};

struct GameState {
    int rowCount;
    int columnCount;
    field ** table;
    field next;
};

void initialize(struct GameState & game) {
    game.table=NULL;
    game.table = new field*[game.rowCount];
    for(int r=0; r<game.rowCount; r++) {
        game.table[r] = new field[game.columnCount];
        for(int c=0; c<game.columnCount; c++) {
            game.table[r][c]=empty;
        }
    }
    game.next = player1;
}

void destruct(struct GameState & game) {
    for(int r=0; r<game.rowCount; r++) {
        delete [] game.table[r];
    }
    delete game.table;
}

string statetostring(field f) {
    switch(f) {
        case player1: return "X"; break;
        case player2: return "O"; break;
        case empty: return "."; break;
        default: return "-";
    }
}

void print(struct GameState & game) {
    cout<<game.rowCount<<" X "<<game.columnCount<< endl;
    cout << endl;
    cout << "  ";
    for(int c=0; c<game.columnCount; c++) {
        cout << char('A'+c);
    }
    cout << endl;
    for(int r=0; r<game.rowCount; r++) {       
        for(int c=0; c<game.columnCount; c++) {
            
            cout << statetostring(game.table[r][c]);
        }
        cout<<endl;
    }
}

bool winner(struct GameState & game) {
    bool win;
    for(int r=0; r<game.rowCount; r++) {
        for(int c=0; c<game.columnCount-WIN; c++) {
            if(game.table[r][c] != empty){
                win = true;
                for(int c2=c+1; c2<c+WIN; c2++)
                    if(game.table[r][c2]!=game.table[r][c]) win = false;
                if(win) return true;
            }
        }
    }

    for(int r=0; r<game.rowCount-WIN; r++) {
        for(int c=0; c<game.columnCount; c++) {
            if(game.table[r][c] != empty){
                win = true;
                for(int r2=r+1; r2<r+WIN; r2++)
                    if(game.table[r2][c]!=game.table[r][c]) win = false;
                if(win) return true;
            }
        }
    }

    for(int r=0; r<game.rowCount-WIN; r++) {
        for(int c=0; c<game.columnCount; c++) {
            if(game.table[r][c] != empty){
                win = true;
                for(int d=1; d<WIN; d++)
                    if(game.table[r+d][c+d]!=game.table[r][c]) win = false;
                if(win) return true;
            }
        }
    }

    for(int r=WIN-1; r<game.rowCount; r++) {
        for(int c=0; c<game.columnCount-WIN; c++) {
            if(game.table[r][c] != empty){
                win = true;
                for(int d=1; d<WIN; d++)
                    if(game.table[r-d][c+d]!=game.table[r][c]) win = false;
                if(win) return true;
            }
        }
    }
    return false; 
}

bool goodnextstep(struct GameState & game, char column, int row) {
    if(column < 'A' || column > 'A'+game.columnCount) return false;
    if(row < 1 || row > game.rowCount) return false;
    if(game.table[row-1][column-'A']!=empty) return false;
    return true;
}

void makenextstep(struct GameState & game, char column, int row) {
    game.table[row-1][column-'A']=game.next;
    game.next = (game.next==player1) ? player2 : player1;
}

int main() {

    struct GameState game;
    cin >> game.rowCount >> game.columnCount;

    initialize(game);
    print(game);
    char column;
    int row;
    while(!winner(game)) {
        do{
            cin >> column >> row;
        } while(! goodnextstep (game, column, row));
        makenextstep(game, column, row);
        print(game);
    }
    if(game.next==player1) {cout<<"Player2";}
    else {cout<<"Player1";}
    cout << " has won the game\n";

    destruct(game);

    return 0;
}