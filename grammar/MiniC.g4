// MiniC.g4 - a small C-like grammar for ANTLR4 (target: C++)
grammar MiniC;

options {
  language = Cpp;
}

// ---------- Parser rules ----------
program
    : (functionDecl | variableDecl)* EOF
    ;

functionDecl
    : type ID '(' parameterList? ')' block
    ;

variableDecl
    : type ID ('=' expression)? ';'
    ;

parameterList
    : parameter (',' parameter)*
    ;

parameter
    : type ID
    ;

block
    : '{' statement* '}'
    ;

statement
    : variableDecl
    | expressionStatement
    | ifStatement
    | whileStatement
    | returnStatement
    | block
    ;

floatType
    : 'float32'
    | 'float64'
    ;

intType
    : 'int8'
    | 'int16'
    | 'int32'
    | 'int64'
    | 'uint8'
    | 'uint16'
    | 'uint32'
    | 'uint64'
    ;
type
    : floatType
    | intType
    | 'void'
    ;

expressionStatement
    : expression? ';'
    ;

ifStatement
    : 'if' '(' expression ')' statement ('else' statement)?
    ;

whileStatement
    : 'while' '(' expression ')' statement
    ;

returnStatement
    : 'return' expression? ';'
    ;

expression
    // unaryExpression
    : op=('+' | '-' | '!') expression
    // assignmentExpression
    | ID '=' expression
    // binaryExpression
    | expression op=('*' | '/' | '+' | '-' | '==' | '!=' | '<' | '<=' | '>' | '>=' | 'AND' | '&&' | 'OR' | '||') expression
    // functionCall
    | ID '(' argumentList? ')'
    // ternaryExpression
    | expression '?' expression ':' expression
    ;

argumentList
    : expression (',' expression)*
    ;

// ---------- Lexer rules ----------
ID
    : [a-zA-Z_][a-zA-Z0-9_]*
    ;

INT_LITERAL
    : [0-9]+
    | '0x'[0-9a-fA-F]+
    | '0b'[01]+
    ;

FLOAT_LITERAL
    : [0-9]+ '.' [0-9]* ( [eE] [+-]? [0-9]+ )?
    | '.' [0-9]+ ( [eE] [+-]? [0-9]+ )?
    | [0-9]+ [eE] [+-]? [0-9]+
    ;

WS
    : [ \t\r\n]+ -> skip
    ;
    
LINE_COMMENT : '//' ~[\r\n]* -> skip ;
BLOCK_COMMENT: '/*' .*? '*/' -> skip ;

