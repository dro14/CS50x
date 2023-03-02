while True:
    try:
        height = int(input('Height: '))
    except ValueError:
        height = 0
    if height >= 1 and height <= 8:
        break

for i in range(height):
    print((height - i - 1) * ' ', end='')
    print((i + 1) * '#', end='')
    print()