all:
	lex x.l
	yacc x.y -d
	cc lex.yy.c y.tab.h -ll
	# rm -f lex.yy.c y.tab.h y.tab.c y.tab.gch
