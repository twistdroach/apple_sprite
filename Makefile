PGM=adder

$(PGM):
	cl65 -t apple2enh -O --start-addr 0x4000 $(PGM).c
	java -jar AppleCommander-ac-1.6.0.jar -d $(PGM).po $(PGM)
	java -jar AppleCommander-ac-1.6.0.jar -as $(PGM).po $(PGM) < $(PGM)
	open $(PGM).po

.PHONY: clean
clean:
	@rm -f *.o $(PGM)
	@echo All clean.
