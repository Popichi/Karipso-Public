/*###############################################
# Name: Anil Celik Maral
# Cruz ID: amaral
# amaral@ucsc.edu
# Student ID: 1454995
# CMPS101, Programming Assignment-3(pa3)
# Date: 10/30/17
###############################################*/

class Matrix
{
    private class Entry
    {
        // Fields
        int column;
        double value;

        // Constructor
        Entry(int column, double value)
        {
            this.value = value;
            this.column = column;
        }
      
        // toString():  overrides Object's toString() method
        public String toString()
        { 
            String entryString = "(" + column + ", " + value + ")";
            return entryString;
        }
      
        // equals(): overrides Object's equals() method
        public boolean equals(Object x)
        {
            boolean eq = false;
            Entry that;
            if(x instanceof Entry)
            {
                that = (Entry) x;
                eq = ((this.column == that.column) && (this.value == that.value));
            }
            return eq;
        }
    }

    // Fields
    private List[] row;
    private int rowAndColumnSize;

    // Constructor
    // Makes a new n x n zero Matrix. pre: n>=1
    Matrix(int n)
    {
        if(n < 1)
        {
            throw new RuntimeException("Matrix Error: Matrix() was called with a size n < 1");
        }
        row = new List[n + 1];
        rowAndColumnSize = n;
        int i = 0;
        int j = 0;
        for (i = 0; i < rowAndColumnSize + 1; i++) 
        {
            row[i] = new List();
        }
    }


    // Access functions

    // Returns n, the number of rows and columns of this Matrix
    int getSize()
    {
        return rowAndColumnSize;
    }

    // Returns the number of non-zero entries in this Matrix
    int getNNZ()
    {
        int numberOfNonZeroEntries = 0;
        for (int i = 1; i < rowAndColumnSize + 1; i++)
        {
            for(row[i].moveFront(); row[i].index() >= 0; row[i].moveNext())
            {
                ++numberOfNonZeroEntries;
            }
        }
        return numberOfNonZeroEntries;
    }

    // overrides Object's equals() method.
    public boolean equals(Object x)
    {
        boolean eq  = false;
        Matrix Q;
        Entry E, N;
        if(x instanceof Matrix)
        {
            Q = (Matrix)x;
            if(!(this.rowAndColumnSize == Q.rowAndColumnSize))
            {
                return eq;
            }
            else if(this.getNNZ() == 0 && Q.getNNZ() == 0)
            {
                return eq = true;
            }
            for (int i = 1; i < rowAndColumnSize + 1; i++)
            {
                Q.row[i].moveFront();
                for(this.row[i].moveFront(); this.row[i].index() >= 0 || Q.row[i].index() >= 0;)
                {
                    if(this.row[i].index() < 0 || Q.row[i].index() < 0)
                    {
                        eq = false;
                        return eq;
                    }
                    E = (Entry)this.row[i].get();
                    N = (Entry)Q.row[i].get();
                    Q.row[i].moveNext();
                    this.row[i].moveNext();
                    eq = E.equals(N);
                    if(!eq)
                    {
                        return eq;
                    }
                }
            }
        }
        return eq;
    }


    // Manipulation procedures

    // sets this Matrix to the zero state
    void makeZero()
    {
        for (int i = 1; i < rowAndColumnSize + 1; i++)
        {
            for (int j = 1; j < rowAndColumnSize + 1; j++)
            {
                changeEntry(i, j, 0);
            }
        }
        return;
    }

    // returns a new Matrix having the same entries as this Matrix.
    Matrix copy()
    {
        Matrix copyMatrix = new Matrix(this.rowAndColumnSize);
        Entry E = null;
        for (int i = 1; i < this.rowAndColumnSize + 1; i++)
        {
            for(this.row[i].moveFront(); this.row[i].index() >= 0; this.row[i].moveNext())
            {
                E = (Entry)this.row[i].get();
                Entry newEntry = new Entry(E.column, E.value);
                copyMatrix.row[i].append(newEntry);
            }
        }
        return copyMatrix;
    }

