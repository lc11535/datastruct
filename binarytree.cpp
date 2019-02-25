/*
 *  二叉树的常见操作
 */

#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <stack>
#include <vector>

using namespace std;


typedef int TElemType;

typedef struct BiTNode{
    TElemType e;
    BiTNode *lchild, *rchild;
}BiTNode;

typedef struct BiTree{
    BiTNode* root;
}BiTree;

#define VISIT(node) {printf("%d\n", node->e);}


// 生成二叉树，按照层序结构，依次从终端读取数据，生成完全二叉树。读取时出错结束。
void CreateBiTree(BiTree* tree){
    if (tree == NULL) return;

    TElemType e;
    tree->root = NULL;

    printf("enter number to create tree:");

    // 生成根结点
    if ( scanf("%d", &e) != 1 ) {
        printf("end\n");
        return;
    }

    tree->root = (BiTNode*)malloc(sizeof(BiTNode));
    tree->root->e = e;
    tree->root->lchild = tree->root->rchild = NULL;

    // 借助层序遍历的思想，按照输入顺序，生成完全二叉树
    std::queue<BiTNode*> q;
    q.push(tree->root);

    
    while( !q.empty() ){

        BiTNode* p = q.front();
        q.pop();

        // 创建结点的左孩子
        if ( scanf("%d", &e) != 1 ) {
            printf("end\n");
            break;
        }

        p->lchild = (BiTNode*)malloc(sizeof(BiTNode));
        p->lchild->e = e;
        p->lchild->lchild = p->lchild->rchild = NULL;

        q.push(p->lchild);
        
        // 创建结点的右孩子
        if ( scanf("%d", &e) != 1 ) {
            printf("end\n");
            break;
        }

        p->rchild = (BiTNode*)malloc(sizeof(BiTNode));
        p->rchild->e = e;
        p->rchild->lchild = p->rchild->rchild = NULL;
        q.push(p->rchild);
    }
}

void CreateDeafultTree(BiTree* tree){
    if (tree == NULL) return;

    TElemType e = 1;

    // 生成根结点
    tree->root = (BiTNode*)malloc(sizeof(BiTNode));
    tree->root->e = e;
    tree->root->lchild = tree->root->rchild = NULL;

    // 借助层序遍历的思想，按照输入顺序，生成完全二叉树
    std::queue<BiTNode*> q;
    q.push(tree->root);

    while( !q.empty() ){

        BiTNode* p = q.front();
        q.pop();

        // 创建结点的左孩子
        p->lchild = (BiTNode*)malloc(sizeof(BiTNode));
        p->lchild->e = ++e;
        p->lchild->lchild = p->lchild->rchild = NULL;
        if (e >= 7) break;

        q.push(p->lchild);
        
        // 创建结点的右孩子
        p->rchild = (BiTNode*)malloc(sizeof(BiTNode));
        p->rchild->e = ++e;
        p->rchild->lchild = p->rchild->rchild = NULL;
        if (e >= 7) break;

        q.push(p->rchild);
    }
}

// 层序遍历 - 借助 queue
void LevelOrderTraverse(BiTNode* root){
    if (root == NULL) return;
    
    std::queue<BiTNode*> q;
    q.push(root);

    while( !q.empty() ){

        BiTNode* p = q.front();             // 取出
        q.pop();

        VISIT(p);                           // 访问

        if (p->lchild) q.push(p->lchild); // 其左孩子入栈
        if (p->rchild) q.push(p->rchild); // 其右孩子入栈
    }
}

// 先序遍历 - 递归
void PreOrderTraverse(BiTNode* root) {
    if (root == NULL) return;
    VISIT(root);
    PreOrderTraverse(root->lchild);
    PreOrderTraverse(root->rchild);
}

// 先序遍历 - 递推 - 借助 stack
void PreOrderTraverseNonRecursion(BiTNode* root) {
    if (root == NULL) return;

    std::stack<BiTNode*> stk;
    stk.push(root);

    while( ! stk.empty() ){

        BiTNode* p = stk.top();
        VISIT(p);
        stk.pop();

        if (p->rchild != NULL ) { // 先压右，pop的时候就先pop的左，即先访问的左
            stk.push(p->rchild);
        }

        if (p->lchild != NULL ) {
            stk.push(p->lchild); 
        }
    }
}


// 中序遍历 - 递归
void InOrderTraverse(BiTNode* root) {
    if (root == NULL) return;

    InOrderTraverse(root->lchild);
    VISIT(root);
    InOrderTraverse(root->rchild);
}

// 中序遍历 - 递推
void InOrderTraverseNonRecursion(BiTNode* root) {
    if (root == NULL) return;

    std::stack<BiTNode*> stk;
    BiTNode* p = root;

    while( p || ! stk.empty() ){

        if (p != NULL) {
            stk.push(p);
            p = p->lchild;
        }
        else{
            p = stk.top();
            stk.pop();
            VISIT(p);
            p = p->rchild;
        }

    }

}

// 后序遍历 - 递归
void PostOrderTraverse(BiTNode* root) {
    if (root == NULL) return;

    PostOrderTraverse(root->lchild);
    PostOrderTraverse(root->rchild);
    VISIT(root);
}



int main()
{
    BiTree tree;
    //CreateBiTree(&tree);
    CreateDeafultTree(&tree);

    printf("LevelOrderTraverse\n");
    LevelOrderTraverse(tree.root);

    printf("PreOrderTraverse\n");
    PreOrderTraverse(tree.root);

    printf("PreOrderTraverseNonRecursion\n");
    PreOrderTraverseNonRecursion(tree.root);

    printf("InOrderTraverse\n");
    InOrderTraverse(tree.root);

    printf("InOrderTraverseNonRecursion\n");
    InOrderTraverseNonRecursion(tree.root);
   
    printf("PostOrderTraverse\n");
    PostOrderTraverse(tree.root);

    return 0;
}
