def is_repeated(num_str):
    # Try to divide the string into num_pieces equal pieces,
    # with size ranging from 2 to len(str).
    for num_pieces in range(2, len(num_str) + 1):
        # If the length of the string isn't divisible by this number,
        # we cannot divide the string into equal pieces of this size,
        # therefore skip.
        if len(num_str) % num_pieces != 0:
            continue

        # All pieces should be equal to numStr[0:size]
        piece_size = len(num_str) // num_pieces
        piece = num_str[0:piece_size]

        if num_str == (piece * num_pieces):
            return True

    return False


def main():
    with open("/Users/whysoserious/repos/aoc/aoc25/day2/input.txt", "r") as inputFile:
        lines = inputFile.readlines()

    ranges = lines[0].replace("\n", "").split(",")

    invalid_ids = 0
    for id_range in ranges:
        start, end = id_range.split("-")
        for num in range(int(start), int(end) + 1):
            num_str = str(num)
            if is_repeated(num_str):
                invalid_ids += num

    print(invalid_ids)


if __name__ == "__main__":
    main()
