#include "quotespi.h"

#include <sstream>

using std::stringstream;

QuoteSpi::QuoteSpi(Logger *logger)
{
	this->logger = logger;
	ready = false;
}


/**
* @brief	ϵͳ��¼���̻ص���
* @details	�˺���ΪLogin()��¼�����Ļص�������Login()�ɹ���������·���ӣ�Ȼ��API������������͵�¼��֤��Ϣ��
*			��¼�ڼ�����ݷ�������͵�¼�Ļ�����Ϣ���ݵ��˻ص������С�
* @param[in] errorCode ���ش�����,0��ʾ�ɹ���
* @param[in] info ��½Ӧ����Ϣ�����errorCode!=0����info=NULL��
* @attention	�ûص����سɹ���˵���û���¼�ɹ������ǲ�����API׼����ϡ���Ҫ�ȵ�OnAPIReady���ܽ��в�ѯ�붩������
* @ingroup G_Q_Login
*/
void TAP_CDECL QuoteSpi::OnRspLogin(TAPIINT32 errorCode, const TapAPIQuotLoginRspInfo *info) 
{
	stringstream log;
	if (!errorCode) {
		log << "��¼�ɹ�";
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
		log << "��½ʧ�ܣ�ErrorCode=" << errorCode;
		LOGERR(logger, &log);
	}
}


/**
* @brief	֪ͨ�û�API׼��������
* @details	ֻ���û��ص��յ��˾���֪ͨʱ���ܽ��к����ĸ����������ݲ�ѯ������\n
*			�˻ص�������API�ܷ����������ı�־��
* @attention  ������ſ��Խ��к�����������
* @ingroup G_Q_Login
*/
void TAP_CDECL QuoteSpi::OnAPIReady()
{
	stringstream log;
	ready = true;
	log << "Quote API ׼������";
	LOGINF(logger, &log);
}


/**
* @brief	API�ͷ���ʧȥ���ӵĻص�
* @details	��APIʹ�ù������������߱��������������ʧȥ���Ӻ󶼻ᴥ���˻ص�֪ͨ�û���������������Ѿ��Ͽ���
* @param[in] reasonCode �Ͽ�ԭ����롣����ԭ����μ��������б� \n
* @ingroup G_Q_Disconnect
*/
void TAP_CDECL QuoteSpi::OnDisconnect(TAPIINT32 reasonCode)
{
	stringstream log;
	ready = false;
	log << "Quote API ��������������жϣ�ErrorCode=" << reasonCode;
	LOGERR(logger, &log);
}


/**
* @brief	��������Ʒ����Ϣ��
* @details	�˻ص��ӿ��������û����صõ�������Ʒ����Ϣ��
* @param[in] sessionID ����ĻỰID
* @param[in] errorCode �����룬��errorCode!=0ʱ,infoΪNULL��
* @param[in] isLast ��ʾ�Ƿ������һ�����ݣ�
* @param[in] info ���ص���Ϣ�������ʼָ�롣
* @attention  ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
* @ingroup G_Q_Commodity
*/
void TAP_CDECL QuoteSpi::OnRspQryCommodity(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteCommodityInfo *info)
{
	stringstream log;
	if (!errorCode) {
		log << "��������Ʒ����Ϣ��SessionID=" << sessionID << ", isLast=" << isLast;
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
		log << "��ȡ����Ʒ����Ϣʧ�ܣ�ErrorCode=" << errorCode;
		LOGERR(logger, &log);
	}
}


/**
* @brief ����ϵͳ�к�Լ��Ϣ
* @param[in] sessionID ����ĻỰID��
* @param[in] errorCode �����룬��errorCode!=0ʱ,infoΪNULL��
* @param[in] isLast ��ʾ�Ƿ������һ�����ݣ�
* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
* @ingroup G_Q_Contract
*/
void TAP_CDECL QuoteSpi::OnRspQryContract(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteContractInfo *info)
{
	stringstream log;
	if (!errorCode) {
		log << "���غ�Լ��Ϣ��SessionID=" << sessionID << ", isLast=" << isLast;
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
		log << "���غ�Լ��Ϣʧ�ܣ�ErrorCode=" << errorCode;
		LOGERR(logger, &log);
	}
}


/**
* @brief	���ض��������ȫ�ġ�
* @details	�˻ص��ӿ��������ض��������ȫ�ġ�ȫ��Ϊ��ǰʱ���������Ϣ��
* @param[in] sessionID ����ĻỰID��
* @param[in] isLast ��ʾ�Ƿ������һ�����ݣ�
* @param[in] errorCode �����룬��errorCode!=0ʱ,infoΪNULL��
* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
* @attention  ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
* @ingroup G_Q_Quote
*/
void TAP_CDECL QuoteSpi::OnRspSubscribeQuote(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteWhole *info)
{
	stringstream log;
	if (!errorCode) {
		log << "���ض��������ȫ�ģ�SessionID=" << sessionID << ", isLast=" << isLast;
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
		log << "���ض��������ȫ��ʧ�ܣ�ErrorCode=" << errorCode;
		LOGERR(logger, &log);
	}
}


/**
* @brief �˶�ָ����Լ������Ľ���ص�
* @param[in] sessionID ����ĻỰID��
* @param[in] errorCode �����룬��errorCode!=0ʱ,infoΪNULL��
* @param[in] isLast ��ʾ�Ƿ������һ�����ݣ�
* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
* @attention  ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
* @ingroup G_Q_Quote
*/
void TAP_CDECL QuoteSpi::OnRspUnSubscribeQuote(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIContract *info)
{
	stringstream log;
	if (!errorCode) {
		log << "�˶�ָ����Լ����Ľ����SessionID=" << sessionID << ", isLast=" << isLast;
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
		log << "�˶���Լ����ʧ�ܣ�ErrorCode=" << errorCode;
		LOGERR(logger, &log);
	}
}


/**
* @brief	���ض�������ı仯���ݡ�
* @details	�˻ص��ӿ�����֪ͨ�û�������Ϣ�����˱仯�������û��ύ�µ�����ȫ�ġ�
* @param[in] info ���µ�����ȫ������
* @attention ��Ҫ�޸ĺ�ɾ��Quoteָʾ�����ݣ��������ý���������������Ч��
* @ingroup G_Q_Quote
*/
void TAP_CDECL QuoteSpi::OnRtnQuote(const TapAPIQuoteWhole *info)
{
	stringstream log;
	log << "��ö�������ı仯����";
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