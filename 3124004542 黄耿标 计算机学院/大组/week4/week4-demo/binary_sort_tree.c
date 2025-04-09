#include "binary_sort_tree.h"

//�����½ڵ�
Node* createNode(int data) {
	Node* newNode = (Node*)malloc(sizeof(Node));

	if (newNode == NULL) {
		printf("�ڴ����ʧ��\n");
		return NULL;
	}
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

//��������в���ڵ�
Node* insertNode(Node* root, int data)
{
	//ֱ���ҵ�Ӧ���õ�λ��ʱ����һ���µĽڵ�洢����
	if (root == NULL) {
		return createNode(data);
	}

	if (data < root->data) {
		//�����Ӽ����ݹ��ж�
		root->left = insertNode(root->left, data);
	}
	else if (data > root->data) {
		//���Һ��Ӽ����ݹ��ж�
		root->right = insertNode(root->right, data);
	}

	return root;
}

//���ҽڵ�
Node* searchNode(Node* root, int data)
{
	//�ҵ��˻����Ҳ���
	if (root == NULL || root->data == data) {
		return root;
	}

	//������ݱȸ��ڵ�����С�������Ӽ�����
	if (data < root->data) {
		return searchNode(root->left, data);
	}

	//������ݱȸ��ڵ����ݴ�����Һ��Ӽ�����
	if (data > root->data) {
		return searchNode(root->right, data);
	}
}

//�ҵ���С�ڵ�
Node* findMin(Node* root) {
	while (root->left != NULL) {
		root = root->left;
	}
	return root;
}

//ɾ���ڵ�
Node* deleteNode(Node* root, int data) {
	if (root == NULL) {
		return root;
	}

	if (data < root->data) {
		//Ҫɾ���Ľڵ������С�ڵ�ǰ�ڵ�����
		root->left =  deleteNode(root->left, data);
	}
	else if (data > root->data) {
		//Ҫɾ���Ľڵ�����ݴ��ڵ�ǰ�ڵ�����
		root->right = deleteNode(root->right, data);
	}
	else {
		//Ҫɾ���Ľڵ�����ݵ��ڵ�ǰ�ڵ�����
		if (root->left == NULL) {
			//�ýڵ����ڵ�Ϊ��
			Node* tmp = root->right;
			free(root);
			return tmp;
		}
		else if (root->right == NULL) {
			//�ýڵ���ҽڵ�Ϊ��
			Node* tmp = root->left;
			free(root);
			return tmp;
		}

		//�ýڵ�����ҽڵ㶼��Ϊ��
		//��ֱ�Ӻ��
		Node* tmp = findMin(root->right);
		root->data = tmp->data;
		root->right =  deleteNode(root->right, tmp->data);
	}
	return root;
}

//����ݹ����
void inorder(Node* root) {
	if (root != NULL) {
		inorder(root->left);
		printf("%d ", root->data);
		inorder(root->right);
	}
}

//����ݹ����
void preorder(Node* root) {
	if (root != NULL) {
		printf("%d ", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}

//����ݹ����
void postorder(Node* root) {
	if (root != NULL) {
		postorder(root->left);
		postorder(root->right);
		printf("%d ", root->data);
	}
}

// �ͷŶ������������ڴ�
void freeTree(Node* root) {
	if (root != NULL) {
		freeTree(root->left);
		freeTree(root->right);
		free(root);
	}
}