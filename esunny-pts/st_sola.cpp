#include "st_sola.h"

ST_Sola::ST_Sola(Logger *logger, Datacore *datacore)
{
	this->logger = logger;
	this->datacore = datacore;
	this->tickBuffer = datacore->tickBuffer;
	klines = new circular_buffer<KLine>(65536);
	//memset(&kline, 0, sizeof(KLine));
	arch_strcpy(kline.DateTimeStamp, "0000-00-00 00:00:00.000", sizeof(TAPIDTSTAMP));
}


void ST_Sola::MergeKLine()
{
	stringstream log;
	int _size = klines->size();
	if (_size < 2)
		return;
	if (_size == 2) {
		circular_buffer<KLine>::iterator it = klines->begin();
		KLine k1 = *it;
		it++;
		KLine k2 = *it;
		if (k1.HighPrice > k2.HighPrice && k1.LowPrice > k2.LowPrice)
			return;
		if (k1.HighPrice < k2.HighPrice && k1.LowPrice < k2.LowPrice)
			return;
		k1.HighPrice = max(k1.HighPrice, k2.HighPrice);
		k1.LowPrice = max(k1.LowPrice, k2.LowPrice);
		if (k1.OpeningPrice > k1.ClosingPrice) {
			k1.OpeningPrice = k1.HighPrice;
			k1.ClosingPrice = k1.LowPrice;
		}
		else {
			k1.OpeningPrice = k1.LowPrice;
			k1.ClosingPrice = k1.HighPrice;
		}
		arch_strcpy(k1.DateTimeStamp, k2.DateTimeStamp, sizeof(TAPIDTSTAMP));
		k1.MA5 = k1.ClosingPrice;
		k1.Covered++;
		klines->pop_front();
		klines->pop_front();
		klines->push_front(k1);
		log << "处理一个包含关系，size = 2";
		LOGMSG(logger, &log);
	}
	// TODO

}


void ST_Sola::UpdateKLine(TapAPIQuoteWhole *tick)
{
	stringstream log;

	// Trading at 09:30 - 11:30, 13:00 - 15:30
	if (!strcmp(tick->DateTimeStamp, "0000-00-00 00:00:00.000")) {
		log << "无效的 tick 数据，时间戳为 0000-00-00 00:00:00.000";
		LOGWAR(logger, &log);
		return;
	}

	int _hh1 = 0, _mm1 = 0, _ss1 = 0;	// tick stamp
	int _hh2 = 0, _mm2 = 0, _ss2 = 0;	// kline stamp
	char _hms[3] = { 0 };
	_hms[0] = tick->DateTimeStamp[11];
	_hms[1] = tick->DateTimeStamp[12];
	_hh1 = atoi(_hms);
	_hms[0] = tick->DateTimeStamp[14];
	_hms[1] = tick->DateTimeStamp[15];
	_mm1 = atoi(_hms);
	_hms[0] = tick->DateTimeStamp[17];
	_hms[1] = tick->DateTimeStamp[18];
	_ss1 = atoi(_hms);
	_hms[0] = kline.DateTimeStamp[11];
	_hms[1] = kline.DateTimeStamp[12];
	_hh2 = atoi(_hms);
	_hms[0] = kline.DateTimeStamp[14];
	_hms[1] = kline.DateTimeStamp[15];
	_mm2 = atoi(_hms);
	_hms[0] = kline.DateTimeStamp[17];
	_hms[1] = kline.DateTimeStamp[18];
	_ss2 = atoi(_hms);
	int secs1 = _hh1 * 3600 + _mm1 * 60 + _ss1;
	int secs2 = _hh2 * 3600 + _mm2 * 60 + _ss2;
	// Check for trading time (by seconds) 
	if (secs1 < 34200 || secs1 > 55800 || secs1 > 41400 && secs1 < 46800) {
		log << "当前 tick 不在设定的交易时间：" << tick->DateTimeStamp;
		LOGWAR(logger, &log);
		return;
	}
	// if secs1 - secs2 >= 15s, then the current tick out of a KLine series
	if (strcmp(kline.DateTimeStamp, "0000-00-00 00:00:00.000") && (secs1 - secs2) >= 15) {
		// Calc MA5
		int _cnt = 0;
		TAPIQPRICE _sum = 0;
		circular_buffer<KLine>::iterator it = klines->begin();
		for (; _cnt < klines->size() && _cnt < 4; _cnt++, it++)
			_sum += (*it).ClosingPrice;
		_cnt++;
		_sum += kline.ClosingPrice;
		kline.MA5 = _sum / _cnt;

		// Push kline into klines (front) and then do merge
		klines->push_front(kline);
		MergeKLine();
		arch_strcpy(kline.DateTimeStamp, "0000-00-00 00:00:00.000", sizeof(TAPIDTSTAMP));
	}
	
	// Init a new KLine
	if (!strcmp(kline.DateTimeStamp, "0000-00-00 00:00:00.000")) {
		arch_strcpy(kline.DateTimeStamp, tick->DateTimeStamp, sizeof(TAPIDTSTAMP));
		kline.DateTimeStamp[20] = '0';
		kline.DateTimeStamp[21] = '0';
		kline.DateTimeStamp[22] = '0';
		int _ss = (_ss2 / 15) * 15;
		kline.DateTimeStamp[17] = '0' + (_ss / 10);
		kline.DateTimeStamp[18] = '0' + (_ss % 10);
		kline.OpeningPrice = tick->QLastPrice;
		kline.HighPrice = tick->QLastPrice;
		kline.LowPrice = tick->QLastPrice;
		kline.ClosingPrice = tick->QLastPrice;
		kline.Covered = 0;
	}
	kline.HighPrice = max(kline.HighPrice, tick->QLastPrice);
	kline.LowPrice = max(kline.LowPrice, tick->QLastPrice);
	kline.ClosingPrice = tick->QLastPrice;
}


void ST_Sola::Run()
{
	stringstream log;
	TapAPIQuoteWhole tick;
	while (true) {
		arch_sleep(0.1);
		if (!(tickBuffer->empty())) {
			LOGMSG(logger, &log);
			tickBuffer->pop(tick);
			UpdateKLine(&tick);
		}


		/* DO TEST */
		log << kline.ClosingPrice << kline.Covered << kline.DateTimeStamp << kline.HighPrice << kline.LowPrice << kline.MA5 << kline.OpeningPrice;
		LOGMSG(logger, &log);
		/* DO TEST */
		if (klines->size() > 0) {
			circular_buffer<KLine>::iterator it = klines->begin();
			for (int i = 0; i < klines->size(); i++, it++) {
				log << (*it).ClosingPrice << ", " << (*it).Covered << ", " << (*it).DateTimeStamp << ", " << (*it).HighPrice;
				LOGMSG(logger, &log);
			}
		}
	}
}


void ST_Sola::Join()
{
	boost::function0<void> f = boost::bind(&ST_Sola::Run, this);
	boost::thread thrd(f);
	thrd.join();
}