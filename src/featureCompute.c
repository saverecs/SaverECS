//#define DEBUG_ON
#ifndef MAX_STR_LENGTH
	#define MAX_STR_LENGTH 256
#endif
//#define DEBUG_ON

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "featureCompute.h"
static int count = 0;

/*
 * For variable x, location l
 * 	Add x'==0 as an activity for location l
 */
void addLocalVariableActivityToLocation(struct location* loc, char* id, int temporal){
	if(loc!=NULL && id!=NULL){
		#ifdef DEBUG_ON 
			printf("[addLocalVariableActivityToLocation] STARTED Loc = [%s], id = [%s], temporal = [%d]\n",loc->name,id,temporal);
		#endif
		
		char *LHS = (char*)malloc(sizeof(char)*(sizeof(id)+2));
		char *RHS = (char*)malloc(sizeof(char)*(sizeof(char)*2));
		sprintf(LHS,"%s'",id);
		sprintf(RHS,"%d",temporal);
		loc->derivative = addToConditionList(loc->derivative,LHS,RHS,0);
		
		#ifdef DEBUG_ON 
			printf("[addLocalVariableActivityToLocation] ENDED\n");
		#endif
	}
}


/*
 * For the given variable "id" add an Identity reset
 * to the transition trans i.e. id' == id so that when
 * the transition is active the variables valuation
 * is retained accross the locations. 
 */
void addIdentityResetToTransition(struct transition* trans, char* id){
	if(trans!=NULL && id!=NULL){
		#ifdef DEBUG_ON 
			printf("[addIdentityResetToTransition] STARTED Transition TO: [%s] Variable ID = [%s]\n",trans->gotoLoc,id);
		#endif
		
		char *temp = (char*)malloc(sizeof(char)*(sizeof(id)+2));
		sprintf(temp,"%s'",id);
		
		char *temp2 = (char*)malloc(sizeof(char)*sizeof(id)+1);
		strcpy(temp2,id);
		
		trans->reset = addToConditionList(trans->reset,temp,temp2,0);
		
		#ifdef DEBUG_ON 
			struct condition* test=trans->reset;
			while(test!=NULL){
				printCondition(test);
				test = test->next;
			}
			printf("\n");
			
			printf("[addIdentityResetToTransition] ENDED\n");
		#endif
	}
}

/*
 * Add local variables of Feature f to the Hybrid Automaton Model
 */
struct phaver* addFeatureLocalVariables(struct phaver* pha, struct feature* f, double maxConst){
	#ifdef DEBUG_ON 
		printf("[addFeatureLocalVariables] STARTED\n");
	#endif
	
	struct identifier* localVars = f->def->localVars;
	maxConst = maxConst*10;
	char number[MAX_STR_LENGTH];
	sprintf(number,"%.8f",maxConst);
	while(localVars!=NULL){
		//Add Local Variable to Control Variable List
		pha->ha->contr_vars = addToIdentifierList(pha->ha->contr_vars, localVars->name);
		
		//Add Initial Value for localvariable
		pha->init->init_conds = addToConditionList(pha->init->init_conds,localVars->name,number,0); 
		
		localVars = localVars->next;
	}
	
	localVars = f->def->localVars;
	struct location* loc = pha->ha->locations;
	while(loc!=NULL){
		while(localVars!=NULL){
			//	Add Local Variable Activity (assuming no temporal 
			//	variable is in the list)
			addLocalVariableActivityToLocation(loc,localVars->name,0);
			
			//Add Identity Resets in Outgoing Transitions
			struct transition* trans = loc->transitions;
			while(trans!=NULL){
				addIdentityResetToTransition(trans,localVars->name);
				trans=trans->next;
			}
			localVars = localVars->next;
		}
		loc = loc->next;
	}
	#ifdef DEBUG_ON 
		printf("[addFeatureLocalVariables] ENDED\n");
	#endif
	
}

/*
 * Add the single local Variable localVar to the Hybrid Automaton
 * Model.
 */
void addLocalVariable(struct phaver* pha, struct identifier* localVar, double maxConst, int temporal){
	if(localVar!=NULL){
		#ifdef DEBUG_ON 
			printf("[addLocalVariable] STARTED LocalVar being Added : [%s]\n",localVar->name);
		#endif
		//maxConst = maxConst*10;
		maxConst = (temporal == 0)? maxConst : 0;
		char number[MAX_STR_LENGTH];
		sprintf(number,"%10f",maxConst);
		
		//Add Local Variable to Control Variable List
		pha->ha->contr_vars = addToIdentifierList(pha->ha->contr_vars, localVar->name);
		
		//Add Initial Value for localvariable
		struct initial* initIterator = pha->init;
		while(initIterator!=NULL){
			if(initIterator->init_conds==NULL){
				printf("ERROR: No Initial Conditions Specified\n");
				exit(0);
			}
			addToConditionList(initIterator->init_conds,localVar->name,number,0); 
			initIterator = initIterator->next;
		}
		
		//pha->init->init_conds = addToConditionList(pha->init->init_conds,localVar->name,number,0); 
		
		struct location* loc = pha->ha->locations;
		
		
		/*while(loc!=NULL){
			printf("NEXT: loc [%s] \n",loc->name);
			struct transition* trans = loc->transitions;
			while(trans!=NULL){
				struct condition* transCond = trans->reset;
				printCondition(transCond);
				printf("\n");
				trans = trans->next;
			}
			printf("\n");
			loc = loc->next;
		}*/
		while(loc!=NULL){
			#ifdef DEBUG_ON 
			printf("[addLocalVariable] Location Being Processed: [%s]\n",loc->name);
			#endif
			//Add Local Variable Activity
			addLocalVariableActivityToLocation(loc,localVar->name,temporal);
			
			//Add Identity Resets in Outgoing Transitions
			struct transition* trans = loc->transitions;
			while(trans!=NULL){
				//For each transition. Add an identity reset
				addIdentityResetToTransition(trans,localVar->name);
				trans=trans->next;
				
			}
			loc = loc->next;
		}
		
		/*
		loc = pha->ha->locations;
		while(loc!=NULL){
			printf("NEXT: ");
			struct transition* trans = loc->transitions;
			while(trans!=NULL){
				printf("[%p] ",trans);
				trans = trans->next;
			}
			printf("\n");
			loc = loc->next;
		}*/
		
		#ifdef DEBUG_ON 
			printf("[addLocalVariable] ENDED\n");
		#endif
		
	}
}

/*
 * Split location loc on PORV porv into l<id> and lx<id> in which 
 * porv is TRUE and FALSE respectively.
 */
struct location *twoWaySplit(struct location *loc, struct PORV* porv, char* sync, struct identifier* vars){
	#ifdef DEBUG_ON 
		printf("[twoWaySplit] STARTED\n");
	#endif
	
	
	//Create a copy of the location
	struct location* negLoc = duplicateLocation(loc);
	#ifdef DEBUG_ON 
		printf("[twoWaySplit] DUPLICATED LOCATION\n");
	#endif
	
	//Change name of the location with PORV true to "name"+id
	sprintf(loc->name,"%s_%d",loc->name,porv->id);
	
	//Change name of the location with PORV false to "name"+"x"+id
	sprintf(negLoc->name,"%s_x%d",negLoc->name,porv->id);
	
	#ifdef DEBUG_ON 
		printf("[twoWaySplit] Altered Location Names\n");
	#endif
	/*
	 * For each incoming transition (u,v)
	 * 	Create a transition to v.PORVID and v.xPORVID
	 */
	#ifdef DEBUG_ON 
		printf("[twoWaySplit] Updating source locations of incoming transitions\n");
	#endif
	
	//For each transition into the location v i.e. (u,v)
	struct transitionWrapper* incoming = loc->incoming;
	while(incoming!=NULL){
		//Update the GOTO name in the transition from (u,old_v) to (u,v)
		strcpy(incoming->trans->gotoLoc,loc->name);
		
		//Add to the transition list of the incoming node
		addToTransitionList(incoming->loc->transitions,incoming->trans->when,incoming->trans->sync,incoming->trans->reset,negLoc->name);
		
		incoming = incoming->next;
	}
	#ifdef DEBUG_ON 
		printf("[twoWaySplit] Incoming location transitions updated, Adding Invariant to loc\n");
	#endif
	
	/*
	 * Adding PORV Invariants
	 */
	#ifdef DEBUG_ON 
		printf("BEFORE %p -> %p\n",porv->porv, porv->porv->next);
		printf("loc->invariant = %p\n",loc->invariant);
	#endif
	
	struct condition* porvCopy = duplicateConditionList(porv->porv);//createCondition(porv->porv->LHS,porv->porv->RHS,porv->porv->op);
	addConditionToList(loc->invariant,porvCopy);
	#ifdef DEBUG_ON 
		printf("AFTER %p -> %p\n",porv->porv, porv->porv->next);
		printf("[twoWaySplit] Invariants added to loc\n");
		
