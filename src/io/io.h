#ifndef IO_H
#define IO_H

// read one byte from the given port
unsigned char insb(unsigned short port);
// read two bytes from the given port
unsigned short insw(unsigned short port);

// write one byte from the given port
void outb(unsigned short port, unsigned char val);
// write two bytes from the given port
void outw(unsigned short port, unsigned short val);

#endif // !IO_H
