CC = wcc386
CFLAGS = -zq
LINKER = wlink
LFLAGS = option quiet

OBJS = bmp.obj t.obj key.obj disp.obj p.obj ctrl.obj main.obj

.c.obj : .autodepend
	$(CC) $(CFLAGS) $<

fruit.exe : $(OBJS)
	$(LINKER) $(LFLAGS) name $@ file { $< }

clean : .symbolic
	rm -f *.obj *.exe