		if(porv->porv->next == porv->porv){
			printf("CAUGHT IT\n");exit(0);
		}
	#endif
	
	struct condition* negPorv = duplicateConditionList(porv->porv);
	
	#ifdef DEBUG_ON 
		printf("[twoWaySplit] Duplicating splitting PORV for negation\n");
	#endif
	
	
	switch(negPorv->op){
		case 1: negPorv->op = 3; break;
		case 3: negPorv->op = 1; break;
		default: printf("ERROR SPLITTING\n");exit(0);
	}
	
	addConditionToList(negLoc->invariant,negPorv);
	
	#ifdef DEBUG_ON 
		printf("[twoWaySplit] Added Negated Invariant\n");
	#endif
	
	/*
	 * Add continuum transitions
	 */
	struct condition* resets = createIdentityResets(vars);
	#ifdef DEBUG_ON 
		printf("[twoWaySplit] Added Resets\n");
	#endif
	
	loc->transitions = addToTransitionList(loc->transitions,negPorv,sync,resets,negLoc->name);
	negLoc->transitions = addToTransitionList(negLoc->transitions,porv->porv,sync,resets,loc->name);
	
	#ifdef DEBUG_ON 
		printf("[twoWaySplit] Updated Transitions\n");
	#endif
	
	//Updating PORV truths for the locations : To later answer the question - does the location satisfy a given PORV
	struct PORV* porvNew = createPORV(porv->porv,porv->id);
	loc->labels = addPORVToList(loc->labels,porvNew);
	
	//Fixing Pointers
	negLoc->next = loc->next;
	loc->next = negLoc;
	
	#ifdef DEBUG_ON 
		printf("[twoWaySplit] Fixed Pointers\n");
		printf("[twoWaySplit] ENDED\n");
	#endif
	
	return loc;
}

/*
 * porv of the form expr == expr
 * Split location loc on PORV porv into l<id>, ll<id> and lg<id> in which 
 * the invariants are respectively, expr == expr, expr <= expr and 
 * expr >=expr
 */
struct location *threeWaySplit(struct location *loc, struct PORV* porv, char* sync, struct identifier* vars){
	//Create Two additional Locations
	struct location* leqLoc = duplicateLocation(loc);
	struct location* geqLoc = duplicateLocation(loc);
	
	//Change the location names
	sprintf(loc->name,"%s_%d",loc->name,porv->id);
	sprintf(leqLoc->name,"%s_l%d",leqLoc->name,porv->id);
	sprintf(geqLoc->name,"%s_g%d",geqLoc->name,porv->id);
	
	/*
	 * For each incoming transition (u,v)
	 * 	Create a transition to v.PORVID and v.xPORVID
	 */
	
	struct transitionWrapper* incoming = loc->incoming;
	while(incoming!=NULL){
		strcpy(incoming->trans->gotoLoc,loc->name);
		addToTransitionList(incoming->loc->transitions,incoming->trans->when,incoming->trans->sync,incoming->trans->reset,leqLoc->name);
		addToTransitionList(incoming->loc->transitions,incoming->trans->when,incoming->trans->sync,incoming->trans->reset,geqLoc->name);
		incoming = incoming->next;
	}
	
	/*
	 * Adding PORV Invariants
	 */
	struct condition* porvCopy = duplicateConditionList(porv->porv);//createCondition(porv->porv->LHS,porv->porv->RHS,porv->porv->op);
	addConditionToList(loc->invariant,porvCopy);
	struct condition* leqPorv = duplicateConditionList(porv->porv);
	struct condition* geqPorv = duplicateConditionList(porv->porv);
	
	leqPorv->op = 1;
	geqPorv->op = 3;
	
	addConditionToList(leqLoc->invariant,leqPorv);
	addConditionToList(geqLoc->invariant,geqPorv);
	
	/*
	 * Add continuum transitions
	 */
	struct condition* resets = createIdentityResets(vars);
	
	loc->transitions = addToTransitionList(loc->transitions,leqPorv,sync,resets,leqLoc->name);
	loc->transitions = addToTransitionList(loc->transitions,geqPorv,sync,resets,geqLoc->name);
	
	leqLoc->transitions = addToTransitionList(leqLoc->transitions,porv->porv,sync,resets,loc->name);
	leqLoc->transitions = addToTransitionList(leqLoc->transitions,geqPorv,sync,resets,geqLoc->name);
	
	geqLoc->transitions = addToTransitionList(geqLoc->transitions,leqPorv,sync,resets,leqLoc->name);
	geqLoc->transitions = addToTransitionList(geqLoc->transitions,porv->porv,sync,resets,loc->name);
	
	//Updating PORV truths for the locations : To later answer the question - does the location satisfy a given PORV
	struct PORV* porvNew = createPORV(porv->porv,porv->id);
	loc->labels = addPORVToList(loc->labels,porvNew);
	
	//Fixing Pointers
	geqLoc->next = loc->next;
	leqLoc->next = geqLoc;	
	loc->next = leqLoc;
	
	return loc;
}

/*
 * Specific Location Splitting:
 * For a PORV of the form I1 <= I2, two way splitting into L1 with I1<=I2 and L2 with I1>=I2
 * For a PORV of the form I1 == I2 three way splitting into L1, L2, and L3 with I1<=I2, I1==I2 and I1>=I2
 * 
 * Returns number of locations split into.
 */
int splitLocation(struct location *loc, struct PORV* porv, char* sync, struct identifier* vars, struct initial* init){
	if(loc!=NULL && porv!=NULL){
		struct initial* initLoc = checkInitial(loc,init);
		if(initLoc != NULL){
			if(porv->porv->op == 0){
				struct initial* initDupL = duplicateInitialConditions(initLoc);
				struct initial* initDupG = duplicateInitialConditions(initLoc);
				
				sprintf(initLoc->init_locs->name,"%s_%d",initLoc->init_locs->name,porv->id);
				sprintf(initDupL->init_locs->name,"%s_l%d",initDupL->init_locs->name,porv->id);
				sprintf(initDupG->init_locs->name,"%s_g%d",initDupG->init_locs->name,porv->id);
				
				initDupG->next = initLoc->next;
				initDupL->next = initDupG;
				initLoc->next = initDupL;
			} else {
				struct initial* initDup = duplicateInitialConditions(initLoc);
				
				sprintf(initLoc->init_locs->name,"%s_%d",initLoc->init_locs->name,porv->id);
				sprintf(initDup->init_locs->name,"%s_x%d",initDup->init_locs->name,porv->id);
				
				initDup->next = initLoc->next;
				initLoc->next = initDup;
			}
		}
		
		/* 
		 * If this is the first split of the location, remember the locations
		 * original Name.
		 */
		if(loc->originalName==NULL){
			loc->originalName = (char*)malloc(sizeof(char)*MAX_STR_LENGTH);
			strcpy(loc->originalName,loc->name);
		}
		
		switch(porv->porv->op){
			case 0: threeWaySplit(loc,porv,sync,vars); break;
			case 1: twoWaySplit(loc,porv,sync,vars); break;
			case 3: twoWaySplit(loc,porv,sync,vars); break;
			default: printf("ERROR SPLITTING\n");exit(0);
		}
		return (porv->porv->op==0)?3:2;
	}
	return 0;
	
}

/*
 * Splitting is either general (for all locations)
 * Or specific for a location
 */
void pSplitTransform(struct automaton* H, struct PORV* porv, char* sync, struct identifier* vars, struct initial* init){
	struct location* locations = H->locations;
	
	struct condition* invariants = NULL;
	struct condition* activity = NULL;
	struct transition* trans = NULL;
	
	struct location* Q = NULL;
	
	while(locations!=NULL){
		Q = locations;
		//Move to the next location, to prevent re-splitting of 
		//an already split location
		locations = locations->next;
		
		//If a location being split is an initial location, then
		//	Delete the location from the initial location list
		//	Add new split locations to the initial location list
		
		
		splitLocation(Q,porv,sync,vars,init);
		processIncomingTransitions(H->locations);
		
		//printf("locations = %p\n",locations);
		
		while(Q!=locations){
			#ifdef DEBUG_ON 
				printf("BEGIN\n");
			#endif
			Q = Q->next;
			
			#ifdef DEBUG_ON 
				printf("Q = %p\n",Q);
				printf("locations = %p\n",locations);
			#endif
				
			if(Q == locations){
				#ifdef DEBUG_ON 
					printf("Im here\n");
				#endif
					
				break;
			}
			#ifdef DEBUG_ON 
				printf("Im here again\n");
			#endif
		}
		#ifdef DEBUG_ON 
			printf("im out\n");
		#endif
	
		if(Q!=locations){
			printf("[pSplitTransform] : ERROR IN SPLITTING\n");
		}
		#ifdef DEBUG_ON 
			printf("I'm really out\n");
		#endif	
	}
}

/*
 * Add $time as a local variable with time'==1 in
 * all locations.
 * 
 * Called when $time is used or when the assertion
 * is temporal in nature. 
 * 
 * $time is added only once, but may be called 
 * multiple times.
 */
