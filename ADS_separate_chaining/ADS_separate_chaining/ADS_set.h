#ifndef ADS_SET_H
#define ADS_SET_H

#include <functional>
#include <algorithm>
#include <iostream>
#include <stdexcept>

template <typename Key, size_t N = 7>
class ADS_set {
public:
    class Iterator;
    using value_type = Key;
    using key_type = Key;
    using reference = key_type&;
    using const_reference = const key_type&;
    using size_type = size_t;
    using difference_type = std::ptrdiff_t;
    using iterator = Iterator;
    using const_iterator = Iterator;
    using key_compare = std::less<key_type>;   // B+-Tree
    using key_equal = std::equal_to<key_type>; // Hashing
    using hasher = std::hash<key_type>;        // Hashing

private:
    struct Elem {
        key_type key;
        Elem* next{ nullptr };

        ~Elem() {
            delete next;
        };
    };
    //FALLS neueInstanzvariablen -> swap veraendern
    Elem* table{ nullptr };
    size_type max_size{ 0 }, curr_size{ 0 };
    // float max_lf{ 0.7 }; // also in if/while in reserve and rehash max; swap;

    size_type h(const_reference key) const { return hasher{}(key) % max_size; } // hash function
    void reserve(size_type n);  // reserves place for min n
    void rehash(size_type n);   // makes new table and rehash it
    Elem* insert_unchecked(const_reference key); // inserts element without checking place etc.
    Elem* find_simple(const_reference key) const;  // return elem by his key

public:
    ADS_set() { rehash(N); } //default

    ADS_set(std::initializer_list<key_type> ilist) :ADS_set() { insert(ilist); }   // initializer
  
    template<typename InputIt> ADS_set(InputIt first, InputIt last) : ADS_set() {  // range
        insert(first, last);
    } 

    ADS_set(const ADS_set& other) :ADS_set{} {          //KopierKonstruktor
        reserve(other.curr_size);
        for (const auto& k : other) {
            insert_unchecked(k);
        }
    }

    ~ADS_set() {
        delete[] table;
    }

    ADS_set& operator=(const ADS_set& other) {   //Kopierzuweisung
        if (this == &other) return *this; 
        ADS_set tmp{ other };
        swap(tmp);
        return *this;
    }

    ADS_set& operator=(std::initializer_list<key_type> ilist) {
        ADS_set tmp{ ilist };
        swap(tmp);
        return *this;
    }
    // ALTEPROBETEST 2020_02_25
   std::pair<key_type, key_type>kk()const {
        size_type max_line_size = 1; // max size of teilfolge
        size_type local_size = 1;   //sz of current teilgolge
        key_type first;             //1st return value
        key_type last;              //2nd return value
        key_type point1;            //savepoint for the first return value;
        bool check = false;         // checks it there are more teilfolge the same size

        for (size_type i = 0; i < max_size;i++) {
            Elem* temp = table[i].next;
            if(temp != nullptr) point1 = temp->key;

            if (temp != nullptr && temp->next == nullptr && check==false && max_line_size==1) {
                check = true;
                first = point1; last = point1;
            }

            while (temp != nullptr && temp->next != nullptr) {
                ++local_size;
                if (key_compare{}(temp->key, temp->next->key)) {
                    if (local_size > max_line_size) {
                        max_line_size = local_size;
                        first = point1;
                        last = temp->next->key;
                    }
                }
                else if(check==true){
                    local_size = 1;
                    point1 = temp->next->key;
                }
                temp = temp->next;
                if (max_line_size == 1 && check == false) { first = point1; last = point1; check = true; }
            } // END WHILE
            local_size = 1;
        }// END FOR

        if (curr_size==0) throw std::runtime_error("Error, no elements");
        return std::make_pair(first, last);
    }

    size_type size() const { return curr_size; }

    bool empty() const { return !curr_size; }

    size_type count(const_reference key) const { return !!find_simple(key); } // return 0 or 1, if elem found
    
    iterator find(const key_type& key) const { 
        size_type idx = h(key);
        if (auto p{ find_simple(key) }) return iterator{ table,p,idx,max_size};
        return end();
    }

