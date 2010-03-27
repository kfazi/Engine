#include "OutputStream.hpp"
#include "../Algorithms/Swap.hpp"

namespace Common
{

void OutputStream::IntegerToString(unsigned long long value)
{
	static const char digits_upper_case[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A',
		'B', 'C', 'D', 'E', 'F' };
	static const char digits_lower_case[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a',
		'b', 'c', 'd', 'e', 'f' };

	String& result = GetWriteBuffer();
	size_t start_index = result.GetLength();
	int base = GetBase();
	const char* digits;
	if (GetNumberUpperCase())
		digits = digits_upper_case;
	else
		digits = digits_lower_case;
	do 
	{
		result += digits[value % base];
		value /= base;
	}
	while (value > 0);
	if (GetAddBase())
	{
		switch (GetBase())
		{
		case BINARY:
			if (GetBaseUpperCase())
				result += "B0";
			else
				result += "b0";
			break;
		case OCTAL:
			result += "0";
			break;
		case DECIMAL:
			break;
		case HEXADECIMAL:
			if (GetBaseUpperCase())
				result += "X0";
			else
				result += "x0";
			break;
		}
	}
	SwapRange(&result[0] + start_index, &result[0] + result.GetLength());
}

OutputStream& OutputStream::operator<< (bool value)
{
	String& result = GetWriteBuffer();
	if (GetBoolAlpha())
	{
		String temp = (value) ? "true" : "false";
		if (GetNumberUpperCase())
			temp.ToUpper();
		result += temp;
	}
	else
		result += (value) ? "1" : "0";
	return *this;
}

OutputStream& OutputStream::operator<< (short value)
{
	return *this;
}

OutputStream& OutputStream::operator<< (unsigned short value)
{
	return *this;
}

OutputStream& OutputStream::operator<< (int value)
{
	return *this;
}

OutputStream& OutputStream::operator<< (unsigned int value)
{
	return *this;
}

OutputStream& OutputStream::operator<< (long value)
{
	return *this;
}

OutputStream& OutputStream::operator<< (unsigned long value)
{
	return *this;
}

OutputStream& OutputStream::operator<< (long long value)
{
	return *this;
}

OutputStream& OutputStream::operator<< (unsigned long long value)
{
	return *this;
}

OutputStream& OutputStream::operator<< (float value)
{
	return *this;
}

OutputStream& OutputStream::operator<< (double value)
{
	return *this;
}

OutputStream& OutputStream::operator<< (long double value)
{
	return *this;
}

OutputStream& OutputStream::operator<< (const void* value)
{
	return *this;
}

}

/* EOF */
