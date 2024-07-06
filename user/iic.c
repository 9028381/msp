#include "gyr_iic.h"

uint8_t IIC_DATA;
/********************************************************
 * 函  数  名:IIC_init
 * 功       能:IIC引脚初始化程序，相关引脚在exinIIC.h文件中列出
 * 参       数:无
 * 注意事项:在使用IIC其他函数时，务必先调用此函数进行初始化
 ********************************************************/
void IIC_init(void) {
  IIC_SCL_OUT;
  IIC_SDA_OUT;
  IIC_SCL_HIGH;
  IIC_SDA_HIGH;
}
/********************************************************
 * 函  数  名:IIC_reset
 * 功       能:IIC总线软件复位，在系统断电或重启后调用该函数复位IIC
 * 参       数:无
 * 注意事项:无
 ********************************************************/
void IIC_reset(void) // IIC软件复位
{
  uint8_t i;
  IIC_start();

  IIC_SCL_LOW;
  IIC_SDA_HIGH;

  for (i = 0; i < 9; i++) // 送入9个时钟
  {
    IIC_SCL_LOW; // 拉低时钟线
    IIC_delay;
    IIC_SCL_HIGH; // 拉高时钟线
    IIC_delay;
    IIC_SCL_LOW; // 拉低时钟线
    IIC_delay;
  }
  IIC_start();
  IIC_stop();
}
/********************************************************
 * 函  数  名:IIC_start
 * 功       能:IIC总线发送起始信号
 *          SCL:_______
 *                     |________
 *          SDA:__
 *                |_________
 * 参       数:无
 * 注意事项:无
 ********************************************************/
// IIC起始信号
void IIC_start(void) {
  IIC_SDA_OUT;
  IIC_SDA_HIGH; // 起始均为高电平
  IIC_SCL_HIGH;
  IIC_delay;
  IIC_SDA_LOW; // 先把SDA拉低
  IIC_delay;
  IIC_SCL_LOW; // 再把SCL拉低
}
/********************************************************
 * 函  数  名:IIC_stop
 * 功       能:IIC总线发送结束信号
 *          SCL:         ______
 *              ________|
 *          SDA:             _______
 *              ____________|
 * 参       数:无
 * 注意事项:无
 ********************************************************/
// IIC停止信号
void IIC_stop(void) {
  IIC_SDA_OUT; // 设置SDA方向为输出
  IIC_SCL_LOW;
  IIC_SDA_LOW;
  IIC_delay;
  IIC_SCL_HIGH;
  IIC_delay;
  IIC_SDA_HIGH;
  IIC_delay;
  //   IIC_SCL_LOW;
  //   IIC_SDA_LOW;
}
/********************************************************
 * 函  数  名:IIC_ACK
 * 功       能:IIC主机发送应答信号
 * 参       数:无
 * 注意事项:无
 ********************************************************/
// 主机应答从机
void IIC_ACK(void) {
  IIC_SCL_LOW;
  IIC_SDA_OUT;
  IIC_SDA_LOW;
  IIC_delay;
  IIC_SCL_HIGH;
  IIC_delay;
  IIC_SCL_LOW;
}
/********************************************************
 * 函  数  名:IIC_NACK
 * 功       能:IIC主机不发送应答信号
 * 参       数:无
 * 注意事项:无
 ********************************************************/
void IIC_NACK(void) {
  IIC_SCL_LOW;
  IIC_SDA_OUT;
  IIC_SDA_HIGH;
  IIC_delay;
  IIC_SCL_HIGH;
  IIC_delay;
  IIC_SCL_LOW;
}

/********************************************************
 * 函  数  名:Check_ACK
 * 功       能:IIC主机检查从机是否应答
 * 参       数:无
 * 注意事项:无
 ********************************************************/
// 主机检查从机是否应答
unsigned char Check_ACK(void) {
  uint8_t error_time = 0;
  IIC_SDA_IN;

  IIC_SDA_HIGH;
  IIC_delay; // 进行延时
  IIC_SCL_HIGH;
  IIC_delay;

  while (IIC_SDA_READ) {
    error_time = error_time + 1;
    if (error_time > 250) {
      IIC_stop();
      return 0;
    }
  }
  IIC_SCL_LOW;
  return 1;
}

