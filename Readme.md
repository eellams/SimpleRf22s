SimpleRf22s
===========
This program allows broadcasting and receiving of simple, unaddressed messages between RF22 modules on the same Arduino board.

I used the connections as described by Mike McCauley in the link below, however each module requires its own interrupt line, and slave select. I used SS --> pin 10 with interrupt --> interrupt 0 for one transceiver, and SS --> pin 9 with interrupt --> interrupt 1 for the other.

This program was written for an Arduino Uno.

Useful Links etc.
-----------------
Based on code by Mike McCauley copyright (C) 2011 Arduino RF22 library ( http://www.airspayce.com/mikem/arduino/RF22/ ) License: http://www.gnu.org/licenses/gpl.html GPL version 2

This program is designed for use with RF22 compatible transceivers (see http://www.hoperf.com )