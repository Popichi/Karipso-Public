#include <iostream>
#include <string>

// Create a node struct
struct node {
    std::string data;
    node* next;
};

class stack {
    public:
        stack();     // Constructor
        ~stack();    // Destructor

        // Pushes a node onto the top of stack
        void push(std::string d);

        // Pop top node off of the stack
        std::string pop();

        // Display the stack's contents as a string (top->bottom)
        std::string to_string();
        bool is_empty();

    private:
        node* top;
};

// Initialize stack to be empty
stack::stack() {
    top = NULL;
}

// Deconstructor to delete all of the dynamic variables
stack::~stack() {
    while (!is_empty()) {
        pop();
    }
}

void stack::push(std::string d) {
    // Need a new node to store d in
    node* temp = new node;
    temp->data = d;

    // Point the new node's next to the old top of the stack
    temp->next = top;
    top = temp;    // Point top to the new top of the stack
}

std::string stack::pop() {
    if (!(is_empty())) {
        std::string value = top->data;
        node* pre_top = top;
        top = pre_top->next;
        delete pre_top;
        return value;
    } else {
        std::cout << "You can't pop from an empty stack!" << std::endl;
        exit(1);
    }
}

std::string stack::to_string() {
    std::string result = "(top) -> ";
    if (is_empty()) {
        result += "NULL";
        return result;
    } else {
        node* current = top;
        while (current != NULL) {
            result += current->data + " -> ";
            current = current->next;
        }
        result += " (END)";
        return result;
    }
    return result;
}

bool stack::is_empty() {
    return (top == NULL);
}

int main() {
    stack* s = new stack();
    std::cout << "Output when empty: " <<  std::endl
        << s->to_string() << std::endl;
    s->push("Cheeseburger");
    s->push("Pizza");
    s->push("Large coffee");
    s->pop();
    s->pop();
    s->pop();

    std::cout << "Output when not empty: " <<  std::endl
        << s->to_string() << std::endl;

    delete s;
    return 0;
}

