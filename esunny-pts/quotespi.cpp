#include "quotespi.h"

#include <sstream>

using std::stringstream;

QuoteSpi::QuoteSpi(Logger *logger, Datacore *datacore)
{
	this->logger = logger;
	this->datacore = datacore;
	ready = false;
}


/**
* @brief	系统登录过程回调。
* @details	此函数为Login()登录函数的回调，调用Login()成功后建立了链路连接，然后API将向服务器发送登录认证信息，
*			登录期间的数据发送情况和登录的回馈信息传递到此回调函数中。
* @param[in] errorCode 返回错误码,0表示成功。
* @param[in] info 登陆应答信息，如果errorCode!=0，则info=NULL。
* @attention	该回调返回成功，说明用户登录成功。但是不代表API准备完毕。需要等到OnAPIReady才能进行查询与订阅请求。
* @ingroup G_Q_Login
*/
void TAP_CDECL QuoteSpi::OnRspLogin(TAPIINT32 errorCode, const TapAPIQuotLoginRspInfo *info) 
{
	stringstream log;
	if (!errorCode) {
		log << "登录成功"
			<< ", 用户名=" << info->UserNo
			<< ", 上次登录IP=" << info->LastLoginIP
			<< ", 上次登录时间=" << info->LastLoginTime
			<< ", 上次退出时间=" << info->LastLogoutTime
			<< ", 用户类型=" << info->UserType;
		//	<< ", InitTime=" << info->InitTime
		//	<< ", LastLoginProt=" << info->LastLoginProt
		//	<< ", LastSettleTime=" << info->LastSettleTime
		//	<< ", QuoteTempPassword=" << info->QuoteTempPassword
		//	<< ", ReservedInfo=" << info->ReservedInfo
		//	<< ", StartTime=" << info->StartTime
		//	<< ", TradeDate=" << info->TradeDate
		//	<< ", UserName=" << info->UserName
		LOGINF(logger, &log);
	}
	else {
		log << "登陆失败，ErrorCode=" << errorCode;
		LOGERR(logger, &log);
	}
}


/**
* @brief	通知用户API准备就绪。
* @details	只有用户回调收到此就绪通知时才能进行后续的各种行情数据查询操作。\n
*			此回调函数是API能否正常工作的标志。
* @attention  就绪后才可以进行后续正常操作
* @ingroup G_Q_Login
*/
void TAP_CDECL QuoteSpi::OnAPIReady()
{
	stringstream log;
	ready = true;
	log << "Quote API 准备就绪";
	LOGINF(logger, &log);
}


/**
* @brief	API和服务失去连接的回调
* @details	在API使用过程中主动或者被动与服务器服务失去连接后都会触发此回调通知用户与服务器的连接已经断开。
* @param[in] reasonCode 断开原因代码。具体原因请参见错误码列表 \n
* @ingroup G_Q_Disconnect
*/
void TAP_CDECL QuoteSpi::OnDisconnect(TAPIINT32 reasonCode)
{
	stringstream log;
	ready = false;
	log << "Quote API 与服务器的连接中断，ErrorCode=" << reasonCode;
	LOGERR(logger, &log);
}


