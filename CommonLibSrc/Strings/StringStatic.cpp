#include "../Internal.hpp"
#include "StringStatic.hpp"

namespace Common
{

bool gStringStaticInitialized = false;

const size_t StringStatic::sBaseCapacity = 16;
HashMap<CharUTF32, StringStatic::CharacterData> StringStatic::sCharacterDataMap(251);

template<> struct DefaultHash<CharUTF32>
{
	size_t operator() (CharUTF32 data) const
	{
		return data;
	}
};

void StringStatic::Initialize()
{
	if (!gStringStaticInitialized)
	{
		gStringStaticInitialized = true;

		CharacterData character_data;
		character_data.LowercaseMapping = 0x0061;
		character_data.UppercaseMapping = 0x0041;
		character_data.TitlecaseMapping = 0x0061;
		sCharacterDataMap[0x0061] = character_data;
	}
}

const StringStatic::CharacterData* StringStatic::GetCharacterData(const CharUTF32& character)
{
	Assert(gStringStaticInitialized, "StringStatic is not initialized");
	if (sCharacterDataMap.Contains(character))
		return &sCharacterDataMap[character];
	else
		return NULL;
}

}

/* EOF */
