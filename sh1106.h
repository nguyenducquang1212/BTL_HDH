// #include "stdint.h"
#include <linux/types.h>

#define _HEIGHT 64
#define _WIDTH 132
#define _BUFFER_SIZE _WIDTH *_HEIGHT / 8

#define CHARGEPUMP 0x8D
#define COLUMNADDR 0x21
#define COMSCANDEC 0xC8
#define COMSCANINC 0xC0
#define DISPLAYALLON 0xA5
#define DISPLAY_ALL_ON_RESUME 0xA4
#define DISPLAYOFF 0xAE
#define DISPLAYON 0xAF
#define EXTERNALVCC 0x1
#define INVERTDISPLAY 0xA7
#define MEMORYMODE 0x20
#define NORMALDISPLAY 0xA6
#define PAGEADDR 0x22
#define SEGREMAP 0xA0
#define SETCOMPINS 0xDA
#define SETCONTRAST 0x81
#define SETDISPLAYCLOCKDIV 0xD5
#define SETDISPLAYOFFSET 0xD3
#define SETHIGHCOLUMN 0x10
#define SETLOWCOLUMN 0x00
#define SETMULTIPLEX 0xA8
#define SETPRECHARGE 0xD9
#define SETSEGMENTREMAP 0xA1
#define SETSTARTLINE 0x40
#define SETVCOMDESELECT 0xDB

typedef struct sSSH1106
{
	uint8_t buffer [_BUFFER_SIZE];
	uint8_t CurX;
	uint8_t CurY;
} SSH1106_t;

typedef struct sObjects
{
	uint8_t oWidth;
	uint8_t oHeight;
	const uint16_t *data;

	// them struct cho font 16 26 va 11 18 su dung 16 bits, cac object khac dung 8 bits
} Objects_t;

typedef enum eColor
{
	white = 0,
	black,
} Color_t;

extern Objects_t Font1118;

extern Objects_t Font710;