/**
* @brief	返回所有品种信息。
* @details	此回调接口用于向用户返回得到的所有品种信息。
* @param[in] sessionID 请求的会话ID
* @param[in] errorCode 错误码，当errorCode!=0时,info为NULL；
* @param[in] isLast 标示是否是最后一批数据；
* @param[in] info 返回的信息数组的起始指针。
* @attention  不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
* @ingroup G_Q_Commodity
*/
void TAP_CDECL QuoteSpi::OnRspQryCommodity(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteCommodityInfo *info)
{
	stringstream log;
	if (!errorCode) {
		log << "品种信息"
			<< ", 交易所编码=" << info->Commodity.CommodityNo
			<< ", 品种类型=" << info->Commodity.CommodityType
			<< ", 交易所编码=" << info->Commodity.ExchangeNo
			<< ", 合约年限=" << info->CommodityContractLen
			<< ", 报价分母=" << info->CommodityDenominator
			<< ", 最小变动价位=" << info->CommodityTickSize
			<< ", 每手乘数=" << info->ContractSize;
		//	<< ", CommodityEngName=" << info->CommodityEngName
		//	<< ", CommodityName=" << info->CommodityName
		//	<< ", CmbDirect=" << info->CmbDirect
		//	<< ", IsDST=" << info->IsDST
		//	<< ", RelateCommodity1.CommodityNo=" << info->RelateCommodity1.CommodityNo
		//	<< ", RelateCommodity1.CommodityType=" << info->RelateCommodity1.CommodityType
		//	<< ", RelateCommodity1.ExchangeNo=" << info->RelateCommodity1.ExchangeNo
		//	<< ", RelateCommodity2.CommodityNo=" << info->RelateCommodity2.CommodityNo
		//	<< ", RelateCommodity2.CommodityType=" << info->RelateCommodity2.CommodityType
		//	<< ", RelateCommodity2.ExchangeNo=" << info->RelateCommodity2.ExchangeNo
		LOGMSG(logger, &log);
	}
	else {
		log << "获取所有品种信息失败，ErrorCode=" << errorCode;
		LOGERR(logger, &log);
	}
}


/**
* @brief 返回系统中合约信息
* @param[in] sessionID 请求的会话ID；
* @param[in] errorCode 错误码，当errorCode!=0时,info为NULL；
* @param[in] isLast 标示是否是最后一批数据；
* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
* @attention 不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
* @ingroup G_Q_Contract
*/
void TAP_CDECL QuoteSpi::OnRspQryContract(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteContractInfo *info)
{
	stringstream log;
	if (!errorCode) {
		log << "合约信息"
			<< ", 品种编号=" << info->Contract.Commodity.CommodityNo
			<< ", 品种类型=" << info->Contract.Commodity.CommodityType
			<< ", 交易所编码=" << info->Contract.Commodity.ExchangeNo
			<< ", 合约代码1=" << info->Contract.ContractNo1
			<< ", 合约代码2=" << info->Contract.ContractNo2;
		//	<< ", Contract.CallOrPutFlag1=" << info->Contract.CallOrPutFlag1
		//	<< ", Contract.CallOrPutFlag2=" << info->Contract.CallOrPutFlag2
		//	<< ", Contract.StrikePrice1=" << info->Contract.StrikePrice1
		//	<< ", Contract.StrikePrice2=" << info->Contract.StrikePrice2
		//	<< ", ContractExpDate=" << info->ContractExpDate
		//	<< ", ContractName=" << info->ContractName
		//	<< ", ContractType=" << info->ContractType
		//	<< ", FirstNoticeDate=" << info->FirstNoticeDate
		//	<< ", LastTradeDate=" << info->LastTradeDate
		//	<< ", QuoteUnderlyingContract=" << info->QuoteUnderlyingContract
		LOGMSG(logger, &log);
	}
	else {
		log << "返回合约信息失败，ErrorCode=" << errorCode;
		LOGERR(logger, &log);
	}
}


