#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// Prototypes of the functions
bool only_letters(string text);
string to_uppercase(string text);
char substitute(char c, string key);
string cipher(string plaintext, string key);


int main(int argc, string argv[])
{

// Checking for the valid number of arguments
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key = argv[1];       // VcHpRzGjNtLsKfBdQwAxEuYmOi
    key = to_uppercase(key);
    int n = strlen(key);
    int num_occur[26] = {0};

// Checking the length of the key and whether it consists of only letters
    if (n != 26 || !only_letters(key))
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }



// Checking for multiple occurences of letters
    // Counting occurences of each letter
    for (int i = 0; i < n; i++)
    {
        num_occur[key[i] - 65]++;
    }

    // Checking whether each letter occures exactly once
    for (int i = 0; i < 26; i++)
    {
        if (num_occur[i] > 1)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
    }


    // Prompting the user to input a text
    string plaintext = get_string("plaintext:  ");

    // Ciphering the text
    string ciphertext = cipher(plaintext, key);

    // Printing the ciphertext
    printf("ciphertext: %s\n", ciphertext);


    return 0;
}


// Function that checks whether the given string consists of only letters or not
bool only_letters(string text)
{
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (!isupper(text[i]) && !islower(text[i]))
        {
            return false;
        }
    }

    return true;
}


string to_uppercase(string text)
{
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        text[i] = toupper(text[i]);
    }

    return text;
}


// Function that substitutes a letter
char substitute(char c, string key)
{
    if (islower(c))
    {
        c = toupper(c);
        c = key[c - 65];
        c = tolower(c);
    }
    else if (isupper(c))
    {
        c = key[c - 65];
    }

    return c;
}


// Function that ciphers a text
string cipher(string plaintext, string key)
{
    string ciphertext = plaintext;

    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        ciphertext[i] = substitute(plaintext[i], key);
    }

    return ciphertext;
}