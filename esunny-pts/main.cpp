#include <sstream>

#include "arch.h"
#include "logger.h"
#include "datacore.h"
#include "quotespi.h"

using std::stringstream;
using ITapTrade::ITapTradeAPI;

#define DEFAULT_QUOTE_USERNAME	("ES")
#define DEFAULT_QUOTE_PASSWORD	("123456")
#define DEFAULT_QUOTE_IP		("123.161.206.213")
#define DEFAULT_QUOTE_PORT		(7171)
#define DEFAULT_TRADE_USERNAME	("Q102681074")
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
	TAPIINT32 iResult = TAPIERROR_SUCCEED;
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
	QuoteSpi *quoteSpi = new QuoteSpi(logger);
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
	// DO Login
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


	while (!quoteSpi->ready) 
		arch_sleep(1);
	
	arch_sleep(2);
	TAPIUINT32 sessionID = 0;
	quoteApi->QryCommodity(&sessionID);

	arch_sleep(2);
	TapAPICommodity commodity = { 0 };
	arch_strcpy(commodity.CommodityNo, "HSI", sizeof(TAPISTR_10));
	commodity.CommodityType = 'F';
	arch_strcpy(commodity.ExchangeNo, "HKEX", sizeof(TAPISTR_10));
	quoteApi->QryContract(&sessionID, &commodity);

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
		


	
	/* Create and Init TradeAPI & TradeSPI */
	ITapTradeAPI *tradeApi = NULL;

	while (true) {
		;
	}

	return 0;
}