#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// Prototypes of the functions
bool only_digits(string str);
char rotate(char c, int n);
string cipher(string plaintext, int n);


int main(int argc, string argv[])
{
    // Checking for the validity of the key
    if (argc != 2 || !only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Converting the key from string to int
    int key = atoi(argv[1]);

    // Prompting the user to input a text
    string plaintext = get_string("plaintext:  ");

    // Ciphering the text
    string ciphertext = cipher(plaintext, key);

    // Printing the ciphertext
    printf("ciphertext: %s\n", ciphertext);


    return 0;
}


// Function that checks whether the given string consists of only digits or not
bool only_digits(string str)
{
    for (int i = 0, n = strlen(str); i < n; i++)
    {
        if (!isdigit(str[i]))
        {
            return false;
        }
    }

    return true;
}


// Function that ciphers a letter
char rotate(char c, int n)
{
    if (isupper(c))
    {
        return (((c - 65) + n) % 26) + 65;
    }
    else if (islower(c))
    {
        return (((c - 97) + n) % 26) + 97;
    }
    else
    {
        return c;
    }
}

// Function that ciphers a text
string cipher(string plaintext, int key)
{
    string ciphertext = plaintext;

    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        ciphertext[i] = rotate(plaintext[i], key);
    }

    return ciphertext;
}