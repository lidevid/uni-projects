#ifndef VECTOR_H
#define VECTOR_H
#include<initializer_list>
#include<iostream>

template<typename T>
class Vector {
public:
	class ConstIterator;
	class Iterator;
	using value_type = T;
	using size_type = std::size_t;
	using difference_type = std::ptrdiff_t;
	using reference = value_type&;
	using const_reference = const value_type&;
	using pointer = value_type*;
	using const_pointer = const value_type*;
	using iterator = Vector::Iterator;
	using const_iterator = Vector::ConstIterator;

private:
	size_type sz;
	size_type max_sz;
	pointer values;
	static constexpr size_type min_sz=5;
public:

	Vector() :sz{ 0 }, max_sz{ min_sz }
	{
		values = new value_type[max_sz];
	}

	Vector(size_type n) :sz{0}, max_sz{ n > min_sz ? n : min_sz }
	{
		values = new value_type[max_sz];
	}

	Vector(std::initializer_list<value_type> list): Vector(list.size()) {    // initializer{}
		for (const auto& v : list)
		{
			values[sz] = v;
			sz++;
		}

	}

	Vector(const Vector& v):Vector(v.sz) // copy constructor 
	{
		sz = v.sz;
		max_sz = v.max_sz;
		for (size_type i = 0; i < v.sz; i++)
		{
			values[i] = v.values[i];
		}
	}
	
	Vector& operator =(const Vector& rop)      // copy assigement 
	{
		pointer buf = rop.values ? new value_type[rop.max_sz] : nullptr;
		for (size_type i = 0; i < rop.sz; i++)
		{
			buf[i] = rop.values[i];
		}
		if (values) delete[]values;
		values = buf;
		sz = rop.sz;
		max_sz = rop.max_sz;
		return *this;
	}
	// METHODS
	
	size_type size() const { return sz; }  //actual size
	bool empty() const { return !sz; }  // true if empty vector
	void clear() { sz = 0; }            //vector = 0 

	void reserve(size_type n)        // reserves place n 
	{
		if (n > max_sz) {
			max_sz = n;
			pointer buf = new value_type[max_sz];
			for (size_type i = 0; i < sz; i++)
			{
				buf[i] = values[i];
			}
			delete[]values;
			values = buf;
		}
		else return;
		
	}
	void shrink_to_fit()  // makes max size to an actual size;
	{
		max_sz = sz;
	}
	void push_back(value_type x)
	{
		if (max_sz == sz) this->reserve(sz * 2);
		values[sz] = x;
		sz++;

	}

	void pop_back()
	{
		if (this->empty()) throw std::runtime_error ("Empty vector");
		sz--;
	}

	reference operator[](size_type index)
	{
		if (index < 0 || index >= sz) throw std::runtime_error("Out of array range");
		return values[index];
	}
	
	const_reference operator[](size_type index) const
	{
		if (index < 0 || index >= sz) throw std::runtime_error("Out of array range");
		return values[index];
	}

	size_type capacity()const { return max_sz; }

	friend std::ostream& operator << (std::ostream& o, const Vector& v)
	{
		o << '[';
		for (size_type i = 0; i < v.sz; i++)
		{
			if (i == v.sz-1) o << v.values[i];
			else o << v.values[i] << ", ";
		}

		o << ']';
		return o;
	}

	~Vector() { delete[]values; }

	class Iterator {
	public:
		using value_type = Vector::value_type;
		using reference = Vector::reference;
		using pointer = Vector::pointer;
		using difference_type = Vector::difference_type;
		using iterator_category = std::forward_iterator_tag;
	private:
		pointer ptr;
	public:
		Iterator() : ptr{ nullptr } {}
		Iterator(pointer ptr) : ptr{ ptr } {}

		//Methods
		reference operator*() {
			return *ptr;
		}
		pointer operator->()
		{
			return ptr;
		}
		bool operator==(const const_iterator& it) const
		{
			return static_cast<const_iterator>(*this)==it;
		}
		bool operator !=(const const_iterator& it)const
		{
			return !(*this == it);
		}

		iterator& operator++()
		{
			++ptr;
			return *this;
		}

		iterator operator++(int)
		{
			iterator it = *this;
			++(*this);
			return it;
		}

		operator const_iterator()const  // if error make return const_iterator(ptr) instead
		{
			const_iterator it (ptr);
			return it;
		}

		 difference_type operator-( const iterator& rop)     // if error make friend
		{
			return static_cast<const_iterator>(*this) - rop;
		}

	};

	class ConstIterator {
	public:
		using value_type = Vector::value_type;
		using reference = Vector::const_reference;
		using pointer = Vector::const_pointer;
		using difference_type = Vector::difference_type;
		using iterator_category = std::forward_iterator_tag;
	private:
		pointer ptr;
	public:
		ConstIterator() : ptr{ nullptr } {}
		ConstIterator(pointer ptr) : ptr{ ptr } {}

		//Methods
		reference operator*() const {
			return *ptr;
		}
		pointer operator->() const
		{
			return ptr;
		}
		bool operator==(const const_iterator& it) const
		{
			return ptr == it.ptr;
		}
		bool operator !=(const const_iterator& it)const
		{
			return ptr != it.ptr;
		}

		const_iterator& operator++()
		{
			++ptr;
			return *this;
		}

		const_iterator operator++(int)
		{
			const_iterator it = *this;
			++(*this);
			return it;
		}

		difference_type operator-(const const_iterator& rop) const    // if error->make friend and delete const
		{
			return ptr - rop.ptr;
		}
	};

	iterator begin()
	{
		return iterator(values);
	}
	iterator end()
	{
		return iterator(values+sz);
	}
	const_iterator begin() const
	{
		return const_iterator(values);
	}
	const_iterator end() const
	{
		return const_iterator(values + sz);
	}

	iterator insert(const_iterator pos, const_reference val)
	{
		auto diff = pos - begin();
		if (diff<0 || static_cast<size_type>(diff)>sz)
			throw std::runtime_error("Iterator out of bounds");
		size_type current{ static_cast<size_type>(diff) };
		if (sz >= max_sz)
			reserve(max_sz * 2);
		for (size_type i{ sz }; i-- > current;)
			values[i + 1] = values[i];
		values[current] = val;
		++sz;
		return iterator{ values + current };
	}

	iterator erase(const_iterator pos)
	{
		auto diff = pos - begin();
		if (diff < 0 || static_cast<size_type>(diff) >= sz)
			throw std::runtime_error("Iterator out of bounds");
		size_type current{ static_cast<size_type>(diff) };
		for (size_type i{ current }; i < sz - 1; i++)
			values[i] = values[i + 1];
		--sz;
		return iterator{ values + current };
	}
};
#endif 

