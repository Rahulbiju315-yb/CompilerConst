#include "parser.h"
#include "parserDef.h"
#include "token.h"


typedef struct {
    NonTerminalSet ntSet;
    TokenSet tSet;
} FollowHelperSet;

typedef struct {
    NonTerminal nt;
    int ruleNo;
    int index;
} Location;

typedef struct {
    int size;
    Location* location;
} LocationArray;

TokenSet firstSetDp[NON_TERMINAL_SIZE];
LocationArray ntLocation[NON_TERMINAL_SIZE];
NonTerminalSet nset;

NonTerminalSet nullNonTermSet(){
    return (NonTerminalSet){0};
}

NonTerminalSet singletonNonTermSet(NonTerminal nt){
    return (NonTermSet){1 << nt};
}

NonTerminalSet nonTermSetUnion(NonTermSet s1, NonTermSet s2){
    return (NonTermSet){s1.bitMask | s2.bitMask};
}

int isNullable(NonTerminal nt){
    return (nset.bitMask >> nt) & 1 == 1;
}

void addNullable(NonTerminal nt){
    nset.bitMask |= (1 << nt); 
}
void addRule(Grammar* grammar, NonTerminal nt, Symbol* symbols, int size, int rNum){
    Rule r = {size, symbols};
    grammar->ruleArray[nt].rule[rNum] = r;
    updateNumOccur(symbols, size);
}

void initRuleArray(Grammar* grammar, NonTerminal nt, int size){
    grammar->ruleArray[nt].size = size;
    grammar->ruleArray[nt].rule = (Rule*)malloc(size * sizeof(Rule));
}

void initNumOccur(){
    for(int i = 0; i < NON_TERMINAL_SIZE; i++)
        ntLocation[i].size = 0;
}

void updateNumOccur(Symbol* symbol, int n){
    for(int i = 0; i < n; i++){
        if(!symbol[i].isTerminal){
            ntLocation[symbol[i].symbol].size++;
        }
    }
}

void initLocations(Grammar* grammar){

    int pos[NON_TERMINAL_SIZE];
    for(int i = 0; i < NON_TERMINAL_SIZE; i++){
        ntLocation[i].location = (Location*)malloc(ntLocation[i].size * sizeof(Location));
        pos[i] = 0;
    }
    for(int i = 0; i < NON_TERMINAL_SIZE; i++){
        for(int j = 0; j < grammar->ruleArray[i].size; j++){
            for(int k = 0; k < grammar->ruleArray[i][j].size; k++){
                Symbol s = grammar->ruleArray[i][j][k];
                if(!s.isTerminal){
                    ntLocation[s.symbol].location[pos[s.symbol]++] = (Location){i, j, k};
                }
            }
        }
    }
}
void initGrammar(Grammar* grammar){
    initNumOccur();
    nset.bitMask = 0;
    int size = NON_TERMINAL_SIZE;

    grammar->size = size;
    grammar->ruleArray = (RuleArray*)malloc(size * sizeof(RuleArray));
    
    Symbol program[] = {{0, OTHER_FUNCTIONS}, {0, MAIN_FUNCTION}};
    initRuleArray(grammar, PROGRAM, 1);
    addRule(grammar, PROGRAM, program, 2, 0);

    Symbol mainFunction[] = {{1, TK_MAIN}, {0, STMTS}, {1, TK_END}};
    initRuleArray(grammar, MAIN_FUNCTION, 1);
    addRule(grammar, MAIN_FUNCTION, mainFunction, 3, 0);

    Symbol otherFunctions0[] = {{0, FUNCTION}, {0, OTHER_FUNCTIONS}};
    Symbol otherFunctions1[] = {{1, EPSILON}};
    initRuleArray(grammar, OTHER_FUNCTIONS, 2);
    addRule(grammar, OTHER_FUNCTIONS, otherFunctions0, 2, 0);
    addRule(grammar, OTHER_FUNCTIONS, otherFunctions1, 1, 1);
     

    // initialize nset at the end
    initLocations(grammar);
}

TokenSet first(Grammar* grammar, NonTerminal nt){
    TokenSet tSet = nullTokenSet();

    if(firstSetDp[nt] != tSet)
        return firstSetDp[nt];
    else {
        for(int i = 0; i < grammar->RuleArray[nt].size; i++){
            for(int j = 0; j < grammar->RuleArray[nt][i].size; j++){
                Symbol s = grammar->RuleArray[nt][i][j];
                if(s.isTerminal){
                    tokenSetUnion(tSet, singletonTokenSet(s.symbol));
                    firstSetDp[nt] = tSet;
                    return tSet;
                }
                else if(!s.isTerminal){
                    tSet = tokenSetUnion(tSet, first(grammar, s.symbol));
                    if(!isNullable(s.symbol))
                        return tSet;
                }
            }
        }
    }

    return tSet;
}

FollowHelperSet followHelper(Grammar* grammar, NonTerminal nt){
    NonTerminalSet followDep = nullNonTermSet();
    TokenSet firstDep = nullTokenSet();

    for(int i = 0; i < ntLocation[nt].size; i++){
        Location l = ntLocation[nt][i];
        l.index++;

        int n = grammar->ruleArray[l.nt][l.ruleNo].size;
        while(l.index < n){
            Symbol s = grammar->ruleArray[l.nt][l.ruleNo][l.index];
            if(s.isTerminal){
                firstDep = tokenSetUnion(firstDep, singletonTokenSet(s.symbol));
                break;
            }
            else{
                firstDep = tokenSetUnion(firstDep, first(grammar, s.symbol));
                if(!isNullable(s.symbol))
                    break;
            }
        }
        Symbol lastSymbol = grammar->ruleArray[l.nt][l.ruleNo][n - 1];
        if(l.index == n && !(lastSymbol.isTerminal) && isNullable(lastSymbol.symbol)){
            followDep = nonTermSetUnion(followDep, singletonNonTermSet(l.nt));
        }
    }

    return (FollowHelperSet){followDep, firstDep};
}

