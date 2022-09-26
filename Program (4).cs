using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
namespace ConsoleApp1
{
    class Time
    {
        public int[] months = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        public int[] vysledek = { 0, 0, 0 };
        public void ctecka()
        {
            string temp = Console.ReadLine();

            string[] temp2 = temp.Split(' ');

            int day_index = Int32.Parse(temp2[0]);
            int month_index = Int32.Parse(temp2[1]);
            int year_index = Int32.Parse(temp2[2]);

            int days_to_pass = Int32.Parse(Console.ReadLine());

            count_days(day_index, month_index, year_index, days_to_pass);
        }
        private bool is_29(int year_index)
        {
            if (year_index % 4 == 0 && year_index % 100 == 0)
            {
                if (year_index % 400 == 0)
                {
                    return true;
                }
            }
            else if (year_index % 4 == 0)
            {
                return true;
            }
            return false;
        }
        public void count_days(int day_index, int month_index, int year_index, int days_to_pass)
        {
            int year_days = 365;
            int year_to_check = (month_index <= 2) ? year_index : year_index + 1;
            if (is_29(year_to_check))
            {
                months[2] = 29;
                year_days = 366;
            }
            else
            {
                months[2] = 28;
            }

            if (day_index > months[month_index])
            {
                day_index = 1;
                if (month_index + 1 > 12)
                {
                    month_index = 1;
                    year_index++;
                }
                else month_index++;
            }

            if (days_to_pass == 0)
            {
                vysledek[0] = day_index;
                vysledek[1] = month_index;
                vysledek[2] = year_index;
                return;
            }

            if (days_to_pass >= year_days)
            {
                days_to_pass = days_to_pass - year_days;
                year_index++;
            }
            else
            {
                day_index++;
                days_to_pass--;
            }
            count_days(day_index, month_index, year_index, days_to_pass);
        }
        public void call()
        {
            ctecka();
            Console.Write(vysledek[0] + " " + vysledek[1] + " " + vysledek[2]);
        }
        class Program
        {

            static void Main(string[] args)
            {


                Time time = new Time();
                time.call();

            }
        }
    }
}
