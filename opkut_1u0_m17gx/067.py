def main():
    with open("p067_triangle.txt", "r") as f:
        next_length = 0
        current_max_row = []
        next_row = []
        for line in f.readlines():
            next_length += 1
            next_row = [int(x) for x in line.split()]
            print(f"length: {next_length}")
            print("\tcurrent_max_row: \t", current_max_row)
            print("\tnext_row: \t\t", next_row)
            print()
            if next_length == 1:
                current_max_row = next_row
            else:
                current_max_row = get_new_max_row(current_max_row, next_row, next_length)
        print(current_max_row)
        print(max(current_max_row))


def get_new_max_row(current_max_row, next_row, next_length):
    next_row[0]  += current_max_row[0]
    next_row[-1] += current_max_row[-1]
    for i in range(1, next_length-1):
        next_row[i] += max(current_max_row[i-1], current_max_row[i])
    return next_row

main()