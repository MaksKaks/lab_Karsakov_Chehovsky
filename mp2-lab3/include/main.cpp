#include "trees.h"
#include "map.h"
#include <exception>
#include <iostream>
#include <string>


using namespace std;
int main() {
    Tree23<int, string> tree;
    tree.Insert(10, "ten");
    cout << "insert 10:" << endl;
    tree.Print();
    cout << endl;
    
    tree.Insert(5, "five");
    cout << "insert 5:" << endl;
    tree.Print();
    cout << endl;
    
    tree.Insert(15, "fifteen");
    cout << "insert 15:" << endl;
    tree.Print();
    cout << endl;
    
    tree.Insert(7, "seven");
    cout << "insert 7:" << endl;
    tree.Print();
    cout << endl;
    
    tree.Insert(12, "twelve");
    cout << "insert 12:" << endl;
    tree.Print();
    cout << endl;
    tree.Delete(15);
    tree.Print();
    cout << endl;










    cout << "Size: " << tree.Count() << endl;
    cout << "Keys: ";
    for (int k : tree.keys()) {
        cout << k << " ";
    }
    cout << endl;
    
    return 0;
}