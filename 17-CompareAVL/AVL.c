#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "AVL.h"

int compareCount = 0; // �� ���� Ƚ���� �����ϴ� ���� ����
int searchCount = 0;  // Ž�� ���� Ƚ���� �����ϴ� ���� ����

// ���ο� ��带 �����ϴ� �Լ�
Node* createNode(int key) {
    Node* nptr = (Node*)malloc(sizeof(Node));
    nptr->key = key;            // ����� Ű ��
    nptr->right = nptr->left = NULL; // �ڽ� ��� �ʱ�ȭ
    nptr->height = 1;           // �ʱ� ���� ����
    return nptr;
}

// ����� ���̸� ��ȯ�ϴ� �Լ�
int getHeight(Node* nptr) {
    if (nptr == NULL) return 0; // NULL ����� ���̴� 0
    else return nptr->height;  // �׷��� ������ �ش� ����� ���� ��ȯ
}

// ����� ���� ����� ����ϴ� �Լ�
int getBalance(Node* nptr) {
    return getHeight(nptr->left) - getHeight(nptr->right); // ���ʰ� ������ ����Ʈ�� ���� ����
}

// ���������� ȸ���ϴ� �Լ� (LL ȸ��)
Node* rotateRight(Node* y) {
    Node* x = y->left;          // ���ο� ��Ʈ ���
    Node* T3 = x->right;        // ���ġ�� ����Ʈ��

    x->right = y;               // ������ ����Ʈ�� ����
    y->left = T3;               // ���ġ�� ����Ʈ�� ����

    // ���� ����
    y->height = 1 + ((getHeight(y->left) > getHeight(y->right))
        ? getHeight(y->left)
        : getHeight(y->right));
    x->height = 1 + ((getHeight(x->left) > getHeight(x->right))
        ? getHeight(x->left)
        : getHeight(x->right));

    return x;                   // ���ο� ��Ʈ ��ȯ
}

// �������� ȸ���ϴ� �Լ� (RR ȸ��)
Node* rotateLeft(Node* y) {
    Node* x = y->right;         // ���ο� ��Ʈ ���
    Node* T2 = x->left;         // ���ġ�� ����Ʈ��

    x->left = y;                // ���� ����Ʈ�� ����
    y->right = T2;              // ���ġ�� ����Ʈ�� ����

    // ���� ����
    y->height = 1 + ((getHeight(y->left) > getHeight(y->right))
        ? getHeight(y->left)
        : getHeight(y->right));
    x->height = 1 + ((getHeight(x->left) > getHeight(x->right))
        ? getHeight(x->left)
        : getHeight(x->right));

    return x;                   // ���ο� ��Ʈ ��ȯ
}

// ���� ��ȸ�� Ʈ���� ����ϴ� �Լ�
void inOrder(Node* root) {
    if (root->left != NULL) inOrder(root->left); // ���� ����Ʈ�� ��ȸ
    printf("%2d[%d] ", root->key, root->height); // ���� ��� ���
    if (root->right != NULL) inOrder(root->right); // ������ ����Ʈ�� ��ȸ
}

// AVL Ʈ���� ��带 �����ϴ� �Լ�
Node* insertNode(Node* root, int key) {
    if (root == NULL) return createNode(key); // �� ��� ����

    if (root->key > key)                      // ���� Ű�� ���� Ű���� ������
        root->left = insertNode(root->left, key); // ���� ����Ʈ���� ����
    else if (root->key < key)                 // ���� Ű�� ���� Ű���� ũ��
        root->right = insertNode(root->right, key); // ������ ����Ʈ���� ����
    else
        return root;                          // Ű�� �ߺ��Ǹ� �ƹ� �۾��� ���� ����

    // ���� ����
    root->height = 1 + ((getHeight(root->left) > getHeight(root->right))
        ? getHeight(root->left)
        : getHeight(root->right));

    // ���� ��� ���
    int balance = getBalance(root);

    // �ұ����� �߻��� ��� ȸ�� ����
    if (balance >= 2) { // LL �Ǵ� LR
        if (getBalance(root->left) >= 0) return rotateRight(root); // LL
        else { // LR
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
    }
    else if (balance <= -2) { // RR �Ǵ� RL
        if (getBalance(root->right) < 0) return rotateLeft(root); // RR
        else { // RL
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
    }

    return root; // ������ �´� ��� �״�� ��ȯ
}

// �ּҰ� ��带 ã�� �Լ�
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != NULL) // ���� ���� ��尡 �ּҰ�
        current = current->left;
    return current;
}

