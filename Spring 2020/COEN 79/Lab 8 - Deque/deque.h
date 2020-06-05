#ifndef DEQUE_H
#define DEQUE_H

//#define USEDEBUG

#ifdef USEDEBUG
#define Debug(x) std::cout << x
#else
#define Debug(x)
#endif


#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <cassert>

#include "deque_iterator.h" // The iterator class for deque (refer to file deque_iterator.h)


namespace coen79_lab8
{
template <class Item>
class deque {
public:
    
    // TYPEDEF
    static const size_t BLOCK_SIZE = 5; // Number of data items per data block
    static const size_t BLOCKPOINTER_ARRAY_SIZE = 5; // Number of entries in the array of block pointers (The minimum acceptable value is 2)
    
    typedef std::size_t size_type;
    typedef Item value_type; // The type of items stored in the deque
    
    typedef deque_iterator<Item> iterator; // A typedef to simplify the use of iterator class
    
    // CONSTRUCTOR and DESTRUCTOR
    deque(int init_bp_array_size = BLOCKPOINTER_ARRAY_SIZE, int initi_block_size = BLOCK_SIZE);
    deque(const deque& source);
    ~deque();
    
    // CONST MEMBER FUNCTIONS
    bool isEmpty();
    value_type front();
    value_type back();
    
    // ITERATOR MEMBER FUNCTIONS
    iterator begin();
    iterator end();
    
    // MODIFICATION MEMBER FUNCTIONS
    void operator=(const deque& source);
    void clear();
    void reserve();
    void push_front(const value_type& entry);
    void push_back(const value_type& entry);
    void pop_back();
    void pop_front();
    
    
private:
    
    value_type** block_pointers;      // A pointer to the array of block pointers
    value_type**  block_pointers_end; // A pointer to the final entry in the array of block pointers
    
    value_type**  first_bp;  // A pointer to the entry of the array of block pointers which points to the first data block
    value_type**  last_bp;   // A pointer to the entry of the array of block pointers which points to the last data block
    
    value_type* front_ptr;   // A pointer to the front element of the deque
    value_type* back_ptr;    // A pointer to the back element of the deque
    
