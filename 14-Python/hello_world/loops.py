def get_fibonacci_number_at_index(index):
    a, b = 0, 1
    current_index = 0
    while current_index < index:
        a, b = b, a + b
        current_index += 1
    return a


def main():
    tenth_fibonacci_number = get_fibonacci_number_at_index(index=10)
    print("10th Fibonacci number is", tenth_fibonacci_number)


if __name__ == '__main__':
    main()
