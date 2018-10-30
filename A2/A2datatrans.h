#ifndef __A2_DATATRANS_V1_H
#define __A2_DATATRANS_V1_H

typedef struct
{
	char Buffer[256];
	char Index;
	char status;
	int  UpdateTime;
}Data_PHY0_Type;

typedef struct
{
	char Buffer[256];
	char Index;
	char ErrorCode;
	int  UpdateTime;
}Data_PHY1_Type;

/*
2	SrcAddr	Դ��ַ
2	DstAddr	Ŀ���ַ
4	DataLen	�����򳤶�
2	DriveCode	�豸���ͱ��
2	ProtocolCode	�����Э����
2	PackID	���ݰ�ID
2	Reserved1	������1
2	Reserved2	������2
2	Reserved3	������3
��ͷ��ʽ
*/
//typedef struct
//{
//	char SrcAddr[2];
//	char DstAddr[2];
//	char DataLen[4];
//	char DriveCode[2];
//	char ProtocolCode[2];
//	char PackID[2];
//	char Reserved1[2];
//	char Reserved2[2];
//	char Reserved3[2];
//}PacketHead_Type;

typedef struct
{
	int SrcAddr;
	int DstAddr;
	long DataLen;
	int DriveCode;
	int ProtocolCode;
	int PackID;
	int Reserved1;
	int Reserved2;
	int Reserved3;
}PacketHead_Type;


#define FRAME_HEAD 0XA7
#define FRAME_END  0X7A

#define HEAD_LENTH  20
#define WAITING_HEAD 0x00
#define GETTING_HEAD 0x01
#define GETTING_PACK 0x02
#define GETTING_END  0x03

#define PHY0RETURN_OK            0X00
#define PHY0RETURN_PACK_TOO_LONG 0X01
#define PHY0RETURN_UNKNOW_ERROR 0X02

#define PHY1ERROR_FRAME_TOO_SHORT 0x01
#define PHY1ERROR_ESCAPE_ERROR    0x02
#define PHY1ERROR_ESCAPE_ERROR_2  0x04

#endif 
