#include<stdio.h>
#include<malloc.h>

//����������ڵ�
typedef struct Node {
	int data;            //����
	struct Node* left;   //��ڵ�
	struct Node* right;  //�ҽڵ�
} Node, *NodePtr;

//�����½ڵ�
Node* createNode(int data);

//��������в���ڵ�
Node* insertNode(Node* root, int data);

//���ҽڵ�
Node* searchNode(Node* root, int data);

//�ҵ���С�ڵ�
Node* findMin(Node* root);

//ɾ���ڵ�
Node* deleteNode(Node* root, int data);

//����ݹ����
void inorder(Node* root);

//����ݹ����
void preorder(Node* root);

//����ݹ����
void postorder(Node* root);

// �ͷŶ������������ڴ�
void freeTree(Node* root);