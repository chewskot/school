using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace ConsoleApp3
{
    class Program
    {
        public static void Main()
        {
            string[] input = File.ReadAllLines("odst.in");
            List<string> words = new List<string>();
            for (int i = 1; i < input.Length; i++)
                words.InsertRange(words.Count, input[i].Split(new string[] { " ", "\r\n" }, StringSplitOptions.RemoveEmptyEntries));
            int width = int.Parse(input[0]);
            StringBuilder output = new StringBuilder();
            List<string> radek = new List<string>();
            int delka = 0;
            int k = 0;
            while (k < words.Count) 
            {
                while (k < words.Count && (delka + words[k].Length <= width || radek.Count == 0))
                {
                    radek.Add(words[k] + " ");
                    delka += radek[radek.Count-1].Length;                   
                    k++;
                }
                radek[radek.Count - 1] = radek[radek.Count - 1].Substring(0, radek[radek.Count - 1].Length-1) + "\n";
                if (k != words.Count)
                {
                    int spaces = width - (delka - 1);
                    for (int i = 0; spaces > 0; spaces--)
                    {
                        if (i >= radek.Count-1)
                            i = 0;
                        radek[i] = radek[i] + " ";
                        i++;
                    }
                }
                for (int i = 0; i < radek.Count; i++)
                    output.Append(radek[i]);
                radek.Clear();
                delka = 0;
            }            
            using (StreamWriter writer = new StreamWriter("odst.out")){
                writer.Write(output);}
        }
    }
}