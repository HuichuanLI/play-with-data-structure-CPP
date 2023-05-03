//
// Created by lhc456 on 2023/5/3.
//

#include "UF.h"

class UnionFind1 : public UF {
private:
    int *id;
    int size;
public:
    UnionFind1(int capacity) {
        id = new int[capacity];
        size = capacity;
        for (int i = 0; i < size; ++i) {
            id[i] = i;
        }
    }

    int getSize() {
        return size;
    }

    int find(int p) {
        assert(p >= 0 && p < size);
        return id[p];
    }

    bool isConnected(int p, int q) {
        return find(p) == find(q);
    }

    void unionElements(int p, int q) {
        int pID = find(p);
        int qID = find(q);
        if (pID == qID) {
            return;
        }

        for (int i = 0; i < size; ++i) {
            if (id[i] == pID) {
                id[i] = qID;
            }
        }
    }
};