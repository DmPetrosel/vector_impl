#ifndef VECTOR_IMPL_HPP_
#define VECTOR_IMPL_HPP_

#include <exception>

//Template


//TODO Make own exception class

class insert_exception :  public std::exception
{

	private:
		const char *msg;
	public:
	insert_exception(int n){
		if (n < 0){
		msg = "There is out of range exception. And index is lower then 0.\n";
		}
		else{
			msg=  "There is out of range exception. And index is higher then it possible.\n";
		}
	}	
	const char* what() const noexcept override{
		return msg; 
	}
};

class vector 
{
#define INIT_SIZE		1
#define SCALE_FACTOR	2

	using T			= int;
	using elem_type = T;

public:
	//vector() = default; 

	vector() {
		m_data		= nullptr;
		m_size		= 0;
		m_capacity	= 0;
	}
	explicit vector(size_t size) {
		m_data = new elem_type[size];
		if (m_data == nullptr) {
			throw std::bad_alloc{};
		}
		m_size = 0;
		m_capacity = size;
	}

	vector(size_t count, elem_type value) {
		m_data = new elem_type[count];
		if (m_data == nullptr) {
			throw std::bad_alloc{};
		}
		for (size_t i = 0; i < count; i++) {
			m_data[i] = value;
		}
		m_size = count;
		m_capacity = count;
	}
	


	//vector(const vector& o) = delete; //never called
	//vector operator= (const vector& o) = delete; // 

	//vector operator= (const vector& o) = default; 
	//deep copy
	vector(const vector& o) {
		if (this != &o) 
		{
			m_data = new elem_type[o.m_capacity];
			if (m_data == nullptr)
				throw std::bad_alloc{};
			//TODO define type 
			// use memcpy() if pod 
			for (size_t i = 0; i < o.m_size; i++)
			{
				m_data[i] = o.m_data[i];

			}
			m_size = o.m_size;
			m_capacity = o.m_capacity;
		}
	}
	//deep copy
	vector& operator= (const vector& o) 
	{
		if (this == &o) 
		{
			this->m_data = new elem_type[m_capacity];
			if (this->m_data == nullptr)
				throw std::bad_alloc{};
			for (size_t i = 0; i < o.m_size; i++)
			{
				this->m_data[i] = o.m_data[i];

			}
			this->m_size = o.m_size;
			this->m_capacity = o.m_capacity;

		}
		return *this;
	}
	//shifting other vector to this
	vector(vector&& o)noexcept 
	{
		if (this != &o) {
			this->m_data = o.m_data;
			o.m_data = nullptr;
			this->m_size = o.m_size;
			this->m_capacity = o.m_capacity;
		}
	}
	//shifting other vector to this
	vector &operator=(vector&& o)noexcept 
	{
		if (this != &o) {
			this->m_data = o.m_data;
			o.m_data = nullptr;
			this->m_size = o.m_size;
			this->m_capacity = o.m_capacity;
		}
		return *this;
	}

	//vector v;
	//vector b = v;
	//vector b(v);
	//v.~vector();
	
	//vector v;
	//vector b (std::move (v));
	//vector v;
	//vector b = std::move(v);
	//v = vector();
	//v = std::move(b);
	


	~vector() {
		if (m_data != nullptr)
			delete[] m_data;
	}

	elem_type& operator [] (size_t ind) const noexcept
	{
		return m_data[ind];
	}


	[[nodiscard]] size_t size() const noexcept
	{
		return m_size;
	}
	
	size_t capacity() const noexcept
	{
		return m_capacity;
	}
	void push_back(elem_type pb)
	{
		if (m_size == m_capacity) 
		{
			size_t		new_cap	  = (m_capacity == 0) ? INIT_SIZE : m_capacity * SCALE_FACTOR;
			try {
				realloc(new_cap);//-1 to check
			}
			catch (const std::exception& e) {
				std::cerr << e.what()<< '\n';
				return;
			}
			m_capacity = new_cap;
		}
		m_data[m_size++] = pb;
	}
	friend std::ostream& operator<<(std::ostream& os, const vector& v) {
		for (int i = 0; i < v.size(); i++)
		{
			os << v[i] << ' ';
		}
		os << '\n';
		return os;
	}


//TODO To insert work with itertor (iterator.begin(), iterator.end()(default))
//Insert function obtain position to insert and vector of elements
	void insert(int pos,const vector& v) {
		try {
			if (pos > this->size() || pos < 0)
			{
				throw insert_exception(pos);
			}

			size_t need = this->m_size + v.size();
			if (this->m_capacity < need)
			{
				realloc(need);
				m_capacity = need;
			}

			for (int i = m_size - 1; i >= pos; i--)
			{
				this->m_data[i + v.size()] = m_data[i];
			}
			for (size_t i = pos, j = 0; j < v.size(); i++, j++)
			{
				m_data[i] = v[j];
			}

			m_size = need;
		}
		catch (std::exception & e) {
			std::cout << e.what()<< '\n';
			return;
		}
		
		
		
		/*int new_cap = this->capacity();
		int sz =  this->size();;
		if (m_capacity < v.size() + this->size()) {
			new_cap = v.size() + this->size();
			this->realloc(new_cap);
		}
		
		int step = v.size();
		for (int i = sz-1; i >= pos; i--) {
			m_data[i + step] = m_data[i];
		}
		for (int i = pos, j= 0; i < v.size()-1; i++, j++) {
			m_data[i] = v.m_data[j];
		}
		m_size = new_cap;
		m_capacity = m_size;*/

	}

private: 
	void realloc(size_t sz) {

		elem_type* ptr_elem = (elem_type*)std::realloc(this->m_data, sz * sizeof(elem_type));
		//this->m_data = (elem_type*)std::realloc(this->m_data, sz * sizeof(elem_type));
		if (!ptr_elem) {
			throw std::bad_alloc{};//("Memory is not given!!!");
		}
		this->m_data = ptr_elem;
	}



	//	vector res(m_size);
	//	for (int i = 0; i < m_size; i++) {
	//		res.m_data[i] = this->m_data[i];
	//	}
	//	res.m_capacity = this->m_capacity;
	//	res.m_size = m_size;
	//	//this->~vector();
	//	delete[] m_data;
	//	this->m_data = new elem_type[capacity_];
	//	for (int i = 0; i < res.m_size; i++) {
	//		this->m_data[i] = res.m_data[i];
	//	}
	//	this->m_capacity = capacity_;
	//	this->m_size = res.m_size;
	//	//res.~vector();
	//	
	//}

	/*vector(const vector& o) 
	{

	}*/// Non callable

private: 
	elem_type*	m_data;
	size_t		m_size;
	size_t		m_capacity;
};




#endif // VECTOR_IMPL_HPP_
