#include <iostream>

struct Node {
    string val;
    Node* next;
    Node(string _val) : val(_val), next(nullptr){}
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
