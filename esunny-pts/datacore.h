#ifndef ESUNNY_DATACORE_H_
#define ESUNNY_DATACORE_H_

#include <atomic>
#include <mutex>
#include <fstream>
#include <sstream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include "arch.h"

using std::mutex;
using std::string;
using std::atomic_bool;
using std::atomic_ullong;
using boost::property_tree::ptree;
using boost::property_tree::ini_parser::read_ini;
using boost::property_tree::ini_parser::write_ini;

class Datacore
{
private:
	ptree pt;

public:
	atomic_bool debug;
	atomic_bool loginf;
	atomic_bool logmsg;
	atomic_bool logwar;
	atomic_bool logerr;
	string logpath;

	string quotepath;
	char quoteLogLevel;

	string tradepath;
	char tradeLogLevel;

public:
	int nMdInstrument;
	char* mdInstrumentIDs[MAX_NR_INSTRUMENT];

private:
	/* 过滤' '和'#'，'blank'表示是否要过滤空格，默认为true，表示过滤空格 */
	string Filter(string s, bool blank = true);
	int ParseContract(string contract) { return 0; }
	char SetLogLevel(char c);

public:
	Datacore(string configpath = "esunny-pts.conf");
	~Datacore();
	void GenConfig();

};

#endif // ESUNNY_DATACORE_H_