/* Copyright (C) 2005-2020, UNIGINE. All rights reserved.
 *
 * This file is a part of the UNIGINE 2 SDK.
 *
 * Your use and / or redistribution of this software in source and / or
 * binary form, with or without modification, is subject to: (i) your
 * ongoing acceptance of and compliance with the terms and conditions of
 * the UNIGINE License Agreement; and (ii) your inclusion of this notice
 * in any version of this software that you use or redistribute.
 * A copy of the UNIGINE License Agreement is available by contacting
 * UNIGINE. at http://unigine.com/
 */


#pragma once

#include <UnigineVector.h>

namespace Unigine
{

template<typename Type>
struct Hasher
{
	using HashType = unsigned long long int;
	UNIGINE_INLINE static HashType create(const Type &t)
	{
		static_assert(sizeof(Type) == 0 && false, "Hash function undefined.");
		return 0;
	}
};

template<typename Type>
struct Hasher <Type *>
{
	using HashType = uintptr_t;
	UNIGINE_INLINE static HashType create(Type *t) { return HashType(t); }
};

template<typename Type>
struct Hasher <const Type *>
{
	using HashType = uintptr_t;
	UNIGINE_INLINE static HashType create(const Type *t) { return HashType(t); }
};

#define DECLARE_DEFAULT_HASHER(TYPE) \
template<> \
struct Hasher <TYPE> \
{ \
	using HashType = unsigned TYPE; \
	UNIGINE_INLINE static HashType create(TYPE t) { return t; } \
}; \
template<> \
struct Hasher <unsigned TYPE> \
{ \
	using HashType = unsigned TYPE; \
	UNIGINE_INLINE static HashType create(unsigned TYPE t) { return t; } \
};

DECLARE_DEFAULT_HASHER(char)
DECLARE_DEFAULT_HASHER(int)
DECLARE_DEFAULT_HASHER(short)
DECLARE_DEFAULT_HASHER(long int)
DECLARE_DEFAULT_HASHER(long long int)
#undef DECLARE_DEFAULT_HASHER

#define HASH_LOAD_FACTOR (0.85f)

template <typename Key, typename Data, typename HashType, typename Counter = unsigned int>
class Hash
{
public:

	template<typename IteratorType, typename IteratorPtrType>
	class IteratorTemplate
	{

		IteratorPtrType ptr;
		IteratorPtrType end;

	public:

		UNIGINE_INLINE IteratorTemplate() : ptr(nullptr), end(nullptr) { }
		UNIGINE_INLINE IteratorTemplate(IteratorPtrType p, IteratorPtrType e) : ptr(p), end(e) { }
		UNIGINE_INLINE IteratorTemplate(const IteratorTemplate &o) : ptr(o.ptr), end(o.end) { }
		UNIGINE_INLINE IteratorTemplate &operator=(const IteratorTemplate &o) { ptr = o.ptr; end = o.end; return *this; }

		UNIGINE_INLINE IteratorTemplate &operator++() { next(); return *this; }
		UNIGINE_INLINE IteratorTemplate operator++(int) { Iterator ret = *this; next(); return ret; }

		template<typename T0, typename T1>
		UNIGINE_INLINE bool operator!=(const IteratorTemplate<T0, T1> &o) const { return ptr != o.get(); }
		template<typename T0, typename T1>
		UNIGINE_INLINE bool operator==(const IteratorTemplate<T0, T1> &o) const { return ptr == o.get(); }
		template<typename T0, typename T1>
		UNIGINE_INLINE bool operator<(const IteratorTemplate<T0, T1> &it) const { return ptr < it.get(); }
		template<typename T0, typename T1>
		UNIGINE_INLINE bool operator>(const IteratorTemplate<T0, T1> &it) const { return ptr > it.get(); }
		template<typename T0, typename T1>
		UNIGINE_INLINE bool operator<=(const IteratorTemplate<T0, T1> &it) const { return ptr <= it.get(); }
		template<typename T0, typename T1>
		UNIGINE_INLINE bool operator>=(const IteratorTemplate<T0, T1> &it) const { return ptr >= it.get(); }

		UNIGINE_INLINE IteratorType &operator*() { return **ptr; }
		UNIGINE_INLINE IteratorType *operator->() { return *ptr; }
		UNIGINE_INLINE IteratorType &operator*() const { return **ptr; }
		UNIGINE_INLINE IteratorType *operator->() const { return *ptr; }

		UNIGINE_INLINE IteratorPtrType get() const { return ptr; }

		using key_type = Key;
		using value_type = IteratorType;
		using iterator_category = std::forward_iterator_tag;
		using difference_type = Counter;
		using pointer = IteratorPtrType;
		using reference = IteratorType &;

	private:

		UNIGINE_INLINE void next()
		{
			if (ptr < end)
				while (++ptr != end && *ptr == nullptr);
		}

	};

	using Iterator = IteratorTemplate<Data, Data **>;
	using ConstIterator = IteratorTemplate<const Data, const Data * const *>;

