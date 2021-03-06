#include "FramebuffersApplication.h"
#include <memory>

int main()
{
	std::unique_ptr<FramebuffersApplication> application(new FramebuffersApplication("Frambuffers", 800, 600));

	try
	{
		application->Run();
	}
	catch (const GameException& exception)
	{
		std::cerr << exception.what() << "\n";
	}
}