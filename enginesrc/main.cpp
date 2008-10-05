#include "engine.hpp"
#include "useful.hpp"
#include <cstdio>
#include <exception>

int main()
{
	try
	{
		engine::Log(engine::Format("%s\n") % engine::CEngine::GetInstance()->ToString());
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

