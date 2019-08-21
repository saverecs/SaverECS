#include "structs.h"
#ifndef FBCOMPUT_H
#define FBCOMPUT_H

// Function Declarations

void addLocalVariableActivityToLocation(struct location* loc, char* id, int temporal);
void addIdentityResetToTransition(struct transition* trans, char* id);
struct phaver* addFeatureLocalVariables(struct phaver* pha, struct feature* f, double maxConst);
void addLocalVariable(struct phaver* pha, struct identifier* localVar, double maxConst, int temporal);
struct location *twoWaySplit(struct location *loc, struct PORV* porv, char* sync, struct identifier* vars);
struct location *threeWaySplit(struct location *loc, struct PORV* porv, char* sync, struct identifier* vars);
int splitLocation(struct location *loc, struct PORV* porv, char* sync, struct identifier* vars, struct initial* init);
void pSplitTransform(struct automaton* H, struct PORV* porv, char* sync, struct identifier* vars, struct initial* init);
void tuneForTemporalProperties(struct phaver* pha);
char* getLocationContext(struct PORV* porvConjunct);
struct phaver* splitPORVConjunct(struct phaver* HA, struct PORV* porvConjunct, char *sync);
struct phaver* splitOnEvent(struct phaver* HA, struct sequenceExpr* seq, char *sync);
struct locationWrapper* splitOnLocationContext(struct phaver* HA, char* context, struct locationWrapper* markedList, struct PORV* iterator, char* sync);
struct condition* generateEventGuard(struct eventType* event, struct condition* derivative);
struct condition* generateConjunctGuards(struct PORV* porv);
int countSequenceExpressions(struct sequenceExpr* seq_expr);
void markDelayForFinal(struct condition* activity);
void resetToZero(struct condition* assignmentResets,char* resetName);
void markOriginalTransitions(struct location* locIterator);
struct condition* generateAssignmentResets(struct condition* assignments);
int countConditions(struct condition* root);
struct condition* createZeroDerivative(struct identifier* vars);
void orderedResets(int ExprID, int dnfID,  struct automaton* H, struct location* loc, struct transition* trans, struct condition* resets, struct identifier* vars);
int isStateEvent(struct eventType* event);
struct phaver* levelSequence(struct phaver* H, struct feature* F, char* syncLabel);
struct phaver* addTimeBound(struct phaver* HA, double bound);
#endif
