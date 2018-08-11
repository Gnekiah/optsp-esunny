#include "tradespi.h"

TradeSpi::TradeSpi(Logger *logger)
{
	this->logger = logger;
	ready = false;
}


/**
* @brief ���ӳɹ��ص�֪ͨ
* @ingroup G_T_Login
*/
void TAP_CDECL TradeSpi::OnConnect()
{

}


/**
* @brief	ϵͳ��¼���̻ص���
* @details	�˺���ΪLogin()��¼�����Ļص�������Login()�ɹ���������·���ӣ�Ȼ��API������������͵�¼��֤��Ϣ��
*			��¼�ڼ�����ݷ�������͵�¼�Ļ�����Ϣ���ݵ��˻ص������С�
* @param[in] errorCode ���ش�����,0��ʾ�ɹ���
* @param[in] loginRspInfo ��½Ӧ����Ϣ�����errorCode!=0����loginRspInfo=NULL��
* @attention	�ûص����سɹ���˵���û���¼�ɹ������ǲ�����API׼����ϡ�
* @ingroup G_T_Login
*/
void TAP_CDECL TradeSpi::OnRspLogin(ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPITradeLoginRspInfo *loginRspInfo)
{

}


/**
* @brief	������֤��ϵ��ʽ֪ͨ��
* @details	��¼��ɺ������Ҫ������֤��9.2.7��̨�������յ���ϵ��ʽ��֪ͨ������ѡ��֪ͨ��Ϣ��һ����ϵ��ʽ��������ߵ绰��
*			�����Ͷ�����֤��Ȩ�루RequestVertificateCode����
* @param[in] errorCode ���ش�����,0��ʾ�ɹ�������˻�û�а󶨶�����֤��ϵ��ʽ���򷵻�10016����
* @param[in] isLast,��ʶ�Ƿ������һ����ϵ��Ϣ��
* @param[in]  ��֤��ʽ��Ϣ�����errorCode!=0����ContactInfoΪ�ա�
* @attention	�ûص����سɹ���˵����Ҫ������֤��������Ҫѡ��һ����ϵ��ʽȻ�����RequestVertificateCode��
* @ingroup G_T_Login
*/
void TAP_CDECL TradeSpi::OnRtnContactInfo(ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TAPISTR_40 ContactInfo)
{

}


/**
* @brief	�����Ͷ�����֤��Ӧ��
* @details	�����ȡ������֤��Ȩ�룬��̨�����ʼ����߶��ţ�������Ӧ�𣬰�����������Լ���֤����Ч�ڡ�
*
* @param[in] sessionID ���������֤��ỰID��
* @param[in]  errorCode ���û�а���ϵ������10016����.
* @param[in]  rsp������֤����Ч�ڣ����뷵�أ��ڶ�����֤��Ч���ڣ������ظ����ö�����֤�룬���ǲ������������������֤�롣
* @attention	�ûص����سɹ���˵����Ҫ������֤��������Ҫѡ��һ����ϵ��ʽȻ�����RequestVertificateCode��
* @ingroup G_T_Login
*/
void TAP_CDECL TradeSpi::OnRspRequestVertificateCode(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIRequestVertificateCodeRsp *rsp)
{

}


/**
* @brief	API�������ѻص�
* @details	�˺���ΪLogin()��¼�ɹ�������������뵱ǰ����С��30�죬����лص����ѡ�
* @param[in] date ����API��Ȩ�����ա�
* @param[in] days ���ػ��м�����Ȩ���ڡ�
* @attention	�ú����ص�����˵����Ȩ��һ����֮�ڵ��ڡ����򲻲����ûص���
* @ingroup G_T_Login
*/
void TAP_CDECL TradeSpi::OnExpriationDate(ITapTrade::TAPIDATE date, int days)
{

}


