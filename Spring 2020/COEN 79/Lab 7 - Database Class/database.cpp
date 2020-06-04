// FILE: database.cpp
// CLASS implemented: database (see database.h for documentation)

// INVARIANT for the database ADT:
//   1. The items in the database are stored in a dynamic array, where each entry of the array includes
//      a company name, a pointer to the head of the linked list of products, and a
//      a pointer to the tail of the linked list of products
//   2. The number of slots in the array of companies is stored in member varibale aloc_slots
//   3. The number of used slots of the array of companies is stored in member varibale used_slots


#ifndef DATABASE_CPP
#define DATABASE_CPP

#include "database.h"


//#define USEDEBUG

#ifdef USEDEBUG
#define Debug( x ) std::cout << x
#else
#define Debug( x )
#endif


namespace coen79_lab7
{
    
    database::database(const size_type& initial_capacity) {
        used_slots = 0;
        aloc_slots = initial_capacity;
        company_array = new company[aloc_slots];
    }
    
    
    database::database(const database &src) {
        Debug("Copy constructor..." << std::endl);

        *this = src;
    }
    
    
    database& database::operator= (const database &rhs) {
        Debug("Assignment operator..." << std::endl);

        reserve(rhs.aloc_slots);
        for (int i = 0; i < rhs.aloc_slots; ++i)
        {
            this-> company_array[i] = rhs.company_array[i];
        }
        this->aloc_slots = rhs.aloc_slots;
        this->used_slots = rhs.used_slots;

        return *this;
    }
    
    
    database::~database() {
        delete[] company_array;
    }
    
    
    void database::reserve(size_type new_capacity) {
        Debug("Reserve..." << std::endl);

        if (new_capacity == aloc_slots)
            return; // The allocated memory is already the right size.
        
        if (new_capacity < used_slots)
            new_capacity = used_slots; // Canít allocate less than we are using.
        
        // make new array
        company* new_array = new company[new_capacity];
        std::copy(company_array, company_array + used_slots, new_array);

        // delete old array, free memory, copy over old technicals
        delete [] company_array;
        company_array = new_array;
        aloc_slots = new_capacity;
    }
    
    
    bool database::insert_company(const std::string &entry) {
        
        Debug("Insert company..." << std::endl);

        assert(entry.length() > 0);
        
        size_type pos = search_company(entry);
        
        // If you find a company that is false, because there are duplicates
        if (pos != COMPANY_NOT_FOUND) {
            return false;
        }

        // make space if necessary
        if (used_slots == aloc_slots)
        {
            reserve(used_slots + 1);
        }

        // insertion
        company_array[used_slots] = entry;
        used_slots++;
        return true;
        
    }
    
    
    bool database::insert_item(const std::string &company, const std::string &product_name, const float &price) {
        Debug("Insert item..." << std::endl);

        assert(company.length() > 0 && product_name.length() > 0);

        size_type pos = search_company(company);

        if (pos != COMPANY_NOT_FOUND)
        {
            company_array[pos].insert(product_name, price);
            return false;
        }
        // increment and insert
        insert_company(company);
        company_array[used_slots - 1].insert(product_name, price);
        return true;
    }
    
    
    bool database::erase_company(const std::string &company) {
        
        size_type company_index = search_company(company);
        
        assert(company.length() > 0);

        if (company_index ==  COMPANY_NOT_FOUND) { return false; }

        // shift
        for (size_type  i = company_index; i < used_slots-1; ++i)
        {
            company_array[i] = company_array[i+1];
        }
        used_slots--;
        return true;
    }
    
    
    bool database::erase_item(const std::string& cName, const std::string& pName) {
        
        assert(cName.length() > 0 && pName.length() > 0);

        size_type pos = search_company(cName);

        // not found
        if (pos == COMPANY_NOT_FOUND) 
        { 
            return false;
        } else {
            // something wrong w erase
            company_array[pos].erase(pName);
            return true;
        }

        // // false if not there but was found
        // if (company_array[company_index].erase(pName) == 0)
        // {
        //     std::cout << "i ran" << std::endl;

        //     return false;
        // }

        // // erase it
        // company_array[company_index].erase(pName);
        // return false;
    }
    
    
    
    database::size_type database::search_company(const std::string& company) {
        assert(company.length() > 0);

        // simple searching
        for (size_t i = 0; i < used_slots; ++i)
        {
            if (company_array[i].get_name() == company) {
                return i;
            }
        }
        return COMPANY_NOT_FOUND;
    }
    
    
    bool database::print_items_by_company(const std::string& cName) {
        assert(cName.length() > 0);

        size_type c_index = search_company(cName);
        
        if (c_index == COMPANY_NOT_FOUND) {
            return false;
        }
        
        std::cout << "Printing the products of " << cName << ":"<< std::endl;
        company_array[c_index].print_items();
        std::cout << std::endl;
        
        return true;
    }
    
    
    void database::print_companies() {
        
        std::cout << "Company List" << std::endl;
        for (int i = 0; i < used_slots; i++) {
            std::cout << "- " << company_array[i].get_name() << std::endl;
        }
    }
}


#endif
