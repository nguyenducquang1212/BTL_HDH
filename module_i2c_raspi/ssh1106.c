#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/i2c.h>
#include <linux/delay.h>
#include <linux/kernel.h>
#include <linux/kthread.h> //kernel threads

#include <linux/string.h>

#include "ssh1106.h"


#define I2C_BUS_AVAILABLE (1)          // I2C Bus available in our Raspberry Pi
#define SLAVE_DEVICE_NAME ("ETX_OLED") // Device and Driver Name
#define SSD1306_SLAVE_ADDR (0x3C)      // SSD1306 OLED Slave Address

 struct task_struct *etx_thread;


 struct i2c_adapter *etx_i2c_adapter = NULL;    // I2C Adapter Structure
 struct i2c_client *etx_i2c_client_oled = NULL; // I2C Cient Structure (In our case it is OLED)

SSH1106_t display;
/*
** This function writes the data into the I2C client
**
**  Arguments:
**      buff -> buffer to be sent
**      len  -> Length of the data
**   
*/
 int I2C_Write(unsigned char *buf, unsigned int len)
{
    /*
    ** Sending Start condition, Slave address with R/W bit, 
    ** ACK/NACK and Stop condtions will be handled internally.
    */
    int ret = i2c_master_send(etx_i2c_client_oled, buf, len);

    return ret;
}

/*
** This function reads one byte of the data from the I2C client
**
**  Arguments:
**      out_buff -> buffer wherer the data to be copied
**      len      -> Length of the data to be read
** 
*/

/*
** This function is specific to the SSD_1306 OLED.
** This function sends the command/data to the OLED.
**
**  Arguments:
**      is_cmd -> true = command, flase = data
**      data   -> data to be written
** 
*/
char str [80];

int thread_function(void *pv)
{
      while (!kthread_should_stop())
    {
        clearScreen();
        setPosition(15, 30);
        sprintf(str, "%d:%d:%d", ds.hour, ds.min, ds.sec);
        // printk("%s", str);
        putString(str,  &Font1118, white);
        updateScreen();
        msleep(1000);
    }
    return 0;
}



void SSD1306_Write(bool is_cmd, unsigned char data)
{
    unsigned char buf[2] = {0};
    int ret;

    /*
    ** First byte is always control byte. Data is followed after that.
    **
    ** There are two types of data in SSD_1306 OLED.
    ** 1. Command
    ** 2. Data
    **
    ** Control byte decides that the next byte is, command or data.
    **
    ** -------------------------------------------------------                        
    ** |              Control byte's | 6th bit  |   7th bit  |
    ** |-----------------------------|----------|------------|    
    ** |   Command                   |   0      |     0      |
    ** |-----------------------------|----------|------------|
    ** |   data                      |   1      |     0      |
    ** |-----------------------------|----------|------------|
    ** 
    ** Please refer the datasheet for more information. 
    **    
    */
    if (is_cmd == true)
    {
        buf[0] = 0x00;
    }
    else
    {
        buf[0] = 0x40;
    }

    buf[1] = data;

    ret = I2C_Write(buf, 2);
}

void WriteData(uint8_t *_buffer, size_t buff_size)
{
    uint8_t buf[150];
    buf[0] = 0x40;
    memcpy(buf + 1, _buffer, buff_size);
    I2C_Write(buf, buff_size + 1);
}

