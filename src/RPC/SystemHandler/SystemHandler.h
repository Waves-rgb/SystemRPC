#pragma once
#ifdef _WINDOWS_
#include <Windows.h>
#endif
class SystemHandler {
public:
	class WINDOWS {
	public:
		void init();
	};
	class LINUX {
	public:
		void init();
	};
};
