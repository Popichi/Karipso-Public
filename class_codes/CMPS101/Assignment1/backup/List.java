/*###############################################
# Name: Anil Celik Maral
# Cruz ID: amaral
# amaral@ucsc.edu
# Student ID: 1454995
# CMPS101, Programming Assignment-1(pa1)
# Date: 10/09/17
###############################################*/

class List
{
    private class Node
    {
        // Fields
        int data;
        Node next;
        Node previous;
      
        // Constructor
        Node(int data) 
        {
            this.data = data;
            next = null;
            previous = null;
        }
      
        // toString():  overrides Object's toString() method
        public String toString()
        { 
            return String.valueOf(data); 
        }
      
        // equals(): overrides Object's equals() method
        public boolean equals(Object x)
        {
            boolean eq = false;
            Node that;
            if(x instanceof Node)
            {
                that = (Node) x;
                eq = (this.data == that.data);
            }
            return eq;
        }
   }

    // Fields
    private Node front;
    private Node back;
    private Node cursor;
    private int length;
    private int index;

    // Constructor
    List() // Creates a new empty list.
    { 
        front = back = cursor = null; 
        length = 0;
        index = -1;
    }

    // Access Functions --------------------------------------------------------

    // Returns true if this List is empty, false otherwise.
    boolean isEmpty()
    { 
        return length == 0; 
    }

    // Returns the number of elements in this List.
    int length()
    {
        return length; 
    }

    // If cursor is defined, returns the index of the cursor element, otherwise returns -1.
    // Precondition: cursor != null(cursor is defined).
    int index()
    {
        if (cursor != null)
        {
            return index;
        }
        return -1;
    }

    // Returns front element.
    // Precondition: !this.isEmpty() which means length() > 0.
    int front()
    {
        if(this.isEmpty()) // if length() == 0.
        {
            throw new RuntimeException("List Error: front() is called on an empty List.");
        }
        return front.data;
    }

    // Returns back element.
    // Precondition: !this.isEmpty() which means length() > 0.
    int back()
    {
        if(this.isEmpty()) // if length() == 0.
        {
            throw new RuntimeException("List Error: back() is called on an empty List.");
        }
        return back.data;
    }

    // Returns cursor element.
    // Precondition: length()>0, index()>=0.
    int get()
    {
        int cursorIndex = this.index();
        if(!this.isEmpty() && cursorIndex >= 0) // if length() !=0 and index >= 0.
        {
            return cursor.data;
        }
        else
        {
            throw new RuntimeException("List Error: get() called on an empty List or index < 0.");
        }
    }

    // Returns true if and only if this List and L are the same
    // integer sequence. The states of the cursors in the two Lists
    // are not used in determining equality.
    // Overrides Object's equals() method.
    public boolean equals(Object x)
    {
        boolean eq  = false;
        List Q;
        Node N, M;
        if(x instanceof List)
        {
            Q = (List)x;
            N = this.front;
            M = Q.front;
            eq = (this.length == Q.length);
            while(eq && N!=null)
            {
                eq = N.equals(M);
                N = N.next;
                M = M.next;
            }
        }
        return eq;
    }

   // Manipulation Procedures -------------------------------------------------

    // Resets this List to its original empty state if it exists, otherwise does nothing.
    void clear()
    {
        if(!this.isEmpty()) // If the list is not empty.
        {
            front = back = cursor = null; 
            length = 0;
            index = -1;
        }
        return;
    }

    // If List is non-empty, places the cursor under the front element, otherwise does nothing.
    void moveFront()
    {
        if(!this.isEmpty()) // If the list is not empty.
        {
            cursor = front;
            index = 0;
        }
        return;
    }

    // If List is non-empty, places the cursor under the back element, otherwise does nothing.
    void moveBack()
    {
        if(!this.isEmpty()) // If the list is not empty.
        {
            cursor = back;
            index = (length - 1);
        }
        return;
    }
    
    // If cursor is defined and not at front, moves cursor one step toward
    // front of this List, if cursor is defined and at front, cursor becomes
    // undefined, if cursor is undefined does nothing.
    void movePrev()
    {
        if(cursor != null && cursor != front)
        {
            Node cursorNode = null;
            cursorNode = cursor;
            cursorNode = cursorNode.previous;
            cursor = cursorNode;
            index += -1;
        }
        else if(cursor != null && cursor == front)
        {
            cursor = null;
            index = -1;
        }
        return;
    }

    // If cursor is defined and not at back, moves cursor one step toward
    // back of this List, if cursor is defined and at back, cursor becomes
    // undefined, if cursor is undefined does nothing.
    void moveNext()
    {
        if(cursor != null && cursor != back)
        {
            Node cursorNode = null;
            cursorNode = cursor;
            cursorNode = cursorNode.next;
            cursor = cursorNode;
            index += 1;
        }
        else if(cursor != null && cursor == back)
        {
            cursor = null;
            index = -1;
        }
        return;
    }

    // Insert new element into this List. If List is non-empty,
    // insertion takes place before front element.
    void prepend(int data)
    {
        Node newNode = new Node(data);
        int cursorIndex = this.index();
        if(!this.isEmpty()) // If the list is not empty.
        {
            newNode.previous = null;
            newNode.next = front;
            front.previous = newNode;
            front = newNode;
            if (length == 1)
            {
                back = newNode.next;
            }
        }
        else // If the list is empty.
        {
            newNode.previous = null;
            newNode.next = null;
            front = back = newNode;
        }
        if (cursorIndex != -1)
        {
            index += 1;
        }
        length += 1;
        return;
    }