    size_type bp_array_size; // Number of entries in the array of block pointers
    size_type block_size;    // Number of entries in each data block

};


// --------------------------IMPLEMENTATION ---------------------------

//CONSTRUCTOR
template <class Item>
deque<Item>::deque (int init_bp_array_size, int init_block_size) {
    
    bp_array_size = init_bp_array_size;
    block_size = init_block_size;
    
    // Create an an array of block pointers and assign its address to "block_pointers"
    block_pointers = new value_type* [BLOCK_SIZE];
    
    // Assign NULL to all the entries of the array of block pointers
    for (size_type index = 0; index < bp_array_size; ++index)
    {
        block_pointers[index] = NULL;
    }
    
    // Set block_pointers_end to point to the end of the array
    block_pointers_end = block_pointers + (bp_array_size - 1);
    
    first_bp = last_bp = NULL;
    front_ptr = back_ptr = NULL;
}


//COPY CONSTRUCTOR
template <class Item>
deque<Item>::deque (const deque<Item>& source) {
    
    first_bp = last_bp = NULL;
    front_ptr = back_ptr = NULL;
    block_pointers = block_pointers_end = NULL;
    
    // Use the assignment operator
    // (must have been already implemented, you cannot rely on the compiler)
    *this = source;
}


// ASSIGNMENT OPERATOR
template <class Item>
void deque<Item>::operator=(const deque<Item>& source) {
    
    // Invoke the clear() function
    clear();
    
    // Delete the array of block pointers
    delete [] block_pointers;
    block_pointers = NULL;
    block_pointers_end = NULL;
    
    // Copy the size variables from "source" object
    bp_array_size = source.bp_array_size;
    block_size = source.block_size;
    
    // Create a new array of block pointers
    block_pointers = new value_type*[bp_array_size]; //recalled that block pointers is a pointer to pointers initially

    // Copy the data blocks of "source" object
    for (size_type bp_array_index = 0; bp_array_index < source.bp_array_size; ++bp_array_index)
    {
        // If an entry of source.block_pointers is NULL, that entry should be NULL in this object as well
        if (source.block_pointers[bp_array_index] == NULL)
        {
            block_pointers[bp_array_index] = NULL;
        }
        else
        {
            //If this is the first_bp of source, then set the first_bp of this deque
            if(*(source.first_bp) == source.block_pointers[bp_array_index])
            {
                first_bp = bp_array_index + block_pointers; 
            }
            
            //If this is the back_ptr of source, then set the back_ptr of this deque
            if(*(source.last_bp) == source.block_pointers[bp_array_index])
            {
                last_bp = bp_array_index + block_pointers; 
            }
            
            // Create a data block
            block_pointers[bp_array_index] = new value_type [block_size];
            
            
            // Copy the elements, and set "front_ptr" and "back_ptr" if appropriate
            for (size_type block_item_index = 0; block_item_index < block_size; ++block_item_index)
            {
                if(source.block_pointers[bp_array_index] + block_item_index == source.front_ptr)
                    front_ptr = block_pointers[bp_array_index] + block_item_index; 

                if(source.block_pointers[bp_array_index] + block_item_index == source.back_ptr)
                    back_ptr = block_pointers[bp_array_index] + block_item_index; //address manipulation
                
                *(block_pointers[bp_array_index] + block_item_index) = *(source.block_pointers[bp_array_index] + block_item_index); 
            }
        }
    }
}

//DESTRUCTOR
template <class Item>
deque<Item>::~deque () {
    
    // Clear the data blocks  
    for (size_type i = 0; i < bp_array_size; ++i)
    {
        delete block_pointers[i];
        if (block_pointers[i] != NULL) { delete[] block_pointers[i]; }
    }
    
    // Clear the array of block pointers        
    delete[] block_pointers;
    first_bp = last_bp = block_pointers_end = block_pointers = NULL;
    front_ptr = back_ptr = NULL;
}


template <class Item>
void deque<Item>::clear () {
    
    // Clear the data blocks
    for (size_type index = 0; index < bp_array_size; ++index)
    {
        if (block_pointers[index] != NULL)
        {
            delete [] block_pointers[index];
            block_pointers[index] = NULL;
        }
    }
    
    first_bp = last_bp = NULL;
    front_ptr = back_ptr = NULL;
    
    // Note: The array of block pointers should not be deleted;
    //       However, all of its entries are NULL because all the
    //       data blocks have been deleted.
    
}



template <class Item>
void deque<Item>::reserve()
{
    // The new array of block pointers includes 20 more entries
    // This results in increasing the size by 20 x BLOCK_SIZE
    size_type newSize = bp_array_size + 20;
    
    // Create a new array of block pointers
    value_type** new_block_pointers = new value_type* [newSize];
    
    // Assign NULL to all the entries of the array of block pointers
    for (size_type index = 0; index < newSize; ++index)
    {
        new_block_pointers[index] = NULL;
    }
    
    // Find the location of "first_bp" in the new array of block pointers
    // The offset enables us to copy the not-NULL elements of the existing
    // array to the middle of the new array
    size_type firstOne = first_bp - block_pointers;
    size_type secondOne = last_bp - block_pointers;
    
    
    // Copy the not-NULL elements of the array of block pointers to the new array,
    // starting at the computer offset
    std::copy(first_bp, last_bp + 1, new_block_pointers + 10 + firstOne);
    
    // Delete the existing array of block pointers
    delete [] block_pointers;
    
    // Set the pointers
    block_pointers = new_block_pointers;
    bp_array_size = newSize;
    block_pointers_end = block_pointers + bp_array_size - 1;
    first_bp = block_pointers + firstOne + 10;
    last_bp = block_pointers + secondOne + 10;
}


template <class Item>
void deque<Item>::push_front(const value_type& entry) //check
{

    // Only the array of block pointers exists (and no data block exists)
    if (first_bp == NULL)
    {
        assert( bp_array_size > 1 );
        size_t bp_mid = floor(bp_array_size/2); // Get the mid point of the array of block pointers
        
        // Both last_bp and first_bp point to
        // the same location of the array of block pointers
        last_bp = first_bp = block_pointers + bp_mid - 1; //point to middle
                
        *first_bp = new value_type[block_size];
        back_ptr = front_ptr = *first_bp;
        *front_ptr = entry;
    }
    
    // There is at least one empty slot before the entry that
    // front_ptr points to (in the same data block)
    else if (front_ptr != *first_bp) //first_bp should always have one star, represent address
    {
        front_ptr--;
        *(front_ptr) = entry; //assign entry
    }
    
    // Data block has no room left before front_ptr; however,
    // the array of block pointers has at least one available
    // slot before first_bp to allocate a new data block
    else if ((*first_bp == front_ptr) && (first_bp != block_pointers))
    {
        // increment upwards
        first_bp--;
        *first_bp = new value_type[block_size];

        front_ptr = *first_bp;
        front_ptr = front_ptr + block_size - 1;
        *front_ptr = entry; 
    }
    
    // Data block has no room left before front_ptr;
    // and the array of block pointers has no available slot before first_bp
    else if ((*first_bp == front_ptr) && (first_bp == block_pointers))
    {
        // increase deque size
        reserve();
        first_bp--;
        *first_bp = new value_type[block_size];
        
        front_ptr = *first_bp;
        front_ptr = front_ptr + block_size - 1;
        *front_ptr = entry; 
    }
}


template <class Item>
void deque<Item>::push_back(const value_type& entry)
{
    // Only the array of block pointers exists (and no data block exists)
    if (last_bp == NULL)
    {
        assert( bp_array_size > 1 );
        size_t bp_mid = floor(bp_array_size/2); // Get the mid point of the array of block pointers
        
        last_bp = first_bp = block_pointers + bp_mid  - 1;
        
        back_ptr = new int [BLOCK_SIZE]; //allocate space 
        front_ptr = back_ptr;
        *(back_ptr) = entry; 

    }
    
    // There is at least one empty slot after the entry
    // that back_ptr points to (in the same data block)
    else if (back_ptr != ((*last_bp) + (block_size - 1)))
    {
        // iterate downwards
        back_ptr++; 
        *(back_ptr) = entry;
    }
    
    // Data block has no room left after back_ptr;
    // however, the array of block pointers has at least one available slot
    // below last_bp to allocate a new data block
    else if ((back_ptr == ((*last_bp) + (block_size - 1))) && (last_bp != block_pointers_end))
    {
        last_bp++;
        back_ptr = *last_bp;
        *(back_ptr) = entry; 
    }
    
    // Data block has no room left after back_ptr;
    // and the array of block pointers has no available slot after last_bp
    else if ((back_ptr == ((*last_bp) + (block_size - 1))) && (last_bp == block_pointers_end))
    {
        reserve();
        last_bp++;
        back_ptr = *last_bp; 
        *(back_ptr)= entry;
    }
}


template <class Item>
void deque<Item>::pop_front()//check
{
    assert(!isEmpty());
    
    // This is the only entry in the deque; remove it and delete the data block
    if (back_ptr == front_ptr)
    {
        clear();
    }
    // This is the last entry of the data block; move to the next block
    else if (front_ptr == ((*first_bp) + block_size - 1))
    {
        // STUDENT WORK...
        delete[] front_ptr;
        ++first_bp;
        front_ptr = (*first_bp);
    }
    // Simply move the pointer
    else
    {
        ++front_ptr;
    }
}


template <class Item>
void deque<Item>::pop_back()
{
    assert(!isEmpty());
    
    if (back_ptr == front_ptr)
    {
        clear();
    }
    else if (back_ptr == *last_bp)
    {
        // set to recent block size
        delete[] back_ptr;
        --last_bp; 
        back_ptr = (*last_bp) + (BLOCK_SIZE - 1);
    }
    else
    {
        --back_ptr;
    }
}

template <class Item>
bool deque<Item>::isEmpty()
{
    if (front_ptr == NULL){
        return true;
    }
    return false;
}

template <class Item>
typename deque<Item>::value_type deque<Item>::back()
{
    assert( !isEmpty() );
    return *back_ptr;
}

template <class Item>
typename deque<Item>::value_type deque<Item>::front()
{
    assert( !isEmpty() );
    return *front_ptr;
}

// Constructs an itertor which points to the
// first element of the deque
template <class Item>
typename deque<Item>::iterator deque<Item>::begin()
{
    value_type* tempC = NULL;
    value_type* tempCB = NULL;
    value_type** tempCBP = NULL;
    
    if (front_ptr != NULL)
    {
        tempC = front_ptr;
        tempCBP = first_bp;
        tempCB = (*first_bp) + (block_size - 1);
    }
    
    return iterator(block_pointers, block_pointers_end, first_bp, last_bp,
                    front_ptr, back_ptr,
                    bp_array_size, block_size,
                    tempC, tempCB, tempCBP);
}

// Constructs an itertor which points to the past the
// last element of the deque
template <class Item>
typename deque<Item>::iterator deque<Item>::end()
{
    value_type* tempC = NULL;
    value_type* tempCB = NULL;
    value_type** tempCBP = NULL;
    
    return iterator(block_pointers, block_pointers_end, first_bp, last_bp,
                    front_ptr, back_ptr,
                    bp_array_size, block_size,
                    tempC, tempCB, tempCBP);
}


} // namespace


#endif