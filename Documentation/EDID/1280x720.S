/* EDID */
#define VERSION 1
#define REVISION 3

/* Display */
#define CLOCK 74250 /* kHz */
#define XPIX 1280
#define YPIX 720
#define XY_RATIO XY_RATIO_16_9
#define XBLANK 370
#define YBLANK 30
#define XOFFSET 110
#define XPULSE 40
#define YOFFSET (63+5)
#define YPULSE (63+5)
#define DPI 96
#define VFREQ 60 /* Hz */
#define TIMING_NAME "1280x720"
/* No ESTABLISHED_TIMINGx_BITS */
#define HSYNC_POL 1
#define VSYNC_POL 1
#define CRC 0x88

#include "edid.S"

