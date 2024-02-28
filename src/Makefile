PROJECT := microwwvb
MMCU := attiny44
PARTNO := t44
F_CPU := 20000000
TOOLS := C:/Users/chris/AppData/Local/Arduino15/packages/arduino/tools
GBIN := $(TOOLS)/avr-gcc/7.3.0-atmel3.6.1-arduino7/bin
DDIR := $(TOOLS)/avrdude/6.3.0-arduino17
DBIN := $(DDIR)/bin
DCONF := $(DDIR)/etc/avrdude.conf

PROGRAMMER := stk500v1
BAUD := 19200
#"C:\Users\chris\AppData\Local\Arduino15\packages\arduino\tools\avrdude\6.3.0-arduino17/bin/avrdude"
# "-CC:\Users\chris\AppData\Local\Arduino15\packages\arduino\tools\avrdude\6.3.0-arduino17/etc/avrdude.conf"
# -v -V -pattiny44 -cstk500v1 -PCOM3 -b19200 "-Uflash:w:C:\Users\chris\AppData\Local\Temp\arduino\sketches\0293C5E4D3D9BA07FD96EAB5CF245FA0/ArduinoISP.ino.hex:i"

SOURCES := $(PROJECT).c \
	serial.c \
	gps.c \
	led.c

HEADERS := \
	serial.h \
	gps.h \
	led.h \
	hardware.h \

CFLAGS := -mmcu=$(MMCU) -flto -Os -DF_CPU=$(F_CPU) -std=c99 \
	-Wall -Wextra -pedantic -Werror

$(PROJECT).hex: $(PROJECT).out
	$(GBIN)/avr-objcopy -O ihex $(PROJECT).out $(PROJECT).hex
	$(GBIN)/avr-size --mcu=$(MMCU) --format=avr $(PROJECT).out

$(PROJECT).out: $(SOURCES) $(HEADERS)
	$(GBIN)/avr-gcc $(CFLAGS) -o $(PROJECT).out $(SOURCES)

.PHONY: program
program: $(PROJECT).hex
	$(DBIN)/avrdude -p $(PARTNO) -P com3 -C$(DCONF) -c $(PROGRAMMER) -b $(BAUD) -U flash:w:$(PROJECT).hex -v -V

.PHONY: program-fuses
program-fuses:
	$DBIN/avrdude -p $(PARTNO) -P com3 -C$(DCONF) -c $(PROGRAMMER) -b $(BAUD) -U lfuse:w:0x5E:m

.PHONY: clean
clean:
	rm -rf $(PROJECT).out $(PROJECT).hex
