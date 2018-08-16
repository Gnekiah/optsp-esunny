#ifndef ESUNNY_DATACORE_H_
#define ESUNNY_DATACORE_H_

#include <atomic>
#include <mutex>
#include <fstream>
#include <sstream>
#include <queue>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/lockfree/queue.hpp>

#include "arch.h"

using std::mutex;
using std::string;
using std::atomic_bool;
using std::atomic_uint32_t;
using boost::property_tree::ptree;
using boost::property_tree::ini_parser::read_ini;
using boost::property_tree::ini_parser::write_ini;

class Datacore
{
private:
	ptree pt;

public:
	atomic_uint32_t sessionID;

public:
	atomic_bool debug;
	atomic_bool loginf;
	atomic_bool logmsg;
	atomic_bool logwar;
	atomic_bool logerr;
	string logpath;

	string quotepath;
	string quoteLogpath;
	char quoteLogLevel;

	string tradepath;
	string tradeLogpath;
	char tradeLogLevel;

public:
	ITapTrade::TAPISTR_20 userNo;
	ITapTrade::TAPISTR_20 password;
	ITapTrade::TAPISTR_10 exchangeNo;
	ITapTrade::TAPISTR_10 commodityNo;
	ITapTrade::TAPISTR_10 contractNo;

public:
	boost::lockfree::queue<TapAPIQuoteWhole> *tickBuffer = NULL;
	//std::queue<TapAPIQuoteWhole> *tickBuffer = NULL;


public:
	//int nMdInstrument;
	//char* mdInstrumentIDs[MAX_NR_INSTRUMENT];

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