/*###############################################
# Name: Anil Celik Maral
# Cruz ID: amaral
# amaral@ucsc.edu
# Student ID: 1454995
# CMPS101, Programming Assignment-1(pa1)
# Date: 10/09/17
###############################################*/

import java.io.File;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileWriter;

public class Lex 
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
                                                    //false otherwise.
        if(textExists == false)
        {
            System.err.println("File to open and read(Command line argument 1) doesn't exist.");
            return;
        }
        
        // We open the file and initialize it to read.
        FileReader file = new FileReader(fileName);
        BufferedReader reader = new BufferedReader(file);

        int numberOfWords = 0;
        String line = reader.readLine(); // This will reference one line at a time.
        while(line != null) // This loop counts the number of words in the input file.
        {
            numberOfWords = numberOfWords + 1;
            line = reader.readLine();
        }
        reader.close(); // Close the file to reset.
        String[] words = new String[numberOfWords]; // Create the String Array.
        List myList = new List(); // Creates the list.
        Integer[] sortedIndexes = new Integer[numberOfWords]; // Creates the array to hold the
                                                              // sorted indexes which will be
                                                              // inserted in a sorted way.

        // Reopen it after the reset.
        file = new FileReader(fileName);
        reader = new BufferedReader(file); 

        int j = 0;
        line = reader.readLine();
        while(j <= (numberOfWords - 1) && line != null) // We save the words into our string.
        {
            words[j] = line;
            sortedIndexes[j] = j;
            line = reader.readLine();
            j = j + 1;
        }

        //Close the input file to start writing to the output file.
        file.close();
        reader.close();

        // Sort the indexes of the array so that we may use the integer sortedIndexes array to
        // insert to the list(myList) in a sorted way one by one.
        insertionSort(words, sortedIndexes, numberOfWords);
    
        // Insert the indices of the array one by one into the appropriate positions of the List.
        // In other words, we will insert the indexes to the list in the sorted order.
        for(j = 0; j < numberOfWords ; j++)
        {
            myList.append(sortedIndexes[j]);
        }
        String outputFileName = args[1]; // The name of the file to open.

        //We start writing into the output file which is indicated by command line argument 2.
        j = 0; // Reset the index!
        FileWriter outputFile = new FileWriter(outputFileName);
        BufferedWriter writer = new BufferedWriter(outputFile);
        for(myList.moveFront(); myList.index() >= 0; myList.moveNext())
        {
            writer.write(words[myList.get()]);
            writer.newLine();
        }
        writer.close(); // Close the file.

        // Free all the used memory by deleting the variables etc.
        fileName = null;
        possibleText = null;
        file = null;
        reader = null;
        line = null;
        words = null;
        myList.clear();
        myList = null;
        sortedIndexes = null;
        outputFileName = null;
        outputFile = null;
        writer = null;
        return;
    }
    /* This is the insertion sort algorithm. Pseudocode was provided in the assignment - 2 
    lab manual for CS - 12B. The credit for providing the pseudocode goes to Professor
    Darrell Don Earl Long from UCSC.*/
    // This algorithm takes the string that stores the words that will be used to correctly
    // sort String array's indexes which will be placed in the integer array k. The sorting
    // (placement) of the indexes are made lexicographically.
    // Precondition: stringLength() > 0, k != null and s != null.
    private static void insertionSort(String[] s, Integer [] k, int stringLength)
    {
        int temporary = 0;
        int j = 0;
        for (int i = 1; i < stringLength; i++)
        {
            temporary = k[i];
            j = i - 1;
            while (j >= 0 && s[k[j]].compareTo(s[temporary]) > 0) // Sort lexicographically.
            {
                k[j + 1] = k[j];
                j = j - 1;
            }
            k[j + 1] = temporary;
        }
        return;
    }
}