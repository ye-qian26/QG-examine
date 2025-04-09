#include "binary_sort_tree.h"

//创建新节点
Node* createNode(int data) {
	Node* newNode = (Node*)malloc(sizeof(Node));

	if (newNode == NULL) {
		printf("内存分配失败\n");
		return NULL;
	}
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

//向二叉树中插入节点
Node* insertNode(Node* root, int data)
{
	//直到找到应放置的位置时创建一个新的节点存储数据
	if (root == NULL) {
		return createNode(data);
	}

	if (data < root->data) {
		//入左孩子继续递归判断
		root->left = insertNode(root->left, data);
	}
	else if (data > root->data) {
		//入右孩子继续递归判断
		root->right = insertNode(root->right, data);
	}

	return root;
}

//查找节点
Node* searchNode(Node* root, int data)
{
	//找到了或者找不到
	if (root == NULL || root->data == data) {
		return root;
	}

	//如果数据比根节点数据小就往左孩子继续找
	if (data < root->data) {
		return searchNode(root->left, data);
	}

	//如果数据比根节点数据大就往右孩子继续找
	if (data > root->data) {
		return searchNode(root->right, data);
	}
}

//找到最小节点
Node* findMin(Node* root) {
	while (root->left != NULL) {
		root = root->left;
	}
	return root;
}

//删除节点
Node* deleteNode(Node* root, int data) {
	if (root == NULL) {
		return root;
	}

	if (data < root->data) {
		//要删除的节点的数据小于当前节点数据
		root->left =  deleteNode(root->left, data);
	}
	else if (data > root->data) {
		//要删除的节点的数据大于当前节点数据
		root->right = deleteNode(root->right, data);
	}
	else {
		//要删除的节点的数据等于当前节点数据
		if (root->left == NULL) {
			//该节点的左节点为空
			Node* tmp = root->right;
			free(root);
			return tmp;
		}
		else if (root->right == NULL) {
			//该节点的右节点为空
			Node* tmp = root->left;
			free(root);
			return tmp;
		}

		//该节点的左右节点都不为空
		//找直接后继
		Node* tmp = findMin(root->right);
		root->data = tmp->data;
		root->right =  deleteNode(root->right, tmp->data);
	}
	return root;
}

//中序递归遍历
void inorder(Node* root) {
	if (root != NULL) {
		inorder(root->left);
		printf("%d ", root->data);
		inorder(root->right);
	}
}

//先序递归遍历
void preorder(Node* root) {
	if (root != NULL) {
		printf("%d ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}

//后序递归遍历
void postorder(Node* root) {
	if (root != NULL) {
		postorder(root->left);
		postorder(root->right);
		printf("%d ", root->data);
	}
}

// 释放二叉排序树的内存
void freeTree(Node* root) {
	if (root != NULL) {
		freeTree(root->left);
		freeTree(root->right);
		free(root);
	}
}