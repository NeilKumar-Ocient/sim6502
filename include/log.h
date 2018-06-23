#ifndef LOG_H
#define LOG_H

#include <cstdio>
#include <string>
#include <cstring>
#include <atomic>
#include <stdarg.h>

static constexpr char debugLogPrefix[] = "[DEBUG] ";
static constexpr char errorLogPrefix[] = "[ERROR] ";
static constexpr size_t logPrefixLen = strlen(errorLogPrefix);
static_assert((strlen(debugLogPrefix) == logPrefixLen) && (strlen(errorLogPrefix) == logPrefixLen));

//TODO we may want this logger to actually log in a different thread
//a class for logging, intentionally not thread safe b/c no 2 threads should be logging to the same logger for this project
//and also to increase performance in debug builds
class logger_t {
public:
	//constructor, opens the specified file, assumed to not be in use elsewhere
	logger_t(const std::string& file) : m_fd(nullptr), m_refCount(new std::atomic<size_t>(1)) {
		m_fd = fopen(file.c_str(), "w");
		if(m_fd == nullptr) {
			throw;
		}
	}

	//copy constructor
	logger_t(const logger_t& rhs) : m_fd(rhs.m_fd), m_refCount(rhs.m_refCount) {
		//increment the ref count
		++(*m_refCount);
	}

	//copy assignment deleted for simplicity
	//move constructor/assignment deleted b/c the original logger is usually static
	logger_t& operator=(const logger_t& rhs) = delete;
	logger_t(logger_t&& rhs) = delete;
	logger_t& operator=(logger_t&& rhs) = delete;

	//destructor, closes the file descriptor
	~logger_t() {
		if(--(*m_refCount) == 0) {
			fclose(m_fd);
		}
	}

	//logs with the debug prefix, doesn't flush right away
	void logDebug(const char* format, ...) {
		//buffer for creating full log line, logs are assumed to be short
		char buffer[256];

		//copy the log prefix into the start of the buffer
		size_t offset = logPrefixLen;
		strncpy(buffer, debugLogPrefix, logPrefixLen);

		//now copy the formatted printf style string into the buffer
		va_list args;
		va_start(args, format);
		offset += vsnprintf(buffer + offset, sizeof(buffer) - offset, format, args);
		va_end(args);
		buffer[offset++] = '\n'; //append newline

		//finally write the string out
		size_t bytesWritten = 0;
		while(bytesWritten < offset) {
			bytesWritten += fwrite(buffer + bytesWritten, sizeof(buffer[0]), offset - bytesWritten, m_fd);
		}
	}

	//logs with the error prefix, flushes the buffer after
	void logError(const char* format, ...) {
		//buffer for creating full log line, logs are assumed to be short
		char buffer[256];

		//copy the log prefix into the start of the buffer
		size_t offset = logPrefixLen;
		strncpy(buffer, errorLogPrefix, logPrefixLen);

		//now copy the formatted printf style string into the buffer
		va_list args;
		va_start(args, format);
		offset += vsnprintf(buffer + offset, sizeof(buffer) - offset, format, args);
		va_end(args);
		buffer[offset++] = '\n'; //append newline

		//finally write the string out
		size_t bytesWritten = 0;
		while(bytesWritten < offset) {
			bytesWritten += fwrite(buffer + bytesWritten, sizeof(buffer[0]), offset - bytesWritten, m_fd);
		}

		//since this is an error log also flush the buffer
		fflush(m_fd);
	}

private:
	std::FILE* m_fd; //the file descriptor to the given file
	std::atomic<size_t>* m_refCount; //pointer to an atomic ref counter, used to allow copying
};


//logger macros, LOG_DEBUG gets compiled out in release mode
#ifdef RELEASE
#define LOG_DEBUG(formatString, ...) do {} while(false)
#define LOG_ERROR(formatString, ...) do {LOGGER.logError(formatString, ##__VA_ARGS__);} while(false)
#else
#define LOG_DEBUG(formatString, ...) do {LOGGER.logDebug(formatString, ##__VA_ARGS__);} while(false)
#define LOG_ERROR(formatString, ...) do {LOGGER.logError(formatString, ##__VA_ARGS__);} while(false)
#endif

#endif
