#ifndef Keyed_Bag_H
#define Keyed_Bag_H
#include <cstdlib>
#include <string>

namespace Coen79_Lab4{

class keyed_bag{

public:
    // type of elements
    typedef int value_type;
    // keys for the bag
    typedef std::string key_type;
    // counter 
    typedef std::size_t size_type;
    // capacity
    static const size_type CAPACITY = 30;

    keyed_bag(){ used = 0; };

    void erase();
    bool deleteElement(const key_type &key);
    void insert(const value_type &entry, const key_type &key);

    // += overload
    void operator +=(const keyed_bag &addend);

    bool has_key(const key_type &key) const;
    value_type get(const key_type &key) const;
    size_type size() const { return used; };
    size_type count(const value_type &target) const;
    bool hasDuplicateKey(const keyed_bag &otherBag) const;

private:
    int indexInArray;
    size_type used;
    key_type keys[CAPACITY];
    value_type values[CAPACITY];
};

keyed_bag operator+(const keyed_bag &b1, const keyed_bag &b2);

}





#endif