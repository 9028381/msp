#include "gy901.h"

#define GYR_ADDR 0x50 //对应原来的0xa1(a1是取前7位，这里取的是后7位)


//参考i2c_controller_rw_multibyte_fifo_poll
float Get_gyr_value(enum gyroscope k)
{
    volatile uint8_t buf[2];
		uint8_t key = k;


	// 发送key
	DL_I2C_fillControllerTXFIFO(I2C_INST, &key, 1); //***

    while (!(
        DL_I2C_getControllerStatus(I2C_INST) & DL_I2C_CONTROLLER_STATUS_IDLE))
        ;

    DL_I2C_startControllerTransferAdvanced(I2C_INST, GYR_ADDR, DL_I2C_CONTROLLER_DIRECTION_TX, 1, DL_I2C_CONTROLLER_START_ENABLE, DL_I2C_CONTROLLER_STOP_ENABLE, DL_I2C_CONTROLLER_ACK_DISABLE); //***
		//DL_I2C_startControllerTransfer(I2C_INST, GYR_ADDR, DL_I2C_CONTROLLER_DIRECTION_TX, 1);
		
    while (DL_I2C_getControllerStatus(I2C_INST) &
           DL_I2C_CONTROLLER_STATUS_BUSY_BUS)
        ;

    while (!(
        DL_I2C_getControllerStatus(I2C_INST) & DL_I2C_CONTROLLER_STATUS_IDLE))
        ;

	//接收
	DL_I2C_startControllerTransfer(I2C_INST, GYR_ADDR, DL_I2C_CONTROLLER_DIRECTION_RX, 2);

	for (uint8_t i = 0; i < 2; i++) {
        while (DL_I2C_isControllerRXFIFOEmpty(I2C_INST))
            ;
        buf[i] = DL_I2C_receiveControllerData(I2C_INST);
    }


    float value = (short)(((short)buf[1] << 8) | buf[0]);

    switch (key)
    {
    case gyr_a_x:
    case gyr_a_y:
    case gyr_a_z:
        return value * 16 * 9.8;
    case gyr_w_x:
    case gyr_w_y:
    case gyr_w_z:
        return value / 2000;
    case gyr_x_roll:
    case gyr_y_pitch:
    case gyr_z_yaw:
        return value * 180 / 32768;
    }
}
