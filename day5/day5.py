from intervaltree import Interval, IntervalTree


def main():
    with open("/Users/whysoserious/repos/aoc/aoc25/day5/input.txt", "r") as inputFile:
        lines = inputFile.readlines()

    interval_tree = IntervalTree()

    # Read the intervals and insert them into the tree
    cnt = 0
    for line in lines:
        if line == "\n":
            cnt += 1
            break

        fresh_range = line.replace("\n", "").split("-")
        # print(f"{fresh_range}")
        range_tuple = Interval(int(fresh_range[0]), int(fresh_range[1]) + 1)
        interval_tree.add(range_tuple)

        cnt += 1

    # After inserting all ranges, merge all overlaps
    interval_tree.merge_overlaps(strict=False)

    # print(f"{interval_tree}")

    fresh_ingredients = 0
    # Part 1
    # for line in lines[cnt:]:
    #     # print(f"checking {line.replace('\n', '')}")
    #     if len(interval_tree.at(int(line))) > 0:
    #         # print(f"{line} is in range")
    #         fresh_ingredients += 1

    # Part 2
    for interval in interval_tree:
        fresh_ingredients += interval[1] - interval[0]

    print(fresh_ingredients)


if __name__ == "__main__":
    main()
