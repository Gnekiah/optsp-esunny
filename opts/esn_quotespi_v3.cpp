#include "esn_quote_v3.h"


QuoteSpiEsnV3::QuoteSpiEsnV3(Logger *logger) {
	this->logger = logger;
}


/**
*��¼�����ص�����
* @param err ����� 0��ʾ��¼�ɹ�������ʧ��
* @param errtext ������Ϣ
* @return 0��ʾ�ɹ�������ʧ��
*/
int QuoteSpiEsnV3::OnRspLogin(int err, const char *errtext)
{

}


/**
*�������ӳ���ص�����
* @param err �����
* @param errtext ������Ϣ
* @return 0��ʾ�ɹ�������ʧ��
*/
int QuoteSpiEsnV3::OnChannelLost(int err, const char *errtext)
{

}


/**
*��ʱ����ص�����
* @param pData ����ṹָ��
* @return 0��ʾ�ɹ�������ʧ��
*/
int QuoteSpiEsnV3::OnStkQuot(struct STKDATA *pData)
{


}


/**
*��ʷ���鷴���ص�����
* @param pHisData ��ʷ�������ݽṹָ��
* @return 0��ʾ�ɹ�������ʧ��
*/
int QuoteSpiEsnV3::OnRspHistoryQuot(struct STKHISDATA *pHisData)
{


}


/**
*��ϸ���ݷ����ص�����
* @param pTraceData ��ϸ���ݽṹָ��
* @return 0��ʾ�ɹ�������ʧ��
*/
int QuoteSpiEsnV3::OnRspTraceData(struct STKTRACEDATA *pTraceData)
{

}


/**
*�г���Ϣ�������������յ��г���Ϣ��ʾ�����Ѿ���ʼ������ˣ�
* @param pMarketInfo �г���Ϣ����ָ��
* @param bLast �Ƿ�Ϊ���һ���г���bLastΪ1��ʾ�����һ����0��ʾ���滹���г�����
* @return 0��ʾ�ɹ�������ʧ��,
*/
int QuoteSpiEsnV3::OnRspMarketInfo(struct MarketInfo *pMarketInfo, int bLast)
{

}