    void clear() {
        ADS_set tmp;
        swap(tmp);
    }
    void swap(ADS_set& other) {
        using std::swap;
        swap(table, other.table);
        swap(curr_size, other.curr_size);
        swap(max_size, other.max_size);
    }

    void insert(std::initializer_list<key_type> ilist) { insert(std::begin(ilist), std::end(ilist)); } // insert ilist;
   
    std::pair<iterator, bool> insert(const key_type& key) {    // insert 1 element
        size_type idx = h(key);
        if (auto p{ find_simple(key) }) return { iterator{table,p,idx,max_size},false };
        reserve(curr_size + 1);
        idx = h(key);
        return { iterator {table,insert_unchecked(key),idx,max_size},true };                      // returns pait It and bool

    }

    template<typename InputIt> void insert(InputIt first, InputIt last) {     //insert from first to last;
        for (auto it{ first }; it != last; ++it) {
            if (!count(*it)) {
                reserve(curr_size + 1);
                insert_unchecked(*it);
            }
        }
    } 

    size_type erase(const key_type& key) {
        size_type  idx{ h(key) };
        Elem* help_1{ table[idx].next };
        Elem* help_2{ nullptr };

        for (; help_1!=nullptr; help_1 = help_1->next) {
            if (key_equal{}(key, help_1->key)) 
            {
                if (help_1 == table[idx].next) {
                    table[idx].next = help_1->next;
                    help_1->next = nullptr;
                    delete  help_1;
                }
                else {
                    help_2->next = help_1->next;
                    help_1->next = nullptr;
                    delete help_1;
                    help_2 = nullptr;
                }
                --curr_size;
                return 1;
            }
            help_2 = help_1;
        }
        return 0;
    }

    const_iterator begin() const {
        if (!curr_size) return end();
        size_type idx{ 0 };
        while (table[idx].next == nullptr) idx++;
        return const_iterator(table, table[idx].next, idx, max_size);

    }

    const_iterator end() const {
        return const_iterator{ nullptr };
    }

    void dump(std::ostream& o = std::cerr) const  // shows the table
    {
        o << "curr_ size = " << curr_size << ", max_size = " << max_size << "\n";
        for (size_type idx{ 0 }; idx < max_size; ++idx)
        {
            o << idx << ": ";

            for (Elem* elem = table[idx].next; elem != nullptr; elem = elem->next) 
            {
                o << elem->key;
                if (elem->next) o << " --> ";
            }
            o << "\n";
        }
        o << "\n";
    }

    friend bool operator==(const ADS_set& lhs, const ADS_set& rhs) {
        if (lhs.curr_size != rhs.curr_size) return false;
        for (const auto& k : rhs) {                                 // Am Klausur die Schleife ohne Iterator
            if (!lhs.count(k)) return false;
        }
        return true;
    }

    friend bool operator!=(const ADS_set& lhs, const ADS_set& rhs) {
        return !(lhs == rhs);
    }

    //ALTEPRUFUNG 20190702
    const_iterator x(const key_type& a, const key_type& b)const {
        size_type idx{ 0 };
        Elem* temp = table[idx].next;            // to find idx of the line of a;
        while (temp != &a && temp!=nullptr) {
            temp = temp->next;
            if (temp == nullptr) {
                idx++; temp = table[idx].next;
            }
        }
        return const_iterator(this.begin(), &a, idx, max_size, b);
    }
};

//manche methods realisieren;

template <typename Key, size_t N>
typename ADS_set<Key, N>::Elem* ADS_set<Key,N>::insert_unchecked(const_reference key) {
    size_type idx{ h(key) };
    Elem* help = new Elem;

    help->next = table[idx].next;
    help->key = key;
    table[idx].next = help;
    ++curr_size;

    return table[idx].next;
}

template <typename Key, size_t N>
typename ADS_set<Key, N>::Elem* ADS_set<Key, N>::find_simple(const_reference key)const {
    size_type idx{ h(key) };

    for (Elem* ptr = table[idx].next; ptr != nullptr; ptr = ptr->next) {
        if (key_equal{}(key,ptr->key)) {
            return ptr;
        }
    }
    return nullptr;
}

