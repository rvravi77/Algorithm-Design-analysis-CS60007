/*
--------------------------------------------------------------
ADA Coding Assignment 3

Group - 11
Members name and Roll number

Pratibha Singh      20CS60R12
Vaibhav Saxena      20CS60R57
Ravi Pratap Singh   20CS60R60
Sahil Jain          20CS60R64
--------------------------------------------------------------

------------------------------------------------------------------------------------
Problem Description:   Generate n distinct points such that their coordinates
                       are integers in the range [20,800] and divisible by 20
------------------------------------------------------------------------------------

--------------------------------------------------------------
Compilation Instruction:

To complie :    g++ <source_filename> -o <Any name>
            eg: g++ a3_1.cpp -o q_a

To Run :        ./<Any name>
            eg: ./q_a
---------------------------------------------------------------

*/

//header files
#include<bits/stdc++.h>
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<fstream>
#include<sstream>
#include<iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    int n_points;
    printf("Enter value of n:   ");
    scanf("%d", &n_points);

    ofstream MyFile("points_1.txt");
    srand(time(0));

    MyFile << n_points << endl;

    for(int i=0; i<n_points; )
    {
        int x = (rand() % (800 - 20 + 1)) + 20;
        int y = (rand() % (800 - 20 + 1)) + 20;

        if( x%20 == 0 && y%20 == 0)
        {
            MyFile << x << " " << y <<endl;
            i++;
        }
    }

    MyFile.close();
    
    return 0;
}