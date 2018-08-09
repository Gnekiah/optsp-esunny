#ifndef ESUNNY_QUOTESPI_H_
#define ESUNNY_QUOTESPI_H_

#include "arch.h"

class QuoteSpi : public ITapQuoteAPINotify
{
private:

public:
	QuoteSpi();

	///系统登录过程回调。
	void TAP_CDECL OnRspLogin(TAPIINT32 errorCode, const TapAPIQuotLoginRspInfo *info);
	///通知用户API准备就绪。
	void TAP_CDECL OnAPIReady();
	///API和服务失去连接的回调
	void TAP_CDECL OnDisconnect(TAPIINT32 reasonCode);
	///返回所有品种信息。
	void TAP_CDECL OnRspQryCommodity(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteCommodityInfo *info);
	///返回系统中合约信息
	void TAP_CDECL OnRspQryContract(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteContractInfo *info);
	///返回订阅行情的全文。
	void TAP_CDECL OnRspSubscribeQuote(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteWhole *info);
	///退订指定合约的行情的结果回调
	void TAP_CDECL OnRspUnSubscribeQuote(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIContract *info);
	///返回订阅行情的变化内容。
	void TAP_CDECL OnRtnQuote(const TapAPIQuoteWhole *info);
	
};

#endif // ESUNNY_QUOTESPI_H_
