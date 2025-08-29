%{

%}

%option noyywrap
%option yylineno

%%
[ \t\n\r]   { /**/ }

.           { return (int)yytext[0]; }
