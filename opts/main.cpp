#include <sstream>

#include "arch.h"
#include "logger.h"
#include "datacore.h"
#include "quotespi.h"
#include "tradespi.h"
#include "st_sola.h"
#include "trader.h"

using std::stringstream;
using ITapTrade::ITapTradeAPI;

#define DEFAULT_QUOTE_USERNAME	("ES")
#define DEFAULT_QUOTE_PASSWORD	("123456")
#define DEFAULT_QUOTE_IP		("123.161.206.213")
#define DEFAULT_QUOTE_PORT		(7171)
#define DEFAULT_TRADE_USERNAME	("Q102681074")
// Q1511540146
// 115317
#define DEFAULT_TRADE_PASSWORD	("981966")
#define DEFAULT_TRADE_IP		("123.161.206.213")
#define DEFAULT_TRADE_PORT		(8383)
#define DEFAULT_PROGRAM_NAME	("Demo_Test")
#define DEFAULT_AUTHCODE ("67EA896065459BECDFDB924B29CB7DF1946CED32E26C1EAC946CED\
32E26C1EAC946CED32E26C1EAC946CED32E26C1EAC5211AF9FEE541DDE41BCBAB68D525B0D111A088\
4D847D57163FF7F329FA574E7946CED32E26C1EAC946CED32E26C1EAC733827B0CE853869ABD9B8F1\
70E14F8847D3EA0BF4E191F5D97B3DFE4CCB1F01842DD2B3EA2F4B20CAD19B8347719B7E20EA1FA7A\
3D1BFEFF22290F4B5C43E6C520ED5A40EC1D50ACDF342F46A92CCF87AEE6D73542C42EC17818349C7\
DEDAB0E4DB16977714F873D505029E27B3D57EB92D5BEDA0A710197EB67F94BB1892B30F58A3F211D\
9C3B3839BE2D73FD08DD776B9188654853DDA57675EBB7D6FBBFC")

const char* ESUNNY_PTS_VERSION = "Esunny-PTS Version: 0.1.0";
const char* ESUNNY_CONFIG_PATH = "esunny-pts.conf";

