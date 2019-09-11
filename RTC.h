/************************************************************************

                          实时时钟模块
此模块功能:
 1. 提供并更新实时时间(通过回调函数方式通知外部更新以连接外部结构)
 2. 用于掉电保存的RAM空间,这里直接直接提供接口使用
相关说明：
  1. 考虑到有的RTC为MCU内部实现，可直接快速读取，故此模块未提供结构缓存，
    如为外部实现时，请在内部根据数据结构实现缓存
  2. 考虑到绝大部分系统只有一个RTC,故这里直接单例化  
此模块独立于应用，但硬件相关故有不同实现方式
************************************************************************/
#ifndef __RTC_H
#define __RTC_H

/************************************************************************
                           相关定义
************************************************************************/

//备份数据区大小(需>=4)
#ifndef RTC_BAK_DATA_SIZE
  #define RTC_BAK_DATA_SIZE  4
#endif

/************************************************************************
                           相关函数
************************************************************************/

//---------------------------------初始化函数----------------------------
void RTC_Init0(signed char IsInited);

//--------------------------------任务函数-------------------------------
//建议256ms更新一次以更新实时时间
void RTC_Task(void);

//-------------------------------设置RTC信息-----------------------------
//Pos定义为:相对年0,月1,日2,时3,分4,秒5
void RTC_SetInfo(unsigned char Pos,
                 unsigned char Data);

//------------------------------写备份数据------------------------------
//用于保存掉电不丢失的数据，为保证与32位硬件兼容，为32Bit模式
void RTC_WrBakData(unsigned char Adr,         //保存位置
                   const unsigned char *pData,//要保存的数据
                   unsigned char Len);          //数据长度

//------------------------------读备份数据---------------------------------
//用于保存掉电不丢失的数据，为保证与32位硬件兼容，为32Bit模式
void RTC_RdBakData(unsigned char Adr,     //保存位置
                   unsigned char *pData,//要保存的数据
                   unsigned char Len);   //数据长度

/************************************************************************
                           回调函数
************************************************************************/

//---------------------------------得到年起始----------------------------
//unsigned short RTC_cbGetStartYear(void);
#define RTC_cbGetStartYear() (YEAR_START)

//------------------------------更新实时时间----------------------------
void RTC_cbUpdate(unsigned char RelativeYear, //相对起始年,0-63
                  unsigned char Mouth,
                  unsigned char Date,
                  unsigned char Hour,
                  unsigned char Minute,
                  unsigned char Sec);

//-----------------------更新实时时间用ZipTime格式----------------------------
void RTC_cbUpdateZipTime(unsigned long ZipTime);

#endif


