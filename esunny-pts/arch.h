#ifndef ESUNNY_ARCH_H_
#define ESUNNY_ARCH_H_

#include <ctime>
#include <cstring>
#include <cstdio>


/* Define etc. */
//#define MAX_NR_INSTRUMENT	512


/* Import QuoteAPI & TradeAPI libs */
/* Define Across-platform Functions */
#if defined(__linux__) && defined( __x86_64__)
#include "quoteapi/linux/TapAPICommDef.h"
#include "quoteapi/linux/TapAPIError.h"
#include "quoteapi/linux/TapQuoteAPI.h"
#include "quoteapi/linux/TapQuoteAPIDataType.h"

#include "tradeapi/linux/iTapAPICommDef.h"
#include "tradeapi/linux/iTapAPIError.h"
#include "tradeapi/linux/iTapTradeAPI.h"
#include "tradeapi/linux/iTapTradeAPIDataType.h"

#define arch_localtime(t, m)    localtime_r(t, m)
#define arch_strcpy(dst, src, n)    strncpy(dst, src, n)
#define arch_sprintf(buf, n, fmt, v)	snprintf(buf, n, fmt, v)
#include <unistd.h>
#define arch_sleep(n)	sleep(((n) < 1 ? 1 : (int) (n)))

#elif defined(_WIN64)
#include "quoteapi/win64/TapAPICommDef.h"
#include "quoteapi/win64/TapAPIError.h"
#include "quoteapi/win64/TapQuoteAPI.h"
#include "quoteapi/win64/TapQuoteAPIDataType.h"

#include "tradeapi/win64/iTapAPICommDef.h"
#include "tradeapi/win64/iTapAPIError.h"
#include "tradeapi/win64/iTapTradeAPI.h"
#include "tradeapi/win64/iTapTradeAPIDataType.h"

#pragma comment (lib, "quoteapi/win64/TapQuoteAPI.lib")
#pragma comment (lib, "tradeapi/win64/iTapTradeAPI_64.lib")

#define arch_localtime(t, m)    localtime_s(m, t)
#define arch_strcpy(dst, src, n)    strcpy_s(dst, n, src)
#define arch_sprintf(buf, n, fmt, v)	sprintf_s(buf, n, fmt, v)
#include <Windows.h>
#define arch_sleep(n)	Sleep((int) (1000 * (n)))

#elif defined(_WIN32)
#include "quoteapi/win32/TapAPICommDef.h"
#include "quoteapi/win32/TapAPIError.h"
#include "quoteapi/win32/TapQuoteAPI.h"
#include "quoteapi/win32/TapQuoteAPIDataType.h"

#include "tradeapi/win32/iTapAPICommDef.h"
#include "tradeapi/win32/iTapAPIError.h"
#include "tradeapi/win32/iTapTradeAPI.h"
#include "tradeapi/win32/iTapTradeAPIDataType.h"

#pragma comment (lib, "quoteapi/win32/TapQuoteAPI.lib")
#pragma comment (lib, "tradeapi/win32/iTapTradeAPI.lib")

#define arch_localtime(t, m)    localtime_s(m, t)
#define arch_strcpy(dst, src, n)    strcpy_s(dst, n, src)
#define arch_sprintf(buf, n, fmt, v)	sprintf_s(buf, n, fmt, v)
#include <Windows.h>
#define arch_sleep(n)	Sleep((int) (1000 * (n)))

#endif


/* Define Logger Operations */
#define LOGINF(handle, stream)	handle->FlushInf(stream, __FUNCTION__)
#define LOGMSG(handle, stream)	handle->FlushMsg(stream, __FUNCTION__)
#define LOGWAR(handle, stream)	handle->FlushWar(stream, __FUNCTION__)
#define LOGERR(handle, stream)	handle->FlushErr(stream, __FUNCTION__)



#endif // !ESUNNY_ARCH_H_
