#ifndef COMMON_SHARED_PTR_HPP
#define COMMON_SHARED_PTR_HPP

#include "../Internal.hpp"
#include "../Algorithms/Swap.hpp"
#include "DeletePolicy.hpp"
#include "DeleteArrayPolicy.hpp"

namespace Common
{

template <typename Type, typename Policy = DeletePolicy>
class SharedPtr
{
	template<typename Type2, typename Policy2> friend class SharedPtr;

	private:
		Type* mData;
		unsigned int* mCounter;

	public:
		typedef SharedPtr<Type, Policy> MyType;
		typedef Type ValueType;
		typedef Type* DataType;

		explicit SharedPtr(Type* data = NULL) : mData(data), mCounter(data ? new unsigned(1) : NULL)
		{
		}

		~SharedPtr()
		{
			if (mData && --(*mCounter) == 0)
			{
				delete mCounter;
				Policy::template Delete<Type>(mData);
			}
		}
		
		SharedPtr(const SharedPtr& sharedPointer) : mData(sharedPointer.mData),
			mCounter(sharedPointer.mCounter)
		{
			if (mData)
				(*mCounter)++;
		}

		SharedPtr& operator= (const SharedPtr& sharedPointer)
		{
			Reset<Type>(sharedPointer);
			return *this;
		}

		template <typename Type2, typename Policy2>
			explicit SharedPtr(const SharedPtr<Type2, Policy2>& sharedPointer) :
			mData(sharedPointer.mData), mCounter(sharedPointer.mCounter)
		{
			if (mData)
				(*mCounter)++;
		}

		template <typename Type2, typename Policy2>
			SharedPtr& operator= (const SharedPtr<Type2, Policy2>& sharedPointer)
		{
			Reset<Type2, Policy2>(sharedPointer);
			return *this;
		}

		Type& operator* () const
		{
			Assert(mData != NULL, "Data is NULL");
			return *mData;
		}

		Type* operator-> () const
		{
			Assert(mData != NULL, "Data is NULL");
			return mData;
		}

		Type& operator[] (size_t index) const
		{
			return mData[index];
		}

		inline friend bool operator== (const SharedPtr& sharedPtr, const Type* data)
		{
			return sharedPtr.mData == data;
		}
		
		inline friend bool operator== (const Type* data, const SharedPtr& sharedPtr)
		{
			return sharedPtr.mData == data;
		}

		inline friend bool operator!= (const SharedPtr& sharedPtr, const Type* data)
		{
			return sharedPtr.mData != data;
		}

		inline friend bool operator!= (const Type* data, const SharedPtr& sharedPtr)
		{
			return sharedPtr.mData != data;
		}

		template <typename Type2, typename Policy2>
			bool operator== (const SharedPtr<Type2, Policy2>& sharedPtr) const
		{
			return sharedPtr.mData == mData;
		}

		template <typename Type2, typename Policy2>
			bool operator!= (const SharedPtr<Type2, Policy2>& sharedPtr) const
		{
			return sharedPtr.mData != mData;
		}

		Type* Get() const
		{
			return mData;
		}

		void Swap(MyType& sharedPtr)
		{
			Common::Swap(sharedPtr.mData, mData);
			Common::Swap(sharedPtr.mCounter, mCounter);
		}

		void Reset(Type* data = NULL)
		{
			if (data == mData)
				return;
			MyType(data).Swap(*this);
		}

		template <typename Type2, typename Policy2>
			void Reset(const SharedPtr<Type2, Policy2>& sharedPtr)
		{
			SharedPtr<Type2, Policy2>(sharedPtr).Swap(*this);
		}

		bool Unique() const
		{
			return mCounter == NULL || *mCounter == 1;
		}

		bool IsNull()
		{
			return mData == NULL;
		}
};

}

#endif /* COMMON_SHARED_PTR_HPP */

/* EOF */
