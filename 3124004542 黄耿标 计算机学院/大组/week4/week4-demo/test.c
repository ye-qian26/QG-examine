#include "non_recursive_traversal.h"

int main() {
	Node* root = NULL;

	//δ�������������
	root = insertNode(root, 10);
	insertNode(root, 7);
	insertNode(root, 6);
	insertNode(root, 8);
	insertNode(root, 12);
	insertNode(root, 11);
	insertNode(root, 13);

	printf("����ݹ�������£�\n");
	preorder(root);
	printf("\n");

	printf("����ݹ�������£�\n");
	inorder(root);
	printf("\n");

	printf("����ݹ�������£�\n");
	postorder(root);
	printf("\n");

	printf("---------------------------\n");

	printf("����ǵݹ�������£�\n");
	preorderWithStack(root);

	printf("����ǵݹ�������£�\n");
	inorderWithStack(root);

	printf("����ǵݹ�������£�\n");
	postorderWithStack(root);

	printf("��α������£�\n");
	levelorder(root);

	printf("---------------------------\n");

	int data = 8;
	Node* find = searchNode(root, data);
	if (find != NULL) {
		printf("�ҵ��ýڵ㣺%d\n", find->data);
	}
	else {
		printf("δ�ҵ��ýڵ�\n");
	}

	root = deleteNode(root, data);
	printf("ɾ���ڵ� %d ��Ķ���������������£�\n", data);
	inorder(root);
	printf("\n");

	//�ͷ��ڴ�
	freeTree(root);
	return 0;
}