    // changes ith row, jth column of this Matrix to x
    // pre: 1<=i<=getSize(), 1<=j<=getSize()
    void changeEntry(int i, int j, double x)
    {
        if(!(1 <= i && i <= getSize()) && !(1 <= j && j <= getSize()))
        {
            throw new RuntimeException
            ("Matrix Error: changeEntry() called with i or j out of boundaries.");
        }
        Entry E = null;
        boolean weFoundJ = false;
        boolean thereIsAGreaterColumnThanJ = false;
        for(row[i].moveFront(); row[i].index() >= 0; row[i].moveNext())
        {
            E = (Entry)row[i].get();
            if(E.column == j)
            {
                weFoundJ = true;
                break;
            }
            else if(E.column > j)
            {
                thereIsAGreaterColumnThanJ = true;
                break;
            }
        }
        if(weFoundJ == false && x == 0)
        {
            return;
        }
        else if(weFoundJ == false && x != 0)
        {
            Entry newEntry = new Entry(j, x);
            // I can do this because I break the loop as soon as I reach the Entry with the greater
            // column.So, I insert right before that element in the list pointed by row[i].
            // cursor is at the entry with the greater column.
            if(thereIsAGreaterColumnThanJ == true)
            {
                row[i].insertBefore(newEntry);
            }
            // Now I know that there no column greater than J. There is either no non-zero elements
            // or all of them are stored in a column less than J. Either way, I don't care.
            // We just append the new entry.
            else // if(thereIsAGreaterColumnThanJ == false)
            {
                row[i].append(newEntry);
            }
        }
        // Here we found the column j and we delete it as it will become a zero element.
        // We can directly call delete() because we break the loop as soon as we find column j.
        // cursor in at the entry we will be deleting.
        else if(weFoundJ == true && x == 0)
        {
            row[i].delete();
        }
        // We can directly overwrite the value because we break the loop as soon as we find
        // column j. cursor in at the entry we will be deleting.
        else // if(weFoundJ == true && x != 0)
        {
            E.value = x;
        }
        return;
    }

    // returns a new Matrix that is the scalar product of this Matrix with x.
    Matrix scalarMult(double x)
    {
        Matrix scalarMultMatrix = new Matrix(this.rowAndColumnSize);
        Entry E = null;
        for (int i = 1; i < this.rowAndColumnSize + 1; i++)
        {
            for(this.row[i].moveFront(); this.row[i].index() >= 0; this.row[i].moveNext())
            {
                E = (Entry)this.row[i].get();
                Entry newEntry = new Entry(E.column, (x * E.value));
                scalarMultMatrix.row[i].append(newEntry);
            }
        }
        return scalarMultMatrix;
    }

    // returns a new Matrix that is the sum of this Matrix with M
    // pre: getSize()==M.getSize()
    Matrix add(Matrix M)
    {
        if(this.getSize() !=  M.getSize())
        {
            throw new RuntimeException("Matrix Error: add() called with thisSize !=  MSize");
        }
        Matrix addMatrix = new Matrix(M.rowAndColumnSize);
        for (int i = 1; i < this.rowAndColumnSize + 1; i++)
        {
            addMatrix.sumARow(this.row[i], M.row[i], i);
        }
        return addMatrix;
    }

    // returns a new Matrix that is the difference of this Matrix with M
    // pre: getSize()==M.getSize()
    Matrix sub(Matrix M)
    {
        if(this.getSize() !=  M.getSize())
        {
            throw new RuntimeException("Matrix Error: sub() called with thisSize !=  MSize");
        }
        Matrix subMatrix = new Matrix(M.rowAndColumnSize);
        for (int i = 1; i < this.rowAndColumnSize + 1; i++)
        {
            subMatrix.subARow(this.row[i], M.row[i], i);
        }
        return subMatrix;
    }

