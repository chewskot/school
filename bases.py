from os import truncate


inputs = input().split()
first = int(inputs[1])
first_base = int(inputs[0])

second = int(inputs[3])
second_base = int(inputs[2])

final_base = int(inputs[4])


def to_decimal(number, base):
    digit = len(str(number)) -1
    number_decimal = 0
    negative = False
    if 0<number < base:
        return number
    for i in str(number):
        if i =="-":
            i =""
            digit-=1
            negative = True
            continue
        if int(i) >= base:
            return None
        number_decimal += (base**digit)*int(i)
        digit -=1
    if(number) == 0:
        return 0
    if negative:
        number_decimal= int("-" +str(number_decimal))
    return number_decimal
first_decimal = (to_decimal(first, first_base))
second_decimal = (to_decimal(second, second_base))
def counting(number1, number2, base): #operace a prevod na zaklad, ktery chceme
    if number1 == None:
        return None
    if number2 == None:
        return None
    suming = number1 + number2
    subtract = number1 - number2
    multiplication = number1 * number2
    if(number2 == 0):
        division = None
    else:
        division = number1 // number2

    suming1 = from_decimal(suming, base)[::-1]
    subtract1 = from_decimal(subtract, base)[::-1]
    multiplication1 = from_decimal(multiplication, base)[::-1]
    if division != None:
        division1 = from_decimal(division, base)[::-1]

    print(suming1)
    print(subtract1)
    print(multiplication1)
    if division1 != None:
        print(division1)
    else:
        print(None)



def from_decimal(number, base):    #prevadeni z desitkoveho zakladu na ten, ktery chceme
    modulation = ""
    digit_location = 0
    next_number = ""
    a= ""
    no = False
    negative = False
    zeros = []
    for k in str(number):
        zeros.append(k)
    zeros.append(None)
    for i in str(number):
        digit_location +=1
        a += i
        if zeros[digit_location] == "0":
            continue
        if a=="-":
            a= ""
            negative = True
            continue

        if int(a) < base:
            continue
        if int(a) >= base:
            next_number += str(int(a)//base)
            a = str(int(a)%base)
    if next_number == "":
        next_number = a
        no = True
    if int(next_number) > base:
        a = a+ from_decimal(next_number, base)
    else:
        if no == False:
            a += next_number
    if(negative):
        a = a + "-"
    return a

    
counting(first_decimal,second_decimal, final_base)