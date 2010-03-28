#error Don't include this file!

template<typename Type>
class RangeTemplate
{
	public:
		/* For input only ranges return types are const. */

		/* All ranges: */
		bool IsEmpty() const;

		/* Finite ranges: */
		size_t GetLength() const;

		/* Input/forward ranges: */
		Type& Front();
		Type& PopFront();

		/* Bidirectional ranges: */
		Type& Back();
		Type& PopBack();

		/* Output ranges: */
		void Put(const Type& value);

		/* Random access ranges: */
		Type& At(size_t index);
		Type& operator[] (size_t index);
};

/* EOF */
