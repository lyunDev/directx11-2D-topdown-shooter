#pragma once

#include <queue>
#include <memory>
#include <stdexcept>

#define DEFAULT_CHUNK_SIZE 10


template<typename T>
class ObjectPool
{
private :
	queue<shared_ptr<T>> freeList;
	size_t chunkSize;
	ObjectPool(const ObjectPool<T>& src);
	ObjectPool operator= (const ObjectPool<T>&rhs);

public :
	ObjectPool(size_t chunkSize = DEFAULT_CHUNK_SIZE) throw (invalid_argument, bad_alloc);
	virtual ~ObjectPool(void);

	shared_ptr<T> AccquireObject();
	void ReleaseObject(shared_ptr<T> obj);

};

template<typename T>
ObjectPool<T>::ObjectPool(size_t chunkSize)
	throw (std::invalid_argument, bad_alloc)
{
	if (chunkSize <= 0)
		throw std::invalid_argument("Chunk size should be positive value");

	this->chunkSize = chunkSize;

	for (int i = 0; i < this->chunkSize; i++)
	{
		freeList.push(make_shared<T>());
	}
}

template<typename T>
shared_ptr<T> ObjectPool<T>::AccquireObject()
{
	if (freeList.empty())
	{
		for (int i = 0; i < chunkSize; i++)
		{
			freeList.push(make_shared<T>());
		}
	}

	auto obj = freeList.front();
	freeList.pop();
	
	return obj;
}

template<typename T>
void ObjectPool<T>::ReleaseObject(shared_ptr<T> obj)
{
	freeList.push(obj);
}


template<typename T>
ObjectPool<T>::~ObjectPool(void)
{
}