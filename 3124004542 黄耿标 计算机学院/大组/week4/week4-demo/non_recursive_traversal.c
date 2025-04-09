#include "non_recursive_traversal.h"

//��ʼ����ջ
void initStack(LinkStack* s) {
	s->top = NULL;
}

//�ж���ջ�Ƿ�Ϊ��
bool isEmpty(LinkStack* s) {
	return s->top == NULL;
}

//��ջ����
void push(LinkStack* s, Node* node) {
	StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
	if (newNode == NULL) {
		printf("�ڴ����ʧ��\n");
		return;
	}
	newNode->node = node;
	newNode->next = s->top;
	newNode->isVisit = 0;
	s->top = newNode;
}

//��ջ����
Node* pop(LinkStack* s) {
	if (isEmpty(s)) {
		printf("��ջΪ�գ��޷���ջ\n");
		return -1;
	}
	StackNode* p = s->top;
	Node* node = p->node;
	s->top = p->next;
	free(p);
	return node;
}

//�ǵݹ��������
void preorderWithStack(Node* root) {
	if (root == NULL) {
		printf("������������\n");
		return;
	}
	//����һ���µ���ջ
	LinkStack s;
	initStack(&s);

	push(&s, root);

	while (!isEmpty(&s)) {
		Node* node = pop(&s);
		printf("%d ", node->data);

		//�ҽڵ�����ջ
		if (node->right != NULL) {
			push(&s, node->right);
		}
		
		//��ڵ����ջ
		if (node->left != NULL) {
			push(&s, node->left);
		}
	}
	printf("\n");
}

//�ǵݹ��������
void inorderWithStack(Node* root) {
	if (root == NULL) {
		printf("������������\n");
		return;
	}
	//����һ���µ���ջ
	LinkStack s;
	initStack(&s);
	Node* node = root;

	while (node != NULL || !isEmpty(&s)) {
		//����������ĵĽڵ㣬��;���Ľڵ���ջ
		while (node != NULL) {
			push(&s, node);
			node = node->left;
		}

		//��ջ��Ԫ�س�ջ
		node = pop(&s);
		printf("%d ", node->data);

		//ת�Ƶ�������
		node = node->right;
	}
	printf("\n");
}

//��ȡջ��Ԫ�ر��
int getTopIsVisit(LinkStack* s) {
	if (!isEmpty(s)) {
		return s->top->isVisit;
	}
	return -1;
}

//����ջ��Ԫ�ر��
void setTopIsVisit(LinkStack* s, int visit) {
	if (!isEmpty(s)) {
		s->top->isVisit = visit;
	}
}

//�ǵݹ�������
void postorderWithStack(Node* root) {
	if (root == NULL) {
		printf("������������\n");
		return;
	}

	//����һ���µ���ջ
	LinkStack s;
	initStack(&s);
	Node* node = root;

	while (node != NULL || !isEmpty(&s)) {
		while (node != NULL) {
			push(&s, node);
			node = node->left;
		}
		if (getTopIsVisit(&s) == 0) {
			//��һ�η��ʣ���ת���ҽ���
			setTopIsVisit(&s, 1);
			node = s.top->node->right;
		}
		else {
			//�ڶ��η��ʣ�ȡ��ջ��Ԫ��
			node = pop(&s);
			printf("%d ", node->data);
			node = NULL;
		}
	}
	printf("\n");
}




//��ʼ������
void initQueue(Queue* q) {
	q->front = NULL;
	q->rear = NULL;
}

//�ж϶����Ƿ�Ϊ��
bool isQueueEmpty(Queue* q) {
	return q->front == NULL;
}

//���
void enqueue(Queue* q, Node* node) {
	QueueNode* newQueueNode = (QueueNode*)malloc(sizeof(QueueNode));
	if (newQueueNode == NULL) {
		printf("�ڴ����ʧ��\n");
		return;
	}
	//������
	newQueueNode->node = node;
	newQueueNode->next = NULL;

	//���
	if (isQueueEmpty(q)) {
		q->front = q->rear = newQueueNode;
	}
	else {
		q->rear->next = newQueueNode;
		q->rear = newQueueNode;
	}
}

//����
Node* dequeue(Queue* q) {
	if (isQueueEmpty(q)) {
		printf("�����������ݣ��޷�����\n");
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

//��α���
void levelorder(Node* root) {
	if (root == NULL) {
		printf("��������������\n");
		return;
	}

	//����һ������
	Queue q;
	initQueue(&q);

	//�����ڵ�����
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