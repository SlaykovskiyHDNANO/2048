#include "threading.hpp"
#ifdef _WIN32
#include <Windows.h>
#else
#include <pthread.h>
#endif


namespace utils {
	namespace threading {
		bool KillNativeThread(std::thread::native_handle_type handle){
#ifdef _WIN32
			return (bool)TerminateThread(handle, 1);
#else
			return false;
			//return (bool)!std::pthread_cancel(handle);
#endif

		}

	}

}