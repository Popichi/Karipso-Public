/*###############################################
# Anil Celik Maral - amaral
# amaral@ucsc.edu
# 1454995
# Java Practice No:11
# Date: 09/29/17
###############################################*/

public class Distance 
{ 
    public static void main(String[] args) 
    { 
        int x, y;
        double distance;
        x = Integer.parseInt(args[0]);
        y = Integer.parseInt(args[1]);
        distance = Math.sqrt(Math.pow((x - 0), 2) + Math.pow((y - 0), 2));
        System.out.println("distance from (" + x + "," + y + ") to (0, 0) =" + distance);
    }
}