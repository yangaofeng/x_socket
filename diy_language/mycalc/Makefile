calc:
	yacc -dv mycalc.y
	lex mycalc.l
	cc -o mycalc y.tab.c lex.yy.c

.PHONY: clean

clean:
	rm *.h *.c *.output mycalc
