#include "trader.h"


Trader::Trader(ITapTrade::ITapTradeAPI *tradeApi, Logger *logger, Datacore *datacore)
{
	this->tradeApi = tradeApi;
	this->logger = logger;
	this->datacore = datacore;
}


// true - BUY; false - SELL
void Trader::Insert(bool direct)
{
	stringstream log;
	TAPIINT32 iResult = 0;
	TAPIUINT32 sessionID = 0;
	ITapTrade::TapAPINewOrder order;
	arch_strcpy(order.AccountNo, datacore->userNo, sizeof(ITapTrade::TAPISTR_20));
	arch_strcpy(order.CommodityNo, datacore->commodityNo, sizeof(ITapTrade::TAPISTR_10));
	arch_strcpy(order.ExchangeNo, datacore->exchangeNo, sizeof(ITapTrade::TAPISTR_10));
	arch_strcpy(order.ContractNo, datacore->contractNo, sizeof(ITapTrade::TAPISTR_10));
	order.CommodityType = ITapTrade::TAPI_COMMODITY_TYPE_FUTURES;
	order.OrderType = ITapTrade::TAPI_ORDER_TYPE_MARKET;
	order.OrderSource = ITapTrade::TAPI_ORDER_SOURCE_PROGRAM;
	order.TimeInForce = ITapTrade::TAPI_ORDER_TIMEINFORCE_GFD;
	order.OrderSide = direct ? ITapTrade::TAPI_SIDE_BUY : ITapTrade::TAPI_SIDE_SELL;
	order.OrderPrice = 0;
	order.OrderQty = 1;
	ITapTrade::TAPISTR_50 orderNo;
	iResult = tradeApi->InsertOrder(&sessionID, &orderNo, &order);
	if (iResult) {
		log << "ÏÂµ¥²Ù×÷Ê§°Ü£¬ErrorCode=" << iResult;
		LOGERR(logger, &log);
	}
}


void Trader::Cancel()
{
	
}