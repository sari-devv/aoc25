
def main():
    with open(
        "/Users/whysoserious/repos/aoc/aoc25/day2/input.txt", "r"
    ) as inputFile:
        lines = inputFile.readlines()

    ranges = lines[0].split(',').replace('\n', '')
    print(ranges)

    invalid_ids = 0
    for id_range in ranges:
        
        for num in range(int(id_range[0]), int(id_range[1])):
            num_str = str(num)
            size = len(num_str)
            first_half = num_str[0:size//2]
            second_half = num_str[size//2:]

            if first_half == second_half:
                invalid_ids += 1

    print(invalid_ids)


if __name__ == "__main__":
    main()
