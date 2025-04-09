#include "non_recursive_traversal.h"

//初始化链栈
void initStack(LinkStack* s) {
	s->top = NULL;
}

//判断链栈是否为空
bool isEmpty(LinkStack* s) {
	return s->top == NULL;
}

//入栈操作
void push(LinkStack* s, Node* node) {
	StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
	if (newNode == NULL) {
		printf("内存分配失败\n");
		return;
	}
	newNode->node = node;
	newNode->next = s->top;
	newNode->isVisit = 0;
	s->top = newNode;
}

//出栈操作
Node* pop(LinkStack* s) {
	if (isEmpty(s)) {
		printf("链栈为空，无法出栈\n");
		return -1;
	}
	StackNode* p = s->top;
	Node* node = p->node;
	s->top = p->next;
	free(p);
	return node;
}

//非递归先序遍历
void preorderWithStack(Node* root) {
	if (root == NULL) {
		printf("二叉树无数据\n");
		return;
	}
	//创建一个新的链栈
	LinkStack s;
	initStack(&s);

	push(&s, root);

	while (!isEmpty(&s)) {
		Node* node = pop(&s);
		printf("%d ", node->data);

		//右节点先入栈
		if (node->right != NULL) {
			push(&s, node->right);
		}
		
		//左节点后入栈
		if (node->left != NULL) {
			push(&s, node->left);
		}
	}
	printf("\n");
}

//非递归中序遍历
void inorderWithStack(Node* root) {
	if (root == NULL) {
		printf("二叉树无数据\n");
		return;
	}
	//创建一个新的链栈
	LinkStack s;
	initStack(&s);
	Node* node = root;

	while (node != NULL || !isEmpty(&s)) {
		//遍历到最左的的节点，将途经的节点入栈
		while (node != NULL) {
			push(&s, node);
			node = node->left;
		}

		//将栈顶元素出栈
		node = pop(&s);
		printf("%d ", node->data);

		//转移到右子树
		node = node->right;
	}
	printf("\n");
}

//获取栈顶元素标记
int getTopIsVisit(LinkStack* s) {
	if (!isEmpty(s)) {
		return s->top->isVisit;
	}
	return -1;
}

//设置栈顶元素标记
void setTopIsVisit(LinkStack* s, int visit) {
	if (!isEmpty(s)) {
		s->top->isVisit = visit;
	}
}

//非递归后序遍历
void postorderWithStack(Node* root) {
	if (root == NULL) {
		printf("二叉树无数据\n");
		return;
	}

	//创建一个新的链栈
	LinkStack s;
	initStack(&s);
	Node* node = root;

	while (node != NULL || !isEmpty(&s)) {
		while (node != NULL) {
			push(&s, node);
			node = node->left;
		}
		if (getTopIsVisit(&s) == 0) {
			//第一次访问，跳转到右节树
			setTopIsVisit(&s, 1);
			node = s.top->node->right;
		}
		else {
			//第二次访问，取出栈顶元素
			node = pop(&s);
			printf("%d ", node->data);
			node = NULL;
		}
	}
	printf("\n");
}




//初始化队列
void initQueue(Queue* q) {
	q->front = NULL;
	q->rear = NULL;
}

//判断队列是否为空
bool isQueueEmpty(Queue* q) {
	return q->front == NULL;
}

//入队
void enqueue(Queue* q, Node* node) {
	QueueNode* newQueueNode = (QueueNode*)malloc(sizeof(QueueNode));
	if (newQueueNode == NULL) {
		printf("内存分配失败\n");
		return;
	}
	//存数据
	newQueueNode->node = node;
	newQueueNode->next = NULL;

	//入队
	if (isQueueEmpty(q)) {
		q->front = q->rear = newQueueNode;
	}
	else {
		q->rear->next = newQueueNode;
		q->rear = newQueueNode;
	}
}

//出队
Node* dequeue(Queue* q) {
	if (isQueueEmpty(q)) {
		printf("队列中无数据，无法出队\n");
		return NULL;
	}
	QueueNode* tmp = q->front;
	Node* node = tmp->node;

	q->front = q->front->next;
	if (q->front == NULL) {
		q->rear = NULL;
	}
	free(tmp);
	return node;
}

//层次遍历
void levelorder(Node* root) {
	if (root == NULL) {
		printf("二叉树中无数据\n");
		return;
	}

	//创建一个队列
	Queue q;
	initQueue(&q);

	//将根节点入列
	enqueue(&q, root);

	while (!isQueueEmpty(&q)) {
		Node* node = dequeue(&q);
		printf("%d ", node->data);

		if (node->left != NULL) {
			enqueue(&q, node->left);
		}

		if (node->right != NULL) {
			enqueue(&q, node->right);
		}
	}
	printf("\n");
}