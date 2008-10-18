#include "engine.hpp"
#include "useful.hpp"
#include <cstdio>
#include <exception>

using namespace engine;

int main()
{
	try
	{
		while (1)
		{
			CEngine::GetInstance()->ProcessFrame();
		}
	}
	catch (std::exception &e)
	{
		printf("%s\n", e.what());
	}
	return 0;
}