/**
* @brief	֪ͨ�û�API׼��������
* @details	ֻ���û��ص��յ��˾���֪ͨʱ���ܽ��к����ĸ����������ݲ�ѯ������\n
*			�˻ص�������API�ܷ����������ı�־��
* @attention ������ſ��Խ��к�����������
* @ingroup G_T_Login
*/
void TAP_CDECL TradeSpi::OnAPIReady()
{
	stringstream log;
	ready = true;
	log << "Trade API ׼������";
	LOGINF(logger, &log);
}


/**
* @brief	API�ͷ���ʧȥ���ӵĻص�
* @details	��APIʹ�ù������������߱��������������ʧȥ���Ӻ󶼻ᴥ���˻ص�֪ͨ�û���������������Ѿ��Ͽ���
* @param[in] reasonCode �Ͽ�ԭ����롣
* @ingroup G_T_Disconnect
*/
void TAP_CDECL TradeSpi::OnDisconnect(ITapTrade::TAPIINT32 reasonCode)
{

}


/**
* @brief ֪ͨ�û������޸Ľ��
* @param[in] sessionID �޸�����ĻỰID,��ChangePassword���صĻỰID��Ӧ��
* @param[in] errorCode ���ش����룬0��ʾ�ɹ���
* @ingroup G_T_UserInfo
*/
void TAP_CDECL TradeSpi::OnRspChangePassword(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode)
{

}


/**
* @brief ��֤�˻����뷴��
* @param[in] sessionID �޸�����ĻỰID,��AuthPassword���صĻỰID��Ӧ��
* @param[in] errorCode ���ش����룬0��ʾ�ɹ���
* @ingroup G_T_UserInfo
*/
void TAP_CDECL TradeSpi::OnRspAuthPassword(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode)
{

}


/**
* @brief �����û�Ԥ����Ϣ����
* @param[in] sessionID �����û�Ԥ����Ϣ�ĻỰID
* @param[in] errorCode ���ش����룬0��ʾ�ɹ���
* @param[in] info ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
* @note �ýӿ���δʵ��
* @ingroup G_T_UserInfo
*/
void TAP_CDECL TradeSpi::OnRspSetReservedInfo(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TAPISTR_50 info)
{

}


/**
* @brief	�����û���Ϣ
* @details	�˻ص��ӿ����û����ز�ѯ���ʽ��˺ŵ���ϸ��Ϣ���û��б�Ҫ���õ����˺ű�ű���������Ȼ���ں����ĺ���������ʹ�á�
* @param[in] sessionID ����ĻỰID��
* @param[in] errorCode �����롣0 ��ʾ�ɹ���
* @param[in] isLast ��ʾ�Ƿ������һ�����ݣ�
* @param[in] info ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
* @ingroup G_T_AccountInfo
*/
void TAP_CDECL TradeSpi::OnRspQryAccount(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIUINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIAccountInfo *info)
{

}


/**
* @brief �����ʽ��˻����ʽ���Ϣ
* @param[in] sessionID ����ĻỰID��
* @param[in] errorCode �����롣0 ��ʾ�ɹ���
* @param[in] isLast 	��ʾ�Ƿ������һ�����ݣ�
* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
* @ingroup G_T_AccountDetails
*/
void TAP_CDECL TradeSpi::OnRspQryFund(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIFundData *info)
{

}


/**
* @brief	�û��ʽ�仯֪ͨ
* @details	�û���ί�гɽ���������ʽ����ݵı仯�������Ҫ���û�ʵʱ������
* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
* @note �������ע�������ݣ������趨Loginʱ��NoticeIgnoreFlag�����Ρ�
* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
* @ingroup G_T_AccountDetails
*/
void TAP_CDECL TradeSpi::OnRtnFund(const ITapTrade::TapAPIFundData *info)
{

}


