#ifndef ASSEMBLY_GEN_H
#define ASSEMBLY_GEN_H

#include "../../frontend/codigo_intermedio/intermediate_code.h"
#include "assembly_instructions.h"

char * generateAssembly(Instruction *list, char *outputFileName);
void   generateAssemblyAux(Instruction *list, FILE *f);

void generateAssemblyInstructionGlobalVarDecl(Instruction *i, FILE *f);
void generateAssemblyInstructionBeginMethod(Instruction *i, FILE *f);
void generateAssemblyInstructionEndMethod(Instruction *i, FILE *f);
void generateAssemblyInstructionLabel(Instruction *i, FILE *f);
void generateAssemblyInstructionAssignmentIntInt(Instruction *i, FILE *f);
void generateAssemblyInstructionAssignmentIntFloat(Instruction *i, FILE *f);
void generateAssemblyInstructionAssignmentFloatInt(Instruction *i, FILE *f);
void generateAssemblyInstructionAssignmentFloatFloat(Instruction *i, FILE *f);
void generateAssemblyInstructionAssignmentBoolBool(Instruction *i, FILE *f);
void generateAssemblyInstructionAdditionIntInt(Instruction *i, FILE *f);
void generateAssemblyInstructionAdditionIntFloat(Instruction *i, FILE *f);
void generateAssemblyInstructionAdditionFloatInt(Instruction *i, FILE *f);
void generateAssemblyInstructionAdditionFloatFloat(Instruction *i, FILE *f);
void generateAssemblyInstructionAnd(Instruction *i, FILE *f);
void generateAssemblyInstructionOr(Instruction *i, FILE *f);
void generateAssemblyInstructionArgument(Instruction *i, FILE *f);
void generateAssemblyInstructionCallMethod(Instruction *i, FILE *f);
void generateAssemblyInstructionReturn(Instruction *i, FILE *f);
void generateAssemblyInstructionSubtractionIntInt(Instruction *i, FILE *f);
void generateAssemblyInstructionSubtractionIntFloat(Instruction *i, FILE *f);
void generateAssemblyInstructionSubtractionFloatInt(Instruction *i, FILE *f);
void generateAssemblyInstructionSubtractionFloatFloat(Instruction *i, FILE *f);
void generateAssemblyInstructionMultiplicationIntInt(Instruction *i, FILE *f);
void generateAssemblyInstructionMultiplicationIntFloat(Instruction *i, FILE *f);
void generateAssemblyInstructionMultiplicationFloatInt(Instruction *i, FILE *f);
void generateAssemblyInstructionMultiplicationFloatFloat(Instruction *i, FILE *f);
void generateAssemblyInstructionDivisionIntInt(Instruction *i, FILE *f);
void generateAssemblyInstructionDivisionIntFloat(Instruction *i, FILE *f);
void generateAssemblyInstructionDivisionFloatInt(Instruction *i, FILE *f);
void generateAssemblyInstructionDivisionFloatFloat(Instruction *i, FILE *f);
void generateAssemblyInstructionModIntInt(Instruction *i, FILE *f);
void generateAssemblyInstructionModIntFloat(Instruction *i, FILE *f);
void generateAssemblyInstructionModFloatInt(Instruction *i, FILE *f);
void generateAssemblyInstructionModFloatFloat(Instruction *i, FILE *f);
void generateAssemblyInstructionComparisonSmallerIntInt(Instruction *i, FILE *f);
void generateAssemblyInstructionComparisonSmallerIntFloat(Instruction *i, FILE *f);
void generateAssemblyInstructionComparisonSmallerFloatInt(Instruction *i, FILE *f);
void generateAssemblyInstructionComparisonSmallerFloatFloat(Instruction *i, FILE *f);
void generateAssemblyInstructionComparisonGreaterIntInt(Instruction *i, FILE *f);
void generateAssemblyInstructionComparisonGreaterIntFloat(Instruction *i, FILE *f);
void generateAssemblyInstructionComparisonGreaterFloatInt(Instruction *i, FILE *f);
void generateAssemblyInstructionComparisonGreaterFloatFloat(Instruction *i, FILE *f);
void generateAssemblyInstructionUnaryMinusInt(Instruction *i, FILE *f);
void generateAssemblyInstructionUnaryMinusFloat(Instruction *i, FILE *f);
void generateAssemblyInstructionNegation(Instruction *i, FILE *f);
void generateAssemblyInstructionJmpFalse(Instruction *i, FILE *f);
void generateAssemblyInstructionJmpTrue(Instruction *i, FILE *f);
void generateAssemblyInstructionJmp(Instruction *i, FILE *f);
void generateAssemblyInstructionEqual(Instruction *i, FILE *f);

#endif // ASSEMBLY_GEN_H
