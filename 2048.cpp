#include<iostream>
#include<ctime>
#include<iomanip>
#include<cstdlib>
using namespace std;

int board[4][4];
int directionline[] = {1, 0, -1, 0};
int directioncolumn[] = {0, 1, 0, -1};

pair<int, int> generateunoccupiedposition() {
    int occupied = 1, line, column;
    while (occupied) {
        line = rand() % 4;
        column = rand() % 4;
        if (board[line][column] == 0) {
            occupied = 0;
        }
    }
    return make_pair(line, column);
}

void addpiece() {
    pair<int, int> pos = generateunoccupiedposition();
    board[pos.first][pos.second] = 2;
}

void newgame() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            board[i][j] = 0;
        }
    }
    addpiece();
}

void printui() {
    system("cls");
    cout<<"         2048 GAME"<<endl;
    cout<<" ADD NUMBERS TO GET SUM OF 2048 ";
    cout<<endl;
    cout<<endl;
    cout<<endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (board[i][j] == 0) {
                cout << setw(4) << ".";
            } else {
                cout << setw(4) << board[i][j];
            }
        }
        cout << endl;
    }
    cout << " n: new game , u: up , d: down , r: right , l: left  , q: quit " << endl;
}

bool candomove(int line, int column, int nextline, int nextcolumn) {
    if (nextline < 0 || nextcolumn < 0 || nextline >= 4 || nextcolumn >= 4
        || (board[line][column] != board[nextline][nextcolumn] && board[nextline][nextcolumn] != 0)) {
        return false;
    }
    return true;
}

void applymove(int direction) {
    int startline = 0, startcolumn = 0, linestep = 1, columnstep = 1;
    if (direction == 0) {
        startline = 3;
        linestep = -1;
    }
    if (direction == 1) {
        startcolumn = 3;
        columnstep = -1;
    }
    int movepossible, canaddpiece = 0;
    do {
        movepossible = 0;
        for (int i = startline; i >= 0 && i < 4; i += linestep) {
            for (int j = startcolumn; j >= 0 && j < 4; j += columnstep) {
                int nexti = i + directionline[direction], nextj = j + directioncolumn[direction];
                if (board[i][j] != 0 && candomove(i, j, nexti, nextj)) {
                    board[nexti][nextj] += board[i][j];
                    board[i][j] = 0;
                    movepossible = canaddpiece = 1;
                }
            }
        }
    } while (movepossible);

    if (canaddpiece) {
        addpiece();
    }
}

int main() {
    srand(time(0));
    char commanddir[128];
    commanddir['d'] = 0;
    commanddir['r'] = 1;
    commanddir['u'] = 2;
    commanddir['l'] = 3;
    newgame();
    while (true) {
        printui();
        char command;
        cin >> command;
        if (command == 'n') {
            newgame();
        } else if (command == 'q') {
            break;
        } else {
            int currentdirection = commanddir[command];
            applymove(currentdirection);
        }
    }
    return 0;
}
