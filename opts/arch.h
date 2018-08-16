#ifndef OPTS_ARCH_H_
#define OPTS_ARCH_H_

#include <ctime>
#include <cstring>
#include <cstdio>


/* Define etc. */
#define MAX_NR_INSTRUMENT	50


/* Import QuoteAPI & TradeAPI libs */
/* V3 */
#ifdef _ESNAPI_V3_
#include "esnapi-v3/EsForeignApiErrCode.h"
#include "esnapi-v3/EsForeignApiStruct.h"
#include "esnapi-v3/EsForeignApiType.h"
#include "esnapi-v3/EsunnyForeignApi.h"
#include "esnapi-v3/EsunnyQuot.h"
#if defined(_WIN64) || defined(_WIN32)
#pragma comment (lib, "esnapi-v3/EsunnyQuot.lib")
#pragma comment (lib, "esnapi-v3/ForeignTradeApi.lib")
#endif 
#endif


/* V9 */
#ifdef _ESNAPI_V9_
#if defined(__linux__) && defined( __x86_64__)
#include "esnapi-v9/linux/iTapAPICommDef.h"
#include "esnapi-v9/linux/TapAPIError.h"
#include "esnapi-v9/linux/TapQuoteAPI.h"
#include "esnapi-v9/linux/TapQuoteAPIDataType.h"
#include "esnapi-v9/linux/iTapAPICommDef.h"
#include "esnapi-v9/linux/iTapAPIError.h"
#include "esnapi-v9/linux/iTapTradeAPI.h"
#include "esnapi-v9/linux/iTapTradeAPIDataType.h"

#elif defined(_WIN64)
#include "esnapi-v9/win64/TapAPICommDef.h"
#include "esnapi-v9/win64/TapAPIError.h"
#include "esnapi-v9/win64/TapQuoteAPI.h"
#include "esnapi-v9/win64/TapQuoteAPIDataType.h"
#include "esnapi-v9/win64/iTapAPICommDef.h"
#include "esnapi-v9/win64/iTapAPIError.h"
#include "esnapi-v9/win64/iTapTradeAPI.h"
#include "esnapi-v9/win64/iTapTradeAPIDataType.h"
#pragma comment (lib, "esnapi-v9/win64/TapQuoteAPI.lib")
#pragma comment (lib, "esnapi-v9/win64/iTapTradeAPI_64.lib")

#elif defined(_WIN32)
#include "esnapi-v9/win32/TapAPICommDef.h"
#include "esnapi-v9/win32/TapAPIError.h"
#include "esnapi-v9/win32/TapQuoteAPI.h"
#include "esnapi-v9/win32/TapQuoteAPIDataType.h"
#include "esnapi-v9/win32/iTapAPICommDef.h"
#include "esnapi-v9/win32/iTapAPIError.h"
#include "esnapi-v9/win32/iTapTradeAPI.h"
#include "esnapi-v9/win32/iTapTradeAPIDataType.h"
#pragma comment (lib, "esnapi-v9/win32/TapQuoteAPI.lib")
#pragma comment (lib, "esnapi-v9/win32/iTapTradeAPI.lib")
#endif
#endif


/* Define Across-platform Functions */
#if defined(__linux__) && defined( __x86_64__)
#define arch_localtime(t, m)    localtime_r(t, m)
#define arch_strcpy(dst, src, n)    strncpy(dst, src, n)
#define arch_sprintf(buf, n, fmt, v)	snprintf(buf, n, fmt, v)
// call sleep()
#include <unistd.h>
#define arch_sleep(n)	sleep(((n) < 1 ? 1 : (int) (n)))
// call _getch()
#include <termio.h>
int _getch(void);

#elif defined(_WIN64) || defined(_WIN32)
#define arch_localtime(t, m)    localtime_s(m, t)
#define arch_strcpy(dst, src, n)    strcpy_s(dst, n, src)
#define arch_sprintf(buf, n, fmt, v)	sprintf_s(buf, n, fmt, v)
// call Sleep()
#include <Windows.h>
#define arch_sleep(n)	Sleep((int) (1000 * (n)))
// call _getch()
#include <conio.h>
#endif


/* Define Logger Operations */
#define LOGINF(handle, stream)	handle->FlushInf(stream, __FUNCTION__)
#define LOGMSG(handle, stream)	handle->FlushMsg(stream, __FUNCTION__)
#define LOGWAR(handle, stream)	handle->FlushWar(stream, __FUNCTION__)
#define LOGERR(handle, stream)	handle->FlushErr(stream, __FUNCTION__)


/* Input Password without Showing */
#define ASCII_ALARM			7
#define ASCII_BACKSPACE		8
#define ASCII_ENTER			13
char *InputPasswd(char *passwd, int max);


#endif // !OPTS_ARCH_H_