/**
* @brief	返回订阅行情的全文。
* @details	此回调接口用来返回订阅行情的全文。全文为当前时间的行情信息。
* @param[in] sessionID 请求的会话ID；
* @param[in] isLast 标示是否是最后一批数据；
* @param[in] errorCode 错误码，当errorCode!=0时,info为NULL；
* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
* @attention  不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
* @ingroup G_Q_Quote
*/
void TAP_CDECL QuoteSpi::OnRspSubscribeQuote(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteWhole *info)
{
	stringstream log;
	if (!errorCode) {
		TapAPIQuoteWhole tick;
		memcpy(&tick, info, sizeof(TapAPIQuoteWhole));
		datacore->tickBuffer->push(tick);
		log << "深度行情"
			<< ", 品种编号=" << info->Contract.Commodity.CommodityNo
			<< ", 合约代码=" << info->Contract.ContractNo1
			<< ", 时间戳=" << info->DateTimeStamp
			<< ", 最新价=" << info->QLastPrice
			<< ", 最新成交量=" << info->QLastQty << std::endl
			<< ", 开盘价=" << info->QOpeningPrice
			<< ", 最高价=" << info->QHighPrice
			<< ", 最低价=" << info->QLowPrice
			<< ", 收盘价=" << info->QClosingPrice
			<< ", 结算价=" << info->QSettlePrice
			<< ", 涨跌值=" << info->QChangeValue
			<< ", 涨幅=" << info->QChangeRate
			<< ", 涨速=" << info->QChangeSpeed
			<< ", 均价=" << info->QAveragePrice
			<< ", 五日均量=" << info->Q5DAvgQty
			<< ", 跌停价=" << info->QLimitDownPrice
			<< ", 涨停价=" << info->QLimitUpPrice << std::endl
			<< ", 振幅=" << info->QSwing
			<< ", 委卖总量=" << info->QTotalAskQty
			<< ", 委买总量=" << info->QTotalBidQty
			<< ", 当日总成交量=" << info->QTotalQty
			<< ", 当日成交金额=" << info->QTotalTurnover
			<< ", 今虚实度=" << info->QCurrDelta
			<< ", 隐含卖价=" << info->QImpliedAskPrice
			<< ", 隐含卖量=" << info->QImpliedAskQty
			<< ", 隐含买价=" << info->QImpliedBidPrice
			<< ", 隐含买量=" << info->QImpliedBidQty << std::endl
			<< ", 昨收盘价=" << info->QPreClosingPrice
			<< ", 昨结算价=" << info->QPreSettlePrice
			<< ", 昨持仓量=" << info->QPrePositionQty
			<< ", 昨虚实度=" << info->QPreDelta
			<< ", 历史最高价=" << info->QHisHighPrice
			<< ", 历史最低价=" << info->QHisLowPrice
			<< ", 内盘量=" << info->QInsideQty
			<< ", 外盘量=" << info->QOutsideQty
			<< ", 市盈率=" << info->QPERatio
			<< ", 持仓量=" << info->QPositionQty
			<< ", 持仓走势=" << info->QPositionTrend
			<< ", 总市值=" << info->QTotalValue
			<< ", 流通市值=" << info->QNegotiableValue
			<< ", 换手率=" << info->QTurnoverRate;
		for (int i = 0; i < 20; i++) {
			if (i % 5 == 0)
				log << std::endl;
			log << ", 买价" << i + 1 << "=" << info->QBidPrice[i];
			log << ", 买量" << i + 1 << "=" << info->QBidQty[i];
		}
		for (int i = 0; i < 20; i++) {
			if (i % 5 == 0)
				log << std::endl;
			log << ", 卖价" << i + 1 << "=" << info->QAskPrice[i];
			log << ", 卖量" << i + 1 << "=" << info->QAskQty[i];
		}			
		//	<< ", 合约代码2=" << info->Contract.ContractNo2
		//	<< ", 执行价1=" << info->Contract.StrikePrice1
		//	<< ", 执行价2=" << info->Contract.StrikePrice2
		//	<< ", 币种编号=" << info->CurrencyNo
		//	<< ", UnderlyContract.CallOrPutFlag1=" << info->UnderlyContract.CallOrPutFlag1
		//	<< ", UnderlyContract.CallOrPutFlag2=" << info->UnderlyContract.CallOrPutFlag2
		//	<< ", UnderlyContract.Commodity.CommodityNo=" << info->UnderlyContract.Commodity.CommodityNo
		//	<< ", UnderlyContract.Commodity.CommodityType=" << info->UnderlyContract.Commodity.CommodityType
		//	<< ", UnderlyContract.Commodity.ExchangeNo=" << info->UnderlyContract.Commodity.ExchangeNo
		//	<< ", UnderlyContract.ContractNo1=" << info->UnderlyContract.ContractNo1
		//	<< ", UnderlyContract.ContractNo2=" << info->UnderlyContract.ContractNo2
		//	<< ", UnderlyContract.StrikePrice1=" << info->UnderlyContract.StrikePrice1
		//	<< ", UnderlyContract.StrikePrice2=" << info->UnderlyContract.StrikePrice2
		//	<< ", 看涨看跌标示1=" << info->Contract.CallOrPutFlag1
		//	<< ", 看涨看跌标示2=" << info->Contract.CallOrPutFlag2
		//	<< ", 品种类型=" << info->Contract.Commodity.CommodityType
		//	<< ", 交易所编码=" << info->Contract.Commodity.ExchangeNo
		//	<< ", 交易状态=" << info->TradingState 
		LOGMSG(logger, &log);
	}
	else {
		log << "返回订阅行情的全文失败，ErrorCode=" << errorCode;
		LOGERR(logger, &log);
	}
}


