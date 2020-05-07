// Adapted from Bennybox tutorial on Youtube
#ifndef TIMING_HPP
#define TIMING_HPP

//#include "core/common.hpp"

struct SDLTiming
{
	static double getTime();
	static void sleep(unsigned int milliseconds);
};

#endif
