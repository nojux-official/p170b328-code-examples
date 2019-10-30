import random


LIST_SIZE = 50


def get_random_list(list_size):
    return [random.randint(0, 100) for _ in range(list_size)]


if __name__ == '__main__':
    vector1 = get_random_list(LIST_SIZE)
    vector2 = get_random_list(LIST_SIZE)
    sum_vector = [x + y for x, y in zip(vector1, vector2)]
    print(sum_vector)
