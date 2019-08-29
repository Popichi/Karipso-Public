//Author Darrell Long from UCSC.
# include       <stdio.h>

static long count = 0;

long A(long m, long n)
{
        count += 1;
        if (m == 0)
                { return n + 1; }
        else if (m > 0 && n == 0)
                { return A(m - 1, 1); }
        else
                { return A(m - 1, A(m , n - 1)); }
}

int main(void)
{
        long m, n;
        long a;

        do 
        { 
		printf("m, n: "); 
		scanf("%ld %ld", &m, &n);
        } while (m < 0 && n < 0);

        a = A(m, n);
        printf("count = %ld, A(%ld, %ld) = %ld\n", count, m, n, a);
        return 0;
}
