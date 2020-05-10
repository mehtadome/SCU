#include "keyed_bag.h"

namespace Coen79_Lab4 {


// erases all the items and keys in the bag
void keyed_bag::erase() {
    for(int i = 0; i < used; ++i){
        values[i] = NULL;
        keys[i] = "deleted";
    }
    used = 0;
}

// delete a certain key and its value
bool keyed_bag::deleteElement(const key_type &key){
    bool checker = false;   // checker for when element is found

    // if the key exists, delete it
    if (has_key(key) == true) {
        // start where the element is
        for (int i = 0; i < used; i++) {

            // once the key wanted is equal to target key
            if (key == keys[i]) {
                checker = true;
            }

            //  only shift once the key's element is reached
            if (checker == true){
                // shift everything to the left
                values[i] = values[i+1];
                keys[i] = keys[i+1];
            }
            
        }
        used -= 1;
        return true;
    } else {
        // return false if there is no such key
        return false;
    } 
}

// insert an entry and key into their respective arrays
void keyed_bag::insert(const value_type &entry, const key_type &key){
    assert(size() < CAPACITY && has_key(key) == false);
    keys[used] = key;
    values[used] = entry;
    used+=1;
}

// += overload
void keyed_bag::operator +=(const keyed_bag &addend){
    assert( size() + addend.size() < CAPACITY);

    for (int i = 0; i < addend.used; ++i){
        // if the keys are the same, skip it
        if (has_key(addend.keys[i]) == false){
            keys[used] = addend.keys[i];
            values[used] = addend.values[i];
            used += 1;
        }
    }
}

// Constant Member Functions
bool keyed_bag::has_key(const key_type &key) const {
    // search to see if keys match, also store place in array, for insertion or deletion
    for (int i = 0; i < used; ++i){
        if (key == keys[i]){
            // indexInArray = i;
            return true;
        }
    }
    return false;
}

// return the value for the key specified
keyed_bag::value_type keyed_bag::get(const key_type &key) const{
    // if true, get the value for the key
    assert(has_key(key));
    for (int i = 0; i < used; ++i) {
        if (keys[i] == key){
            return values[i];
        }
    }
    return NULL;
}

// returns how many times target is in the bag
keyed_bag::size_type keyed_bag::count(const value_type &target) const{
    int count = 0;
    for (int i = 0; i < used; ++i){
        // increment count if target is equal to data value
        if (target == values[i]){
            count+=1;
        }
    }
    return count;
}

// check if another bag has the same key specified
bool keyed_bag::hasDuplicateKey(const keyed_bag &otherBag) const{
    for (int i = 0; i < otherBag.used; ++i){
        if ( has_key(otherBag.keys[i]) ){
            return true;
        }
    }
    return false;
}

keyed_bag operator+(const keyed_bag &b1, const keyed_bag &b2){
    assert(b1.size() + b2.size() <= keyed_bag::CAPACITY);
    keyed_bag addedBag;
    addedBag += b1;
    addedBag += b2;

    return addedBag;
}

} // namespace end