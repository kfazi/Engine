#ifndef COMMON_STRING_STATIC_HPP
#define COMMON_STRING_STATIC_HPP

#include "../Internal.hpp"
#include "../Containers/HashMap.hpp"
#include "CharTypes.hpp"

namespace Common
{

class COMMONDLLIMPORTEXPORT StringStatic
{
	public:
/*
 * Code point value
 * |   Name
 * |   |                      General category
 * |   |                      |  Combining class
 * |   |                      |  | Bidirectional category
 * |   |                      |  | | Decomposition
 * |   |                      |  | | |Decimal digit value
 * |   |                      |  | | ||Digit value
 * |   |                      |  | | |||Numeric value
 * |   |                      |  | | ||||Mirrored
 * |   |                      |  | | ||||| Unicode 1.0 name
 * |   |                      |  | | ||||| |10646 comment field
 * |   |                      |  | | ||||| ||Uppercase mapping
 * |   |                      |  | | ||||| |||Lowercase mapping
 * |   |                      |  | | ||||| ||||    Titlecase mapping
 * 0041;LATIN CAPITAL LETTER A;Lu;0;L;;;;;N;;;;0061;
 */
		struct CharacterData
		{
			CharUTF32 UppercaseMapping;
			CharUTF32 LowercaseMapping;
			CharUTF32 TitlecaseMapping;
		};

		static void Initialize();

	protected:
		static size_t GetBaseCapacity()
		{
			return sBaseCapacity;
		}

		static const CharacterData* GetCharacterData(const CharUTF32& character);

	private:
		static const size_t sBaseCapacity;
		static HashMap<CharUTF32, CharacterData> sCharacterDataMap;
};

}

#endif /* COMMON_STRING_STATIC_HPP */

/* EOF */
