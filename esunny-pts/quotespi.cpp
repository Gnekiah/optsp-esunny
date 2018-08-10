#include "quotespi.h"

#include <sstream>

using std::stringstream;

QuoteSpi::QuoteSpi(Logger *logger)
{
	this->logger = logger;
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
		log << "登录成功";
		LOGINF(logger, &log);
		log << "TapAPIQuotLoginRspInfo"
			<< ", InitTime=" << info->InitTime
			<< ", LastLoginIP=" << info->LastLoginIP
			<< ", LastLoginProt=" << info->LastLoginProt
			<< ", LastLoginTime=" << info->LastLoginTime
			<< ", LastLogoutTime=" << info->LastLogoutTime
			<< ", LastSettleTime=" << info->LastSettleTime
			<< ", QuoteTempPassword=" << info->QuoteTempPassword
			<< ", ReservedInfo=" << info->ReservedInfo
			<< ", StartTime=" << info->StartTime
			<< ", TradeDate=" << info->TradeDate
			<< ", UserName=" << info->UserName
			<< ", UserNo=" << info->UserNo
			<< ", UserType" << info->UserType;
		LOGMSG(logger, &log);
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
		log << "返回所有品种信息，SessionID=" << sessionID << ", isLast=" << isLast;
		LOGMSG(logger, &log);
		log << "TapAPIQuoteCommodityInfo"
			<< ", CmbDirect=" << info->CmbDirect
			<< ", Commodity.CommodityNo=" << info->Commodity.CommodityNo
			<< ", Commodity.CommodityType=" << info->Commodity.CommodityType
			<< ", Commodity.ExchangeNo=" << info->Commodity.ExchangeNo
			<< ", CommodityContractLen=" << info->CommodityContractLen
			<< ", CommodityDenominator=" << info->CommodityDenominator
			<< ", CommodityEngName=" << info->CommodityEngName
			<< ", CommodityName=" << info->CommodityName
			<< ", CommodityTickSize=" << info->CommodityTickSize
			<< ", ContractSize=" << info->ContractSize
			<< ", IsDST=" << info->IsDST
			<< ", RelateCommodity1.CommodityNo=" << info->RelateCommodity1.CommodityNo
			<< ", RelateCommodity1.CommodityType=" << info->RelateCommodity1.CommodityType
			<< ", RelateCommodity1.ExchangeNo=" << info->RelateCommodity1.ExchangeNo
			<< ", RelateCommodity2.CommodityNo=" << info->RelateCommodity2.CommodityNo
			<< ", RelateCommodity2.CommodityType=" << info->RelateCommodity2.CommodityType
			<< ", RelateCommodity2.ExchangeNo=" << info->RelateCommodity2.ExchangeNo; 
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
		log << "返回合约信息，SessionID=" << sessionID << ", isLast=" << isLast;
		LOGMSG(logger, &log);
		log << "TapAPIQuoteContractInfo"
			<< ", Contract.CallOrPutFlag1=" << info->Contract.CallOrPutFlag1
			<< ", Contract.CallOrPutFlag2=" << info->Contract.CallOrPutFlag2
			<< ", Contract.Commodity.CommodityNo=" << info->Contract.Commodity.CommodityNo
			<< ", Contract.Commodity.CommodityType=" << info->Contract.Commodity.CommodityType
			<< ", Contract.Commodity.ExchangeNo=" << info->Contract.Commodity.ExchangeNo
			<< ", Contract.ContractNo1=" << info->Contract.ContractNo1
			<< ", Contract.ContractNo2=" << info->Contract.ContractNo2
			<< ", Contract.StrikePrice1=" << info->Contract.StrikePrice1
			<< ", Contract.StrikePrice2=" << info->Contract.StrikePrice2
			<< ", ContractExpDate=" << info->ContractExpDate
			<< ", ContractName=" << info->ContractName
			<< ", ContractType=" << info->ContractType
			<< ", FirstNoticeDate=" << info->FirstNoticeDate
			<< ", LastTradeDate=" << info->LastTradeDate
			<< ", QuoteUnderlyingContract=" << info->QuoteUnderlyingContract;
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
		log << "返回订阅行情的全文，SessionID=" << sessionID << ", isLast=" << isLast;
		LOGMSG(logger, &log);
		log << "TapAPIQuoteWhole"
			<< ", Contract.CallOrPutFlag1=" << info->Contract.CallOrPutFlag1
			<< ", Contract.CallOrPutFlag2=" << info->Contract.CallOrPutFlag2
			<< ", Contract.Commodity.CommodityNo=" << info->Contract.Commodity.CommodityNo
			<< ", Contract.Commodity.CommodityType=" << info->Contract.Commodity.CommodityType
			<< ", Contract.Commodity.ExchangeNo=" << info->Contract.Commodity.ExchangeNo
			<< ", Contract.ContractNo1=" << info->Contract.ContractNo1
			<< ", Contract.ContractNo2=" << info->Contract.ContractNo2
			<< ", Contract.StrikePrice1=" << info->Contract.StrikePrice1
			<< ", Contract.StrikePrice2=" << info->Contract.StrikePrice2
			<< ", CurrencyNo=" << info->CurrencyNo
			<< ", DateTimeStamp=" << info->DateTimeStamp
			<< ", Q5DAvgQty=" << info->Q5DAvgQty
			<< ", QAskPrice=" << info->QAskPrice
			<< ", QAskQty=" << info->QAskQty
			<< ", QAveragePrice=" << info->QAveragePrice
			<< ", QBidPrice=" << info->QBidPrice
			<< ", QBidQty=" << info->QBidQty
			<< ", QChangeRate=" << info->QChangeRate
			<< ", QChangeSpeed=" << info->QChangeSpeed
			<< ", QChangeValue=" << info->QChangeValue
			<< ", QClosingPrice=" << info->QClosingPrice
			<< ", QCurrDelta=" << info->QCurrDelta
			<< ", QHighPrice=" << info->QHighPrice
			<< ", QHisHighPrice=" << info->QHisHighPrice
			<< ", QHisLowPrice=" << info->QHisLowPrice
			<< ", QImpliedAskPrice=" << info->QImpliedAskPrice
			<< ", QImpliedAskQty=" << info->QImpliedAskQty
			<< ", QImpliedBidPrice=" << info->QImpliedBidPrice
			<< ", QImpliedBidQty=" << info->QImpliedBidQty
			<< ", QInsideQty=" << info->QInsideQty
			<< ", QLastPrice=" << info->QLastPrice
			<< ", QLastQty=" << info->QLastQty
			<< ", QLimitDownPrice=" << info->QLimitDownPrice
			<< ", QLimitUpPrice=" << info->QLimitUpPrice
			<< ", QLowPrice=" << info->QLowPrice
			<< ", QNegotiableValue=" << info->QNegotiableValue
			<< ", QOpeningPrice=" << info->QOpeningPrice
			<< ", QOutsideQty=" << info->QOutsideQty
			<< ", QPERatio=" << info->QPERatio
			<< ", QPositionQty=" << info->QPositionQty
			<< ", QPositionTrend=" << info->QPositionTrend
			<< ", QPreClosingPrice=" << info->QPreClosingPrice
			<< ", QPreDelta=" << info->QPreDelta
			<< ", QPrePositionQty=" << info->QPrePositionQty
			<< ", QPreSettlePrice=" << info->QPreSettlePrice
			<< ", QSettlePrice=" << info->QSettlePrice
			<< ", QSwing=" << info->QSwing
			<< ", QTotalAskQty=" << info->QTotalAskQty
			<< ", QTotalBidQty=" << info->QTotalBidQty
			<< ", QTotalQty=" << info->QTotalQty
			<< ", QTotalTurnover=" << info->QTotalTurnover
			<< ", QTotalValue=" << info->QTotalValue
			<< ", QTurnoverRate=" << info->QTurnoverRate
			<< ", TradingState=" << info->TradingState
			<< ", UnderlyContract.CallOrPutFlag1=" << info->UnderlyContract.CallOrPutFlag1
			<< ", UnderlyContract.CallOrPutFlag2=" << info->UnderlyContract.CallOrPutFlag2
			<< ", UnderlyContract.Commodity.CommodityNo=" << info->UnderlyContract.Commodity.CommodityNo
			<< ", UnderlyContract.Commodity.CommodityType=" << info->UnderlyContract.Commodity.CommodityType
			<< ", UnderlyContract.Commodity.ExchangeNo=" << info->UnderlyContract.Commodity.ExchangeNo
			<< ", UnderlyContract.ContractNo1=" << info->UnderlyContract.ContractNo1
			<< ", UnderlyContract.ContractNo2=" << info->UnderlyContract.ContractNo2
			<< ", UnderlyContract.StrikePrice1=" << info->UnderlyContract.StrikePrice1
			<< ", UnderlyContract.StrikePrice2=" << info->UnderlyContract.StrikePrice2;
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
		log << "退订指定合约行情的结果，SessionID=" << sessionID << ", isLast=" << isLast;
		LOGMSG(logger, &log);
		log << "TapAPIContract"
			<< ", CallOrPutFlag1=" << info->CallOrPutFlag1
			<< ", CallOrPutFlag2=" << info->CallOrPutFlag2
			<< ", Commodity.CommodityNo=" << info->Commodity.CommodityNo
			<< ", Commodity.CommodityType=" << info->Commodity.CommodityType
			<< ", Commodity.ExchangeNo=" << info->Commodity.ExchangeNo
			<< ", ContractNo1=" << info->ContractNo1
			<< ", ContractNo2=" << info->ContractNo2
			<< ", StrikePrice1=" << info->StrikePrice1
			<< ", StrikePrice2=" << info->StrikePrice2;
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
	log << "获得订阅行情的变化内容";
	LOGMSG(logger, &log);
	log << "TapAPIQuoteWhole"
		<< ", Contract.CallOrPutFlag1=" << info->Contract.CallOrPutFlag1
		<< ", Contract.CallOrPutFlag2=" << info->Contract.CallOrPutFlag2
		<< ", Contract.Commodity.CommodityNo=" << info->Contract.Commodity.CommodityNo
		<< ", Contract.Commodity.CommodityType=" << info->Contract.Commodity.CommodityType
		<< ", Contract.Commodity.ExchangeNo=" << info->Contract.Commodity.ExchangeNo
		<< ", Contract.ContractNo1=" << info->Contract.ContractNo1
		<< ", Contract.ContractNo2=" << info->Contract.ContractNo2
		<< ", Contract.StrikePrice1=" << info->Contract.StrikePrice1
		<< ", Contract.StrikePrice2=" << info->Contract.StrikePrice2
		<< ", CurrencyNo=" << info->CurrencyNo
		<< ", DateTimeStamp=" << info->DateTimeStamp
		<< ", Q5DAvgQty=" << info->Q5DAvgQty
		<< ", QAskPrice=" << info->QAskPrice
		<< ", QAskQty=" << info->QAskQty
		<< ", QAveragePrice=" << info->QAveragePrice
		<< ", QBidPrice=" << info->QBidPrice
		<< ", QBidQty=" << info->QBidQty
		<< ", QChangeRate=" << info->QChangeRate
		<< ", QChangeSpeed=" << info->QChangeSpeed
		<< ", QChangeValue=" << info->QChangeValue
		<< ", QClosingPrice=" << info->QClosingPrice
		<< ", QCurrDelta=" << info->QCurrDelta
		<< ", QHighPrice=" << info->QHighPrice
		<< ", QHisHighPrice=" << info->QHisHighPrice
		<< ", QHisLowPrice=" << info->QHisLowPrice
		<< ", QImpliedAskPrice=" << info->QImpliedAskPrice
		<< ", QImpliedAskQty=" << info->QImpliedAskQty
		<< ", QImpliedBidPrice=" << info->QImpliedBidPrice
		<< ", QImpliedBidQty=" << info->QImpliedBidQty
		<< ", QInsideQty=" << info->QInsideQty
		<< ", QLastPrice=" << info->QLastPrice
		<< ", QLastQty=" << info->QLastQty
		<< ", QLimitDownPrice=" << info->QLimitDownPrice
		<< ", QLimitUpPrice=" << info->QLimitUpPrice
		<< ", QLowPrice=" << info->QLowPrice
		<< ", QNegotiableValue=" << info->QNegotiableValue
		<< ", QOpeningPrice=" << info->QOpeningPrice
		<< ", QOutsideQty=" << info->QOutsideQty
		<< ", QPERatio=" << info->QPERatio
		<< ", QPositionQty=" << info->QPositionQty
		<< ", QPositionTrend=" << info->QPositionTrend
		<< ", QPreClosingPrice=" << info->QPreClosingPrice
		<< ", QPreDelta=" << info->QPreDelta
		<< ", QPrePositionQty=" << info->QPrePositionQty
		<< ", QPreSettlePrice=" << info->QPreSettlePrice
		<< ", QSettlePrice=" << info->QSettlePrice
		<< ", QSwing=" << info->QSwing
		<< ", QTotalAskQty=" << info->QTotalAskQty
		<< ", QTotalBidQty=" << info->QTotalBidQty
		<< ", QTotalQty=" << info->QTotalQty
		<< ", QTotalTurnover=" << info->QTotalTurnover
		<< ", QTotalValue=" << info->QTotalValue
		<< ", QTurnoverRate=" << info->QTurnoverRate
		<< ", TradingState=" << info->TradingState
		<< ", UnderlyContract.CallOrPutFlag1=" << info->UnderlyContract.CallOrPutFlag1
		<< ", UnderlyContract.CallOrPutFlag2=" << info->UnderlyContract.CallOrPutFlag2
		<< ", UnderlyContract.Commodity.CommodityNo=" << info->UnderlyContract.Commodity.CommodityNo
		<< ", UnderlyContract.Commodity.CommodityType=" << info->UnderlyContract.Commodity.CommodityType
		<< ", UnderlyContract.Commodity.ExchangeNo=" << info->UnderlyContract.Commodity.ExchangeNo
		<< ", UnderlyContract.ContractNo1=" << info->UnderlyContract.ContractNo1
		<< ", UnderlyContract.ContractNo2=" << info->UnderlyContract.ContractNo2
		<< ", UnderlyContract.StrikePrice1=" << info->UnderlyContract.StrikePrice1
		<< ", UnderlyContract.StrikePrice2=" << info->UnderlyContract.StrikePrice2;
	LOGMSG(logger, &log);
}