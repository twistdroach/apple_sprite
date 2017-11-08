PGM=adder

$(PGM):
	cl65 -t apple2enh -O --start-addr 0x4000 $(PGM).c
	java -jar AppleCommander-1.3.5-ac.jar -d $(PGM).po $(PGM)
	java -jar AppleCommander-1.3.5-ac.jar -cc65 $(PGM).po $(PGM) BIN < $(PGM)
	open $(PGM).po

.PHONY: clean
clean:
	@rm -f *.o $(PGM)
	@echo All clean.
