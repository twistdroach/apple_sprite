PGM=adder

$(PGM):
	cl65 -t apple2enh -O $(PGM).c
	java -jar AppleCommander-ac-1.6.0.jar -d $(PGM).po $(PGM)
	java -jar AppleCommander-ac-1.6.0.jar -as $(PGM).po $(PGM) < $(PGM)
	open $(PGM).po

.PHONY: clean all

clean:
	@rm -f *.o $(PGM)
	@echo All clean.

all: $(PGM)
