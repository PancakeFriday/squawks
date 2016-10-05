//------------------------------
//-- Hey, I didn't write this (I modified it though)
//-- Credit: http://vilipetek.com/2014/04/17/thread-safe-simple-logger-in-c11/
//------------------------------

#pragma once
#include <string>
#include <sstream>
#include <mutex>
#include <memory>
#include <fstream>

// log message levels
enum Level { Trace, Debug, Info, Warning, Error };
enum OStream { File, Stdout, Stdout_File };

// Show all loglevels by default
#define LOG_OLEVEL Level::Trace
// Print to Stdout and to file by default
#define LOG_OSTREAM OStream::Stdout_File
#define LOGFILE "logfile"

class logger;
extern logger Log;

class logstream : public std::ostringstream
{
public:
	logstream(logger& oLogger, Level nLevel);
	logstream(const logstream& ls);
	~logstream();

private:
	logger& m_oLogger;
	Level m_nLevel;
};

class logger
{
public:
	logger(std::string filename);
	virtual ~logger();

	void log(Level nLevel, std::string oMessage);

	logstream operator()();
	logstream operator()(Level nLevel);

private:
	const tm* getLocalTime();

private:
	std::mutex		m_oMutex;
	std::ofstream	m_oFile;

	tm				m_oLocalTime;
};
