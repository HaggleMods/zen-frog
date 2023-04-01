#include <sdk/SexySDK.hpp> //for deluxe
#include <MinHook.h>

static void (__fastcall* Sexy__Board__LoadLevel2_)(Sexy::Board*, char*, std::string*);
void __fastcall Sexy__Board__LoadLevel2(Sexy::Board* this_, char* edx, std::string* level_name)
{
	std::string next_level = "levels/doublehelix.dat";
	return Sexy__Board__LoadLevel2_(this_, edx, &next_level);
}

void init()
{
	MH_Initialize();

	MH_CreateHook((void*)0x00429D10, Sexy__Board__LoadLevel2, (void**)&Sexy__Board__LoadLevel2_);

	MH_EnableHook(MH_ALL_HOOKS);
}

DWORD WINAPI OnAttachImpl(LPVOID lpParameter)
{
	init();
	return 0;
}

DWORD WINAPI OnAttach(LPVOID lpParameter)
{
	__try
	{
		return OnAttachImpl(lpParameter);
	}
	__except (0)
	{
		FreeLibraryAndExitThread((HMODULE)lpParameter, 0xDECEA5ED);
	}

	return 0;
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls(hModule);
		CreateThread(nullptr, 0, OnAttach, hModule, 0, nullptr);
		return true;
	}

	return false;
}
