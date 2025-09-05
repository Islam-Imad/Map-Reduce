import math
import random

si = lambda: input()
ii = lambda: int(input())
mi = lambda: map(int, input().split())
li = lambda: list(mi())


def write_to_file(filename, content):
    with open(filename, "w") as f:
        f.write(content)


def generate_random_intList(n, smallest, largest):
    return [random.randint(smallest, largest) for _ in range(n)]


def generate_random_string(length):
    letters = "abcdefghijklmnopqrstuvwxyz"
    return "".join(random.choice(letters) for _ in range(length))


def generate_random_word_list(num_words, max_word_length):
    return [
        generate_random_string(random.randint(1, max_word_length))
        for _ in range(num_words)
    ]


def generate_word_count_tests(
    num_files, max_words_per_file, max_word_length, directory
):
    for file_index in range(num_files):
        num_words = random.randint(1, max_words_per_file)
        words = generate_random_word_list(num_words, max_word_length)
        file_name = f"{directory}/random_word_count_{file_index + 1}.txt"
        write_to_file(file_name, "\n".join(words))


def solve():
    generate_word_count_tests(5, 100, 10, "./samples")


def main():
    t = 1
    # t = ii()
    for _ in range(t):
        solve()


main()