    // returns a new Matrix that is the transpose of this Matrix.
    Matrix transpose()
    {
        Matrix transposeMatrix = new Matrix(this.rowAndColumnSize);
        Entry E = null;
        for (int i = 1; i < this.rowAndColumnSize + 1; i++)
        {
            int j = 1;
            for(this.row[i].moveFront(); this.row[i].index() >= 0; this.row[i].moveNext())
            {
                E = (Entry)this.row[i].get();
                Entry newEntry = new Entry(E.column, E.value);
                int correctRow = E.column;
                newEntry.column = i;
                transposeMatrix.row[correctRow].append(newEntry);
                ++j;
            }
        }
        return transposeMatrix;
    }

    // returns a new Matrix that is the product of this Matrix with M
    // pre: getSize()==M.getSize()
    Matrix mult(Matrix M)
    {
        if(this.getSize() !=  M.getSize())
        {
            throw new RuntimeException("Matrix Error: mult() called with thisSize !=  MSize");
        }
        Matrix transposeM = new Matrix(M.rowAndColumnSize);
        Matrix multMatrix = new Matrix(M.rowAndColumnSize);
        transposeM = M.transpose();
        double dotSum = 0;
        for (int i = 1; i < this.rowAndColumnSize + 1; i++)
        {
            for (int j = 1; j < rowAndColumnSize + 1; j++)
            {
                dotSum = dot(this.row[i], transposeM.row[j]);
                multMatrix.changeEntry(i, j, dotSum);
            }
        }
        return multMatrix;
    }

    // Other functions
    public String toString() // overrides Object's toString() method
    {
        int i = 0;
        int j = 0;
        boolean notInTheBeginning = true;
        boolean thisRowHasColumns = false;
        StringBuffer sb = new StringBuffer();
        Entry E = null;
        for (i = 1; i < rowAndColumnSize + 1; i++)
        {
            notInTheBeginning = true;
            thisRowHasColumns = false;
            for(row[i].moveFront(); row[i].index() >= 0; row[i].moveNext())
            {
                E = (Entry)row[i].get();
                if(notInTheBeginning == true)
                {
                    sb.append(i + ": ");
                    notInTheBeginning = false;
                }
                else
                {
                    sb.append(" ");
                }
                sb.append(E.toString());
                thisRowHasColumns = true;
            }
            if(thisRowHasColumns == true)
            {
                sb.append("\n");
            }
        }
        return new String(sb);
    }

    // This computes the vector dot product of two matrix rows(one is transposed so column j
    // becomes row j) represented by Lists P and Q. Returns the result of the dot product.
    // It is used inside mult() function.
    private static double dot(List P, List Q)
    {
        Entry E = null;
        Entry N = null;
        double dotSum = 0;
        Q.moveFront();
        P.moveFront();
        while(P.index() >= 0 && Q.index() >= 0)
        {
            E = (Entry)P.get();
            N = (Entry)Q.get();
            if(E.column == N.column)
            {
                dotSum += (E.value * N.value);
                Q.moveNext();
                P.moveNext();
            }
            else if(E.column < N.column)
            {
                P.moveNext();
            }
            else // if(E.column > N.column)
            {
                Q.moveNext();
            }
        }
        return dotSum;
    }
    
