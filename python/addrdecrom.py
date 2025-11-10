rom=bytearray(8192)

#D0 CE for RAM
ramce=0b11111110
#D1 CE for ROM
romce=0b11111101
#D2 CE for VIA
viace=0b11111011

#RAM from address 0x0000 0x01ff
for x in range(0x0000,0x0020):
	rom[x]=ramce

#VIA from address 0x0200 0x020f
for x in range(0x0020,0x0021):
	rom[x]=viace

#RAM from address 0x0210 0x7fff
for x in range(0x0021,0x0800):
	rom[x]=ramce

#ROM from address 0x8000 0xffff
for x in range(0x0800,0x1000):
	rom[x]=romce

with open("addrdec.bin","wb") as out_file:
	out_file.write(rom)

