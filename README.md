# QuadCalc
Arduino-based calculator displaying bin/oct/dec/hex versions of argument and result simultaneously

Schematic: https://github.com/Dovgalyuk/QuadCalc/blob/master/pcb-avr/pcb.pdf

## Flashing

Read low fuse bits into file low:

    sudo avrdude -p m2560 -c usbtiny -U lfuse:r:low:r

Write low fuse bits from file low. It should contain single FF byte:

    sudo avrdude -p m2560 -c usbtiny -U lfuse:w:low:r

Write high fuse bits from file high. It should contain single D8 byte:

    sudo avrdude -p m2560 -c usbtiny -U hfuse:w:high:r

Write the firmware image:

    sudo avrdude -p m2560 -c usbtiny -U flash:w:calc.ino.hex:i

# Links

MK61 hardware emulator: https://gitlab.com/vitasam/mk61s
