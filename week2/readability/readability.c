#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

// Prototypes of the functions
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);


int main(void)
{
    // Prompt the user to input a text
    string text = get_string("Text: ");

    // Counting letters, words and sentences
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    // Calculating the averages and the index
    double L = 100.0 * letters / words;
    double S = 100.0 * sentences / words;
    double index = 0.0588 * L - 0.296 * S - 15.8;

    // Rounding the index to the nearest integer
    int grade = round(index);

    // Printing the result
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 15)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}


// Function for counting letters
int count_letters(string text)
{
    int letters = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isupper(text[i]) || islower(text[i]))
        {
            letters++;
        }
    }

    return letters;
}


// Function for counting words
int count_words(string text)
{
    int words = 1;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == ' ' && text[i + 1] != ' ')
        {
            words++;
        }
    }

    return words;
}


// Function for counting sentences
int count_sentences(string text)
{
    int sentences = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }

    return sentences;
}