const uint16_t Font11x18[] =
	{
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, // sp
		0x0000, 0x0C00, 0x0C00, 0x0C00, 0x0C00, 0x0C00, 0x0C00, 0x0C00, 0x0C00, 0x0C00,
		0x0C00, 0x0C00, 0x0000, 0x0C00, 0x0C00, 0x0000, 0x0000,
		0x0000, // !
		0x0000, 0x1B00, 0x1B00, 0x1B00, 0x1B00, 0x1B00, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, // "
		0x0000, 0x1980, 0x1980, 0x1980, 0x1980, 0x7FC0, 0x7FC0, 0x1980, 0x3300, 0x7FC0,
		0x7FC0, 0x3300, 0x3300, 0x3300, 0x3300, 0x0000, 0x0000,
		0x0000, // #
		0x0000, 0x1E00, 0x3F00, 0x7580, 0x6580, 0x7400, 0x3C00, 0x1E00, 0x0700, 0x0580,
		0x6580, 0x6580, 0x7580, 0x3F00, 0x1E00, 0x0400, 0x0400,
		0x0000, // $
		0x0000, 0x7000, 0xD800, 0xD840, 0xD8C0, 0xD980, 0x7300, 0x0600, 0x0C00, 0x1B80,
		0x36C0, 0x66C0, 0x46C0, 0x06C0, 0x0380, 0x0000, 0x0000,
		0x0000, // %
		0x0000, 0x1E00, 0x3F00, 0x3300, 0x3300, 0x3300, 0x1E00, 0x0C00, 0x3CC0, 0x66C0,
		0x6380, 0x6180, 0x6380, 0x3EC0, 0x1C80, 0x0000, 0x0000,
		0x0000, // &
		0x0000, 0x0C00, 0x0C00, 0x0C00, 0x0C00, 0x0C00, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, // '
		0x0080, 0x0100, 0x0300, 0x0600, 0x0600, 0x0400, 0x0C00, 0x0C00, 0x0C00, 0x0C00,
		0x0C00, 0x0C00, 0x0400, 0x0600, 0x0600, 0x0300, 0x0100,
		0x0080, // (
		0x2000, 0x1000, 0x1800, 0x0C00, 0x0C00, 0x0400, 0x0600, 0x0600, 0x0600, 0x0600,
		0x0600, 0x0600, 0x0400, 0x0C00, 0x0C00, 0x1800, 0x1000,
		0x2000, // )
		0x0000, 0x0C00, 0x2D00, 0x3F00, 0x1E00, 0x3300, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, // *
		0x0000, 0x0000, 0x0000, 0x0C00, 0x0C00, 0x0C00, 0x0C00, 0xFFC0, 0xFFC0, 0x0C00,
		0x0C00, 0x0C00, 0x0C00, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, // +
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0C00, 0x0C00, 0x0400, 0x0400,
		0x0800, // ,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1E00,
		0x1E00, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, // -
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0C00, 0x0C00, 0x0000, 0x0000,
		0x0000, // .
		0x0000, 0x0300, 0x0300, 0x0300, 0x0600, 0x0600, 0x0600, 0x0600, 0x0C00, 0x0C00,
		0x0C00, 0x0C00, 0x1800, 0x1800, 0x1800, 0x0000, 0x0000,
		0x0000, // /
		0x0000, 0x1E00, 0x3F00, 0x3300, 0x6180, 0x6180, 0x6180, 0x6D80, 0x6D80, 0x6180,
		0x6180, 0x6180, 0x3300, 0x3F00, 0x1E00, 0x0000, 0x0000, 0x0000, // 0
		0x0000, 0x0600, 0x0E00, 0x1E00, 0x3600, 0x2600, 0x0600, 0x0600, 0x0600, 0x0600,
		0x0600, 0x0600, 0x0600, 0x0600, 0x0600, 0x0000, 0x0000, 0x0000, // 1
		0x0000, 0x1E00, 0x3F00, 0x7380, 0x6180, 0x6180, 0x0180, 0x0300, 0x0600, 0x0C00,
		0x1800, 0x3000, 0x6000, 0x7F80, 0x7F80, 0x0000, 0x0000, 0x0000, // 2
		0x0000, 0x1C00, 0x3E00, 0x6300, 0x6300, 0x0300, 0x0E00, 0x0E00, 0x0300, 0x0180,
		0x0180, 0x6180, 0x7380, 0x3F00, 0x1E00, 0x0000, 0x0000, 0x0000, // 3
		0x0000, 0x0600, 0x0E00, 0x0E00, 0x1E00, 0x1E00, 0x1600, 0x3600, 0x3600, 0x6600,
		0x7F80, 0x7F80, 0x0600, 0x0600, 0x0600, 0x0000, 0x0000, 0x0000, // 4
		0x0000, 0x7F00, 0x7F00, 0x6000, 0x6000, 0x6000, 0x6E00, 0x7F00, 0x6380, 0x0180,
		0x0180, 0x6180, 0x7380, 0x3F00, 0x1E00, 0x0000, 0x0000, 0x0000, // 5
		0x0000, 0x1E00, 0x3F00, 0x3380, 0x6180, 0x6000, 0x6E00, 0x7F00, 0x7380, 0x6180,
		0x6180, 0x6180, 0x3380, 0x3F00, 0x1E00, 0x0000, 0x0000, 0x0000, // 6
		0x0000, 0x7F80, 0x7F80, 0x0180, 0x0300, 0x0300, 0x0600, 0x0600, 0x0C00, 0x0C00,
		0x0C00, 0x0800, 0x1800, 0x1800, 0x1800, 0x0000, 0x0000, 0x0000, // 7
		0x0000, 0x1E00, 0x3F00, 0x6380, 0x6180, 0x6180, 0x2100, 0x1E00, 0x3F00, 0x6180,
		0x6180, 0x6180, 0x6180, 0x3F00, 0x1E00, 0x0000, 0x0000, 0x0000, // 8
		0x0000, 0x1E00, 0x3F00, 0x7300, 0x6180, 0x6180, 0x6180, 0x7380, 0x3F80, 0x1D80,
		0x0180, 0x6180, 0x7300, 0x3F00, 0x1E00, 0x0000, 0x0000, 0x0000, // 9
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0C00, 0x0C00, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0C00, 0x0C00, 0x0000, 0x0000, 0x0000, // :
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0C00, 0x0C00, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0C00, 0x0C00, 0x0400, 0x0400, 0x0800, // ;
		0x0000, 0x0000, 0x0000, 0x0000, 0x0080, 0x0380, 0x0E00, 0x3800, 0x6000, 0x3800,
		0x0E00, 0x0380, 0x0080, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, // <
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x7F80, 0x7F80, 0x0000, 0x0000, 0x7F80,
		0x7F80, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, // =
		0x0000, 0x0000, 0x0000, 0x0000, 0x4000, 0x7000, 0x1C00, 0x0700, 0x0180, 0x0700,
		0x1C00, 0x7000, 0x4000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, // >
		0x0000, 0x1F00, 0x3F80, 0x71C0, 0x60C0, 0x00C0, 0x01C0, 0x0380, 0x0700, 0x0E00,
		0x0C00, 0x0C00, 0x0000, 0x0C00, 0x0C00, 0x0000, 0x0000, 0x0000, // ?
		0x0000, 0x1E00, 0x3F00, 0x3180, 0x7180, 0x6380, 0x6F80, 0x6D80, 0x6D80, 0x6F80,
		0x6780, 0x6000, 0x3200, 0x3E00, 0x1C00, 0x0000, 0x0000, 0x0000, // @
		0x0000, 0x0E00, 0x0E00, 0x1B00, 0x1B00, 0x1B00, 0x1B00, 0x3180, 0x3180, 0x3F80,
		0x3F80, 0x3180, 0x60C0, 0x60C0, 0x60C0, 0x0000, 0x0000, 0x0000, // A
		0x0000, 0x7C00, 0x7E00, 0x6300, 0x6300, 0x6300, 0x6300, 0x7E00, 0x7E00, 0x6300,
		0x6180, 0x6180, 0x6380, 0x7F00, 0x7E00, 0x0000, 0x0000, 0x0000, // B
		0x0000, 0x1E00, 0x3F00, 0x3180, 0x6180, 0x6000, 0x6000, 0x6000, 0x6000, 0x6000,
		0x6000, 0x6180, 0x3180, 0x3F00, 0x1E00, 0x0000, 0x0000, 0x0000, // C
		0x0000, 0x7C00, 0x7F00, 0x6300, 0x6380, 0x6180, 0x6180, 0x6180, 0x6180, 0x6180,
		0x6180, 0x6300, 0x6300, 0x7E00, 0x7C00, 0x0000, 0x0000, 0x0000, // D
		0x0000, 0x7F80, 0x7F80, 0x6000, 0x6000, 0x6000, 0x6000, 0x7F00, 0x7F00, 0x6000,
		0x6000, 0x6000, 0x6000, 0x7F80, 0x7F80, 0x0000, 0x0000, 0x0000, // E
		0x0000, 0x7F80, 0x7F80, 0x6000, 0x6000, 0x6000, 0x6000, 0x7F00, 0x7F00, 0x6000,
		0x6000, 0x6000, 0x6000, 0x6000, 0x6000, 0x0000, 0x0000, 0x0000, // F
		0x0000, 0x1E00, 0x3F00, 0x3180, 0x6180, 0x6000, 0x6000, 0x6000, 0x6380, 0x6380,
		0x6180, 0x6180, 0x3180, 0x3F80, 0x1E00, 0x0000, 0x0000, 0x0000, // G
		0x0000, 0x6180, 0x6180, 0x6180, 0x6180, 0x6180, 0x6180, 0x7F80, 0x7F80, 0x6180,
		0x6180, 0x6180, 0x6180, 0x6180, 0x6180, 0x0000, 0x0000, 0x0000, // H
		0x0000, 0x3F00, 0x3F00, 0x0C00, 0x0C00, 0x0C00, 0x0C00, 0x0C00, 0x0C00, 0x0C00,
		0x0C00, 0x0C00, 0x0C00, 0x3F00, 0x3F00, 0x0000, 0x0000, 0x0000, // I
		0x0000, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180, 0x0180,
		0x6180, 0x6180, 0x7380, 0x3F00, 0x1E00, 0x0000, 0x0000, 0x0000, // J
		0x0000, 0x60C0, 0x6180, 0x6300, 0x6600, 0x6600, 0x6C00, 0x7800, 0x7C00, 0x6600,
		0x6600, 0x6300, 0x6180, 0x6180, 0x60C0, 0x0000, 0x0000, 0x0000, // K
		0x0000, 0x6000, 0x6000, 0x6000, 0x6000, 0x6000, 0x6000, 0x6000, 0x6000, 0x6000,
		0x6000, 0x6000, 0x6000, 0x7F80, 0x7F80, 0x0000, 0x0000, 0x0000, // L
		0x0000, 0x71C0, 0x71C0, 0x7BC0, 0x7AC0, 0x6AC0, 0x6AC0, 0x6EC0, 0x64C0, 0x60C0,
		0x60C0, 0x60C0, 0x60C0, 0x60C0, 0x60C0, 0x0000, 0x0000, 0x0000, // M
		0x0000, 0x7180, 0x7180, 0x7980, 0x7980, 0x7980, 0x6D80, 0x6D80, 0x6D80, 0x6580,
		0x6780, 0x6780, 0x6780, 0x6380, 0x6380, 0x0000, 0x0000, 0x0000, // N
		0x0000, 0x1E00, 0x3F00, 0x3300, 0x6180, 0x6180, 0x6180, 0x6180, 0x6180, 0x6180,
		0x6180, 0x6180, 0x3300, 0x3F00, 0x1E00, 0x0000, 0x0000, 0x0000, // O
		0x0000, 0x7E00, 0x7F00, 0x6380, 0x6180, 0x6180, 0x6180, 0x6380, 0x7F00, 0x7E00,
		0x6000, 0x6000, 0x6000, 0x6000, 0x6000, 0x0000, 0x0000, 0x0000, // P
		0x0000, 0x1E00, 0x3F00, 0x3300, 0x6180, 0x6180, 0x6180, 0x6180, 0x6180, 0x6180,
		0x6580, 0x6780, 0x3300, 0x3F80, 0x1E40, 0x0000, 0x0000, 0x0000, // Q
		0x0000, 0x7E00, 0x7F00, 0x6380, 0x6180, 0x6180, 0x6380, 0x7F00, 0x7E00, 0x6600,
		0x6300, 0x6300, 0x6180, 0x6180, 0x60C0, 0x0000, 0x0000, 0x0000, // R
		0x0000, 0x0E00, 0x1F00, 0x3180, 0x3180, 0x3000, 0x3800, 0x1E00, 0x0700, 0x0380,
		0x6180, 0x6180, 0x3180, 0x3F00, 0x1E00, 0x0000, 0x0000, 0x0000, // S
		0x0000, 0xFFC0, 0xFFC0, 0x0C00, 0x0C00, 0x0C00, 0x0C00, 0x0C00, 0x0C00, 0x0C00,
		0x0C00, 0x0C00, 0x0C00, 0x0C00, 0x0C00, 0x0000, 0x0000, 0x0000, // T
		0x0000, 0x6180, 0x6180, 0x6180, 0x6180, 0x6180, 0x6180, 0x6180, 0x6180, 0x6180,
		0x6180, 0x6180, 0x7380, 0x3F00, 0x1E00, 0x0000, 0x0000, 0x0000, // U
		0x0000, 0x60C0, 0x60C0, 0x60C0, 0x3180, 0x3180, 0x3180, 0x1B00, 0x1B00, 0x1B00,
		0x1B00, 0x0E00, 0x0E00, 0x0E00, 0x0400, 0x0000, 0x0000, 0x0000, // V
		0x0000, 0xC0C0, 0xC0C0, 0xC0C0, 0xC0C0, 0xC0C0, 0xCCC0, 0x4C80, 0x4C80, 0x5E80,
		0x5280, 0x5280, 0x7380, 0x6180, 0x6180, 0x0000, 0x0000, 0x0000, // W
		0x0000, 0xC0C0, 0x6080, 0x6180, 0x3300, 0x3B00, 0x1E00, 0x0C00, 0x0C00, 0x1E00,
		0x1F00, 0x3B00, 0x7180, 0x6180, 0xC0C0, 0x0000, 0x0000, 0x0000, // X
		0x0000, 0xC0C0, 0x6180, 0x6180, 0x3300, 0x3300, 0x1E00, 0x1E00, 0x0C00, 0x0C00,
		0x0C00, 0x0C00, 0x0C00, 0x0C00, 0x0C00, 0x0000, 0x0000, 0x0000, // Y
		0x0000, 0x3F80, 0x3F80, 0x0180, 0x0300, 0x0300, 0x0600, 0x0C00, 0x0C00, 0x1800,
		0x1800, 0x3000, 0x6000, 0x7F80, 0x7F80, 0x0000, 0x0000, 0x0000, // Z
		0x0F00, 0x0F00, 0x0C00, 0x0C00, 0x0C00, 0x0C00, 0x0C00, 0x0C00, 0x0C00, 0x0C00,
		0x0C00, 0x0C00, 0x0C00, 0x0C00, 0x0C00, 0x0C00, 0x0F00, 0x0F00, // [
		0x0000, 0x1800, 0x1800, 0x1800, 0x0C00, 0x0C00, 0x0C00, 0x0C00, 0x0600, 0x0600,
		0x0600, 0x0600, 0x0300, 0x0300, 0x0300, 0x0000, 0x0000, 0x0000, /* \ */
		0x1E00, 0x1E00, 0x0600, 0x0600, 0x0600, 0x0600, 0x0600, 0x0600, 0x0600, 0x0600,
		0x0600, 0x0600, 0x0600, 0x0600, 0x0600, 0x0600, 0x1E00,
		0x1E00, // ]
		0x0000, 0x0C00, 0x0C00, 0x1E00, 0x1200, 0x3300, 0x3300, 0x6180, 0x6180, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, // ^
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFE0, 0x0000, // _
		0x0000, 0x3800, 0x1800, 0x0C00, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, // `
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1F00, 0x3F80, 0x6180, 0x0180, 0x1F80,
		0x3F80, 0x6180, 0x6380, 0x7F80, 0x38C0, 0x0000, 0x0000, 0x0000, // a
		0x0000, 0x6000, 0x6000, 0x6000, 0x6000, 0x6E00, 0x7F00, 0x7380, 0x6180, 0x6180,
		0x6180, 0x6180, 0x7380, 0x7F00, 0x6E00, 0x0000, 0x0000, 0x0000, // b
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1E00, 0x3F00, 0x7380, 0x6180, 0x6000,
		0x6000, 0x6180, 0x7380, 0x3F00, 0x1E00, 0x0000, 0x0000, 0x0000, // c
		0x0000, 0x0180, 0x0180, 0x0180, 0x0180, 0x1D80, 0x3F80, 0x7380, 0x6180, 0x6180,
		0x6180, 0x6180, 0x7380, 0x3F80, 0x1D80, 0x0000, 0x0000, 0x0000, // d
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1E00, 0x3F00, 0x7300, 0x6180, 0x7F80,
		0x7F80, 0x6000, 0x7180, 0x3F00, 0x1E00, 0x0000, 0x0000, 0x0000, // e
		0x0000, 0x07C0, 0x0FC0, 0x0C00, 0x0C00, 0x7F80, 0x7F80, 0x0C00, 0x0C00, 0x0C00,
		0x0C00, 0x0C00, 0x0C00, 0x0C00, 0x0C00, 0x0000, 0x0000, 0x0000, // f
		0x0000, 0x0000, 0x0000, 0x0000, 0x1D80, 0x3F80, 0x7380, 0x6180, 0x6180, 0x6180,
		0x6180, 0x7380, 0x3F80, 0x1D80, 0x0180, 0x6380, 0x7F00, 0x3E00, // g
		0x0000, 0x6000, 0x6000, 0x6000, 0x6000, 0x6F00, 0x7F80, 0x7180, 0x6180, 0x6180,
		0x6180, 0x6180, 0x6180, 0x6180, 0x6180, 0x0000, 0x0000, 0x0000, // h
		0x0000, 0x0600, 0x0600, 0x0000, 0x0000, 0x3E00, 0x3E00, 0x0600, 0x0600, 0x0600,
		0x0600, 0x0600, 0x0600, 0x0600, 0x0600, 0x0000, 0x0000, 0x0000, // i
		0x0600, 0x0600, 0x0000, 0x0000, 0x3E00, 0x3E00, 0x0600, 0x0600, 0x0600, 0x0600,
		0x0600, 0x0600, 0x0600, 0x0600, 0x0600, 0x4600, 0x7E00, 0x3C00, // j
		0x0000, 0x6000, 0x6000, 0x6000, 0x6000, 0x6180, 0x6300, 0x6600, 0x6C00, 0x7C00,
		0x7600, 0x6300, 0x6300, 0x6180, 0x60C0, 0x0000, 0x0000, 0x0000, // k
		0x0000, 0x3E00, 0x3E00, 0x0600, 0x0600, 0x0600, 0x0600, 0x0600, 0x0600, 0x0600,
		0x0600, 0x0600, 0x0600, 0x0600, 0x0600, 0x0000, 0x0000, 0x0000, // l
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xDD80, 0xFFC0, 0xCEC0, 0xCCC0, 0xCCC0,
		0xCCC0, 0xCCC0, 0xCCC0, 0xCCC0, 0xCCC0, 0x0000, 0x0000, 0x0000, // m
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x6F00, 0x7F80, 0x7180, 0x6180, 0x6180,
		0x6180, 0x6180, 0x6180, 0x6180, 0x6180, 0x0000, 0x0000, 0x0000, // n
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1E00, 0x3F00, 0x7380, 0x6180, 0x6180,
		0x6180, 0x6180, 0x7380, 0x3F00, 0x1E00, 0x0000, 0x0000, 0x0000, // o
		0x0000, 0x0000, 0x0000, 0x0000, 0x6E00, 0x7F00, 0x7380, 0x6180, 0x6180, 0x6180,
		0x6180, 0x7380, 0x7F00, 0x6E00, 0x6000, 0x6000, 0x6000, 0x6000, // p
		0x0000, 0x0000, 0x0000, 0x0000, 0x1D80, 0x3F80, 0x7380, 0x6180, 0x6180, 0x6180,
		0x6180, 0x7380, 0x3F80, 0x1D80, 0x0180, 0x0180, 0x0180, 0x0180, // q
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x6700, 0x3F80, 0x3900, 0x3000, 0x3000,
		0x3000, 0x3000, 0x3000, 0x3000, 0x3000, 0x0000, 0x0000, 0x0000, // r
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1E00, 0x3F80, 0x6180, 0x6000, 0x7F00,
		0x3F80, 0x0180, 0x6180, 0x7F00, 0x1E00, 0x0000, 0x0000, 0x0000, // s
		0x0000, 0x0000, 0x0800, 0x1800, 0x1800, 0x7F00, 0x7F00, 0x1800, 0x1800, 0x1800,
		0x1800, 0x1800, 0x1800, 0x1F80, 0x0F80, 0x0000, 0x0000, 0x0000, // t
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x6180, 0x6180, 0x6180, 0x6180, 0x6180,
		0x6180, 0x6180, 0x6380, 0x7F80, 0x3D80, 0x0000, 0x0000, 0x0000, // u
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x60C0, 0x3180, 0x3180, 0x3180, 0x1B00,
		0x1B00, 0x1B00, 0x0E00, 0x0E00, 0x0600, 0x0000, 0x0000, 0x0000, // v
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xDD80, 0xDD80, 0xDD80, 0x5500, 0x5500,
		0x5500, 0x7700, 0x7700, 0x2200, 0x2200, 0x0000, 0x0000, 0x0000, // w
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x6180, 0x3300, 0x3300, 0x1E00, 0x0C00,
		0x0C00, 0x1E00, 0x3300, 0x3300, 0x6180, 0x0000, 0x0000, 0x0000, // x
		0x0000, 0x0000, 0x0000, 0x0000, 0x6180, 0x6180, 0x3180, 0x3300, 0x3300, 0x1B00,
		0x1B00, 0x1B00, 0x0E00, 0x0E00, 0x0E00, 0x1C00, 0x7C00, 0x7000, // y
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x7FC0, 0x7FC0, 0x0180, 0x0300, 0x0600,
		0x0C00, 0x1800, 0x3000, 0x7FC0, 0x7FC0, 0x0000, 0x0000, 0x0000, // z
		0x0380, 0x0780, 0x0600, 0x0600, 0x0600, 0x0600, 0x0600, 0x0E00, 0x1C00, 0x1C00,
		0x0E00, 0x0600, 0x0600, 0x0600, 0x0600, 0x0600, 0x0780, 0x0380, // {
		0x0600, 0x0600, 0x0600, 0x0600, 0x0600, 0x0600, 0x0600, 0x0600, 0x0600, 0x0600,
		0x0600, 0x0600, 0x0600, 0x0600, 0x0600, 0x0600, 0x0600, 0x0600, // |
		0x3800, 0x3C00, 0x0C00, 0x0C00, 0x0C00, 0x0C00, 0x0C00, 0x0E00, 0x0700, 0x0700,
		0x0E00, 0x0C00, 0x0C00, 0x0C00, 0x0C00, 0x0C00, 0x3C00, 0x3800, // }
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3880, 0x7F80, 0x4700,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, // ~
																		
};