    // This function sums a row of Matrix A and Matrix B for A + B and inserts them to their
    // appropriate places in the resulting sum Matrix. It is used in add().
    private void sumARow(List P, List Q, int k)
    {
        Entry E = null;
        Entry N = null;
        double sum = 0;
        boolean nIsInitialized = false, eIsInitialized = false;
        Q.moveFront();
        P.moveFront();
        while(P.index() >= 0 || Q.index() >= 0)
        {
            if(P.index() >= 0 && Q.index() >= 0)
            {
                E = (Entry)P.get();
                N = (Entry)Q.get();
                nIsInitialized = true;
                eIsInitialized = true;
            }
            else if(Q.index() >= 0)
            {
                N = (Entry)Q.get();
                nIsInitialized = true;
            }
            else if(P.index() >= 0)
            {
                E = (Entry)P.get();
                eIsInitialized = true;
            }
            if(nIsInitialized == true && eIsInitialized != true)
            {
                Entry newEntry = new Entry(N.column, N.value);
                this.row[k].append(newEntry);
                Q.moveNext();
            }
            else if(nIsInitialized != true && eIsInitialized == true)
            {
                Entry newEntry = new Entry(E.column, E.value);
                this.row[k].append(newEntry);
                P.moveNext();
            }
            else if(E.column == N.column)
            {
                sum = (E.value + N.value);
                if(sum != 0)
                {
                    Entry newEntry = new Entry(E.column, sum);
                    this.row[k].append(newEntry);
                }
                if(Q != P)
                {
                    Q.moveNext();
                    P.moveNext();
                }
                else
                {
                    P.moveNext();
                }
            }
            else if(E.column < N.column)
            {
                if(P.index() < 0)
                {
                    Entry newEntry = new Entry(N.column, N.value);
                    this.row[k].append(newEntry);
                    Q.moveNext();
                }
                else
                {
                    Entry newEntry = new Entry(E.column, E.value);
                    this.row[k].append(newEntry);
                    P.moveNext();
                }
            }
            else // if(E.column > N.column)
            {
                if(Q.index() < 0)
                {
                    Entry newEntry = new Entry(E.column, E.value);
                    this.row[k].append(newEntry);
                    P.moveNext();
                }
                else
                {
                    Entry newEntry = new Entry(N.column, N.value);
                    this.row[k].append(newEntry);
                    Q.moveNext();
                }
            }
        }
        return;
    }

    // This function subtracts a row of Matrix A and Matrix B for A - B and inserts them to their
    // appropriate places in the resulting subtraction Matrix. It is used in sub().
    private void subARow(List P, List Q, int k)
    {
        Entry E = null;
        Entry N = null;
        double sub = 0;
        boolean nIsInitialized = false, eIsInitialized = false;
        Q.moveFront();
        P.moveFront();
        while(P.index() >= 0 || Q.index() >= 0)
        {
            if(P.index() >= 0 && Q.index() >= 0)
            {
                E = (Entry)P.get();
                N = (Entry)Q.get();
                nIsInitialized = true;
                eIsInitialized = true;
            }
            else if(Q.index() >= 0)
            {
                N = (Entry)Q.get();
                nIsInitialized = true;
            }
            else if(P.index() >= 0)
            {
                E = (Entry)P.get();
                eIsInitialized = true;
            }
            if(nIsInitialized == true && eIsInitialized != true)
            {
                Entry newEntry = new Entry(N.column, -N.value);
                this.row[k].append(newEntry);
                Q.moveNext();
            }
            else if(nIsInitialized != true && eIsInitialized == true)
            {
                Entry newEntry = new Entry(E.column, E.value);
                this.row[k].append(newEntry);
                P.moveNext();
            }
            else if(E.column == N.column)
            {
                sub = (E.value - N.value);
                if (!(sub == 0))
                {
                    Entry newEntry = new Entry(E.column, sub);
                    this.row[k].append(newEntry);
                }
                //else(Otherwise) do nothing.
                if(Q != P)
                {
                    Q.moveNext();
                    P.moveNext();
                }
                else
                {
                    P.moveNext();
                }
            }
            else if(E.column < N.column)
            {
                if(P.index() < 0)
                {
                    Entry newEntry = new Entry(N.column, -N.value);
                    this.row[k].append(newEntry);
                    Q.moveNext();
                }
                else
                {
                    Entry newEntry = new Entry(E.column, E.value);
                    this.row[k].append(newEntry);
                    P.moveNext();
                }
            }
            else // if(E.column > N.column)
            {
                if(Q.index() < 0)
                {
                    Entry newEntry = new Entry(E.column, E.value);
                    this.row[k].append(newEntry);
                    P.moveNext();
                }
                else
                {
                    Entry newEntry = new Entry(N.column, -N.value);
                    this.row[k].append(newEntry);
                    Q.moveNext();
                }
            }
        }
        return;
    }
}