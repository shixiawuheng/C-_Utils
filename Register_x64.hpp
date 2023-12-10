#pragma once
#include <Windows.h>

namespace Utils {
	class Register_x64
	{
	public:
		UINT64* rax;
		UINT64* rbx;
		UINT64* rcx;
		UINT64* rdx;
		UINT64* rbp;
		UINT64* rsi;
		UINT64* rdi;
		UINT64* r8;
		UINT64* r9;
		UINT64* r10;
		UINT64* r11;
		UINT64* r12;
		UINT64* r13;
		UINT64* r14;
		UINT64* r15;
		Register_x64(UINT64 rsp)
		{
			rsp += 8;
			r15 = (UINT64*)rsp;
			rsp += 8;
			r14 = (UINT64*)rsp;
			rsp += 8;
			r13 = (UINT64*)rsp;
			rsp += 8;
			r12 = (UINT64*)rsp;
			rsp += 8;
			r11 = (UINT64*)rsp;
			rsp += 8;
			r10 = (UINT64*)rsp;
			rsp += 8;
			r9 = (UINT64*)rsp;
			rsp += 8;
			r8 = (UINT64*)rsp;
			rsp += 8;
			rdi = (UINT64*)rsp;
			rsp += 8;
			rsi = (UINT64*)rsp;
			rsp += 8;
			rbp = (UINT64*)rsp;
			rsp += 8;
			rdx = (UINT64*)rsp;
			rsp += 8;
			rcx = (UINT64*)rsp;
			rsp += 8;
			rbx = (UINT64*)rsp;
			rsp += 8;
			rax = (UINT64*)rsp;
		}
	};
}