// AVL Ʈ������ ��带 �����ϴ� �Լ�
Node* deleteNode(Node* root, int key) {
    if (root == NULL) return root; // ��尡 ������ ��ȯ

    if (key < root->key)                  // ���� Ű�� ������ ���� ����Ʈ��
        root->left = deleteNode(root->left, key);
    else if (key > root->key)             // ���� Ű�� ũ�� ������ ����Ʈ��
        root->right = deleteNode(root->right, key);
    else {                                // ���� Ű�� ���� ���� ������
        if ((root->left == NULL) || (root->right == NULL)) { // �ڽ��� �ϳ� ����
            Node* temp = root->left ? root->left : root->right;
            if (temp == NULL) {          // �ڽ��� ���� ���
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;           // �ڽ��� �ϳ��� ��� ��ü
            free(temp);                  // �޸� ����
        }
        else {                           // �ڽ��� ���� ���
            Node* temp = minValueNode(root->right); // ������ ����Ʈ�� �ּҰ�
            root->key = temp->key;      // Ű�� ����
            root->right = deleteNode(root->right, temp->key); // ����� Ű ����
        }
    }

    if (root == NULL) return root;       // ��Ʈ�� NULL�̸� ��ȯ

    // ���� ����
    root->height = 1 + ((getHeight(root->left) > getHeight(root->right))
        ? getHeight(root->left)
        : getHeight(root->right));

    // ���� ��� ��� �� ȸ�� ����
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0) // LL
        return rotateRight(root);
    if (balance > 1 && getBalance(root->left) < 0) { // LR
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0) // RR
        return rotateLeft(root);
    if (balance < -1 && getBalance(root->right) > 0) { // RL
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root; // ���� ���� ����
}

// ��带 Ž���ϴ� �Լ�
Node* searchNode(Node* root, int key) {
    compareCount++; // �� Ƚ�� ����
    if (root == NULL || root->key == key) {
        return root; // ��带 ã�Ұų� NULL ��ȯ
    }
    compareCount++;
    if (root->key < key) // Ű�� ũ�� ������ Ž��
        return searchNode(root->right, key);
    return searchNode(root->left, key); // Ű�� ������ ���� Ž��
}

// Ʈ�� �޸𸮸� �����ϴ� �Լ�
void freeTree(Node* root) {
    if (root != NULL) {
        freeTree(root->left);  // ���� ����Ʈ�� ����
        freeTree(root->right); // ������ ����Ʈ�� ����
        free(root);            // ���� ��� ����
    }
}

// AVL Ʈ������ 2000���� ������ �����ϴ� �Լ�
void doAVLBatch(Node* root) {
    for (int i = 0; i < 2000; i++) {
        int A = rand() % 3; // ���� ���� (����, ����, Ž��) ����
        int B = rand() % 1000; // Ű ��
        if (A == 0) {
            root = insertNode(root, B); // ����
        }
        else if (A == 1) {
            root = deleteNode(root, B); // ����
        }
        else if (A == 2) {
            searchNode(root, B);       // Ž��
            searchCount++;
        }
    }
}

// �Ϲ� ���� Ž�� Ʈ������ 2000���� ������ �����ϴ� �Լ�
void doBinaryBatch(Node* root) {
    for (int i = 0; i < 2000; i++) {
        int A = rand() % 3; // ���� ���� (����, ����, Ž��) ����
        int B = rand() % 1000; // Ű ��
        if (A == 0) {
            root = insertNode(root, B); // ����
        }
        else if (A == 1) {
            root = deleteNode(root, B); // ����
        }
        else if (A == 2) {
            searchNode(root, B);       // Ž��
            searchCount++;
        }
    }
}
