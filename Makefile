PGM=adder
.PHONY: clean all

all: $(PGM).po
	open $(PGM).po

$(PGM): $(PGM).c
	cl65 -t apple2enh -O $(PGM).c

$(PGM).po: $(PGM)
	cp -f bootable.po $(PGM).po
	cat $(PGM) | java -jar AppleCommander-ac-1.6.0.jar -as $(PGM).po $(PGM)

clean:
	rm -f $(PGM).po $(PGM) *.o
	@echo All clean.