/**
* @brief 退订指定合约的行情的结果回调
* @param[in] sessionID 请求的会话ID；
* @param[in] errorCode 错误码，当errorCode!=0时,info为NULL；
* @param[in] isLast 标示是否是最后一批数据；
* @param[in] info		指向返回的信息结构体。当errorCode不为0时，info为空。
* @attention  不要修改和删除info所指示的数据；函数调用结束，参数不再有效。
* @ingroup G_Q_Quote
*/
void TAP_CDECL QuoteSpi::OnRspUnSubscribeQuote(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIContract *info)
{
	stringstream log;
	if (!errorCode) {
		log << "退订合约"
			<< ", 合约代码1=" << info->ContractNo1
			<< ", 合约代码2=" << info->ContractNo2
			<< ", 品种编号=" << info->Commodity.CommodityNo
			<< ", 品种类型=" << info->Commodity.CommodityType
			<< ", 交易所编号=" << info->Commodity.ExchangeNo;
		//	<< ", CallOrPutFlag1=" << info->CallOrPutFlag1
		//	<< ", CallOrPutFlag2=" << info->CallOrPutFlag2
		//	<< ", StrikePrice1=" << info->StrikePrice1
		//	<< ", StrikePrice2=" << info->StrikePrice2
		LOGMSG(logger, &log);
	}
	else {
		log << "退订合约行情失败，ErrorCode=" << errorCode;
		LOGERR(logger, &log);
	}
}


