include ../config.mk
TARGET = displaypgm.elf

CFLAGS += -O2 -I$(BASELIBC)/include -I$(LIBACTSEMI)
LIBS = -L$(BASELIBC) -lc -L$(LIBACTSEMI) -lactsemi
OBJS = displaypgm.o

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $< $(LIBS)

clean:
	rm -f $(OBJS) $(TARGET)
