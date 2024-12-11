#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "AVL.h"

int compareCount = 0; // 비교 연산 횟수를 저장하는 전역 변수
int searchCount = 0;  // 탐색 연산 횟수를 저장하는 전역 변수

// 새로운 노드를 생성하는 함수
Node* createNode(int key) {
    Node* nptr = (Node*)malloc(sizeof(Node));
    nptr->key = key;            // 노드의 키 값
    nptr->right = nptr->left = NULL; // 자식 노드 초기화
    nptr->height = 1;           // 초기 높이 설정
    return nptr;
}

// 노드의 높이를 반환하는 함수
int getHeight(Node* nptr) {
    if (nptr == NULL) return 0; // NULL 노드의 높이는 0
    else return nptr->height;  // 그렇지 않으면 해당 노드의 높이 반환
}

// 노드의 균형 계수를 계산하는 함수
int getBalance(Node* nptr) {
    return getHeight(nptr->left) - getHeight(nptr->right); // 왼쪽과 오른쪽 서브트리 높이 차이
}

// 오른쪽으로 회전하는 함수 (LL 회전)
Node* rotateRight(Node* y) {
    Node* x = y->left;          // 새로운 루트 노드
    Node* T3 = x->right;        // 재배치될 서브트리

    x->right = y;               // 오른쪽 서브트리 연결
    y->left = T3;               // 재배치된 서브트리 연결

    // 높이 갱신
    y->height = 1 + ((getHeight(y->left) > getHeight(y->right))
        ? getHeight(y->left)
        : getHeight(y->right));
    x->height = 1 + ((getHeight(x->left) > getHeight(x->right))
        ? getHeight(x->left)
        : getHeight(x->right));

    return x;                   // 새로운 루트 반환
}

// 왼쪽으로 회전하는 함수 (RR 회전)
Node* rotateLeft(Node* y) {
    Node* x = y->right;         // 새로운 루트 노드
    Node* T2 = x->left;         // 재배치될 서브트리

    x->left = y;                // 왼쪽 서브트리 연결
    y->right = T2;              // 재배치된 서브트리 연결

    // 높이 갱신
    y->height = 1 + ((getHeight(y->left) > getHeight(y->right))
        ? getHeight(y->left)
        : getHeight(y->right));
    x->height = 1 + ((getHeight(x->left) > getHeight(x->right))
        ? getHeight(x->left)
        : getHeight(x->right));

    return x;                   // 새로운 루트 반환
}

// 중위 순회로 트리를 출력하는 함수
void inOrder(Node* root) {
    if (root->left != NULL) inOrder(root->left); // 왼쪽 서브트리 순회
    printf("%2d[%d] ", root->key, root->height); // 현재 노드 출력
    if (root->right != NULL) inOrder(root->right); // 오른쪽 서브트리 순회
}

// AVL 트리에 노드를 삽입하는 함수
Node* insertNode(Node* root, int key) {
    if (root == NULL) return createNode(key); // 새 노드 생성

    if (root->key > key)                      // 삽입 키가 현재 키보다 작으면
        root->left = insertNode(root->left, key); // 왼쪽 서브트리에 삽입
    else if (root->key < key)                 // 삽입 키가 현재 키보다 크면
        root->right = insertNode(root->right, key); // 오른쪽 서브트리에 삽입
    else
        return root;                          // 키가 중복되면 아무 작업도 하지 않음

    // 높이 갱신
    root->height = 1 + ((getHeight(root->left) > getHeight(root->right))
        ? getHeight(root->left)
        : getHeight(root->right));

    // 균형 계수 계산
    int balance = getBalance(root);

    // 불균형이 발생한 경우 회전 수행
    if (balance >= 2) { // LL 또는 LR
        if (getBalance(root->left) >= 0) return rotateRight(root); // LL
        else { // LR
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
    }
    else if (balance <= -2) { // RR 또는 RL
        if (getBalance(root->right) < 0) return rotateLeft(root); // RR
        else { // RL
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
    }

    return root; // 균형이 맞는 경우 그대로 반환
}

// 최소값 노드를 찾는 함수
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != NULL) // 가장 왼쪽 노드가 최소값
        current = current->left;
    return current;
}

// AVL 트리에서 노드를 삭제하는 함수
Node* deleteNode(Node* root, int key) {
    if (root == NULL) return root; // 노드가 없으면 반환

    if (key < root->key)                  // 삭제 키가 작으면 왼쪽 서브트리
        root->left = deleteNode(root->left, key);
    else if (key > root->key)             // 삭제 키가 크면 오른쪽 서브트리
        root->right = deleteNode(root->right, key);
    else {                                // 삭제 키가 현재 노드와 같으면
        if ((root->left == NULL) || (root->right == NULL)) { // 자식이 하나 이하
            Node* temp = root->left ? root->left : root->right;
            if (temp == NULL) {          // 자식이 없는 경우
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;           // 자식이 하나인 경우 대체
            free(temp);                  // 메모리 해제
        }
        else {                           // 자식이 둘인 경우
            Node* temp = minValueNode(root->right); // 오른쪽 서브트리 최소값
            root->key = temp->key;      // 키를 복사
            root->right = deleteNode(root->right, temp->key); // 복사된 키 삭제
        }
    }

    if (root == NULL) return root;       // 루트가 NULL이면 반환

    // 높이 갱신
    root->height = 1 + ((getHeight(root->left) > getHeight(root->right))
        ? getHeight(root->left)
        : getHeight(root->right));

    // 균형 계수 계산 및 회전 수행
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

    return root; // 균형 유지 상태
}

// 노드를 탐색하는 함수
Node* searchNode(Node* root, int key) {
    compareCount++; // 비교 횟수 증가
    if (root == NULL || root->key == key) {
        return root; // 노드를 찾았거나 NULL 반환
    }
    compareCount++;
    if (root->key < key) // 키가 크면 오른쪽 탐색
        return searchNode(root->right, key);
    return searchNode(root->left, key); // 키가 작으면 왼쪽 탐색
}

// 트리 메모리를 해제하는 함수
void freeTree(Node* root) {
    if (root != NULL) {
        freeTree(root->left);  // 왼쪽 서브트리 해제
        freeTree(root->right); // 오른쪽 서브트리 해제
        free(root);            // 현재 노드 해제
    }
}

// AVL 트리에서 2000개의 연산을 수행하는 함수
void doAVLBatch(Node* root) {
    for (int i = 0; i < 2000; i++) {
        int A = rand() % 3; // 연산 종류 (삽입, 삭제, 탐색) 결정
        int B = rand() % 1000; // 키 값
        if (A == 0) {
            root = insertNode(root, B); // 삽입
        }
        else if (A == 1) {
            root = deleteNode(root, B); // 삭제
        }
        else if (A == 2) {
            searchNode(root, B);       // 탐색
            searchCount++;
        }
    }
}

// 일반 이진 탐색 트리에서 2000개의 연산을 수행하는 함수
void doBinaryBatch(Node* root) {
    for (int i = 0; i < 2000; i++) {
        int A = rand() % 3; // 연산 종류 (삽입, 삭제, 탐색) 결정
        int B = rand() % 1000; // 키 값
        if (A == 0) {
            root = insertNode(root, B); // 삽입
        }
        else if (A == 1) {
            root = deleteNode(root, B); // 삭제
        }
        else if (A == 2) {
            searchNode(root, B);       // 탐색
            searchCount++;
        }
    }
}
