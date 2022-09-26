class Stack:
    
    def __init__(self):
        self.__items = []

    def __repr__(self) -> str:
        return "Stack " + str(self.__items)

    # def __str__(self) -> str:
    #    pass

    def push(self, item):
        self.__items.append(item)

    def peek(self):
        return self.__items[-1]

    def pop(self):
        return self.__items.pop()

        value = self.__items[-1]
        del self.__items[-1]
        return value

    def is_empty(self):
        if len(self.__items) == 0:
            return True
            
        else:
            return False   
          

# print(__name__)

if __name__ == '__main__':

    stack = Stack()
    posledni = ""
    for a in input():
        predposledni = posledni
        stack.push(a)
        posledni = stack.peek()
        if(predposledni == "("):
            if( posledni == ")"):
                stack.pop()
                stack.pop()
                if stack.is_empty() == True:
                    continue
                else:

                    posledni = stack.peek()
        if(predposledni == "["):
            if( posledni == "]"):
                stack.pop()
                stack.pop()
                if(stack.is_empty()) == True:
                    continue
                else:

                    posledni = stack.peek()
        if(predposledni == "{"):
            if( posledni == "}"):
                stack.pop()
                stack.pop()
                if(stack.is_empty() == True):
                    continue
                else:

                    posledni = stack.peek()
        if(predposledni == "<"):
            if( posledni == ">"):
                stack.pop()
                stack.pop()
                if(stack.is_empty() == True):
                    continue
                else:

                    posledni = stack.peek()
    if ( stack.is_empty() == True):
        print(True)
    else:
        print(False)
