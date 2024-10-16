#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define STACK_SIZE 100

typedef struct {
    char data[STACK_SIZE];
    int top;
} Stack;

//初始化栈
void initStack(Stack* s) {
    s->top = -1;
}

//判断是否为空
bool isEmpty(Stack* s) {
    return s->top == -1;
}

//判断是否已满
bool isFull(Stack* s) {
    return s->top == STACK_SIZE - 1;
}

//添加数值

void push(Stack* s, char item) {
    if (isFull(s)) {
        printf("已无位置可存\n");
    }
    else {
        s->data[++s->top] = item;
    }
}

//输出数值
char pop(Stack* s) {

    if (isEmpty(s)) {
        printf("该栈为空，没有元素\n");
        return '\0';
    }
    else {
        return s->data[s->top--];
    }
}

//插入数值
void insertChar(Stack* textStack, Stack* historyStack, char c) {
        push(historyStack, 'i');  // 'i' 代表插入
        push(textStack, c);
}

//删除数值
void deleteChar(Stack* textStack, Stack* historyStack) {
    if (isEmpty(textStack)!=-1) {
        push(historyStack, 'd');  // 'd' 代表删除
        pop(textStack);
    }
}

//撤销操作
void undo(Stack* textStack, Stack* historyStack) {
    if (!isEmpty(historyStack)) {
        char lastOperation = pop(historyStack);
       
        if (lastOperation == 'i') {
            pop(textStack);  // 使栈的最后一个值被推出
        }
        else if (lastOperation == 'd') {
            char lastChar = pop(textStack);
            push(historyStack, 'i');  // 将“插入”来替代原先的“删除”——即撤回某一操作
            push(textStack, lastChar);  // 将刚才删除的值重新推入
           
        }
    }
}

//示例函数
void testEditor() {
    Stack textStack, historyStack;
    initStack(&textStack);
    initStack(&historyStack);
    

    insertChar(&textStack, &historyStack, 'a');
    insertChar(&textStack, &historyStack, 'b');
    insertChar(&textStack, &historyStack, 'c');
    deleteChar(&textStack, &historyStack);  //d
    undo(&textStack, &historyStack);   //用i代替d
    undo(&textStack, &historyStack);    //撤回 i

    printf("结果字符串：");
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

//测试
int main() {
    testEditor();
    return 0;
}