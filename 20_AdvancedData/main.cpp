#include "AdvancedDataApplication.h"
#include <memory>

int main()
{
	std::unique_ptr<AdvancedDataApplication> application(new AdvancedDataApplication("Cubemap", 800, 600));

	try
	{
		application->Run();
	}
	catch (const GameException& exception)
	{
		std::cerr << exception.what() << "\n";
	}
}