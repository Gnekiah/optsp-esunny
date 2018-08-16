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
		//log << "处理一个包含关系，size = 2";
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
	//log << "处理一个包含关系，Covered=" << k1.Covered;
	//LOGMSG(logger, &log);

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
		//log << "将当前 KLine 插入到 KLines 中，secs1=" << secs1 << "，secs2=" << secs2;
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
		//log << "初始化一个新的 KLine";
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
		// 非交易时间
		if (secs < 34260 || secs > 55740 || (secs > 41340 && secs < 46860)) {
			if (traded) {
				trader->Insert(!direct);
				traded = false;
				log << "平仓";
				LOGMSG(logger, &log);
				// TODO：执行平仓
				//		将traded置为false
				//		更新profit
				//		更新nrTrade
			}
			continue;
		}
		/* Do Strategy */
		// K线数量小于5条，不执行操作
		if (klines->size() < 5) {
			continue;
		}
		/* waiting for quit current trading */
		// 已建仓，则进行平仓的条件判断
		if (traded) {
			// 平多单
			if (direct) {
				// 止损 & 止盈
				if (tick.QLastPrice <= sl || tick.QLastPrice >= tp) {
					trader->Insert(!direct);
					traded = false;
					log << "平仓";
					LOGMSG(logger, &log);
					// TODO：进行平仓操作，并更新：
					//		将traded设置为false
					//		更新profit
					//		更新nrTrade
				}
			}
			// 平空单
			else {
				// 止损 & 止盈
				if (tick.QLastPrice >= sl || tick.QLastPrice <= tp) {
					// 同上
					trader->Insert(!direct);
					traded = false;
					log << "平仓";
					LOGMSG(logger, &log);
				}
			}
		}
		/* waiting for enter a trading */
		// 未建仓，则进行建仓的条件判断
		if (!traded) {
			// 获取K线表的最新四根K线（不包含正在绘制的未加入K线表的K线）
			it = klines->begin();
			KLine k1 = *it;
			KLine k2 = *(it + 1);
			KLine k3 = *(it + 2);
			KLine k4 = *(it + 3);

			// check for direction
			// 根据K1和K2来判断方向，true表示涨势，false表示跌势
			if (k1.HighPrice > k2.HighPrice) {
				direct = true;
				// 根据K2和K3来判断K2是否为顶/底
				// 条件1：K2必须为顶/底
				if (k2.LowPrice > k3.LowPrice) {
					continue;
				}
				// 条件2：作为顶/底的K2与前两根（K3/K4）的极差值 >= 15
				if (max(k3.HighPrice, k4.HighPrice) - k2.LowPrice < 15) {
					continue;
				}
				// 条件3：K1的收盘价 > MA5
				if (k1.ClosingPrice <= k1.MA5) {
					continue;
				} 
				// 条件4：K1与K2的极差值 < 30
				if (k1.HighPrice - k2.LowPrice >= 30) {
					continue;
				}
				// 条件5：K1中包含的K线必须 < 3
				if (k1.Covered >= 3) {
					continue;
				}
				// 条件6：K1和K2中包含的K线必须 <= 5
				if (k1.Covered + k2.Covered > 5) {
					continue;
				}
				// 执行开仓的点位：最新报价 > K1的最大(小)值
				if (tick.QLastPrice > k1.HighPrice) {
					trader->Insert(direct);
					traded = true;
					sl = k2.LowPrice - 1;
					tp = tick.QLastPrice + 7;
					log << "开多单";
					LOGMSG(logger, &log);
					// TODO：开仓成功过后，需要更新如下值：
					//		用于标记是否开仓的flag：traded
					//		用于记录止损止盈的变量：sl / tp
					//		输出开仓的日志记录
				}
			}
			else {
				direct = false;
				// 根据K2和K3来判断K2是否为顶/底
				// 条件1：K2必须为顶/底
				if (k2.HighPrice < k3.HighPrice) {
					continue;
				}
				// 条件2：作为顶/底的K2与前两根（K3/K4）的极差绝对值 >= 15
				if (k2.HighPrice - max(k3.LowPrice, k4.LowPrice) < 15) {
					continue;
				}
				// 条件3：K1的收盘价 < MA5
				if (k1.ClosingPrice >= k1.MA5) {
					continue;
				}
				// 条件4：K1与K2的极差绝对值 < 30
				if (k2.HighPrice - k1.LowPrice >= 30) {
					continue;
				}
				// 条件5：K1中包含的K线必须 < 3
				if (k1.Covered >= 3) {
					continue;
				}
				// 条件6：K1和K2中包含的K线必须 <= 5
				if (k1.Covered + k2.Covered > 5) {
					continue;
				}
				// 执行开仓的点位：最新报价 < K1的最大(小)值
				if (tick.QLastPrice < k1.LowPrice) {
					trader->Insert(direct);
					traded = true;
					sl = k2.HighPrice + 1;
					tp = tick.QLastPrice - 7;
					log << "开空单";
					LOGMSG(logger, &log);
					// TODO：开仓成功过后，需要更新如下值：
					//		用于标记是否开仓的flag：traded
					//		用于记录止损止盈的变量：sl / tp
					//		输出开仓的日志记录
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