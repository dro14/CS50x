#include <stdio.h>
#include <cs50.h>

bool valid_triangle(double a, double b, double c);


int main()
{
    double a = get_double("First side of the triangle: ");
    double b = get_double("Second side of the triangle: ");
    double c = get_double("Third side of the triangle: ");
    bool result = valid_triangle(a, b, c);

    if (result) {
        printf("The triangle is valid\n");
    } else {
        printf("The triangle is not valid\n");
    }
}


bool valid_triangle(double a, double b, double c)
{
    if (a > 0 && b > 0 && c > 0)
        if (a + b > c && b + c > a && a + c > b)
            return true;

    return false;
}