#include "hook.h"

namespace Utils
{
	void _Handle(UINT64 rsp, HookHandle Handle)
	{
		Register_x64 reg(rsp);
		Handle(&reg);
	}

	void Hook::run()
	{
		Buffer writeData = Buffer({ 72, 129, 236, 0, 2, 0, 0, 80, 83, 81, 82, 85, 86, 87, 65, 80, 65, 81, 65, 82, 65, 83, 65, 84, 65, 85, 65, 86, 65, 87, 102, 156 })
			+ Buffer({ 72,139,204,72,186 }) + (UINT64)&this->Handle + Buffer({ 72,186 }) + (UINT64)&_Handle + Buffer({ 255,208 })
			+ Buffer({ 102, 157, 65, 95, 65, 94, 65, 93, 65, 92, 65, 91, 65, 90, 65, 89, 65, 88, 95, 94, 93, 90, 89, 91, 88, 72, 129, 196, 0, 2, 0, 0 })
			+ OldData
			+ Buffer({ 0xFF,0x25,0,0,0,0 })
			+ (UINT64)Addr + OldData.size();
		RunData = VirtualAlloc(NULL, writeData.size(), MEM_COMMIT, PAGE_EXECUTE_READWRITE);
		memcpy((void*)writeData.data(), RunData, writeData.size());
		if (RunData == NULL)throw std::invalid_argument("申请HOOK代码内存块失败");
		HookData = Buffer({ 0xFF,0x25,0,0,0,0 }) + (UINT64)RunData;
		HookData.resize(OldData.size());
		memcpy((void*)HookData.data(), Addr, HookData.size());
	}

	Hook::Hook(LPVOID adder, Buffer oldData, HookHandle Handle)
	{
		size_t len = oldData.size();
		if(len<14) throw std::invalid_argument("Hook长度不可以小于14");
		if (!VirtualProtect(adder, len, PAGE_EXECUTE_READ | PAGE_EXECUTE_WRITECOPY, NULL)) throw std::invalid_argument("修改内存属性失败");
		OldData = oldData;
		Addr = adder;
		this->Handle=Handle;
		run();
	}

	Hook::Hook(LPVOID adder, size_t len, HookHandle Handle)
	{
		if (len < 14) throw std::invalid_argument("Hook长度不可以小于14");
		if (!VirtualProtect(adder, len, PAGE_EXECUTE_READ | PAGE_EXECUTE_WRITECOPY, NULL)) throw std::invalid_argument("修改内存属性失败");
		char* oldData = new char[len];
		memcpy(adder, oldData, len);
		OldData = Buffer(oldData,len);
		Addr = adder;
		this->Handle = Handle;
		run();
	}

	Hook::~Hook()
	{
		memcpy((void*)OldData.data(), Addr, OldData.size());
		VirtualFree(RunData, 0, MEM_RELEASE);
	}
}
