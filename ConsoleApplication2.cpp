#include <stdio.h>
#include <iostream>
#include "temps.h"
using namespace std;
//constexpr int no_value = -999;
//constexpr int temperatures[]{ 10, 12, no_value, no_value, 20, 14, 6, -1, -5, 0, no_value, 1, -3 };
//constexpr int temperatures1[]{ 10, 12,2, 14, 6,-3,5 }; //*
//constexpr int temperatures2[]{ 6, -1, 5, 0, 1, -3 }; // #
//prints stars for temperature on thermomether
void stars(int n) { //output of * /1.2e
    if (n < 0)
    {
        n = n * -1;
        for (int i = 0; i < n; i++) printf("*");
    }
    else
    {
        for (int i = 0; i < n; i++) printf("*");
    }
    
}
void hasht(int n) { // output of # /1.2e
    if (n < 0)
    {
        n = n * -1;
        for (int i = 0; i < n; i++) printf("#");
    }
    else
    {
        for (int i = 0; i < n; i++) printf("#");
    }
}

void space(int spaces) { // spaces for 1.2d
    for (int i = 0; i < spaces; i++) printf(" ");
}

void tree(int height) { //prins tree from 1.1c
    bool branches = false;
    for (int i = 0; i < height; i++) {
        if (i == 3 && branches == false) {
            i -= 2;
            branches = true;
        }
        space(height - i);
        stars(1 + (2 * i));
        printf("\n");
    }
}
int minimum(const int field[], int field_size) { // minimum for 
    int min;
    if (field[0] == no_value) {
        min = 0;
    }
    else min = field[0];
    for (int i = 1; i < field_size; i++) {
        if (field[i] < min && field[i] != no_value) min = field[i];
    }
    return min;
}

void calculation(const int temperatures1[], const int temperatures2[], int n,int m)
{
    
    for (int i = 0; i < n; i++)
    {
        if (temperatures1[i] > temperatures2[i]) // * #
        {
            stars(temperatures1[i]);
            hasht(temperatures2[i]);
            printf("\n");
        }
        else // # *
        {
            hasht(temperatures2[i]);
            stars(temperatures1[i]);
            printf("\n");
        }
    }

}
void thermometer(const int field[], int field_size) {
    int min = minimum(field, field_size);
    if (min < 0) min *= -1;
    else min = 0;
    for (int i = 0; i < field_size; i++) {
        int wrong_temp = 0;
        while (field[i] == no_value) {
            wrong_temp += 1;
            i -= 1;
        }
        int current = field[i];
        if (current < 0) {
            space(min + current);
            stars(-1 * current);
            printf("|");
        }
        else {
            space(min);
            printf("|");
            stars(current);
        }
        while (wrong_temp != 0) {
            wrong_temp -= 1;
            i += 1;
        }
        printf("\n");
    }
}
void thermometer2(const int field[],int n) // thermometer from 1.2a

{
    
    for (int i = 0; i < n; i++)
    {
        stars(field[i]);
        printf("\n");

    }
}

int main() {
    //int n = (sizeof(temperatures1) / sizeof(*temperatures1)); // size of first array
    //int m = (sizeof(temperatures2) / sizeof(*temperatures2)); // size of second array
    //calculation(temperatures1, temperatures2,n,m); //1.2e
    //tree(6); //1.1c
    
    thermometer(temperatures, (sizeof(temperatures) / sizeof(temperatures[0]))); //1.2d
    
    //thermometer2(temperatures1,n); // 1.2a


}

