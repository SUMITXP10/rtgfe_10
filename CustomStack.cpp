#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *stack;
    int *inc;   // To store increment values for each element in the stack.
    int maxSize;
    int top;
} CustomStack;

CustomStack* customStackCreate(int maxSize) {
    CustomStack* obj = (CustomStack*)malloc(sizeof(CustomStack));
    obj->stack = (int*)malloc(maxSize * sizeof(int));
    obj->inc = (int*)calloc(maxSize, sizeof(int));  // Initialize increments to 0.
    obj->maxSize = maxSize;
    obj->top = -1;
    return obj;
}

void customStackPush(CustomStack* obj, int x) {
    if (obj->top < obj->maxSize - 1) {
        obj->top++;
        obj->stack[obj->top] = x;
    }
}

int customStackPop(CustomStack* obj) {
    if (obj->top == -1) {
        return -1;
    }
    
    int poppedValue = obj->stack[obj->top] + obj->inc[obj->top];
    
    if (obj->top > 0) {
        obj->inc[obj->top - 1] += obj->inc[obj->top];  // Pass the increment to the next lower element.
    }
    
    obj->inc[obj->top] = 0;  // Reset the increment for this element after popping.
    obj->top--;
    
    return poppedValue;
}

void customStackIncrement(CustomStack* obj, int k, int val) {
    int limit = (k < obj->top + 1) ? k : obj->top + 1;
    if (limit > 0) {
        obj->inc[limit - 1] += val;  // Increment the bottom k elements.
    }
}

void customStackFree(CustomStack* obj) {
    free(obj->stack);
    free(obj->inc);
    free(obj);
}

/**
 * Your CustomStack struct will be instantiated and called as such:
 * CustomStack* obj = customStackCreate(maxSize);
 * customStackPush(obj, x);
 * int param_2 = customStackPop(obj);
 * customStackIncrement(obj, k, val);
 * customStackFree(obj);
 */
