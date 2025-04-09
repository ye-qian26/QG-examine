#include "non_recursive_traversal.h"

int main() {
	Node* root = NULL;

	//未二叉树添加数据
	root = insertNode(root, 10);
	insertNode(root, 7);
	insertNode(root, 6);
	insertNode(root, 8);
	insertNode(root, 12);
	insertNode(root, 11);
	insertNode(root, 13);

	printf("先序递归遍历如下：\n");
	preorder(root);
	printf("\n");

	printf("中序递归遍历如下：\n");
	inorder(root);
	printf("\n");

	printf("后序递归遍历如下：\n");
	postorder(root);
	printf("\n");

	printf("---------------------------\n");

	printf("先序非递归遍历如下：\n");
	preorderWithStack(root);

	printf("中序非递归遍历如下：\n");
	inorderWithStack(root);

	printf("后序非递归遍历如下：\n");
	postorderWithStack(root);

	printf("层次遍历如下：\n");
	levelorder(root);

	printf("---------------------------\n");

	int data = 8;
	Node* find = searchNode(root, data);
	if (find != NULL) {
		printf("找到该节点：%d\n", find->data);
	}
	else {
		printf("未找到该节点\n");
	}

	root = deleteNode(root, data);
	printf("删除节点 %d 后的二叉树中序遍历如下：\n", data);
	inorder(root);
	printf("\n");

	//释放内存
	freeTree(root);
	return 0;
}