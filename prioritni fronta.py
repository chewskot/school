a = ""
com = []
que = []


def swap(x, y):
    temp = que[x]
    que[x] = que[y]
    que[y] = temp

def insert(x):
    que.append(x)
    i = len(que)-1
    while i > 0:
        if (que[i][0] > que[i//2][0]):
            swap(i, i//2)
            i //= 2
        else:
            break

def drop():
    dropped = que[0]
    que[0] = que[len(que)-1]
    que.pop()

    i = 0
    while 2*i < len(que):
        j = i
        if que[j][0] < que[2*i][0]:
            j = 2*i
        if (2*i+1 < len(que)):
            if (que[j][0] < que[2*i+1][0]):
                j = 2*i+1
        if i == j:
            break
        swap(i, j)
        i = j

    return dropped


while (a != "DONE"):    
    com.append(a.split(" "))
    a = input()

for i in com:
    if (i[0] == "ENQUEUE"):
        insert([int(i[2]), i[1]])
    elif (i[0] == "DEQUEUE"):
        temp = drop()
        print(temp[1] + " " + str(temp[0]))