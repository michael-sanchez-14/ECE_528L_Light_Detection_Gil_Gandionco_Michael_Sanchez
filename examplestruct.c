#include <stdio.h>

struct example
{
    int num1;
    int num2;
};

int main()
{
    struct example nums = {12345,67890};
    printf("num1 = %d\n", nums.num1);
    printf("num2 = %d\n", nums.num2);
    return 0;
}