	using iterator = Iterator;
	using const_iterator = ConstIterator;

public:

	void swap(Hash &hash)
	{
		if (data == hash.data)
			return;
		Counter tmp = length;
		length = hash.length;
		hash.length = tmp;

		tmp = capacity;
		capacity = hash.capacity;
		hash.capacity = tmp;

		Data **d = data;
		data = hash.data;
		hash.data = d;
	}

	UNIGINE_INLINE Counter size() const { return length; }
	UNIGINE_INLINE Counter space() const { return capacity; }
	UNIGINE_INLINE size_t getMemoryUsage() const
	{
		size_t ret = 0;
		ret += sizeof(length);
		ret += sizeof(capacity);
		ret += sizeof(Data *);
		ret += length * sizeof(Data);
		ret += capacity * sizeof(Data *);
		return ret;
	}
	UNIGINE_INLINE Counter empty() const { return length == 0; }

	UNIGINE_INLINE bool contains(const Key &key) const { return length != 0 && do_find(key) != nullptr; }

	UNIGINE_INLINE Iterator find(const Key &key)
	{
		if (length == 0)
			return end();
		Data **d = do_find(key);
		Data **e = data + capacity;
		return d == nullptr ? Iterator(e, e) : Iterator(d, e);
	}

	UNIGINE_INLINE Data **findFast(const Key &key) const { return do_find(key); }

	UNIGINE_INLINE ConstIterator find(const Key &key) const
	{
		if (length == 0)
			return end();
		const Data * const *d = do_find(key);
		const Data * const *e = data + capacity;
		return d == nullptr ? ConstIterator(e, e) : ConstIterator(d, e);
	}

	UNIGINE_INLINE Vector<Key> keys() const
	{
		Vector<Key> keys;
		getKeys(keys);
		return keys;
	}

	UNIGINE_INLINE void getKeys(Vector<Key> &keys) const
	{
		keys.allocate(keys.size() + length);
		for (Counter i = 0; i < capacity; ++i)
		{
			if (data[i] == nullptr)
				continue;
			keys.appendFast(data[i]->key);
		}
	}
	
	UNIGINE_INLINE const Key &getKey(int num) const { return data[num]->key; }
	UNIGINE_INLINE Key &getKey(int num) { return data[num]->key; }

	UNIGINE_INLINE bool remove(const Key &key) { return do_remove(Hasher<Key>::create(key), key); }
	UNIGINE_INLINE bool remove(const Iterator &it) { return do_remove(it->hash, it->key); }
	UNIGINE_INLINE bool remove(const ConstIterator &it) { return do_remove(it->hash, it->key); }

	UNIGINE_INLINE bool erase(const Key &key) { return do_remove(Hasher<Key>::create(key), key); }

	template<typename IteratorType, typename IteratorPtrType>
	UNIGINE_INLINE IteratorTemplate<IteratorType, IteratorPtrType> erase(const IteratorTemplate<IteratorType, IteratorPtrType> &it)
	{
		do_remove(it->hash, it->key);
		if (*it.get())
			return it;

		auto ret = it;
		return ++ret;
	}

	UNIGINE_INLINE void clear()
	{
		length = 0;
		for (Counter i = 0; i < capacity; ++i)
		{
			delete data[i];
			data[i] = nullptr;
		}
	}

	UNIGINE_INLINE void destroy()
	{
		for (Counter i = 0; i < capacity; ++i)
			delete data[i];

		delete [] data;
		data = nullptr;
		length = 0;
		capacity = 0;
	}

	void reserve(Counter size)
	{
		Counter v = static_cast<Counter>(float(size) / HASH_LOAD_FACTOR + 0.5f);
		if (v <= capacity)
			return;
		rehash(round_up(v));
	}

	void shrink()
	{
		if (capacity == 0)
			return;
		if (length == 0)
		{
			destroy();
			return;
		}
		Counter v = static_cast<Counter>(float(length) / HASH_LOAD_FACTOR + 0.5f);
		if (v >= capacity)
			return;
		rehash(round_up(v));
	}

	UNIGINE_INLINE Iterator begin()
	{
		Data **ptr = data;
		Data **end = data + capacity;
		while (ptr != end && *ptr == nullptr)
			ptr++;
		return Iterator(ptr, end);
	}

	UNIGINE_INLINE Iterator end()
	{
		Data **end = data + capacity;
		return Iterator(end, end);
	}

	UNIGINE_INLINE ConstIterator begin() const
	{
		const Data * const *ptr = data;
		const Data * const *end = data + capacity;
		while (ptr != end && *ptr == nullptr)
			ptr++;
		return ConstIterator(ptr, end);
	}

	UNIGINE_INLINE ConstIterator cbegin() const
	{
		const Data * const *ptr = data;
		const Data * const *end = data + capacity;
		while (ptr != end && *ptr == nullptr)
			ptr++;
		return ConstIterator(ptr, end);
	}