/**
* @brief ����ϵͳ�еĽ�������Ϣ
* @param[in] sessionID ����ĻỰID��
* @param[in] errorCode �����롣0 ��ʾ�ɹ���
* @param[in] isLast 	��ʾ�Ƿ������һ�����ݣ�
* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
* @ingroup G_T_TradeSystem
*/
void TAP_CDECL TradeSpi::OnRspQryExchange(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIExchangeInfo *info)
{

}


/**
* @brief	����ϵͳ��Ʒ����Ϣ
* @details	�˻ص��ӿ��������û����صõ�������Ʒ����Ϣ��
* @param[in] sessionID ����ĻỰID����GetAllCommodities()�������ض�Ӧ��
* @param[in] errorCode �����롣0 ��ʾ�ɹ���
* @param[in] isLast 	��ʾ�Ƿ������һ�����ݣ�
* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
* @ingroup G_T_Commodity
*/
void TAP_CDECL TradeSpi::OnRspQryCommodity(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPICommodityInfo *info)
{

}


/**
* @brief ����ϵͳ�к�Լ��Ϣ
* @param[in] sessionID ����ĻỰID��
* @param[in] errorCode �����롣0 ��ʾ�ɹ���
* @param[in] isLast 	��ʾ�Ƿ������һ�����ݣ�
* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
* @ingroup G_T_Contract
*/
void TAP_CDECL TradeSpi::OnRspQryContract(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPITradeContractInfo *info)
{

}


/**
* @brief	����������Լ��Ϣ
* @details	���û������µĺ�Լ����Ҫ���������ڽ���ʱ����з�����������º�Լʱ�����û����������Լ����Ϣ��
* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
* @ingroup G_T_Contract
*/
void TAP_CDECL TradeSpi::OnRtnContract(const ITapTrade::TapAPITradeContractInfo *info)
{

}


/**
* @brief	��������Ӧ��
* @details	�µ����������ĵ�Ӧ���µ������д�Ӧ��ص�������µ�����ṹ��û����д��Լ�����ʽ��˺ţ�������ش���š�
* �������ĵ�������Ӧ���OnRtnOrder���ɹ�������OnRtnOrder�ص���
* sessionID��ʶ�����Ӧ��sessionID���Ա�ȷ���ñ�Ӧ���Ӧ������
*
* @param[in] sessionID ����ĻỰID��
* @param[in] errorCode �����롣0 ��ʾ�ɹ���
* @param[in] info ����Ӧ��������ͣ����������������ͺͶ�����Ϣָ�롣
* ������Ϣָ�벿������¿���Ϊ�գ����Ϊ�գ�����ͨ��SessiuonID�ҵ���Ӧ�����ȡ�������͡�
* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
* @ingroup G_T_TradeActions
*/
void TAP_CDECL TradeSpi::OnRspOrderAction(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderActionRsp *info)
{

}

/**
* @brief ������ί�С����µĻ��������ط��µ����͹����ġ�
* @details	���������յ��ͻ��µ�ί�����ݺ�ͻᱣ�������ȴ�������ͬʱ���û�����һ��
*			��ί����Ϣ˵����������ȷ�������û������󣬷��ص���Ϣ�а�����ȫ����ί����Ϣ��
*			ͬʱ��һ��������ʾ��ί�е�ί�кš�
* @param[in] info ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
* @note �������ע�������ݣ������趨Loginʱ��NoticeIgnoreFlag�����Ρ�
* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
* @ingroup G_T_TradeActions
*/
void TAP_CDECL TradeSpi::OnRtnOrder(const ITapTrade::TapAPIOrderInfoNotice *info)
{

}


/**
* @brief	���ز�ѯ��ί����Ϣ
* @details	�����û���ѯ��ί�еľ�����Ϣ��
* @param[in] sessionID ����ĻỰID��
* @param[in] errorCode �����롣0 ��ʾ�ɹ���
* @param[in] isLast ��ʾ�Ƿ������һ�����ݣ�
* @param[in] info ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
* @ingroup G_T_TradeInfo
*/
void TAP_CDECL TradeSpi::OnRspQryOrder(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIOrderInfo *info)
{

}