/**
* @brief	返回订阅行情的变化内容。
* @details	此回调接口用来通知用户行情信息产生了变化，并向用户提交新的行情全文。
* @param[in] info 最新的行情全文内容
* @attention 不要修改和删除Quote指示的数据；函数调用结束，参数不再有效。
* @ingroup G_Q_Quote
*/
void TAP_CDECL QuoteSpi::OnRtnQuote(const TapAPIQuoteWhole *info)
{
	stringstream log;
	TapAPIQuoteWhole tick;
	memcpy(&tick, info, sizeof(TapAPIQuoteWhole));
	datacore->tickBuffer->push(tick);
	log << "深度行情"
		<< ", 品种编号=" << info->Contract.Commodity.CommodityNo
		<< ", 合约代码=" << info->Contract.ContractNo1
		<< ", 时间戳=" << info->DateTimeStamp
		<< ", 最新价=" << info->QLastPrice
		<< ", 最新成交量=" << info->QLastQty << std::endl
		<< ", 开盘价=" << info->QOpeningPrice
		<< ", 最高价=" << info->QHighPrice
		<< ", 最低价=" << info->QLowPrice
		<< ", 收盘价=" << info->QClosingPrice
		<< ", 结算价=" << info->QSettlePrice
		<< ", 涨跌值=" << info->QChangeValue
		<< ", 涨幅=" << info->QChangeRate
		<< ", 涨速=" << info->QChangeSpeed
		<< ", 均价=" << info->QAveragePrice
		<< ", 五日均量=" << info->Q5DAvgQty
		<< ", 跌停价=" << info->QLimitDownPrice
		<< ", 涨停价=" << info->QLimitUpPrice << std::endl
		<< ", 振幅=" << info->QSwing
		<< ", 委卖总量=" << info->QTotalAskQty
		<< ", 委买总量=" << info->QTotalBidQty
		<< ", 当日总成交量=" << info->QTotalQty
		<< ", 当日成交金额=" << info->QTotalTurnover
		<< ", 今虚实度=" << info->QCurrDelta
		<< ", 隐含卖价=" << info->QImpliedAskPrice
		<< ", 隐含卖量=" << info->QImpliedAskQty
		<< ", 隐含买价=" << info->QImpliedBidPrice
		<< ", 隐含买量=" << info->QImpliedBidQty << std::endl
		<< ", 昨收盘价=" << info->QPreClosingPrice
		<< ", 昨结算价=" << info->QPreSettlePrice
		<< ", 昨持仓量=" << info->QPrePositionQty
		<< ", 昨虚实度=" << info->QPreDelta
		<< ", 历史最高价=" << info->QHisHighPrice
		<< ", 历史最低价=" << info->QHisLowPrice
		<< ", 内盘量=" << info->QInsideQty
		<< ", 外盘量=" << info->QOutsideQty
		<< ", 市盈率=" << info->QPERatio
		<< ", 持仓量=" << info->QPositionQty
		<< ", 持仓走势=" << info->QPositionTrend
		<< ", 总市值=" << info->QTotalValue
		<< ", 流通市值=" << info->QNegotiableValue
		<< ", 换手率=" << info->QTurnoverRate;
	for (int i = 0; i < 20; i++) {
		if (i % 5 == 0)
			log << std::endl;
		log << ", 买价" << i + 1 << "=" << info->QBidPrice[i];
		log << ", 买量" << i + 1 << "=" << info->QBidQty[i];
	}
	for (int i = 0; i < 20; i++) {
		if (i % 5 == 0)
			log << std::endl;
		log << ", 卖价" << i + 1 << "=" << info->QAskPrice[i];
		log << ", 卖量" << i + 1 << "=" << info->QAskQty[i];
	}
	//	<< ", 合约代码2=" << info->Contract.ContractNo2
	//	<< ", 执行价1=" << info->Contract.StrikePrice1
	//	<< ", 执行价2=" << info->Contract.StrikePrice2
	//	<< ", 币种编号=" << info->CurrencyNo
	//	<< ", UnderlyContract.CallOrPutFlag1=" << info->UnderlyContract.CallOrPutFlag1
	//	<< ", UnderlyContract.CallOrPutFlag2=" << info->UnderlyContract.CallOrPutFlag2
	//	<< ", UnderlyContract.Commodity.CommodityNo=" << info->UnderlyContract.Commodity.CommodityNo
	//	<< ", UnderlyContract.Commodity.CommodityType=" << info->UnderlyContract.Commodity.CommodityType
	//	<< ", UnderlyContract.Commodity.ExchangeNo=" << info->UnderlyContract.Commodity.ExchangeNo
	//	<< ", UnderlyContract.ContractNo1=" << info->UnderlyContract.ContractNo1
	//	<< ", UnderlyContract.ContractNo2=" << info->UnderlyContract.ContractNo2
	//	<< ", UnderlyContract.StrikePrice1=" << info->UnderlyContract.StrikePrice1
	//	<< ", UnderlyContract.StrikePrice2=" << info->UnderlyContract.StrikePrice2
	//	<< ", 看涨看跌标示1=" << info->Contract.CallOrPutFlag1
	//	<< ", 看涨看跌标示2=" << info->Contract.CallOrPutFlag2
	//	<< ", 品种类型=" << info->Contract.Commodity.CommodityType
	//	<< ", 交易所编码=" << info->Contract.Commodity.ExchangeNo
	//	<< ", 交易状态=" << info->TradingState 
	LOGMSG(logger, &log);
}