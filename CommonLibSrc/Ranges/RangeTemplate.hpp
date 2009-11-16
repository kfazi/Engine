#error Don't include this file!

template<typename TType>
class RangeTemplate
{
	public:
		/* For input only ranges return types are const. */

		/* All ranges: */
		bool IsEmpty() const;

		/* Finite ranges: */
		unsigned int GetLength() const;

		/* Input/forward ranges: */
		TType& Front();
		TType& PopFront();

		/* Bidirectional ranges: */
		TType& Back();
		TType& PopBack();

		/* Output ranges: */
		void Put(TType& tValue);

		/* Random access ranges: */
		TType& At(unsigned int iIndex);
		TType& operator[] (unsigned int iIndex);
};

/* EOF */
