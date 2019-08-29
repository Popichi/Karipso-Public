#############################################
# Anil Celik Maral - amaral
# amaral@ucsc.edu
# 1454995
# Lab-1
# Lab: Friday, 9:00am - 10:00am
# Lab Partner: None
#############################################

Files that are submitted for lab1: hello.c, cat.c, README-lab1.txt and files that are used in cat
which are ed, edd and eddie. Additionally, these files should be viewed using vim as they were
formatted using vim.

Note:In my makefile and cat.c, I used function, structures and examples that we given in the
lab manual. Therefore, there may be a lot of similarities within these files to the examples
that we provided. I am writing this to avoid any plaigiarism problems.

hello.c: This file contains the source code that is required to get the output
"Hello, world!" which it prints.

cat.c: The first important feature of the program is the variable 'bytesRead' which is of type
ssize_t. This type is similar to size_t but is signed. It can be considered as an int but 
actually shouldn't be treated as one. This variable is used by the 'read' function to save the
number of bytes that were read in the file that was opened. This is the case only when the
function is able to read correctly. If there is an error '-1' is set as to indicate the error.
Secondly, you can see a character array named that is named 'buffer' and 1024 bytes long. This
array is used by 'read' function to save the characters that were read in the file. We later
use this array to print the contents of the files. Thirdly, we store the file names in a
variable called 'fileName' so that the user can give in as many arguments as needed and the
function will work as the code is not hardcoded. The main flow of the function is as following:
We have a for loop that starts at the 'index = 1' because otherwise we would get the './cat'
string as an input. However, we only want to deal with the files. This for loop ends after
all of the arguments are passed in and processed. For example, './cat ed edd eddie' would have
only 'ed', 'edd' and 'eddie' as arguments. As implied previously, the program uses sprintf to
store the file name in an array to open the desired files using the open function. We check for
errors incase there is a problem. If we fail to open the file, we call 'perror' and then we call
'exit' to warn the user about the error. The error checking for other functions is exactly the 
similar with only difference being the different flags used. After opening the file, we read it.
The 'read' function only reads as many bytes as the buffer is so the max file lenght must be less
than or equal to the size of the array. We record the number of bytes that the function detected
to later use this as the check for our printing algorithm. We only print as many bytes as we read.
This helps us prevent the problem of accidentally reading more bytes than we should as we don't
know what are the values kept in certain places of the array. The reason is that they are
uninitialized. We have declarations before our printing algorithm so that they automatically reset
before entering the while loop. Here, we print what is stored in the buffer and increment our index
until it is equal to the number of bytes we read. After we are done printing, we close the file that
we previously opened so that we can open another one without any problems while we use
'fileDirectory' variable. After all of the arguments are passed in and processed, we return 0 to
indicate that the function was successful.
