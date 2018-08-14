#ifndef ESUNNY_ST_SOLA_H_
#define ESUNNY_ST_SOLA_H_

#include <boost/circular_buffer.hpp>
#include <boost/thread.hpp>
#include <boost/lockfree/queue.hpp>


#include "arch.h"
#include "datacore.h"
#include "logger.h"
#include "trader.h"

using boost::circular_buffer;

typedef struct KLine {
	TAPIDTSTAMP DateTimeStamp;
	TAPIQPRICE OpeningPrice;
	TAPIQPRICE HighPrice;
	TAPIQPRICE LowPrice;
	TAPIQPRICE ClosingPrice;
	TAPIQPRICE MA5;
	int Covered;
} KLine;


class ST_Sola {
private:
	Logger *logger = NULL;
	Datacore *datacore = NULL;
	Trader *trader = NULL;

private:
	KLine kline;
	circular_buffer<KLine> *klines = NULL;
	boost::lockfree::queue<TapAPIQuoteWhole> *tickBuffer = NULL;

private:
	TAPIQPRICE sl = 0;					// stop losses
	TAPIQPRICE tp = 0;					// take profit
	TAPIQPRICE profit = 0;				// sum of profit
	int nrTrade = 0;					// nummer of trading
	bool traded = false;				// now is trading or not
	bool direct = true;					// true - raise up, false - fall down


private:
	void Run();
	void MergeKLine();
	void UpdateKLine(TapAPIQuoteWhole *tick);

public:
	ST_Sola(Trader *trader, Logger *logger, Datacore *datacore);
	void Join();

};

#endif // ESUNNY_ST_SOLA_H_
