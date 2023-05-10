//
// Created by lhc456 on 2023/5/11.
//
#include<iostream>
#include <queue>
#include <fstream>
#include <time.h>

using namespace std;

struct PuzzleState {
    int puzzle[9];
    int depth;
};

int getPermutationHash(int perm[9]) {
    const int fact[9] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320};
    int res = 0;
    for (int i = 0; i < 9; i++) {
        int t = 0;
        for (int j = 0; j < i; j++)
            if (perm[j] > perm[i])
                t++;
        res += t * fact[i];
    }
    return res;
}

long getTime() {
    struct timeval tv;
    clock_t start, finish;
    start = clock();
    return start;
}

bool isSameBoard(int a[9], int b[9]) {
    for (int i = 0; i < 9; i++)
        if (a[i] != b[i])
            return false;
    return true;
}

void printResult(int depth, int stateCount, long tstart, long tend) {
    cout << "Total steps: " << depth << endl;
    cout << "Total states: " << stateCount << endl;
    cout << "Total run time: " << (tend - tstart + 0.0) / 1000 << endl;
}

void bfs(PuzzleState sp, PuzzleState ep) {
    queue<PuzzleState> q;
    q.push(sp);
    int hashState[362881];
    for (int i = 0; i <= 362880; i++)
        hashState[i] = INT_MAX;
    hashState[getPermutationHash(sp.puzzle)] = 0;
    long tstart = getTime();

    int stateCount = 0;
    while (!q.empty()) {
        PuzzleState state = q.front();
        q.pop();
        stateCount++;
        int p = 0;
        while (state.puzzle[p] != 0)
            p++;
        for (int i = 0; i < 4; i++) {
            int newPuzzle[9];
            memcpy(newPuzzle, state.puzzle, sizeof(newPuzzle));
            int rp = -1;
            if (i == 0 && p < 6)
                rp = p + 3;
            if (i == 1 && p > 2)
                rp = p - 3;
            if (i == 2 && p % 3 != 2)
                rp = p + 1;
            if (i == 3 && p % 3 != 0)
                rp = p - 1;
            if (rp == -1)
                continue;
            newPuzzle[p] = newPuzzle[rp];
            newPuzzle[rp] = 0;

            int permHash = getPermutationHash(newPuzzle);
            if (hashState[permHash] < INT_MAX)
                continue;
            hashState[permHash] = state.depth + 1;
            if (isSameBoard(newPuzzle, ep.puzzle)) {
                printResult(state.depth + 1, stateCount, tstart, getTime());
                return;
            }
            PuzzleState ps;
            ps.depth = state.depth + 1;
            memcpy(ps.puzzle, newPuzzle, sizeof(ps.puzzle));
            q.push(ps);
        }

    }
}

int main() {
    ios::sync_with_stdio(false);
    ifstream fin("/Users/lhc456/Desktop/c++/play-with-data-structure-CPP/Search/data/astar/1.in");
    cout.tie(NULL);

    PuzzleState sp, ep;
    sp.depth = 0;
    for (int i = 0; i < 9; i++)
        fin >> sp.puzzle[i];
    for (int i = 0; i < 9; i++)
        fin >> ep.puzzle[i];
    fin.close();

    bfs(sp, ep);

    return 0;
}