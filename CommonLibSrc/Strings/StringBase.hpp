#ifndef COMMON_STRING_BASE_HPP
#define COMMON_STRING_BASE_HPP

#include "../Internal.hpp"
#include "../Containers/Vector.hpp"
#include "../Algorithms/Copy.hpp"
#include "StringStatic.hpp"

namespace Common
{

template<typename CharType> class StringIterator;

template<typename CharType> class StringBase: protected StringStatic
{
	public:
		typedef StringBase<CharType> MyType;
		typedef typename Vector<CharType>::Iterator Iterator;
		typedef typename Vector<CharType>::ConstIterator ConstIterator;
		typedef typename Vector<CharType>::ReverseIterator ReverseIterator;
		typedef typename Vector<CharType>::ConstReverseIterator ConstReverseIterator;

		StringBase()
		{
			mBuffer.Allocate(GetBaseCapacity());
			mBuffer.Resize(1, 0);
		}

		StringBase(size_t capacity) : mBuffer(capacity + 1)
		{
			mBuffer.Resize(1, 0);
		}

		StringBase(const MyType& string) : mBuffer(string.mBuffer)
		{
		}

		StringBase(const CharType* plainString)
		{
			size_t length = 1;
			while (plainString[length - 1])
				length++;
			CopyFromPlainString(plainString, length);
		}

		StringBase(const CharType* plainString, size_t length)
		{
			CopyFromPlainString(plainString, length + 1);
		}

		~StringBase()
		{
		}

		/*!
		 * Returns iterator pointing to first character.
		 *
		 * \return Iterator pointing to first character.
		 */
		Iterator Begin()
		{
			return mBuffer.Begin();
		}

		/*!
		 * Returns iterator pointing to first character.
		 *
		 * \return Iterator pointing to first character.
		 */
		ConstIterator Begin() const
		{
			return mBuffer.Begin();
		}

		/*!
		 * Returns iterator pointing to after the last character.
		 *
		 * \return Iterator pointing to after the last character.
		 */
		Iterator End()
		{
			return mBuffer.End();
		}

		/*!
		 * Returns iterator pointing to after the last character.
		 *
		 * \return Iterator pointing to after the last character.
		 */
		ConstIterator End() const
		{
			return mBuffer.End();
		}

		/*!
		 * Returns iterator pointing to the last character.
		 *
		 * \return Iterator pointing to the last character.
		 */
		ReverseIterator ReverseBegin()
		{
			return mBuffer.ReverseBegin();
		}

		/*!
		 * Returns iterator pointing to the last character.
		 *
		 * \return Iterator pointing to the last character.
		 */
		ConstReverseIterator ReverseBegin() const
		{
			return mBuffer.ReverseBegin();
		}

		/*!
		* Returns iterator pointing to character one before first.
		*
		* \return Iterator pointing to character one before first.
		 */
		ReverseIterator ReverseEnd()
		{
			return mBuffer.ReverseEnd();
		}

		/*!
		 * Returns iterator pointing to character one before first.
		 *
		 * \return Iterator pointing to character one before first.
		 */
		ConstReverseIterator ReverseEnd() const
		{
			return mBuffer.ReverseEnd();
		}

		void Allocate(size_t newCapacity)
		{
			mBuffer.Allocate(newCapacity);
		}

		size_t GetLength() const
		{
			return mBuffer.GetLength() - 1;
		}

		size_t GetCapacity() const
		{
			return mBuffer.GetCapacity();
		}

		void Clear()
		{
			mBuffer.Resize(1, 0);
			mBuffer[0] = 0;
		}

		bool IsEmpty() const
		{
			return mBuffer.GetLength() == 0;
		}

		CharType& operator[] (size_t index)
		{
			return mBuffer[index];
		}

		const CharType& operator[] (size_t index) const
		{
			return mBuffer[index];
		}

		CharType At(size_t index) const
		{
			return mBuffer[index];
		}

		MyType& operator+= (const MyType& string)
		{
			size_t length = GetLength();
			size_t new_capacity = length + string.GetLength() + 1;
			mBuffer.Resize(new_capacity, 0);
			Copy(string.mBuffer.Begin(), string.mBuffer.End(), mBuffer.Begin() + length);
			return *this;
		}

		MyType& operator+= (const CharType* plainString)
		{
			MyType string(plainString);
			*this += string;
			return *this;
		}

		MyType& operator+= (CharType plainChar)
		{
			mBuffer.Resize(GetLength() + 2, 0);
			mBuffer[GetLength()] = plainChar;
			return *this;
		}

		MyType& operator= (const MyType& string)
		{
			mBuffer = string.mBuffer;
			return *this;
		}

		MyType& operator= (const CharType* plainString)
		{
			MyType string(plainString);
			*this = string;
			return *this;
		}

		MyType& operator= (CharType plainChar)
		{
			mBuffer.Resize(2, 0);
			mBuffer[0] = plainChar;
			return *this;
		}

		const CharType *GetRaw() const
		{
			return &mBuffer[0];
		}

	private:
		Vector<CharType> mBuffer;

		void CopyFromPlainString(const CharType* plainString, size_t length)
		{
			if (length < GetBaseCapacity())
				mBuffer.Allocate(GetBaseCapacity());
			mBuffer.Resize(length, 0);
			Copy(plainString, plainString + length, mBuffer.Begin());
		}
};

}

#endif /* COMMON_STRING_BASE_HPP */

/* EOF */
