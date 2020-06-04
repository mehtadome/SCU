#include "node.h"
#include <cassert>    // Provides assert
#include <cstdlib>    // Provides NULL and size_t
#include <iostream>

using namespace std;

namespace coen79_lab6
{
size_t list_length(const node* head_ptr)
// Library facilities used: cstdlib
{
const node *cursor;
size_t answer;

answer = 0;
for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
    ++answer;

return answer;
}

void list_head_insert(node*& head_ptr, const node::value_type& entry)
{
    head_ptr = new node(entry, head_ptr);
}

void list_insert(node* previous_ptr, const node::value_type& entry)
{
    node *insert_ptr;

    insert_ptr = new node(entry, previous_ptr->link( ));
    previous_ptr->set_link(insert_ptr);
}

node* list_search(node* head_ptr, const node::value_type& target)
// Library facilities used: cstdlib
{
    node *cursor;

    for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
        if (target == cursor->data( ))
            return cursor;

    return NULL;
}

const node* list_search(const node* head_ptr, const node::value_type& target)
// Library facilities used: cstdlib
{
    const node *cursor;

    for (cursor = head_ptr; cursor != NULL; cursor = cursor->link( ))
        if (target == cursor->data( ))
            return cursor;

    return NULL;
}

node* list_locate(node* head_ptr, size_t position)
// Library facilities used: cassert, cstdlib
{
    node *cursor;
    size_t i;

    assert (0 < position);
    cursor = head_ptr;
    for (i = 1; (i < position) && (cursor != NULL); i++)
        cursor = cursor->link( );

    return cursor;
}

const node* list_locate(const node* head_ptr, size_t position)
// Library facilities used: cassert, cstdlib
{
    const node *cursor;
    size_t i;

    assert (0 < position);
    cursor = head_ptr;
    for (i = 1; (i < position) && (cursor != NULL); i++)
        cursor = cursor->link( );

    return cursor;
}

void list_head_remove(node*& head_ptr)
{
    node *remove_ptr;

    remove_ptr = head_ptr;
    head_ptr = head_ptr->link( );
    delete remove_ptr;
}

void list_remove(node* previous_ptr)
{
    node *remove_ptr;

    remove_ptr = previous_ptr->link( );
    previous_ptr->set_link( remove_ptr->link( ) );
    delete remove_ptr;
}

void list_clear(node*& head_ptr)
// Library facilities used: cstdlib
{
    while (head_ptr != NULL)
        list_head_remove(head_ptr);
}

void list_copy(const node* source_ptr, node*& head_ptr, node*& tail_ptr)
// Library facilities used: cstdlib
{
    head_ptr = NULL;
    tail_ptr = NULL;

    // Handle the case of the empty list.
    if (source_ptr == NULL)
        return;

    // Make the head node for the newly created list, and put data in it.
    list_head_insert(head_ptr, source_ptr->data( ));
    tail_ptr = head_ptr;

    // Copy the rest of the nodes one at a time, adding at the tail of new list.
    source_ptr = source_ptr->link( );
    while (source_ptr != NULL)
    {
        list_insert(tail_ptr, source_ptr->data( ));
        tail_ptr = tail_ptr->link( );
        source_ptr = source_ptr->link( );
    }
}

// My implementation for rest of functions
void list_piece(node*  start_ptr, node* end_ptr, node* &head_ptr, node* &tail_ptr){
    tail_ptr = NULL;
    head_ptr = NULL;

    // if one node or empty list
    if (start_ptr == end_ptr || start_ptr == NULL)
    {
        return;
    }
    // insert node at head
    list_head_insert(head_ptr, start_ptr->data());
    tail_ptr = head_ptr;

    while (start_ptr->link() != end_ptr)
    {
        // incremement
        start_ptr = start_ptr->link();
        // insert data
        list_insert(tail_ptr, start_ptr->data());
        tail_ptr = tail_ptr->link();
    }
}

size_t list_occurrences(node* head_ptr, const node::value_type &target)
{
    node* mover = head_ptr;
    size_t count = 0;

    if (head_ptr == NULL)
    {
        return count;
    }

    while (mover != NULL)
    {
        if (mover->data() == target)
        {
            count++;
        }
        mover = mover->link();
    }
    return count;
}

void list_insert_at(node* &head_ptr, const node::value_type &entry, size_t position){
    assert(position > 0 && position <= list_length(head_ptr) + 1);

    // insert at head
    if (position == 1)
    {
        list_head_insert(head_ptr, entry);

    } else if (position == list_length(head_ptr) + 1)
    {
        list_insert(list_locate(head_ptr, list_length(head_ptr)), entry);
    } else {
        list_insert(list_locate(head_ptr, position - 1), entry);
    }
}

node::value_type list_remove_at(node* &head_ptr, size_t position){
    assert(position > 0 && position <= list_length(head_ptr));

    node::value_type mover = list_locate(head_ptr, position)->data();

    if (position == 1)
    {
        node::value_type mover = head_ptr->data();
        list_head_remove(head_ptr);
        return mover;
    } else {
        list_remove(list_locate(head_ptr, position - 1));
        return mover;
    }
}

node* list_copy_segment(node* head_ptr, size_t start, size_t finish){
    assert (1<= start && start<=finish && finish<=list_length(head_ptr) );
    // empty list
    if (head_ptr == NULL)
    {
        return NULL;
    }
    node *newHead = NULL;
    node *newTail = NULL;
    node *myStart = list_locate(head_ptr, start);
    node *myEnd = list_locate(head_ptr, finish + 1);
    list_piece(myStart, myEnd, newHead, newTail);

    return newHead;
}

void list_print(const node* head_ptr){
    if (head_ptr == NULL)
    {
        std::cout << std::endl;
        return;
    }

    while (head_ptr->link() != NULL)
    {
        std::cout << head_ptr->data() << ", ";
        head_ptr = head_ptr->link();
    }
    std::cout << head_ptr->data() << std::endl;
    return;
}

void list_remove_dups(node* head_ptr){
    if (head_ptr == NULL){
        return;
    }
    node* first;
    node* second;
    node* dupe;

    first = head_ptr;
    while (first != NULL && first->link() != NULL)
    {
        second = first;
        while (second->link() != NULL)
        {
            // remove duplicate
            if (first->data() == second->link()->data())
            {
                dupe = second->link();
                second->set_link(second->link()->link());
                delete(dupe);
            }
            else {
                // incremenent
                second = second->link();
            }
            // increment
            first = first ->link();
        }
    }
    return;
}

node* list_detect_loop (node* head_ptr){
    // default edge case
    if (head_ptr == NULL)
    {
        return NULL;
    }

    node* fast_boi = head_ptr;
    node* slow_boi = head_ptr;

    while( fast_boi != NULL && fast_boi->link() != NULL )
    {
        bool hasLoop = false;
        fast_boi = fast_boi->link()->link();
        slow_boi = slow_boi->link();
        if (slow_boi == fast_boi)
        {
            hasLoop = true;
            break;
        }
    }
    // no loop, return null
    if (fast_boi == NULL || fast_boi->link() == NULL)
    {
        return NULL;
    }
    // find the intersection of cycle
    slow_boi = head_ptr;
    while (slow_boi != fast_boi){
        slow_boi = slow_boi->link();
        fast_boi = fast_boi->link();
    }
    std::cout << "THEY MET" << std::endl;
    return slow_boi;
}

    
}
