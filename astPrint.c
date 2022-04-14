#include "astPrint.h"
#include <stdio.h>
void printTabs(int n){
    for(int i = 0; i < n; i++) printf("\t");
}

void print(char* str, int n){
    printTabs(n);
    printf("%s", str);
}

void printDataType(Datatype dt, int n){

}
char* typeDefinitionsToStr(Ast_TypeDefinition* t, int n){
    print("Ast_TypeDefinition", n);
    n = n + 1;
    print(t->id1, n);
    print(t->id2, n);
    printDataType(t->datatype, n);
    printFieldDefinitions(t->fieldDefinitions, n);
}

char* otherStmtsToStr(Ast_OtherStmts* t){

}

char* declarationsToStr(Ast_Declarations* t){

}

char* idListToStr(Ast_IdList* t){

}

char* otherFunctionsToStr(Ast_OtherFunctions* t){

}

char* parameterListToStr(Ast_ParameterList* t){

}

char* fieldDefinitionsToStr(Ast_FieldDefinitions* t){

}

char* singleOrRecIdToStr(Ast_SingleOrRecId* t){

}

char* optionSingleConstructedToStr(Ast_OptionSingleConstructed* t){

}

char* datatypeToStr(Ast_Datatype* t){

}

char* fieldDefinitionToStr(Ast_FieldDefinition* t){

}

char* defineTypeStmtToStr(Ast_DefineTypeStmt* t){

}

char* aToStr(Ast_A* t){

}

char* numToStr(Ast_Num* t){

}

char* rnumToStr(Ast_Rnum* t){

}

char* declarationToStr(Ast_Declaration* t){

}

char* stmtsToStr(Ast_Stmts* t){

}

char* mainToStr(Ast_Main* t){

}

char* programToStr(Ast_Program* t){

}

char* functionToStr(Ast_Function* t){

}

char* parameterDeclarationToStr(Ast_ParameterDeclaration* t){

}

char* primitiveDatatypeToStr(Ast_PrimitiveDatatype* t){

}

char* constructedDatatypeToStr(Ast_ConstructedDatatype* t){

}

char* typeDefinitionToStr(Ast_TypeDefinition* t){

}

char* arithmeticExpressionToStr(Ast_ArithmeticExpression* t){

}

char* booleanExpressionToStr(Ast_BooleanExpression* t){

}

char* assignmentStmtToStr(Ast_AssignmentStmt* t){

}

char* funCallStmtToStr(Ast_FunCallStmt* t){

}

char* varToStr(Ast_Var* t){

}

char* iterativeStmtToStr(Ast_IterativeStmt* t){

}

char* conditionalStmtToStr(Ast_ConditionalStmt* t){

}

char* ioStmtToStr(Ast_IoStmt* t){

}

char* elsePartToStr(Ast_ElsePart* t){

}

char* logicalOperatorToStr(Ast_LogicalOperator* t){

}

char* relationalOperatorToStr(Ast_RelationalOperator* t){

}

char* arithmeticOperatorToStr(Ast_ArithmeticOperator* t){

}

char* moreExpansionToStr(Ast_MoreExpansion* t){

}
