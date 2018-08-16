#ifndef OPTS_TRADER_H_
#define OPTS_TRADER_H_


class Trader
{
	virtual int SetTickBuffer(boost::lockfree::queue<TapAPIQuoteWhole> *tickBuffer) = 0;
};


#endif // OPTS_TRADER_H_