void tuneForTemporalProperties(struct phaver* HA){
	
	if(HA->temporal == 0){
		#ifdef DEBUG_ON
			printf("[tuneForTemporalProperties] STARTED\n");
			printf("[tuneForTemporalProperties] Adding $time to the HA\n");
		
			count++;
			if(count>1)
				printf("WHOA!!! I should not be here in any temporal dimension.\n");
		#endif	
			
		char temporal[5];
		sprintf(temporal,"time");
		struct identifier* time = createIdentifier(temporal);
		
		#ifdef DEBUG_ON
			printf("[tuneForTemporalProperties] Adding TIME as a control variable\n");
		#endif	
			
		addLocalVariable(HA,time,0,1);
		
		#ifdef DEBUG_ON
			printf("[tuneForTemporalProperties] Added TIME\n");
		#endif	
		//A time property has been added
		HA->temporal = 1;
		
		#ifdef DEBUG_ON
			printf("[tuneForTemporalProperties] STARTED\n");
			printf("[tuneForTemporalProperties] Adding $time to the HA\n");
		#endif
		
	}
}

char* getLocationContext(struct PORV* porvConjunct){
	if(porvConjunct!=NULL){
		struct PORV* iterator = porvConjunct;
		char *context = NULL;
		
		//Check for a Location context
		while(iterator!=NULL){
			if(iterator->id == 0){
				//Location context found
				context = iterator->porv->RHS;
				break;
			}
			iterator = iterator->next;
		}
		return context;
	}
	return NULL;
}


struct locationWrapper* splitOnLocationContext(struct phaver* HA, char* context, struct locationWrapper* markedList, struct PORV* porv, char* sync){
	#ifdef DEBUG_ON 
		printf("[splitOnLocationContext] Printing context\n"); fflush(stdout);
		printf("[splitOnLocationContext] Context = %s\n",context); fflush(stdout);
		printf("[splitOnLocationContext] Printing markedlist\n"); fflush(stdout);
		printf("[splitOnLocationContext] markedList = %p\n",markedList);
	#endif
		
	struct location* loc = getUnmarkedLocation(HA->ha->locations, context, markedList);
	
	#ifdef DEBUG_ON 
		printPseudoLocationList(markedList);
	#endif
	
	if(loc != NULL){
		//Atleast one location found
		while(loc!=NULL){
			int splitCount = splitLocation(loc,porv,sync,HA->ha->contr_vars,HA->init);
			processIncomingTransitions(HA->ha->locations);
			
			#ifdef DEBUG_ON 
				printf("[splitOnLocationContext] Marking the original location that was split, now [%s]\n",loc->name);
			#endif
			
			markedList = addToPseudoLocationList(markedList,loc);
			struct location* tempLoc = loc->next;
			while(splitCount>1 && tempLoc!=NULL){
				markedList = addToPseudoLocationList(markedList,tempLoc);
				
				#ifdef DEBUG_ON 
					printf("[splitOnLocationContext] Marking the newly added location after the split, [%s]\n",tempLoc->name);
					printPseudoLocationList(markedList);
				#endif
				
				tempLoc = tempLoc->next;
				splitCount--;
			}
			
			//Get Next Location For Splitting
			loc = getUnmarkedLocation(HA->ha->locations,context, markedList);
			
			#ifdef DEBUG_ON 
				printPseudoLocationList(markedList);
			#endif
		}
		
	} else {
		printf("Feature Error : Could not find the Location: %s\n",context);
	}
	#ifdef DEBUG_ON 
		printf("[splitOnLocationContext] ========== ENDED PORV Split =========\n");
	#endif
	
	return markedList;
}

/*
 * Find location context of the PORV Conjunct
 */
struct phaver* splitPORVConjunct(struct phaver* HA, struct PORV* porvConjunct, char *sync){
	if(porvConjunct!=NULL){
		struct PORV* iterator = porvConjunct;
		struct locationWrapper* markedList = NULL;
		char *context = NULL;
		
		//Check for a Location context
		context = getLocationContext(porvConjunct);
		
		if(context==NULL){
			// No Location Context
			// Split All locations
			iterator = porvConjunct;
			while(iterator!=NULL){
				//For Each PORV, Split All Locations
				pSplitTransform(HA->ha,iterator,sync,HA->ha->contr_vars,HA->init);
				#ifdef DEBUG_ON 
					printf("iterator->next = %p\n",iterator);
				#endif
				
				iterator = iterator->next;
				
			}
			//exit(0);
		} else {
			//Location Context Exists
			// For each PORV
			//	For each location in context
			//		Split all such locations
			iterator = porvConjunct;
			while(iterator!=NULL){
				if(iterator->id > 0){//Split on PORVs only. Their IDs are positive.
					//Get the next location within context, that has not yet been split.
					#ifdef DEBUG_ON 
						printf("[splitPORVConjunct] ========== Next PORV Split =========\n");
					#endif
					markedList = splitOnLocationContext(HA, context, markedList, iterator, sync);
					/*struct location* loc = getUnmarkedLocation(HA->ha->locations, context, markedList);
					
					#ifdef DEBUG_ON 
						printPseudoLocationList(markedList);
					#endif
						
					if(loc != NULL){
						//Atleast one location found
						while(loc!=NULL){
							int splitCount = splitLocation(loc,iterator,sync,HA->ha->contr_vars,HA->init);
							processIncomingTransitions(HA->ha->locations);
							#ifdef DEBUG_ON 
								printf("[splitPORVConjunct] Marking the original location that was split, now [%s]\n",loc->name);
							#endif
							markedList = addToPseudoLocationList(markedList,loc);
							struct location* tempLoc = loc->next;
							while(splitCount>1 && tempLoc!=NULL){
								markedList = addToPseudoLocationList(markedList,tempLoc);
								#ifdef DEBUG_ON 
									printf("[splitPORVConjunct] Marking the newly added location after the split, [%s]\n",tempLoc->name);
									printPseudoLocationList(markedList);
								#endif
								
								tempLoc = tempLoc->next;
								splitCount--;
							}
							
							//Get Next Location For Splitting
							loc = getUnmarkedLocation(HA->ha->locations,context, markedList);
							
							#ifdef DEBUG_ON 
								printPseudoLocationList(markedList);
							#endif
						}
						
					} else {
						printf("Feature Error : Could not find the Location: %s\n",context);
					}
					#ifdef DEBUG_ON 
						printf("[splitPORVConjunct] ========== ENDED PORV Split =========\n");
					#endif
					*/
				}
				freePseudoLocationList(markedList);
				markedList = NULL;
				iterator=iterator->next;
			}
		}
	}
	#ifdef DEBUG_ON 
		printf("[splitPORVConjunct] ENDED\n");
	#endif
	return HA;
}


struct phaver* splitOnEvent(struct phaver* HA, struct sequenceExpr* seq, char *sync){
	//NULL POINTER CHECK
	#ifdef DEBUG_ON 
		printf("[splitOnEvent] STARTED\n");
	#endif
		
	if(HA!=NULL && seq!=NULL && sync!=NULL){
		/*
			struct sequenceExpr{	
				struct expression* expr;	//Sub-sequence Expression
				struct timeDelay* delay;	//Delay associated with expr match
				struct condition* assignments;	//List of Assignments when expr matches within delay
				struct sequenceExpr* next;	//Next sub-expression
			};
			struct PORV{				//List of PORV's conjuncted together
				struct condition* porv;
				int id;
				struct PORV* next;
			};
			
			struct eventType{
				int type;			//Event Type - posedge(1), negedge(2), either(0)
				struct PORV* porv;		//Event Condition
			};
			
			struct PORVExpression{
				struct PORV* conjunct;		//List of PORVs conjuncted together
				struct PORVExpression* next;	//Next PORVConjunct in the Disjunction
			};
			
			struct expression{
				struct PORVExpression* dnf;	//Disjunction of Conjunction of PORVs
				struct eventType* event;	//Event
			};
		*/
		
		struct eventType* event = seq->expr->event;			//Event (Only One allowed per sub expression
		struct PORVExpression* disjunctIterator = seq->expr->dnf;	//Disjunction of PORV conjuncts (Includes possible location Contexts)
		struct locationWrapper* markedList = NULL;
		
		struct identifier* contextList = NULL;
		//Collect location contexts to split
		while(disjunctIterator!=NULL){
			//For each conjunct in the disjunctive normal form, check for a location context
			#ifdef DEBUG_ON 
				printf("[splitOnEvent] Searching for Context.\n");
			#endif
			char* context = getLocationContext(disjunctIterator->conjunct);
			
			if(context!=NULL){
				#ifdef DEBUG_ON 
					printf("[splitOnEvent] Context Found. Adding to List.\n");
				#endif
				
				contextList = addToIdentifierList(contextList,context);
				
				#ifdef DEBUG_ON 
					printf("[splitOnEvent] Context Added.\n");
				#endif
			} else {
				//There Exists atleast one Conjunct with no location context. All Locations should be split
				freeIdentifierList(contextList);
				contextList = NULL;
				break;
			}
			
			#ifdef DEBUG_ON 
				if(context==NULL)
					printf("[splitOnEvent] No Context Found.\n");
			#endif
			//Goto the next disjunction of PORVs
			disjunctIterator = disjunctIterator->next;
		} 
		
		if(contextList==NULL){
			// Split all locations on the event
			#ifdef DEBUG_ON 
				printf("[splitOnEvent] Split all locations on the event.\n");
			#endif
				
			pSplitTransform(HA->ha,event->porv,sync,HA->ha->contr_vars,HA->init);
			
			#ifdef DEBUG_ON 
				printf("[splitOnEvent] Splitting Complete.\n");
			#endif
			
		} else {
			// Split locations within the context list
			#ifdef DEBUG_ON 
				printf("[splitOnEvent] Split on context.\n");
			#endif
			
			struct identifier* idIterator = contextList;
			if(event!=NULL){
				while(idIterator!=NULL){
					//Get next location in context and split it on the event
					//printf("HERE Event is %d\n",event==NULL?0:1);
					markedList = splitOnLocationContext(HA, idIterator->name, markedList, event->porv, sync);
					
					//printf("HERE\n");
					freePseudoLocationList(markedList);
					markedList = NULL;
					idIterator = idIterator->next;
				}
			}
		} 
		
	}
	