/**
* @brief ���ز�ѯ��ί�б仯������Ϣ
* @param[in] sessionID ����ĻỰID��
* @param[in] errorCode �����룬��errorCode==0ʱ��infoָ�򷵻ص�ί�б仯���̽ṹ�壬��ȻΪNULL��
* @param[in] isLast ��ʾ�Ƿ������һ�����ݣ�
* @param[in] info ���ص�ί�б仯����ָ�롣
* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
* @ingroup G_T_TradeInfo
*/
void TAP_CDECL TradeSpi::OnRspQryOrderProcess(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIOrderInfo *info)
{

}


/**
* @brief ���ز�ѯ�ĳɽ���Ϣ
* @param[in] sessionID ����ĻỰID��
* @param[in] errorCode �����롣0 ��ʾ�ɹ���
* @param[in] isLast 	��ʾ�Ƿ������һ�����ݣ�
* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
* @ingroup G_T_TradeInfo
*/
void TAP_CDECL TradeSpi::OnRspQryFill(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIFillInfo *info)
{

}


/**
* @brief	�������ĳɽ���Ϣ
* @details	�û���ί�гɽ������û����ͳɽ���Ϣ��
* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
* @note �������ע�������ݣ������趨Loginʱ��NoticeIgnoreFlag�����Ρ�
* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
* @ingroup G_T_TradeActions
*/
void TAP_CDECL TradeSpi::OnRtnFill(const ITapTrade::TapAPIFillInfo *info)
{

}


/**
* @brief ���ز�ѯ�ĳֲ�
* @param[in] sessionID ����ĻỰID��
* @param[in] errorCode �����롣0 ��ʾ�ɹ���
* @param[in] isLast 	��ʾ�Ƿ������һ�����ݣ�
* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
* @ingroup G_T_TradeInfo
*/
void TAP_CDECL TradeSpi::OnRspQryPosition(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIPositionInfo *info)
{

}


/**
* @brief �ֱֲ仯����֪ͨ
* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
* @note �������ע�������ݣ������趨Loginʱ��NoticeIgnoreFlag�����Ρ�
* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
* @ingroup G_T_TradeActions
*/
void TAP_CDECL TradeSpi::OnRtnPosition(const ITapTrade::TapAPIPositionInfo *info)
{

}


/**
* @brief �ֲ�ӯ��֪ͨ
* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
* @note �������ע�������ݣ������趨Loginʱ��NoticeIgnoreFlag�����Ρ�
* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
* @ingroup G_T_TradeActions
*/
void TAP_CDECL TradeSpi::OnRtnPositionProfit(const ITapTrade::TapAPIPositionProfitNotice *info)
{

}


/**
* @brief ����ϵͳ�еı�����Ϣ
* @param[in] sessionID ����ĻỰID��
* @param[in] errorCode �����롣0 ��ʾ�ɹ���
* @param[in] isLast 	��ʾ�Ƿ������һ�����ݣ�
* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
* @ingroup G_T_TradeSystem
*/
void TAP_CDECL TradeSpi::OnRspQryCurrency(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPICurrencyInfo *info)
{

}


/**
* @brief	������Ϣ֪ͨ
* @details	���ز�ѯ���û��ʽ�״̬��Ϣ����Ϣ˵�����û����ʽ�״̬���û���Ҫ��ϸ�鿴��Щ��Ϣ��
* @param[in] sessionID ����ĻỰID��
* @param[in] errorCode �����롣0 ��ʾ�ɹ���
* @param[in] isLast 	��ʾ�Ƿ������һ�����ݣ�
* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
* @ingroup G_T_AccountDetails
*/
void TAP_CDECL TradeSpi::OnRspQryTradeMessage(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPITradeMessage *info)
{

}


