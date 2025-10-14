#include <asm/termbits.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stddef.h>
#include <termios.h>

#include "USB.h"

int handle;
int baud;

int Init_PiSerial(const char* path, int baud_)
{
    handle = -1;
    struct termios tio;
    baud = baud_;
    handle = open(path, O_RDWR | O_NOCTTY | O_NONBLOCK);

    if (handle < 0)
        return 1; // error

    speed_t speed;
    switch(baud_) {
        case 9600: speed = B9600; break;
        case 19200: speed = B19200; break;
        case 38400: speed = B38400; break;
        case 57600: speed = B57600; break;
        case 115200: speed = B115200; break;
        case 230400: speed = B230400; break;
        case 460800: speed = B460800; break;
        case 500000: speed = B500000; break;
        default: speed = B115200;
    }
    cfsetispeed(&tio, speed);
    cfsetospeed(&tio, speed);

    tio.c_cflag = CS8 | CLOCAL | CREAD;
    tio.c_oflag = 0;
    tio.c_iflag = 0;
    tio.c_lflag = 0;

    tio.c_cflag &= ~(CSTOPB); // stopbit one
    tio.c_iflag &= ~(INPCK | ISTRIP);
    tio.c_cflag &= ~(PARENB | PARODD | CMSPAR); // parity none
    
    tio.c_cc[VMIN] = 0;
    tio.c_cc[VTIME] = 0;
    
    if(tcsetattr(handle, TCSANOW, &tio) != 0) {
        return 1;
    }
    
    tcflush(handle, TCIOFLUSH);
    return 0;
}

void Kill_PiSerial()
{
    if (handle >= 0)
        close(handle);
    handle = -1;
}

bool PiSerial_Send(unsigned char* data, int len)
{
    int rlen = write(handle, data, len);
    tcdrain(handle);
    return(rlen == len);
}

int PiSerial_Receive(unsigned char* data, int len)
{
    int lenRCV = 0;
    while (lenRCV < len)
    {
        int rlen = read(handle, &data[lenRCV], len - lenRCV);
        lenRCV += rlen;
    }
    return lenRCV;
}
