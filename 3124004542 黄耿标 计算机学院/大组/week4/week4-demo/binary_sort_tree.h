#include<stdio.h>
#include<malloc.h>

//定义二叉树节点
typedef struct Node {
	int data;            //数据
	struct Node* left;   //左节点
	struct Node* right;  //右节点
} Node, *NodePtr;

//创建新节点
Node* createNode(int data);

//向二叉树中插入节点
Node* insertNode(Node* root, int data);

//查找节点
Node* searchNode(Node* root, int data);

//找到最小节点
Node* findMin(Node* root);

//删除节点
Node* deleteNode(Node* root, int data);

//中序递归遍历
void inorder(Node* root);

//先序递归遍历
void preorder(Node* root);

//后序递归遍历
void postorder(Node* root);

// 释放二叉排序树的内存
void freeTree(Node* root);