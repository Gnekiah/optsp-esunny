#include "st_sola.h"

ST_Sola::ST_Sola(Trader *trader, Logger *logger, Datacore *datacore)
{
	this->logger = logger;
	this->datacore = datacore;
	this->trader = trader;
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
		//log << "KLine Size=" << _size;
		//LOGMSG(logger, &log);
		circular_buffer<KLine>::iterator it = klines->begin();
		KLine k1 = *it;
		it++;
		KLine k2 = *it;
		if ((k1.HighPrice > k2.HighPrice && k1.LowPrice > k2.LowPrice) || 
			(k1.HighPrice < k2.HighPrice && k1.LowPrice < k2.LowPrice)) {
			//log << "k1.HighPrice=" << k1.HighPrice << ", k2.HighPrice=" << k2.HighPrice;
			//log << ", k1.LowPrice=" << k1.LowPrice << ", k2.LowPrice=" << k2.LowPrice;
			//LOGMSG(logger, &log);
			return;
		}
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
		k1.Covered += k2.Covered;
		klines->pop_front();
		klines->pop_front();
		klines->push_front(k1);
		//log << "����һ��������ϵ��size = 2";
		//LOGMSG(logger, &log);
		return;
	}
	
	circular_buffer<KLine>::iterator it = klines->begin();
	KLine k1 = *it;
	it++;
	KLine k2 = *it;
	it++;
	KLine k3 = *it;
	if ((k1.HighPrice > k2.HighPrice && k1.LowPrice > k2.LowPrice) ||
		(k1.HighPrice < k2.HighPrice && k1.LowPrice < k2.LowPrice))
		return;
	if (k2.HighPrice > k3.HighPrice) {
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
	}
	else {
		k1.HighPrice = min(k1.HighPrice, k2.HighPrice);
		k1.LowPrice = min(k1.LowPrice, k2.LowPrice);
		if (k1.OpeningPrice > k1.ClosingPrice) {
			k1.OpeningPrice = k1.HighPrice;
			k1.ClosingPrice = k1.LowPrice;
		}
		else {
			k1.OpeningPrice = k1.LowPrice;
			k1.ClosingPrice = k1.HighPrice;
		}
	}

	klines->pop_front();
	klines->pop_front();
	arch_strcpy(k1.DateTimeStamp, k2.DateTimeStamp, sizeof(TAPIDTSTAMP));
	k1.Covered += k2.Covered;

	// Calc MA5
	int _cnt = 0;
	TAPIQPRICE _sum = 0;
	it = klines->begin();
	for (; _cnt < klines->size() && _cnt < 5; _cnt++, it++)
		_sum += (*it).ClosingPrice;
	_cnt++;
	_sum += k1.ClosingPrice;
	k1.MA5 = _sum / _cnt;

	klines->push_front(k1);
	//log << "����һ��������ϵ��Covered=" << k1.Covered;
	//LOGMSG(logger, &log);

}


