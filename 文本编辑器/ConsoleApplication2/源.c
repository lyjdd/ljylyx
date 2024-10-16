#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define STACK_SIZE 100

typedef struct {
    char data[STACK_SIZE];
    int top;
} Stack;

//��ʼ��ջ
void initStack(Stack* s) {
    s->top = -1;
}

//�ж��Ƿ�Ϊ��
bool isEmpty(Stack* s) {
    return s->top == -1;
}

//�ж��Ƿ�����
bool isFull(Stack* s) {
    return s->top == STACK_SIZE - 1;
}

//�����ֵ

void push(Stack* s, char item) {
    if (isFull(s)) {
        printf("����λ�ÿɴ�\n");
    }
    else {
        s->data[++s->top] = item;
    }
}

//�����ֵ
char pop(Stack* s) {

    if (isEmpty(s)) {
        printf("��ջΪ�գ�û��Ԫ��\n");
        return '\0';
    }
    else {
        return s->data[s->top--];
    }
}

//������ֵ
void insertChar(Stack* textStack, Stack* historyStack, char c) {
        push(historyStack, 'i');  // 'i' �������
        push(textStack, c);
}

//ɾ����ֵ
void deleteChar(Stack* textStack, Stack* historyStack) {
    if (isEmpty(textStack)!=-1) {
        push(historyStack, 'd');  // 'd' ����ɾ��
        pop(textStack);
    }
}

//��������
void undo(Stack* textStack, Stack* historyStack) {
    if (!isEmpty(historyStack)) {
        char lastOperation = pop(historyStack);
       
        if (lastOperation == 'i') {
            pop(textStack);  // ʹջ�����һ��ֵ���Ƴ�
        }
        else if (lastOperation == 'd') {
            char lastChar = pop(textStack);
            push(historyStack, 'i');  // �������롱�����ԭ�ȵġ�ɾ��������������ĳһ����
            push(textStack, lastChar);  // ���ղ�ɾ����ֵ��������
           
        }
    }
}

//ʾ������
void testEditor() {
    Stack textStack, historyStack;
    initStack(&textStack);
    initStack(&historyStack);
    

    insertChar(&textStack, &historyStack, 'a');
    insertChar(&textStack, &historyStack, 'b');
    insertChar(&textStack, &historyStack, 'c');
    deleteChar(&textStack, &historyStack);  //d
    undo(&textStack, &historyStack);   //��i����d
    undo(&textStack, &historyStack);    //���� i

    printf("����ַ�����");
    for (int i = 0; i <= textStack.top+1; i++) {
        printf("%c", textStack.data[i]);
    }
    printf("\n");
    for (int i = 0; i < historyStack.top+1; i++)
    {
        printf("%c", historyStack.data[i]);
        printf("\n");
    }
}

//����
int main() {
    testEditor();
    return 0;
}