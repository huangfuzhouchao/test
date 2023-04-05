#include "stm32f10x.h"
#include <stdio.h>
#include <stdarg.h>

u8 CRC_L=0,CRC_H=0;
unsigned long CRC_wcrc=0XFFFF;	//预置16位crc寄存器，初值全部为1 
unsigned char CRC_temp;					//定义中间变量 
int CRC_i=0,CRC_j=0;								//定义计数 

void crc16(unsigned char *ptr,unsigned int len) 
{ 
	CRC_wcrc=0XFFFF;
	for(CRC_i=0;CRC_i<len;CRC_i++)					//循环计算每个数据 
	{ 
		CRC_temp=*ptr&0X00FF;					//将八位数据与crc寄存器亦或 
		ptr++;										//指针地址增加，指向下个数据 
		CRC_wcrc^=CRC_temp;								//将数据存入crc寄存器 
		for(CRC_j=0;CRC_j<8;CRC_j++)					//循环计算数据的 
		{ 
			if(CRC_wcrc&0X0001)					//判断右移出的是不是1，如果是1则与多项式进行异或。 
			{ 
				CRC_wcrc>>=1;							//先将数据右移一位 
				CRC_wcrc^=0XA001;					//与上面的多项式进行异或 
			}else{									//如果不是1，则直接移出 
			 	CRC_wcrc>>=1;							//直接移出 
			} 
		} 
	} 
	CRC_temp=CRC_wcrc;							//crc的值 
	CRC_L=CRC_wcrc;									//crc的低八位 		 
	CRC_H=CRC_wcrc>>8;							//crc的高八位 
}		
