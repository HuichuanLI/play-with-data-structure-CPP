//
// Created by lhc456 on 2023/5/15.
//

#ifndef PLAY_WITH_ALGO_REDBLACKTREE_H
#define PLAY_WITH_ALGO_REDBLACKTREE_H

#include <iostream>

using namespace std;

enum colorRB {
    Red, Black
};

struct RBNode {
    int val;
    colorRB color;
    RBNode *parent, *leftChild, *rightChild;
};

RBNode *root;

int maxTreeHeight = 0;


RBNode *getNewNode(int number) {
    RBNode *node = new RBNode;
    node->val = number;
    node->leftChild = NULL;
    node->rightChild = NULL;
    node->parent = NULL;
    // 新生成的节点的颜色一律为红色
    node->color = Red;
    return node;
}

// 常规的单旋转
RBNode *rotate(RBNode *root, RBNode *a) {
    RBNode *b = a->parent;
    if (!b)
        return a;

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
    if (root == b)
        return a;
    return root;
}

RBNode *rebalanceInsert(RBNode *root, RBNode *node) {
    RBNode *parent;
    while (parent = node->parent) {
        // 如果当前节点的父节点是黑节点，符合红黑特性，直接跳出
        if (parent->color == Black)
            break;
        // 下面parent肯定都是红节点
        // 如果当前节点的父节点是根节点（即祖父节点为空）
        // 那么只需要将parent修改为黑色，即可满足红黑特性
        RBNode *gparent = parent->parent;
        if (gparent == NULL) {
            parent->color = Black;
            break;
        }
        // 父节点同层的叔节点
        RBNode *uncle = (parent == gparent->leftChild) ?
                        gparent->rightChild : gparent->leftChild;

        // 如果叔节点是黑色或者空，需要讨论
        // 红黑树本质上和AVL树类似，仍然是同侧单旋异侧双旋，但这里有一个技巧
        // 由于parent向gparent旋转这一步无论是单旋还是双旋（第二步）都要做
        // 所以不妨先判断是否需要双旋，如果需要的话，先执行双旋第一步
        if (!uncle || uncle->color == Black) {
            // 双旋条件：异侧，这里用异或来判断
            if ((parent == gparent->leftChild) ^ (node == parent->leftChild)) {
                // 只转1次（即双旋第一步），因为gparent肯定不为空，所以不用修改root
                rotate(root, node);
                // 交换node和parent变量（即让node仍然是下面的节点，无缝衔接下一步）
                RBNode *tmp = node;
                node = parent;
                parent = tmp;
            }
            // 单旋，或双旋第二步。root有可能改变，所以需要修改
            root = rotate(root, parent);
            // 旋转完成后修改父节点和祖父节点的颜色，然后就可以跳出循环
            parent->color = Black;
            gparent->color = Red;
            break;
        }
        // 最后一种情况，parent和uncle都是红节点
        // 需要修改他们以及祖父节点的颜色
        parent->color = Black;
        uncle->color = Black;
        gparent->color = Red;
        // 最后让node等于它的祖父节点，直接向上跳两层，继续
        node = gparent;
    }
    return root;
}

RBNode *rbInsert(RBNode *root, int number) {
    RBNode *current = root;
    RBNode *previous = NULL;
    while (current) {
        previous = current;
        if (current->val >= number)
            current = current->leftChild;
        else
            current = current->rightChild;
    }

    RBNode *node = getNewNode(number);
    if (!previous)
        return node;

    node->parent = previous;
    if (previous->val >= node->val)
        previous->leftChild = node;
    else
        previous->rightChild = node;

    // 红黑树的核心操作——再平衡
    return rebalanceInsert(root, node);
}

