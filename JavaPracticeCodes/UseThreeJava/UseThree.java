/*###############################################
# Anil Celik Maral - amaral
# amaral@ucsc.edu
# 1454995
# Java Practice No:4
# Date: 09/30/17
###############################################*/

/******************************************************************************
 *  Compilation:  javac UseThree.java
 *  Execution:    java UseThree name1 name2 name3
 *
 *  Takes 3 command-line arguments and prints them in reverse order
 *  in a friendly greeting.
 *
 *  % java UseThree Alice Bob Carol
 *  Hi, Carol, Bob, and Alice.
 *
 *  % java UseThree Carol Bob Alice
 *  Hi, Alice, Bob, and Carol.
 *
 ******************************************************************************/

public class UseThree
{
    public static void main(String[] args)
    {
        int i = 0;
        System.out.print("Hi ");
        for (i = 2; i >= 1; i--)
        {
            System.out.print(args[i]);
            System.out.print(", ");
        }
        System.out.print("and ");
        System.out.print(args[i]);
        System.out.println(".");
    }
}