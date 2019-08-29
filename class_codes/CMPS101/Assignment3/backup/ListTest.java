/*###############################################
# Name: Anil Celik Maral
# Cruz ID: amaral
# amaral@ucsc.edu
# Student ID: 1454995
# CMPS101, Programming Assignment-3(pa3)
# Date: 10/30/17
###############################################*/

public class ListTest
{
    public static void main(String[] args)
    {
        // Create the matrices.
        List A = new List();
        List B = new List();
        
        // Add integers starting at 1 upto 20. This should still work although we use Object type
        // this time.
        for(int i = 1; i <= 20; i++)
        {
            A.append(i);
            B.prepend(i);
        }
        // A should be in ascending order from 1 to 20.
        System.out.println(A);
        // B should be in descending order from 20 to 1.
        System.out.println(B);

        // Let's print the length of both lists, it should be 20.
        System.out.println("Length A =");
        System.out.println(A.length());
        System.out.println("Length B =");
        System.out.println(B.length());

        //Let's get the front back element of A and front element of B. Both should be 20.
        System.out.println("Back Element A =");
        System.out.println(A.back());
        System.out.println("Front Element B =");
        System.out.println(B.front());

        for(A.moveFront(); A.index() >= 0; A.moveNext())
        {
            System.out.print((int)A.get() + " "); // We need to cast object to an int.
        }
        System.out.println();
        for(B.moveBack(); B.index() >= 0; B.movePrev())
        {
            System.out.print((int)B.get() + " "); // We need to cast object to an int.
        }
        System.out.println();

        // Should be false!
        System.out.println(A.equals(B));
      
        A.moveFront();
        for(int i = 0; i < 5; i++) // at index 5
        {
            A.moveNext();
        }
        A.insertBefore(-1); // Insert at index 6
        for(int i = 0; i < 9; i++) // at index 15
        {
            A.moveNext();
        }
        A.insertAfter(-2); // insert at index 15.
        for(int i = 0; i < 5; i++) // at index 10
        {
            A.movePrev();
        }
        A.delete(); // Delete the element at index 5.
        System.out.println(A); // -1 should be in between 5 and 6 and -2 should be in between 15
                               // and 16.
        System.out.println(A.length()); // Should be 21.

        // Now, let's print the back element of A and front element of B. 20 should be deleted.
        A.deleteBack();
        System.out.println(A);
        B.deleteFront();
        System.out.println(B);

        A.clear();
        System.out.println(A.length());
        return;
    }
}