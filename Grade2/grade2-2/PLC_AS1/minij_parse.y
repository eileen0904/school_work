%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "minij.h"
	#include "minij_parse.h"
	extern int yylineno;
%}

%token CLASS PUB STATIC
%left  AND OR
%left  LT LE EQ
%left  ADD MINUS
%left  TIMES
%token LBP RBP LSP RSP LP RP
%token INT BOOLEAN
%token IF ELSE
%token WHILE PRINT
%token ASSIGN
%token VOID MAIN STR
%token RETURN
%token SEMI COMMA
%token THIS NEW DOT
%token ID LIT TRUE FALSE NOT

%expect 32

%%
prog	:	mainc cdcls
		{ printf("%d Program -> MainClass ClassDecl*\n", yylineno);
		  printf("%d Parsed OK!\n", yylineno); }
	|
		{ printf("%d ****** Parsing failed!\n", yylineno); }	
	;

mainc	:	CLASS ID LBP PUB STATIC VOID MAIN LP STR LSP RSP ID RP LBP stmts RBP RBP
		{ printf("%d MainClass -> class id lbp public static void main lp string lsp rsp id rp lbp Statemet* rbp rbp\n", yylineno); }
	;

cdcls	:	cdcl cdcls
		{ printf("%d (for ClassDecl*) cdcls : cdcl cdcls\n", yylineno); }
	|
		{ printf("%d (for ClassDecl*) cdcls : \n", yylineno); }
	;

cdcl	:	CLASS ID LBP vdcls mdcls RBP
		{ printf("%d ClassDecl -> class id lbp VarDecl* MethodDecl* rbp\n", yylineno); }
	;

vdcls	:	vdcl vdcls
		{ printf("%d (for VarDecl*) vdcls : vdcl vdcls\n", yylineno); }
	|
		{ printf("%d (for VarDecl*) vdcls : \n", yylineno); }
	;

vdcl	:	type ID SEMI
		{ printf("%d VarDecl -> Type id semi\n", yylineno); }
	;

mdcls	:	mdcl mdcls
		{ printf("%d (for MethodDecl*) mdcls : mdcl mdcls\n", yylineno); }
	|
		{ printf("%d (for MethodDecl*) mdcls : \n", yylineno); }
	;

mdcl	:	PUB type ID LP formals RP LBP vdcls stmts RETURN exp SEMI RBP
		{ printf("%d MethodDecl -> public Type id lp FormalList rp lbp Statements* return Exp semi rbp\n", yylineno); }
	;

formals	:	type ID frest
		{ printf("%d FormalList -> Type id FormalRest*\n", yylineno); }
	|
		{ printf("%d FormalList -> \n", yylineno); }
	;

frest	:	COMMA type ID frest
		{ printf("%d FormalRest -> comma Type id FormalRest\n", yylineno); }
	|
		{ printf("%d FormalRest -> \n", yylineno); }
	;

type	:	INT LSP RSP
		{ printf("%d Type -> INT LSP RSP \n", yylineno); }
	|		
			BOOLEAN
		{ printf("%d Type -> BOOLEAN \n", yylineno); }
	|		
			INT
		{ printf("%d Type -> INT \n", yylineno); }
	|		
			ID
		{ printf("%d Type -> --%s-- \n", yylineno, $1); }
	;

stmt	:	LBP stmts RBP
		{ printf("%d stmt -> lbp Statement* rbp \n", yylineno); }
	|		
			IF LP exp RP stmt ELSE stmt
		{ printf("%d stmt -> if lp Exp rp Statement else Statement \n", yylineno); }
	|		
			WHILE LP exp RP stmt
		{ printf("%d stmt -> while lp Exp rp Statement \n", yylineno); }
	|		
			PRINT LP exp RP SEMI
		{ printf("%d stmt -> print lp Exp rp semi \n", yylineno); }
	|		
			ID ASSIGN exp SEMI
		{ printf("%d stmt -> id assign Exp rp semi \n", yylineno); }
	|		
			ID LSP exp RSP ASSIGN exp SEMI
		{ printf("%d stmt -> id lsp Exp rsp assign Exp semi \n", yylineno); }
	|		
			vdcl
		{ printf("%d stmt -> VarDecl \n", yylineno); }
	;

stmts	:	stmt stmts
		{ printf("%d stmts -> Statement* \n", yylineno); }
	|
		{ printf("%d stmts -> \n", yylineno); }
	;

exp 	:	exp ADD exp
		{ printf("%d exp -> Exp add Exp \n", yylineno); }
	|
			exp MINUS exp
		{ printf("%d exp -> Exp minus Exp \n", yylineno); }
	|
			exp TIMES exp
		{ printf("%d exp -> Exp times Exp \n", yylineno); }
	|		
			exp AND exp
		{ printf("%d exp -> Exp and Exp \n", yylineno); }
	|		
			exp OR exp
		{ printf("%d exp -> Exp or Exp \n", yylineno); }
	|		
			exp LT exp
		{ printf("%d exp -> Exp lt Exp \n", yylineno); }
	|		
			exp LE exp
		{ printf("%d exp -> Exp le Exp \n", yylineno); }
	|		
			exp EQ exp
		{ printf("%d exp -> Exp eq Exp \n", yylineno); }
	|		
			ID LSP exp RSP
		{ printf("%d exp -> id lsp Exp rsp \n", yylineno); }
	|		
			ID LP expls RP
		{ printf("%d exp -> id lp Explist rp \n", yylineno); }
	|		
			LP exp RP
		{ printf("%d exp -> lp Exp rp \n", yylineno); }
	|		
			exp DOT exp
		{ printf("%d exp -> Exp dot Exp \n", yylineno); }
	|		
			LIT
		{ printf("%d exp -> --%s-- \n", yylineno, $1); }
	|		
			TRUE
		{ printf("%d exp -> true \n", yylineno); }
	|		
			FALSE
		{ printf("%d exp -> false \n", yylineno); }
	|		
			ID
		{ printf("%d exp -> --%s-- \n", yylineno, $1); }
	|		
			THIS
		{ printf("%d exp -> this \n", yylineno); }
	| 		
			NEW INT LSP exp RSP
		{ printf("%d exp -> new int lsp exp rsp \n", yylineno); }
	| 		
			NEW ID LP RP
		{ printf("%d exp -> new id lp rp \n", yylineno); }	
	|		
			NOT exp
		{ printf("%d exp -> Exp \n", yylineno); }
	;

expls	:	exp exprest
		{ printf("%d expls -> Exp ExpRest* \n", yylineno); }
	|
		{ printf("%d expls -> \n", yylineno); }
	;

exprest : COMMA exp exprest
		{ printf("%d exprests -> comma Exp \n", yylineno); }
	|
		{ printf("%d exprests -> \n", yylineno); }
	;

// Practice on writing the grammar rules for
// 1. type
// 2. statement
// 3. exp
// 4. explist
// 5. exprest
// (see the description in Programming Assignment #1)

%%

int yyerror(char *s)
{
	printf("%s\n",s);
	return 1;
}

