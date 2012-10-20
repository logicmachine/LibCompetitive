#ifndef LIBCOMPETITIVE_TEST_STOPWATCH_H
#define LIBCOMPETITIVE_TEST_STOPWATCH_H

#include <gtest/gtest.h>
#include <sys/time.h>

namespace testtool {

	class StopWatch {
	private:
		unsigned long long m_start_time;
		unsigned long long get_timestamp(){
			struct timeval tv;
			gettimeofday(&tv, NULL);
			return tv.tv_sec * 1000 + tv.tv_usec / 1000;
		}
	public:
		StopWatch(){ m_start_time = get_timestamp(); }
		unsigned long long get(){ return get_timestamp() - m_start_time; }
	};

}

#endif

