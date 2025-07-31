#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100

typedef struct HistoryNode {
    char url[MAX_LEN];
    char timestamp[MAX_LEN];
    struct HistoryNode* prev;
    struct HistoryNode* next;
} HistoryNode;

typedef struct StackNode {
    char url[MAX_LEN];
    char timestamp[MAX_LEN];
    struct StackNode* next;
} StackNode;

StackNode* backStack = NULL;
StackNode* forwardStack = NULL;
char currentUrl[MAX_LEN] = "";
char currentTimestamp[MAX_LEN] = "";
HistoryNode* historyHead = NULL;
HistoryNode* historyTail = NULL;

void push(StackNode** top, const char* url, const char* timestamp) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    strcpy(newNode->url, url);
    strcpy(newNode->timestamp, timestamp);
    newNode->next = *top;
    *top = newNode;
}

int isEmpty(StackNode* top) {
    return top == NULL;
}

void pop(StackNode** top, char* url, char* timestamp) {
    if (*top == NULL) return;
    StackNode* temp = *top;
    strcpy(url, temp->url);
    strcpy(timestamp, temp->timestamp);
    *top = temp->next;
    free(temp);
}

void clearStack(StackNode** top) {
    char u[MAX_LEN], t[MAX_LEN];
    while (!isEmpty(*top)) {
        pop(top, u, t);
    }
}

void addHistory(const char* url, const char* timestamp) {
    HistoryNode* newNode = (HistoryNode*)malloc(sizeof(HistoryNode));
    strcpy(newNode->url, url);
    strcpy(newNode->timestamp, timestamp);
    newNode->prev = historyTail;
    newNode->next = NULL;
    if (historyTail != NULL) historyTail->next = newNode;
    else historyHead = newNode;
    historyTail = newNode;
}

void showHistory() {
    if (historyHead == NULL) {
        printf("Khong co lich su duyet web.\n");
        return;
    }
    printf("Lich su duyet web:\n");
    HistoryNode* temp = historyHead;
    while (temp != NULL) {
        printf("URL: %s | Thoi gian: %s\n", temp->url, temp->timestamp);
        temp = temp->next;
    }
}

void clearHistory() {
    HistoryNode* temp = historyHead;
    while (temp != NULL) {
        HistoryNode* toDelete = temp;
        temp = temp->next;
        free(toDelete);
    }
    historyHead = historyTail = NULL;
}

void visitWebsite() {
    char url[MAX_LEN], timestamp[MAX_LEN];
    printf("Nhap URL: ");
    scanf(" %[^\n]", url);
    printf("Nhap thoi gian: ");
    scanf(" %[^\n]", timestamp);

    if (strlen(currentUrl) > 0) {
        push(&backStack, currentUrl, currentTimestamp);
    }

    strcpy(currentUrl, url);
    strcpy(currentTimestamp, timestamp);
    addHistory(url, timestamp);
    clearStack(&forwardStack);
    printf("Da truy cap: %s\n", url);
}

void goBackward() {
    if (isEmpty(backStack)) {
        printf("Khong the BACK.\n");
        return;
    }
    push(&forwardStack, currentUrl, currentTimestamp);
    pop(&backStack, currentUrl, currentTimestamp);
    printf("Back den trang: %s\n", currentUrl);
}

void goForward() {
    if (isEmpty(forwardStack)) {
        printf("Khong the FORWARD.\n");
        return;
    }
    push(&backStack, currentUrl, currentTimestamp);
    pop(&forwardStack, currentUrl, currentTimestamp);
    printf("Forward den trang: %s\n", currentUrl);
}

void showCurrent() {
    if (strlen(currentUrl) == 0) {
        printf("Chua co trang nao duoc truy cap.\n");
    } else {
        printf("Trang hien tai: %s | Thoi gian: %s\n", currentUrl, currentTimestamp);
    }
}

void exitProgram() {
    clearStack(&backStack);
    clearStack(&forwardStack);
    clearHistory();
    printf("Thoat chuong trinh.\n");
}

void showMenu() {
    printf("\n------ MENU ------\n");
    printf("1. VISIT\n");
    printf("2. BACKWARD\n");
    printf("3. FORWARD\n");
    printf("4. CURRENT\n");
    printf("5. HISTORY\n");
    printf("6. CLEAR HISTORY\n");
    printf("7. THOAT\n");
    printf("Chon: ");
}

int main() {
    int choice;
    do {
        showMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 1: visitWebsite(); break;
            case 2: goBackward(); break;
            case 3: goForward(); break;
            case 4: showCurrent(); break;
            case 5: showHistory(); break;
            case 6: clearHistory(); printf("Da xoa lich su.\n"); break;
            case 7: exitProgram(); break;
            default: printf("Lua chon khong hop le.\n");
        }
    } while (choice != 7);
    return 0;
}