	#ifdef DEBUG_ON 
		printf("[splitOnEvent] ENDED\n");
	#endif
	return HA;
}

/* 
 * struct condition* generateTemporalGuards(struct sequenceExpr* seq)
 * Creates a temporal guard. Given [lower:upper], generates lower<=time, time <= upper
 */
struct condition* generateTemporalGuards(struct sequenceExpr* seq){
	if(seq!=NULL){
		if(seq->delay!=NULL){
			struct condition* temporalGuards = NULL;
			char* lower = (char*)malloc(sizeof(char)*MAX_STR_LENGTH);
			char* upper = (char*)malloc(sizeof(char)*MAX_STR_LENGTH);
			switch(seq->delay->type){
				case 0: //Finite lower and upper bounds;
					sprintf(lower,"%f",seq->delay->lower);
					sprintf(upper,"%f",seq->delay->upper);
					temporalGuards = addToConditionList(temporalGuards,lower,"time",1);
					temporalGuards = addToConditionList(temporalGuards,"time",upper,1);
					break;

				case 1: //Unconstrained upper bounds : upper == 0
					sprintf(lower,"%f",seq->delay->lower);
					temporalGuards = addToConditionList(temporalGuards,lower,"time",1);
					break;
					
				case 2: //Exact Finite Time
					sprintf(lower,"%f",seq->delay->lower);
					temporalGuards = addToConditionList(temporalGuards,lower,"time",0);
					break;
					
				default: printf("[generateTemporalGuards] ERROR\n");exit(0);
			}
			return temporalGuards;
		} 
		return NULL;
	}
	return NULL;
}

/*
struct condition* generateGuard(struct PORV* porv){
	if(porv!=NULL){
		struct condition* guard = NULL;
		guard = createCondition(porv->porv->LHS,porv->porv->RHS,porv->porv->op);
		return guard;
	}
	return NULL;
}
*/

struct condition* generateEventGuard(eventType* event, condition* derivative){
	#ifdef DEBUG_ON 
		printf("[generateEventGuard] STARTED\n");
	#endif
		
	if(event!=NULL){
		struct condition* guard = NULL;
		guard = createCondition(event->porv->porv->LHS,event->porv->porv->RHS,0);
		if(derivative!=NULL){
			struct condition* iterator = derivative;
			while(derivative){
				#ifdef DEBUG_ON 
                                printf("[generateEventGuard] Event on Variable [%s]\n",derivative->LHS);
				#endif
                                
                                if(strncmp(event->porv->porv->LHS,derivative->LHS,strlen(derivative->LHS)-1)==0){
					int op = 0;
					//1 posedge
					//2 negedge
					//0 either
					switch(event->type){
						case 1:	if(event->porv->porv->op == 0 || \
							event->porv->porv->op == 3 || \
							event->porv->porv->op == 5){
								op = 3;
							} else op = 1;
							break;
							
						case 2: if(event->porv->porv->op == 0 || \
							event->porv->porv->op == 3 || \
							event->porv->porv->op == 5){
								op = 1;
							} else op = 3;
							break;
							
						default: op = 0;
					}
					if(op>0)
						guard = addToConditionList(guard,event->porv->porv->LHS,derivative->RHS,op);
					
					break;
				}
				derivative = derivative->next;
			}
		}
		#ifdef DEBUG_ON 
			printf("[generateEventGuard] STARTED\n");
		#endif
		return guard;
	}
	#ifdef DEBUG_ON 
		printf("[generateEventGuard] STARTED\n");
	#endif
	return NULL;
}

struct condition* generateConjunctGuards(struct PORV* porv){
	if(porv!=NULL){
		struct condition* guard = NULL;
		while(porv!=NULL){
			if(porv->id>0)
				guard = addConditionToList(guard,createCondition(porv->porv->LHS,porv->porv->RHS,porv->porv->op));
			porv = porv->next;
		}
		return guard;
	}
	return NULL;
}

int countSequenceExpressions(struct sequenceExpr* seq_expr){
	int expr_count = 0;
	
	while(seq_expr!=NULL){
		expr_count++;
		seq_expr = seq_expr->next;
	}
	return expr_count;
}

void markDelayForFinal(struct condition* activity){
	while(activity){
		if(strcasecmp(activity->LHS,"time'")==0){
			sprintf(activity->RHS,"1");
		}
		activity = activity->next;
	}
}


void markOriginalTransitions(struct location* locIterator){
	struct transition* transIterator = NULL;
	
	while(locIterator!=NULL){
		transIterator = locIterator->transitions;
		while(transIterator!=NULL){
			transIterator->original = 1;
			transIterator = transIterator->next;
		}
		locIterator = locIterator->next;
	}
}

struct condition* generateAssignmentResets(struct condition* assignments){
	#ifdef DEBUG_ON 
	printf("[generateAssignmentResets] STARTED\n");
	#endif
	
	if(assignments!=NULL){
		struct condition* root = NULL;
		struct condition* iterator = assignments;
		
		while(iterator!=NULL){
			char* LHS = (char*)malloc(sizeof(char)*MAX_STR_LENGTH);
			char* RHS = (char*)malloc(sizeof(char)*MAX_STR_LENGTH);
			
			#ifdef DEBUG_ON 
				printCondition(iterator);printf("\n");
			#endif
			
			sprintf(LHS,"%s'",iterator->LHS);
			
			if(strcmp(iterator->RHS,"$time")==0){
				sprintf(RHS,"time");
			} else strcpy(RHS,iterator->RHS);

			#ifdef DEBUG_ON
				printf("CONDITION ADDED IS : %s == %s\n",LHS,RHS);
			#endif
			
			root = addToConditionList(root,LHS,RHS,0);
			
			iterator = iterator->next;
		}
		#ifdef DEBUG_ON 
			printf("[generateAssignmentResets] ENDED\n");
		#endif
		
		return root;
	} 
	#ifdef DEBUG_ON 
		printf("[generateAssignmentResets] ENDED\n");
	#endif
	return NULL;
	
}

int countConditions(struct condition* root){
	#ifdef DEBUG_ON 
		printf("[countConditions] STARTED\n");
	#endif
	
	struct condition* iterator = root;
	int count = 0;
	while(iterator!=NULL){
		count++;
		iterator = iterator->next;
	}
	
	#ifdef DEBUG_ON 
		printf("[countConditions] ENDED\n");
	#endif
	
	return count;
}

struct condition* createZeroDerivative(struct identifier* vars){
	#ifdef DEBUG_ON 
		printf("[createZeroDerivative] STARTED\n");
	#endif
		
	if(vars!=NULL){
		#ifdef DEBUG_ON
			printf("[createZeroDerivative] vars!=NULL\n");
		#endif
		
		struct identifier* iterator = vars;
		struct condition* root = NULL;
		char* LHS = (char*)malloc(sizeof(char)*MAX_STR_LENGTH);
		char* RHS = (char*)malloc(sizeof(char)*MAX_STR_LENGTH);
		
		while(iterator!=NULL){
			sprintf(LHS,"%s'",iterator->name);
			sprintf(RHS,"0");
			root = addToConditionList(root,LHS,RHS,0);
			
			iterator = iterator->next;
		}
		free(LHS);
		free(RHS);
		
		#ifdef DEBUG_ON 
			printf("[createZeroDerivative] ENDED\n");
		#endif
			
		return root;
	}
	#ifdef DEBUG_ON 
		printf("[createZeroDerivative] vars NULL ENDED\n");
	#endif
	return NULL;
}

