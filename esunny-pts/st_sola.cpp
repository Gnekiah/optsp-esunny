#include "st_sola.h"

ST_Sola::ST_Sola(Logger *logger)
{
	this->logger = logger;
	Klines = new circular_buffer<KLine>(65536);
}


void ST_Sola::Run()
{
	while (true) {
		arch_sleep(0.1);
	}
}


void ST_Sola::Join()
{
	boost::function0<void> f = boost::bind(&ST_Sola::Run, this);
	boost::thread thrd(f);
	thrd.join();
}