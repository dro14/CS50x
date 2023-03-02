from cs50 import get_int


def main():
    sum = 0

    # Prompt the user to input a card number
    card_number = get_int('Number: ')
    num = card_number

    # Calculate checksum
    i = 1
    while num / 10 != 0:
        # Processing digits at odd positions
        if i % 2 == 1:
            remainder_odd = num % 10
            remainder_last = remainder_odd
            sum += remainder_odd
            num = int(num / 10)
            i += 1
        # Processing digits at even positions
        elif i % 2 == 0:
            remainder_even = num % 10
            remainder_last = remainder_even
            sum += sum_of_digits(remainder_even * 2)
            num = int(num / 10)
            i += 1

    # Checking validity of checksum
    if sum % 10 == 0:
        # Checking for American Express
        if card_number > 1e14 and card_number < 1e15 and remainder_odd == 3 and remainder_even in [4, 7]:
            print('AMEX')
        # Checking for VISA
        elif card_number > 1e12 and card_number < 1e16 and remainder_last == 4:
            print('VISA')
        # Checking for MasterCard
        elif card_number > 1e15 and card_number < 1e16 and remainder_even == 5 and remainder_odd in [1, 2, 3, 4, 5]:
            print('MASTERCARD')
    else:
        print('INVALID')


# A function that finds the sum of the digits of a given number
def sum_of_digits(n):
    sum = 0
    while n / 10 != 0:
        sum += n % 10
        n = int(n / 10)
    return sum


if __name__ == '__main__':
    main()