/* Please refer to license.txt */

#pragma once

#include <iostream>

namespace GEngine
{

namespace mdata
{

//Argh, I really need to program a doubly linked list, linked list, and binary tree here.
//Or find a good library supplying these.

//Really, just a wrapper to x, y, z, so that I only have to manage one variable instead of three.
class Location3D
{
public:
	long x, y, z;

	Location3D()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	//Sets all three variables at once.
	void set(long X, long Y, long Z)
	{
		x = X;
		y = Y;
		z = Z;
	}
};

template <typename T>
class DoublyLinkedList
{
private:
	DoublyLinkedList *next_neighbor, *previous_neighbor;
	T *the_data;
	bool delete_data;

public:
	DoublyLinkedList()
	{
		next_neighbor = nullptr;
		previous_neighbor = nullptr;

		delete_data = true;

		the_data = nullptr;
	}

	DoublyLinkedList(T &_data, bool copy = false)
	{
		next_neighbor = nullptr;
		previous_neighbor = nullptr;

		if (copy)
		{
			the_data = new T;
			*the_data = _data;
			delete_data = true;
		}
		else
		{
			the_data = &_data;
			delete_data = false;
		}
	}

	~DoublyLinkedList()
	{
		if (delete_data && the_data)
		{
			delete the_data;
		}
		the_data = nullptr;

		if (next_neighbor && previous_neighbor)
		{
			//Has a left and right neighbor. Splice this guy out.
			next_neighbor->previous_neighbor = previous_neighbor;
			previous_neighbor->next_neighbor = next_neighbor;
			next_neighbor = nullptr;
			previous_neighbor = nullptr;
		}
		else if (next_neighbor)
		{
			//It's the start of the line. Make the next one the start of the line.
			next_neighbor->previous_neighbor = nullptr;
			next_neighbor = nullptr;
		}
		else if (previous_neighbor)
		{
			//It's the end of the line. Make the previos one the end of the line.
			previous_neighbor->next_neighbor = nullptr;
			previous_neighbor = nullptr;
		}
	}

	void alloc(T &_data, bool copy)
	{
		if (the_data && delete_data)
		{
			delete the_data;
		}

		if (copy)
		{
			the_data = new T;
			*the_data = _data;
			delete_data = true;
		}
		else
		{
			the_data = &_data;
			delete_data = false;
		}
	}

	void allocNext()
	{
		if (next_neighbor) //Make sure it doesn't already exist.
		{
			//Does. That's bad.
			std::cout << "*** mdata::DoublyLinkedList *** ERROR IN FUNCTION allocNext(): DoublyLinkedList already already has next_neighbor on line" << __LINE__ << " in file \"" << __FILE__ <<  "\"\n";
			throw; //TODO: It's error time again -- they got you runnin' through the night! It's a terrifying time~
		}

		next_neighbor = new DoublyLinkedList();
		next_neighbor->previous_neighbor = this;
	}

	void allocNext(T &_data, bool copy = false)
	{
		if (next_neighbor) //Make sure it doesn't already exist.
		{
			//Does. That's bad.
			std::cout << "*** mdata::DoublyLinkedList *** ERROR IN FUNCTION allocNext(): DoublyLinkedList already already has next_neighbor on line" << __LINE__ << " in file \"" << __FILE__ <<  "\"\n";
			throw; //TODO: It's error time again -- they got you runnin' through the night! It's a terrifying time~
		}
		next_neighbor = new DoublyLinkedList(_data, copy);
		next_neighbor->previous_neighbor = this;
	}

	void allocPrevious()
	{
		if (previous_neighbor) //Make sure it doesn't already exist.
		{
			//Does. That's bad.
			std::cout << "*** mdata::DoublyLinkedList *** ERROR IN FUNCTION allocPrevious(): DoublyLinkedList already already has previous_neighbor on line" << __LINE__ << " in file \"" << __FILE__ <<  "\"\n";
			throw; //TODO: It's error time again -- they got you runnin' through the night! It's a terrifying time~
		}
		previous_neighbor = new DoublyLinkedList();
		previous_neighbor->next_neighbor = this;
	}

	void allocPrevious(T &_data, bool copy = false)
	{
		if (previous_neighbor) //Make sure it doesn't already exist.
		{
			//Does. That's bad.
			std::cout << "*** mdata::DoublyLinkedList *** ERROR IN FUNCTION allocPrevious(): DoublyLinkedList already already has previous_neighbor on line" << __LINE__ << " in file \"" << __FILE__ <<  "\"\n";
			throw; //TODO: It's error time again -- they got you runnin' through the night! It's a terrifying time~
		}
		previous_neighbor = new DoublyLinkedList(_data, copy);
		previous_neighbor->next_neighbor = this;
	}

	DoublyLinkedList* next()
	{
		return next_neighbor;
	}

	DoublyLinkedList* previous()
	{
		return previous_neighbor;
	}

	T* data()
	{
		return the_data;
	}
};

} //namespace mdata

} //namespace GEngine