/********************************************************
 * 函  数  名:IIC_Send_Byte
 * 功       能:发送一个8位数据
 * 参       数:Data
 * 注意事项:一次发送为8位，为unsigned char类型
 ********************************************************/
void IIC_Send_Byte(uint8_t Data) {
  IIC_SDA_OUT;
  IIC_SCL_LOW;
  IIC_delay;
  uint8_t i;
  for (i = 0; i < 8; i++) {
    if ((Data & 0x80) >> 7 == 1) {
      IIC_SDA_HIGH;
    } else {
      IIC_SDA_LOW;
    }
    Data <<= 1;
    IIC_SCL_HIGH;
    IIC_delay;
    IIC_SCL_LOW;
    IIC_delay;
  }
}
/********************************************************
 * 函  数  名:IIC_Read_Byte
 * 功       能:主机读取一次数据
 * 参       数:ack
 * 注意事项:
 *      函数将读取的1字节数据作为返回值返回
            读取完毕后，主机是否应答，通过ack参数决定
            ack = 1主机在读取完1字节数据后产生一次应答
            ack = 0主机在读取完1字节数据后不产生应答信号
 ********************************************************/
unsigned char IIC_Read_Byte(uint8_t ack) {
  uint8_t i, temp = 0;
  IIC_SDA_IN;

  for (i = 0; i < 8; i++) {
    IIC_SCL_LOW;
    IIC_delay;
    IIC_SCL_HIGH;
    temp = temp << 1;
    if (IIC_SDA_READ == 1)
      temp++;
  }
  if (!ack)
    IIC_NACK();
  else
    IIC_ACK();
  return temp;
}

uint8_t IIC_Read_To_Mem(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf) {
  IIC_start();                       // 产生IIC开始信号
  IIC_Send_Byte((addr << 1) | 0x00); // 发送器件地址+写命令
  if (!Check_ACK()) {
    IIC_stop(); // 没有检测到应答信号就发送结束信号
    return 1;   // 发送1错误
  }
  IIC_Send_Byte(reg); // 发送寄存器地址
  Check_ACK();
  IIC_start(); // 产生IIC开始信号

  IIC_Send_Byte((addr << 1) | 0x01); // 发送器件地址+读命令
  Check_ACK();

  while (len) {
    if (len == 1) {
      *buf = IIC_Read_Byte(0); // 不应答
    } else {
      *buf = IIC_Read_Byte(1); // 应答
    }
    len--;
    buf++;
  }
  IIC_stop(); // 发送停止信号
  return 0;
}

uint8_t IIC_Read(uint8_t addr, uint8_t len, uint8_t *buf) {
  IIC_Send_Byte((addr << 1) | 0x01); // 发送器件地址+读命令
  Check_ACK();

  while (len) {
    if (len == 1) {
      *buf = IIC_Read_Byte(0); // 不应答
    } else {
      *buf = IIC_Read_Byte(1); // 应答
    }
    len--;
    buf++;
  }
  IIC_stop(); // 发送停止信号
  return 0;
}

uint8_t IIC_Write_To_Mem(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *buf) {
  uint8_t i;
  IIC_start();                       // 产生IIC开始信号
  IIC_Send_Byte((addr << 1) | 0x00); // 发送器件地址+写命令
  if (!Check_ACK()) {
    IIC_stop(); // 没有检测到应答信号就发送结束信号
    return 1;   // 发送1错误
  }
  IIC_Send_Byte(reg); // 发送寄存器地址
  Check_ACK();
  for (i = 0; i < len - 1; i++) {
    IIC_Send_Byte(buf[i]);
    IIC_ACK();
  }
  IIC_Send_Byte(buf[i]);
  IIC_NACK();
  IIC_stop();
  return 0;
}

uint8_t IIC_Write(uint8_t addr, uint8_t len, uint8_t *buf) {
  uint8_t i;
  IIC_start();                       // 产生IIC开始信号
  IIC_Send_Byte((addr << 1) | 0x00); // 发送器件地址+写命令
  Check_ACK();
  for (i = 0; i < len - 1; i++) {
    IIC_Send_Byte(buf[i]);
    IIC_ACK();
  }
  IIC_Send_Byte(buf[i]);
  IIC_NACK();
  IIC_stop();
  return 0;
}
