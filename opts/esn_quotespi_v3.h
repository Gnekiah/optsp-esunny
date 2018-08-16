#ifndef OPTS_ESN_QUOTE_V3_H_
#define OPTS_ESN_QUOTE_V3_H_
#define _ESNAPI_V3_

#include "arch.h"
#include "logger.h"


class QuoteSpiEsnV3 : public IEsunnyQuotNotify
{

private:
	Logger *logger = NULL;

public:
	QuoteSpiEsnV3(Logger *logger);

public:
	/**
	*��¼�����ص�����
	* @param err ����� 0��ʾ��¼�ɹ�������ʧ��
	* @param errtext ������Ϣ
	* @return 0��ʾ�ɹ�������ʧ��
	*/
	virtual int __cdecl OnRspLogin(int err, const char *errtext);
	/**
	*�������ӳ���ص�����
	* @param err �����
	* @param errtext ������Ϣ
	* @return 0��ʾ�ɹ�������ʧ��
	*/
	virtual int __cdecl OnChannelLost(int err, const char *errtext);
	/**
	*��ʱ����ص�����
	* @param pData ����ṹָ��
	* @return 0��ʾ�ɹ�������ʧ��
	*/
	virtual int __cdecl OnStkQuot(struct STKDATA *pData);
	/**
	*��ʷ���鷴���ص�����
	* @param pHisData ��ʷ�������ݽṹָ��
	* @return 0��ʾ�ɹ�������ʧ��
	*/
	virtual int __cdecl OnRspHistoryQuot(struct STKHISDATA *pHisData);
	/**
	*��ϸ���ݷ����ص�����
	* @param pTraceData ��ϸ���ݽṹָ��
	* @return 0��ʾ�ɹ�������ʧ��
	*/
	virtual int __cdecl OnRspTraceData(struct STKTRACEDATA *pTraceData);
	/**
	*�г���Ϣ�������������յ��г���Ϣ��ʾ�����Ѿ���ʼ������ˣ�
	* @param pMarketInfo �г���Ϣ����ָ��
	* @param bLast �Ƿ�Ϊ���һ���г���bLastΪ1��ʾ�����һ����0��ʾ���滹���г�����
	* @return 0��ʾ�ɹ�������ʧ��,
	*/
	virtual int __cdecl OnRspMarketInfo(struct MarketInfo *pMarketInfo, int bLast);
};




#endif // OPTS_ESN_QUOTE_V3_H_