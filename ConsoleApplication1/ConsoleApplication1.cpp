#include <iostream>
#include <fstream>
#include <queue>


using std::cout;
using std::endl;
using std::cin;
using std::ifstream;

const int N = 10;
void printMap(char map[N][N]) {

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
}
int confirm_ship(char map[N][N], bool(&checked_ps)[N][N], int x, int y) {
    struct cords
    {
        int x;
        int y;
    };
    enum Directions {
        undef,
        vertical,
        horizontal
    };
    std::queue<cords> go_ls;
    go_ls.push({ x, y });

    int res = 0;
    Directions direction = Directions::undef;
    while (!go_ls.empty()) {
        cords cur_pt = go_ls.front();
        go_ls.pop();
        checked_ps[cur_pt.x][cur_pt.y] = true;
        res++;

        if (cur_pt.x < N - 1)
            if (!checked_ps[cur_pt.x + 1][cur_pt.y]
                && map[cur_pt.x + 1][cur_pt.y] == '*'
                && (direction == Directions::undef || direction == Directions::horizontal))
            {
                go_ls.push({ cur_pt.x + 1, cur_pt.y });
                direction = Directions::horizontal;
            }

        if (cur_pt.y < N - 1)
            if (!checked_ps[cur_pt.x][cur_pt.y + 1]
                && map[cur_pt.x][cur_pt.y + 1] == '*'
                && (direction == Directions::undef || direction == Directions::vertical))
            {
                go_ls.push({ cur_pt.x, cur_pt.y + 1 });
                direction = Directions::vertical;
            }
    }
    return res;
}
void checkShips(char map[N][N]) {
    int isCorrect = true;
    int one4deckship = 0;
    int one3deckship = 0;
    int one2deckship = 0;
    int one1deckship = 0;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {                        
            if (map[i][j] == '*') {// на диагоналях
                if (map[i + 1][j - 1] == '*') {//правая верхняя диагональ
                    cout << "Error!!! upper right diagonal" << endl;
                    isCorrect = false;
                    return;
                }
                else if (map[i + 1][j+1] == '*') {//правая нижняя диагональ
                    cout << "Error!!! lower right diagonal" << endl;
                    isCorrect = false;
                    return;
                }
                else if(map[i - 1][j + 1] == '*'){//левая нижняя диагональ
                    cout << "Error!!! lower left diagonal" << endl;
                    isCorrect = false;
                    return;
                }
                else if (map[i - 1][j - 1] == '*') {//левая верхняя диагональ
                    cout << "Error!!! upper left diagonal" << endl;
                    isCorrect = false;
                    return;
                }
                // сверху, снизу, слева, справа

                if (map[i + 1][j] == '*' &&
                    map[i + 2][j] == '*' &&
                    map[i + 3][j] == '*' &&
                    map[i + 4][j] == '*') {
                    cout << "Eror!!! lower, the ship is too long" << endl;   
                    isCorrect = false;
                    return;
                }
                else if (map[i][j - 1] == '*' &&
                    map[i][j - 2] == '*' &&
                    map[i][j - 3] == '*' &&
                    map[i][j - 4] == '*') {
                    cout << "Eror!!! left, the ship is too long" << endl;
                    isCorrect = false;
                    return;
                }
                else if (map[i - 1][j] == '*' &&
                    map[i - 2][j] == '*'&&
                    map[i - 3][j] == '*'&&
                    map[i - 4][j] == '*') {
                    cout << "Eror!!! upper, the ship is too long" << endl;
                    isCorrect = false;
                    return;
                }
                else if (map[i][j + 1] == '*' &&
                    map[i][j + 2] == '*' &&
                    map[i][j + 3] == '*' &&
                    map[i][j + 4] == '*') {
                    cout << "Eror!!! right, the ship is too long" << endl;
                    isCorrect = false;
                    return;
                }
            }
        }
    } 
    bool checked_ps[N][N];
    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            checked_ps[i][j] = false;
        }
    }

    for (size_t i = 0; i < N; i++)
    {
        for (size_t j = 0; j < N; j++)
        {
            if (map[i][j] == '*' && checked_ps[i][j] == false) {
                int res = confirm_ship(map, checked_ps, i, j);
                if (res == 1) one1deckship++;
                if (res == 2) one2deckship++;
                if (res == 3) one3deckship++;
                if (res == 4) one4deckship++;
            }
        }
    }//1 четырехпалубный корабль, 2 трехпалубных, 3 двухпалубных, 4 однопалубных

    if (one4deckship != 1 || one3deckship != 2 || one2deckship != 3 || one1deckship != 4)
    {
        cout << "Error!!! you need 1 - 4 deck ship, 2 - 3 deck ship, 3 - 2 deck ship, 4 - 1 deck ship" << endl;
        cout << "4 deck ship: " << one4deckship << endl;
        cout << "3 deck ship: " << one3deckship << endl;
        cout << "2 deck ship: " << one2deckship << endl;
        cout << "1 deck ship: " << one1deckship << endl;
        isCorrect = false;
    }
    if (isCorrect) {
        cout << "Map is correct!" << endl;
    }
}

void gotOrNotGot(char map[N][N]) {
    int x, y;
    
    while (true) {
        cout << "enter the coordinates of the target : " << endl;
        cin >> x;
        cin >> y;
        if (x > 10 || y > 10) {
            cout << "enter the coordinates x <= 10 or y <= 10" << endl;
        }
        x -= 1;
        y -= 1;
        if (map[x][y] == '*') {
            cout << "Got" << endl;
            map[x][y] = '!';
            printMap(map);
            bool find_ship = false;
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    if (map[i][j] == '*') {
                        find_ship = true;
                    }
                }
                if (find_ship == true) {
                    break;
                }
            }
            if (find_ship == false) {
                cout << "You win!!!" << endl;
                break;
            }
        }else{
            cout << "Not got" << endl;
            map[x][y] = '#';
            printMap(map);
        }
    }
}

int main()
{
    char map[N][N];
    ifstream in("field.txt" );
    if (in.is_open()) {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                in >> map[i][j];
            }
        }
        in.close();
    }   

    printMap(map);
    checkShips(map);
    gotOrNotGot(map); 
    return 0;
}


