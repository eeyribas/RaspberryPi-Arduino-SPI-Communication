#include <QDebug>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <fcntl.h>
#include <cstring>
#include <unistd.h>
#include <iostream>

using namespace std;

u_int8_t SPIRxTx(u_int8_t txDat);

int fd;

int main(int argc, char *argv[])
{
    fd = open("/dev/spidev0.0", O_RDWR);
    unsigned int speed = 4000000;
    ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
    u_int8_t value = 0;
    u_int8_t increase = 1;
    int i = 0;

    while (true) {
        i = 0;
        while (i < (255 * 255)) {
            int result = SPIRxTx(value);
            cout << result << endl;
            usleep(10);

            if (value == 255) {
               value = 0;
               i++;
            } else {
                value = value + increase;
            }
        }

        cout<< "***********************************************************";
        cout<< "***********************************************************";
        cout<< "***********************************************************";
   }
}

u_int8_t SPIRxTx(u_int8_t tx_data)
{
    u_int8_t rx_data;
    struct spi_ioc_transfer spi;
    memset(&spi, 0, sizeof(spi));

    spi.tx_buf = (unsigned long)&tx_data;
    spi.rx_buf = (unsigned long)&rx_data;
    spi.len = 1;
    ioctl(fd, SPI_IOC_MESSAGE(1), &spi);

    return rx_data;
}
