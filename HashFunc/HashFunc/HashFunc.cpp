// HashFunc.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <unordered_set>
#include <iostream>
using namespace std;

template <typename T>
inline void hash_combine(size_t& seed, const T& val)
{
	seed ^= std::hash<T>()(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template <typename T>
inline void hash_val(size_t& seed, const T& val)
{
	hash_combine(seed, val);
}

template <typename T, typename... Types>
inline void hash_val(size_t& seed, const T& val, const Types&... args)
{
	hash_combine(seed, val);
	hash_val(seed, args...);
}

template <typename... Types>
inline size_t hash_val(const Types&... args)
{
	size_t seed = 0;
	hash_val(seed, args...);
	return seed;
}

typedef struct _Customer_
{
	std::string fname;
	std::string lname;
	int no;
}Customer;

class CustomerHash
{
public:
	size_t operator() (const Customer& c) const
	{
		return hash_val(c.fname, c.lname, c.no);
	}
};

struct CustomerEqualTo
{
	bool operator()(const Customer& c1, const Customer& c2) const
	{
		return c1.fname == c2.fname &&
			c1.lname == c2.lname &&
			c1.no == c2.no;
	}
};

int main()
{
	unordered_set<Customer, CustomerHash, CustomerEqualTo> set1;
	set1.insert(Customer{ "Jack", "zhang", 1 });
	set1.insert(Customer{ "Lucas", "wang", 2 });
	set1.insert(Customer{ "Tom", "zhou", 3 });
	set1.insert(Customer{ "Jerry", "li", 4 });
	set1.insert(Customer{ "Leo", "tang", 5 });
	set1.insert(Customer{ "Mark", "ding", 6 });
	set1.insert(Customer{ "Jonson", "cai", 7 });
	cout << "set current bucket_count: " << set1.bucket_count() << endl;

	CustomerHash hCustomer;
	cout << "bucket Jack: " << hCustomer(Customer{ "Jack", "zhang", 1 }) % 11 << endl;
	cout << "bucket Lucas: " << hCustomer(Customer{ "Lucas", "wang", 2 }) % 11 << endl;
	cout << "bucket Tom: " << hCustomer(Customer{ "Tom", "zhou", 3 }) % 11 << endl;
	cout << "bucket Jerry: " << hCustomer(Customer{ "Jerry", "li", 4 }) % 11 << endl;
	cout << "bucket Leo: " << hCustomer(Customer{ "Leo", "tang", 5 }) % 11 << endl;
	cout << "bucket Mark: " << hCustomer(Customer{ "Mark", "ding", 6 }) % 11 << endl;
	cout << "bucket Jonson: " << hCustomer(Customer{ "Jonson", "cai", 7 }) % 11 << endl;

	for (int i = 0; i < set1.bucket_count(); i++)
		cout << "bucket #" << i << " has " << set1.bucket_size(i) << endl;

	system("pause");
    return 0;
}

