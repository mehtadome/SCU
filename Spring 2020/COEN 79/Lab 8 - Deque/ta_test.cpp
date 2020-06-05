#include <iostream>
#include "deque.h"

using namespace coen79_lab8;

int main(int argc, const char * argv[]) {

    std::cout << "Testing constructor...!\n";
    coen79_lab8::deque<int> myDeque1;

    std::cout << "\n--------\n";

    std::cout << "Testing push_back() and back()...!\n";
    for (int i = 0; i < 10; ++i)
    {
        myDeque1.push_back(i);
        std::cout << myDeque1.back() << " ";
    }

    std::cout << "\n--------\n";

    std::cout << "Testing push_front() and front()...!\n";
    for (int i = 0; i < 10; ++i)
    {
        myDeque1.push_front(i);
        std::cout << myDeque1.front() << " ";
    }

    std::cout << "\n--------\n";

    std::cout << "Testing printing with iterator...!\n";
    for (deque<int>::iterator it = myDeque1.begin(); it != myDeque1.end(); ++it)
        std::cout << *it << " ";

    std::cout << "\n--------\n";

    std::cout << "Testing pop_front()...!\n";
    myDeque1.pop_front();
    std::cout << "Front is now: " << myDeque1.front() << std::endl;;

    std::cout << "\nTesting pop_back()...!\n";
    myDeque1.pop_back();
    std::cout << "Back is now: " << myDeque1.back() << std::endl;

    std::cout << "\n--------\n";

    // PROBLEMS BELOW

    std::cout << "Testing assignment operator...!\n";
    coen79_lab8::deque<int> *myDeque2 = new coen79_lab8::deque<int>;

    myDeque2->push_front(3);
    myDeque2->push_back(4);

    // Deque2 does have elements though
    //std::cout << "Deque2 Front is now: " << myDeque2->front() << std::endl;;
    //std::cout << "Deque2 Back is now: " << myDeque2->back() << std::endl;;

    coen79_lab8::deque<int> myDeque3;
    myDeque3 = *myDeque2;


    myDeque2->pop_front();

    for (deque<int>::iterator it = myDeque3.begin(); it != myDeque3.end(); ++it)
    {
        std::cout << *it << " ";
    }
    


    std::cout << "\n--------\n";

    std::cout << "Testing copy constructor...!\n";
    coen79_lab8::deque<int> myDeque4(myDeque3);


    for (deque<int>::iterator it = myDeque4.begin(); it != myDeque4.end(); ++it)
    {
        std::cout << *it << " ";
    }

    std::cout << std::endl;

    std::cout << "\n--------\n";

    // END OF PROBLEMS

    std::cout << "Testing destructor...!\n";
    delete myDeque2;
}
