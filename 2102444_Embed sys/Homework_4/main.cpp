#include <iostream>
#include "Point.h"

using std::cout;
using std::endl;
using mySpace::Point;

int main()
{
    std::cout << "Hello world!\n";
    
    // create two objects on stack with default constructors
    // P1 (no argument) and P2 (one argument).
    Point P1, P2(-2);
    cout << "P1"; P1.print(); 
    cout << "P2"; P2.print(); 
    cout << endl;
    
    Point *Q; 
    // "new" command creates an object using default constructor with 2 inputs
    // Q holds a pointer of an object kept on heap 
    Q = new Point(-3,-2);
    cout << "Q"; Q->print(); 
    // destroy Q, no longer needed
    delete Q;
    cout << endl;
    // memory on heap can be allocated and deallocated at any time. 
    // But make sure you destroy it when you don't want it.

    // R holds a pointer of an object whose variables are 
    // created by the Copy constructor
    Point *R = new Point(P2);
    cout << "R"; R -> print(); 
    cout << endl;
    
    // P1 & P2 are destroyed autometically after return but
    // *R2 still occupies memory on heap
    // Can you please destroy it?
    return 0;
}
