#ifndef ESUNNY_LOGGER_H_
#define ESUNNY_LOGGER_H_

#include <mutex>
#include <sstream>
#include <fstream>
#include <iostream>

#include "datacore.h"

using std::mutex;
using std::string;
using std::ofstream;
using std::ostream;
using std::stringstream;

class Logger
{
private:
	mutex mLock;
	Datacore *datacore = NULL;

	void WriteLog(string type, string log, const char* _FUNC_);

public:
	Logger(Datacore *datacore);
	void FlushInf(stringstream *strStream, const char* _FUNC_);
	void FlushErr(stringstream *strStream, const char* _FUNC_);
	void FlushWar(stringstream *strStream, const char* _FUNC_);
	void FlushMsg(stringstream *strStream, const char* _FUNC_);
};
#endif // ESUNNY_LOGGER_H_
