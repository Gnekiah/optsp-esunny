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
		log << "��¼�ɹ�"
			<< ", �û���=" << info->UserNo
			<< ", �ϴε�¼IP=" << info->LastLoginIP
			<< ", �ϴε�¼ʱ��=" << info->LastLoginTime
			<< ", �ϴ��˳�ʱ��=" << info->LastLogoutTime
			<< ", �û�����=" << info->UserType;
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
		log << "Ʒ����Ϣ"
			<< ", ����������=" << info->Commodity.CommodityNo
			<< ", Ʒ������=" << info->Commodity.CommodityType
			<< ", ����������=" << info->Commodity.ExchangeNo
			<< ", ��Լ����=" << info->CommodityContractLen
			<< ", ���۷�ĸ=" << info->CommodityDenominator
			<< ", ��С�䶯��λ=" << info->CommodityTickSize
			<< ", ÿ�ֳ���=" << info->ContractSize;
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
		log << "��Լ��Ϣ"
			<< ", Ʒ�ֱ��=" << info->Contract.Commodity.CommodityNo
			<< ", Ʒ������=" << info->Contract.Commodity.CommodityType
			<< ", ����������=" << info->Contract.Commodity.ExchangeNo
			<< ", ��Լ����1=" << info->Contract.ContractNo1
			<< ", ��Լ����2=" << info->Contract.ContractNo2;
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
		TapAPIQuoteWhole tick;
		memcpy(&tick, info, sizeof(TapAPIQuoteWhole));
		datacore->tickBuffer->push(tick);
		log << "�������"
			<< ", Ʒ�ֱ��=" << info->Contract.Commodity.CommodityNo
			<< ", ��Լ����=" << info->Contract.ContractNo1
			<< ", ʱ���=" << info->DateTimeStamp
			<< ", ���¼�=" << info->QLastPrice
			<< ", ���³ɽ���=" << info->QLastQty << std::endl
			<< ", ���̼�=" << info->QOpeningPrice
			<< ", ��߼�=" << info->QHighPrice
			<< ", ��ͼ�=" << info->QLowPrice
			<< ", ���̼�=" << info->QClosingPrice
			<< ", �����=" << info->QSettlePrice
			<< ", �ǵ�ֵ=" << info->QChangeValue
			<< ", �Ƿ�=" << info->QChangeRate
			<< ", ����=" << info->QChangeSpeed
			<< ", ����=" << info->QAveragePrice
			<< ", ���վ���=" << info->Q5DAvgQty
			<< ", ��ͣ��=" << info->QLimitDownPrice
			<< ", ��ͣ��=" << info->QLimitUpPrice << std::endl
			<< ", ���=" << info->QSwing
			<< ", ί������=" << info->QTotalAskQty
			<< ", ί������=" << info->QTotalBidQty
			<< ", �����ܳɽ���=" << info->QTotalQty
			<< ", ���ճɽ����=" << info->QTotalTurnover
			<< ", ����ʵ��=" << info->QCurrDelta
			<< ", ��������=" << info->QImpliedAskPrice
			<< ", ��������=" << info->QImpliedAskQty
			<< ", �������=" << info->QImpliedBidPrice
			<< ", ��������=" << info->QImpliedBidQty << std::endl
			<< ", �����̼�=" << info->QPreClosingPrice
			<< ", ������=" << info->QPreSettlePrice
			<< ", ��ֲ���=" << info->QPrePositionQty
			<< ", ����ʵ��=" << info->QPreDelta
			<< ", ��ʷ��߼�=" << info->QHisHighPrice
			<< ", ��ʷ��ͼ�=" << info->QHisLowPrice
			<< ", ������=" << info->QInsideQty
			<< ", ������=" << info->QOutsideQty
			<< ", ��ӯ��=" << info->QPERatio
			<< ", �ֲ���=" << info->QPositionQty
			<< ", �ֲ�����=" << info->QPositionTrend
			<< ", ����ֵ=" << info->QTotalValue
			<< ", ��ͨ��ֵ=" << info->QNegotiableValue
			<< ", ������=" << info->QTurnoverRate;
		for (int i = 0; i < 20; i++) {
			if (i % 5 == 0)
				log << std::endl;
			log << ", ���" << i + 1 << "=" << info->QBidPrice[i];
			log << ", ����" << i + 1 << "=" << info->QBidQty[i];
		}
		for (int i = 0; i < 20; i++) {
			if (i % 5 == 0)
				log << std::endl;
			log << ", ����" << i + 1 << "=" << info->QAskPrice[i];
			log << ", ����" << i + 1 << "=" << info->QAskQty[i];
		}			
		//	<< ", ��Լ����2=" << info->Contract.ContractNo2
		//	<< ", ִ�м�1=" << info->Contract.StrikePrice1
		//	<< ", ִ�м�2=" << info->Contract.StrikePrice2
		//	<< ", ���ֱ��=" << info->CurrencyNo
		//	<< ", UnderlyContract.CallOrPutFlag1=" << info->UnderlyContract.CallOrPutFlag1
		//	<< ", UnderlyContract.CallOrPutFlag2=" << info->UnderlyContract.CallOrPutFlag2
		//	<< ", UnderlyContract.Commodity.CommodityNo=" << info->UnderlyContract.Commodity.CommodityNo
		//	<< ", UnderlyContract.Commodity.CommodityType=" << info->UnderlyContract.Commodity.CommodityType
		//	<< ", UnderlyContract.Commodity.ExchangeNo=" << info->UnderlyContract.Commodity.ExchangeNo
		//	<< ", UnderlyContract.ContractNo1=" << info->UnderlyContract.ContractNo1
		//	<< ", UnderlyContract.ContractNo2=" << info->UnderlyContract.ContractNo2
		//	<< ", UnderlyContract.StrikePrice1=" << info->UnderlyContract.StrikePrice1
		//	<< ", UnderlyContract.StrikePrice2=" << info->UnderlyContract.StrikePrice2
		//	<< ", ���ǿ�����ʾ1=" << info->Contract.CallOrPutFlag1
		//	<< ", ���ǿ�����ʾ2=" << info->Contract.CallOrPutFlag2
		//	<< ", Ʒ������=" << info->Contract.Commodity.CommodityType
		//	<< ", ����������=" << info->Contract.Commodity.ExchangeNo
		//	<< ", ����״̬=" << info->TradingState 
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
		log << "�˶���Լ"
			<< ", ��Լ����1=" << info->ContractNo1
			<< ", ��Լ����2=" << info->ContractNo2
			<< ", Ʒ�ֱ��=" << info->Commodity.CommodityNo
			<< ", Ʒ������=" << info->Commodity.CommodityType
			<< ", ���������=" << info->Commodity.ExchangeNo;
		//	<< ", CallOrPutFlag1=" << info->CallOrPutFlag1
		//	<< ", CallOrPutFlag2=" << info->CallOrPutFlag2
		//	<< ", StrikePrice1=" << info->StrikePrice1
		//	<< ", StrikePrice2=" << info->StrikePrice2
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
	TapAPIQuoteWhole tick;
	memcpy(&tick, info, sizeof(TapAPIQuoteWhole));
	datacore->tickBuffer->push(tick);
	log << "�������"
		<< ", Ʒ�ֱ��=" << info->Contract.Commodity.CommodityNo
		<< ", ��Լ����=" << info->Contract.ContractNo1
		<< ", ʱ���=" << info->DateTimeStamp
		<< ", ���¼�=" << info->QLastPrice
		<< ", ���³ɽ���=" << info->QLastQty << std::endl
		<< ", ���̼�=" << info->QOpeningPrice
		<< ", ��߼�=" << info->QHighPrice
		<< ", ��ͼ�=" << info->QLowPrice
		<< ", ���̼�=" << info->QClosingPrice
		<< ", �����=" << info->QSettlePrice
		<< ", �ǵ�ֵ=" << info->QChangeValue
		<< ", �Ƿ�=" << info->QChangeRate
		<< ", ����=" << info->QChangeSpeed
		<< ", ����=" << info->QAveragePrice
		<< ", ���վ���=" << info->Q5DAvgQty
		<< ", ��ͣ��=" << info->QLimitDownPrice
		<< ", ��ͣ��=" << info->QLimitUpPrice << std::endl
		<< ", ���=" << info->QSwing
		<< ", ί������=" << info->QTotalAskQty
		<< ", ί������=" << info->QTotalBidQty
		<< ", �����ܳɽ���=" << info->QTotalQty
		<< ", ���ճɽ����=" << info->QTotalTurnover
		<< ", ����ʵ��=" << info->QCurrDelta
		<< ", ��������=" << info->QImpliedAskPrice
		<< ", ��������=" << info->QImpliedAskQty
		<< ", �������=" << info->QImpliedBidPrice
		<< ", ��������=" << info->QImpliedBidQty << std::endl
		<< ", �����̼�=" << info->QPreClosingPrice
		<< ", ������=" << info->QPreSettlePrice
		<< ", ��ֲ���=" << info->QPrePositionQty
		<< ", ����ʵ��=" << info->QPreDelta
		<< ", ��ʷ��߼�=" << info->QHisHighPrice
		<< ", ��ʷ��ͼ�=" << info->QHisLowPrice
		<< ", ������=" << info->QInsideQty
		<< ", ������=" << info->QOutsideQty
		<< ", ��ӯ��=" << info->QPERatio
		<< ", �ֲ���=" << info->QPositionQty
		<< ", �ֲ�����=" << info->QPositionTrend
		<< ", ����ֵ=" << info->QTotalValue
		<< ", ��ͨ��ֵ=" << info->QNegotiableValue
		<< ", ������=" << info->QTurnoverRate;
	for (int i = 0; i < 20; i++) {
		if (i % 5 == 0)
			log << std::endl;
		log << ", ���" << i + 1 << "=" << info->QBidPrice[i];
		log << ", ����" << i + 1 << "=" << info->QBidQty[i];
	}
	for (int i = 0; i < 20; i++) {
		if (i % 5 == 0)
			log << std::endl;
		log << ", ����" << i + 1 << "=" << info->QAskPrice[i];
		log << ", ����" << i + 1 << "=" << info->QAskQty[i];
	}
	//	<< ", ��Լ����2=" << info->Contract.ContractNo2
	//	<< ", ִ�м�1=" << info->Contract.StrikePrice1
	//	<< ", ִ�м�2=" << info->Contract.StrikePrice2
	//	<< ", ���ֱ��=" << info->CurrencyNo
	//	<< ", UnderlyContract.CallOrPutFlag1=" << info->UnderlyContract.CallOrPutFlag1
	//	<< ", UnderlyContract.CallOrPutFlag2=" << info->UnderlyContract.CallOrPutFlag2
	//	<< ", UnderlyContract.Commodity.CommodityNo=" << info->UnderlyContract.Commodity.CommodityNo
	//	<< ", UnderlyContract.Commodity.CommodityType=" << info->UnderlyContract.Commodity.CommodityType
	//	<< ", UnderlyContract.Commodity.ExchangeNo=" << info->UnderlyContract.Commodity.ExchangeNo
	//	<< ", UnderlyContract.ContractNo1=" << info->UnderlyContract.ContractNo1
	//	<< ", UnderlyContract.ContractNo2=" << info->UnderlyContract.ContractNo2
	//	<< ", UnderlyContract.StrikePrice1=" << info->UnderlyContract.StrikePrice1
	//	<< ", UnderlyContract.StrikePrice2=" << info->UnderlyContract.StrikePrice2
	//	<< ", ���ǿ�����ʾ1=" << info->Contract.CallOrPutFlag1
	//	<< ", ���ǿ�����ʾ2=" << info->Contract.CallOrPutFlag2
	//	<< ", Ʒ������=" << info->Contract.Commodity.CommodityType
	//	<< ", ����������=" << info->Contract.Commodity.ExchangeNo
	//	<< ", ����״̬=" << info->TradingState 
	LOGMSG(logger, &log);
}