void orderedResets(int ExprID, int dnfID, struct automaton* H, struct location* loc, struct transition* trans, struct condition* resets, struct identifier* vars){
	#ifdef DEBUG_ON 
		printf("[orderedResets] BEGIN\n");
	#endif
		
	if(loc!=NULL && trans!=NULL){
		int resetCount = resets?countConditions(resets):0;
		struct condition* iterator = resets;
		int id=1;
		
		#ifdef DEBUG_ON
			printf("[orderedResets] Condition List:\n");
		
			/*struct condition* tempC = resets ;
			while(tempC!=NULL){
				printCondition(tempC);printf(" , ");
				tempC=tempC->next;
			}*/
			printConditionList(resets);
			printf("\n");
		#endif
			
		if(resetCount>1){
			#ifdef DEBUG_ON 
				printf("[orderedResets] Ordering Required - More than 1 assignment present\n");
			#endif
			char* name = (char*)malloc(sizeof(char)*MAX_STR_LENGTH);
			char* gotoName = (char*)malloc(sizeof(char)*MAX_STR_LENGTH);
			
			while(iterator!=NULL){
				sprintf(name,"%sS%dD%dR%d",loc->name, ExprID, dnfID, id-1);
				sprintf(gotoName,"%sS%dD%dR%d",loc->name, ExprID, dnfID, id);
				struct condition* whileInvariant = duplicateConditionList(loc->invariant);
				struct condition* derivative = createZeroDerivative(vars);
				
				/*
				printf("[orderedResets] Created Derivative list:\n");
				struct condition* tempC = derivative ;
				while(tempC!=NULL){
					printCondition(tempC);printf(" && ");
					tempC=tempC->next;
				}
				*/
				
				struct condition* reset = createCondition(iterator->LHS,iterator->RHS,0);
				struct condition* resetList = NULL;
				if(id==resetCount){
					struct condition* condIterator = trans->reset;
					/*if(strcmp(condIterator->LHS,reset->LHS)==0){
						trans->reset= condIterator->next;
					} else {
						while(condIterator->next!=NULL){
							if(strcmp(condIterator->next->LHS,reset->LHS)==0){
								condIterator->next = condIterator->next->next;
								break;
							}
							condIterator = condIterator->next;
						}
					}*/
					while(condIterator!=NULL){
						if(strcmp(condIterator->LHS,reset->LHS)==0){
							strcpy(condIterator->RHS,reset->RHS);
							break;
						}
						condIterator = condIterator->next;
					}
					
				} else {
					resetList = createIdentityResets(H->contr_vars);
					struct condition* condIterator = resetList;
					/*if(strcmp(condIterator->LHS,reset->LHS)==0){
					 *	strcpy(condIterator->RHS,reset->RHS);
					 *	//resetList = condIterator->next;
					} else {
						while(condIterator->next!=NULL){
							if(strcmp(condIterator->next->LHS,reset->LHS)==0){
								strcpy(condIterator->next->RHS,reset->RHS);
								//condIterator->next = condIterator->next->next;
								break;
							}
							condIterator = condIterator->next;
						}
					}*/
					
					while(condIterator!=NULL){
						if(strcmp(condIterator->LHS,reset->LHS)==0){
							strcpy(condIterator->RHS,reset->RHS);
							break;
						}
						condIterator = condIterator->next;
					}
					
					
				} 
				
				#ifdef DEBUG_ON
					printf("RESET IS : ");printCondition(reset);printf("\n");
				#endif
					
				if(id==1){
					//Starting Location to next location
					loc->transitions = addToTransitionList(loc->transitions,duplicateConditionList(trans->when),trans->sync,resetList,gotoName);
				} else if(id<resetCount){
					//Intermediate locations
					struct transition* dummyTrans = createTransition(duplicateConditionList(trans->when),trans->sync,resetList,gotoName);
					H->locations = addToLocationList(H->locations,name,whileInvariant,derivative,dummyTrans,1);
				} else {//Last Location
					//trans->reset = addConditionToList(trans->reset,reset);
					H->locations = addToLocationList(H->locations,name,whileInvariant,derivative,trans,1);
				}
				id++;
				iterator = iterator->next;
			}
		} else {
			#ifdef DEBUG_ON 
				printf("[orderedResets] Ordering Not Required.\n");
			#endif
			
			if(resetCount==1){
				struct condition* reset = createCondition(iterator->LHS,iterator->RHS,0);
		
				struct condition* condIterator = trans->reset;
				
				while(condIterator!=NULL){
					if(strcmp(condIterator->LHS,reset->LHS)==0){
						strcpy(condIterator->RHS,reset->RHS);
						break;
					}
					condIterator = condIterator->next;
				}
				
				
				#ifdef DEBUG_ON
					printf("RESET IS : ");printCondition(reset);printf("\n");
				#endif	
				
			}
			
			//trans->reset = addConditionToList(trans->reset,reset);
			loc->transitions = addTransitionToList(loc->transitions,trans);
		} 
		
	}
	#ifdef DEBUG_ON 
		printf("[orderedResets] ENDED\n");
	#endif
}

void resetToZero(struct condition* assignmentResets,char* varName){
	//printf("********************************************* HERE ***************************************************\n");
	if(varName!=NULL){
		/*char* resetName = (char*)malloc(sizeof(char)*MAX_STR_LENGTH);
		sprintf(resetName,"%s'",varName);
		*/
		while(assignmentResets){
			if(strncasecmp(assignmentResets->LHS,varName,strlen(varName))==0){
				sprintf(assignmentResets->RHS,"0");
			}
			//printf("********************************************* [%s] ***************************************************\n",assignmentResets->LHS);
			assignmentResets = assignmentResets->next;
		}
	}
}

//Determines if the event is on the discrete state variable
int isStateEvent(struct eventType* event){
	#ifdef DEBUG_ON 
		printf("[isStateEvent] STARTED\n");
	#endif
	
	if(event && event->porv){
		if(strcasecmp(event->porv->porv->LHS,"state")==0){
			#ifdef DEBUG_ON 
				printf("[isStateEvent] ENDED: Is a state based event\n");
			#endif
			return 1;
		} else {
			#ifdef DEBUG_ON 
				printf("[isStateEvent] ENDED: NOT a state based event\n");
			#endif
			return 0;
		}
	}
	
	#ifdef DEBUG_ON 
		printf("[isStateEvent] ENDED - Something is NULL\n");
	#endif
}


/* 
 * This function computes the product automaton that is key to Feature Analysis
 */
struct phaver* levelSequence(struct phaver* H, struct feature* F, char* syncLabel){
	#ifdef DEBUG_ON 
		printf("[levelSequence] BEGIN\n");
	#endif
	
