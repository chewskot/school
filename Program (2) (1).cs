using System;
using System.Linq;
using System.Collections.Generic;

namespace _022
{
    class Program
    {
        static void Main(string[] args)
        {
            int[,] moves = { { -1, -1 }, { -1, 0 }, { -1, 1 }, { 0, -1 }, { 0, 1 }, { 1, -1 }, { 1, 0 }, { 1, 1 } };
            int distance = 1;
            bool impossible = true;
            int[,] board = new int[10, 10] {
            {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 },
            {-1,69,69,69,69,69,69,69,69,-1 },
            {-1,69,69,69,69,69,69,69,69,-1 },
            {-1,69,69,69,69,69,69,69,69,-1 },
            {-1,69,69,69,69,69,69,69,69,-1 },
            {-1,69,69,69,69,69,69,69,69,-1 },
            {-1,69,69,69,69,69,69,69,69,-1 },
            {-1,69,69,69,69,69,69,69,69,-1 },
            {-1,69,69,69,69,69,69,69,69,-1 },
            {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 },
            };
            int obstacle = int.Parse(Console.ReadLine());
            for (int i = 0; i < obstacle; i++)
            {
                var obstacle_pos = Console.ReadLine().Trim().Split().Select(int.Parse).ToArray();
                board[obstacle_pos[0], obstacle_pos[1]] = -1;
            }
            var starting_pos = Console.ReadLine().Trim().Split().Select(int.Parse).ToArray();
            board[starting_pos[0], starting_pos[1]] = 0;
            var finishing_pos = Console.ReadLine().Trim().Split().Select(int.Parse).ToArray();
            Queue<int> que = new Queue<int>();
            que.Enqueue(starting_pos[0]);
            que.Enqueue(starting_pos[1]);
            que.Enqueue(distance);
            while (que.Count > 0)
            {
                int posx = que.Dequeue();
                int posy = que.Dequeue();
                distance = que.Dequeue();
                for (int i = 0; i < moves.GetLength(0); i++)
                {
                    if (board[posx + moves[i, 0], posy + moves[i, 1]] == 69)
                    {
                        board[posx + moves[i, 0], posy + moves[i, 1]] = distance;
                        if (posx + moves[i, 0] == finishing_pos[0] & posy + moves[i, 1] == finishing_pos[1])
                        {
                            printing(board[finishing_pos[0], finishing_pos[1]]);
                            impossible = false;
                            break;
                        }
                        que.Enqueue(posx + moves[i, 0]);
                        que.Enqueue(posy + moves[i, 1]);
                        que.Enqueue(distance + 1);
                    }
                }
                if (impossible == false)
                {
                    que.Enqueue(starting_pos[0]);
                    que.Enqueue(starting_pos[1]);
                    break;
                }
            }
            if (impossible == true)
            {
                Console.WriteLine("-1");
            }
            void printing(int finish)
            {
                int posx = finishing_pos[0];
                int posy = finishing_pos[1];
                Stack<int> path = new Stack<int>();
                path.Push(posx);
                path.Push(posy);
                while (finish > 0)
                {
                    for (int i = 0; i < moves.GetLength(0); i++)
                    {
                        if (board[posx + moves[i, 0], posy + moves[i, 1]] == (finish - 1))
                        {
                            posy = posy + moves[i, 1];
                            posx = posx + moves[i, 0];

                            path.Push(posy);
                            path.Push(posx);

                            finish--;
                            break;
                        }
                    }
                }
                int x = path.Count;
                for (int i = 0; i < x / 2; i++)
                {
                    int printx = path.Pop();
                    int printy = path.Pop();
                    Console.WriteLine(printx + " " + printy);
                }
            }
        }
    }
}
