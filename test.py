rook = None
end = None
board = []
grid = []


for row in range(8):

    board.append([])
    grid.append([])
    str_row = input()

    for column in range(8):

        
        board[row].append(str_row[column])
        
        grid[row].append(float("infinity"))

        if str_row[column] == "v":

            rook = [row,column]

        elif str_row[column] == "c":

            end = [row,column]

position = rook

stack = [rook]

grid[rook[0]][rook[1]]=0

while True:

    for j in range(position[1],8):

        if board[position[0]][j] == "x":
           
             break

        if board[position[0]][j] in ".c" and grid[position[0]][position[1]] + 1 < grid[position[0]][j]:
           
            grid[position[0]][j] = grid[position[0]][position[1]] + 1
           
            stack.append((position[0],j))

    for j in range(position[0], 8):

        if board[j][position[1]] == "x": 
           
            break
        
        if board[j][position[1]] in ".c" and grid[position[0]][position[1]] + 1 < grid[j][position[1]]:
           
            grid[j][position[1]] = grid[position[0]][position[1]]+1


            stack.append((j,position[1]))


    


    for j in range(position[0],-1,-1):

        if board[j][position[1]] == "x":

             break

        if board[j][position[1]] in ".c" and grid[position[0]][position[1]] + 1 < grid[j][position[1]]:

            grid[j][position[1]] = grid[position[0]][position[1]] + 1

            stack.append((j,position[1]))

    for j in range(position[1],-1,-1):

        if board[position[0]][j] == "x":

             break

        if board[position[0]][j] in ".c" and grid[position[0]][position[1]] + 1 < grid[position[0]][j]:

            grid[position[0]][j] = grid[position[0]][position[1]] + 1

            stack.append((position[0],j))

    if len(stack)>0:

        position = stack.pop()

    else:

        break



if grid[end[0]][end[1]] != float ("infinity"):

    print (grid[end[0]][end[1]])

else:

    print(-1)

    




