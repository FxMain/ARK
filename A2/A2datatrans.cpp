/**
  *********************************************************************************
* File Name          : A2_datatrans_V1.c
* Author             : Ribon
* Version            : V1.0
* Description        : A2 Studio data transfer protocol, uart ,UDP pack or TCP pack
***********************************************************************************
* History:
* 18/09/28 v1.0
***********************************************************************************
  */
#include "A2_datatrans_V1.h"
#include <string.h>

//#define BIG_END
#define LITTLE_END

PacketHead_Type PackHead;

Data_PHY1_Type PHY1_TX,PHY1_RX;
Data_PHY0_Type PHY0_TX,PHY0_RX;
char RX_Pack[256];
char TX_Pack[256];


//以下为接收部分实现
void data_Application(char *Pack)
{
	;
}

void Unpack(Data_PHY1_Type *PHY1_Frame)
{
	if(PHY1_Frame->Index <= HEAD_LENTH)
	{
		;//包太短，虽然现在在前方校验过，防止异步导致问题这里还是再检一次
	}
	
	//获得头
	memcpy(&PackHead ,&PHY1_Frame            , HEAD_LENTH);
	memcpy(&RX_Pack  ,&PHY1_Frame+HEAD_LENTH , PHY1_Frame->Index-HEAD_LENTH);	
	
	//丢入应用层
	data_Application(RX_Pack);
}

void ErrorHandler(void)
{
	;
}

void PHY0_to_PHY1(Data_PHY0_Type *PHY0_Frame , Data_PHY1_Type *PHY1_Frame )
{
	PHY1_Frame->ErrorCode = 0;
	if(PHY0_Frame->Index < HEAD_LENTH)
	{
		PHY1_Frame->ErrorCode |= PHY1ERROR_FRAME_TOO_SHORT;//收到的包不够长
	}
	else
	{
		char i = 0;
		char temp;
		for(i = 0; i< PHY0_Frame->Index ; i++)
		{
			temp = PHY1_Frame->Buffer[i];
			if(temp != 0XA6 && temp != 0X7B)
			{
				PHY1_Frame->Buffer[i] = temp;
			}
			else if(temp == 0XA6)
			{
				if(PHY1_Frame->Buffer[i+1] == 0X01  && i+1< PHY0_Frame->Index)
				{
					PHY1_Frame->Buffer[i] = 0XA6;
					i++;//跳过属于转义的下一个字节
				}
				else if(PHY1_Frame->Buffer[i+1] == 0X02 && i+1< PHY0_Frame->Index)
				{
					PHY1_Frame->Buffer[i] = 0XA7;
					i++;//跳过属于转义的下一个字节
				}
				else
				{
					PHY1_Frame->ErrorCode |= PHY1ERROR_ESCAPE_ERROR;//包内容有转义错误
				}
			}
			else if(temp == 0X7B)
			{
				if(PHY1_Frame->Buffer[i+1] == 0X01  && i+1< PHY0_Frame->Index)
				{
					PHY1_Frame->Buffer[i] = 0XA6;
					i++;//跳过属于转义的下一个字节
				}
				else if(PHY1_Frame->Buffer[i+1] == 0X02 && i+1< PHY0_Frame->Index)
				{
					PHY1_Frame->Buffer[i] = 0XA7;
					i++;//跳过属于转义的下一个字节
				}
				else
				{
					PHY1_Frame->ErrorCode |= PHY1ERROR_ESCAPE_ERROR;//包内容有转义错误
				}
			}
			
			
		}
	}
	
	if(PHY1_Frame->ErrorCode)
	{
		ErrorHandler();
	}
	else
	{
		Unpack(PHY1_Frame);
	}
}

char PHY0_input(char data , Data_PHY0_Type *PHY0_Frame)
{
	if(data == FRAME_HEAD)//只要收到0XA7，就准备接收
	{
		PHY0_Frame->Index = 0;
		PHY0_Frame->status = GETTING_HEAD;
	}
	else if(PHY0_Frame->status ==GETTING_HEAD  && data!=FRAME_HEAD )//第一个非0XA7的字节开始接收
	{
		PHY0_Frame->Buffer[PHY0_Frame->Index] = data;
		PHY0_Frame->Index++;
		PHY0_Frame->status = GETTING_PACK;
	}
	else if(PHY0_Frame->status ==GETTING_PACK)//接收数据帧内容
	{
		PHY0_Frame->Buffer[PHY0_Frame->Index] = data;
		PHY0_Frame->Index++;
	}
	else if(data == FRAME_END)//接收到帧尾，丢入PHY0层解包
	{
		PHY0_to_PHY1(PHY0_Frame,&PHY1_RX);
		PHY0_Frame->status = WAITING_HEAD;
	}
	else   //其他异常
	{
		PHY0_Frame->Index = 0;
		PHY0_Frame->status = WAITING_HEAD;
		return PHY0RETURN_UNKNOW_ERROR;
	}
	
	if(PHY0_Frame->Index >= 250)//数据包太长，丢弃
	{
		PHY0_Frame->Index = 0;
		PHY0_Frame->status = WAITING_HEAD;
		return PHY0RETURN_PACK_TOO_LONG;
	}
	
	return PHY0RETURN_OK;
}





//以下为发送部分实现
char PutFrameIntoPHY1(char* frame , char lenth);
char PHY1_to_PHY0(Data_PHY1_Type *PHY1,Data_PHY0_Type *PHY0);
char PHY0_output(Data_PHY0_Type *PHY0_TX_Frame ,char lenth);
void Send(char* frame , char lenth)
{
	PutFrameIntoPHY1(frame , lenth);
	PHY1_to_PHY0( &PHY1_TX , &PHY0_TX );
	PHY0_output(&PHY0_TX , PHY0_TX.Index);
}

char PutFrameIntoPHY1(char* frame , char lenth)//把数据帧丢给PHY1层
{
	//AddHead();
	//
	;
	return 0;
}

char PHY1_to_PHY0(Data_PHY1_Type *PHY1,Data_PHY0_Type *PHY0)
{
	char i = 0,j=0;
	char temp;
	
	//增加帧头
	for(i=0; i<8; i++)
	{
		PHY0->Buffer[j] = 0xA7; 
		j++;
	}
	
	for(i = 0; i< PHY1->Index ; i++)
	{
		temp = PHY1->Buffer[i];
		if(temp != 0XA7 && temp != 0X7A)
		{
			PHY0->Buffer[j] = temp;
		}
		else if(temp == 0XA7)
		{
			PHY0->Buffer[j]   = 0xA6;
			PHY0->Buffer[++j] = 0x02;
		}
		else if(temp != 0X7A)
		{
			PHY0->Buffer[j]   = 0xA6;
			PHY0->Buffer[++j] = 0x01;
		}
		j++;
	}

	//增加帧尾
	PHY0->Buffer[j++] = 0X7A;
	
	PHY0->Index = j;
	return PHY0->Index;
}
	

char PHY0_output(Data_PHY0_Type *PHY0_TX_Frame , char lenth)
{
	;//物理层发送
	return 0;
}

