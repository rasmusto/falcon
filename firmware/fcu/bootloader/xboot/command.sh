sudo avrdude -p x128a3 -P usb:00A000401033 -c jtag2pdi -b 19200 -U flash:w:xboot.hex
