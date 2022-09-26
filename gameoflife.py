world_size = input().split()
number_steps = int(input())

x = int(world_size[0])
y = int(world_size[1])


world = []

for i in range(y):
    world.insert(i,[])
for i in range(y):
    l = 0
    for k in str(input()):
        world[i].extend(k)
        l+=1
def newworlds(time, world):
    print(("="*x).strip())
    new_world = []
    for row in range(y):
        new_world.insert(row,[])
        for column in range(x):

            around= str(world[(row-1)%y][(column-1)%x])+str(world[(row-1)%y][(column)%x])+str(world[(row-1)%y][(column+1)%x])+str(world[(row)%y][(column-1)%x])+str(world[(row)%y][(column+1)%x])+str(world[(row+1)%y][(column-1)%x])+str(world[(row+1)%y][(column)%x])+str(world[(row+1)%y][(column+1)%x])

            neighbour = 0
            for k in around:
                if k == "o":
                    neighbour +=1
            if world[(row)][(column)] == "o" and neighbour < 2:
                new_world[row].extend(".")
            elif world[(row)][(column)] == "o" and 2 <= neighbour <=3:
                new_world[row].extend("o")
            elif world[(row)][(column)] == "o" and 3 < neighbour:
                new_world[row].extend(".")
            elif world[(row)][(column)] == "." and neighbour == 3:
                new_world[row].extend("o")
            else:
                new_world[row].extend(world[row][column])

    for u in range(y):
        printed = ""
        for v in range(x):
            printed += str(new_world[u][v])
        print(printed.strip())
    time -=1
    if time !=0:
        newworlds(time,new_world)
    else:
        return None
newworlds(number_steps,world)
                
