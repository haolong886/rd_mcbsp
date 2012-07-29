#ifndef _RD_GPIO_I2C_H
#define _RD_GPIO_I2C_H


//gpio


#define GPIO6_BASE				0x49058000
#define GPIO_SETDATAOUT_GPIO6 	0x49058094
#define GPIO_CLRDATAOUT_GPIO6 	0x49058090
#define GPIO6_DATAOUT		  	0x4905803c
#define GPIO6_OE			  	0x49058034
#define GPIO6_SYSCONFIG			0x49058010
#define GPIO6_DATAIN			0x49058038
#define GPIO6_WAKEUP_ENABLE		(GPIO6_BASE + 0x20)

#define FSX_IO					0x2
#define CLKX_IO					0x4
#define GPIO_DX					158
#define GPIO_CLKX				161
#define GPIO_DIR				162

#define DATA_TYPE				16
#define ACK_MAGIC				0x5a	//fpga send ack_magic number after write fpga reg

#define NDELAY					100
#define TRUE                    0   
#define FALSE                   -1
void clk_low(unsigned int gpio);
void clk_high(unsigned int gpio);
void sda_out(void);
void sda_in(void);
void rd_i2c_start(unsigned int clk, unsigned int dx);
void rd_i2c_stop(unsigned int clk, unsigned int dx);
void send_data(unsigned int clk, unsigned int dx, unsigned int data);
int write_table2fpga(u8 *table_data, unsigned int size);

//return 0, receive complete
//return -1, receive error
//receive data store in arg data 
int receive_data(unsigned int clk, unsigned int rx, u16 *data);
int set_reg(u16 data);

//return 0, get reg status complete
//return -1, get reg status error
//arg reg_info(8bit) transmit reg addr to function
//when receive completed, reg status(8bit) stored in arg reg_info
int get_reg(u16 *reg_info);

#endif

