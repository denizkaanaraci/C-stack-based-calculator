make: exp2.c
	gcc exp2.c -o exp2 -ansi
run:
	./exp2 inputfile outputfile

.PHONY: clean



clean:

	rm -f $(ODIR)/*.o exp2