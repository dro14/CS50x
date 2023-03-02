#include <cs50.h>
#include <stdio.h>

void print_hash(int n);
void print_space(int n);

int main(void)
{
    // Input an integer only between 1 and 8
    int n = 0;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

    // Building the pyramid
    for (int i = 1; i <= n; i++)
    {
        print_space(n - i);
        print_hash(i);
        printf("\n");
    }
}


// A function that prints multiple hashes
void print_hash(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("#");
    }
}

// A function that prints multiple whilespaces
void print_space(int n)
{
    for (int i = 0; i < n; i++)
    {
        printf(" ");
    }
}