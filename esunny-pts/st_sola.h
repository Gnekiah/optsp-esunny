#ifndef ESUNNY_ST_SOLA_H_
#define ESUNNY_ST_SOLA_H_

#include <boost/circular_buffer.hpp>
#include <boost/thread.hpp>
#include <boost/lockfree/queue.hpp>


#include "arch.h"
#include "datacore.h"
#include "logger.h"

using boost::circular_buffer;

typedef struct KLine {
	TAPIDTSTAMP DateTimeStamp;
	TAPIQPRICE OpeningPrice;
	TAPIQPRICE HighPrice;
	TAPIQPRICE LowPrice;
	TAPIQPRICE ClosingPrice;
	TAPIQPRICE MA5;
	TAPIQVOLUME PositionQty;
	int Covered;
} KLine;


class ST_Sola {
private:
	Logger *logger = NULL;
	Datacore *datacore = NULL;
	circular_buffer<KLine> *klines = NULL;
	boost::lockfree::queue<TapAPIQuoteWhole> *tickBuffer = NULL;

private:
	void Run();
	void UpdateKLine(TapAPIQuoteWhole *tick);

public:
	ST_Sola(Logger *logger, Datacore *datacore);
	void Join();

};

#endif // ESUNNY_ST_SOLA_H_
