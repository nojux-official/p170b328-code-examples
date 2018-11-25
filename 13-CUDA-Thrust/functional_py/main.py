import functools


def get_vector():
    return range(1, 21)


def main():
    vector = get_vector()
    # filter only even numbers
    even = (number for number in vector if number % 2 == 0)
    # map to squares
    squares = (number * number for number in even)
    # reduce to sum
    result = functools.reduce(lambda acc, x: acc + x, squares, 0)
    print(result)


if __name__ == '__main__':
    main()

