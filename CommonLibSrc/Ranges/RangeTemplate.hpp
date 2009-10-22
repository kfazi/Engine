#error Don't include this file!

template<typename TType>
class RangeTemplate
{
	public:
		/* Input/forward ranges: */
		bool IsEmpty() const;
		TType& Front();
		TType& PopFront();

		/* Bidirectional ranges: */
		TType& Back();
		TType& PopBack();

		/* Random access ranges: */
		TType& At(unsigned int iIndex);
		TType& operator[] (unsigned int iIndex);
};

/* EOF */
