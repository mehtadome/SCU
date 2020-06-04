#include <iostream>
#include <algorithm> //provides copy function
#include <cassert> //for assert function
#include "sequence.h" //header file for class
#include "node.h" // provides node class

using namespace std; //For copy function

namespace coen79_lab6
{
    // Default private member variable initialization function.
    void sequence::init()
    {
        //Initializing pointers to NULL
        head_ptr = NULL;
        tail_ptr = NULL;
        cursor = NULL;
        precursor = NULL;
        //Initializiing many_nodes (or our counter) to 0
        many_nodes = 0;
    }

    //CONSTRUCTOR IMPLEMENTATION for default constructor
    sequence :: sequence ()
    {
        init();
    }

    //Copy Constructor
    sequence :: sequence(const sequence& source)
    {
        init();
        *this = source;
    }

    sequence::~sequence(){
        list_clear(head_ptr);
        many_nodes = 0;
    }

    // mod member funcs
    void sequence::start()
    {
        precursor = NULL;
        cursor = head_ptr;
        return;
    }

    void sequence::end()
    {
        cursor = tail_ptr;
        // cout << "tail pointer is " << cursor -> data() << endl;

        // list of length 1
        if (head_ptr == tail_ptr)
        {
            precursor = NULL;
        } else {
            precursor = head_ptr;
            while (precursor->link() != tail_ptr){
                precursor = precursor->link();
            }
        }
        
    }


    void sequence::remove_current()
    {
        assert(is_item());
        if (cursor == head_ptr)
        {
            if (head_ptr == tail_ptr)
            {
                // one element list
                list_head_remove(head_ptr);
                cursor = NULL;
                precursor = NULL;
                tail_ptr = NULL;
                head_ptr = NULL;
            }
            else {
                // list has stuff
                list_head_remove(head_ptr);
                cursor = head_ptr;
                precursor = NULL;
            }
        } else if (cursor == tail_ptr)
        {
            // cursor at tail
            // cout << "cursor is at tail: " << precursor->data() << endl;
            list_remove(precursor);
            tail_ptr = precursor;
            precursor = NULL;
            cursor = NULL;
        } else {
            // cout  << "i ran in middle" << endl;
            // cursor in middle
            list_remove(precursor);
            cursor = cursor->link();
        }
        many_nodes--;
    }


    void sequence::advance(){
        assert(is_item());

        // if (cursor == tail_ptr)
        // {

        //     cursor = NULL;
        //     return;
        // }

        precursor = cursor;
        cursor = cursor->link();
        //cout << "\nspecial:" << cursor->data() << endl;
        return;
    }

    void sequence::insert(const value_type &entry)
    {
        if (head_ptr == NULL)
        {
            list_head_insert(head_ptr, entry);
            cursor = head_ptr;
            precursor = NULL;
            tail_ptr = head_ptr;

        } else if (is_item() && cursor == head_ptr)
        {
            list_head_insert(head_ptr, entry);
            cursor = head_ptr;
            precursor = NULL;

        } else if (is_item() && cursor != head_ptr)
        {
            list_insert(precursor, entry);
            cursor = precursor->link();

        } else if (!is_item())
        {
            list_head_insert(head_ptr, entry);
            tail_ptr = precursor->link();
            cursor = head_ptr;
            precursor = NULL;
        }
        many_nodes++;
        return;
    }

    void sequence::attach(const value_type &entry)
    {
        if (head_ptr == NULL)
        {
            // empty list
            list_head_insert(head_ptr, entry);
            cursor = head_ptr;
            precursor = NULL;
            tail_ptr = head_ptr;

        } else if (is_item() && many_nodes == 1)
        {
            // head is tail
            list_insert(head_ptr, entry);
            precursor = head_ptr;
            tail_ptr = precursor->link();
            cursor = tail_ptr;

        } else if (is_item() && many_nodes > 1 && cursor == head_ptr)
        {
            // cursor is head and list > 1
            list_insert(head_ptr, entry);
            precursor = head_ptr;
            cursor = precursor->link();
            
        } else if (is_item() && cursor != head_ptr)
        {
            // middle of list
            if (cursor != tail_ptr)
            {   
                list_insert(cursor, entry);
                advance();
            } else {
                // else if tail
                list_insert(tail_ptr, entry);
                tail_ptr = cursor->link();
                precursor = cursor;
                cursor = tail_ptr;
            }
        } else if (!is_item() && many_nodes > 0)
        {
            cout << "i run" << endl;
            // null cursor, list has stuff
            list_insert(tail_ptr, entry);
            precursor = tail_ptr;
            cursor = precursor->link();
            tail_ptr = cursor;
        }
        many_nodes++;
        return;
    }

    void sequence::operator =(const sequence &source)
    {
        if (this == &source){ return; }

        list_clear(head_ptr);
        many_nodes = 0;
        node *temp;
        list_copy(source.head_ptr, head_ptr, temp);
        cursor = head_ptr;
        tail_ptr = temp;

        node* anotherTemp = source.head_ptr;
        precursor = head_ptr;
        if (source.cursor == NULL)
        {
            cursor = NULL;
            precursor = tail_ptr;
        } else {
            while (anotherTemp != source.precursor)
            {
                anotherTemp = anotherTemp->link();
                precursor = precursor->link();
            }
            if (precursor != NULL)
            {
                cursor = precursor->link();
            }
        }
        many_nodes = source.many_nodes;
    }

    // const 
    sequence::size_type sequence::size() const{
        return many_nodes;
    }

    bool sequence::is_item() const {
        if (cursor == NULL)
        {
            return false;
        } else {
            return true;
        }
    }

    sequence::value_type sequence::current() const {
        assert (is_item());
        return cursor->data();
    }

    
}
