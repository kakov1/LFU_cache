import random


for i in range(1, 11):
    file = open(f"{i}test.txt", 'w')

    file.write("10000 100000 ")
    for i in range(100000):
        file.write(f"{random.randint(1, 100000)} ")
        