/*
** This function sends the commands that need to used to Initialize the OLED.
**
**  Arguments:
**      none
** 
*/
 int SSD1306_DisplayInit(void)
{
    msleep(100); // delay

    SSD1306_Write(true, 0xAE); // Entire Display OFF
    SSD1306_Write(true, 0xD5); // Set Display Clock Divide Ratio and Oscillator Frequency
    SSD1306_Write(true, 0xF0); // Default Setting for Display Clock Divide Ratio and Oscillator Frequency that is recommended
    SSD1306_Write(true, 0xA8); // Set Multiplex Ratio
    SSD1306_Write(true, 0x3F); // 64 COM lines
    SSD1306_Write(true, 0xD3); // Set display offset
    SSD1306_Write(true, 0x3F); // 0 offset
    SSD1306_Write(true, 0x40); // Set first line as the start line of the display
    SSD1306_Write(true, 0x8D); // Charge pump
    SSD1306_Write(true, 0x14); // Enable charge dump during display on
    SSD1306_Write(true, 0x20); // Set memory addressing mode
    SSD1306_Write(true, 0x00); // Horizontal addressing mode
    SSD1306_Write(true, 0xA1); // Set segment remap with column address 127 mapped to segment 0
    SSD1306_Write(true, 0xC8); // Set com output scan direction, scan from com63 to com 0
    SSD1306_Write(true, 0xDA); // Set com pins hardware configuration
    SSD1306_Write(true, 0x12); // Alternative com pin configuration, disable com left/right remap
    SSD1306_Write(true, 0x81); // Set contrast control
    SSD1306_Write(true, 0xAF); // Set Contrast to 128
    SSD1306_Write(true, 0xD9); // Set pre-charge period
    SSD1306_Write(true, 0xF1); // Phase 1 period of 15 DCLK, Phase 2 period of 1 DCLK
    SSD1306_Write(true, 0xDB); // Set Vcomh deselect level
    SSD1306_Write(true, 0x40); // Vcomh deselect level ~ 0.77 Vcc
    SSD1306_Write(true, 0xA4); // Entire display ON, resume to RAM content display
    SSD1306_Write(true, 0xA6); // Set Display in Normal Mode, 1 = ON, 0 = OFF
    SSD1306_Write(true, 0x2E); // Deactivate scroll
    SSD1306_Write(true, 0xAF); // Display ON in normal mode

    return 0;
}

void clearScreen(void)
{
    uint16_t i = 0;

    for (i = 0; i < _BUFFER_SIZE; i++)
    {

        display.buffer[i] = 0x00;
    }
}

void blackScreen(void)
{
    uint16_t i = 0;

    for (i = 0; i < _BUFFER_SIZE; i++)
    {

        display.buffer[i] = 0xFF;
    }
}
void updateScreen(void)
{
    uint8_t i = 0;
    //uint8_t j = 0;
    for (i = 0; i < (_HEIGHT / 8); i++)
    {
   
        SSD1306_Write(true, 0XB0 + i);
        SSD1306_Write(true, 0X00);
        SSD1306_Write(true, 0X10);

        // WriteData(&display.buffer [_WIDTH * i], _WIDTH);
        WriteData(&display.buffer[_WIDTH * i], _WIDTH);
    }
}

void moveCursor(int8_t x, int8_t y)
{
    display.CurX += x;
    display.CurY += y;
}

void setPosition(uint8_t x, uint8_t y)
{
    display.CurX = x + 2;
    display.CurY = y;
}

void drawPixel(uint8_t x, uint8_t y, Color_t color)
{
    //	Check x, y in screen
    if (x >= _WIDTH || y >= _HEIGHT)
    {
        //		printf("FAIL HERE\n");
        return;
    }
    if (color == white)
    {
        //set this pixel
        display.buffer[x + (y / 8) * _WIDTH] |= (1 << (y % 8));
    }
    else
    {
        //reset this pixel
        display.buffer[x + (y / 8) * _WIDTH] &= ~(1 << (y % 8));
    }
}

char putChar(char _char, Objects_t *Font, Color_t color)
{
    uint8_t hor_cnt = 0; //Horizon current cursor
    uint8_t ver_cnt = 0; //Vertical current cursor
    uint16_t temp_point = 0;

    if ((display.CurX + Font->oWidth) >= _WIDTH || (display.CurY + Font->oHeight) >= _HEIGHT)
    {
        return 0;
    }
    for (ver_cnt = 0; ver_cnt < Font->oHeight; ver_cnt++)
    {
        temp_point = Font->data[(_char - 32) * Font->oHeight + ver_cnt];
        for (hor_cnt = 0; hor_cnt < Font->oWidth; hor_cnt++)
        {
            if ((temp_point << hor_cnt) & 0x8000)
            //			if ((temp_point << hor_cnt) & 0x80)
            {
                drawPixel(display.CurX + hor_cnt, display.CurY + ver_cnt, color);
            }
            else
            {
                drawPixel(display.CurX + hor_cnt, display.CurY + ver_cnt, !color);
            }
        }
    }
    display.CurX += Font->oWidth;
    return _char;
}

void putString(char *_string, Objects_t *Font, Color_t _color)
{
    uint8_t cnt = 0;

    for (cnt = 0; cnt < strlen(_string); cnt++)
    {
        putChar(*(_string + cnt), Font, _color);
    }
}