const uint16_t Font7x10[] =
	{
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, // sp
		0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x0000, 0x1000, 0x0000, 0x0000, // !
		0x2800, 0x2800, 0x2800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, // "
		0x2400, 0x2400, 0x7C00, 0x2400, 0x4800, 0x7C00, 0x4800, 0x4800, 0x0000, 0x0000, // #
		0x3800, 0x5400, 0x5000, 0x3800, 0x1400, 0x5400, 0x5400, 0x3800, 0x1000, 0x0000, // $
		0x2000, 0x5400, 0x5800, 0x3000, 0x2800, 0x5400, 0x1400, 0x0800, 0x0000, 0x0000, // %
		0x1000, 0x2800, 0x2800, 0x1000, 0x3400, 0x4800, 0x4800, 0x3400, 0x0000, 0x0000, // &
		0x1000, 0x1000, 0x1000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, // '
		0x0800, 0x1000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x2000, 0x1000, 0x0800, // (
		0x2000, 0x1000, 0x0800, 0x0800, 0x0800, 0x0800, 0x0800, 0x0800, 0x1000, 0x2000, // )
		0x1000, 0x3800, 0x1000, 0x2800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, // *
		0x0000, 0x0000, 0x1000, 0x1000, 0x7C00, 0x1000, 0x1000, 0x0000, 0x0000, 0x0000, // +
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1000, 0x1000, 0x1000, // ,
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3800, 0x0000, 0x0000, 0x0000, 0x0000, // -
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1000, 0x0000, 0x0000, // .
		0x0800, 0x0800, 0x1000, 0x1000, 0x1000, 0x1000, 0x2000, 0x2000, 0x0000, 0x0000, // /
		0x3800, 0x4400, 0x4400, 0x5400, 0x4400, 0x4400, 0x4400, 0x3800, 0x0000, 0x0000, // 0
		0x1000, 0x3000, 0x5000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x0000, 0x0000, // 1
		0x3800, 0x4400, 0x4400, 0x0400, 0x0800, 0x1000, 0x2000, 0x7C00, 0x0000, 0x0000, // 2
		0x3800, 0x4400, 0x0400, 0x1800, 0x0400, 0x0400, 0x4400, 0x3800, 0x0000, 0x0000, // 3
		0x0800, 0x1800, 0x2800, 0x2800, 0x4800, 0x7C00, 0x0800, 0x0800, 0x0000, 0x0000, // 4
		0x7C00, 0x4000, 0x4000, 0x7800, 0x0400, 0x0400, 0x4400, 0x3800, 0x0000, 0x0000, // 5
		0x3800, 0x4400, 0x4000, 0x7800, 0x4400, 0x4400, 0x4400, 0x3800, 0x0000, 0x0000, // 6
		0x7C00, 0x0400, 0x0800, 0x1000, 0x1000, 0x2000, 0x2000, 0x2000, 0x0000, 0x0000, // 7
		0x3800, 0x4400, 0x4400, 0x3800, 0x4400, 0x4400, 0x4400, 0x3800, 0x0000, 0x0000, // 8
		0x3800, 0x4400, 0x4400, 0x4400, 0x3C00, 0x0400, 0x4400, 0x3800, 0x0000, 0x0000, // 9
		0x0000, 0x0000, 0x1000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1000, 0x0000, 0x0000, // :
		0x0000, 0x0000, 0x0000, 0x1000, 0x0000, 0x0000, 0x0000, 0x1000, 0x1000, 0x1000, // ;
		0x0000, 0x0000, 0x0C00, 0x3000, 0x4000, 0x3000, 0x0C00, 0x0000, 0x0000, 0x0000, // <
		0x0000, 0x0000, 0x0000, 0x7C00, 0x0000, 0x7C00, 0x0000, 0x0000, 0x0000, 0x0000, // =
		0x0000, 0x0000, 0x6000, 0x1800, 0x0400, 0x1800, 0x6000, 0x0000, 0x0000, 0x0000, // >
		0x3800, 0x4400, 0x0400, 0x0800, 0x1000, 0x1000, 0x0000, 0x1000, 0x0000, 0x0000, // ?
		0x3800, 0x4400, 0x4C00, 0x5400, 0x5C00, 0x4000, 0x4000, 0x3800, 0x0000, 0x0000, // @
		0x1000, 0x2800, 0x2800, 0x2800, 0x2800, 0x7C00, 0x4400, 0x4400, 0x0000, 0x0000, // A
		0x7800, 0x4400, 0x4400, 0x7800, 0x4400, 0x4400, 0x4400, 0x7800, 0x0000, 0x0000, // B
		0x3800, 0x4400, 0x4000, 0x4000, 0x4000, 0x4000, 0x4400, 0x3800, 0x0000, 0x0000, // C
		0x7000, 0x4800, 0x4400, 0x4400, 0x4400, 0x4400, 0x4800, 0x7000, 0x0000, 0x0000, // D
		0x7C00, 0x4000, 0x4000, 0x7C00, 0x4000, 0x4000, 0x4000, 0x7C00, 0x0000, 0x0000, // E
		0x7C00, 0x4000, 0x4000, 0x7800, 0x4000, 0x4000, 0x4000, 0x4000, 0x0000, 0x0000, // F
		0x3800, 0x4400, 0x4000, 0x4000, 0x5C00, 0x4400, 0x4400, 0x3800, 0x0000, 0x0000, // G
		0x4400, 0x4400, 0x4400, 0x7C00, 0x4400, 0x4400, 0x4400, 0x4400, 0x0000, 0x0000, // H
		0x3800, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x3800, 0x0000, 0x0000, // I
		0x0400, 0x0400, 0x0400, 0x0400, 0x0400, 0x0400, 0x4400, 0x3800, 0x0000, 0x0000, // J
		0x4400, 0x4800, 0x5000, 0x6000, 0x5000, 0x4800, 0x4800, 0x4400, 0x0000, 0x0000, // K
		0x4000, 0x4000, 0x4000, 0x4000, 0x4000, 0x4000, 0x4000, 0x7C00, 0x0000, 0x0000, // L
		0x4400, 0x6C00, 0x6C00, 0x5400, 0x4400, 0x4400, 0x4400, 0x4400, 0x0000, 0x0000, // M
		0x4400, 0x6400, 0x6400, 0x5400, 0x5400, 0x4C00, 0x4C00, 0x4400, 0x0000, 0x0000, // N
		0x3800, 0x4400, 0x4400, 0x4400, 0x4400, 0x4400, 0x4400, 0x3800, 0x0000, 0x0000, // O
		0x7800, 0x4400, 0x4400, 0x4400, 0x7800, 0x4000, 0x4000, 0x4000, 0x0000, 0x0000, // P
		0x3800, 0x4400, 0x4400, 0x4400, 0x4400, 0x4400, 0x5400, 0x3800, 0x0400, 0x0000, // Q
		0x7800, 0x4400, 0x4400, 0x4400, 0x7800, 0x4800, 0x4800, 0x4400, 0x0000, 0x0000, // R
		0x3800, 0x4400, 0x4000, 0x3000, 0x0800, 0x0400, 0x4400, 0x3800, 0x0000, 0x0000, // S
		0x7C00, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x0000, 0x0000, // T
		0x4400, 0x4400, 0x4400, 0x4400, 0x4400, 0x4400, 0x4400, 0x3800, 0x0000, 0x0000, // U
		0x4400, 0x4400, 0x4400, 0x2800, 0x2800, 0x2800, 0x1000, 0x1000, 0x0000, 0x0000, // V
		0x4400, 0x4400, 0x5400, 0x5400, 0x5400, 0x6C00, 0x2800, 0x2800, 0x0000, 0x0000, // W
		0x4400, 0x2800, 0x2800, 0x1000, 0x1000, 0x2800, 0x2800, 0x4400, 0x0000, 0x0000, // X
		0x4400, 0x4400, 0x2800, 0x2800, 0x1000, 0x1000, 0x1000, 0x1000, 0x0000, 0x0000, // Y
		0x7C00, 0x0400, 0x0800, 0x1000, 0x1000, 0x2000, 0x4000, 0x7C00, 0x0000, 0x0000, // Z
		0x1800, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1800, // [
		0x2000, 0x2000, 0x1000, 0x1000, 0x1000, 0x1000, 0x0800, 0x0800, 0x0000, 0x0000, /* \ */
		0x3000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x3000, // ]
		0x1000, 0x2800, 0x2800, 0x4400, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, // ^
		0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFE00, // _
		0x2000, 0x1000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, // `
		0x0000, 0x0000, 0x3800, 0x4400, 0x3C00, 0x4400, 0x4C00, 0x3400, 0x0000, 0x0000, // a
		0x4000, 0x4000, 0x5800, 0x6400, 0x4400, 0x4400, 0x6400, 0x5800, 0x0000, 0x0000, // b
		0x0000, 0x0000, 0x3800, 0x4400, 0x4000, 0x4000, 0x4400, 0x3800, 0x0000, 0x0000, // c
		0x0400, 0x0400, 0x3400, 0x4C00, 0x4400, 0x4400, 0x4C00, 0x3400, 0x0000, 0x0000, // d
		0x0000, 0x0000, 0x3800, 0x4400, 0x7C00, 0x4000, 0x4400, 0x3800, 0x0000, 0x0000, // e
		0x0C00, 0x1000, 0x7C00, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x0000, 0x0000, // f
		0x0000, 0x0000, 0x3400, 0x4C00, 0x4400, 0x4400, 0x4C00, 0x3400, 0x0400, 0x7800, // g
		0x4000, 0x4000, 0x5800, 0x6400, 0x4400, 0x4400, 0x4400, 0x4400, 0x0000, 0x0000, // h
		0x1000, 0x0000, 0x7000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x0000, 0x0000, // i
		0x1000, 0x0000, 0x7000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0xE000, // j
		0x4000, 0x4000, 0x4800, 0x5000, 0x6000, 0x5000, 0x4800, 0x4400, 0x0000, 0x0000, // k
		0x7000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x0000, 0x0000, // l
		0x0000, 0x0000, 0x7800, 0x5400, 0x5400, 0x5400, 0x5400, 0x5400, 0x0000, 0x0000, // m
		0x0000, 0x0000, 0x5800, 0x6400, 0x4400, 0x4400, 0x4400, 0x4400, 0x0000, 0x0000, // n
		0x0000, 0x0000, 0x3800, 0x4400, 0x4400, 0x4400, 0x4400, 0x3800, 0x0000, 0x0000, // o
		0x0000, 0x0000, 0x5800, 0x6400, 0x4400, 0x4400, 0x6400, 0x5800, 0x4000, 0x4000, // p
		0x0000, 0x0000, 0x3400, 0x4C00, 0x4400, 0x4400, 0x4C00, 0x3400, 0x0400, 0x0400, // q
		0x0000, 0x0000, 0x5800, 0x6400, 0x4000, 0x4000, 0x4000, 0x4000, 0x0000, 0x0000, // r
		0x0000, 0x0000, 0x3800, 0x4400, 0x3000, 0x0800, 0x4400, 0x3800, 0x0000, 0x0000, // s
		0x2000, 0x2000, 0x7800, 0x2000, 0x2000, 0x2000, 0x2000, 0x1800, 0x0000, 0x0000, // t
		0x0000, 0x0000, 0x4400, 0x4400, 0x4400, 0x4400, 0x4C00, 0x3400, 0x0000, 0x0000, // u
		0x0000, 0x0000, 0x4400, 0x4400, 0x2800, 0x2800, 0x2800, 0x1000, 0x0000, 0x0000, // v
		0x0000, 0x0000, 0x5400, 0x5400, 0x5400, 0x6C00, 0x2800, 0x2800, 0x0000, 0x0000, // w
		0x0000, 0x0000, 0x4400, 0x2800, 0x1000, 0x1000, 0x2800, 0x4400, 0x0000, 0x0000, // x
		0x0000, 0x0000, 0x4400, 0x4400, 0x2800, 0x2800, 0x1000, 0x1000, 0x1000, 0x6000, // y
		0x0000, 0x0000, 0x7C00, 0x0800, 0x1000, 0x2000, 0x4000, 0x7C00, 0x0000, 0x0000, // z
		0x1800, 0x1000, 0x1000, 0x1000, 0x2000, 0x2000, 0x1000, 0x1000, 0x1000, 0x1800, // {
		0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, 0x1000, // |
		0x3000, 0x1000, 0x1000, 0x1000, 0x0800, 0x0800, 0x1000, 0x1000, 0x1000, 0x3000, // }
		0x0000, 0x0000, 0x0000, 0x7400, 0x4C00, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, // ~
};

Objects_t Font1118 =
{ 11, 18, Font11x18 };

Objects_t Font710 =
{ 7, 10, Font7x10 };


void moveCursor(int8_t x, int8_t y);

void drawBitmap(Objects_t *Obj, Color_t _color);

void setPosition(uint8_t x, uint8_t y);

char putChar(char _char, Objects_t *Font, Color_t _color);

void putString(char *_string, Objects_t *Font, Color_t _color);
