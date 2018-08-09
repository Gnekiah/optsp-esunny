#include "quotespi.h"


QuoteSpi::QuoteSpi()
{

}


/**
* @brief	ϵͳ��¼���̻ص���
* @details	�˺���ΪLogin()��¼�����Ļص�������Login()�ɹ���������·���ӣ�Ȼ��API������������͵�¼��֤��Ϣ��
*			��¼�ڼ�����ݷ�������͵�¼�Ļ�����Ϣ���ݵ��˻ص������С�
* @param[in] errorCode ���ش�����,0��ʾ�ɹ���
* @param[in] info ��½Ӧ����Ϣ�����errorCode!=0����info=NULL��
* @attention	�ûص����سɹ���˵���û���¼�ɹ������ǲ�����API׼����ϡ���Ҫ�ȵ�OnAPIReady���ܽ��в�ѯ�붩������
* @ingroup G_Q_Login
*/
void TAP_CDECL QuoteSpi::OnRspLogin(TAPIINT32 errorCode, const TapAPIQuotLoginRspInfo *info) 
{

}
/**
* @brief	֪ͨ�û�API׼��������
* @details	ֻ���û��ص��յ��˾���֪ͨʱ���ܽ��к����ĸ����������ݲ�ѯ������\n
*			�˻ص�������API�ܷ����������ı�־��
* @attention  ������ſ��Խ��к�����������
* @ingroup G_Q_Login
*/
void TAP_CDECL QuoteSpi::OnAPIReady()
{

}
/**
* @brief	API�ͷ���ʧȥ���ӵĻص�
* @details	��APIʹ�ù������������߱��������������ʧȥ���Ӻ󶼻ᴥ���˻ص�֪ͨ�û���������������Ѿ��Ͽ���
* @param[in] reasonCode �Ͽ�ԭ����롣����ԭ����μ��������б� \n
* @ingroup G_Q_Disconnect
*/
void TAP_CDECL QuoteSpi::OnDisconnect(TAPIINT32 reasonCode)
{

}
/**
* @brief	��������Ʒ����Ϣ��
* @details	�˻ص��ӿ��������û����صõ�������Ʒ����Ϣ��
* @param[in] sessionID ����ĻỰID
* @param[in] errorCode �����룬��errorCode!=0ʱ,infoΪNULL��
* @param[in] isLast ��ʾ�Ƿ������һ�����ݣ�
* @param[in] info ���ص���Ϣ�������ʼָ�롣
* @attention  ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
* @ingroup G_Q_Commodity
*/
void TAP_CDECL QuoteSpi::OnRspQryCommodity(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteCommodityInfo *info)
{

}
/**
* @brief ����ϵͳ�к�Լ��Ϣ
* @param[in] sessionID ����ĻỰID��
* @param[in] errorCode �����룬��errorCode!=0ʱ,infoΪNULL��
* @param[in] isLast ��ʾ�Ƿ������һ�����ݣ�
* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
* @ingroup G_Q_Contract
*/
void TAP_CDECL QuoteSpi::OnRspQryContract(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteContractInfo *info)
{

}
/**
* @brief	���ض��������ȫ�ġ�
* @details	�˻ص��ӿ��������ض��������ȫ�ġ�ȫ��Ϊ��ǰʱ���������Ϣ��
* @param[in] sessionID ����ĻỰID��
* @param[in] isLast ��ʾ�Ƿ������һ�����ݣ�
* @param[in] errorCode �����룬��errorCode!=0ʱ,infoΪNULL��
* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
* @attention  ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
* @ingroup G_Q_Quote
*/
void TAP_CDECL QuoteSpi::OnRspSubscribeQuote(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIQuoteWhole *info)
{

}
/**
* @brief �˶�ָ����Լ������Ľ���ص�
* @param[in] sessionID ����ĻỰID��
* @param[in] errorCode �����룬��errorCode!=0ʱ,infoΪNULL��
* @param[in] isLast ��ʾ�Ƿ������һ�����ݣ�
* @param[in] info		ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
* @attention  ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
* @ingroup G_Q_Quote
*/
void TAP_CDECL QuoteSpi::OnRspUnSubscribeQuote(TAPIUINT32 sessionID, TAPIINT32 errorCode, TAPIYNFLAG isLast, const TapAPIContract *info)
{

}
/**
* @brief	���ض�������ı仯���ݡ�
* @details	�˻ص��ӿ�����֪ͨ�û�������Ϣ�����˱仯�������û��ύ�µ�����ȫ�ġ�
* @param[in] info ���µ�����ȫ������
* @attention ��Ҫ�޸ĺ�ɾ��Quoteָʾ�����ݣ��������ý���������������Ч��
* @ingroup G_Q_Quote
*/
void TAP_CDECL QuoteSpi::OnRtnQuote(const TapAPIQuoteWhole *info)
{

}