void ST_Sola::UpdateKLine(TapAPIQuoteWhole *tick)
{
	stringstream log;

	// Trading at 09:30 - 11:30, 13:00 - 15:30
	if (!strcmp(tick->DateTimeStamp, "0000-00-00 00:00:00.000")) {
		log << "��Ч�� tick ���ݣ�ʱ���Ϊ 0000-00-00 00:00:00.000";
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
		log << "��ǰ tick �����趨�Ľ���ʱ�䣺" << tick->DateTimeStamp;
		LOGWAR(logger, &log);
		return;
	}
	// if secs1 - secs2 >= 15s, then the current tick out of a KLine series
	if (strcmp(kline.DateTimeStamp, "0000-00-00 00:00:00.000") && (secs1 - secs2) >= 15) {
		//log << "����ǰ KLine ���뵽 KLines �У�secs1=" << secs1 << "��secs2=" << secs2;
		//LOGMSG(logger, &log);
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

		/* DO TEST */
		it = klines->begin();
		for (int i = 0; i < klines->size(); i++, it++) {
			//log << (*it).Covered << ", " << (*it).DateTimeStamp << ", Opening=" << (*it).OpeningPrice << ", High=" << (*it).HighPrice
			//	<< ", Low=" << (*it).LowPrice << ", Closing" << (*it).ClosingPrice << ", MA5=" << (*it).MA5;
			//LOGMSG(logger, &log);
		}
	}
	
	// Init a new KLine
	if (!strcmp(kline.DateTimeStamp, "0000-00-00 00:00:00.000")) {
		//log << "��ʼ��һ���µ� KLine";
		//LOGMSG(logger, &log);
		arch_strcpy(kline.DateTimeStamp, tick->DateTimeStamp, sizeof(TAPIDTSTAMP));
		kline.DateTimeStamp[20] = '0';
		kline.DateTimeStamp[21] = '0';
		kline.DateTimeStamp[22] = '0';
		int _ss = (_ss1 / 15) * 15;
		kline.DateTimeStamp[17] = '0' + (_ss / 10);
		kline.DateTimeStamp[18] = '0' + (_ss % 10);
		kline.OpeningPrice = tick->QLastPrice;
		kline.HighPrice = tick->QLastPrice;
		kline.LowPrice = tick->QLastPrice;
		kline.ClosingPrice = tick->QLastPrice;
		kline.Covered = 1;
	}
	kline.HighPrice = max(kline.HighPrice, tick->QLastPrice);
	kline.LowPrice = min(kline.LowPrice, tick->QLastPrice);
	kline.ClosingPrice = tick->QLastPrice;
}


