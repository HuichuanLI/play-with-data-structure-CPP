//
// Created by lhc456 on 2023/5/15.
//

#ifndef PLAY_WITH_ALGO_AVLTEST_H
#define PLAY_WITH_ALGO_AVLTEST_H

#include <iostream>
#include <sys/time.h>
#include <fstream>


using namespace std;

struct AVLNode {
    int val, bf;
    AVLNode *leftChild, *rightChild, *parent;
};

AVLNode *root = NULL;

int maxTreeHeight = 0;

long getTime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

AVLNode *getNewNode(int number) {
    AVLNode *node = new AVLNode;
    node->val = number;
    node->leftChild = NULL;
    node->rightChild = NULL;
    node->parent = NULL;
    node->bf = 0;
    return node;
}

void rotate(AVLNode *a) {
    AVLNode *b = a->parent;
    if (!b)
        return;

    // 计算旋转后二者的bf值变化
    // 注意：此时a和b的bf值已经按照插入后的值进行了修改
    // a的bf可能值为-1, 0, 1
    // b的bf可能值为-2, -1, 1, 2，不可能是0，否则不会发生旋转
    // 需要根据a和b的值来分类讨论
    if (a->bf == 0 && abs(b->bf) < 2) {
        // 如果a是新插入节点，那么b的值只可能是-1或1（0的话压根不会旋转）
        // 此时a的bf值应该取决于a是b的左子节点还是右子节点，b的bf值应为0
        a->bf = (a == b->leftChild) ? 1 : -1;
        b->bf = 0;
    } else if (abs(b->bf) < 2) {
        // b的bf是-1或1，即a插入改变了b的平衡
        if (a->bf == b->bf) {
            // a和b的偏向相同，则旋转后a和b的左右偏向都刚好和原来相反
            b->bf = -b->bf;
            a->bf = -a->bf;
        } else {
            // a和b偏向相反，则旋转后b平衡，a的bf变为之前的2倍
            // 问：这种情况是否会发生呢？
            b->bf = 0;
            a->bf *= 2;
        }
    } else {
        // b的bf是-2或者2
        // 此时只有一种可能，就是a和b的偏向相同（即单旋或双旋第二步）
        // 所以旋转完后a的bf变为0，b的bf计算如下
        if (b->bf == -2) {
            b->bf = b->bf + 1 - a->bf;
            a->bf = (a->bf < 0) ? 0 : a->bf + 1;
        } else {
            b->bf = b->bf - 1 - a->bf;
            a->bf = (a->bf > 0) ? 0 : a->bf - 1;
        }
    }

    // 计算完a和b各自新的bf后，再进行旋转
    if (a == b->leftChild) {
        b->leftChild = a->rightChild;
        if (a->rightChild)
            a->rightChild->parent = b;
        a->rightChild = b;
    } else {
        b->rightChild = a->leftChild;
        if (a->leftChild)
            a->leftChild->parent = b;
        a->leftChild = b;
    }

    if (b->parent)
        if (b == b->parent->leftChild)
            b->parent->leftChild = a;
        else
            b->parent->rightChild = a;

    a->parent = b->parent;
    b->parent = a;
}

// 插入操作的再平衡过程
// x代表当前节点，y代表父节点
// 返回新的根节点
AVLNode *rebalanceInsert(AVLNode *root, AVLNode *x) {
    AVLNode *y = x->parent;
    while (y) {
        // 插入到y的高度较低的一边，此时平衡，可以退出
        if (x == y->leftChild && y->bf > 0 ||
            x == y->rightChild && y->bf < 0) {
            y->bf = 0;
            break;
        }
        // y两边平衡，此时插入到的那一边的高度+1，继续判断y的父节点
        if (y->bf == 0) {
            y->bf = (x == y->leftChild) ? -1 : 1;
            x = y;
            y = y->parent;
        } else {
            // 否则出现了高度差为+-2的情况，需要进行旋转，完成旋转后直接退出
            y->bf *= 2;
            AVLNode *z = NULL;
            // 同侧单旋，注意=0也算同侧
            if (x == y->leftChild && x->bf <= 0 ||
                x == y->rightChild && x->bf >= 0) {
                z = x;
                rotate(z);
            } else {
                // 异侧双旋
                z = (x == y->leftChild) ? x->rightChild : x->leftChild;
                rotate(z);
                rotate(z);
            }

            // 如果旋转完成后z没有父节点，则z是新的根节点，返回
            if (z->parent == NULL)
                return z;
            return root;
        }
    }
    return root;
}

AVLNode *avlInsert(AVLNode *root, int number) {
    AVLNode *current = root;
    AVLNode *previous = NULL;
    while (current) {
        previous = current;
        if (current->val >= number)
            current = current->leftChild;
        else
            current = current->rightChild;
    }

    AVLNode *node = getNewNode(number);
    if (!previous)
        return node;

    node->parent = previous;
    if (previous->val >= node->val)
        previous->leftChild = node;
    else
        previous->rightChild = node;

    // AVL的核心操作——再平衡
    return rebalanceInsert(root, node);
}

AVLNode *avlFind(AVLNode *root, int number) {
    AVLNode *current = root;
    while (current) {
        if (current->val == number)
            return current;
        else if (current->val > number)
            current = current->leftChild;
        else
            current = current->rightChild;
    }
    return NULL;
}

