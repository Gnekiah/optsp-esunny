#include "st_sola.h"

ST_Sola::ST_Sola(Logger *logger, Datacore *datacore)
{
	this->logger = logger;
	this->datacore = datacore;
	this->tickBuffer = datacore->tickBuffer;
	klines = new circular_buffer<KLine>(65536);
}


void ST_Sola::UpdateKLine(TapAPIQuoteWhole *tick)
{
	if ()
	
}


void ST_Sola::Run()
{
	TapAPIQuoteWhole tick;
	while (true) {
		arch_sleep(0.01);
		if (!(tickBuffer->empty())) {
			tickBuffer->pop(tick);
			UpdateKLine(&tick);
		}
	}
}


void ST_Sola::Join()
{
	boost::function0<void> f = boost::bind(&ST_Sola::Run, this);
	boost::thread thrd(f);
	thrd.join();
}