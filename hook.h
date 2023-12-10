#include "buffer.hpp"
#include <Windows.h>
#include "Register_x64.hpp"


namespace Utils
{
	typedef void(*HookHandle)(Register_x64*);
	class Hook
	{
	private:
		LPVOID Addr;
		HookHandle Handle;
		Buffer OldData;
		Buffer HookData;
		LPVOID RunData;
		void run();
	public:
		Hook(LPVOID adder, Buffer oldData, HookHandle Handle);
		Hook(LPVOID adder, size_t len, HookHandle Handle);
		~Hook();
	};
}
