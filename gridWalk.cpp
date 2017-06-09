//
//  main.cpp
//  gridwalk
//
//  Created by Simran Kaur Arora on 10/17/16.
//  Copyright © 2016 Simran Kaur Arora. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>

/*
 There is a monkey which can walk around on a planar grid. The monkey
 can move one space at a time left, right, up or down. That is, from
 (x, y) the monkey can go to (x+1, y), (x-1, y), (x, y+1), and (x, y-1).
 Points where the sum of the digits of the absolute value of the x
 coordinate plus the sum of the digits of the absolute value of the y
 coordinate are lesser than or equal to 19 are accessible to the monkey.
 For example, the point (59, 79) is inaccessible because 5 + 9 + 7 + 9 = 30,
 which is greater than 19. Another example: the point (-5, -7) is
 accessible because abs(-5) + abs(-7) = 5 + 7 = 12, which is less than 19.
 How many points can the monkey access if it starts at (0, 0), including
 (0, 0) itself?
 */

using namespace std;

struct monkey {
    int position[400][400];
    int counter;
    
    monkey() {
        memset(&(position[0][0]), 0, 400 * 400 * sizeof(int));
        counter = move(0, 0);
    }
    
    /*
     *	Description:		This function will check if a pair of coordinates
     *						digits will sum up to be greater than 19. If they
     *						do than will return false, If they dont than returns
     *						true.
     *
     *	input:
     *	int x, int y:		The x coordinate and y coordinate
     *
     *	output:
     *	false:				The digits add up to be greater than 19.
     *	true:				The digits add up to be less than or equal to 19.
     */
    
    bool SumOfDigit(int x, int y){
        
        int sum = 0;
        //checks if x is not 0, if not then will add up all the digits
        //in the number and stores the added values into sum.
        while (x != 0){
            sum += x % 10;
            x = x / 10;
        }
        //checks if y is not 0, if not then will add up all the digits
        //in the number and stores the added values into sum.
        while (y != 0){
            sum += y % 10;
            y = y / 10;
        }
        //checks to see if sum is greater than 19, if so returns false
        if (sum > 19){
            return false;
        }
        return true;
    }
    
    /*
     *	Description:		This function will take an input of a grid point and find all the
     *						valid points starting from that grid point the monkey can travel
     *						to. This function also depends on array pos[][], to find what the
     *						max area is on the grid. This grid will only count from the upper
     *						half of the first quadrant.
     *
     *	input:
     *	int x, int y:		the x and y coordinates on the grid
     *
     *	ouput:
     *	sum		=			amount of points that grid point was worth, ie. (2,2) = 4 but (2,3) = 8
     *	0		=			invalid point.
     *
     *
     */
    int move(int x, int y) {
        int add;
        // if the sum of the digits is greater than 19
        if (!SumOfDigit(x, y)){
            return 0;
        }
        // checks to see if the point exists and to know when to stop increasing x and y
        if (position[x][y]){
            return 0;
        }
        //if x and y equal they only have 3 other possible
        //duplicates with those digits makeing 4 all together
        //**if x is 0 then the cord is (0,0) which can only be counted once**
        if ((x == y)){
            
            add = (1 + 3 * (x != 0));
            position[x][y] = add;
        }
        //mulitiply by 4 because there are 4 other quad
        //add 4 because only calculating for half
        //of the quad so need to account for the other halves
        //**if y is 0 its on an axis, the point can only be counted 4 times**
        else{
            
            add = (4 + 4 * (y != 0));
            position[x][y] = add;
        }
        add += move(x + 1, y); //traverses through all x in first quad
        //checks if y is greater than x, because if y is greater than x when x goes
        //to its max it will always fail (sum of digits > 19, or unrechable)
        //so no need to check these values
        if (x > y)
            add += move(x, y + 1); // traverses through all y in first quad
        return add;
    }
};

int main() {
    monkey monk;
    printf("%d%", monk.counter);
    getchar();
    return 0;
}
