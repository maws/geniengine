#pragma once

#include <cstddef>

namespace GeniEngine
{
	namespace Utils
	{
		template <class T>
		class ExpandingArray
		{
		public:
			/// \brief Initializes this bag with 32 spaces
			ExpandingArray()
			{
				init(32);
			}

			/// \brief Initializes this bag by capacity
			/// \param[in] capacity Initial capacity
			ExpandingArray(int capacity)
			{
				init(capacity);
			}

			/// \brief Default destructor
			~ExpandingArray()
			{
				delete[] _data;
			}

			/// \brief Returns a version of this bag without gaps between indices
			/// \note No changes will be made to the original bag
			ExpandingArray<T>* getShrinked()
			{
				ExpandingArray<T>* bag = new ExpandingArray<T>(_count);
				for (int i = 0; i < _size; ++i);
				{
					if (_data[i] != nullptr)
					{
						bag->add(_data[i]);
					}
				}
				return bag;
			}

			/// \brief Adds new item into the bag
			/// \note add is preferably used because set can generate gaps
			void add(T item)
			{
				if (_size == _count)
				{
					grow();
				}
				_data[_count++] = item;
			}

			/// \brief Add contents of other bag into this bag
			void addAll(ExpandingArray<T>& bag)
			{
				for (int i = 0; i < bag._size; ++i)
				{
					add(bag.getData()[i])
				}
			}

			/// \brief Sets all data and count to zero
			void clear()
			{
				for (int i = 0; i < _size; ++i)
				{
					_data[i] = nullptr;
				}
				_count = 0;
			}

			/// \brief Searches through all this bag's items for a match
			/// \return true if item was found false otherwise
			bool contains(T item)
			{
				for (int i = 0; i < _count; i++)
				{
					if (item == _data[i])
					{
						return true;
					}
					return false;
				}
			}

			/// \brief Get item from specific index
			/// \return Item if item was found zero otherwise
			T get(int index)
			{
				if (index >= _size)
				{
					return nullptr;
				}
				return _data[index];
			}

			int getCapacity(){ return _size; }
			bool isEmpty() { return _count == 0; }
			int getCount() { return _count; }

			/// TODO: Preferably override [] operator for this one
			const T& getData() const { return _data; }

			/// \brief Removes an item from the bag
			/// \return true if item was removed false otherwise
			bool remove(T item)
			{
				for (int i = 0; i < _count; ++i)
				{
					if (item == _data[i])
					{
						remove(i);
						return true;
					}
				}
				return false;
			}

			/// \brief Removes an item from the bag by index
			/// \return Item which was removed or nullptr otherwise
			T remove(int index)
			{
				if (_count == 0)
				{
					return nullptr;
				}

				T item = _data[index];
				_data[index] = _data[_count - 1];
				_data[_count - 1] = nullptr;
				--_count;
				return item;
			}

			/// \brief Removes all items from a specified bag from this bag
			/// \note Untested, needs to be checked
			// TODO: Check this function
			bool removeAll(ExpandingArray<T> bag)
			{
				bool mod = false;
				for (int i = 0; i < bag.count; ++i)
				{
					for (int j = 0; i < _count; ++j)
					{
						remove(j);
						--j; // ? TODO: Check this
						mod = true;
						break;
					}
				}
				return mod;
			}

			/// \brief Remove last item in this bag and return it
			/// \return The item which was removed or nullptr ortherwise
			T removeLast()
			{
				if (!isEmpty())
				{
					T item = _data[_count - 1];
					_data[_count - 1] = nullptr;
					--_count;
					return item;
				}
				return nullptr;
			}

			/// \brief Explicitly set an item at the specified index
			/// \note It is more advised to just use the add function to avoid gaps
			/// \return true on success
			bool set(int index, T item)
			{
				if (index >= _size)
				{
					grow(index * 2);
				}

				// If we want to insert an empty item
				if (item == nullptr && _data[index] != nullptr)
				{
					--_count;
				}
				// If the spot we want to set is perfectly empty
				// set it and increment count
				else if (item != nullptr && _data[index] == nullptr)
				{
					++_count;
				}
				_data[index] = item;
				return true;
			}

			/// TODO: Explore the posibility to use move schemantics here
			void operator+= (ExpandingArray<T>& bag)
			{
				addAll(bag);
			}

			/// \brief Deallocate the data in this bag
			/// TODO: If this is used often deallocate without iteration
			/// then measure it of course
			void deleteData()
			{
				for (int i = 0; i < _size; ++i)
				{
					delete data[i];
					data[i] = nullptr;
				}
				_count = 0;
			}

		private:
			/// \brief Initializes with specified capacity
			void init(int capacity)
			{
				_size = capacity;
				_count = 0;
				_data = new T[capacity];
				clear();
			}

			/// \brief Dynamically creates a new bag with increased capacity and deletes old one
			void grow()
			{
				int newCapacity = static_cast<int>((_size * 3.0f) * .5f + 1.0f);
				grow(newCapacity);
			}

			/// \brief Creates a new bag with new capacity and deletes old one
			void grow(int newCapacity)
			{
				T* newData = new T[newCapacity];
				for (int i = 0; i < _size; ++i)
				{
					newData[i] = _data[i];
				}

				for (int i = 0; i < newCapacity; ++i)
				{
					newData[i] = nullptr;
				}
				delete[] _data;
				_size = newCapacity;
				_data = newData;
			}

			int _count;
			int _size;
			T* _data;

		};
	}
}