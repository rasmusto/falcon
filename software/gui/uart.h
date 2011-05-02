#ifndef __UART_H
#define __UART_H

#define BAUDRATE B57600

int initUART(char *devicePath);
void initTimeout(void);

int getDataReadyFlag(void);
void clearDataReadyFlag(void);

int getTimeoutFlag(void);
void setTimeoutFlag(void);
void clearTimeoutFlag(void);
void stopTimeout(void);
void startTimeout(void);

#endif
