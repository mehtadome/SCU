#include "database.h"

using namespace coen79_lab7;

int main(int argc, const char * argv[]) {

    std::cout << "\nTesting constructor and company insert!\n";
    database myDB1;
    myDB1.insert_company("Google");

    std::cout << "\nTesting inserting 2 items\n";
    myDB1.insert_item("Google", "Pixel", 200.0);
    myDB1.insert_item("Google", "Pixel 2", 300.0);

    std::cout << "\nPrint all items for company1\n";
    myDB1.print_items_by_company("Google");

    std::cout << "\nBasic erase items test\n";
    myDB1.erase_item("Google", "Pixel");
    myDB1.erase_item("Google", "Pixel 2");

    std::cout << "\nInsert to recently empty list test\n";
    myDB1.insert_item("Google", "Pixel 3", 400.00);

    std::cout << "\nPrint all items after erase and reinsert\n";
    myDB1.print_items_by_company("Google");

    std::cout << "\n----------------------------\n";

    std::cout << "\nTesting operator= for database2 and print\n";
    database *myDB2 = new database();
    (*myDB2) = myDB1;

    myDB2->print_items_by_company("Google");

    std::cout << "\nTesting insert into DB2\n";
    myDB2->insert_item("Google", "Pixel 4", 10000.00);

    std::cout << "\nPrint both databases (should be different)\n";

    std::cout << "DB1\n";
    myDB1.print_items_by_company("Google");
    std::cout << "-----\n\n";
    std::cout << "DB2\n";
    myDB2->print_items_by_company("Google");

    std::cout << "\n----------------------------\n";

    std::cout << "\nTesting copy constructor from DB2 to DB3\n";
    database myDB3(*myDB2);

    std::cout << "DB3\n";
    myDB3.print_items_by_company("Google");

    std::cout << "\n erase company from database3 and print\n";
    myDB3.erase_company("Google");

    myDB3.print_items_by_company("Google");

    std::cout << "\nDatabase destructor test\n";

    delete myDB2;

    return 0;
}
