#include "QueueImpl.h"
#include "StackImpl.h"
#include <iostream>

int main(int argc, char const *argv[])
{
    std::cout << "hello world" << std::endl;

    Stack<uint32_t> stk;
    stk.push(1);
    stk.push(2);
    stk.push(3);
    stk.push(4);

    stk.peek();

    stk.pop();
    stk.pop();
    stk.pop();
    stk.pop();
    return 0;
}
