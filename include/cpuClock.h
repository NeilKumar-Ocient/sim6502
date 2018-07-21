#ifndef CPU_CLOCK_H
#define CPU_CLOCK_H

#include <ctime>
#include <cassert>
#include <chrono>
#include "log.h"
#include <vector>
#include <iostream>

static constexpr size_t NANO =  1000UL * 1000UL * 1000UL;
static constexpr size_t FREQUENCY_CONVERSION_FACTOR =  1000UL * NANO; //1 trillion nanoseconds divided by frequency in mHz gives us the period in nanoseconds

using timeSpec_t = struct timespec;

//the clock, used to make sure everything that should happen in 1 cycle does
class cpuClock_t {
public:
	//constructor, takes in a frequency in mHz
	cpuClock_t(size_t frequency, const logger_t& logger) : m_frequency(frequency), m_period(FREQUENCY_CONVERSION_FACTOR / m_frequency), LOGGER(logger) {

		//below code is used to initialize the vector we will use to determine how long to wait if we finish an instruction early
		LOG_DEBUG("Starting cpuClock sampling");
		timeSpec_t startTime;
		timeSpec_t endTime;
		size_t timeDelta = 0;

		size_t i = 1;

		while(true) {
			timeDelta=0;
			size_t totalCycleSample = i * 1000000;
			size_t cycleCount = 0;
			clock_gettime(CLOCK_REALTIME, &startTime);
			while(cycleCount < totalCycleSample) {
				cycleCount++;
			}
			clock_gettime(CLOCK_REALTIME, &endTime);
			timeDelta = timeElapsed(startTime, endTime) / 1000000;
			if(timeDelta/10 == (m_timeCycle.size()+1))
			{
				m_timeCycle.emplace_back(i);
				LOG_DEBUG("added to cycleList");
				i+=2;
			} else if(timeDelta/10 > (m_timeCycle.size()+1)) {
				LOG_DEBUG("numCycles: %lu, \ttimeElapsed: %lu, \tcurrentValIndexWouldBe: %lu, \ttimeWeAreLookingFor %lu", i, timeDelta, timeDelta / 10, m_timeCycle.size() + 1);
				i-=2;	
			} else {
				LOG_DEBUG("numCycles: %lu, \ttimeElapsed: %lu, \tcurrentValIndexWouldBe: %lu, \ttimeWeAreLookingFor %lu", i, timeDelta, timeDelta / 10, m_timeCycle.size() + 1);
				i += 2;
			}

			if((m_timeCycle.size()+1)*10 > m_period){
				break;
			}
		}

		//uncomment below to have it print vector when cpu is constructed
		for(size_t i = 0; i < m_timeCycle.size(); i ++) {
			LOG_DEBUG("time: %lu, \tcycleCount: %lu\n", (i + 1) * 10, m_timeCycle[i]);
		}

		LOG_DEBUG("Finished cpu clock sampling");
	}

	//starts the clock at the current time
	void start() {
		//set m_checkPoint to the current time
		LOG_DEBUG("Starting clock");
		clock_gettime(CLOCK_REALTIME, &m_checkPoint);
	}

	//checks that the time since the checkpoint has less than or equal to delta
	//if the time is greater, meaning more than 1 cycle has actually passed then this fails
	//otherwise it waits for the remainder of the cycle to finish and updates the checkpoint
	void cycle() {
		timeSpec_t currentTime;
		clock_gettime(CLOCK_REALTIME, &currentTime);

		size_t delta = timeElapsed(m_checkPoint, currentTime);
		LOG_DEBUG("Clock cycle took %lu of %lu nanoseconds", delta, m_period);
		if(delta < m_period) {
			//wait the remaining number of nanoseconds
			waitForTime(m_period - delta);
		}
		else {
			//the cycle was too slow, log an error and kill the program unless NO_CLOCK is defined
			LOG_ERROR("Clock cycle was too slow, took %lu nanoseconds, expected less than %lu", delta, m_period);
#ifndef NO_CLOCK
			throw;
#endif
		}

		//update the checkpoint, can't just manually add to it b/c we could have clock drift that way
		//since the time it takes for this function to execute it not exact, especially the leftover waiting
		clock_gettime(CLOCK_REALTIME, &m_checkPoint);
	}

private:
	size_t m_frequency; //the frequency of the clock in mHz b/c we want to be able to handle fractions of a Hz and don't want to use a double
	timeSpec_t m_checkPoint; //the time of the last checkpoint
	size_t m_period; //the time delta between cycles determined by the frequency in nanoseconds
	logger_t LOGGER; //the logger, is always copied from some other logger

	std::vector<size_t> m_timeCycle;

	//returns the number of nanoseconds between oldTime newTime
	size_t timeElapsed(const timeSpec_t& oldTime, const timeSpec_t& newTime) {
		size_t oldNano = (oldTime.tv_sec * NANO) + oldTime.tv_nsec;
		size_t newNano = (newTime.tv_sec * NANO) + newTime.tv_nsec;
		return newNano - oldNano;
	}
	
	void waitForTime(size_t timeToWait) {
		size_t cycle = 0;
		if(timeToWait < 25) {
			while(cycle < m_timeCycle[0]) {
				cycle++;
			}
		} else {
			size_t numCycles = m_timeCycle[(timeToWait-25)/10];
			while(cycle < numCycles) {
				cycle++;
			}
		}	
	}
};

#endif
