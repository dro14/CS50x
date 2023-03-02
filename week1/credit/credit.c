#include <cs50.h>
#include <stdio.h>

int sumOfDigits(int n);



int main(void)
{
    int sum = 0;
    int remainder_last = 0;
    int remainder_odd = 0;
    int remainder_even = 0;

    // Prompt the user to input a card number
    const long card_number = get_long("Number: ");
    long num = card_number;


    // Calculate checksum
    for (int i = 1; num / 10.0 != 0; i++)
    {
        // Processing digits at odd positions
        if (i % 2 == 1)
        {
            remainder_odd = num % 10;
            remainder_last = remainder_odd;
            sum += remainder_odd;
            num /= 10;
        }
        // Processing digits at even positions
        else if (i % 2 == 0)
        {
            remainder_even = num % 10;
            remainder_last = remainder_even;
            sum += sumOfDigits(remainder_even * 2);
            num /= 10;
        }
    }

    // Checking validity via checksum
    if (sum % 10 != 0)
    {
        printf("INVALID\n");
    }
    // Checking for American Express
    else if (card_number > (long) 1e14 && card_number < (long) 1e15 && remainder_odd == 3 &&
             (
                 remainder_even == 4 ||
                 remainder_even == 7
             )
            )
    {
        printf("AMEX\n");
    }
    // Checking for VISA
    else if (card_number > (long) 1e12 && card_number < (long) 1e16 && remainder_last == 4)
    {
        printf("VISA\n");
    }
    // Checking for MasterCard
    else if (card_number > (long) 1e15 && card_number < (long) 1e16 && remainder_even == 5 &&
             (
                 remainder_odd == 1 ||
                 remainder_odd == 2 ||
                 remainder_odd == 3 ||
                 remainder_odd == 4 ||
                 remainder_odd == 5
             )
            )
    {
        printf("MASTERCARD\n");
    }
    else
    {
        printf("INVALID\n");
    }
}



// A function that finds the sum of the digits of a given number
int sumOfDigits(int n)
{
    int sum = 0;

    while (n / 10.0 != 0)
    {
        sum += n % 10;
        n /= 10;
    }

    return sum;
}