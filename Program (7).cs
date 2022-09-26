using System;
using System.Linq;
using System.Collections.Generic;


namespace KingsPath
{
    internal class Program
    {
        static void Main(string[] args)
        {
            int[,] board = new int[10, 10]
            {
            {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 },
            {-1,99,99,99,99,99,99,99,99,-1 },
            {-1,99,99,99,99,99,99,99,99,-1 },
            {-1,99,99,99,99,99,99,99,99,-1 },
            {-1,99,99,99,99,99,99,99,99,-1 },
            {-1,99,99,99,99,99,99,99,99,-1 },
            {-1,99,99,99,99,99,99,99,99,-1 },
            {-1,99,99,99,99,99,99,99,99,-1 },
            {-1,99,99,99,99,99,99,99,99,-1 },
            {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 },
            };



            int[,] moves = { { -1, -1 }, { -1, 0 }, { -1, 1 },{0,-1 }, { 0, 1 }, { 1, -1 }, { 1, 0 },{ 1, 1 } };


            int obstacle = int.Parse(Console.ReadLine());

            for (int i = 0; i < obstacle; i++)
            {
                var obstacle_pos = Console.ReadLine().Trim().Split().Select(int.Parse).ToArray();
                board[obstacle_pos[0], obstacle_pos[1]] = -1;
            }

            //starting position
            var starting_pos = Console.ReadLine().Trim().Split().Select(int.Parse).ToArray();
            board[starting_pos[0], starting_pos[1]] = 0;

            //finishing position
            var finishing_pos = Console.ReadLine().Trim().Split().Select(int.Parse).ToArray();


            Queue<int> queue = new Queue<int>();

            queue.Enqueue(starting_pos[0]);
            queue.Enqueue(starting_pos[1]);

            int distance = 1;
            queue.Enqueue(distance);
            bool outof = true;

            while (queue.Count > 0)
            {
                //x,y coordinates
                int x_pos = queue.Dequeue();
                int y_pos = queue.Dequeue();

                distance = queue.Dequeue();

                for (int i = 0; i < 8; i++)
                {
                    // if not visited
                    if (board[x_pos + moves[i,0], y_pos + moves[i,1]] == 99)
                    {
                        board[x_pos + moves[i,0], y_pos + moves[i,1]] = distance;

                        if (x_pos + moves[i, 0] == finishing_pos[0] & y_pos + moves[i,1] == finishing_pos[1])
                        {
                            Console.WriteLine(board[finishing_pos[0], finishing_pos[1]]);
                            outof = false;
                            break;
                        }

                        queue.Enqueue(x_pos + moves[i, 0]);
                        queue.Enqueue(y_pos + moves[i, 1]);
                        queue.Enqueue(distance + 1);    //next tiles are 1 distance further
                    }
                }

                if (outof == false)
                {
                    break;
                }

            }
            if (outof == true)
            {
                Console.WriteLine("-1");
            }
        }
    }
}