RBNode *rbFind(RBNode *root, int number) {
    RBNode *current = root;
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

RBNode *swapData(RBNode *a, RBNode *b) {
    int tmp = a->val;
    a->val = b->val;
    b->val = tmp;
    return b;
}

RBNode *rbDelete(RBNode *root, RBNode *node) {
    // 同时有左右儿子的话，和普通删除一样，需要找替代节点
    if (node->leftChild && node->rightChild) {
        RBNode *replaceNode = node->leftChild;
        while (replaceNode->rightChild)
            replaceNode = replaceNode->rightChild;
        // 特殊操作：只交换node和replaceNode的数据（val)，不改变指针或color
        // 这样等于事实上完成了交换，其他节点和它们之间的大小关系都不受影响，
        // 且交换后的node最多只会有一个左儿子，方便后续操作
        // 因为node马上就要被删掉，所以replaceNode和node之间大小关系暂时乱掉也没关系
        node = swapData(node, replaceNode);
    }
    // 这样一来，node最多只有一个儿子，且如果有的话，这个儿子一定是红节点
    // 否则违反红黑特性第二条（每条从根到叶的路径经过相同数目的黑节点）
    // 因此，当node为红节点的时候，它的儿子不可能是红节点，所以它一定没有子节点，
    // 可以直接删掉
    RBNode *parent = node->parent;
    if (node->color == Red) {
        if (parent)
            if (node == parent->leftChild)
                parent->leftChild = NULL;
            else
                parent->rightChild = NULL;
        if (root == node)
            root = NULL;
        delete (node);
    } else { // node为黑节点
        RBNode *child = (node->leftChild) ? node->leftChild : node->rightChild;
        if (child) {
            // 当node为黑节点的时候，如果它有子节点，那么肯定是红节点
            // 所以直接将它的子节点修改为黑色，然后取代它即可
            if (parent)
                if (node == parent->leftChild)
                    parent->leftChild = child;
                else
                    parent->rightChild = child;
            child->parent = parent;
            child->color = Black;
            if (root == node)
                root = child;
            delete (node);
        } else {
            // 最麻烦的情况：node为黑节点，且无子节点。
            // 此时不能直接删除node，否则就会破坏红黑特性
            // 删除node可能会影响到它的兄弟，以及它兄弟的儿子
            // 所以需要相应地对它的兄弟进行旋转，以及修改节点颜色

            // 特殊情况：如果剩余节点本身就是根节点，那么树被删空
            if (root == node)
                return NULL;
            parent = node->parent;
            bool isLeftChild = (node == parent->leftChild);
            if (isLeftChild)
                parent->leftChild = NULL;
            else
                parent->rightChild = NULL;
            delete (node);
            node = NULL;

            RBNode *brother, *closeNephew, *distantNephew;
            // 不断调整直到node已经没有父节点
            while (true) {
                if (node)
                    isLeftChild = (node == parent->leftChild);
                // 计算node的父、兄弟、远近侄子节点
                if (isLeftChild) {
                    brother = parent->rightChild;
                    closeNephew = brother->leftChild;
                    distantNephew = brother->rightChild;
                } else {
                    brother = parent->leftChild;
                    closeNephew = brother->rightChild;
                    distantNephew = brother->leftChild;
                }

                // 如果兄弟节点是红色，那么先通过一次旋转和调整将兄弟节点改为黑色
                if (brother->color == Red) {
                    root = rotate(root, brother);
                    brother->color = Black;
                    parent->color = Red;
                    brother = closeNephew;
                    if (isLeftChild) {
                        closeNephew = brother->leftChild;
                        distantNephew = brother->rightChild;
                    } else {
                        closeNephew = brother->rightChild;
                        distantNephew = brother->leftChild;
                    }
                }
                // 如果较远侄子节点存在且是红色，旋转后需要相应修改颜色，然后跳出
                if (distantNephew && distantNephew->color == Red) {
                    root = rotate(root, brother);
                    brother->color = parent->color;
                    parent->color = Black;
                    distantNephew->color = Black;
                    break;
                }
                // 如果较近侄子节点存在且是红色，旋转后需要相应修改节点颜色，然后尝试下一种情况
                if (closeNephew && closeNephew->color == Red) {
                    // 根节点不会改变，因为brother不可能是根
                    rotate(root, closeNephew);
                    brother->color = Red;
                    closeNephew->color = Black;
                    distantNephew = brother;
                    brother = closeNephew;
                    continue;
                }
                // 如果能执行到这里，两个侄子节点均为黑色（空或有数据）
                if (parent->color == Red) {
                    // 如果父节点为红色，则改为黑色，并修改兄弟节点为红色，跳出
                    brother->color = Red;
                    parent->color = Black;
                    break;
                }
                // 否则的话，兄弟节点改为红色，然后继续尝试上一层
                brother->color = Red;
                node = parent;
                parent = node->parent;
                if (!parent)
                    break;
            }
        }
    }

    return root;
}

#endif //PLAY_WITH_ALGO_REDBLACKTREE_H
