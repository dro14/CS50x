from cs50 import get_float


def main():
    # Ask how many dollars the customer is owed
    cents = get_cents()

    # Calculate the number of quarters to give the customer
    quarters = calculate_quarters(cents)
    cents -= quarters * 25

    # Calculate the number of dimes to give the customer
    dimes = calculate_dimes(cents)
    cents -= dimes * 10

    # Calculate the number of nickels to give the customer
    nickels = calculate_nickels(cents)
    cents -= nickels * 5

    # Calculate the number of pennies to give the customer
    pennies = calculate_pennies(cents)
    cents -= pennies * 1

    # Sum coins
    coins = quarters + dimes + nickels + pennies

    # Print total number of coins to give the customer
    print(coins)


def get_cents():
    while True:
        cash = get_float('Change owed: ')
        if cash >= 0:
            break
    return int(cash * 100)


def calculate_quarters(cents):
    return int(cents / 25)


def calculate_dimes(cents):
    return int(cents / 10)


def calculate_nickels(cents):
    return int(cents / 5)


def calculate_pennies(cents):
    return int(cents / 1)


if __name__ == '__main__':
    main()