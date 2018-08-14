#ifndef ESUNNY_TRADER_H_
#define ESUNNY_TRADER_H_

#include "arch.h"
#include "logger.h"
#include "datacore.h"

class Trader
{
private:
	Logger * logger = NULL;
	Datacore *datacore = NULL;
	ITapTrade::ITapTradeAPI *tradeApi = NULL;

public:
	Trader(ITapTrade::ITapTradeAPI *tradeApi, Logger *logger, Datacore *datacore);
	void Insert(bool direct);
	void Cancel();
};


#endif // ESUNNY_TRADER_H_