void drawBitmap(Objects_t *Obj, Color_t _color)
{
    uint8_t byteWidth = (Obj->oWidth + 7) / 8; //ByteWidth is number of byte will obtain by object
    uint8_t byteCursor = 0;                    //Cursor byte point to object array
    uint8_t ver_pixel_counter = 0;             //Vertical to pixel by pixel of object
    uint8_t hor_pixel_counter = 0;             //Horizontal to pixel by pixel of object

    for (ver_pixel_counter = 0; ver_pixel_counter < Obj->oHeight; ver_pixel_counter++)
    {
        for (hor_pixel_counter = 0; hor_pixel_counter < Obj->oWidth; hor_pixel_counter++)
        {
            // Shift bit in byte
            if (hor_pixel_counter & 7)
            {
                byteCursor <<= 1;
            }
            // Assign new value to new byte
            else
            {
                byteCursor = Obj->data[ver_pixel_counter * byteWidth
                                       //Line
                                       + hor_pixel_counter / 8];
                //Byte in line
            }
            if (byteCursor & 0x80)
            {
                drawPixel(display.CurX + hor_pixel_counter,
                          display.CurY + ver_pixel_counter, white);
            }
            else
            {
                drawPixel(display.CurX + hor_pixel_counter,
                          display.CurY + ver_pixel_counter, black);
            }
        }
    }

    display.CurX += Obj->oWidth;
}


/*
** This function getting called when the slave has been found
** Note : This will be called only once when we load the driver.
*/
 int etx_oled_probe(struct i2c_client *client,
                          const struct i2c_device_id *id)
{
    SSD1306_DisplayInit();
    printk("%d", ds.min);
    //fill the OLED with this data
    // SSD1306_Fill(0xFF);

    clearScreen();
    setPosition(0, 0);
    drawBitmap(&LogoHUST, white);
    updateScreen();
    msleep(3000);
    clearScreen();
    setPosition(0, 0);
    drawBitmap(&Teacher, white);
    updateScreen();
    msleep(3000);
    clearScreen();
    setPosition(3, 30);

    putString("Welcome!", &Font1118, white);
    updateScreen();
    clearScreen();
    setPosition(15, 30);    
    msleep(1000);
    // putChar('C', &Font1118, white);
    

    pr_info("OLED Probed!!!\n");

    return 0;
}

/*
** This function getting called when the slave has been removed
** Note : This will be called only once when we unload the driver.
*/
 int etx_oled_remove(struct i2c_client *client)
{
    //fill the OLED with this data
    // SSD1306_Fill(0x00);
    clearScreen();
    updateScreen();

    printk("OLED Removed!!!\n");
    return 0;
}

/*
** Structure that has slave device id
*/
 const struct i2c_device_id etx_oled_id[] = {
    {SLAVE_DEVICE_NAME, 0},
    {}};
MODULE_DEVICE_TABLE(i2c, etx_oled_id);

/*
** I2C driver Structure that has to be added to linux
*/
 struct i2c_driver etx_oled_driver = {
    .driver = {
        .name = SLAVE_DEVICE_NAME,
        .owner = THIS_MODULE,
    },
    .probe = etx_oled_probe,
    .remove = etx_oled_remove,
    .id_table = etx_oled_id,
};

/*
** I2C Board Info strucutre
*/
 struct i2c_board_info oled_i2c_board_info = {
    I2C_BOARD_INFO(SLAVE_DEVICE_NAME, SSD1306_SLAVE_ADDR)};

/*
** Module Init function
*/
 int __init etx_driver_init(void)
{
    int ret = -1;
    etx_i2c_adapter = i2c_get_adapter(I2C_BUS_AVAILABLE);

    if (etx_i2c_adapter != NULL)
    {
        etx_i2c_client_oled = i2c_new_client_device(etx_i2c_adapter, &oled_i2c_board_info);

        if (etx_i2c_client_oled != NULL)
        {
            i2c_add_driver(&etx_oled_driver);
            ret = 0;
        }

        i2c_put_adapter(etx_i2c_adapter);
    }

    printk("Driver Added!!!\n");

    etx_thread = kthread_create(thread_function, NULL, "eTx Thread");
    if (etx_thread)
    {
        wake_up_process(etx_thread);
    }
    else
    {
        pr_err("Cannot create kthread\n");
    }

    return ret;
}

/*
** Module Exit function
*/
void __exit etx_driver_exit(void)
{
    i2c_unregister_device(etx_i2c_client_oled);
    i2c_del_driver(&etx_oled_driver);
    //pr_info("Driver Removed!!!\n");
    printk("Driver Removed!!!\n");
}

module_init(etx_driver_init);
module_exit(etx_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("NHOM 5");
MODULE_DESCRIPTION("Simple I2C driver explanation (SSD_1306 OLED Display Interface)");
MODULE_VERSION("1.34");
