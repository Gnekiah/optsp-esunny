#ifndef OPTS_ESN_TRADE_V9_OUTER_H_
#define OPTS_ESN_TRADE_V9_OUTER_H_
#define _ESNAPI_V9_

#include <mutex>

#include "arch.h"
#include "logger.h"

using std::atomic_bool;

class TradeSpi : public ITapTrade::ITapTradeAPINotify
{
private:
	Logger * logger = NULL;

public:
	atomic_bool ready;

public:
	TradeSpi(Logger *logger);

	///���ӳɹ��ص�֪ͨ
	void TAP_CDECL OnConnect();
	///ϵͳ��¼���̻ص���
	void TAP_CDECL OnRspLogin(ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPITradeLoginRspInfo *loginRspInfo);
	///������֤��ϵ��ʽ֪ͨ��
	void TAP_CDECL OnRtnContactInfo(ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TAPISTR_40 ContactInfo);
	///�����Ͷ�����֤��Ӧ��
	void TAP_CDECL OnRspRequestVertificateCode(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIRequestVertificateCodeRsp *rsp);
	///API�������ѻص�
	void TAP_CDECL OnExpriationDate(ITapTrade::TAPIDATE date, int days);
	///֪ͨ�û�API׼��������
	void TAP_CDECL OnAPIReady();
	///API�ͷ���ʧȥ���ӵĻص�
	void TAP_CDECL OnDisconnect(ITapTrade::TAPIINT32 reasonCode);
	///֪ͨ�û������޸Ľ��
	void TAP_CDECL OnRspChangePassword(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode);
	///��֤�˻����뷴��
	void TAP_CDECL OnRspAuthPassword(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode);
	///�����û�Ԥ����Ϣ����
	void TAP_CDECL OnRspSetReservedInfo(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TAPISTR_50 info);
	///�����û���Ϣ
	void TAP_CDECL OnRspQryAccount(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIUINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIAccountInfo *info);
	///�����ʽ��˻����ʽ���Ϣ
	void TAP_CDECL OnRspQryFund(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIFundData *info);
	///�û��ʽ�仯֪ͨ
	void TAP_CDECL OnRtnFund(const ITapTrade::TapAPIFundData *info);
	///����ϵͳ�еĽ�������Ϣ
	void TAP_CDECL OnRspQryExchange(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIExchangeInfo *info);
	///����ϵͳ��Ʒ����Ϣ
	void TAP_CDECL OnRspQryCommodity(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPICommodityInfo *info);
	///����ϵͳ�к�Լ��Ϣ
	void TAP_CDECL OnRspQryContract(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPITradeContractInfo *info);
	///����������Լ��Ϣ
	void TAP_CDECL OnRtnContract(const ITapTrade::TapAPITradeContractInfo *info);
	///��������Ӧ��
	void TAP_CDECL OnRspOrderAction(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderActionRsp *info);
	///������ί�С����µĻ��������ط��µ����͹����ġ�
	void TAP_CDECL OnRtnOrder(const ITapTrade::TapAPIOrderInfoNotice *info);
	///���ز�ѯ��ί����Ϣ
	void TAP_CDECL OnRspQryOrder(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIOrderInfo *info);
	///���ز�ѯ��ί�б仯������Ϣ
	void TAP_CDECL OnRspQryOrderProcess(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIOrderInfo *info);
	///���ز�ѯ�ĳɽ���Ϣ
	void TAP_CDECL OnRspQryFill(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIFillInfo *info);
	///�������ĳɽ���Ϣ
	void TAP_CDECL OnRtnFill(const ITapTrade::TapAPIFillInfo *info);
	///���ز�ѯ�ĳֲ�
	void TAP_CDECL OnRspQryPosition(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIPositionInfo *info);
	///�ֱֲ仯����֪ͨ
	void TAP_CDECL OnRtnPosition(const ITapTrade::TapAPIPositionInfo *info);
	///�ֲ�ӯ��֪ͨ
	void TAP_CDECL OnRtnPositionProfit(const ITapTrade::TapAPIPositionProfitNotice *info);
	///����ϵͳ�еı�����Ϣ
	void TAP_CDECL OnRspQryCurrency(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPICurrencyInfo *info);
	///������Ϣ֪ͨ
	void TAP_CDECL OnRspQryTradeMessage(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPITradeMessage *info);
	///������Ϣ֪ͨ
	void TAP_CDECL OnRtnTradeMessage(const ITapTrade::TapAPITradeMessage *info);
	///��ʷί�в�ѯӦ��
	void TAP_CDECL OnRspQryHisOrder(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIHisOrderQryRsp *info);
	///��ʷί�����̲�ѯӦ��
	void TAP_CDECL OnRspQryHisOrderProcess(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIHisOrderProcessQryRsp *info);
	///��ʷ�ɽ���ѯӦ��
	void TAP_CDECL OnRspQryHisMatch(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIHisMatchQryRsp *info);
	///��ʷ�ֲֲ�ѯӦ��
	void TAP_CDECL OnRspQryHisPosition(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIHisPositionQryRsp *info);
	///��ʷ�����ѯӦ��
	void TAP_CDECL OnRspQryHisDelivery(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIHisDeliveryQryRsp *info);
	///�ʽ������ѯӦ��
	void TAP_CDECL OnRspQryAccountCashAdjust(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIAccountCashAdjustQryRsp *info);
	///��ѯ�û��˵�Ӧ��
	void TAP_CDECL OnRspQryBill(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIBillQryRsp *info);
	///��ѯ�˻������Ѽ������
	void TAP_CDECL OnRspQryAccountFeeRent(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIAccountFeeRentQryRsp *info);
	///��ѯ�˻���֤��������
	void TAP_CDECL OnRspQryAccountMarginRent(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIAccountMarginRentQryRsp *info);
	///�۽���������˫�߱���Ӧ��
	void TAP_CDECL OnRspHKMarketOrderInsert(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderMarketInsertRsp *info);
	///�۽���������˫�߳���Ӧ��
	void TAP_CDECL OnRspHKMarketOrderDelete(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderMarketDeleteRsp *info);
	///�۽���ѯ��֪ͨ
	void TAP_CDECL OnHKMarketQuoteNotice(const ITapTrade::TapAPIOrderQuoteMarketNotice *info);
	///����ɾ��Ӧ��
	void TAP_CDECL OnRspOrderLocalRemove(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderLocalRemoveRsp *info);
	///����¼��Ӧ��
	void TAP_CDECL OnRspOrderLocalInput(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderLocalInputRsp *info);
	///�����޸�Ӧ��
	void TAP_CDECL OnRspOrderLocalModify(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderLocalModifyRsp *info);
	///����ת��Ӧ��
	void TAP_CDECL OnRspOrderLocalTransfer(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderLocalTransferRsp *info);
	///�ɽ�¼��Ӧ��
	virtual void TAP_CDECL OnRspFillLocalInput(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIFillLocalInputRsp *info);
	///����ɾ��Ӧ��
	void TAP_CDECL OnRspFillLocalRemove(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIFillLocalRemoveRsp *info);

};


#endif // OPTS_ESN_TRADE_V9_OUTER_H_