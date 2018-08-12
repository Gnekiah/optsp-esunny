#ifndef ESUNNY_ST_SOLA_H_
#define ESUNNY_ST_SOLA_H_

#include <boost/circular_buffer.hpp>
#include <boost/thread.hpp>

#include "arch.h"
#include "datacore.h"
#include "logger.h"

using boost::circular_buffer;

typedef struct KLine {
	TAPIQPRICE OpeningPrice;
	TAPIQPRICE HighPrice;
	TAPIQPRICE LowPrice;
	TAPIQPRICE ClosingPrice;
	int Covered;
} KLine;

class ST_Sola {
private:
	Logger *logger = NULL;
	circular_buffer<KLine> *Klines = NULL;

private:
	void Run();

public:
	ST_Sola(Logger *logger);
	void Join();

};

#endif // ESUNNY_ST_SOLA_H_
