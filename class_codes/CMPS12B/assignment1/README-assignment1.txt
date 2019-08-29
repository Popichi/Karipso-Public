#############################################
# Anil Celik Maral - amaral
# amaral@ucsc.edu
# 1454995
# Assignment - 1
# Lab: Friday, 9:00am - 10:00am
# Lab Partner: None
# Date: 04/22/17
###############################################

Files submitted for assignment - 1 are: bv.h, bv.c, sieve.h, sieve.c, parfait.c and Makefile.
These are the only files to compile the code.

-How the program works-

The program starts by creating the required variables to find prime, composite and perfect numbers.
The most important of these are the length of the bit vector, which is also the upper bound for the
numbers that will be checked, the array for divisors of composite numbers, which contain only the
prime divisors, and the arrary for divisors of perfect numbers which contain all the divisors of
the number expect itself. We create a bit vector that has as many bits as the specified length,
which defaults to 100,000. Afterward, give use function sieve to manipulate the bit vector so that
the bits that are 1 represent the prime numbers and the bits that are 0 represent the composite
numbers. This helps us tremendously because with the knowledge of prime numbers in a given list,
we are able to cut a huge amount of work that would otherwise slow our program significantly.
Since the prime numbers don't have any other divisors othen than themselves and 1, we don't do
any check on them. Instead, we immediately print the number and say it is a prime number. We start
checking for composite numbers by assuming that they are not perfect. Then, we initialize the
variable that are needed while checking and later printing. We keep track of how many divisors a
number has so that we can print them correctly later. Composite numbers only need their prime 
divisors to be printed without combining them. For example, 32 is composite and its prime 
divisors are 2,2,2,2,2. Perfect numbers need all of their divisors to be printed. We should be
careful because this means divisors other than prime divisors are also included. For example, 
28 is a perfect number and its divisors are 1, 2, 4, 7, 14. The divisors' sum is equal to the
number itself. A for loop is used to check for the number and we stop once we reach the half value
of the number that is being checked because after this point it is not possible to find a divisor
that divides the number evenly other than the number itself. Each divisor is saved to an array to
be printed later. If a number is found the be perfect, a flag is set that says the number is a
perfect number. This is determined by summing all the the divisors that can divide the number being
checked evenly. Afterward, all the numbers are factorized to their prime divisors including the
perfect numbers. Again, we do not go beyond half the value of the number being checked
Additionally, we need to use the quotient of the number being checked each time to correctly
factorize it to its prime factors. Once the quotient is lower than 2, we stop the check. One big
difference in this check is that we only check the prime divisors and save them into an array if
they divide the number evenly. For composite numbers, printing is done here as it is trivial to
do so. After a prime number is confirmed to divide the number, it is printed. After this check is
done, we print all of the divisors if the number is perfect. This is done by using the array that
we previously saved the divisors into. Moreover, the divisor count is used here to print only 
the correct amount of divisors. The program ends when n numbers(in this case 100,000 numbers) are
checked. The allocated memory spaces are free()d. For manipulations such as checking certain bits,
the bit vector(bv.h) library is used.
