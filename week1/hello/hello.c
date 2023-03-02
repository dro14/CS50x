#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Prompt the user to enter hir/her name
    string name = get_string("What's your name?\n");

    // Print greeting with the given name
    printf("hello, %s\n", name);
}