	if(H!=NULL && F!=NULL){
		//Initial states all start with level == 0 
		int id = 0;
		int nextId = 0;	
		char* strID = (char*)malloc(sizeof(char)*MAX_STR_LENGTH);
		
		struct sequenceExpr* seq_expr = F->def->seq;
		//expr_count <--- Number of subsequences in the sequence expression
		int expr_count = countSequenceExpressions(seq_expr);
		
		#ifdef DEBUG_ON 
			printf("[levelSequence] Sequence Expression Count = [%d]\n",expr_count);
		#endif
	
		//Now we mark transitions that are of the original automaton i.e. level 0
		#ifdef DEBUG_ON 
			printf("[levelSequence] Marking Transitions of level 0 as ORIGINAL\n");
		#endif
		struct location* locIterator = H->ha->locations;
		struct transition* transIterator = NULL;
	
		markOriginalTransitions(H->ha->locations);
		
		//Synchronization label for level switching is syncLabel

		//Level Sequencing starts here.
		
		#ifdef DEBUG_ON 
			printf("[levelSequence] Sequencing Begins\n");
		#endif
		
		//ADDING FINAL LOCATION
		char* name = (char*)malloc(sizeof(char)*MAX_STR_LENGTH);
		sprintf(name,"FINAL");
		struct condition* whileInvariant = createCondition(NULL,NULL,-1);
		struct condition* derivative = createZeroDerivative(H->ha->contr_vars);
		markDelayForFinal(derivative);
		H->ha->locations = addToLocationList(H->ha->locations,name,whileInvariant,derivative,NULL,1);
		
		whileInvariant = NULL;
		derivative = NULL;
		
		//Get the list of Sequence Expressions - seq_expr
		seq_expr = F->def->seq;
			
		//For Each Expression create a level
		while(seq_expr!=NULL){
			
			//id = Position of the subexpression
			nextId = ((id+1 == expr_count)? 0 : id+1);
			
			// Generating Temporal Guards
			struct condition* temporalGuards = generateTemporalGuards(seq_expr);
			
			// Generate Event Guards
			int eType = -1;
			int stateEvent = 0; // Either these is no event associated with the subexpression or the event isn't over the discrete state variable.
			char* eventContext = NULL;
			struct condition* eventGuards = NULL;
			if(seq_expr->expr->event!=NULL){
				/* 
				 * Check Event Type
				 * Check on which variable the PORV is defined (This assumes each PORV has one variable on the LHS)
				 *
				 * If it is a state even all transitions 
				 * at this level to the next level entering 
				 * or leaving the state have to be treated 
				 * appropriately.
				 */
				stateEvent = isStateEvent(seq_expr->expr->event);
				eventContext = stateEvent?seq_expr->expr->event->porv->porv->RHS:NULL;
				
				//If it's a non-state event then prepare an event guard
				//printf("\nHERE\n");
				//printf("\n[%p]\n",seq_expr->expr->event);

				eventGuards = stateEvent?NULL:generateEventGuard(seq_expr->expr->event,NULL);
				
				eType = seq_expr->expr->event->type;
				
			}
			
			// Level Guards
			sprintf(strID,"%d",id);
			struct condition* levelGuard = createCondition("level",strID,0);
			
			// Generate Conjunct Guards for PORVs in the conjunct
			struct condition* conjunctGuards = NULL;
				
			// Generate Resets
			sprintf(strID,"%d",nextId);
			struct condition* levelResets = createCondition("level'", strID, 2);
			
			struct condition* temporalResets = NULL;
			
			if(H->temporal==1){
				temporalResets = addToConditionList(temporalResets,"time'","time",2);
			}
			
			struct condition* assignmentResets = NULL;//seq_expr->assignments;
			
			struct condition* featureAssignments = generateAssignmentResets(F->def->featureAssign);
			
			/* 
			 * For each location Q either the locations satisfies 
			 * the sub-expression or not. 
			 * 
			 * If the location satisfies the subexpression, transitions
			 * are added at this location to the next level.
			 * 
			 * For location p, if there is an event applicable on q, then
			 * there are the following three possibilities:
			 * @+(q) : Transitions from p to q are the ones on which 
			 *         the level changes. Other transitions are deleted. 
			 * @-(q) : Transitions from q to p are the ones on which
			 *         the level changes. Other transitions from q are deleted.
			 * @(q)  : Transition from p to q, and from q to p are ones
			 *         on which level changes. Others are deleted.
			 */
			locIterator = H->ha->locations;
			while(locIterator!=NULL){
				#ifdef DEBUG_ON
					printf("\n");
					printf("\n[levelSequence] LEVEL [%d] : Location: %s :  Location Truth = %d\n", id, locIterator->name, isTrueExpr(locIterator,seq_expr->expr));
				#endif
				
				//For non-pause locations, skip all pause locations
				if(locIterator->type==1){ locIterator=locIterator->next; continue;}
				eventGuards = stateEvent?NULL:generateEventGuard(seq_expr->expr->event,locIterator->derivative);
				//if(isTrueExpr(locIterator,seq_expr->expr)==1){//REMOVED AS PART OF NO SPLIT change
					//The Location Satisfies the expression
						//ENHANCEMENT: FOR WHICH CONJUNCTS IS THE EXPRESSION TRUE
					
					#ifdef DEBUG_ON 
						printf("[levelSequence] [EXPR-MATCH]Location [%s] at Level [%d]\n",locIterator->name,id);
					#endif
					
					struct PORVExpression* dnf = seq_expr->expr->dnf;
					int dnfID = 0;
					while(dnf!=NULL){
						//For each conjunct create one transition
						dnfID++;
						struct transition* trans = NULL;
						
						#ifdef DEBUG_ON 
							printf("[levelSequence] [EXPR-MATCH]Generating Transition for \n");
							printPORVExpression(dnf);printf("-\n");
						#endif
						
						//Get Location Context
						char* context = getLocationContext(dnf->conjunct);
						#ifdef DEBUG_ON
							if(context!=NULL){ 
								printf("Context = [%s]\n",context);
								printf("locIterator = %p\n",locIterator);
								printf("original Name");fflush(stdout);printf(" = %d\n", locIterator->originalName);
								if(locIterator->originalName!=NULL){
									printf("Original Name is not null = %p\n",locIterator->originalName);
									printf("locIterator = %p\n",locIterator);
									printf("original Name");fflush(stdout);printf(" = %s\n", locIterator->originalName);
									printf("strcmp([%s],[%s])=%d\n",context,locIterator->originalName,strcmp(context,locIterator->originalName));
								}
							}
							
							printf("Main bahar hun\n");
							printf("%d\n",(context!=NULL && (locIterator->originalName!=NULL?(strcmp(context,locIterator->originalName)==0):(strcmp(context,locIterator->name)==0))));
							printf("NAME = %s\n",locIterator->name);
							printf("Main bahar hun\n");
						#endif
						
						
						if((context == NULL) || (context!=NULL && strcmp(context,locIterator->name)==0)){ //(locIterator->originalName!=NULL?(strcmp(context,locIterator->originalName)==0):(strcmp(context,locIterator->name)==0)))){
							//If there is a location context for the formula, then consider the context
							#ifdef DEBUG_ON 
								printf("[levelSequence] No Location Context OR Context Match \n");
								printf("[levelSequence] Creating Transition\n");
								fflush(stdout);
							#endif
							
							//Generate the Guards
							struct condition* when = duplicateConditionList(temporalGuards);
							
							//Add event guards
							if(!stateEvent){
								when = addConditionToList(when,duplicateConditionList(eventGuards));
							}
							
							//Add Conjunct Guard
							if(dnf->conjunct!=NULL)
								conjunctGuards = generateConjunctGuards(dnf->conjunct);
							when = addConditionToList(when,conjunctGuards);
							
							//Add Level Guard
							//if(id!=0)                                                        
							when = addConditionToList(when,levelGuard);
							
							/*
							 * If there is a state Q based event, then on all transitions 
							 * from P to Q, the event is applicable, if it is a posedge
							 * otherwise if it is a negedge it is applicable if P==Q.
							 * Event Type - posedge(1), negedge(2), either(0)
							 */
							if(stateEvent){
								//A Posedge Transition entering location Q = "eventContext" from the current location
								if(eType == 1 || eType == 0){
									struct transition* transIterator = locIterator->transitions;
									while(transIterator){
										//If not an original transition skip
										if(!transIterator->original){transIterator = transIterator->next; continue;}
										
										//If transition is not to Q skip
										if(strcmp(transIterator->gotoLoc,eventContext)!=0){transIterator = transIterator->next; continue;}			
										else{
											//If it is to Q then make a copy and add on all the other feature luggage onto it
											struct transition* posTrans = duplicateTransision(transIterator);
											posTrans->next = NULL;
											posTrans->original = 0;
											posTrans->when = addConditionToList(posTrans->when,duplicateConditionList(when));
                                                                                        removeConditionFromList(&posTrans->reset,"level");                                                                                       
											posTrans->reset = addConditionToList(posTrans->reset,duplicateConditionList(levelResets));
											
											//Order Resets for assignments
											assignmentResets = generateAssignmentResets(seq_expr->assignments);
											assignmentResets = reverseConditionList(assignmentResets);
											
											struct condition* allResets = duplicateConditionList(temporalResets);
											posTrans->reset = addConditionToList(posTrans->reset,allResets);
											
											if(id==expr_count-1){
												//Feature Computation
												assignmentResets = addConditionToList(assignmentResets,featureAssignments);
												char varName[MAX_STR_LENGTH] = "time";
												resetToZero(posTrans->reset,varName);
												
												strcpy(posTrans->gotoLoc,name);
											}
											
											//Add the transition to the location's transition list
											orderedResets(id,dnfID,H->ha,locIterator,posTrans,assignmentResets,H->ha->contr_vars);
											assignmentResets = NULL;
											
											posTrans = NULL; //Just to be safe :)
										}
										
										transIterator = transIterator->next;
									}
								}
								
								//If its a negedge or an anyedge and this is location Q (the current location is the eventLocation), we want to exit this location on the negedge
								if((eType == 2 || eType == 0) && strcmp(locIterator->name,eventContext)==0){
									struct transition* transIterator = locIterator->transitions;
									while(transIterator){
										//If not an original transition skip
										if(!transIterator->original){transIterator = transIterator->next; continue;}
										
										//If it is an original transition
										struct transition* negTrans = duplicateTransision(transIterator);
										negTrans->next = NULL;
										negTrans->original = 0;
										negTrans->when = addConditionToList(negTrans->when,duplicateConditionList(when));
                                                                                removeConditionFromList(&negTrans->reset,"level");                                                                                       
                                                                                negTrans->reset = addConditionToList(negTrans->reset,duplicateConditionList(levelResets));
										
										//Order Resets for assignments
										assignmentResets = generateAssignmentResets(seq_expr->assignments);
										assignmentResets = reverseConditionList(assignmentResets);
										
										struct condition* allResets = duplicateConditionList(temporalResets);
										negTrans->reset = addConditionToList(negTrans->reset,allResets);
										
										if(id==expr_count-1){
											//Feature Computation
											assignmentResets = addConditionToList(assignmentResets,featureAssignments);
											char varName[MAX_STR_LENGTH] = "time";
											resetToZero(negTrans->reset,varName);
											
											strcpy(negTrans->gotoLoc,name);
										}
										
										//Add the transition to the location's transition list
										orderedResets(id,dnfID,H->ha,locIterator,negTrans,assignmentResets,H->ha->contr_vars);
										assignmentResets = NULL;
										
										negTrans = NULL; //Just to be safe :)
									
										transIterator = transIterator->next;
									}
								}
							} else {
								
								#ifdef DEBUG_ON 
									if(when!=NULL){
										printf("[levelSequence] When Clause is as follows:\n");printConditionList(when);
									} else	
										printf("[levelSequence] When Clause is Null\n");
									
								#endif
							
								trans = createTransitionOnEvent(when,syncLabel,duplicateConditionList(levelResets),locIterator->name,H->ha->contr_vars);
								
								#ifdef DEBUG_ON 
									if(trans!=NULL)
										printf("[levelSequence] Transition Created\n");
									else	
										printf("[levelSequence] Transition NOT Created\n");
									
								#endif
								
								//Order Resets for assignments
								assignmentResets = generateAssignmentResets(seq_expr->assignments);
								#ifdef DEBUG_ON 
									printf("[levelSequence] Assignment Resets from Sub-expression  =  %p\n",assignmentResets);
									printConditionList(assignmentResets);
								#endif
									
								assignmentResets = reverseConditionList(assignmentResets);
								
								#ifdef DEBUG_ON 
									printf("[levelSequence] Reversing Assignment Resets =  %p\n",assignmentResets);
									printConditionList(assignmentResets);
								#endif
								
								struct condition* allResets = duplicateConditionList(temporalResets);
								trans->reset = addConditionToList(trans->reset,allResets);
								//assignmentResets = addConditionToList(assignmentResets,allResets);
								#ifdef DEBUG_ON 
									printf("\n[levelSequence] [HERE] id = %d  expr_count = %d\n",id, expr_count);
								#endif
								
								if(id==expr_count-1){
									//Feature Computation
									assignmentResets = addConditionToList(assignmentResets,featureAssignments);
									char varName[MAX_STR_LENGTH] = "time";
									resetToZero(trans->reset,varName);
									/*      
									char* name = (char*)malloc(sizeof(char)*MAX_STR_LENGTH);
									//char* gotoName = (char*)malloc(sizeof(char)*MAX_STR_LENGTH);
									sprintf(name,"FINAL");
									//sprintf(gotoName,"%sS%dR%d",loc->name, ExprID, id);
									struct condition* whileInvariant = duplicateConditionList(locIterator->invariant);
									struct condition* derivative = createZeroDerivative(H->ha->contr_vars);
									//struct condition* resetList = createIdentityResets(H->ha->contr_vars);
									H->ha->locations = addToLocationList(H->ha->locations,name,whileInvariant,derivative,NULL);
									*/
									strcpy(trans->gotoLoc,name);
								}
								#ifdef DEBUG_ON
									printf("[levelSequence] All Assignment Resets  =  %p\n",assignmentResets);
									printConditionList(assignmentResets);
								#endif
								orderedResets(id,dnfID,H->ha,locIterator,trans,/*addConditionToList(assignmentResets,duplicateConditionList(temporalResets))*/\
												assignmentResets,H->ha->contr_vars);
								assignmentResets = NULL;
								//Add the transition to the location's transition list
 								#ifdef DEBUG_ON
								printConditionList(featureAssignments);
								printConditionList(trans->reset);
								#endif
								
								#ifdef DEBUG_ON
									printf("[levelSequence] The transition is original = %d\n",trans->original);
								#endif
								//locIterator->transitions = addTransitionToList(locIterator->transitions, trans);
								trans = NULL; //Just to be safe :)
									
							}
						}
						
						//Check the next conjunct
						dnf = dnf->next;
					}
					
					if(seq_expr->expr->dnf==NULL){
						//No PORVs only the event
						#ifdef DEBUG_ON 
							printf("---------------- DNF IS NULL --------------\n");
						#endif
							
						if(stateEvent){
							//A Posedge Transition entering location Q = "eventContext" from the current location
							if(eType == 1 || eType == 0){
								struct transition* transIterator = locIterator->transitions;
								while(transIterator){
									//If not an original transition skip
									if(!transIterator->original){transIterator = transIterator->next; continue;}
									
									//If transition is not to Q skip
									if(strcmp(transIterator->gotoLoc,eventContext)!=0){transIterator = transIterator->next; continue;}			
									else{
										//If it is to Q then make a copy and add on all the other feature luggage onto it
										struct transition* posTrans = duplicateTransision(transIterator);
										posTrans->next = NULL;
										posTrans->original = 0;
										
										struct condition* when = duplicateConditionList(temporalGuards);
										when = addConditionToList(when,duplicateConditionList(levelGuard));
								
										posTrans->when = addConditionToList(posTrans->when,duplicateConditionList(when));
                                                                                removeConditionFromList(&posTrans->reset,"level");                                                                                       
                                                                                posTrans->reset = addConditionToList(posTrans->reset,duplicateConditionList(levelResets));
										
										//Order Resets for assignments
										assignmentResets = generateAssignmentResets(seq_expr->assignments);
										assignmentResets = reverseConditionList(assignmentResets);
										
										struct condition* allResets = duplicateConditionList(temporalResets);
										posTrans->reset = addConditionToList(posTrans->reset,allResets);
										
										if(id==expr_count-1){
											//Feature Computation
											assignmentResets = addConditionToList(assignmentResets,featureAssignments);
											char varName[MAX_STR_LENGTH] = "time";
											resetToZero(posTrans->reset,varName);
											
											strcpy(posTrans->gotoLoc,name);
										}
										
										//Add the transition to the location's transition list
										orderedResets(id,dnfID,H->ha,locIterator,posTrans,assignmentResets,H->ha->contr_vars);
										assignmentResets = NULL;
										
										posTrans = NULL; //Just to be safe :)
									}
									
									transIterator = transIterator->next;
								}
							}
							
							//If its a negedge or an anyedge and this is location Q (the current location is the eventLocation), we want to exit this location on the negedge
							if((eType == 2 || eType == 0) && strcmp(locIterator->name,eventContext)==0){
								struct transition* transIterator = locIterator->transitions;
								while(transIterator){
									//If not an original transition skip
									if(!transIterator->original){transIterator = transIterator->next; continue;}
									
									//If it is an original transition
									struct transition* negTrans = duplicateTransision(transIterator);
									negTrans->next = NULL;
									negTrans->original = 0;
								
									struct condition* when = duplicateConditionList(temporalGuards);
									when = addConditionToList(when,duplicateConditionList(levelGuard));
									
									negTrans->when = addConditionToList(negTrans->when,duplicateConditionList(when));
									removeConditionFromList(&negTrans->reset,"level");                                                                                       
                                                                        negTrans->reset = addConditionToList(negTrans->reset,duplicateConditionList(levelResets));
									
									//Order Resets for assignments
									assignmentResets = generateAssignmentResets(seq_expr->assignments);
									assignmentResets = reverseConditionList(assignmentResets);
									
									struct condition* allResets = duplicateConditionList(temporalResets);
									negTrans->reset = addConditionToList(negTrans->reset,allResets);
									
									if(id==expr_count-1){
										//Feature Computation
										assignmentResets = addConditionToList(assignmentResets,featureAssignments);
										char varName[MAX_STR_LENGTH] = "time";
										resetToZero(negTrans->reset,varName);
										
										strcpy(negTrans->gotoLoc,name);
									}
									
									//Add the transition to the location's transition list
									orderedResets(id,dnfID,H->ha,locIterator,negTrans,assignmentResets,H->ha->contr_vars);
									assignmentResets = NULL;
									
									negTrans = NULL; //Just to be safe :)
								
									transIterator = transIterator->next;
								}
							}
						} else {
							if(seq_expr->expr->event!=NULL){
								
								struct condition* when = duplicateConditionList(temporalGuards);
								if(!stateEvent){
									when = addConditionToList(when,duplicateConditionList(eventGuards));
								}
								when = addConditionToList(when,duplicateConditionList(levelGuard));
								
								struct transition* trans = createTransitionOnEvent(when, syncLabel, duplicateConditionList(levelResets), locIterator->name, H->ha->contr_vars);
								
								//Order Resets for assignments
								assignmentResets = generateAssignmentResets(seq_expr->assignments);
								
								#ifdef DEBUG_ON 
								printf("Assignment Resets  =  %p\n",assignmentResets);
								printConditionList(assignmentResets);
								#endif
								
								assignmentResets = reverseConditionList(assignmentResets);
								
								#ifdef DEBUG_ON 
								printf("Assignment Resets after reversing  =  %p\n",assignmentResets);
								printConditionList(assignmentResets);
								#endif
								
								if(id==expr_count-1){
									//Feature Computation
									assignmentResets = addConditionToList(assignmentResets,featureAssignments);
									/*
									char* name = (char*)malloc(sizeof(char)*MAX_STR_LENGTH);
									//char* gotoName = (char*)malloc(sizeof(char)*MAX_STR_LENGTH);
									sprintf(name,"FINAL");
									//sprintf(gotoName,"%sS%dR%d",loc->name, ExprID, id);
									struct condition* whileInvariant = duplicateConditionList(locIterator->invariant);
									struct condition* derivative = createZeroDerivative(H->ha->contr_vars);
									//struct condition* resetList = createIdentityResets(H->ha->contr_vars);
									H->ha->locations = addToLocationList(H->ha->locations,name,whileInvariant,derivative,NULL);
									*/
									strcpy(trans->gotoLoc,name);
								}
								
								#ifdef DEBUG_ON
									printf("Assignment Resets  =  %p\n",assignmentResets);
								
									printf("------------------------TRANS GOTO = %s\n",trans->gotoLoc);
								#endif
									
								struct condition* allResets = duplicateConditionList(temporalResets);
								trans->reset = addConditionToList(trans->reset,allResets);
								orderedResets(id,dnfID, H->ha,locIterator,trans,/*addConditionToList(assignmentResets,duplicateConditionList(temporalResets))*/assignmentResets,H->ha->contr_vars);
								
								assignmentResets = NULL;
								#ifdef DEBUG_ON
								printConditionList(trans->reset);
								#endif
								//printf("transition is original = %d\n",trans->original);
								//locIterator->transitions = addTransitionToList(locIterator->transitions, trans);
								
								trans = NULL; //Just to be safe :)
							}
						}
					}
					
				//}//REMOVED AS PART OF NO SPLIT change
				
				//FROM THE IF!!!!!!!!!!!!!!!!!!!!!!!
				//else if(id!=0){ //REMOVED AS PART OF NO SPLIT change
				//printf(	"dnf = %p\n",dnf);
				
				
				/*
				 * If the Location Does Not Satisfy the Expression and 
				 * it is a non level 0 location then all transitions 
				 * are retained at this level.
				 */
				if(seq_expr->expr->dnf!=NULL){//ADDED AS PART OF NO SPLIT change
					dnf=seq_expr->expr->dnf;
				
					char* context = getLocationContext(dnf->conjunct);
				
                                        #ifdef DEBUG_ON
					printf("============>  CONTEXT = [%s]\n",context);
                                        #endif
                                        
                                        if(id!=0 && (stateEvent || (context!=NULL && strcmp(context,locIterator->name)!=0))){//ADDED AS PART OF NO SPLIT change
						
						/* Checking if any location with the same original 
						 * Name satisfies the sequence expression (to eliminate cycles)
						 */ 
						//isTrueExpr(locIterator,seq_expr->expr)==1
						int breakCycle = 0;
						/*REMOVED AS PART OF NO SPLIT change
						* if(locIterator->originalName!=NULL){//There are other locations to check
							struct location* locList = H->ha->locations;
							
							//While there are locations left and no location satisfies the subexpression
							while(locList!=NULL){
								//If the location was previously split
								if(locList->originalName!=NULL){
									//If the location is a sibling of the current location
									if(strcmp(locList->originalName,locIterator->originalName)==0 && strcmp(locList->name,locIterator-> name)!=0){
										//If the sibling is a final state for this level
										if(isTrueExpr(locList,seq_expr->expr)==1){
											breakCycle = 1;
											break;
										}
									}
								}
								locList = locList->next;
							}
						}*/
						
						/* 
						 * Make a copy of each original transitions, and guard it 
						 * with the level guard
						 */
                                                if(locHasTransAtLevel(locIterator,id)==0){
                                                        if(breakCycle == 0){
                                                                struct transition* trans = locIterator->transitions;
                                                                //For each location P not satisfying Expr
                                                                while(trans!=NULL){
                                                                        //printf("trans->original = %d\n",(int)trans->original);
                                                                        if((int)(trans->original)==1){
                                                                                //Make a copy of each original Transition with level guard
                                                                                struct transition *newTrans = NULL;
                                                                                newTrans = addToTransitionList(newTrans,duplicateConditionList(trans->when),trans->sync,duplicateConditionList(trans->reset),trans->gotoLoc);
                                                                                newTrans->next = NULL;
                                                                                
                                                                                //Add guard level == id
                                                                                newTrans->when = addConditionToList(newTrans->when,levelGuard);
                                                                                
                                                                                //Add transition to List of Transition
                                                                                locIterator->transitions = addTransitionToList(locIterator->transitions, newTrans);	
                                                                                //end of IF
                                                                        }
                                                                        trans = trans->next;
                                                                        //end of transition WHILE
                                                                }
                                                        }
                                                }
						//end of ELSE
					}
				} else if(stateEvent) {
                                        /* 
                                         * If the event is an @+(L) then a level change occurs on every location entering L and no normal transition is allowed at this level for those
                                         * If the event is an @-(L) then a level change is applicable on L only and normal transitions are allowed for others
                                         */
                                        
                                        if(locHasTransAtLevel(locIterator,id)==0){
                                        
                                                dnf=seq_expr->expr->dnf;
                                        
                                                char* context = getLocationContext(dnf->conjunct);
                                                
                                                printf("============> STATE-EVENT-CONTEXT = [%s]\n",context);
                                                if(id!=0 && (context!=NULL && strcmp(context,locIterator->name)!=0)){
                                                        int breakCycle = 0;
                                                        
                                                        /* 
                                                        * Make a copy of each original transitions, and guard it 
                                                        * with the level guard
                                                        */
                                                        if(breakCycle == 0){
                                                                struct transition* trans = locIterator->transitions;
                                                                //For each location P not satisfying Expr
                                                                while(trans!=NULL){
                                                                        //printf("trans->original = %d\n",(int)trans->original);
                                                                        if((int)(trans->original)==1){
                                                                                //Make a copy of each original Transition with level guard
                                                                                struct transition *newTrans = NULL;
                                                                                newTrans = addToTransitionList(newTrans,duplicateConditionList(trans->when),trans->sync,duplicateConditionList(trans->reset),trans->gotoLoc);
                                                                                newTrans->next = NULL;
                                                                                
                                                                                //Add guard level == id
                                                                                newTrans->when = addConditionToList(newTrans->when,levelGuard);
                                                                                
                                                                                //Add transition to List of Transition
                                                                                locIterator->transitions = addTransitionToList(locIterator->transitions, newTrans);     
                                                                                //end of IF
                                                                        }
                                                                        trans = trans->next;
                                                                        //end of transition WHILE
                                                                }
                                                        }
                                                        //end of ELSE
                                                }
                                        }
                                }
				
				
				
				//Check the next location
				locIterator = locIterator->next;
				//end of location WHILE
			}
			//end
			
			seq_expr = seq_expr->next;
			id++;
		//end of WHILE
		}
		
		#ifdef DEBUG_ON 
			printf("[levelSequence] Sequencing End\n");
		#endif
		
		//Setting level 0 transitions to be gated by level == 0
		#ifdef DEBUG_ON 
			printf("[levelSequence] Gating Level 0 transitions.\n");
		#endif
			
		locIterator = H->ha->locations;
		transIterator = NULL;
		
		while(locIterator!=NULL){
			transIterator = locIterator->transitions;
			while(transIterator!=NULL){
				if(transIterator->original == 1){
					#ifdef DEBUG_ON
						struct condition* condIterator = transIterator->when;
						while(condIterator!=NULL){
							printFeatureCondition(condIterator);
							printf("\t");
							condIterator = condIterator->next;
						}printf("\n");
					#endif
					
					transIterator->when = addConditionToList(transIterator->when,createCondition("level","0",0));
				} 
				transIterator = transIterator->next;
			}
			locIterator = locIterator->next;
		}
		
		//end of protective IF
		free(strID);
		#ifdef DEBUG_ON 
			printf("[levelSequence] Sequencing Ends\n");
		#endif
	}
	
	#ifdef DEBUG_ON 
		printf("[levelSequence] ENDED\n");
	#endif
	return H;
}

struct phaver* addTimeBound(struct phaver* HA, double bound){
	if(HA!=NULL){
		struct location* locIterator = HA->ha->locations;
		while(locIterator!=NULL){
			char *strBound  = (char*)malloc(sizeof(char)*MAX_STR_LENGTH);
			if(strcasecmp(locIterator->name,"final")==0)
				sprintf(strBound,"1");
			else sprintf(strBound,"%f",bound);
			
			struct condition* timeBound = createCondition("time",strBound,1);
			
			locIterator->invariant = addConditionToList(locIterator->invariant,timeBound);
			
			locIterator = locIterator->next;
		}
	}
	return HA;
}

/*int main(){
	struct condition porv;
	sprintf(&(porv.LHS),"x");
	sprintf(&(porv.RHS),"12");
	porv.op = 1;
	
	return 0;
}*/
