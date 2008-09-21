#include "engine.hpp"
#include "debug.hpp"
#include <cstdio>
#include <exception>

int main()
{
	try
	{
		engine::Debug("%s\n", engine::CEngine::GetInstance()->ToString().c_str());
		while (1)
		{
			engine::CEngine::GetInstance()->ProcessFrame();
		}
	}
	catch (std::exception &e)
	{
		printf("%s\n", e.what());
	}
	return 0;
}

