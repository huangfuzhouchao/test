#include "stm32f10x.h"
#include <stdio.h>
#include <stdarg.h>

u8 CRC_L=0,CRC_H=0;
unsigned long CRC_wcrc=0XFFFF;	//Ԥ��16λcrc�Ĵ�������ֵȫ��Ϊ1 
unsigned char CRC_temp;					//�����м���� 
int CRC_i=0,CRC_j=0;								//������� 

void crc16(unsigned char *ptr,unsigned int len) 
{ 
	CRC_wcrc=0XFFFF;
	for(CRC_i=0;CRC_i<len;CRC_i++)					//ѭ������ÿ������ 
	{ 
		CRC_temp=*ptr&0X00FF;					//����λ������crc�Ĵ������ 
		ptr++;										//ָ���ַ���ӣ�ָ���¸����� 
		CRC_wcrc^=CRC_temp;								//�����ݴ���crc�Ĵ��� 
		for(CRC_j=0;CRC_j<8;CRC_j++)					//ѭ���������ݵ� 
		{ 
			if(CRC_wcrc&0X0001)					//�ж����Ƴ����ǲ���1�������1�������ʽ������� 
			{ 
				CRC_wcrc>>=1;							//�Ƚ���������һλ 
				CRC_wcrc^=0XA001;					//������Ķ���ʽ������� 
			}else{									//�������1����ֱ���Ƴ� 
			 	CRC_wcrc>>=1;							//ֱ���Ƴ� 
			} 
		} 
	} 
	CRC_temp=CRC_wcrc;							//crc��ֵ 
	CRC_L=CRC_wcrc;									//crc�ĵͰ�λ 		 
	CRC_H=CRC_wcrc>>8;							//crc�ĸ߰�λ 
}		
