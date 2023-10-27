PROJECT := microwwvb
MMCU := attiny44
PARTNO := t44
F_CPU := 20000000
CONF := C:\Users\chris\AppData\Local\Arduino15\packages\arduino\tools\avrdude\6.3.0-arduino17/etc/avrdude.conf
#$(AVRDUDECONF)
PROGRAMMER := stk500v1
BAUD := 19200
#"C:\Users\chris\AppData\Local\Arduino15\packages\arduino\tools\avrdude\6.3.0-arduino17/bin/avrdude"
# "-CC:\Users\chris\AppData\Local\Arduino15\packages\arduino\tools\avrdude\6.3.0-arduino17/etc/avrdude.conf"
# -v -V -pattiny44 -cstk500v1 -PCOM3 -b19200 "-Uflash:w:C:\Users\chris\AppData\Local\Temp\arduino\sketches\0293C5E4D3D9BA07FD96EAB5CF245FA0/ArduinoISP.ino.hex:i"

SOURCES := $(PROJECT).c \
	serial.c \
	gps.c \

HEADERS := \
	serial.h \
	gps.h \
	hardware.h \

CFLAGS := -mmcu=$(MMCU) -flto -Os -DF_CPU=$(F_CPU) -std=c99 \
	-Wall -Wextra -pedantic -Werror

$(PROJECT).hex: $(PROJECT).out
	avr-objcopy -O ihex $(PROJECT).out $(PROJECT).hex;\
	avr-size --mcu=$(MMCU) --format=avr $(PROJECT).out

$(PROJECT).out: $(SOURCES) $(HEADERS)
	avr-gcc $(CFLAGS) -o $(PROJECT).out $(SOURCES)

.PHONY: program
program: $(PROJECT).hex
	avrdude -p $(PARTNO) -P com3 -C $(CONF) -c $(PROGRAMMER) -b $(BAUD 	) -U flash:w:$(PROJECT).hex -v -V

.PHONY: program-fuses
program-fuses:
	avrdude -p $(PARTNO) -P com3 -C$(CONF) -c $(PROGRAMMER) -b $(BAUD) -U lfuse:w:0x5E:m

.PHONY: clean
clean:
	rm -rf $(PROJECT).out $(PROJECT).hex
