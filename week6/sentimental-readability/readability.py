from cs50 import get_string


def main():
    # Prompt the user to input a text
    text = get_string('Text: ')

    # Counting letters, words and sentences
    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)

    # Calculating the averages and the index
    L = letters / words * 100
    S = sentences / words * 100
    index = 0.0588 * L - 0.296 * S - 15.8

    # Rounding the index to the nearest integer
    grade = round(index)

    # Printing the result
    if grade < 1:
        print('Before Grade 1')
    elif grade > 15:
        print('Grade 16+')
    else:
        print(f'Grade {grade}')


# Function for counting letters
def count_letters(text):
    letters = 0
    length = len(text)
    for i in range(length):
        if text[i].isalpha():
            letters += 1
    return letters


# Function for counting words
def count_words(text):
    words = 1
    length = len(text)
    for i in range(length):
        if text[i] == ' ' and text[i + 1] != ' ':
            words += 1
    return words


# Function for counting sentences
def count_sentences(text):
    sentences = 0
    length = len(text)
    for i in range(length):
        if text[i] == '.' or text[i] == '!' or text[i] == '?':
            sentences += 1
    return sentences


if __name__ == '__main__':
    main()