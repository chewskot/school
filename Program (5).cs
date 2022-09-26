using System;
using System.Collections.Generic;
namespace beast
{
    public class Program
    {
        const char zed = 'X';
        const char prazdno = '.';
        const char nahoru = '^';
        const char vlevo = '<';
        const char vpravo = '>';
        const char dolu = 'v';

        public static int xx;
        public static int yy;
        public static char stav;

        static char[,] Bludiste()
        {
            int y = Convert.ToInt32(Console.ReadLine());
            int x = Convert.ToInt32(Console.ReadLine());

            char[,] bludiste = new char[x + 2, y + 2];

            for (int i = 0; i < x + 2; i++)
            {
                bludiste[i, 0] = zed;
                bludiste[i, y + 1] = zed;
            }
            for (int i = 0; i < y + 2; i++)
            {
                bludiste[0, i] = zed;
                bludiste[x + 1, i] = zed;
            }
            for (int i = 1; i < x + 1; i++)
            {
                string temp = Console.ReadLine();
                for (int j = 1; j < y + 1; j++)
                {
                    bludiste[i, j] = temp[j - 1];
                    if (bludiste[i, j] == nahoru || bludiste[i, j] == dolu || bludiste[i, j] == vlevo || bludiste[i, j] == vpravo)
                    {
                        xx = i;
                        yy = j;
                        stav = bludiste[i, j];
                    }
                }
            }
            return bludiste;
        }
        static char[,] Dopredu(char[,] bludiste, char orientace)
        {
            bludiste[xx, yy] = prazdno;
            switch (orientace)
            {
                case nahoru:
                    xx--;
                    break;
                case dolu:
                    xx++;
                    break;
                case vlevo:
                    yy--;
                    break;
                case vpravo:
                    yy++;
                    break;
                default:
                    break;
            }
            bludiste[xx, yy] = orientace;
            return bludiste;
        }
        static char[,] Doleva(char[,] bludiste, char orientace)
        {
            switch (orientace)
            {
                case nahoru:
                    bludiste[xx, yy] = vlevo;
                    break;
                case dolu:
                    bludiste[xx, yy] = vpravo;
                    break;
                case vlevo:
                    bludiste[xx, yy] = dolu;
                    break;
                case vpravo:
                    bludiste[xx, yy] = nahoru;
                    break;
                default:
                    break;
            }
            return bludiste;
        }
        static char[,] Doprava(char[,] bludiste, char orientace)
        {
            switch (orientace)
            {
                case nahoru:
                    bludiste[xx, yy] = vpravo;
                    break;
                case dolu:
                    bludiste[xx, yy] = vlevo;
                    break;
                case vlevo:
                    bludiste[xx, yy] = nahoru;
                    break;
                case vpravo:
                    bludiste[xx, yy] = dolu;
                    break;
                default:
                    break;
            }
            return bludiste;
        }
        static void bludPrint(char[,] bludiste)
        {
            for (int i = 1; i < bludiste.GetLength(0) - 1; i++)
            {
                for (int j = 1; j < bludiste.GetLength(1) - 1; j++)
                {
                    Console.Write(bludiste[i, j]);
                }
                Console.Write("\n");
            }
            Console.WriteLine();
        }
        static void Bludiste1(char[,] bludiste)
        {
            int opakovani = 0;
            char orientace = bludiste[xx, yy];
            char new_orientace_right = vpravo;
            char new_orientace_left = vlevo;
            int forward_x = xx;
            int forward_y = yy;
            int right_x = xx;
            int right_y = yy;
            while (opakovani < 20)
            {
                switch (orientace)
                {
                    case nahoru:
                        right_x = xx;
                        right_y = yy + 1;
                        forward_x = xx - 1;
                        forward_y = yy;
                        new_orientace_right = vpravo;
                        new_orientace_left = vlevo;
                        break;
                    case dolu:
                        right_x = xx;
                        right_y = yy - 1;
                        forward_x = xx + 1;
                        forward_y = yy;
                        new_orientace_right = vlevo;
                        new_orientace_left = vpravo;
                        break;
                    case vlevo:
                        right_x = xx - 1;
                        right_y = yy;
                        forward_x = xx;
                        forward_y = yy - 1;
                        new_orientace_right = nahoru;
                        new_orientace_left = dolu;
                        break;
                    case vpravo:
                        right_x = xx + 1;
                        right_y = yy;
                        forward_x = xx;
                        forward_y = yy + 1;
                        new_orientace_right = dolu;
                        new_orientace_left = nahoru;
                        break;
                    default:
                        break;
                }
                if (bludiste[right_x, right_y] == zed)
                {
                    if (bludiste[forward_x, forward_y] != zed)
                    {
                        bludiste = Dopredu(bludiste, orientace);
                    }
                    else
                    {
                        bludiste = Doleva(bludiste, orientace);
                        orientace = new_orientace_left;
                    }
                    opakovani++;
                    bludPrint(bludiste);
                }


                else
                {
                    bludiste = Doprava(bludiste, orientace);
                    orientace = new_orientace_right;
                    bludPrint(bludiste);
                    opakovani++;
                    if (opakovani < 20)
                    {
                        bludiste = Dopredu(bludiste, orientace);
                        bludPrint(bludiste);
                        opakovani++;
                    }
                }
            }
        }
        static void Main(string[] args)
        {
            char[,] bludiste = Bludiste();
            Bludiste1(bludiste);
        }
    }
}