/**
* @brief	������Ϣ֪ͨ
* @details	�û��ڽ��׹����п�����Ϊ�ʽ𡢳ֲ֡�ƽ�ֵ�״̬�䶯ʹ�˻�����ĳЩΣ��״̬������ĳЩ��Ҫ����Ϣ��Ҫ���û�֪ͨ��
* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
* @ingroup G_T_AccountDetails
*/
void TAP_CDECL TradeSpi::OnRtnTradeMessage(const ITapTrade::TapAPITradeMessage *info)
{

}


/**
* @brief ��ʷί�в�ѯӦ��
* @param[in] sessionID ����ĻỰID��
* @param[in] errorCode �����롣0 ��ʾ�ɹ���
* @param[in] isLast 	��ʾ�Ƿ������һ������
* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
* @ingroup G_T_HisInfo
*/
void TAP_CDECL TradeSpi::OnRspQryHisOrder(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIHisOrderQryRsp *info)
{

}


/**
* @brief ��ʷί�����̲�ѯӦ��
* @param[in] sessionID ����ĻỰID��
* @param[in] errorCode �����롣0 ��ʾ�ɹ���
* @param[in] isLast 	��ʾ�Ƿ������һ������
* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
* @ingroup G_T_HisInfo
*/
void TAP_CDECL TradeSpi::OnRspQryHisOrderProcess(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIHisOrderProcessQryRsp *info)
{

}


/**
* @brief ��ʷ�ɽ���ѯӦ��
* @param[in] sessionID ����ĻỰID��
* @param[in] errorCode �����롣0 ��ʾ�ɹ���
* @param[in] isLast 	��ʾ�Ƿ������һ������
* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
* @ingroup G_T_HisInfo
*/
void TAP_CDECL TradeSpi::OnRspQryHisMatch(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIHisMatchQryRsp *info)
{

}


/**
* @brief ��ʷ�ֲֲ�ѯӦ��
* @param[in] sessionID ����ĻỰID��
* @param[in] errorCode �����롣0 ��ʾ�ɹ���
* @param[in] isLast 	��ʾ�Ƿ������һ������
* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
* @ingroup G_T_HisInfo
*/
void TAP_CDECL TradeSpi::OnRspQryHisPosition(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIHisPositionQryRsp *info)
{

}


/**
* @brief ��ʷ�����ѯӦ��
* @param[in] sessionID ����ĻỰID��
* @param[in] errorCode �����롣0 ��ʾ�ɹ���
* @param[in] isLast 	��ʾ�Ƿ������һ������
* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
* @ingroup G_T_HisInfo
*/
void TAP_CDECL TradeSpi::OnRspQryHisDelivery(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIHisDeliveryQryRsp *info)
{

}


/**
* @brief �ʽ������ѯӦ��
* @param[in] sessionID ����ĻỰID��
* @param[in] errorCode �����롣0 ��ʾ�ɹ���
* @param[in] isLast 	��ʾ�Ƿ������һ������
* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
* @ingroup G_T_HisInfo
*/
void TAP_CDECL TradeSpi::OnRspQryAccountCashAdjust(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIAccountCashAdjustQryRsp *info)
{

}


/**
* @brief ��ѯ�û��˵�Ӧ�� Add:2013.12.11
* @param[in] sessionID ����ĻỰID��
* @param[in] errorCode �����롣0 ��ʾ�ɹ���
* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
* @ingroup G_T_Bill
*/
void TAP_CDECL TradeSpi::OnRspQryBill(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIBillQryRsp *info)
{

}


/**
* @brief ��ѯ�˻������Ѽ������ Add:2017.01.14
* @param[in] sessionID ����ĻỰID��
* @param[in] errorCode �����롣0 ��ʾ�ɹ���
* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
* @ingroup G_T_Rent
*/
void TAP_CDECL TradeSpi::OnRspQryAccountFeeRent(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIAccountFeeRentQryRsp *info)
{

}