	UNIGINE_INLINE ConstIterator end() const
	{
		const Data * const *end = data + capacity;
		return ConstIterator(end, end);
	}

	UNIGINE_INLINE ConstIterator cend() const
	{
		const Data * const *end = data + capacity;
		return ConstIterator(end, end);
	}

protected:

	UNIGINE_INLINE bool is_need_realloc() const { return (float(length + 1) / float(capacity + 1)) >= HASH_LOAD_FACTOR; }

	UNIGINE_INLINE void realloc(Counter *index = nullptr) { rehash(capacity == 0 ? 8 : capacity << 1, index); }

	UNIGINE_INLINE void rehash(Counter new_capacity, Counter *index = nullptr)
	{
		Data **new_data = new Data*[new_capacity];
		memset(new_data, 0, new_capacity * sizeof(Data *));
		
		if (data != nullptr)
		{
			Counter mask = (new_capacity - 1);
			for (Counter i = 0; i < capacity; ++i)
			{
				if (data[i] == nullptr)
					continue;
				Counter new_index = data[i]->hash & mask;
				while (new_data[new_index])
					new_index = (new_index + 1) & mask;
				new_data[new_index] = data[i];

				if (index && *index == i)
				{
					*index = new_index;
					index = nullptr;
				}
			}
			delete [] data;
		}

		data = new_data;
		capacity = new_capacity;
	}

	UNIGINE_INLINE Data **do_find(const Key &key) const
	{
		if (length == 0)
			return nullptr;
		HashType hash = Hasher<Key>::create(key);
		Counter index = hash & (capacity - 1);
		while (data[index])
		{
			if (data[index]->hash == hash && data[index]->key == key)
				return data + index;

			index = (index + 1) & (capacity - 1);
		}
		return nullptr;
	}

	UNIGINE_INLINE Data *do_append(HashType hash, const Key &key)
	{
		if (capacity == 0)
			realloc();
		Counter index = hash & (capacity - 1);
		while (data[index])
		{
			if (data[index]->hash == hash && data[index]->key == key)
				return *(data + index);

			index = (index + 1) & (capacity - 1);
		}
		Data *d = new Data(hash, key);
		data[index] = d;
		++length;
		if (is_need_realloc())
			realloc();
		return d;
	}

	UNIGINE_INLINE Data *do_append(const Key &key)
	{
		if (capacity == 0)
			realloc();
		HashType hash = Hasher<Key>::create(key);
		Counter index = hash & (capacity - 1);
		while (data[index])
		{
			if (data[index]->hash == hash && data[index]->key == key)
				return *(data + index);

			index = (index + 1) & (capacity - 1);
		}

		Data *d = new Data(hash, key);
		data[index] = d;
		++length;
		if (is_need_realloc())
			realloc();
		return d;
	}

	UNIGINE_INLINE Data *do_append(Key &&key)
	{
		if (capacity == 0)
			realloc();
		HashType hash = Hasher<Key>::create(key);
		Counter index = hash & (capacity - 1);
		while (data[index])
		{
			if (data[index]->hash == hash && data[index]->key == key)
				return *(data + index);

			index = (index + 1) & (capacity - 1);
		}

		Data *d = new Data(hash, std::move(key));
		data[index] = d;
		++length;
		if (is_need_realloc())
			realloc();
		return d;
	}

	UNIGINE_INLINE bool do_remove(HashType hash, const Key &key)
	{
		if (length == 0)
			return false;
		Counter index = hash & (capacity - 1);

		while (data[index])
		{
			if (data[index]->hash == hash && data[index]->key == key)
				break;
			index = (index + 1) & (capacity - 1);
		}

		if (data[index] == nullptr)
			return false;

		delete data[index];
		data[index] = nullptr;

		--length;
		rehash_data(index);
		return true;
	}

	UNIGINE_INLINE void rehash_data(Counter index)
	{
		Counter mask = (capacity - 1);
		index = (index + 1) & mask;

		#define CHECK(i) if (data[(index + i) & mask] == nullptr || (data[(index + i) & mask]->hash & mask) != ((index + i) & mask)) { index = (index + i) & mask; break; }
		while (data[index])
		{
			if ((data[index]->hash & mask) != index)
				break;
			CHECK(1)
			CHECK(2)
			CHECK(3)
			CHECK(4)
			CHECK(5)
			CHECK(6)
			index = (index + 7) & mask;
		}
		#undef CHECK

		while (data[index])
		{
			Data *d = data[index];
			data[index] = nullptr;

			Counter new_index = d->hash & mask;
			while (data[new_index])
				new_index = (new_index + 1) & mask;

			data[new_index] = d;
			index = (index + 1) & mask;
		}
	}

	UNIGINE_INLINE Counter round_up(Counter v)
	{
		v--;
		for (Counter i = 1; i < sizeof(v) * 8; i *= 2)
			v |= v >> i;
		return ++v;
	}

	Data ** data;
	Counter length;
	Counter capacity;

};

} // namespace Unigine
