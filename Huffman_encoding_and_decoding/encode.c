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

# ifndef MAXHISTOGRAMSIZE
# define MAXHISTOGRAMSIZE 256
# endif

/* --Function Prototypes-- */

/* Allocates space for a pointer to a huffman tree. */
treeItemPointer *createArrayOfQueues(); 

/*--Global Variables--*/

/* The number of bits(non-encoded) that the original file had! */
uint64_t bitCount = 0;

/* The number of bits(encoded) that the original file had! */
uint64_t bitCountEncoded = 0;

int main(int argc, char**argv)
{
    ssize_t bytesRead = 0; // Used by read().
    struct stat fileInfo; // Usage from -> https://linux.die.net/man/2/stat
    char *inputFile = NIL; // Path name of the file that we encode.
    char *outputFile = NIL; // Path name of the file that we write the encode version.
    char inputCharacter = 0; // getopt flag variable.
    char characterBeingReadAndPrinted = 0; // Read character from the input file.
    bool queueOperationCheck = false;
    bool queueStatusCheck = false;
    uint8_t readBufferIndex = 0; // Size of read() buffer.
    uint8_t writeToStdoutFlag = true; // True only if no -o is specified.
    uint8_t huffmanHistogramLocation = 0; // Corresponds to the character location.
    uint8_t codeStackLocation = 0;  // Correspond to the code location for a specific char.
    uint8_t onlyOneElementLeftInTheQueue = false; // If true, priority queue built the Huff. tree.
    uint8_t getStatistics = false; // Used for -v flag.
    uint8_t readBuffer[1];   //The characters are saved into this character array.
    uint16_t huffmanTreeSize = 0; // This size will be (3 * leafCount)-1 (but never less than zero)
    uint16_t numberOfActiveSymbolsInTheHistogram = 0; // How many leaves will we have?
    uint32_t huffmanMagicNumber = 0xdeadd00d; // Represents a huffman encoded file.
    uint32_t huffmanHistogram[256]; // Holds the number of chars at corresponding locations.
    uint32_t queueSize = 0; // If we know the # of leaves, we can build a sufficient queue size.
    uint32_t codeStackLengthBackUp = 0; // Used when saving the code to the B.V.
    uint64_t bitVectorLengthInBits = 0;
    uint64_t originalFileSizeBytes = 0; // How many chars in the Org. file?
    int fileResetCheck = 0; // Used a a lseek() flag.
    int fileStatusCheck = 0; // Used to check if a file exists or not.
    int closedFlag = 0;     // This flag is used to check if close function worked properly or not.
    int inputFileDirectory = 0;  // This holds the reference to the file that we open to read.
    int outputFileDirectory = 0;  // This holds the reference to the file that we open to write.
    queue *queueOne = NIL; // Priority queue.
    treeNode *joinedInteriorNode = NIL; // Used by join().
    treeItemPointer *dequeuedTreeNode = NIL; // First dequeued node.
    treeItemPointer *dequeuedTreeNodeTwo = NIL; // Second dequeued node.
    treeItemPointer *constructedHuffmanTree = NIL; // Pointer to the completed tree.
    treeItemPointer newTreeNode = NIL;
    bitV *bitVector = NULL;
    bitVector = newVec(16384);    //Used to spit out the encoded version of the original file.
    while ((inputCharacter = getopt(argc, argv, "vi:o:")) != -1)
    {
        if (inputCharacter == 'v') // To get only statistics.
        {
            getStatistics = true;
        } 
        else if (inputCharacter == 'i') // Give a file to encode.
        {
            inputFile = strdup(optarg);
        }
        else if (inputCharacter == 'o') // Give a file to write the encoded version. Optional
        {
            outputFile = strdup(optarg);
            writeToStdoutFlag = false;
        }
    }
    for (uint32_t i = 0; i < MAXHISTOGRAMSIZE; i++) // Initialize the histogram
    {
        huffmanHistogram[i] = 0;
    }
    // The two values below are always to 1 to deal with empty file and file with same char.
    huffmanHistogram[0] = 1; // This idea comes from Darrell Long.
    huffmanHistogram[255] = 1;
    // Stack table with bits in reverse order.
    code stackTable[256];
    for (uint32_t i = 0; i < 256; i++) // Initialize the code stack.
    {
        stackTable[i] = newCode();
    }
    // Stack table with bits in correct order.
    code correctOrderedStackTable[256];
    for (uint32_t i = 0; i < 256; i++) // Initialize the code stack.
    {
        correctOrderedStackTable[i] = newCode();
    }
    // Open the file that will be encoded and save the reference to it.
    inputFileDirectory = open(inputFile, O_RDONLY);
    if (inputFileDirectory == -1)    // If we failed, call perror, exit and warn about the error.
    {    
        perror("An input file is mandatory.");
        exit(errno);
    }
    // Open the file that will be decoded to. If it doesn't exist, then create one.
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
    bytesRead = read(inputFileDirectory, readBuffer, 1);
	while (bytesRead != 0) // Read until the EOF!
    {
        if (bytesRead == -1)    // If we failed, call perror, exit and warn about the error.
        {
            perror("Couldn't read the input file");
            exit(errno);
        }
        while (readBufferIndex != bytesRead) // Until buffer is empty.
        {
            characterBeingReadAndPrinted = readBuffer[readBufferIndex];
            huffmanHistogramLocation = characterBeingReadAndPrinted; // Char is also the index.
            ++huffmanHistogram[huffmanHistogramLocation]; // Increment the # char at loc.
            ++originalFileSizeBytes;
            ++readBufferIndex;
        }
        readBufferIndex = 0; // Reset.
        characterBeingReadAndPrinted = 0;
        bytesRead = read(inputFileDirectory, readBuffer, 1);
    }
    // How many different chars are there?
    for (uint32_t i = 0; i < MAXHISTOGRAMSIZE; i++)
    {
        if (huffmanHistogram[i] != 0)
        {
            ++numberOfActiveSymbolsInTheHistogram;
        }
    }
    queueSize = ((3 * numberOfActiveSymbolsInTheHistogram) - 1); // Required queue size.
    queueOne = newQueue((queueSize + 1)); // +1 because a circular queue holds n - 1 elements.
    if (queueOne != NIL)
    {
        for (uint32_t i = 0; i < MAXHISTOGRAMSIZE; i++)
        {
            if (huffmanHistogram[i] != 0) // Create a leaf for each diff. char.
            {
                newTreeNode = newNode(i, true, huffmanHistogram[i]);
                if (newTreeNode != NIL)
                {
                    queueOperationCheck = enqueue(queueOne, newTreeNode); // Put to prior. queue.
                    if (queueOperationCheck == false) // If failed, free to avoid mem. leak.
                    {
                        free(newTreeNode);
                    }
                }
            }
        }
        // Alloc space to hold dequeued nodes.
        dequeuedTreeNode = createArrayOfQueues();
        dequeuedTreeNodeTwo = createArrayOfQueues();
        // Below is the loop to build the huffman tree.
        do
        {
            queueOperationCheck = dequeue(queueOne, dequeuedTreeNode); // Get the smallest elem.
            queueStatusCheck = empty(queueOne);
            // If not empty, dequeue one more and join.
            if (queueOperationCheck == true && dequeuedTreeNode != NIL &&
                queueStatusCheck == false)
            {
                queueOperationCheck = dequeue(queueOne, dequeuedTreeNodeTwo);
                queueStatusCheck = empty(queueOne);
                // If empty, skip the part below and join and that is our root.
                if (queueOperationCheck == true && dequeuedTreeNodeTwo != NIL &&
                    queueStatusCheck == false)
                {
                    // Join two subtrees.
                    joinedInteriorNode = join(*dequeuedTreeNode, *dequeuedTreeNodeTwo);
                    // Pushed the joined interior node back.
                    queueOperationCheck = enqueue(queueOne, joinedInteriorNode);
                    // If enqueue failed free the node to prevent mem. leak.
                    if (queueOperationCheck == false && joinedInteriorNode != NIL)
                    {
                        free(joinedInteriorNode);
                    }
                }
                else
                {
                    // We dequeued the last element, we need to join these two and get the root.
                    joinedInteriorNode = join(*dequeuedTreeNode, *dequeuedTreeNodeTwo);
                    if (joinedInteriorNode != NIL)
                    {
                        constructedHuffmanTree = &joinedInteriorNode;
                        onlyOneElementLeftInTheQueue = true;
                    }
                }
            }
            else
            {
                // This is the last element in the priority queue. It must be the root.
                if (dequeuedTreeNode != NIL)
                {
                    constructedHuffmanTree = dequeuedTreeNode;
                    onlyOneElementLeftInTheQueue = true;
                }
            }
        } while (onlyOneElementLeftInTheQueue == false);
        code codeStack = newCode(); // Bit stack to get encoded char codes.
        buildCode(*constructedHuffmanTree, codeStack, stackTable);
        // Below, we reverse the bits so that they are in correct order.
        for (uint32_t i = 0; i < 256; i++)
        {
            if (stackTable[i].l > 0) // There is code.
            {
                for (long int j = stackTable[i].l; j >= 0; j--) // For l bits.
                {
                    uint32_t poppedBit = 3; // To differentiate from 0 and 1.
                    bool popStatusCheck = popCode(&stackTable[i], &poppedBit);
                    if (popStatusCheck == true)
                    {
                        // Next time we pop, bits will come in correct order.
                        bool pushStatusCheck = pushCode(&correctOrderedStackTable[i], poppedBit);
                        if (pushStatusCheck == false)
                        {
                            printf("\nCouldn't push the code!\n");
                        }
                    }
                }
            }
        }
    }
    // If we are given a specific file to write to.
    if (writeToStdoutFlag == false)
    {
        write(outputFileDirectory, &huffmanMagicNumber, sizeof(huffmanMagicNumber)); // Credit:DDEL
        write(outputFileDirectory, &originalFileSizeBytes, sizeof(originalFileSizeBytes));
        huffmanTreeSize = (uint16_t)queueSize; // Tree size must be written in 2 bytes.
        write(outputFileDirectory, &huffmanTreeSize, sizeof(huffmanTreeSize));
        dumpTree(*constructedHuffmanTree, outputFileDirectory); //Writes the tree in post-order.
        fileResetCheck = lseek(inputFileDirectory, 0, SEEK_SET); // Reset to beginning.
        if (fileResetCheck == -1)   // If we failed, call perror, exit and warn about the error.
        {
            perror("File reset failed!");
            exit(errno);
        }
        // Reset the variables used for the previous read.
        bytesRead = 0;
        readBufferIndex = 0;
        characterBeingReadAndPrinted = 0;
        // Read the file and save the chars in our buffer and the number of bytes we read to var.
        bytesRead = read(inputFileDirectory, readBuffer, 1);
        while (bytesRead != 0)  // Read until the EOF!
        {
            if (bytesRead == -1)    // If we failed, call perror, exit and warn about the error.
            {
                perror("Last read failed");
                exit(errno);
            }
            while (readBufferIndex != bytesRead)    // Until buffer is empty.
            {
                characterBeingReadAndPrinted = readBuffer[readBufferIndex];
                codeStackLocation = characterBeingReadAndPrinted;   // Char is also the index.
                if (correctOrderedStackTable[codeStackLocation].l > 0) // Code exist?
                {
                    // Back up the index so that we can use the code loc. as much as we want to.
                    codeStackLengthBackUp = correctOrderedStackTable[codeStackLocation].l;
                    // Save to the bit vector for l bits of the code.
                    for (long int j = correctOrderedStackTable[codeStackLocation].l; j >= 0; j--)
                    {
                        uint32_t poppedBit = 3; // To differentiate from 0 and 1.
                        bool popStatusCheck = popCode(&correctOrderedStackTable[codeStackLocation],
                                                      &poppedBit);
                        if (popStatusCheck == true && poppedBit == 1)
                        {
                            // If B.V full, extend it.
                            if (bitVectorLengthInBits >= bitVector->l)
                            {
                                reallocVec(bitVector);
                            }
                            setBit(bitVector, bitVectorLengthInBits);
                            ++bitVectorLengthInBits;
                        }
                        else if (popStatusCheck == true && poppedBit == 0) //No need to clear bit.
                        {
                            ++bitVectorLengthInBits;
                        }
                    }
                    correctOrderedStackTable[codeStackLocation].l = codeStackLengthBackUp; // Reset
                }
                ++readBufferIndex;
            }
            readBufferIndex = 0; // Reset.
            characterBeingReadAndPrinted = 0;
            bytesRead = read(inputFileDirectory, readBuffer, 1);
        }
        size_t numberOfBytesToBeCopiedBitV = 0; // How many bytes to copy from B.V.?
        if ((bitVectorLengthInBits / 8) == 0 && bitVectorLengthInBits > 0)
        {
            numberOfBytesToBeCopiedBitV = 1;
        }
        else
        {
            numberOfBytesToBeCopiedBitV = ((bitVectorLengthInBits / 8) + 1);
        }
        write(outputFileDirectory, bitVector->v, numberOfBytesToBeCopiedBitV);
    }
    else
    {
        write(1, &huffmanMagicNumber, sizeof(huffmanMagicNumber));
        write(1, &originalFileSizeBytes, sizeof(originalFileSizeBytes));
        huffmanTreeSize = (uint16_t)queueSize; // Tree size must be written in 2 bytes.
        write(1, &huffmanTreeSize, sizeof(huffmanTreeSize));
        dumpTree(*constructedHuffmanTree, 1); //Writes the tree in post-order.
        fileResetCheck = lseek(inputFileDirectory, 0, SEEK_SET); // Reset to beginning.
        if (fileResetCheck == -1)   // If we failed, call perror, exit and warn about the error.
        {
            perror("File reset failed!");
            exit(errno);
        }
        // Reset the variables used for the previous read.
        bytesRead = 0;
        readBufferIndex = 0;
        characterBeingReadAndPrinted = 0;
        // Read the file and save the chars in our buffer and the number of bytes we read to var.
        bytesRead = read(inputFileDirectory, readBuffer, 1);
        while (bytesRead != 0)  // Read until the EOF!
        {
            if (bytesRead == -1)    // If we failed, call perror, exit and warn about the error.
            {
                perror("Last read failed");
                exit(errno);
            }
            while (readBufferIndex != bytesRead)    // Until buffer is empty.
            {
                characterBeingReadAndPrinted = readBuffer[readBufferIndex];
                codeStackLocation = characterBeingReadAndPrinted;   // Char is also the index.
                if (correctOrderedStackTable[codeStackLocation].l > 0) // Code exist?
                {
                    // Back up the index so that we can use the code loc. as much as we want to.
                    codeStackLengthBackUp = correctOrderedStackTable[codeStackLocation].l;
                    // Save to the bit vector for l bits of the code.
                    for (long int j = correctOrderedStackTable[codeStackLocation].l; j >= 0; j--)
                    {
                        uint32_t poppedBit = 3; // To differentiate from 0 and 1.
                        bool popStatusCheck = popCode(&correctOrderedStackTable[codeStackLocation],
                                                      &poppedBit);
                        if (popStatusCheck == true && poppedBit == 1)
                        {
                            // If B.V full, extend it.
                            if (bitVectorLengthInBits >= bitVector->l)
                            {
                                reallocVec(bitVector);
                            }
                            setBit(bitVector, bitVectorLengthInBits);
                            ++bitVectorLengthInBits;
                        }
                        else if (popStatusCheck == true && poppedBit == 0) //No need to clear bit.
                        {
                            ++bitVectorLengthInBits;
                        }
                    }
                    correctOrderedStackTable[codeStackLocation].l = codeStackLengthBackUp; // Reset
                }
                ++readBufferIndex;
            }
            readBufferIndex = 0; // Reset.
            characterBeingReadAndPrinted = 0;
            bytesRead = read(inputFileDirectory, readBuffer, 1);
        }
        size_t numberOfBytesToBeCopiedBitV = 0; // How many bytes to copy from B.V.?
        if ((bitVectorLengthInBits / 8) == 0 && bitVectorLengthInBits > 0)
        {
            numberOfBytesToBeCopiedBitV = 1;
        }
        else
        {
            numberOfBytesToBeCopiedBitV = ((bitVectorLengthInBits / 8) + 1);
        }
        write(1, bitVector->v, numberOfBytesToBeCopiedBitV);
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
        bitCountEncoded = bitVectorLengthInBits;
        printf("Original %lu bits: leaves %u (%u bytes) encoding %lu bits.\n",
               bitCount, numberOfActiveSymbolsInTheHistogram, queueSize, bitVectorLengthInBits);
    }
    free(inputFile);
    if (writeToStdoutFlag == false) // If we opened a file to write, free the path name.
    {
        free(outputFile);
    }
    free(dequeuedTreeNode);
    free(dequeuedTreeNodeTwo);
    free(*constructedHuffmanTree);
    delVec(bitVector);
    delQueue(queueOne);
    return 0;
}

// Allocates space for a pointer to a huffman tree.
treeItemPointer *createArrayOfQueues()
{
    static uint32_t newAoPCapacity = 1;
    treeItemPointer *newAoP = NIL;
    newAoP = (treeItemPointer *)calloc(newAoPCapacity, sizeof(treeItemPointer));
    if (newAoP != NIL)
    {
        return newAoP;
    }
    return NIL;
}