PGM=adder
.PHONY: clean all

#disable default rule (Oi!)
%.o: %.c

all: $(PGM).po
	open $(PGM).po

%.asm: %.c
	cc65 -t apple2enh -O -o $@ $<

%.o: %.asm
	ca65 -t apple2enh -o $@ $<

$(PGM): $(patsubst %.c, %.o, $(wildcard *.c))
	cl65 -t apple2enh -o $(PGM) $^

$(PGM).po: $(PGM)
	cp -f bootable.po $(PGM).po
	java -jar AppleCommander-ac-1.6.0.jar -as $(PGM).po $(PGM) < $(PGM)

clean:
	rm -f $(PGM).po $(PGM) *.o *.asm
	@echo All clean.

