
%{
int count = 0;
%}

%%
[A-Z] {printf("%s capital letter\n", yytext);
	count++;}
\n|.      { return yytext[0]; }

%%

int yywrap(){}
int main(){

    yylex();
    printf("\nNumber of Capital letters in the given input - %d\n", count);

    return 0;
}
