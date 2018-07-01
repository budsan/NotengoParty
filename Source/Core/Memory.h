#pragma once

#include <type_traits>
#include <stdint.h>

#if defined(DEBUG)
#include <assert.h>
#endif

template <typename S, typename T> class RPtr
{
	S _offset;
public:
	RPtr() { static_assert(std::is_integral<S>::value, "Integer required."); }
	RPtr(std::nullptr_t) : RPtr() { _offset = 0; }
	RPtr(T* other) : RPtr() { this->operator=(other); }

	T* operator -> ()
	{
#if defined(DEBUG)
		SYS_ASSERT(_offset != 0); // this is NULL
#endif

		return reinterpret_cast<T*>(((intptr_t*)&_offset) + _offset);
	}

	void operator = (T* other)
	{
		_offset = static_cast<S>( other != 0 ? ((intptr_t)other) - ((intptr_t)&_offset) : 0 );
	}

	void operator = (std::nullptr_t)
	{
		_offset = 0;
	}

	T& operator [] (size_t index)
	{
		T* ptr = operator->();
		return ptr[index];
	}
};

template <typename T> using RPtr8  = RPtr<uint8_t , T>;
template <typename T> using RPtr16 = RPtr<uint16_t, T>;
template <typename T> using RPtr32 = RPtr<uint32_t, T>;

template <size_t N> class StackAlloc
{
	void* heap;
	void* sPtr;

public:
	StackAlloc(void* _heap)
		: heap(_heap)
		, sPtr(_heap)
	{
	}

	template <typename T>
	inline T* Alloc(size_t align = alignof(T))
	{
		return reinterpret_cast<T*>(Alloc(sizeof(T), align));
	}

	void* HeapPtr()
	{
		return heap;
	}

	void* Alloc(size_t s, size_t align)
	{
		intptr_t addr = (intptr_t)sPtr;
		uint8_t* sPtrAligned = (uint8_t*)((addr + (align - 1)) & ~(align - 1));
		sPtr = sPtrAligned + s;

		bool notOutOfHeap = sPtr < ((uint8_t*)heap + N);

#if defined(DEBUG)
		SYS_ASSERT(notOutOfHeap);
#endif

		return notOutOfHeap ? sPtrAligned : nullptr;
	}

	void DeallocAll()
	{
		sPtr = heap;
	}

	inline uint32_t GetCurrentOffset()
	{
		return (uint32_t)((uint8_t*)sPtr - (uint8_t*)heap);
	}
};
