//
//  main.c
//  maxrangeSum
//
//  Created by Simran Kaur Arora on 9/26/16.
//  Copyright © 2016 Simran Kaur Arora. All rights reserved.
//

#include <stdio.h>
int main(int argc, char *argv[]) {
    FILE *fp;
    int days, digits[99];
    
    //checking for at least two arguments in the file
    if (argc != 2) {
        printf("Usage: %s [FILE]\n", argv[0]);
        return 1;
    }
    //reading the arguments of file and storing in a string
    fp = fopen(*++argv, "r");
               //storing the day of each case entered
               while (fscanf(fp, "%d;", &days) != EOF) {
                   int max = 0, sum = 0, num, i = 0;
                   //reading the digits(profit/loss) of each element (day) in the array and finding the maximum array(maximum profit)
                   do {
                       fscanf(fp, "%d", &num);
                       //if else loop to keep the check of the counter with number of days to calculate maximum profit in continous days
                       if (i < days) {
                           sum += num;
                           digits[i++] = num;
                       } else {
                           sum += num - digits[i % days];
                           digits[i++ % days] = num;
                       }
                       //condition to keep a check on maximum profit and minimum profit is 0(negative not displayed)
                       if (i >= days && sum > max)
                           max = sum;
                   } while (getc(fp) == ' '); // do the while till end of each entry
                   printf("%d\n", max);       // display maximum profit for each entry
               }
               return 0;
               }