/**
* @brief ��ѯ�˻���֤�������� Add:2017.01.14
* @param[in] sessionID ����ĻỰID��
* @param[in] errorCode �����롣0 ��ʾ�ɹ���
* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
* @ingroup G_T_Rent
*/
void TAP_CDECL TradeSpi::OnRspQryAccountMarginRent(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, ITapTrade::TAPIYNFLAG isLast, const ITapTrade::TapAPIAccountMarginRentQryRsp *info)
{

}


/**
* @brief �۽���������˫�߱���Ӧ�� Add:2017.08.29
* @param[in] sessionID ����ĻỰID��
* @param[in] errorCode �����롣0 ��ʾ�ɹ���
* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
* @ingroup G_T_HKMarket
*/
void TAP_CDECL TradeSpi::OnRspHKMarketOrderInsert(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderMarketInsertRsp *info)
{
	
}


/**
* @brief �۽���������˫�߳���Ӧ�� Add:2017.08.29
* @param[in] sessionID ����ĻỰID��
* @param[in] errorCode �����롣0 ��ʾ�ɹ���
* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
* @ingroup G_T_HKMarket
*/
void TAP_CDECL TradeSpi::OnRspHKMarketOrderDelete(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderMarketDeleteRsp *info)
{

}


/**
* @brief �۽���ѯ��֪ͨ Add:2017.08.29
* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
* @ingroup G_T_HKMarket
*/
void TAP_CDECL TradeSpi::OnHKMarketQuoteNotice(const ITapTrade::TapAPIOrderQuoteMarketNotice *info)
{

}


/**
* @brief ����ɾ��Ӧ�� Add:2017.12.05
* @param[in] sessionID ����ĻỰID��
* @param[in] errorCode �����롣0 ��ʾ�ɹ���
* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
* @ingroup G_T_LocalAction
*/
void TAP_CDECL TradeSpi::OnRspOrderLocalRemove(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderLocalRemoveRsp *info)
{

}


/**
* @brief ����¼��Ӧ�� Add:2017.12.05
* @param[in] sessionID ����ĻỰID��
* @param[in] errorCode �����롣0 ��ʾ�ɹ���
* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
* @ingroup G_T_LocalAction
*/
void TAP_CDECL TradeSpi::OnRspOrderLocalInput(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderLocalInputRsp *info)
{

}


/**
* @brief �����޸�Ӧ�� Add:2017.12.05
* @param[in] sessionID ����ĻỰID��
* @param[in] errorCode �����롣0 ��ʾ�ɹ���
* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
* @ingroup G_T_LocalAction
*/
void TAP_CDECL TradeSpi::OnRspOrderLocalModify(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderLocalModifyRsp *info)
{

}


/**
* @brief ����ת��Ӧ�� Add:2017.12.05
* @param[in] sessionID ����ĻỰID��
* @param[in] errorCode �����롣0 ��ʾ�ɹ���
* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
* @ingroup G_T_LocalAction
*/
void TAP_CDECL TradeSpi::OnRspOrderLocalTransfer(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIOrderLocalTransferRsp *info)
{

}


/**
* @brief �ɽ�¼��Ӧ�� Add:2017.12.05
* @param[in] sessionID ����ĻỰID��
* @param[in] errorCode �����롣0 ��ʾ�ɹ���
* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
* @ingroup G_T_LocalAction
*/
void TAP_CDECL TradeSpi::OnRspFillLocalInput(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIFillLocalInputRsp *info)
{

}


/**
* @brief ����ɾ��Ӧ�� Add:2017.12.05
* @param[in] sessionID ����ĻỰID��
* @param[in] errorCode �����롣0 ��ʾ�ɹ���
* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
* @ingroup G_T_LocalAction
*/
void TAP_CDECL TradeSpi::OnRspFillLocalRemove(ITapTrade::TAPIUINT32 sessionID, ITapTrade::TAPIINT32 errorCode, const ITapTrade::TapAPIFillLocalRemoveRsp *info)
{

}