    // Insert new element into this List. If List is non-empty,
    // insertion takes place after back element.
    void append(int data)
    {
        Node newNode = new Node(data);
        if(!this.isEmpty()) // If the list is not empty.
        {
            newNode.previous = back;
            newNode.next = null;
            back.next = newNode;
            back = newNode;
            if(length == 1)
            {
                front = newNode.previous;
            }
        }
        else // If the list is empty.
        {
            newNode.previous = null;
            newNode.next = null;
            front = back = newNode;
        }
        length += 1;
        return;
    }
    
    // Insert new element before cursor.
    // Pre: length()>0, index()>=0
    void insertBefore(int data)
    {
        Node newNode = new Node(data);
        int cursorIndex = this.index();
        if(!this.isEmpty() && cursorIndex >= 0) // if length() !=0 and index >= 0.
        {
            if(cursor == front) // Cursor is defined and at the front, prepend!
            {
                this.prepend(data);
            }
            else if(cursor == back) // Cursor defined and at the back, put it before back element.
            {
                newNode.previous = back.previous;
                back.previous.next = newNode;
                back.previous = newNode;
                newNode.next = back;
                index += 1;
                length += 1;
            }
            else // Cursor is defined and somewhere in the middle
            {
                newNode.previous = cursor.previous;
                cursor.previous.next = newNode;
                cursor.previous = newNode;
                newNode.next = cursor;
                index += 1;
                length += 1;
            }
        }
        else
        {
            throw new RuntimeException(
            "List Error: insertBefore() called on an empty List or index < 0.");
        }
        return;
    }

    // Inserts new element after cursor.
    // Pre: length()>0, index()>=0
    void insertAfter(int data)
    {
        Node newNode = new Node(data);
        int cursorIndex = this.index();
        if(!this.isEmpty() && cursorIndex >= 0) // if length() !=0 and index >= 0.
        {
            if(cursor == back) // Cursor is defined and at the back, append!
            {
                this.append(data);
            }
            else if(cursor == front) // Cursor defined and at the back, put it before back element.
            {
                front.next.previous = newNode;
                newNode.next = front.next;
                front.next = newNode;
                newNode.previous = front;
                index += 1;
                length += 1;
            }
            else // Cursor is defined and somewhere in the middle
            {
                newNode.next = cursor.next;
                newNode.previous = cursor;
                cursor.next.previous = newNode;
                cursor.next = newNode;
                index += 1;
                length += 1;
            }
        }
        else
        {
            throw new RuntimeException(
            "List Error: insertAfter() called on an empty List or index < 0.");
        }
        return;
    }

    // Deletes the front element. Pre: length()>0.
    void deleteFront()
    {
        Node frontTemp;
        int cursorIndex = this.index();
        if(!this.isEmpty()) // if length() != 0.
        {
            if(front == back)
            {
                this.clear();
                return;
            }
            frontTemp = front;
            front.next.previous = null;
            if(cursorIndex != -1)
            {
                if(cursor == front)
                {
                    cursor = null;
                    index = -1;
                }
                else
                {
                    index += -1;
                }
            }
            front = front.next;
            frontTemp = null;
            length += -1;
        }
        return;
    }

    // Deletes the back element. Pre: length()>0
    void deleteBack()
    {
        Node backTemp;
        int cursorIndex = this.index();
        if(!this.isEmpty()) // if length() != 0.
        {
            if(back == front)
            {
                this.clear();
                return;
            }
            backTemp = back;
            back.previous.next = null;
            if(cursorIndex != -1)
            {
                if(cursor == back)
                {
                    cursor = null;
                    index = -1;
                }
            }
            back = back.previous;
            backTemp = null;
            length += -1;

        }
        return;
    }

    // Deletes cursor element, making cursor undefined.
    // Pre: length()>0, index()>=0
    void delete()
    {
        int cursorIndex = this.index();
        if(!this.isEmpty() && cursorIndex >= 0) // if length() !=0 and index >= 0.
        {
            if(cursor == front)
            {
                this.deleteFront();
            }
            else if(cursor == back)
            {
                this.deleteBack();
            }
            else // Cursor is somewhere in the middle.
            {
                cursor.previous.next = cursor.next;
                cursor.next.previous = cursor.previous;
                cursor = null;
                index = -1;
                length += -1;
            }
        }
        return;
    }

    // Other Methods ---------------------------------------------------------

    // Overrides Object's toString method. Returns a String
    // representation of this List consisting of a space
    // separated sequence of integers, with front on left.
    public String toString()
    {
        int notInTheBeginning = 0;
        StringBuffer sb = new StringBuffer();
        Node N = front;
        while(N != null)
        {
            if(notInTheBeginning == 0)
            {
                notInTheBeginning = -1;
            }
            else
            {
                sb.append(" ");
            }
            sb.append(N.toString());
            N = N.next;
        }
        return new String(sb);
    }

    // Returns a new List representing the same integer sequence as this
    // List. The cursor in the new list is undefined, regardless of the
    // state of the cursor in this List. This List is unchanged.
    // Returns a new List identical to this List.
    List copy()
    {
        List Q = new List();
        Node N = this.front;
        while(N != null)
        {
            Q.append(N.data);
            N = N.next;
        }
        return Q;
   }
}