template <typename Key, size_t N>
void ADS_set<Key, N>::reserve(size_type n) {
    if (n > max_size)
    {   
        size_type new_max_size{ max_size };
        do {
            new_max_size = new_max_size * 2 + 1;
        } while (n > new_max_size);
        rehash(new_max_size);
    }
}

template <typename Key, size_t N>
void ADS_set<Key, N>::rehash(size_type n) {
    size_type new_max_size{ std::max(N,std::max(n,max_size)) };
    Elem* new_table = new Elem [new_max_size];

    size_type old_max_size{ max_size };
    Elem* old_table{ table };

    curr_size = 0;
    max_size = new_max_size;
    table = new_table;
    for (size_type idx{ 0 }; idx < old_max_size; ++idx)
    {
        for (Elem* ptr = old_table[idx].next; ptr != nullptr; ptr = ptr->next) {
            insert_unchecked(ptr->key);
        }
    }
    delete[] old_table;
    
}

template <typename Key, size_t N>
class ADS_set<Key, N>::Iterator {
public:
    using value_type = Key;
    using difference_type = std::ptrdiff_t;
    using reference = const value_type&;
    using pointer = const value_type*;
    using iterator_category = std::forward_iterator_tag;
private:
    Elem* new_set;
    Elem* pos;
    size_type it_pos; //mean iterator table position, not in the chain. table[it_pos]
    size_type table_sz;
    bool modus=false;
    key_type first;
    key_type last;

    void skip() {
        do {
            it_pos++;
        } while (new_set[it_pos].next == nullptr && it_pos < table_sz);
    }
public:
    explicit Iterator(Elem* new_set = nullptr, Elem* pos = nullptr, size_type it_pos = 0,size_type table_sz=0):
        new_set{ new_set }, pos{ pos }, it_pos{ it_pos }, table_sz{table_sz}
    { 
    }

    explicit Iterator(Elem* new_set, Elem* pos, size_type it_pos, size_type table_sz, key_type last) :
        new_set{ new_set }, pos{ pos }, it_pos{ it_pos }, table_sz{ table_sz }, last{last}
    {
        bool check = false;
        for (*Elem ptr = new_set.next; this->new_set!= nullptr; ptr=ptr->next) {
            if (ptr == nullptr) { skip(); ptr = &this->new_set[it_pos]; }
            if (key_equal{}(this.last, ptr->key)) check = true;

            if (key_equal{}(pos->key, ptr->key) && check == true) {
                this->new_set = nullptr;
                this->pos = nullptr;
            }

            if ((!key_equal{}(pos->key,ptr->key) || !key_equal{}(ptr->key, this.last)) && this.it_pos == this.table_sz - 1 && ptr->next == nullptr) {
                this->new_set = nullptr;
                this->pos = nullptr;
            }
        }
        modus = true;
    }


    reference operator*() const {
        return pos->key;
    }
    pointer operator->() const {
        return & pos->key;
    }
    Iterator& operator++() {
        if (modus == false) {
            if (pos->next) pos = pos->next;
            else {
                skip();
                if (it_pos == table_sz) { pos = nullptr; return *this; }
                pos = new_set[it_pos].next;
            }
            return *this;
        }

        else if (modus == true) {
            if (key_equal{}(pos->key, last)) { new_set = nullptr; pos = nullptr; return *this; }

            if (pos->next && !key_equal{}(pos->next->key, last)) { pos = pos->next; return *this }

            else if(pos->next==nullptr) {
                skip();
                if (!key_equal{}(new_set[it].next->key, last)) pos = new_set[it_pos].next;
                else { new_set = nullptr; pos = nullptr; return *this; }
            }
            else if (key_equal{}(pos->next->key, last)) { new_set = nullptr; pos = nullptr; return *this; }

        }
    }

    Iterator operator++(int) {
        auto rc{ *this };
        ++* this;
        return rc;
    }
    friend bool operator==(const Iterator& lhs, const Iterator& rhs) {
        return lhs.pos == rhs.pos;
    }
    friend bool operator!=(const Iterator& lhs, const Iterator& rhs) {
        return !(lhs == rhs);
    }
};

template <typename Key, size_t N> void swap(ADS_set<Key, N>& lhs, ADS_set<Key, N>& rhs) { lhs.swap(rhs); }
#endif 