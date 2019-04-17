/*###############################################
# Anil Celik Maral - amaral
# amaral@ucsc.edu
# 1454995
# Assignment - 4
# Lab: Friday, 9:00am - 10:00am
# Lab Partner: None
# Date: 05/27/17
###############################################*/

# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <stdlib.h>
# include <stdint.h>
# include <string.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include "stack.h"
# include "code.h"
# include "huffman.h"
# include "queue.h"
# include "bv.h"
# include "statistics.h"

# ifndef NIL
# define NIL (void *) 0
# endif

/* --Function Prototypes-- */

/*Free()s the allocated memory chunk for the huffman tree nodes!*/
void treeDel(treeNode *root);

/*--Global Variables--*/

/* The number of bits(non-encoded) that the original file had! */
uint64_t bitCount = 0;

int main(int argc, char**argv)
{
    treeNode *reconstructedHuffmanTree = NIL;
    static treeNode *treeRoot = NIL; // This is the root of the huffman tree.
    ssize_t bytesRead = 0; // Used by read().
    ssize_t bytesWritten = 0; // Used by write().
    size_t bytesToBeRead = 0; // Used by read().
    size_t bytesToBeWritten = 0; // Used by write(),
    struct stat fileInfo; // Usage from -> https://linux.die.net/man/2/stat
    char *inputFile = NIL; // Path name of the file that we encode.
    char *outputFile = NIL; // Path name of the file that we write the encode version.
    char *writeCharArray = NIL; // This is the buffer that holds the decoded characters.
    char inputCharacter = 0; // getopt flag variable.
    uint8_t getStatistics = false; // Used for -v flag.
    uint8_t desiredBit = 3; // Used to get a byte from the decoded file.
    uint8_t bitValue = 3; // This is the specific value at a bit of desiredBit.
    uint8_t bitIndex = 0; // Used to check each bit from 0 to 7.
    uint8_t writeToStdoutFlag = true; // True only if no -o is specified.
    uint8_t *savedHuffmanTree = NIL; // The array that holds the tree info.
    uint8_t readBuffer[1];   //The characters are saved into this character array.
    uint8_t magicNumberMatchesFlag = false;
    uint16_t huffmanTreeSize = 0; // This size will be (3 * leafCount)-1 (but never less than zero)
    uint32_t huffmanMagicNumber = 0xdeadd00d;
    uint32_t huffmanMagicNumberRead = 0x0;
    uint64_t readBufferIndex = 0; // General read buffer.
    uint64_t writeCharIndex = 0; // This is the index of our decoded character array.
    uint64_t originalFileSizeBytes = 0; // How many chars in the Org. file?
    int32_t stepTreeCheck = 0;
    int fileStatusCheck = 0; // Used to check if a file exists or not.
    int closedFlag = 0;     // This flag is used to check if close function worked properly or not.
    int inputFileDirectory = 0;  // This holds the reference to the file that we open to read.
    int outputFileDirectory = 0;  // This holds the reference to the file that we open to write.
    while ((inputCharacter = getopt(argc, argv, "vi:o:")) != -1)
    {
        if (inputCharacter == 'v') // To get only statistics.
        {
            getStatistics = true;
        } 
        else if (inputCharacter == 'i') // Give a file to decode.
        {
            inputFile = strdup(optarg);
        }
        else if (inputCharacter == 'o') // Give a file to write the decode version. Optional
        {
            outputFile = strdup(optarg);
            writeToStdoutFlag = false;
        }
    }
    // Open the file that will be decoded and save the reference to it.
    inputFileDirectory = open(inputFile, O_RDONLY);
    if (inputFileDirectory == -1)    // If we failed, call perror, exit and warn about the error.
    {    
        perror("An input file is mandatory.");
        exit(errno);
    }
    // Open the file that will be encoded to. If it doesn't exist, then create one.
    if (writeToStdoutFlag == false)
    {
        fileStatusCheck = stat(outputFile, &fileInfo); // Does it exist?
        if (fileStatusCheck == -1) // If not, create.
        {
            outputFileDirectory = creat(outputFile, S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH);
            if (outputFileDirectory == -1)  // If we failed, call perror, exit and warn.
            {    
                writeToStdoutFlag = false;
            }
        }
        else // If exists, open. However, we don't want to overwrite.
        {
            printf("\nThe file exists, we cannot overwrite it.\n");
            return 1;
            outputFileDirectory = open(outputFile, O_WRONLY);
            if (outputFileDirectory == -1)  // If we failed, call perror, exit and warn.
            {    
                perror("Couldn't open the output file");
                exit(errno);
            }
        }
    }
    // Read the file and save the chars in our buffer and the number of bytes we read to variab.
    bytesRead = read(inputFileDirectory, &huffmanMagicNumberRead, sizeof(huffmanMagicNumber));
    if (bytesRead == -1)    // If we failed, call perror, exit and warn about the error.
    {
        perror("Couldn't read the input file - Magic Number");
        exit(errno);
    }
    if (huffmanMagicNumberRead == huffmanMagicNumber)
    {
        magicNumberMatchesFlag = true;
    }
    else
    {
        printf("\nThis is not a huffman encoded file!\n");
        return 1;
    }
    bytesRead = read(inputFileDirectory, &originalFileSizeBytes, sizeof(originalFileSizeBytes));
    if (bytesRead == -1)    // If we failed, call perror, exit and warn about the error.
    {
        perror("Couldn't read the input file - original file size in bytes");
        exit(errno);
    }
    else // Create the array of decoded characters.
    {
        writeCharArray = (char *)calloc(originalFileSizeBytes, sizeof(char));
        if (writeCharArray == NIL)
        {
            printf("\nwriteCharArray failure!\n");
            return 1;
        }
    }
    read(inputFileDirectory, &huffmanTreeSize, sizeof(huffmanTreeSize));
    if (bytesRead == -1)    // If we failed, call perror, exit and warn about the error.
    {
        perror("Couldn't read the input file - huffman tree size");
        exit(errno);
    }
    else // Create the array of uint8_t that holds the saved huffman tree info by the encoder.
    {
        savedHuffmanTree = (uint8_t *)calloc(huffmanTreeSize, sizeof(uint8_t));
        if (savedHuffmanTree == NIL)
        {
            printf("\nTree calloc failure!\n");
            return 1;
        }
    }
    bytesToBeRead = huffmanTreeSize;
    read(inputFileDirectory, savedHuffmanTree, bytesToBeRead); // Save the saved tree info.
    if (bytesRead == -1)    // If we failed, call perror, exit and warn about the error.
    {
        perror("Couldn't read the input file - saved huffman tree");
        exit(errno);
    }
    else // Reconstruct the huffman tree using the info we've just got.
    {
        reconstructedHuffmanTree = loadTree(savedHuffmanTree, huffmanTreeSize); // Reconstruct tree
        if (reconstructedHuffmanTree != NIL)
        {
            treeRoot = reconstructedHuffmanTree;
        }
        else
        {
            printf("\nHuffman tree reconstruction failure!\n");
            return 1;
        }
    }
    // Now, we have all the information to decode the code saved in the rest of the file. So, we
    // start reading the file byte by byte and save the symbols for corresponding codes that were
    // saved.
    bytesRead = read(inputFileDirectory, readBuffer, 1);
	while (bytesRead != 0) // Read until the EOF!
    {
        if (bytesRead == -1)    // If we failed, call perror, exit and warn about the error.
        {
            perror("Couldn't read the input file");
            exit(errno);
        }
        uint64_t bytesReadComparisonReplecament = bytesRead; // Prevent unsigned, signed complaint!
        while (readBufferIndex != bytesReadComparisonReplecament) // Until buffer is empty.
        {
            desiredBit = readBuffer[readBufferIndex];
            while (bitIndex < 8) // Check every bit of the byte we've just read.
            {
                bitValue = (((desiredBit) & (0x01 << (bitIndex % 8))) >> (bitIndex % 8)); //Get bit
                if (bitValue == 1 || bitValue == 0) // We step through the tree for each 0 and 1.
                {
                    stepTreeCheck = stepTree(treeRoot, &(reconstructedHuffmanTree), bitValue);
                    if (stepTreeCheck != -2 && stepTreeCheck != -1) //No error return or int. node.
                    {
                        if (writeCharIndex < originalFileSizeBytes) // Save char to the array.
                        {
                            writeCharArray[writeCharIndex] = (char)stepTreeCheck;
                            ++writeCharIndex;
                        }
                    }
                    else if (stepTreeCheck == -2 && stepTreeCheck != -1) //If error (not int.node)
                    {
                        printf("\nStep tree failure!\n");
                    }
                }
                else
                {
                    printf("\nBit value failure!\n");
                }
                ++bitIndex; // Go to next bit.
            }
            ++readBufferIndex; // Go to next byte.
        }
        bitIndex = 0; // Reset.
        readBufferIndex = 0; // Reset.
        bytesRead = read(inputFileDirectory, readBuffer, 1); // Continue reading.
    }
    if (originalFileSizeBytes == writeCharIndex) // If we saved correctly.
    {
        bytesToBeWritten = originalFileSizeBytes;
        if (writeToStdoutFlag == false) // If we opened a file to write.
        {
            bytesWritten = write(outputFileDirectory, writeCharArray, bytesToBeWritten);
        }
        else
        {
            bytesWritten = write(1, writeCharArray, bytesToBeWritten); // Write to stdout!
        }
        if (bytesWritten == -1)    // If we failed, call perror, exit and warn about the error.
        {
            perror("Couldn't write the characters to the output file");
            exit(errno);
        }
    }
    else
    {
        printf("\nDidn't get all the characters from the encoded file.\n");
    }
    closedFlag = close(inputFileDirectory);
    if (closedFlag == -1)   // If we failed, call perror, exit and warn about the error.
    {
        perror("Couldn't close the input file");
        exit(errno);
    }
    if (writeToStdoutFlag == false) // If we opened a file to write, close it.
    {
        closedFlag = close(outputFileDirectory);
        if (closedFlag == -1)   // If we failed, call perror, exit and warn about the error.
        {
            perror("Couldn't close the output file");
            exit(errno);
        }
    }
    if (getStatistics == true)
    {
        bitCount = (originalFileSizeBytes * 8);
        printf("Original %lu bits: tree (%u)\n", bitCount, huffmanTreeSize);
    }
    free(inputFile);
    if (writeToStdoutFlag == false) // If we opened a file to write, free the path name.
    {
        free(outputFile);
    }
    treeDel(reconstructedHuffmanTree);
    free(((stack *)loadTreeStack)->entries);
    free((stack *)loadTreeStack);
    free(writeCharArray);
    free(savedHuffmanTree);
    return 0;
    ++magicNumberMatchesFlag; // To prevent compiler from complaining.
}

void treeDel(treeNode *root)
{
    if (root != NIL)
    {
        treeDel(root->left);
        treeDel(root->right);
        free(root);
        root = NIL;
    }
    return;
}