int main() 
{
	/* Init Datacore & Logger */
	Datacore *datacore = new Datacore(ESUNNY_CONFIG_PATH);
	Logger *logger = new Logger(datacore);
	
	/* Logging Version Information */
	stringstream log;
	log << ESUNNY_PTS_VERSION << ", Trading System Running....";
	LOGINF(logger, &log);
	log << "Tap Quote API Version=" << GetTapQuoteAPIVersion();
	LOGINF(logger, &log);
	log << "Tap Trade API Version=" << GetITapTradeAPIVersion();
	LOGINF(logger, &log);

	/* Create and Init QuoteAPI & QuoteSPI */
	TAPIINT32 iResult = 0;
	TAPIUINT32 sessionID = 0;
	// Create QuoteAPI Instance
	TapAPIApplicationInfo appInfo = { 0 };
	arch_strcpy(appInfo.AuthCode, DEFAULT_AUTHCODE, sizeof(TAPIAUTHCODE));
	arch_strcpy(appInfo.KeyOperationLogPath, datacore->quoteLogpath.c_str(), sizeof(TAPISTR_300));
	ITapQuoteAPI *quoteApi = CreateTapQuoteAPI(&appInfo, iResult);
	if (!quoteApi) {
		log << "创建 quote API 实例失败，ErrorCode=" << iResult;
		LOGERR(logger, &log);
		return iResult;
	}
	// Create QuoteSPI Instance
	QuoteSpi *quoteSpi = new QuoteSpi(logger, datacore);
	quoteApi->SetAPINotify(quoteSpi);
	// Set Quote Data Path
	iResult = SetTapQuoteAPIDataPath(datacore->quotepath.c_str());
	if (iResult) {
		log << "设置 quote 相关保存路径失败，ErrorCode=" << iResult;
		LOGERR(logger, &log);
		return iResult;
	}
	// Set Quote Log Level
	iResult = SetTapQuoteAPILogLevel(datacore->quoteLogLevel);
	if (iResult) {
		log << "设置 quote 日志记录等级失败，ErrorCode=" << iResult;
		LOGERR(logger, &log);
		return iResult;
	}
	// Set Host FrontAddr
	iResult = quoteApi->SetHostAddress(DEFAULT_QUOTE_IP, DEFAULT_QUOTE_PORT);
	if (iResult) {
		log << "设置 quote 前置服务器地址失败，ErrorCode=" << iResult;
		LOGERR(logger, &log);
		return iResult;
	}
	// Do Login
	TapAPIQuoteLoginAuth loginAuth = { 0 };
	arch_strcpy(loginAuth.UserNo, DEFAULT_QUOTE_USERNAME, sizeof(TAPISTR_20));
	arch_strcpy(loginAuth.Password, DEFAULT_QUOTE_PASSWORD, sizeof(TAPISTR_20));
	loginAuth.ISModifyPassword = APIYNFLAG_NO;
	loginAuth.ISDDA = APIYNFLAG_NO;
	iResult = quoteApi->Login(&loginAuth);
	if (iResult) {
		log << "登录 quote 认证失败，ErrorCode=" << iResult;
		LOGERR(logger, &log);
		return iResult;
	}
	// Waiting for QuoteAPI Status to be Ready
	while (!quoteSpi->ready) 
		arch_sleep(1);
	// Query All of Commodities
	arch_sleep(2);
	iResult = quoteApi->QryCommodity(&sessionID);
	if (iResult) {
		log << "查询所有品种的请求执行失败，ErrorCode=" << iResult;
		LOGERR(logger, &log);
		return iResult;
	}
	// Query Information of A Detail Contract
	arch_sleep(2);
	TapAPICommodity commodity = { 0 };
	arch_strcpy(commodity.CommodityNo, "HSI", sizeof(TAPISTR_10));
	commodity.CommodityType = 'F';
	arch_strcpy(commodity.ExchangeNo, "HKEX", sizeof(TAPISTR_10));
	iResult = quoteApi->QryContract(&sessionID, &commodity);
	if (iResult) {
		log << "查询指定合约品种详细信息的请求执行失败，ErrorCode=" << iResult;
		LOGERR(logger, &log);
		return iResult;
	}
	// Do Subscribe
	arch_sleep(2);
	TapAPIContract contract = { 0 };
	memset(&contract, 0, sizeof(TapAPIContract));
	contract.Commodity.CommodityType = TAPI_COMMODITY_TYPE_FUTURES;
	arch_strcpy(contract.Commodity.ExchangeNo, "HKEX", sizeof(TAPISTR_10));
	arch_strcpy(contract.Commodity.CommodityNo, "HSI", sizeof(TAPISTR_10));
	arch_strcpy(contract.ContractNo1, "1808", sizeof(TAPISTR_10));
	contract.CallOrPutFlag1 = TAPI_CALLPUT_FLAG_NONE;
	contract.CallOrPutFlag2 = TAPI_CALLPUT_FLAG_NONE;
	iResult = quoteApi->SubscribeQuote(&sessionID, &contract);
	if (iResult) {
		log << "订阅指定合约行情信息的请求执行失败，ErrorCode=" << iResult;
		LOGERR(logger, &log);
		return iResult;
	}
	
	/* Create and Init TradeAPI & TradeSPI */
	// Create TradeAPI Instance
	ITapTrade::TapAPIApplicationInfo iappInfo = { 0 };
	arch_strcpy(iappInfo.AuthCode, DEFAULT_AUTHCODE, sizeof(ITapTrade::TAPIAUTHCODE));
	arch_strcpy(iappInfo.KeyOperationLogPath, datacore->tradeLogpath.c_str(), sizeof(ITapTrade::TAPISTR_300));
	ITapTrade::ITapTradeAPI *tradeApi = CreateITapTradeAPI(&iappInfo, iResult);
	if (!tradeApi) {
		log << "创建 trade API 实例失败，ErrorCode=" << iResult;
		LOGERR(logger, &log);
		return iResult;
	}
	// Create TradeSPI Instance
	TradeSpi *tradeSpi = new TradeSpi(logger);
	tradeApi->SetAPINotify(tradeSpi);
	// Set Trade Data Path
	iResult = SetITapTradeAPIDataPath(datacore->tradepath.c_str());
	if (iResult) {
		log << "设置 trade 相关保存路径失败，ErrorCode=" << iResult;
		LOGERR(logger, &log);
		return iResult;
	}
	// Set Trade Log Level
	iResult = SetITapTradeAPILogLevel(datacore->tradeLogLevel);
	if (iResult) {
		log << "设置 trade 日志记录等级失败，ErrorCode=" << iResult;
		LOGERR(logger, &log);
		return iResult;
	}
	// Set Host FrontAddr
	iResult = tradeApi->SetHostAddress(DEFAULT_TRADE_IP, DEFAULT_TRADE_PORT);
	if (iResult) {
		log << "设置 trade 前置服务器地址失败，ErrorCode=" << iResult;
		LOGERR(logger, &log);
		return iResult;
	}
	// Do Login
	ITapTrade::TapAPITradeLoginAuth iloginAuth = { 0 };
	arch_strcpy(iloginAuth.UserNo, DEFAULT_TRADE_USERNAME, sizeof(ITapTrade::TAPISTR_20));
	arch_strcpy(iloginAuth.Password, DEFAULT_TRADE_PASSWORD, sizeof(ITapTrade::TAPISTR_20));
	iloginAuth.ISModifyPassword = ITapTrade::APIYNFLAG_NO;
	iResult = tradeApi->Login(&iloginAuth);
	if (iResult) {
		log << "登录 trade 认证失败，ErrorCode=" << iResult;
		LOGERR(logger, &log);
		return iResult;
	}
	// Waiting for TradeAPI Status to be Ready
	while (!tradeSpi->ready)
		arch_sleep(1);

	/* Create and Init Trader */
	Trader *trader = new Trader(tradeApi, logger, datacore);

	/* Create and Init ST_Sola (Strategy) */
	ST_Sola *stsola = new ST_Sola(trader, logger, datacore);
	stsola->Join();

	return 0;
}