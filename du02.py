i=2
a=int(input())
while i <= a :
    if (a // i)*i == a :
        print(i)
        a=a // i
    if(a//i)*i != a :
        i+=1
