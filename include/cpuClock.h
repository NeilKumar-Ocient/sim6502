#ifndef CPU_CLOCK_H
#define CPU_CLOCK_H

#include <ctime>
#include <cassert>

#define NANO 1000 * 1000 * 1000
#define CONVERSION_FACTOR 1000 * NANO //1 trillion nanoseconds divided by frequency in mHz gives us the period in nanoseconds

typedef struct timespec timeSpec_t;

//the clock, used to make sure everything that should happen in 1 cycle does
class cpuClock_t {
public:
	//constructor, takes in a frequency in mHz
	cpuClock_t(size_t frequency) : m_frequency(frequency), m_period(CONVERSION_FACTOR / m_frequency) {}

	//starts the clock at the current time
	void start() {
		//set m_checkPoint to the current time
		int retval = clock_gettime(CLOCK_REALTIME, &m_checkPoint);
		assert(retval == 0);
	}

	//checks that the time since the checkpoint has less than or equal to delta
	//if the time is greater, meaning more than 1 cycle has actually passed then this fails
	//otherwise it waits for the remainder of the cycle to finish and updates the checkpoint
	void cycle() {
		timeSpec_t currentTime;
		int retval = clock_gettime(CLOCK_REALTIME, &currentTime);
		assert(retval == 0);

		size_t delta = timeElapsed(m_checkPoint, currentTime);
		assert(delta < m_period);

		//TODO wait the remaining number of nanoseconds somehow
		size_t leftover = m_period - delta;

		//update the checkpoint, can't just manually add to it b/c we could have clock drift that way
		//since the time it takes for this function to execute it not exact, especially the leftover waiting
		retval = clock_gettime(CLOCK_REALTIME, &m_checkPoint);

	}

private:
	size_t m_frequency; //the frequency of the clock in mHz b/c we want to be able to handle fractions of a Hz and don't want to use a double
	timeSpec_t m_checkPoint; //the time of the last checkpoint
	size_t m_period; //the time delta between cycles determined by the frequency in nanoseconds

	//returns the number of nanoseconds between oldTime newTime
	size_t timeElapsed(const timeSpec_t& oldTime, const timeSpec_t& newTime) {
		size_t oldNano = (oldTime.tv_sec * NANO) + oldTime.tv_nsec;
		size_t newNano = (newTime.tv_sec * NANO) + newTime.tv_nsec;
		return newNano - oldNano;
	}
};

#endif
