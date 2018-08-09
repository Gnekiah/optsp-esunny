#ifndef ESUNNY_QUOTESPI_H_
#define ESUNNY_QUOTESPI_H_

#include "arch.h"

class QuoteSpi : public ITapQuoteAPINotify
{
private:

public:
	QuoteSpi();

	///ϵͳ��¼���̻ص���
	void TAP_CDECL OnRspLogin(TAPIINT32 errorCode, const TapAPIQuotLoginRspInfo *info);
	///֪ͨ�û�API׼��������
	void TAP_CDECL OnAPIReady();
	///API�ͷ���ʧȥ���ӵĻص�
	void TAP_CDECL OnDisconnect(TAPIINT32 reasonCode);
	///��������Ʒ����Ϣ��
	void TAP_CDECL OnRspQryCommodity(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteCommodityInfo *info);
	///����ϵͳ�к�Լ��Ϣ
	void TAP_CDECL OnRspQryContract(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteContractInfo *info);
	///���ض��������ȫ�ġ�
	void TAP_CDECL OnRspSubscribeQuote(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteWhole *info);
	///�˶�ָ����Լ������Ľ���ص�
	void TAP_CDECL OnRspUnSubscribeQuote(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIContract *info);
	///���ض�������ı仯���ݡ�
	void TAP_CDECL OnRtnQuote(const TapAPIQuoteWhole *info);
	
};

#endif // ESUNNY_QUOTESPI_H_