void ST_Sola::Run()
{
	stringstream log;
	TapAPIQuoteWhole tick;
	circular_buffer<KLine>::iterator it;
	while (true) {
		arch_sleep(1);
		while (!(tickBuffer->empty())) {
			tickBuffer->pop(tick);
			UpdateKLine(&tick);
		}

		/* Check for timestamp */
		int _hh = 0, _mm = 0, _ss = 0;
		char _hms[3] = { 0 };
		_hms[0] = tick.DateTimeStamp[11];
		_hms[1] = tick.DateTimeStamp[12];
		_hh = atoi(_hms);
		_hms[0] = tick.DateTimeStamp[14];
		_hms[1] = tick.DateTimeStamp[15];
		_mm = atoi(_hms);
		_hms[0] = tick.DateTimeStamp[17];
		_hms[1] = tick.DateTimeStamp[18];
		_ss = atoi(_hms);
		int secs = _hh * 3600 + _mm * 60 + _ss;
		// not trading time
		// �ǽ���ʱ��
		if (secs < 34260 || secs > 55740 || (secs > 41340 && secs < 46860)) {
			if (traded) {
				trader->Insert(!direct);
				traded = false;
				log << "ƽ��";
				LOGMSG(logger, &log);
				// TODO��ִ��ƽ��
				//		��traded��Ϊfalse
				//		����profit
				//		����nrTrade
			}
			continue;
		}
		/* Do Strategy */
		// K������С��5������ִ�в���
		if (klines->size() < 5) {
			continue;
		}
		/* waiting for quit current trading */
		// �ѽ��֣������ƽ�ֵ������ж�
		if (traded) {
			// ƽ�൥
			if (direct) {
				// ֹ�� & ֹӯ
				if (tick.QLastPrice <= sl || tick.QLastPrice >= tp) {
					trader->Insert(!direct);
					traded = false;
					log << "ƽ��";
					LOGMSG(logger, &log);
					// TODO������ƽ�ֲ����������£�
					//		��traded����Ϊfalse
					//		����profit
					//		����nrTrade
				}
			}
			// ƽ�յ�
			else {
				// ֹ�� & ֹӯ
				if (tick.QLastPrice >= sl || tick.QLastPrice <= tp) {
					// ͬ��
					trader->Insert(!direct);
					traded = false;
					log << "ƽ��";
					LOGMSG(logger, &log);
				}
			}
		}
		/* waiting for enter a trading */
		// δ���֣�����н��ֵ������ж�
		if (!traded) {
			// ��ȡK�߱�������ĸ�K�ߣ����������ڻ��Ƶ�δ����K�߱��K�ߣ�
			it = klines->begin();
			KLine k1 = *it;
			KLine k2 = *(it + 1);
			KLine k3 = *(it + 2);
			KLine k4 = *(it + 3);

			// check for direction
			// ����K1��K2���жϷ���true��ʾ���ƣ�false��ʾ����
			if (k1.HighPrice > k2.HighPrice) {
				direct = true;
				// ����K2��K3���ж�K2�Ƿ�Ϊ��/��
				// ����1��K2����Ϊ��/��
				if (k2.LowPrice > k3.LowPrice) {
					continue;
				}
				// ����2����Ϊ��/�׵�K2��ǰ������K3/K4���ļ���ֵ >= 15
				if (max(k3.HighPrice, k4.HighPrice) - k2.LowPrice < 15) {
					continue;
				}
				// ����3��K1�����̼� > MA5
				if (k1.ClosingPrice <= k1.MA5) {
					continue;
				} 
				// ����4��K1��K2�ļ���ֵ < 30
				if (k1.HighPrice - k2.LowPrice >= 30) {
					continue;
				}
				// ����5��K1�а�����K�߱��� < 3
				if (k1.Covered >= 3) {
					continue;
				}
				// ����6��K1��K2�а�����K�߱��� <= 5
				if (k1.Covered + k2.Covered > 5) {
					continue;
				}
				// ִ�п��ֵĵ�λ�����±��� > K1�����(С)ֵ
				if (tick.QLastPrice > k1.HighPrice) {
					trader->Insert(direct);
					traded = true;
					sl = k2.LowPrice - 1;
					tp = tick.QLastPrice + 7;
					log << "���൥";
					LOGMSG(logger, &log);
					// TODO�����ֳɹ�������Ҫ��������ֵ��
					//		���ڱ���Ƿ񿪲ֵ�flag��traded
					//		���ڼ�¼ֹ��ֹӯ�ı�����sl / tp
					//		������ֵ���־��¼
				}
			}
			else {
				direct = false;
				// ����K2��K3���ж�K2�Ƿ�Ϊ��/��
				// ����1��K2����Ϊ��/��
				if (k2.HighPrice < k3.HighPrice) {
					continue;
				}
				// ����2����Ϊ��/�׵�K2��ǰ������K3/K4���ļ������ֵ >= 15
				if (k2.HighPrice - max(k3.LowPrice, k4.LowPrice) < 15) {
					continue;
				}
				// ����3��K1�����̼� < MA5
				if (k1.ClosingPrice >= k1.MA5) {
					continue;
				}
				// ����4��K1��K2�ļ������ֵ < 30
				if (k2.HighPrice - k1.LowPrice >= 30) {
					continue;
				}
				// ����5��K1�а�����K�߱��� < 3
				if (k1.Covered >= 3) {
					continue;
				}
				// ����6��K1��K2�а�����K�߱��� <= 5
				if (k1.Covered + k2.Covered > 5) {
					continue;
				}
				// ִ�п��ֵĵ�λ�����±��� < K1�����(С)ֵ
				if (tick.QLastPrice < k1.LowPrice) {
					trader->Insert(direct);
					traded = true;
					sl = k2.HighPrice + 1;
					tp = tick.QLastPrice - 7;
					log << "���յ�";
					LOGMSG(logger, &log);
					// TODO�����ֳɹ�������Ҫ��������ֵ��
					//		���ڱ���Ƿ񿪲ֵ�flag��traded
					//		���ڼ�¼ֹ��ֹӯ�ı�����sl / tp
					//		������ֵ���־��¼
				}
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