//
// Created by lhc456 on 2023/5/10.
//
#include<iostream>
#include <queue>
#include<fstream>


using namespace std;

const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};

char maze[102][102];
int minTurns[102][102][4], pre[102][102][4][3];
int n, head, tail;

class postion {
public:
    int x;
    int y;
    int direction;
    int turns;
public:
    postion(int x, int y, int dir, int turns) {
        this->x = x;
        this->y = y;
        this->direction = dir;
        this->turns = turns;
    }
};


void printResult(int x, int y, int dir) {
    int res[40001][2];
    int turns = 0;
    res[0][0] = x;
    res[0][1] = y;
    while (x != 1 || y != 1) {
        int tx = pre[x][y][dir][0];
        int ty = pre[x][y][dir][1];
        dir = pre[x][y][dir][2];
        res[++turns][0] = tx;
        res[turns][1] = ty;
        x = tx;
        y = ty;
    }
    for (int i = turns; i >= 0; i--)
        cout << '(' << res[i][0] << ',' << res[i][1] << ") --> ";
    cout << '(' << n << ',' << n << ')' << endl;
}


queue<postion> q;

void bfs() {
    memset(minTurns, 10, sizeof(minTurns));
    memset(pre, 0, sizeof(pre));

    q.push(postion(1, 1, 0, -1));
    q.push(postion(1, 1, 0, -1));
    while (q.size() > 0) {
        postion cur = q.front();
        q.pop();
        int x, y, dir, turns;
        x = cur.x;
        y = cur.y;
        dir = cur.direction;
        turns = cur.turns;
        int tx = x;
        int ty = y;
        while (true) {
            tx += dx[dir];
            ty += dy[dir];
            if (maze[tx][ty] == '*')
                break;
            if (tx == n && ty == n) {
                printResult(x, y, dir);
                return;
            }
            for (int i = 0; i < 2; i++) {
                // 变化方向
                int id = (dir + 3 - i * 2) % 4;
                if (maze[tx + dx[id]][ty + dy[id]] == '.' && minTurns[tx][ty][id] > turns + 1) {
                    q.push(postion(tx, ty, id, turns + 1));
                    minTurns[tx][ty][id] = turns + 1;
                    pre[tx][ty][id][0] = x;
                    pre[tx][ty][id][1] = y;
                    pre[tx][ty][id][2] = dir;
                }
            }
        }


    }

}

int main() {
    ios::sync_with_stdio(false);
    ifstream fin("/Users/lhc456/Desktop/c++/play-with-data-structure-CPP/Search/data/dfs/2.in");
    cout.tie(NULL);

    fin >> n;
    for (int i = 0; i <= n + 1; i++) {
        string s;
        fin >> s;
        for (int j = 0; j <= n + 1; j++) {
            maze[i][j] = s[j];
        }
    }
    fin.close();

    bfs();

    cout << "Total States: " << tail << endl;
    return 0;
}