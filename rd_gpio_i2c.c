#include <asm-generic/gpio.h>
#include <linux/delay.h>

#include "rd_gpio_i2c.h"

#define     SET_HIGH(gpio)      clk_high(gpio)
#define     SET_LOW(gpio)       clk_low(gpio)

//#define		I2C_DELAY
#define			NOP				((void) 0;)
#define			DELAY			(ndelay(NDELAY);)

//#define I2C_DEBUG

#ifdef I2C_DEBUG
#define I2C_DBG(...)			(printk(KERN_INFO __VA_ARGS__))
#else
#define I2C_DBG(...)
#endif

void clk_low(unsigned int gpio)
{
	gpio_set_value_cansleep(gpio, 0);
}
void clk_high(unsigned int gpio)
{
	gpio_set_value_cansleep(gpio, 1);
}
void sda_out(void)
{
//	SET_HIGH(GPIO_DIR);
	ndelay(NDELAY);
}
void sda_in(void)
{
//	SET_LOW(GPIO_DIR);
	ndelay(NDELAY);
}
void rd_i2c_start_signal(unsigned int clk, unsigned int dx)
{
	SET_LOW(dx);
#ifdef I2C_DELAY
	ndelay(NDELAY);
#endif
}
void rd_i2c_stop_signal(unsigned int clk, unsigned int dx)
{
	SET_LOW(dx);
#ifdef I2C_DELAY
	ndelay(NDELAY);
#endif
	SET_HIGH(dx);
#ifdef I2C_DELAY
	ndelay(NDELAY);
#endif
}
void send_data(unsigned int clk, unsigned int dx, unsigned int data)
{
	int n, d;
	gpio_direction_output(clk, 1);
	gpio_direction_output(dx, 1);
	sda_out(); //gpio158 is output dir
	rd_i2c_start_signal(clk, dx);
	for(n=(DATA_TYPE-1); n>=0; n--)
	{
		clk_low(clk);
		d = (data >> n) & 0x1;
		gpio_set_value_cansleep(dx, d);
#ifdef I2C_DELAY
		ndelay(NDELAY);
#endif
		clk_high(clk);
#ifdef I2C_DELAY
		ndelay(NDELAY);
#endif
		
	}
	rd_i2c_stop_signal(clk, dx);
}

int write_table2fpga(u8 *table_data, unsigned int size)
{
	u16 ack;
	u16 data;
	int loop;

    for (loop=0; loop < size; loop++)
    {
		data = *(table_data + loop);
		data &= 0xff;
		data |= 0x1000; 	//add fpga register address
		
		//send table data
		send_data(GPIO_CLKX, GPIO_DX, data);
		//get ack signal
		if((receive_data(GPIO_CLKX, GPIO_DX, &ack) == FALSE) || (ACK_MAGIC != ack))
		{
			printk(KERN_ERR "[WRITE_TABLE]: write table to FPGA error, ACK = %d\n", ack);
			return FALSE;
		}
    }
	
	return TRUE;
}

//return 0, receive complete
//return -1, receive error
//receive data store in arg data 
int receive_data(unsigned int clk, unsigned int rx, u16 *data)
{
	unsigned int n = 3, d;
	unsigned int rev_d = 0;
	gpio_direction_output(clk, 1);
	gpio_direction_input(rx);
	sda_in();	//gpio158 is input dir
#ifdef I2C_DELAY
	ndelay(NDELAY);
#endif
	while(n--)	//if rx !=0, FPGA didnt ready to send data
	{
		if(0 == gpio_get_value_cansleep(rx)) //FPGA ready to send data
		{
			for(n=0; n<(DATA_TYPE); n++)
			{
				clk_low(clk);
#ifdef I2C_DELAY
				ndelay(NDELAY);
#endif
				clk_high(clk);
				d = gpio_get_value_cansleep(rx);
				rev_d = (rev_d << 1) | d;
			}
			*data = rev_d;
			gpio_direction_output(rx, 1);
			sda_out();	//gpio158 is output dir
			return TRUE;
		}
#ifdef I2C_DELAY
		ndelay(NDELAY);
#endif
	}
	
	gpio_direction_output(rx, 1);
	sda_out(); //gpio158 is output dir
	return FALSE;
}
int set_reg(u16 data)
{
	u16 ack;
	int n = 3;
//	printk("[MCBSP SET REG]: data = 0x%x\n", data & 0xff);

	I2C_DBG("[MCBSP SET REG]: data = 0x%x\n", data & 0xff);
//	printk("[MCBSP SET REG]: addr = 0x%x\n", (data & 0xff00) >> 8);
	I2C_DBG("[MCBSP SET REG]: addr = 0x%x\n", (data & 0xff00) >> 8);

	//add write bit
	data &= 0x7fff;					//bit7 = 0, write flag
	while(n--)
	{
		//send data
		send_data(GPIO_CLKX, GPIO_DX, data);
		//get ack signal
		if((receive_data(GPIO_CLKX, GPIO_DX, &ack) == 0) && (ACK_MAGIC == ack))
		{
			return TRUE;
		}
		printk(KERN_ERR "[set_reg]: ack = 0x%x, no ack signal or ack magic error\n", ack);
	}
	return FALSE;
}

//return 0, get reg status complete
//return -1, get reg status error
//arg reg_info(8bit) transmit reg addr to function
//when receive completed, reg status(8bit) stored in arg reg_info
int get_reg(u16 *reg_info)
{
	u16 rev_d;
	u16	rev_addr = *reg_info;
	int i = 0;
	int n=3;	//if receive addr != which i send or FPGA does not send i2c ready signal,  get reg_status again untill 3 times
	
	I2C_DBG("[MCBSP READ FPGA]: send reg addr = 0x%x\n", rev_addr);
	//add read bit
	rev_addr |= 0x80; //7bit = 1, read cmd
	rev_addr = rev_addr << 8;
	while(n--)
	{
		//use i2c to send reg addr
		send_data(GPIO_CLKX, GPIO_DX, rev_addr);
		//read reg status from i2c, 16bit, returned data store in rev_d
		if(receive_data(GPIO_CLKX, GPIO_DX, &rev_d) < 0)
		{
			printk(KERN_ERR "[MCBSP READ FPGA]: SDA line didnt pull low at receive start, start again, %d times\n", ++i);
			continue;
		}
//		printk(KERN_INFO "[MCBSP READ FPGA]: get from fpga = 0x%x\n", rev_d);
		//check addr received from FPGA, if it != what i send, indicate transfer error
		if((rev_d & 0x7f00) == (rev_addr & 0x7f00))
		{
			*reg_info = (rev_d & 0x00ff);
			I2C_DBG("[MCBSP READ FPGA]:read from fpga addr = 0x%x, data = 0x%x\n", rev_d >> 8, *reg_info);
			return TRUE;
		}
		I2C_DBG("[MCBSP READ FPGA]: received addr != which i send, start get again, %d times\n", ++i);
		//ndelay(NDELAY);
	}
	return FALSE;
}

