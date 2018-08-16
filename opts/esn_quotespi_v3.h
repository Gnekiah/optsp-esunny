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
	*登录反馈回调函数
	* @param err 错误号 0表示登录成功，否则失败
	* @param errtext 错误信息
	* @return 0表示成功，否则失败
	*/
	virtual int __cdecl OnRspLogin(int err, const char *errtext);
	/**
	*物理连接出错回调函数
	* @param err 错误号
	* @param errtext 错误信息
	* @return 0表示成功，否则失败
	*/
	virtual int __cdecl OnChannelLost(int err, const char *errtext);
	/**
	*即时行情回调函数
	* @param pData 行情结构指针
	* @return 0表示成功，否则失败
	*/
	virtual int __cdecl OnStkQuot(struct STKDATA *pData);
	/**
	*历史行情反馈回调函数
	* @param pHisData 历史行情数据结构指针
	* @return 0表示成功，否则失败
	*/
	virtual int __cdecl OnRspHistoryQuot(struct STKHISDATA *pHisData);
	/**
	*明细数据反馈回调函数
	* @param pTraceData 明细数据结构指针
	* @return 0表示成功，否则失败
	*/
	virtual int __cdecl OnRspTraceData(struct STKTRACEDATA *pTraceData);
	/**
	*市场信息包反馈函数，收到市场信息表示数据已经初始化完成了！
	* @param pMarketInfo 市场信息数据指针
	* @param bLast 是否为最后一个市场，bLast为1表示是最后一个，0表示后面还有市场数据
	* @return 0表示成功，否则失败,
	*/
	virtual int __cdecl OnRspMarketInfo(struct MarketInfo *pMarketInfo, int bLast);
};




#endif // OPTS_ESN_QUOTE_V3_H_