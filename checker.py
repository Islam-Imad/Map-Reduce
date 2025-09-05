import math
import sys

si = lambda: input()
ii = lambda: int(input())
mi = lambda: map(int, input().split())
li = lambda: list(mi())


def sort_and_cmp_tokens(correct_file, user_file):
    try:
        with open(correct_file, "r") as f:
            correct_tokens = f.read().strip().split()
        with open(user_file, "r") as f:
            user_tokens = f.read().strip().split()
        correct_tokens.sort()
        user_tokens.sort()
        return correct_tokens == user_tokens
    except FileNotFoundError as e:
        print(f"Error: File not found - {e}")
        return False
    except Exception as e:
        print(f"Error: {e}")
        return False


def solve():
    if len(sys.argv) != 3:
        print("Usage: python3 checker.py <correct_file> <user_file>")
        return False
    
    correct_file = sys.argv[1]
    user_file = sys.argv[2]
    
    if sort_and_cmp_tokens(correct_file, user_file):
        print("Output is correct.")
        return True
    else:
        print("Output is incorrect.")
        return False


def main():
    success = solve()
    sys.exit(0 if success else 1)


if __name__ == "__main__":
    main()
