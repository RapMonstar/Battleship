#include <iostream>
#include <fstream>


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


void checkShips(char map[N][N]) {
    int isCorrect = true;
    int t = 0;
    int temp_a = 0;//лево
    int temp_b = 0;//вверх
    int temp_c = 0;//право
    int temp_d = 0;//низ
    for (int i = 0; i < N; i++)
    {
        t = 0;
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
    if (isCorrect) {
        cout << ("Map is correct!") << endl;
    }
}

void gotOrNotGot(char map[N][N]) {
    int x, y;
    while (true) {
        cout << "enter the coordinates of the target : " << endl;
        cin >> x;
        cin >> y;
        x -=1;
        y -=1;
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
        }
        else {
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


