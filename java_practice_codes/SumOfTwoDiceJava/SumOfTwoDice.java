/*###############################################
# Anil Celik Maral - amaral
# amaral@ucsc.edu
# 1454995
# Java Practice No:12
# Date: 09/29/17
###############################################*/

public class SumOfTwoDice 
{ 
    public static void main(String[] args) 
    { 
        int rollOne, rollTwo, sum;
        rollOne = 1 + (int)(Math.random() * 6);
        rollTwo = 1 + (int)(Math.random() * 6);
        sum = rollOne + rollTwo;
        System.out.println(sum);
    }
}