/*###############################################
# Name: Anil Celik Maral
# Cruz ID: amaral
# amaral@ucsc.edu
# Student ID: 1454995
# CMPS101, Programming Assignment-3(pa3)
# Date: 10/30/17
###############################################*/

public class MatrixTest
{
    public static void main(String[] args)
    {
        int matrixASize = 3;
        int matrixBSize = 6;
        int matrixCSize = 4;
        Matrix A = new Matrix(matrixASize); // Shouldn't complain.
        Matrix B = new Matrix(matrixBSize);
        Matrix C = new Matrix(matrixCSize);

        // Construct Matrix A. Tests appending in changeEntry.
        for (int i = 1; i <= matrixASize; i++)
        {
            for (int j = 1; j <= matrixASize; j++)
            {
                double w = (j + 0.7); 
                A.changeEntry(i, j, w);
            }
        }

        // Construct Matrix B. Tests appending in changeEntry.
        for (int i = 1; i <= matrixBSize; i++)
        {
            for (int j = 1; j <= matrixBSize; j++)
            {
                double w = (j + 0.9); 
                B.changeEntry(i, j, w);
            }
        }

        // Construct Matrix C with some zero entries. Tests appending in changeEntry.
        for (int i = 1; i <= matrixCSize; i++)
        {
            for (int j = 1; j <= matrixCSize; j++)
            {
                double w = (j + 0.9);
                if((i == 2 && j == 2) || (i == 3 && j == 1))
                {
                    w = 0;
                }
                C.changeEntry(i, j, w);
            }
        }

        System.out.println("A =");
        System.out.println(A);
        System.out.println("B =");
        System.out.println(B);
        System.out.println("C =");
        System.out.println(C);
        
        // Tests changing some elements to 0 --> Deletes some columns in A.
        A.changeEntry(1, 2, 0);
        A.changeEntry(2, 1, 0);
        A.changeEntry(3, 3, 0);
        
        System.out.println("A =");
        System.out.println(A);

        // Tests changing some elements from 0 to a non-zero value.
        A.changeEntry(1, 2, 16.432); // Inserts before column 3 in row 1.
        A.changeEntry(2, 1, -435.878); //Inserts back the first column of row 2.
        A.changeEntry(3, 3, 0.4359); // Inserts the last column of row 3 by appending.
        A.changeEntry(3, 2, 31.62); // Simply overwrites the value in column 2 in row 3.

        // Now we should get a full matrix again.
        System.out.println("A =");
        System.out.println(A);

        // We copy Matrix A to a new Matrix named D and print it to check if the copy is correct.
        Matrix D = A.copy();
        System.out.println("D =");
        System.out.println(D);
        
        // We use equals() to check if A and D are equal(if we copied correctly).
        System.out.print("Is Matrix A equal to D?(Must return true)--> ");
        System.out.println(A.equals(D)); // Must return true.

        // Now let's check that equals returns the correct value when two matrices are not equal.
        System.out.print("Is Matrix B equal to D?(Must return false)--> ");
        System.out.println(B.equals(D)); // Must return false.
        Matrix E = B.copy();
        System.out.print("Is Matrix E equal to B?(Must return true)--> ");
        System.out.println(E.equals(B)); // Must return true.
        E.changeEntry(1, 2, 0); // Let's delete 2nd column of 1st row. 
        System.out.println();
        System.out.println("E =");
        System.out.println(E);

        // Now, we have a one column difference between E and B. So, we must get a false.
        System.out.println();
        System.out.print(
        "Is Matrix E equal to B?(Must return false because we deleted an element of E)--> ");
        System.out.println(E.equals(B)); // Must return false.

        // We get the transpose of A.
        System.out.println();
        Matrix F = A.transpose();
        System.out.println("F(Transpose(A)) =");
        System.out.println(F);

        // Let's check the number of non-zero entries of Matrix F and E.
        System.out.print("Number of non-zero entries of F: ");
        System.out.println(F.getNNZ());
        System.out.print("Number of non-zero entries of E: ");
        System.out.println(E.getNNZ());

        // Now let's set E Matrix to the zero state.
        E.makeZero();
        System.out.println();
        System.out.print("E(Should print no rows because we set it to the zero state): ");
        System.out.println(E);

        // Now, let's multiply F by 3.
        F = F.scalarMult(3.0);
        System.out.println();
        System.out.println("F x 3.0 =");
        System.out.println(F);

        //Let's create two Matrices G and H and do matrix multiplication on them.
        Matrix G = new Matrix(3);
        // Construct Matrix G.
        for (int i = 1; i <= 3; i++)
        {
            for (int j = 1; j <= 3; j++)
            {
                double w = (j); 
                G.changeEntry(i, j, w);
            }
        }
        Matrix H = G.copy();
        Matrix multGAndH = G.mult(H);
        System.out.println();
        System.out.println("G =");
        System.out.println(G);
        System.out.println();
        System.out.println("H =");
        System.out.println(H);
        System.out.println();
        System.out.println("G x H =");
        System.out.println(multGAndH);

        // Now, let's add Matrices G and H.
        System.out.println();
        System.out.println("G =");
        System.out.println(G);
        System.out.println();
        System.out.println("H =");
        System.out.println(H);
        Matrix addGAndH = G.add(H);
        System.out.println();
        System.out.println("G + H =");
        System.out.println(addGAndH);

        // Now, let's add Matrices G and H.
        System.out.println();
        System.out.println("G =");
        System.out.println(G);
        System.out.println();
        System.out.println("H =");
        System.out.println(H);
        Matrix subGAndH = G.sub(H);
        System.out.println();
        System.out.println("G - H =");
        System.out.println(subGAndH);

        return;
    }
}
