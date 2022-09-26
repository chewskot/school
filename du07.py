import os


current_file_directory = os.path.dirname(os.path.realpath(__file__))


file_path = current_file_directory + "/input.txt"
seznam_vysledku = []
with open(file_path) as file:
    while True:
        line = file.readline().strip()
        if line == "":
            break
        vektor1 = line[line.find("(")+1 : line.find(")")].split()
        vektor2 = line[line.find(")")+2 : line.find("/n")].split()
        vysledek = 0
        for i in range(len(vektor1)):
            vysledek = vysledek + int(vektor1[i])* int(vektor2[i])
        seznam_vysledku.append(vysledek)


file_path_write = current_file_directory + "/output.txt"
with open(file_path_write, "a") as file:
    for i in range(len(seznam_vysledku)):
        print(seznam_vysledku[i], file=file)
