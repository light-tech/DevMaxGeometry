/*
 * Basic container data structure using array
 *
 * Author: Lightech (lightech@outlook.com)
 *
 * Public Domain.
 */

#ifndef _ARRAY_H_
#define _ARRAY_H_

#include "DevMax.h"

template<typename E>
class Array
{
public:
	E *data;
	int length;

	Array()
	{
		data = nullptr;
		capacity = length = 0;
	}

	void Free()
	{
		if (data != nullptr)
		{
			free(data);
			data = nullptr;
			capacity = length = 0;
		}
	}

	template<typename TAction>
	void ForEach(TAction action)
	{
		for(int i = 0; i < length; i++)
			action(data[i]);
	}

	E& operator[](int p)
	{
		return data[p];
	}

	void Reserve(int size)
	{
		if (capacity > size)
			return;

		data = (E*)realloc(data, sizeof(E) * size);
		capacity = size;
	}

	void Reserve(int size, E initial_value)
	{
		if (capacity > size)
			return;

		data = (E*)realloc(data, sizeof(E) * size);
		capacity = size;
		for(int i = length; i < capacity; i++)
			data[i] = initial_value;
	}

	template<typename TPrintElement>
	void Print(TPrintElement print_element)
	{
		if (length < 0)
			PrintString("[invalid_array: length < 0]");

		PrintString("[");
		if (length > 0)
			print_element(data[0]);
		for(int i = 1; i < length; i++)
		{
			PrintString(",");
			print_element(data[i]);
		}
		PrintString("]");
	}

	void Append(E e)
	{
		if (length == capacity)
			Reserve(2 * length + 1);

		data[length] = e;
		length++;
	}

	void Insert(int p, E e)
	{
		if (length == capacity)
			Reserve(2 * length + 1);

		for(int i = length - 1; i >= p; i--)
			data[i+1] = data[i];
		data[p] = e;
		length++;
	}

private:
	int capacity;
};

#endif /* _ARRAY_H_ */