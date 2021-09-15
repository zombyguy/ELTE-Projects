def main():
    limit = 1000
    out = 0
    for i in range(0, limit, 3):
        out += i
    
    for i in range(0, limit, 5):
        out += i

    for i in range(0, limit, 15):
        out -= i
    print(out)

def main2():
    limit = 1000
    out = 0
    for i in range(limit):
        if i % 3 == 0 or i % 5 == 0:
            out += i
    print(out)

main()
main2()