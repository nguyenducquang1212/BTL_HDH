/*
 * ds1307.c
 *
 *  Created on: Aug 18, 2021
 *      Author: Quang Anh
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/i2c.h>
#include <linux/delay.h>
#include <linux/kernel.h>
#include <linux/time.h>
#include <linux/string.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/time64.h>
#include <linux/time.h>
#include <linux/ktime.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/slab.h>    //kmalloc()
#include <linux/uaccess.h> //copy_to/from_user()
#include <linux/kthread.h> //kernel threads
#include <linux/sched.h>   //task_struct
#include <linux/delay.h>


#include "ds1307.h"

#define I2C_BUS_AVAILABLE (1)         // I2C Bus available in our Raspberry Pi
#define SLAVE_DEVICE_NAME ("ETX_RTC") // Device and Driver Name
#define DS1307_SLAVE_ADDR (0x68)      // DS1307 OLED Slave Address

static struct i2c_adapter *etx_i2c_adapter = NULL;   // I2C Adapter Structure
static struct i2c_client *etx_i2c_client_rtc = NULL; // I2C Client Structure (In our case it is RTC)

struct timespec64 t;
struct tm br;


static struct task_struct *etx_thread;

#define toDEC(c) ((c >> 4) * 10 + (c & 0x0F))
#define toBCD(c) ((c / 10) << 4 | (c % 10))

DS1307_t ds;
EXPORT_SYMBOL(ds);
static void DS1307_getTime(DS1307_t *ds1307);

int thread_function(void *pv)
{
    // int i = 0;

    while (!kthread_should_stop())
    {
        DS1307_getTime(&ds);

        printk("%d - %d - %d ", ds.date, ds.month, ds.year);
        printk("%d:%d:%d", ds.hour, ds.min, ds.sec);
        msleep(1000);
    }
    return 0;
}


static void DS1307_setTime(DS1307_t *ds1307, uint8_t sec, uint8_t min, uint8_t hour, uint8_t date, uint8_t month, uint8_t year)
{
    ds1307->buffer[0] = 0x00; // Secs register address
    ds1307->buffer[1] = toBCD(sec);
    ds1307->buffer[2] = toBCD(min);
    ds1307->buffer[3] = toBCD(hour);

    ds1307->buffer[5] = toBCD(date);
    ds1307->buffer[6] = toBCD(month);
    ds1307->buffer[7] = toBCD(year);

    i2c_master_send(etx_i2c_client_rtc, ds1307->buffer, 8);
    // msleep(10);
}

static void DS1307_getTime(DS1307_t *ds1307)
{

    ds1307->buffer[0] = 0x00; // Secs register address
    i2c_master_send(etx_i2c_client_rtc, ds1307->buffer, 1);

    i2c_master_recv(etx_i2c_client_rtc, ds1307->buffer, 7);

    ds1307->sec = toDEC(ds1307->buffer[0]);
    ds1307->min = toDEC(ds1307->buffer[1]);
    ds1307->hour = toDEC(ds1307->buffer[2]);

    ds1307->day = toDEC(ds1307->buffer[3]);
    ds1307->date = toDEC(ds1307->buffer[4]);
    ds1307->month = toDEC(ds1307->buffer[5]);
    ds1307->year = toDEC(ds1307->buffer[6]);
}


void RTC_Init(void)
{
    uint8_t data_reg[2] = {0, 0};

    i2c_master_send(etx_i2c_client_rtc, &data_reg[0], 1);

    i2c_master_recv(etx_i2c_client_rtc, &data_reg[1], 1);

    data_reg[1] &= 0x7F;

    i2c_master_send(etx_i2c_client_rtc, data_reg, 2);

    data_reg[0] = 0x02;

    i2c_master_send(etx_i2c_client_rtc, &data_reg[0], 1);

    i2c_master_recv(etx_i2c_client_rtc, &data_reg[1], 1);

    data_reg[1] &= 0xBF;

    i2c_master_send(etx_i2c_client_rtc, data_reg, 2);
}

/*
** This function getting called when the slave has been found
** Note : This will be called only once when we load the driver.
*/
static int etx_rtc_probe(struct i2c_client *client,
                         const struct i2c_device_id *id)
{
    RTC_Init();

    // struct tm *tm;

    // tm = gmtime(&st.st_mtim.tv_sec);

    // DS1307_setTime(&ds, tm->tm_sec, tm->tm_min, tm->tm_hour, tm->tm_mday, tm->tm_mon, tm->tm_year - 100);
   
    ktime_get_real_ts64(&t);

    time64_to_tm(t.tv_sec, 0, &br);
    // printk("%d - %d - %d - %d day", br.date, ds.month, ds.year, ds.day);
    DS1307_setTime(&ds, br.tm_sec, br.tm_min, br.tm_hour+7, br.tm_mday, br.tm_mon+1, br.tm_year-100);

    printk("OLED Probed!!!\n");

    // DS1307_getTime(&ds);

    // printk("%d - %d - %d - %d day", ds.date, ds.month, ds.year, ds.day);
    // printk("%d:%d:%d", ds.hour, ds.min, ds.sec);

    // msleep(3000);

    // DS1307_getTime(&ds);
    // printk("%d - %d - %d - %d day", ds.date, ds.month, ds.year, ds.day);
    // printk("%d:%d:%d", ds.hour, ds.min, ds.sec);

    return 0;
}



/*
** This function getting called when the slave has been removed
** Note : This will be called only once when we unload the driver.
*/
static int etx_rtc_remove(struct i2c_client *client)
{
    printk("OLED Removed!!!\n");
    return 0;
}

/*
** Structure that has slave device id
*/
static const struct i2c_device_id etx_rtc_id[] = {
    {SLAVE_DEVICE_NAME, 0},
    {}};
MODULE_DEVICE_TABLE(i2c, etx_rtc_id);

/*
** I2C driver Structure that has to be added to linux
*/
static struct i2c_driver etx_rtc_driver = {
    .driver = {
        .name = SLAVE_DEVICE_NAME,
        .owner = THIS_MODULE,
    },
    .probe = etx_rtc_probe,
    .remove = etx_rtc_remove,
    .id_table = etx_rtc_id,
};

/*
** I2C Board Info strucutre
*/
static struct i2c_board_info rtc_i2c_board_info = {
    I2C_BOARD_INFO(SLAVE_DEVICE_NAME, DS1307_SLAVE_ADDR)};

/*
** Module Init function
*/
static int __init etx_driver_init(void)
{
    int ret = -1;
    etx_i2c_adapter = i2c_get_adapter(I2C_BUS_AVAILABLE);

    if (etx_i2c_adapter != NULL)
    {
        etx_i2c_client_rtc = i2c_new_client_device(etx_i2c_adapter, &rtc_i2c_board_info);

        if (etx_i2c_client_rtc != NULL)
        {
            i2c_add_driver(&etx_rtc_driver);
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

    // while (1)
    // {
    //     DS1307_getTime(&ds);

    //     printk("%d - %d - %d - %d day", ds.date, ds.month, ds.year, ds.day);
    //     printk("%d:%d:%d", ds.hour, ds.min, ds.sec);

    //     msleep(1000);
    // }
    return ret;
}

/*
** Module Exit function
*/
static void __exit etx_driver_exit(void)
{
    i2c_unregister_device(etx_i2c_client_rtc);
    i2c_del_driver(&etx_rtc_driver);
    printk("Driver Removed!!!\n");
}

module_init(etx_driver_init);
module_exit(etx_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nhom 5");
MODULE_DESCRIPTION("Simple I2C driver explanation (SSD_1306 OLED Display Interface)");
MODULE_VERSION("1.34");