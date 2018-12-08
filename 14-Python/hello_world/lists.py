def main():
    a = [98, 93, 77, 82, 83]
    a_sum = 0
    for value in a:
        a_sum += value
    print(a_sum / len(a))
    # alternative
    a_sum2 = sum(a)
    print(a_sum2 / len(a))


if __name__ == '__main__':
    main()
