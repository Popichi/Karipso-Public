/*###############################################
# Name: Anil Celik Maral
# Cruz ID: amaral
# amaral@ucsc.edu
# Student ID: 1454995
# CMPS101, Programming Assignment-3(pa3)
# Date: 10/30/17
###############################################*/

import java.io.File;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.*;
import java.util.Scanner;

public class Sparse
{ 
    public static void main(String[] args) throws Exception
    { 
        if(args.length < 2) // Check if we have less than two arguments.
        {
            System.err.println("No arguments in the command line");
            return;
        }
        else if(args.length > 2) // Checks if we have more than two arguments.
        {
            System.err.println("Too many arguments in the command line");
            return;
        }
        String fileName = args[0]; // The name of the file to open.
        File possibleText = new File(fileName);
        boolean textExists = possibleText.exists(); // textExists true if the file exists, and 
                                                    // false otherwise.
        if(textExists == false)
        {
            System.err.println("File to open and read(Command line argument 1) doesn't exist.");
            return;
        }
        
        Scanner inputFile = null;
        PrintWriter outputFile = null;
        String line = null;
        String[] token = null;
        int lineNumber = 0;
        int matrixSize = 0;
        int startingLineOfMatricesData = 1;
        int startingLineOfMatrixAData = 3;
        int startingLineOfMatrixBData = 0;
        int matrixANumberOfNonZeroElements = 0;
        int matrixBNumberOfNonZeroElements = 0;

        // Open the input and input files to open them later.
        inputFile = new Scanner(new File(args[0]));
        outputFile = new PrintWriter(new FileWriter(args[1]));

        Matrix A = null;
        Matrix B = null;
        while(inputFile.hasNextLine())
        {
            ++lineNumber;
            line = inputFile.nextLine() + " "; // add extra space so split works right
            token = line.split("\\s+"); // split line around white space
            if(lineNumber == startingLineOfMatricesData)
            {
                matrixSize = Integer.parseInt(token[0]);
                A = new Matrix(matrixSize);
                B = new Matrix(matrixSize);
                matrixANumberOfNonZeroElements = Integer.parseInt(token[1]);
                matrixBNumberOfNonZeroElements = Integer.parseInt(token[2]);
                startingLineOfMatrixBData = (startingLineOfMatrixAData +
                                             matrixANumberOfNonZeroElements);
            }
            else if(startingLineOfMatrixAData <= lineNumber &&
                    lineNumber < (startingLineOfMatrixAData + matrixANumberOfNonZeroElements))
            {
                int row = Integer.parseInt(token[0]);
                int column = Integer.parseInt(token[1]);
                double value = Double.parseDouble(token[2]);
                A.changeEntry(row, column, value);
            }
            else if(startingLineOfMatrixBData < lineNumber &&
                    lineNumber <= (startingLineOfMatrixBData + matrixBNumberOfNonZeroElements))
            {
                int row = Integer.parseInt(token[0]);
                int column = Integer.parseInt(token[1]);
                double value = Double.parseDouble(token[2]);
                B.changeEntry(row, column, value);
            }
        }

        // Print/Write non-zero entries of A and B and their matrices.
        outputFile.println("A has " + A.getNNZ() + " non-zero entries:");
        outputFile.println(A);
        outputFile.println("B has " + B.getNNZ() + " non-zero entries:");
        outputFile.println(B);

        // Print/Write the resulting matrix for (1.5) * A.
        outputFile.println("(1.5)*A =");
        outputFile.println(A.scalarMult(1.5));

        // Print/Write the resulting matrix for A + B.
        outputFile.println("A+B =");
        outputFile.println(A.add(B));

        // Print/Write the resulting matrix for A + A.
        outputFile.println("A+A =");
        outputFile.println(A.add(A));

        // Print/Write the resulting matrix for B - A.
        outputFile.println("B-A =");
        outputFile.println(B.sub(A));

        // Print/Write the resulting matrix for A - A.
        outputFile.println("A-A =");
        outputFile.println(A.sub(A));

        // Print/Write the resulting matrix for Transpose(A).
        outputFile.println("Transpose(A) =");
        outputFile.println(A.transpose());

        // Print/Write the resulting matrix for A * B.
        outputFile.println("A*B =");
        outputFile.println(A.mult(B));

        // Print/Write the resulting matrix for B * B.
        outputFile.println("B*B =");
        outputFile.println(B.mult(B));

        inputFile.close();
        outputFile.close();
        return;
    }
}