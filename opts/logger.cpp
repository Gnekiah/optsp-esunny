#include "logger.h"

#include <ctime>
#include <iostream>

#include "arch.h"

using std::ios;
using std::stringstream;
using std::cout;
using std::endl;

Logger::Logger(Datacore *datacore)
{
	this->datacore = datacore;
}


void Logger::WriteLog(string type, string log, const char* _FUNC_)
{
	ofstream ofStream;
	time_t tTime;
	struct tm tmTime;
	time(&tTime);
	arch_localtime(&tTime, &tmTime);

	stringstream stream;
	stream << 1900 + tmTime.tm_year;
	stream << (tmTime.tm_mon > 8 ? "-" : "-0") << 1 + tmTime.tm_mon;
	stream << (tmTime.tm_mday > 9 ? "-" : "-0") << tmTime.tm_mday;
	stream << (tmTime.tm_hour > 9 ? " " : " 0") << tmTime.tm_hour;
	stream << (tmTime.tm_min > 9 ? ":" : ":0") << tmTime.tm_min;
	stream << (tmTime.tm_sec > 9 ? ":" : ":0") << tmTime.tm_sec;
	stream << " " << type << " <" << _FUNC_ << "> " << log << endl;

	mLock.lock();
	if (datacore->debug)
		cout << stream.str();
	ofStream.open(datacore->logpath, ios::app);
	ofStream << stream.str();
	ofStream.close();

	mLock.unlock();
}


void Logger::FlushInf(stringstream *strStream, const char* _FUNC_)
{
	if (!datacore->loginf) return;
	WriteLog("[INF]", strStream->str(), _FUNC_);
	strStream->str("");
}


void Logger::FlushMsg(stringstream *strStream, const char* _FUNC_)
{
	if (!datacore->logmsg) return;
	WriteLog("[MSG]", strStream->str(), _FUNC_);
	strStream->str("");
}


void Logger::FlushWar(stringstream *strStream, const char* _FUNC_)
{
	if (!datacore->logwar) return;
	WriteLog("[WAR]", strStream->str(), _FUNC_);
	strStream->str("");
}


void Logger::FlushErr(stringstream *strStream, const char* _FUNC_)
{
	if (!datacore->logerr) return;
	WriteLog("[ERR]", strStream->str(), _FUNC_);
	strStream->str("");
}
