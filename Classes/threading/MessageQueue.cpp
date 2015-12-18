#include "threading.hpp"
#ifdef _WIN32
#include <Windows.h>
#else
#include <ptrhead.h>
#endif


namespace utils {
	namespace threading {
		bool KillNativeThread(std::thread::native_handle_type handle){
#ifdef _WIN32
			return (bool)TerminateThread(handle, 1);
#else
			return (bool)!pthread_cancel(handle);
#endif

		}

	}

}