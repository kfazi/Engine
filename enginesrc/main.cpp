#include "engine.hpp"
#include "debug.hpp"
#include <cstdio>
#include <exception>

int main()
{
	try
	{
		kfz::Debug("%s\n", kfz::CEngine::GetInstance()->ToString().c_str());
		while (1)
		{
			kfz::CEngine::GetInstance()->ProcessFrame();
		}
	}
	catch (std::exception &e)
	{
		printf("%s\n", e.what());
	}
	return 0;
}

