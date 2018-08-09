#include "datacore.h"

#include <fstream>
#include <iostream>

#include <boost/exception/exception.hpp>
#include <boost/filesystem.hpp>

using std::ifstream;
using std::string;
using std::cout;
using std::endl;
using std::min;


Datacore::Datacore(string filename)
{
	string contract;
	string loglevel;

	ifstream fin(filename);
	if (!fin)
	{
		GenConfig();
		write_ini(filename, pt);
		cout << "Generated esunny-pts.conf as Config File." << endl;
		exit(0);
	}

	read_ini(filename, pt);
	debug = pt.get<bool>("Logger.Debug", true);
	loginf = pt.get<bool>("Logger.LogInf", true);
	logmsg = pt.get<bool>("Logger.LogMsg", true);
	logwar = pt.get<bool>("Logger.LogWar", true);
	logerr = pt.get<bool>("Logger.LogErr", true);
	logpath = Filter(pt.get<string>("Logger.LogPath", "esunny-pts.log"));

	quotepath = Filter(pt.get<string>("Quote.QuotePath", "./quote"));
	loglevel = Filter(pt.get<string>("Quote.LogLevel", "D"));
	quoteLogLevel = SetLogLevel(loglevel.c_str()[0]);

	tradepath = Filter(pt.get<string>("Trade.QuotePath", "./trade"));
	loglevel = Filter(pt.get<string>("Trade.LogLevel", "D"));
	tradeLogLevel = SetLogLevel(loglevel.c_str()[0]);


//	contract = Filter(pt.get<string>("Quote.Contract", ""), false);
//	ParseContract(contract);

	if (!boost::filesystem::exists(quotepath) || !boost::filesystem::is_directory(quotepath)) {
		boost::filesystem::create_directories(quotepath);
	}
}


Datacore::~Datacore()
{

}

/*
int Datacore::ParseContract(string sContract)
{
	this->nMdInstrument = 0;
	int len = sContract.length();
	TThostFtdcInstrumentIDType entry;

	TapAPIContract en;

	int ep = 0;

	for (int i = 0; i < len; i++) {
		if (sContract[i] == ' ') continue;
		if (sContract[i] != ',') {
			entry[ep++] = sContract[i];
			continue;
		}

		mdInstrumentIDs[this->nMdInstrument][ep] = '\0';
		for (int k = 0; k < ep; k++)
			mdInstrumentIDs[this->nMdInstrument][k] = entry[k];
		if (this->nMdInstrument++ >= MAX_NR_INSTRUMENT) return MAX_NR_INSTRUMENT;
		ep = 0;
	}

	if (ep) {
		mdInstrumentIDs[this->nMdInstrument][ep] = '\0';
		for (int k = 0; k < ep; k++)
			mdInstrumentIDs[this->nMdInstrument][k] = entry[k];
		if (this->nMdInstrument++ >= MAX_NR_INSTRUMENT) return MAX_NR_INSTRUMENT;
	}
	return this->nMdInstrument;
}
*/

void Datacore::GenConfig()
{
	pt.put<string>("Logger.Debug", "true## Debug模式");
	pt.put<string>("Logger.LogInf", "true## Info级日志");
	pt.put<string>("Logger.LogMsg", "true## Message级日志");
	pt.put<string>("Logger.LogWar", "true## Warning级日志");
	pt.put<string>("Logger.LogErr", "true## Error级日志");
	pt.put<string>("Logger.LogFile", "cielf.log## 日志文件保存路径");

	pt.put<string>("Quote.QuotePath", "./quote## quote相关的保存路径");
	pt.put<string>("Quote.LogLevel", "D ## quote日志的记录等级，分为4种，None/Debug/Warning/Error");

	pt.put<string>("Trade.QuotePath", "./trade## trade相关的保存路径");
	pt.put<string>("Trade.LogLevel", "D ## trade日志的记录等级，分为4种，None/Debug/Warning/Error");

	//pt.put<string>("Quote.Contract", "## 合约信息, e.g. rb1810,c1809,i1901,rb1901");
}


string Datacore::Filter(string s, bool blank)
{
	int pos = INT_MAX, pos1 = -1, pos2 = -1, pos3 = -1;
	if (blank)
		pos1 = s.find_first_of(" ", 0);
	pos2 = s.find_first_of("#", 0);
	pos3 = s.find_first_of("\t", 0);
	if (pos1 >= 0)
		pos = min(pos, pos1);
	if (pos2 >= 0)
		pos = min(pos, pos2);
	if (pos3 >= 0)
		pos = min(pos, pos3);
	if (pos == INT_MAX)
		return s;
	return s.substr(0, pos);
}


char Datacore::SetLogLevel(char c)
{
	switch (c) {
	case 'n':
	case 'N':
		return 'N';
		break;
	case 'e':
	case 'E':
		return 'E';
		break;
	case 'w':
	case 'W':
		return 'W';
		break;
	case 'd':
	case 'D':
		return 'D';
		break;
	default:
		return 'D';
		break;
	}
}