#pragma once

#include <bitset>

template<class key, class value>
class hash_table
{
public:
	hash_table();

	~hash_table();

	const int operator()(key _key);

	value& operator[](const key& _key);

	//const value& operator[](const key& _key);

	const value& get(const key& _key);

	void set_size(int new_size);

	void erase(const key& _key);

	void clear();

	void Print();
private:
	std::pair<key, value>** container;
	int size;

	std::bitset<64> divide;
	int divide_count_bits;

	void set_divide_size();
	int decide_collision(int index);
	void initialize(int size);
	int calc_start(const std::bitset<64> any) const;
	int calc_word_size(const std::bitset<64> any) const;
	int find_key(key _key) const;
	
};

template<class key, class value>
hash_table<key, value>::hash_table()
{
	size = 128;

	initialize(size);
}

template<class key, class value>
hash_table<key, value>::~hash_table()
{
	clear();
}

template<class key, class value>
void hash_table<key, value>::initialize(int size)
{
	container = new std::pair<key, value> * [size];

	memset(container, 0, size * sizeof(*container));

	divide = size - 1;
	set_divide_size();
}

template<class key, class value>
value& hash_table<key, value>::operator[](const key& _key)
{
	int i = this->operator()(_key);
	if (container[i] == nullptr)
	{
		container[i] = new std::pair<key, value>(_key, value{});
	}

	return container[i]->second;
}

template<class key, class value>
void hash_table<key, value>::erase(const key& _key)
{
	int i = find_key(_key);

	if (container[i] == nullptr)
	{
		std::cout << "Element isn't found" << endl;
		return;
	}

	delete containter[i];

	container[i] = nullptr;
}

template<class key, class value>
const value& hash_table<key, value>::get(const key& _key)
{
	int i = find_key(_key);

	return container[i]->second;

}

template<class key, class value>
void hash_table<key, value>::Print()
{
	for (int i = 0; i < size; ++i)
	{
		std::cout << "Key: " << container[i]->first << "Value: " << container[i]->second << std::endl;
	}
}

template<class key, class value>
void hash_table<key, value>::clear()
{
	for (size_t i = 0; i < size; ++i)
	{
		delete container[i];
	}

	delete[] container;
}

template<class key, class value>
const int hash_table<key, value>::operator()(key _key)
{
	std::bitset<64> bin_key(_key);
	std::bitset<64> remainder;
	if (calc_start(divide) > calc_start(_key))
	{
		return decide_collision(bin_key.to_ullong());
	}

	int to_start_bit;

	to_start_bit = calc_start(bin_key);

	int j = divide_count_bits - 1;
	for (size_t i = to_start_bit; i > (to_start_bit - divide_count_bits); --i)
	{
		remainder[j] = bin_key[i];
		--j;
	}

	int difference;
	int it_bin_key = to_start_bit - divide_count_bits;
	remainder ^= divide;
	while (it_bin_key > -1)
	{
		difference = calc_start(remainder) - calc_start(divide);

		if (it_bin_key + difference < 0)
		{
			return decide_collision(remainder.to_ullong());
		}

		if (difference < 0)
		{
			std::bitset<64> buf_remainder;
			buf_remainder.reset();
			int it_remainder = 0 - difference;
			for (size_t i = 0; i != calc_start(remainder) + 1; ++i)
			{
				buf_remainder[it_remainder] = remainder[i];
				++it_remainder;
			}
			it_remainder = -1 - difference;
			while (it_remainder > -1)
			{
				buf_remainder[it_remainder] = bin_key[it_bin_key];
				--it_remainder;
				--it_bin_key;
			}
			remainder = buf_remainder;
		}
		remainder ^= divide;

	}

	return decide_collision(remainder.to_ullong());
}

template<class key, class value>
int hash_table<key, value>::decide_collision(int index)
{
	if (container[index] == nullptr)
	{
		return index;
	}

	for (size_t i = index + 1; i < size; ++i)
	{
		if (i == index)
		{
			set_size(size * 2);
		}
		if (container[i] == nullptr)
		{
			return i;
		}
	}

	return index;
}

template<class key, class value>
void hash_table<key, value>::set_size(int new_size)
{
	std::pair<key, value>** buf_container = container;

	initialize(new_size);

	for (size_t i = 0; i < size; ++i)
	{
		if (buf_container[i] != nullptr)
		{
			operator[](buf_container[i]->first) = buf_container[i]->second;
		}
	}
	size = new_size;
}

template<class key, class value>
void hash_table<key, value>::set_divide_size()
{
	divide_count_bits = divide.count();
}

template<class key, class value>
int hash_table<key, value>::calc_start(const std::bitset<64> any) const 
{
	int to_start_bit = any.size()-1;
	while (any[to_start_bit] != 1 && to_start_bit != -1)
	{
		--to_start_bit;
	}

	return to_start_bit;
}

template<class key, class value>
int hash_table<key, value>::calc_word_size(const std::bitset<64> any)const
{
	return calc_start(any) + 1;
}

template<class key, class value>
int hash_table<key, value>::find_key(key _key) const
{
	std::bitset<64> bin_key(_key);
	std::bitset<64> remainder;
	if (calc_start(divide) > calc_start(_key))
	{
		return bin_key.to_ullong();
	}

	int to_start_bit;

	to_start_bit = calc_start(bin_key);

	size_t j = divide_count_bits - 1;
	for (size_t i = to_start_bit; i > (to_start_bit - divide_count_bits); --i)
	{
		remainder[j] = bin_key[i];
		--j;
	}

	int difference;
	int it_bin_key = to_start_bit - divide_count_bits;
	remainder ^= divide;
	while (it_bin_key > -1)
	{
		difference = calc_start(remainder) - calc_start(divide);


		if (it_bin_key + difference < 0)
		{
			break;
		}

		if (difference < 0)
		{
			std::bitset<64> buf_remainder;
			buf_remainder.reset();
			int it_remainder = 0 - difference;
			for (size_t i = 0; i != calc_start(remainder) + 1; ++i)
			{
				buf_remainder[it_remainder] = remainder[i];
				++it_remainder;
			}
			it_remainder = -1 - difference;
			while (it_remainder > -1)
			{
				buf_remainder[it_remainder] = bin_key[it_bin_key];
				--it_remainder;
				--it_bin_key;
			}
			remainder = buf_remainder;
		}
		remainder ^= divide;

	}

	int int_remainder = remainder.to_ullong();
	int i = int_remainder;

	while (container[i]->first != _key && i != int_remainder)
	{
		++i;
		if (i == size - 1)
		{
			i = 0;
		}
	}

	return i;
}