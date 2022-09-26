using System;
using System.IO;

namespace ConsoleApp1
{
    class nasobeni
    {
        static void kontrola(int[] p, int n)
        {
            int[,] m = new int[n, n];
            int[,] bracket = new int[n, n];

            for (int i = 1; i < n; i++)
            {
                m[i, i] = 0;
            }
            for (int L = 2; L < n; L++)
            {
                for (int i = 1; i < n - L + 1; i++)
                {
                    int j = i + L - 1;
                    m[i, j] = int.MaxValue;
                    for (int k = i; k <= j - 1; k++)
                    {
                        int q = m[i, k] + m[k + 1, j] + p[i - 1] * p[k] * p[j];
                        if (q < m[i, j])
                        {
                            m[i, j] = q;
                            bracket[i, j] = k;
                        }
                    }
                }
            }
            zavorky(1, n - 1, n, bracket);
            Console.Write("\n");
            Console.WriteLine(m[1, n - 1]);
        }
        static void zavorky(int i, int j, int n, int[,] bracket)
        {
            if (i == j)
            {
                Console.Write("A" + i);
                return;
            }
            Console.Write("(");
            zavorky(i, bracket[i, j], n, bracket);
            Console.Write("*");
            zavorky(bracket[i, j] + 1, j, n, bracket);
            Console.Write(")");
        }

        static void Main(string[] args)
        {
            using (var input = new StreamReader("mch.in"))
            {
                int pocet = int.Parse(input.ReadLine());
                int[] vel = new int[pocet];
                for (int i = 0; i < pocet; i++)
                {
                    vel[i] = int.Parse(input.ReadLine());
                }
                kontrola(vel, pocet);

            }
                
        }
    }
}

