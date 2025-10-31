#ifdef MAIN

#include "ABDQ.hpp"
#include "ABQ.hpp"
#include "ABS.hpp"
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include "LLDQ.hpp"
#include "LLQ.hpp"
#include "LLS.hpp"
#include <iostream>

/*
    - LEAVE THE IFDEF GUARDS TO KEEP YOUR MAIN WITHOUT CONFLICTING WITH GRADESCOPE!
    - Test your code in this main and run locally with the RunMain configuration in CLion, or
    through your own command line compilation. Make sure to add flag "-DMAIN" to your compilation so this
    main function can compile.

*/

int main() {
    // LinkedList<int> intList;
    // intList.addHead(3);
    // intList.addHead(2);
    // intList.addHead(1);
    // intList.addTail(4);
    // intList.addTail(5);

    // cout << "Forward:" << endl;
    // intList.printForward();
    // cout << "Reverse:" << endl;
    // intList.printReverse();

    // cout << "Count:" << intList.getCount() << endl;

    // intList.removeHead(); // remove 1
    // intList.removeTail(); // remove 5

    // intList.printForward();
    // cout << "Count: " << intList.getCount() << endl;

    // LinkedList<int> copyList(intList);
    // copyList.printForward();

    // LinkedList<int> assignList;
    // assignList = intList;
    // assignList.printForward();

    // LinkedList<int> movedList(std::move(intList));
    // movedList.printForward();
    // cout << intList.getCount() << endl;

    // LinkedList<int> anotherList;
    // anotherList = std::move(movedList);
    // anotherList.printForward();
    // cout << movedList.getCount() << endl; // expect: 0

    // anotherList.Clear();
    // cout << anotherList.getCount() << endl; // expect: 0

    return 0;
}


#endif