// 删除操作的再平衡过程
// x代表当前节点，y代表父节点
// 返回新的根节点
AVLNode *rebalanceDelete(AVLNode *root, AVLNode *x) {
    while (x) {
        // x的bf是-1或者1，说明删除之前x的bf是0，此时更高节点的bf不会改变，退出
        if (x->bf == 1 || x->bf == -1)
            break;
        // x的bf是0，说明删除前是1或者-1，以x为根的树高度减1，对x的父节点会产生影响
        // 修改父节点的bf，继续检查它的父节点
        if (x->bf == 0) {
            if (x->parent)
                x->parent->bf += (x == x->parent->leftChild) ? 1 : -1;
            x = x->parent;
        } else {
            // 否则x的bf为+-2，说明删除导致x出现了平衡因子不合法的情况
            // 需要对x的另一侧进行旋转来消除不合法
            // 与插入的rebalance不同：插入旋转1次就可以消除不平衡，而删除
            // 会导致树高降低，旋转也会导致树高降低，叠加后可能导致上层节点出现
            // 平衡因子变为2或者-2，所以要不断向上修改，而不能旋转1次就退出
            AVLNode *y = x->parent;
            AVLNode *z = (x->bf == -2) ? x->leftChild : x->rightChild;
            bool heightNoChange = false;
            // 同侧单旋，注意这里=0也看作单侧
            // 这里比较麻烦的是，删除会降低树的高度，所以z会来自被删除的一侧的对侧
            // 所以z完全有可能bf为0，而且旋转完后这棵树高度不降
            // 不降的话就没必要继续循环了
            if (x->bf < 0 && z->bf <= 0 ||
                x->bf > 0 && z->bf >= 0) {
                if (z->bf == 0)
                    heightNoChange = true;
                rotate(z);
            } else {
                // 异侧双旋
                z = (z == x->leftChild) ? z->rightChild : z->leftChild;
                rotate(z);
                rotate(z);
            }
            // 如果x是旋转之前的根节点，则z是新的根节点，返回
            if (root == x)
                return z;
            // 和插入的rebalance不同：这里不能直接返回，因为父节点
            // 的bf值有可能会变得不合法
            // 旋转完后，这一侧树高度可能会-1，所以要调整父节点的bf值
            // 否则的话，对更高层的节点的bf值无影响，可以直接跳出循环
            if (!heightNoChange)
                y->bf += (z == y->leftChild) ? 1 : -1;
            else
                break;
            x = y;
        }
    }
    return root;
}

// 和BSTDelete区别：delete过程中要修改受影响节点的bf值
AVLNode *avlDelete(AVLNode *root, AVLNode *node) {
    // rebalanceNode定义：最深的删除后bf值改变的节点
    // 除了被删除节点同时有左右子节点时，是代替节点（左子树最大节点）的父节点之外
    // 其余情况都是被删除节点的父节点
    AVLNode *rebalanceNode = node->parent;
    if (!(node->leftChild || node->rightChild)) {
        if (root == node) {
            root = NULL;
        } else {
            if (node->parent->leftChild == node) {
                node->parent->leftChild = NULL;
                node->parent->bf++;
            } else {
                node->parent->rightChild = NULL;
                node->parent->bf--;
            }
            node->parent = NULL;
        }
    } else if (node->leftChild && !node->rightChild) {
        if (root == node) {
            root = node->leftChild;
            node->leftChild->parent = NULL;
        } else {
            node->leftChild->parent = node->parent;
            if (node == node->parent->leftChild) {
                node->parent->leftChild = node->leftChild;
                node->parent->bf++;
            } else {
                node->parent->rightChild = node->leftChild;
                node->parent->bf--;
            }
        }
    } else if (node->rightChild && !node->leftChild) {
        if (root == node) {
            root = node->rightChild;
            node->rightChild->parent = NULL;
        } else {
            node->rightChild->parent = node->parent;
            if (node == node->parent->leftChild) {
                node->parent->leftChild = node->rightChild;
                node->parent->bf++;
            } else {
                node->parent->rightChild = node->rightChild;
                node->parent->bf--;
            }
        }
    } else {
        AVLNode *replaceNode = node->leftChild;
        while (replaceNode->rightChild)
            replaceNode = replaceNode->rightChild;
        if (replaceNode->leftChild)
            replaceNode->leftChild->parent = replaceNode->parent;
        if (replaceNode == replaceNode->parent->leftChild) {
            replaceNode->parent->leftChild = replaceNode->leftChild;
            replaceNode->parent->bf++;
            // 特殊情况：如果代替节点就是待删除节点的左子节点，那么rebalance
            // 的起始节点应该是replaceNode自身
            rebalanceNode = replaceNode;
        } else {
            replaceNode->parent->rightChild = replaceNode->leftChild;
            replaceNode->parent->bf--;
            rebalanceNode = replaceNode->parent;
        }

        replaceNode->leftChild = node->leftChild;
        replaceNode->rightChild = node->rightChild;
        if (node->leftChild)
            node->leftChild->parent = replaceNode;
        node->rightChild->parent = replaceNode;
        replaceNode->parent = node->parent;
        replaceNode->bf = node->bf;
        if (node->parent)
            if (node == node->parent->leftChild)
                node->parent->leftChild = replaceNode;
            else
                node->parent->rightChild = replaceNode;
        if (root == node)
            root = replaceNode;
    }
    delete node;
    // AVL核心操作——再平衡
    return rebalanceDelete(root, rebalanceNode);
}

void printAvl(AVLNode *node, ofstream &fout, int h) {
    if (h > maxTreeHeight)
        maxTreeHeight = h;
    if (node == NULL)
        return;
    printAvl(node->leftChild, fout, h + 1);
    fout << node->val << ' ' << h << endl;
    printAvl(node->rightChild, fout, h + 1);
}

#endif //PLAY_WITH_ALGO_AVLTEST_H
