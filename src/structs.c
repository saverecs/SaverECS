#ifndef MAX_STR_LENGTH
	#define MAX_STR_LENGTH 4096
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include <ctype.h>
#include <map>
#include <unistd.h> /* for fork */
#include <sys/types.h> /* for pid_t */
#include <sys/wait.h> /* for wait */
#include <sys/time.h> /* for time */

#include <glib-object.h>
#include <json-glib/json-glib.h>

#include "structs.h"
#include "featureCompute.h"
#include "drhOutParser.tab.h"

extern FILE* drhOutin;
extern FILE* drhOutout;
extern int drhOutparse(void);
extern int kValue;
extern int lValue;
static int traceCount = 0;

/*-----------------------Operator Maps-------------------------*/
char* SpaceExOpMap(int op)
{
	char* ret = (char*)malloc(sizeof(char)*6);
	switch(op)
	{
		case -99 : sprintf(ret, " ");
		break;
		case 0 : sprintf(ret, "==");
		break;
		case 1 : sprintf(ret, "&lt;=");
		break;
		case 2 : sprintf(ret, "=");
		break;
		case 3 : sprintf(ret, "&gt;=");
		break;
		case 4 : sprintf(ret, "&lt;");
		break;
		case 5 : sprintf(ret, "&gt;");
		break;
		case 6 : sprintf(ret, "&amp;");
		break;
		default : sprintf(ret, "==");
	}
	return ret;
}

char* operatorMap(int op){	
	char *p=(char *)malloc(sizeof(char)*3);
	switch(op){
		case 0: sprintf(p,"==");break;
		case 1: sprintf(p,"<=");break;
		case 2: sprintf(p,":=");break;
		case 3: sprintf(p,">=");break;
		case 4: sprintf(p,"<");break;
		case 5: sprintf(p,">");break;
		default:sprintf(p,"==");break;
		
	}
	//printf("%s",p);
	return p;
}

/*-----------------------CONDITION----------------------------*/

struct condition* createCondition(char *LHS, char* RHS, int op){
	#ifdef DEBUG_ON 
		printf("[createCondition] STARTED\n");
	#endif
	struct condition* cond = (struct condition*)malloc(sizeof(struct condition));
		
	if(LHS!=NULL)
		strcpy(cond->LHS,LHS);
	if(RHS!=NULL)
		strcpy(cond->RHS,RHS);
	cond->op = op;
	cond->next = NULL;
	#ifdef DEBUG_ON 
		printf("[createCondition] CREATED NODE\n");
	#endif
	return cond;
}

struct condition* addConditionToList(struct condition* root, struct condition* cond){
	#ifdef DEBUG_ON 
		printf("[addConditionToList] STARTED\n");	
		printf("ROOT = %p ; cond = %p\n",root,cond);
	#endif
	struct condition* temp = root;
		
	if(root!=NULL){
		#ifdef DEBUG_ON 
			printf("[addConditionToList] CONDITION LIST NOT EMPTY\n");
		#endif
		
		while(temp->next!=NULL){
			if(temp == cond){
				return root;
			}
			temp=temp->next;
		}
		if(temp == cond){
			return root;
		}
		
		#ifdef DEBUG_ON 
			printf("[addConditionToList] ADDING TO CONDITION LIST\n");
			printf("temp = %p ; cond = %p\n",temp ,cond);
		#endif
			
		temp->next = cond;
	} else {
		#ifdef DEBUG_ON 
			printf("[addConditionToList] CONDITION LIST EMPTY\n");
			printf("[addConditionToList] ADDING TO CONDITION LIST\n");
		#endif
		
		root = cond;
		#ifdef DEBUG_ON 
			printf("[addConditionToList] ROOT CHANGED\n");
		#endif
		
	}
	#ifdef DEBUG_ON 
		printf("[addConditionToList] ADDED CONDITION\n");
	#endif
	
	return root;
}

struct condition* addToConditionList(struct condition* root, char *LHS, char* RHS, int op){
	#ifdef DEBUG_ON 
	printf("[addToConditionList] STARTED\n");
	#endif
	
	struct condition* cond = (struct condition*)malloc(sizeof(struct condition));
	struct condition* temp = root;
	
	strcpy(cond->LHS,LHS);
	strcpy(cond->RHS,RHS);
	cond->op = op;
	cond->next = NULL;
	#ifdef DEBUG_ON 
	printf("[addToConditionList] CRETED NODE\n");
	#endif
	
	
	if(root!=NULL){
		#ifdef DEBUG_ON 
		printf("[addToConditionList] CONDITION LIST NOT EMPTY\n");
		#endif
		
		while(temp->next!=NULL){
			temp=temp->next;
		}
		#ifdef DEBUG_ON 
		printf("[addToConditionList] ADDING TO CONDITION LIST\n");
		#endif
		
		temp->next = cond;
		
	} else {
		#ifdef DEBUG_ON 
		printf("[addToConditionList] CONDITION LIST EMPTY\n");
		printf("[addToConditionList] ADDING TO CONDITION LIST\n");
		#endif
		
		root = cond;
		
		#ifdef DEBUG_ON 
		printf("[addToConditionList] ROOT CHANGED\n");
		printf("[addToConditionList] ROOT = %p, NEXT = %p\n",root,root->next);
		#endif
		
	}
	#ifdef DEBUG_ON 
	printf("[addToConditionList] ADDED CONDITION %s %d %s\n",LHS,op,RHS);
	#endif
	
	return root;
}

struct condition* duplicateConditionList(struct condition* root){
	#ifdef DEBUG_ON 
	printf("[duplicateCondition] STARTED\n");
	#endif
	
	struct condition* temp = root;
	struct condition* newRoot = NULL;
	#ifdef DEBUG_ON 
	printf("[root = %p] %p \n",root,root!=NULL?root->next:NULL);
	#endif
	
	while(temp!=NULL){
		newRoot = addToConditionList(newRoot, temp->LHS, temp->RHS, temp->op);
		#ifdef DEBUG_ON 
		printf("[duplicateCondition] DUPLICATING NEXT CONDITION [%p] %s %s %d [%p]\n",temp,temp->LHS,temp->RHS,temp->op,temp->next);
		printf("[root = %p]\n",root);
		//if(temp == temp->next) temp->next=NULL;//exit(0);
		#endif
		
		temp = temp->next;
	}
	#ifdef DEBUG_ON 
	printf("[duplicateCondition] COMPLETED\n");
	#endif
	
	return newRoot;
}

struct condition* createIdentityResets(struct identifier* root){
	struct condition* reset = NULL;
	struct identifier* temp = root;
	char nameD[MAX_STR_LENGTH];
	
	
	while(temp!=NULL){
		sprintf(nameD,"%s'",temp->name);
		reset = addToConditionList(reset,nameD,temp->name,0);
		temp = temp->next;
	}
	return reset;
}

void printCondition(struct condition* cond){
	if(cond!=NULL){
		//printf("[%p] %s %s %s ",cond,cond->LHS,operatorMap(cond->op),cond->RHS);	
		printf("%s %s %s ",cond->LHS,operatorMap(cond->op),cond->RHS);	
	}
}

void printConditionList(struct condition* cond){
	printf("\n\n---------------CONDITION LIST-----------------\n");
	while(cond!=NULL){
		printf("\n");
		printCondition(cond);
		cond = cond->next;
	}
	printf("\n\n----------------------------------------------\n");
}

struct condition* reverseConditionList(struct condition* root){

	if(root==NULL){
		#ifdef DEBUG_ON 
			printf("[reverseConditionList] STARTED AND ENDED - NULL ROOT\n");
		#endif
	
		return NULL;
	}
	#ifdef DEBUG_ON 
		printf("[reverseConditionList] STARTED\n");
	#endif
	struct condition *prev, *current, *next;
	
	current = root;
	next=root->next;
	root->next = NULL;
	
	while(next!=NULL){
		prev = current;
		current = next;
		next = current->next;
		current->next = prev;
	}
	#ifdef DEBUG_ON 
		printf("[reverseConditionList] ENDED - returning current = %d\n",current);
	#endif
	
	return current;
}


void printInvariant(struct condition* invariant){
	while(invariant!=NULL){
		if(invariant->op == -1){
			printf("true");
		} else {
			printf("%s %s %s",invariant->LHS,phOperatorMap(invariant->op),invariant->RHS);
		}
		//printf("%s %s %s",invariant->LHS,phOperatorMap(invariant->op),invariant->RHS);
		if(invariant->next != NULL){
			printf(" & ");
		} else {
			printf("\n\t\t\t");
		}
		invariant = invariant->next;
	}
}

/*
 * Compares if a condition has a specified LHS with a specified RHS
 */
int conditionCompare(struct condition* cond, char* LHS, char* RHS){
        #ifdef DEBUG_ON 
        printf("[conditionCompare] STARTED\n");
        #endif

        if(cond){
                if(LHS){
                        if(strcmp(LHS,cond->LHS)==0){
                                if(RHS){
                                        if(strcmp(RHS,cond->RHS)==0)
                                                return 1;
                                }
                        }
                }
        }
        
        return 0;
        
        #ifdef DEBUG_ON 
        printf("[conditionCompare] STARTED\n");
        #endif
}


/*
 * Checks if a given LHS,RHS pair is present in the list of conditions
 */
int inConditionList(struct condition* list, char* LHS, char* RHS){
        #ifdef DEBUG_ON 
        printf("[inConditionList] STARTED\n");
        #endif

        while(list){
                if(conditionCompare(list,LHS,RHS)){
                        return 1;
                }
                list = list->next;
        }
        
        return 0;
        
        #ifdef DEBUG_ON 
        printf("[inConditionList] STARTED\n");
        #endif
}

int removeConditionFromList(struct condition** root, char* LHS){
        #ifdef DEBUG_ON 
        printf("[removeConditionFromList] STARTED\n");
        #endif
        
        if(*root && LHS){
                //printConditionList(*root);
                struct condition* prev = *root;
                struct condition* curr = *root;
                while(curr){
                        //printf("Comparing [%s] with [%s]\n",curr->LHS,LHS);
                        if(strncmp(curr->LHS,LHS,strlen(LHS))==0){
                                //printf("FOUND\n");
                                if(curr == *root){
                                        //printf("CURRENT IS ROOT\n");
                                        *root = curr->next;
                                        free(curr);
                                } else {
                                        prev->next = curr->next;
                                        free(curr);
                                }
                                break;
                        }
                        prev = curr;
                        curr = curr->next;
                }
                
                //printf("\nNow it is: \n");
                //printConditionList(*root);
        }
        
        #ifdef DEBUG_ON 
        printf("[removeConditionFromList] ENDED\n");
        #endif
}

/*-----------------------IDENTIFIER-----------------------------*/
struct identifier* createIdentifier(char *id){
	#ifdef DEBUG_ON 
	printf("[createIdentifier] STARTED\n");
	#endif
	
	struct identifier* ID = (struct identifier*)malloc(sizeof(struct identifier));
	ID->next = NULL;
	strcpy(ID->name,id);
	#ifdef DEBUG_ON 
	printf("[createIdentifier] CRETED NODE\n");
	#endif
	
	
	return ID;
}

struct identifier* addIdentifierToList(struct identifier* root, struct identifier* ID){
	#ifdef DEBUG_ON 
	printf("[addIdentifierToList] STARTED\n");
		#endif
	
	struct identifier* temp = root;
	
	if(root!=NULL){
		#ifdef DEBUG_ON 
		printf("[addIdentifierToList] ID LIST NOT EMPTY\n");
		#endif
		
		while(temp->next!=NULL){
			temp=temp->next;
		}
		#ifdef DEBUG_ON 
		printf("[addIdentifierToList] ADDING TO ID LIST\n");
		#endif
		
		temp->next = ID;
	} else {
		#ifdef DEBUG_ON 
		printf("[addIdentifierToList] ID LIST EMPTY\n");
		printf("[addIdentifierToList] ADDING TO ID LIST\n");
		#endif
		
		root = ID;
		#ifdef DEBUG_ON 
		printf("[addIdentifierToList] ROOT CHANGED: ROOT->NAME = %s\n",root->name);
		#endif
		
	}
	#ifdef DEBUG_ON 
	printf("[addIdentifierToList] ADDED IDENTIFIER [%s]\n",ID->name);
	#endif
	
	return root;
}

struct identifier* addToIdentifierList(struct identifier* root, char *id){
	#ifdef DEBUG_ON 
	printf("[addToIdentifierList] STARTED\n");
	#endif
	
	struct identifier* ID = (struct identifier*)malloc(sizeof(struct identifier));
	struct identifier* temp = root;
	ID->next = NULL;
	strcpy(ID->name,id);
	#ifdef DEBUG_ON 
	printf("[addToIdentifierList] CRETED NODE\n");
	#endif
	
	if(root!=NULL){
		#ifdef DEBUG_ON 
		printf("[addToIdentifierList] ID LIST NOT EMPTY\n");
		#endif
		
		while(temp->next!=NULL){
			temp=temp->next;
		}
		#ifdef DEBUG_ON 
		printf("[addToIdentifierList] ADDING TO ID LIST\n");
		#endif
		
		temp->next = ID;
	} else {
		#ifdef DEBUG_ON 
		printf("[addToIdentifierList] ID LIST EMPTY\n");
		printf("[addToIdentifierList] ADDING TO ID LIST\n");
		#endif
		
		root = ID;
		#ifdef DEBUG_ON 
		printf("[addToIdentifierList] ROOT CHANGED: ROOT->NAME = %s\n",root->name);
		#endif
		
	}
	#ifdef DEBUG_ON 
	printf("[addToIdentifierList] ADDED IDENTIFIER [%s]\n",id);
	#endif
	
	return root;
}

int getIdentifierID(struct identifier* list, char *name){
	struct identifier* temp = list;
	int count=0;
	while(temp!=NULL){
		count++;
		if(strcmp(temp->name,name)==0){
			return count;
		}
		temp=temp->next;
	}	
	return 0;
}

struct identifier* duplicateIdentifierList(struct identifier* root){
	#ifdef DEBUG_ON 
	printf("[duplicateIdentifierList] STARTED\n");
	#endif
	
	struct identifier* temp = root;
	struct identifier* newRoot = NULL;
	while(temp!=NULL){
		newRoot = addToIdentifierList(newRoot, temp->name);
		temp = temp->next;
	}
	#ifdef DEBUG_ON 
	printf("[duplicateIdentifierList] COMPLETED\n");
	#endif
	
	return newRoot;
}

void freeIdentifierList(struct identifier* id){
	if(id!=NULL){
		freeIdentifierList(id->next);
		free(id);
	}
}

char* containsIdentifier(struct identifier* list1, struct identifier* list2){
	struct identifier* temp = list1;
	while(temp){
		if(getIdentifierID(list2,temp->name)==0){
			char* err = (char*)malloc(sizeof(char)*MAX_STR_LENGTH);
			sprintf(err,"Identifier [%s] not declared in the the signature of the module.\n",temp->name);
			return err;			
		}
		temp = temp->next;
	}
	return NULL;
}


void printIdentifier(struct identifier* id){
	if(id!=NULL){
		//printf("[%p] %s %s %s ",cond,cond->LHS,operatorMap(cond->op),cond->RHS);
		printf("Addrs: %p\n",id);
		printf("Name: %s\n",id->name);	
		printf("Next: %p\n\n",id->next);
	}
}

void printIdentifierList(struct identifier* id){
	printf("\n\n---------------IDENTIFIER LIST-----------------\n");
	while(id!=NULL){	
		printIdentifier(id);	
		//printf("%s, ",id->name);
		id = id->next;
	}
	printf("\n\n----------------------------------------------\n");
}


/*-----------------------TRANSITION-----------------------------*/

struct transition* createTransition(struct condition* when, char *sync, struct condition* reset, char* gotoLoc){
	#ifdef DEBUG_ON 
	printf("[createTransition] STARTED\n");
	#endif
	
	struct transition* trans = (struct transition*)malloc(sizeof(struct transition));
	
	strcpy(trans->sync,sync);
	strcpy(trans->gotoLoc,gotoLoc);
	trans->when = when;
	trans->reset = reset;
	trans->next = NULL;
	trans->original = 0;
	
	#ifdef DEBUG_ON 
	printf("[createTransition] CRETED NODE\n");
	#endif
	
	return trans;
}

struct transition* addTransitionToList(struct transition* root, struct transition* trans){
	#ifdef DEBUG_ON 
	printf("[addTransitionToList] STARTED\n");
	#endif
	
	struct transition* temp = root;
	
	if(root!=NULL){
		#ifdef DEBUG_ON 
		printf("[addTransitionToList] TRANSITION LIST NOT EMPTY\n");
		#endif
		
		while(temp->next!=NULL){
			temp=temp->next;
		}
		#ifdef DEBUG_ON 
		printf("[addTransitionToList] ADDING TO TRANSITION LIST\n");
		#endif
		
		temp->next = trans;
	} else {
		#ifdef DEBUG_ON 
		printf("[addTransitionToList] TRANSITION LIST EMPTY\n");
		printf("[addTransitionToList] ADDING TO TRANSITION LIST\n");
		#endif
		
		root = trans;
		#ifdef DEBUG_ON 
		printf("[addTransitionToList] ROOT CHANGED\n");
		#endif
		
	}
	#ifdef DEBUG_ON 
	printf("[addTransitionToList] ADDED TRANSITION TO [%s]\n",trans->gotoLoc);
	#endif
	
	return root;
}

struct transition* addToTransitionList(struct transition* root, struct condition* when, char *sync, struct condition* reset, char* gotoLoc){
	#ifdef DEBUG_ON 
	printf("[addToTransitionList] STARTED\n");
	#endif
	
	struct transition* trans = (struct transition*)malloc(sizeof(struct transition));
	struct transition* temp = root;
	
	strcpy(trans->sync,sync);
	strcpy(trans->gotoLoc,gotoLoc);
	trans->when = duplicateConditionList(when);
	trans->reset = duplicateConditionList(reset);
	trans->next = NULL;
	trans->original = 0;
	
	#ifdef DEBUG_ON 
	printf("[addToTransitionList] CRETED NODE\n");
	#endif
	
	
	if(root!=NULL){
		#ifdef DEBUG_ON 
		printf("[addToTransitionList] TRANSITION LIST NOT EMPTY\n");
		#endif
		
		while(temp->next!=NULL){
			temp=temp->next;
		}
		#ifdef DEBUG_ON 
		printf("[addToTransitionList] ADDING TO TRANSITION LIST\n");
		#endif
		
		temp->next = trans;
	} else {
		#ifdef DEBUG_ON 
		printf("[addToTransitionList] TRANSITION LIST EMPTY\n");
		printf("[addToTransitionList] ADDING TO TRANSITION LIST\n");
		#endif
		
		root = trans;
		#ifdef DEBUG_ON 
		printf("[addToTransitionList] ROOT CHANGED\n");
		#endif
		
	}
	#ifdef DEBUG_ON 
	printf("[addToTransitionList] ADDED TRANSITION TO [%s]\n",gotoLoc);
	printf("[addToTransitionList] ENDED\n");
	#endif
	
	return root;
}

struct transition* addTransitionToLocationTransitionList(struct location* loc, struct transition* trans){
	if(loc!=NULL){
		#ifdef DEBUG_ON
			printf("[addTransitionToLocationTransitionList] Loc not null, loc->transitions = [%p]\n",loc->transitions);
		#endif
			
		loc->transitions = addTransitionToList(loc->transitions,trans);
		return loc->transitions;
	}
}

struct transition* duplicateTransision(struct transition* temp){
	#ifdef DEBUG_ON 
	printf("[duplicateTransition] STARTED\n");
	#endif
	struct transition* newRoot = NULL;
	
	if(temp!=NULL){
		struct condition* when = NULL;
		struct condition* reset = NULL;
		when = duplicateConditionList(temp->when);
		reset = duplicateConditionList(temp->reset);
		newRoot = addToTransitionList(newRoot, when, temp->sync, reset, temp->gotoLoc);		
	}
	
	#ifdef DEBUG_ON 
	printf("[duplicateTransition] COMPLETED\n");
	#endif
	
	return newRoot;
}

struct transition* duplicateTransitionList(struct transition* root){
	#ifdef DEBUG_ON 
	printf("[duplicateTransitionList] STARTED\n");
	#endif
	
	struct transition* temp = root;
	struct transition* newRoot = NULL;
	while(temp!=NULL){
		struct condition* when = NULL;
		struct condition* reset = NULL;
		when = duplicateConditionList(temp->when);
		reset = duplicateConditionList(temp->reset);
		newRoot = addToTransitionList(newRoot, when, temp->sync, reset, temp->gotoLoc);
		temp = temp->next;
	}
	#ifdef DEBUG_ON 
	printf("[duplicateTransitionList] COMPLETED\n");
	#endif
	
	return newRoot;
}

/*
 * Checks if a location has any transition out of the location with the specified level
 */
int locHasTransAtLevel(struct location* loc, int level){
        #ifdef DEBUG_ON 
        printf("[locHasTransAtLevel] STARTED\n");
        #endif
        
        if(loc){
                struct transition* trans = loc->transitions;
                char* levelStr = "level";
                char valStr[MAX_STR_LENGTH];
                sprintf(valStr,"%d",level);
                
                while(trans){
                        if(inConditionList(trans->when,levelStr,valStr)){
                                #ifdef DEBUG_ON 
                                printf("[locHasTransAtLevel] ENDED\n");
                                #endif
                                return 1;
                        }
                        trans = trans->next;
                }
        }
        
        return 0;
        
        #ifdef DEBUG_ON 
        printf("[locHasTransAtLevel] ENDED\n");
        #endif
}


struct transitionWrapper* addToPseudoTransitionList(struct transitionWrapper* root, struct location* loc, struct transition* trans){
	#ifdef DEBUG_ON 
	printf("[addToPseudoTransitionList] STARTED\n");
	#endif
	
	struct transitionWrapper* temp = root;
	struct transitionWrapper* transW = (struct transitionWrapper*)malloc(sizeof(struct transitionWrapper));
	
	transW->trans = trans;
	transW->loc = loc;
	transW->next=NULL;
	
	#ifdef DEBUG_ON 
	printf("[addToPseudoTransitionList] CRETED NODE\n");
	#endif
	
	
	if(root!=NULL){
		#ifdef DEBUG_ON 
		printf("[addToPseudoTransitionList] PSEUDO TRANSITION LIST NOT EMPTY\n");
		#endif
		
		while(temp->next!=NULL){
			temp=temp->next;
		}
		#ifdef DEBUG_ON 
		printf("[addToPseudoTransitionList] ADDING TO PSEUDO TRANSITION LIST\n");
		#endif
		
		temp->next = transW;
		//transW->id = temp->id + 1;
	} else {
		#ifdef DEBUG_ON 
		printf("[addToPseudoTransitionList] PSEUDO TRANSITION LIST EMPTY\n");
		printf("[addToPseudoTransitionList] ADDING TO PSEUDO TRANSITION LIST\n");
		#endif
		
		root = transW;
		//transW->id=0;
		#ifdef DEBUG_ON 
		printf("[addToPseudoTransitionList] ROOT CHANGED\n");
		#endif
		
	}
	#ifdef DEBUG_ON 
	printf("[addToPseudoTransitionList] ADDED PSEUDO TRANSITION [%s]\n",loc->name);
	#endif
	
	return root;
}


struct transition* createTransitionOnEvent(struct condition* eventCond, char* syncLabel, struct condition* resets, char* gotoLoc, struct identifier* localVars){
	if(eventCond!=NULL && syncLabel!=NULL && gotoLoc!=NULL && localVars!=NULL){
		#ifdef DEBUG_ON
			printf("[createTransitionOnEvent] STARTED [eventCond = %p, syncLabel = %s, gotoLoc = [%s], localVars = [%s]\n",eventCond,syncLabel,gotoLoc,localVars);
		#endif	
		/*struct condition* tempNext = eventCond->next;
		eventCond->next = NULL;
		
		struct condition* whenCond = duplicateConditionList(eventCond);
		eventCond->next = tempNext;
		tempNext = NULL;
		*/
		struct transition* trans = createTransition(/*whenCond*/ eventCond, syncLabel, resets, gotoLoc);
		
		//Create Identity Resets
		
		while(localVars!=NULL){
			//Add Identity Resets in Outgoing Transitions
			if(strcmp(localVars->name,"level")!=0 && strcmp(localVars->name,"time")!=0)
				addIdentityResetToTransition(trans,localVars->name);
			
			localVars = localVars->next;
		}
		trans->original = 0;
		return trans;
	}
	
	if(eventCond == NULL && syncLabel!=NULL && gotoLoc!=NULL && localVars!=NULL){
		#ifdef DEBUG_ON
			printf("[createTransitionOnEvent] STARTED [eventCond = NULL, syncLabel = %s, gotoLoc = [%s], localVars = [%s]\n",syncLabel,gotoLoc,localVars);
		#endif
		
		struct transition* trans = createTransition(NULL, syncLabel, NULL, gotoLoc);
		
		//Create Identity Resets
		
		while(localVars!=NULL){
			//Add Identity Resets in Outgoing Transitions
			if(strcmp(localVars->name,"level")!=0)
				addIdentityResetToTransition(trans,localVars->name);
			
			localVars = localVars->next;
		}
		trans->original = 0;
		return trans;		
	}
	return NULL;
}

/*
 * Duplicate contents of "transList"
 */
struct transitionWrapper* duplicatePseudoTransitionList(struct transitionWrapper* transList){
	if(transList!=NULL){
		#ifdef DEBUG_ON 
			printf("[duplicatePseudoTransitionList] STARTED\n");
		#endif
		struct transitionWrapper* transNew = (struct transitionWrapper*)malloc(sizeof(struct transitionWrapper));
		
		transNew->loc = transList->loc;
		transNew->trans = transList->trans;
		
		transNew->next = duplicatePseudoTransitionList(transList->next);
		
		#ifdef DEBUG_ON 
			if(transNew->next == NULL){
				printf("[duplicatePseudoTransitionList] End of TransitionList\n");
			}
			
			printf("[duplicatePseudoTransitionList] CREATED Duplicate TransitionList\n");
		#endif
		
		return transNew;
	}
	return NULL;
}


void freeIncomingTransitions(struct transitionWrapper* incoming){
	#ifdef DEBUG_ON 
		printf("[freeIncomingTransitions] STARTED\n");
	#endif
	struct transitionWrapper* next = NULL;
	//int flag = 0;
	//next = incoming;
/*	while(next!=NULL){
		printf("I'm ok\n");
		flag = 1;
		next = next->next;
	}
	printf("I reached here now\n");fflush(stdout);fflush(stderr);
	while(flag==1 & incoming!=NULL){
		next = incoming->next;
		free(incoming);
		incoming = next;		
	}
	*/
	if(incoming!=NULL){
		freeIncomingTransitions(incoming->next);
		#ifdef DEBUG_ON
			printf("incoming = %p\n",incoming);
		#endif
			
		free(incoming);
	}
	#ifdef DEBUG_ON 
		printf("[freeIncomingTransitions] ENDED\n");
	#endif
}

void processIncomingTransitions(struct location* root){
	#ifdef DEBUG_ON 
		printf("[processIncomingTransitions] STARTED\n");
	#endif
	
	struct location* locList = root;
	//Free All incoming lists
	while(locList!=NULL){
		#ifdef DEBUG_ON 
		printf("Incoming = %p\n",locList->incoming);
		#endif
		freeIncomingTransitions(locList->incoming);
		locList->incoming = NULL;
		locList = locList->next;
	}
	
	#ifdef DEBUG_ON 
		printf("[processIncomingTransitions] Cleant up all incoming transitions\n");
		printf("[processIncomingTransitions] Setting new transitions in place\n");
	#endif
	
	locList = root;
	while(locList!=NULL){
		// For each location in the Automaton		
		struct transition* transList = locList->transitions;
		while(transList!=NULL){
			/* 
			 * For each outgoing transition (source,dest) add an incoming 
			 * transition (source,dest) to dest
			 */
			struct location* dest = getLocationByName(root, transList->gotoLoc);
			dest->incoming = addToPseudoTransitionList(dest->incoming,locList,transList);
			transList = transList->next;
		}
		locList = locList->next;
	}
	
	#ifdef DEBUG_ON 
	printf("[processIncomingTransitions] ENDED\n");
	#endif
}

void printTransition(struct transition* transition){
	struct condition* reset;
	struct condition* when;
	when = transition->when;
	reset= transition->reset;
	
	printf("\n\t\t\twhen ");
	
	while(when!=NULL){
		printf("%s %s %s",when->LHS,phOperatorMap(when->op),when->RHS);
		
		if(when->next != NULL){
			printf(" & ");
		} else {
			printf("\n\t\t\t");
		}
		when=when->next;
	}
	printf("sync %s do { ",transition->sync);
	//int flag = 0; char timeLabel[5]; sprintf(timeLabel,"time");	
	while(reset!=NULL){
		/*
		if(flag == 0 && strcmp(reset->RHS,timeLabel)==0)
			flag = 1;
		if (flag==1 && strcmp(reset->RHS,timeLabel)==0) 
			printf("Houston we have a problem in the list\n");
		*/
		printf("%s %s %s",reset->LHS,"==",reset->RHS);
		if(reset->next != NULL){
			printf(" & ");
		} else {
			printf(" }\n\t\t\t");
		}
		reset=reset->next;
	}
	printf("goto %s;\n",transition->gotoLoc);
}



/*-----------------------INITIAL-----------------------------*/

struct initial* createInitial(struct identifier* init_locs, struct condition* init_conds){
	#ifdef DEBUG_ON 
	printf("[createInitial] STARTED\n");
	#endif
	
	struct initial* init = (struct initial*)malloc(sizeof(struct initial));
	
	init->init_conds = init_conds;
	init->init_locs = init_locs;
	init->next = NULL;
	
	#ifdef DEBUG_ON 
	printf("[createInitial] CRETED NODE\n");
	#endif
	
	
	return init;
}

struct initial* addInitialToList(struct initial* root, struct initial* init){
	#ifdef DEBUG_ON 
	printf("[addInitialToList] STARTED\n");
	#endif
	
	struct initial* temp = root;
	
	if(root!=NULL){
		#ifdef DEBUG_ON 
		printf("[addInitialToList] INITIAL LIST NOT EMPTY\n");
		#endif
		
		while(temp->next!=NULL){
			temp=temp->next;
		}
		#ifdef DEBUG_ON 
		printf("[addInitialToList] ADDING TO INITIAL LIST\n");
		#endif
		
		temp->next = init;
	} else {
		#ifdef DEBUG_ON 
		printf("[addInitialToList] INITIAL LIST EMPTY\n");
		printf("[addInitialToList] ADDING TO INITIAL LIST\n");
		#endif
		
		root = init;
		#ifdef DEBUG_ON 
		printf("[addInitialToList] ROOT CHANGED\n");
		#endif
		
	}
	#ifdef DEBUG_ON 
	printf("[addInitialToList] ADDED INITIAL \n");
	#endif
	
	return root;
}

/*
 * Duplicate contents of "Initial"
 */
struct initial* duplicateInitialList(struct initial* init){
	if(init!=NULL){
		#ifdef DEBUG_ON 
			printf("[duplicateInitialList] STARTED\n");
		#endif
		struct initial* initNew = (struct initial*)malloc(sizeof(struct initial));
		
		initNew->init_locs = duplicateIdentifierList(init->init_locs);
		initNew->init_conds = duplicateConditionList(init->init_conds);
		initNew->next = duplicateInitialList(init->next);
		
		#ifdef DEBUG_ON 
			if(initNew->next == NULL){
				printf("[duplicateInitialList] End of Initial List\n");
			}
			
			printf("[duplicateInitialList] CREATED Duplication Initial List\n");
		#endif
		
		return initNew;
	}
	return NULL;
}

/*
 * Duplicate contents of "Initial"
 */
struct initial* duplicateInitialConditions(struct initial* init){
	if(init!=NULL){
		#ifdef DEBUG_ON 
			printf("[duplicateInitialConditions] STARTED\n");
		#endif
		struct initial* initNew = (struct initial*)malloc(sizeof(struct initial));
		
		initNew->init_locs = duplicateIdentifierList(init->init_locs);
		initNew->init_conds = duplicateConditionList(init->init_conds);
		initNew->next = NULL;
		
		#ifdef DEBUG_ON 
			printf("[duplicateInitialConditions] CREATED Duplication Initial List\n");
		#endif
		return initNew;
	}
	return NULL;
}

/*
 * Return initial condition if location is an initial location
 */
struct initial* checkInitial(struct location* loc, struct initial* init){
	if(loc!=NULL && init!=NULL){
		while(init!=NULL){
			if(strcmp(loc->name, init->init_locs->name)==0){
				return init;
			}
			init = init->next;
		}
	} 
	return NULL;
}

void printInitial(struct initial* init){
	struct identifier* init_locs = NULL;
	struct condition* init_conds = NULL;
	printf("\ninitially: ");
	while(init!=NULL){
		init_locs = init->init_locs;
		init_conds = init->init_conds;
		
		while(init_locs!=NULL){
			printf("%s",init_locs->name);
			if(init_locs->next != NULL){
				printf(" & ");
			} else {
				if(init_conds != NULL)
					printf(" & ");
			}
			init_locs=init_locs->next;
		}
		while(init_conds!=NULL){
			printf("%s %s %s",init_conds->LHS,phOperatorMap(init_conds->op),init_conds->RHS);
			if(init_conds->next != NULL){
				printf(" & ");
			} 
			init_conds=init_conds->next;
		}
		if(init->next!=NULL){
			printf(", ");
		} else printf(";\n");
		init = init->next;
	}
}

void printSpaceExConfigInitial(char* name, struct initial* init,FILE* out){
	struct identifier* init_locs = NULL;
	struct condition* init_conds = NULL;
	fprintf(out,"initially = \"");
	while(init!=NULL){
		init_locs = init->init_locs;
		init_conds = init->init_conds;
		//fprintf(out," ( ");
		while(init_locs!=NULL){
			//fprintf(out,"( loc(%s_bind) == %s",name,init_locs->name);
			fprintf(out," loc(%s_bind) == %s",name,init_locs->name);
			if(init_locs->next != NULL){
				fprintf(out," | ");
			} else {
				//if(init_conds != NULL) fprintf(out," ) & ");
				//else fprintf(out," )");
				if(init_conds != NULL) fprintf(out," & ");
				
			}
			init_locs=init_locs->next;
		}
		while(init_conds!=NULL){
			fprintf(out,"%s %s %s",init_conds->LHS,phOperatorMap(init_conds->op),init_conds->RHS);
			if(init_conds->next != NULL){
				fprintf(out," & ");
			} 
			init_conds=init_conds->next;
		}
		if(init->next!=NULL){
			//fprintf(out," ) | ");
			fprintf(out," | ");
		}// else fprintf(out," ) ");
		init = init->next;
		
	}
	fprintf(out,"\"\n");
}


/*-----------------------LOCATION-----------------------------*/


struct location* createLocation(char *name, struct condition* invariant, struct condition* derivative, struct transition* transitions/*,int req*/){
	
	#ifdef DEBUG_ON 
		printf("[createLocation] STARTED\n");
	#endif
	
	struct location* loc = (struct location*)malloc(sizeof(struct location));
		
	strcpy(loc->name,name);
	loc->originalName = NULL;
	loc->invariant = invariant;
	loc->derivative = derivative;
	loc->transitions = transitions;
	//loc->requires = req;
	loc->next = NULL;
	loc->labels = NULL;
	loc->type = 0;
	#ifdef DEBUG_ON 
		printf("[createLocation] CRETED NODE\n");
	#endif
	
	
	return loc;
}

struct location* addLocationToList(struct location* root, struct location* loc){
	#ifdef DEBUG_ON 
		printf("[addLocationToList] STARTED\n");
	#endif
	
	
	struct location* temp = root;
	
	if(root!=NULL){
		#ifdef DEBUG_ON 
			printf("[addLocationToList] LOCATION LIST NOT EMPTY\n");
		#endif
		
		while(temp->next!=NULL){
			temp=temp->next;
		}
		#ifdef DEBUG_ON 
			printf("[addLocationToList] ADDING TO LOCATION LIST\n");
		#endif
		
		temp->next = loc;
	} else {
		#ifdef DEBUG_ON 
			printf("[addLocationToList] LOCATION LIST EMPTY\n");
			printf("[addLocationToList] ADDING TO LOCATION LIST\n");
		#endif
		
		root = loc;
		#ifdef DEBUG_ON 
			printf("[addLocationToList] ROOT CHANGED\n");
		#endif
		
	}
	#ifdef DEBUG_ON 
	printf("[addLocationToList] ADDED LOCATION [%s]\n",loc->name);
	#endif
	
	return root;
}

struct location* addToLocationList(struct location* root, char *name, struct condition* invariant, struct condition* derivative, struct transition* transitions, int locType/*,int req*/){
	#ifdef DEBUG_ON 
	printf("[addToLocationList] STARTED\n");
	#endif
	
	struct location* loc = (struct location*)malloc(sizeof(struct location));
	struct location* temp = root;
	
	strcpy(loc->name,name);
	loc->invariant = invariant;
	loc->derivative = derivative;
	loc->transitions = transitions;
	//loc->requires = req;
	loc->next = NULL;
	loc->labels = NULL;
	loc->originalName = NULL;
	loc->type = locType;
	#ifdef DEBUG_ON 
	printf("[addToLocationList] CRETED NODE\n");
	#endif
	
	
	if(root!=NULL){
		#ifdef DEBUG_ON 
		printf("[addToLocationList] LOCATION LIST NOT EMPTY\n");
		#endif
		
		while(temp->next!=NULL){
			temp=temp->next;
		}
		#ifdef DEBUG_ON 
		printf("[addToLocationList] ADDING TO LOCATION LIST\n");
		#endif
		
		temp->next = loc;
	} else {
		#ifdef DEBUG_ON 
		printf("[addToLocationList] LOCATION LIST EMPTY\n");
		printf("[addToLocationList] ADDING TO LOCATION LIST\n");
		#endif
		
		root = loc;
		#ifdef DEBUG_ON 
		printf("[addToLocationList] ROOT CHANGED\n");
		#endif
		
	}
	#ifdef DEBUG_ON 
	printf("[addToLocationList] ADDED LOCATION [%s]\n",name);
	#endif
	
	return root;
}


struct locationWrapper* addToPseudoLocationList(struct locationWrapper* root, struct location* loc){
	#ifdef DEBUG_ON 
	printf("[addToPseudoLocationList] STARTED\n");
	#endif
	
	struct locationWrapper* temp = root;
	struct locationWrapper* locW = (struct locationWrapper*)malloc(sizeof(struct locationWrapper));
	locW->loc = loc;
	locW->next=NULL;
	#ifdef DEBUG_ON 
	printf("[addToPseudoLocationList] CRETED NODE\n");
	#endif
	
	if(root!=NULL){
		#ifdef DEBUG_ON 
		printf("[addToPseudoLocationList] LOCATION LIST NOT EMPTY\n");
		#endif
		
		while(temp->next!=NULL){
			temp=temp->next;
		}
		#ifdef DEBUG_ON 
		printf("[addToPseudoLocationList] ADDING TO LOCATION LIST\n");
		#endif
		
		temp->next = locW;
		locW->id = temp->id + 1;
	} else {
		#ifdef DEBUG_ON 
		printf("[addToPseudoLocationList] LOCATION LIST EMPTY\n");
		printf("[addToPseudoLocationList] ADDING TO LOCATION LIST\n");
		#endif
		
		root = locW;
		locW->id=0;
		#ifdef DEBUG_ON 
		printf("[addToPseudoLocationList] ROOT CHANGED\n");
		#endif
		
	}
	#ifdef DEBUG_ON 
	printf("[addToPseudoLocationList] ADDED LOCATION [%s]\n",loc->name);
	#endif
	
	return root;
}

void printPseudoLocationList(struct locationWrapper *root){
	if(root!=NULL){
		#ifdef DEBUG_ON 
		printf("[printPseudoLocationList] STARTED\n");
		#endif
		
		struct locationWrapper* locationIterator = root;
		while(locationIterator!=NULL){
			
			if(locationIterator->loc->originalName==NULL){
				printf("Unsplit Location [%s]\n",locationIterator->loc->name);
			} else {
				printf(" Split  Location [%s], originally Location [%s]\n",locationIterator->loc->name,locationIterator->loc->originalName);
			} 
			locationIterator = locationIterator->next;
		}
		
		#ifdef DEBUG_ON 
		printf("[printPseudoLocationList] ENDED\n");
		#endif
		
	}
}


void freePseudoLocationList(struct locationWrapper* root){
	#ifdef DEBUG_ON 
	printf("[freePseudoLocationList] STARTED\n");
	#endif
	if(root!=NULL){
		#ifdef DEBUG_ON 
		printf("[freePseudoLocationList] Freeing Next Root [%p]\n",root->next);
		#endif
		
		freePseudoLocationList(root->next);
		#ifdef DEBUG_ON 
		printf("[freePseudoLocationList] Freeing Current Root [%p]\n",root);
		#endif
		free(root);
	}
	#ifdef DEBUG_ON 
	printf("[freePseudoLocationList] ENDED\n");
	#endif
}
/*
 * Duplicate contents of "loc"
 */
struct location* duplicateLocation(struct location* loc){
	if(loc!=NULL){
		#ifdef DEBUG_ON 
			printf("[duplicateLocation] STARTED\n");
		#endif
		struct location* locNew = (struct location*)malloc(sizeof(struct location));
		
		strcpy(locNew->name,loc->name);
		
		locNew->invariant = duplicateConditionList(loc->invariant);
		locNew->derivative = duplicateConditionList(loc->derivative);
		locNew->transitions = duplicateTransitionList(loc->transitions);
		locNew->labels = duplicatePORVList(loc->labels);
		//locNew->requires = loc->requires;
		
		if(loc->originalName!=NULL){
			locNew->originalName = (char*)malloc(sizeof(char)*MAX_STR_LENGTH);
			strcpy(locNew->originalName,loc->originalName);
		} else {
			locNew->originalName = NULL;
		}
		
		#ifdef DEBUG_ON 
			printf("[duplicateLocation] Duplicating Incoming Transition List\n");
		#endif
		
		locNew->incoming = duplicatePseudoTransitionList(loc->incoming);
		locNew->next = NULL;
		
		#ifdef DEBUG_ON 
			printf("[duplicateLocation] CRETED LOCATION\n");
		#endif
			
		return locNew;
	}
	return NULL;
}

/*
char* cleanLocationName(char *locName){
	int iterator = 0;
	char *cleanName = (char *)malloc(sizeof(char) * 1024);
	while(locName[iterator] != '\0' || locName[iterator] != '_'){
		cleanName[iterator] = locName[iterator];
		iterator++;
	}
	cleanName[iterator]='\0';
	return cleanName;
}
*/

int isMarked(struct locationWrapper* markedList, struct location *loc){
	#ifdef DEBUG_ON
		printf("[isMarked] STARTED\n");
	#endif
	
	if(markedList!=NULL && loc!=NULL){
		struct locationWrapper* iterator = markedList;
		while(iterator!=NULL){
			#ifdef DEBUG_ON
				printf("[isMarked] (Split location [TER CHECK) Iterator Location = [%p] checked with Input Location [%p]\n",iterator->loc,loc);
			#endif
			
			if(iterator->loc == loc){
				#ifdef DEBUG_ON
					printf("[isMarked] Found Location Marked. ENDED\n");
				#endif
				return 1;
			}
			iterator = iterator->next;
		}
		#ifdef DEBUG_ON
			printf("[isMarked] Nothing found. ENDED\n");
		#endif
		
		return 0;
	}
	#ifdef DEBUG_ON
	printf("[isMarked] ENDED\n");
	#endif
	return 0;
}

struct location* getLocationByName(struct location* root, char *locName){
	if(root!=NULL){
		struct location* iterator = root;
		while(iterator!=NULL){
			if(strcmp(iterator->name,locName)==0){
				return iterator;
			}
			iterator = iterator->next;
		}
	} else return NULL;
}

//Need to keep track of which location has already been returned
//Do this in a location wrapper list
struct location* getUnmarkedLocation(struct location* root, char *locName, struct locationWrapper* marked){
	#ifdef DEBUG_ON
	printf("[getUnmarkedLocation] STARTED\n");
	#endif
	//Check for Null Location List
	if(root!=NULL){
		//Get the list of marked/visited locations ===> list
		//The current location being analysed in each iteration will be given by ==> iterator
		struct location* iterator = root;
		while(iterator!=NULL){
			//char *cleanName = cleanLocationName(iterator->name);
			#ifdef DEBUG_ON
				char* strTemp = (char*)malloc(sizeof(char)*(isMarked(marked,iterator)?3:7));
				if(isMarked(marked,iterator)){
					sprintf(strTemp,"IS");
				} else sprintf(strTemp,"IS NOT");
				printf("[getUnmarkedLocation] Checking [%s] Location : [%s] and Location %s Marked\n",locName,(iterator->originalName==NULL)?iterator->name:iterator->originalName,strTemp);
			#endif
			
			//If the location has not yet been split. The locations name is it's original name.
			if(iterator->originalName==NULL && isMarked(marked,iterator)==0){
				#ifdef DEBUG_ON
				printf("[getUnmarkedLocation] The location [%s] is unmarked.\n",iterator->name );
				#endif
				if(strcmp(iterator->name,locName)==0){
					//Mark the location as visited
					//*marked = addToPseudoLocationList(*marked,iterator);
					
					#ifdef DEBUG_ON
					printf("[getUnmarkedLocation] Matched [%s] Unsplit Location : [%s]\n",locName,iterator->name);
					#endif
					//Return the location as the next location to split.
					return iterator;
				}
			} else if(iterator->originalName!=NULL){
				//If the location was previously split, we'll be in this block.
				#ifdef DEBUG_ON
				printf("[getUnmarkedLocation] The location has been previously split.\n");
				#endif
				//The locations original name is given by the "originalName" field.
				if(strcmp(iterator->originalName,locName)==0 && isMarked(marked,iterator)==0){
					#ifdef DEBUG_ON
					printf("[getUnmarkedLocation] The location [%s] is unmarked.\n",iterator->name);
					#endif
					//Location is unmarked, mark the location and return it.
					//*marked = addToPseudoLocationList(*marked,iterator);
					
					#ifdef DEBUG_ON
					printf("[getUnmarkedLocation] FOUND : [%s]\n",iterator->originalName);
					#endif
					
					return iterator;
				}
			}
			
			iterator = iterator->next;
		}
	} 
	#ifdef DEBUG_ON
		printf("[getUnmarkedLocation] ENDED\n");
	#endif
	
	return NULL;
}

void printLocation(struct location* loc){
	
	struct condition* invariant=NULL;
	struct condition* derivative=NULL;
	struct transition* transitions=NULL;
	struct condition* when=NULL;
	struct condition* reset=NULL;
	struct transitionWrapper* incoming = NULL;
	printf("\nloc %s:\t\t",loc->name);
	printf("while ");
	invariant=loc->invariant;
	while(invariant!=NULL){
		if(invariant->op == -1){
			printf("true");
		} else {
			printf("%s %s %s",invariant->LHS,phOperatorMap(invariant->op),invariant->RHS);
		}
		
		if(invariant->next != NULL){
			printf(" & ");
		} else {
			printf("\n\t\t\t");
		}
		invariant=invariant->next;
	}
	printf("\twait {");
	derivative=loc->derivative;
	while(derivative!=NULL){
		printf("%s %s %s",derivative->LHS,phOperatorMap(derivative->op),derivative->RHS);
		//printf("%s == %s",derivative->LHS,derivative->RHS);
		if(derivative->next != NULL){
			printf(" & ");
		} else {
			printf(" };\n\t\t\t");
		}
		derivative=derivative->next;
	}
		
		
	//OUTGOING TRANSITIONS
	transitions = loc->transitions;
	//printf("transitions = %p\n",loc->transitions);
	while(transitions!=NULL){
		printTransition(transitions);
		//printf("\n");
		transitions=transitions->next;
	}
			
	//INCOMING TRANSITIONS
	incoming = loc->incoming;
	//printf("********************** INCOMING TRANSITIONS *********************");
	while(incoming!=NULL){
		transitions = incoming->trans;
		when = transitions->when;
		reset= transitions->reset;
		printf("\n\t\tFROM : %s",incoming->loc->name);
		printf("\n\t\t\twhen ");
		while(when!=NULL){
			printf("%s %s %s",when->LHS,phOperatorMap(when->op),when->RHS);
			if(when->next != NULL){
				printf(" & ");
			} else {
				printf("\n\t\t\t");
			}
			when=when->next;
		}
		printf("sync %s do { ",transitions->sync);
			
		while(reset!=NULL){
			printf("%s %s %s",reset->LHS,"==",reset->RHS);
			if(reset->next != NULL){
				printf(" & ");
			} else {
				printf(" }\n\t\t\t");
			}
			reset=reset->next;
		}
		printf("goto %s;\n",transitions->gotoLoc);
		printf("\n");
		incoming=incoming->next;
	}
	printf("loc [%p] tra [%p] \n",loc,loc->transitions);
}

void printLocationList(struct location* l){
	while(l!=NULL){
		printLocation(l);
		l=l->next;
	}
}

//-----------------------------------------------------------------------------


int isTruePORV(struct location* loc, struct PORV* porv){
	#ifdef DEBUG_ON
		printf("[isTruePORV] STARTED\n");
	#endif
	
	if(loc!=NULL && porv!=NULL){
		struct PORV* iterator = loc->labels;
		while(iterator!=NULL){
			if(iterator->id == porv->id){
				#ifdef DEBUG_ON
					printf("[isTruePORV] ENDED\n");
				#endif
				return 1;
			}
			iterator = iterator->next;
		}
	}
	
	#ifdef DEBUG_ON
		printf("[isTruePORV] ENDED\n");
	#endif
	return 0;
}

int isTrueConjunct(struct location* loc, struct PORV* conjunct){
	#ifdef DEBUG_ON
		printf("[isTrueConjunct] STARTED\n");
	#endif
	
	if(loc!=NULL && conjunct!=NULL){
		struct PORV* porv = conjunct;
		struct PORV* iterator;
		int flag =1;
		
		#ifdef DEBUG_ON
			iterator = loc->labels;
			while(iterator!=NULL){
				printf("%d\t",iterator->id);
				iterator = iterator->next;
			}
		
			printf("To compare with: ");
			iterator = porv;
			while(iterator!=NULL){
				printf("%d\t",iterator->id);
				iterator = iterator->next;
			}
			printf("\n\n");
		#endif
		while(porv!=NULL && flag == 1){
			if(porv->id>0){
				iterator = loc->labels;
				flag = 0;
				while(iterator!=NULL){
					if(iterator->id == porv->id){
						#ifdef DEBUG_ON
							printf("[isTrueConjunct] ENDED\n");
						#endif
						flag = 1;
						break;
					}
					iterator = iterator->next;
				}
			}
			porv = porv->next;
		}
		return flag;
	}
	
	#ifdef DEBUG_ON
		printf("[isTrueConjunct	] ENDED\n");
	#endif
	return 0;
}

int isTruePORVExpr(struct location* loc, struct PORVExpression* PORVExpr){
	#ifdef DEBUG_ON
		printf("[isTruePORVExpr] STARTED\n");
	#endif
	
	if(loc!=NULL && PORVExpr!=NULL){
		struct PORVExpression* conjunctWrapper = PORVExpr;
		
		while(conjunctWrapper!=NULL){
			if(isTrueConjunct(loc,conjunctWrapper->conjunct) == 1)
				return 1;
			
			conjunctWrapper = conjunctWrapper->next;
		}
		
	}
	
	#ifdef DEBUG_ON
		printf("[isTruePORVExpr	] ENDED\n");
	#endif
	return 0;
}

int isTrueExpr(struct location* loc, struct expression* expr){
	#ifdef DEBUG_ON
		printf("[isTrueExpr] STARTED\n");
	#endif
	int eventFlag = 0; int exprFlag = 0;
	if(loc!=NULL && expr!=NULL){
		if(expr->event!=NULL){
			eventFlag = isTruePORV(loc,expr->event->porv);
			//printf("[%s] EVENTFLAG = %d\n",loc->name,eventFlag);
		} else eventFlag = 1;
		
		#ifdef DEBUG_ON
			printf("[%s] EVENTFLAG = %d\n",loc->name,eventFlag);
		#endif
		
		if(expr->dnf!=NULL){
			exprFlag = isTruePORVExpr(loc,expr->dnf);
			//printf("[%s] exprFlag = %d\n",loc->name,exprFlag);
		}
		else exprFlag = 1;
		
		#ifdef DEBUG_ON
			printf("[%s] exprFlag = %d\n",loc->name,exprFlag);
		#endif
			
		if(eventFlag==1 && exprFlag==1){

			#ifdef DEBUG_ON
				printf("[isTrueExpr] ENDED\n");
			#endif
			
			return 1;
		}	
	}
	
	#ifdef DEBUG_ON
		printf("[isTrueExpr] ENDED\n");
	#endif
	
	if(expr->dnf == NULL && expr->event==NULL){
		return 1;
	}
	
	return 0;
}

/*-----------------------AUTOMATON-----------------------------*/

struct automaton* createAutomaton(struct automaton* root, char* name, struct identifier* contr_vars, struct identifier* synclabs, struct location* locations){
	#ifdef DEBUG_ON 
		printf("[addAutomaton] STARTED\n");
	#endif
	
	struct automaton* ha = (struct automaton*)malloc(sizeof(struct automaton));
	struct automaton* temp = root;
	
	strcpy(ha->name,name);
	ha->contr_vars = contr_vars;
	ha->synclabs = synclabs;
	ha->locations = locations;
	ha->var_inputs = NULL;
	processIncomingTransitions(locations);
	#ifdef DEBUG_ON 
		printf("[addAutomaton] CRETED NODE\n");
	#endif
	fflush(stdout);
	fflush(stderr);
	
	root = ha;
	#ifdef DEBUG_ON 
		printf("[addAutomaton] ROOT CHANGED\n");
	
		printf("[addAutomaton] ADDED NODE\n");
	#endif
	
	return root;
}

/*-----------------------PHAVER-----------------------------*/

struct phaver* createPhaverStruct(struct phaver* root, struct condition* params, struct automaton* ha, struct initial* init){
	#ifdef DEBUG_ON 
		printf("[addPhaver] STARTED\n");
	#endif
	struct phaver* pha = (struct phaver*)malloc(sizeof(struct phaver));
	root = pha;
	pha->params = params;
	pha->ha = ha;
	pha->init = init;
	pha->temporal = 0;
	
	#ifdef DEBUG_ON 
		printf("[addPhaver] CRETED NODE\n");
		printf("[addPhaver] ROOT CHANGED\n");
		printf("[addPhaver] ADDED NODE\n");
	#endif
	return pha;
}

/*-----------------------MISCELLANEOUS-----------------------------*/

int charInList(char *c, char *list, int count){
	int i=0;
	for(i=0;i<count;i++){
		if(*c==list[i])
			return 1;
	}
	return 0;
	
}

void zeroDerivative(char *eqn, char *var){//Equation, varname to look for
	char list[14]={'{','}','(',')','[',']','+','-','*','/',' ','%','&','='};
	
	int eqnLen = strlen(eqn);
	int varLen = strlen(var);
	
	if(var!=NULL && eqn!=NULL){
		int i,j,k;
		for(i=0;i<eqnLen;i++){
			if(eqn[i]==var[0]){
				if((i!=0 && (charInList(&eqn[i-1],list,14)==1))||i==0){
					for(j=0;j<varLen && eqn[i+j]==var[j];j++);
					if(j==varLen){
						if(eqnLen==(i+j)||(eqnLen>(i+j)&&charInList(&eqn[i+j],list,14))) {
							//REPLACE STRING
							k=0;
							for(k=eqnLen;k>(i+varLen-1);k--){
								eqn[k+4]=eqn[k];
							}
							eqn[i]='(';
							eqn[i+1]='0';
							eqn[i+2]='*';
							for(k=0;k<varLen;k++){
								eqn[i+3+k]=var[k];
							}
							eqn[i+varLen+3]=')';
							eqnLen=strlen(eqn);
							i=i+varLen+4;
						}
					}
				}
			}
		}
	}
}

/*-----------------------Event-------- ---------------------*/

struct eventType* createEvent(int type, struct PORV* porv){
	#ifdef DEBUG_ON 
		printf("[createEvent] STARTED\n");
	#endif
	struct eventType* event = (struct eventType*)malloc(sizeof(struct eventType));
	
	event->type = type;
	event->porv = porv;
	#ifdef DEBUG_ON 
		printf("[createEvent] CRETED NODE\n");
	#endif
		
	return event;
}


/*-----------------------PORV-------- ---------------------*/

struct PORV* createPORV(struct condition* cond,int id){
	#ifdef DEBUG_ON 
		printf("[createPORV] STARTED\n");
	#endif
	struct PORV* porv = (struct PORV*)malloc(sizeof(struct PORV));
	
	porv->porv = cond;
	porv->id = id;
	porv->next = NULL;
	#ifdef DEBUG_ON 
		printf("[createPORV] CRETED NODE\n");
	#endif
	
	return porv;
}

struct PORV* addPORVToList(struct PORV* root, struct PORV* porv){
	#ifdef DEBUG_ON 
		printf("[addPORVToList] STARTED\n");
	#endif
	
	struct PORV* temp = root;
	
	if(root!=NULL){
		#ifdef DEBUG_ON 
			printf("[addPORVToList] PORV LIST NOT EMPTY\n");
		#endif
		while(temp->next!=NULL){
			temp=temp->next;
		}
		#ifdef DEBUG_ON 
			printf("[addPORVToList] ADDING TO PORV LIST\n");
		#endif
		temp->next = porv;
	} else {
		#ifdef DEBUG_ON 
			printf("[addPORVToList] PORV LIST EMPTY\n");
			printf("[addPORVToList] ADDING TO PORV LIST\n");
		#endif
		root = porv;
		#ifdef DEBUG_ON 
			printf("[addPORVToList] ROOT CHANGED\n");
		#endif
		
	}
	#ifdef DEBUG_ON 
		printf("[addPORVToList] ADDED PORV\n");
	#endif
	return root;
}

struct PORV* duplicatePORVList(struct PORV* root){
	#ifdef DEBUG_ON 
		printf("[duplicatePORVList] STARTED\n");
	#endif
	
	struct PORV* temp = root;
	struct PORV* newRoot = NULL;
	#ifdef DEBUG_ON 
		printf("[root = %p] %p \n",root,root->next);
	#endif
	
	while(temp!=NULL){
		struct PORV* newPORV = (struct PORV*)malloc(sizeof(struct PORV));
		newPORV->id = temp->id;
		newPORV->next = NULL;
		newPORV->porv = duplicateConditionList(temp->porv);
		
		newRoot = addPORVToList (newRoot, newPORV);
		#ifdef DEBUG_ON 
			printf("[duplicatePORVList] DUPLICATING NEXT PORV [%p]\n",temp->next);
			printf("[root = %p]\n",root);
		//if(temp == temp->next) temp->next=NULL;//exit(0);
		#endif
		
		temp = temp->next;
	}
	#ifdef DEBUG_ON 
		printf("[duplicatePORVList] COMPLETED\n");
	#endif
	
	return newRoot;
}
/*-----------------------PORVExpression--------------------*/
struct PORVExpression* createPORVExpression(struct PORV* conjunct){
	#ifdef DEBUG_ON 
	printf("[createPORVExpression] STARTED\n");
	#endif
	struct PORVExpression* porvExpr = (struct PORVExpression*)malloc(sizeof(struct PORVExpression));
	
	porvExpr->conjunct = conjunct;
	porvExpr->next = NULL;
	#ifdef DEBUG_ON 
	printf("[createPORVExpression] CRETED NODE\n");
	#endif
	
	return porvExpr;
}

struct PORVExpression* addPORVExpressionToEOfList(struct PORVExpression* root, struct PORVExpression* porvExpr){
	#ifdef DEBUG_ON 
	printf("[addPORVExpressionToList] STARTED\n");
	#endif
	
	struct PORVExpression* temp = root;
	
	if(root!=NULL){
		#ifdef DEBUG_ON 
		printf("[addPORVExpressionToList] PORV LIST NOT EMPTY\n");
		#endif
		while(temp->next!=NULL){
			temp=temp->next;
		}
		#ifdef DEBUG_ON 
		printf("[addPORVExpressionToList] ADDING TO PORV LIST\n");
		#endif
		temp->next = porvExpr;
	} else {
		#ifdef DEBUG_ON 
		printf("[addPORVExpressionToList] PORV LIST EMPTY\n");
		printf("[addPORVExpressionToList] ADDING TO PORV LIST\n");
		#endif
		root = porvExpr;
		#ifdef DEBUG_ON 
		printf("[addPORVExpressionToList] ROOT CHANGED\n");
		#endif
		
	}
	#ifdef DEBUG_ON 
	printf("[addPORVExpressionToList] ADDED PORV\n");
	#endif
	return root;
}

/*-----------------------Expression--------------------*/
struct expression* createExpression(struct PORVExpression* porvExpr, struct eventType* event){
	#ifdef DEBUG_ON 
	printf("[createExpression] STARTED\n");
	#endif
	struct expression* expr = (struct expression*)malloc(sizeof(struct expression));
	
	expr->dnf = porvExpr;
	expr->event = event;
	#ifdef DEBUG_ON 
	printf("[createExpression] CRETED NODE\n");
	#endif
	
	return expr;
}

/*-------------------SequenceExpression----------------*/
/*
 s *truct sequenceExpr{	
	 struct expression* expr;	//Sub-sequence Expression
	 struct timeDelay* delay;	//Delay associated with expr match
	 struct condition* assignments;	//List of Assignments when expr matches within delay
	 struct sequenceExpr* next;	//Next sub-expression
 };
 */

struct sequenceExpr* createSequenceExpr(struct expression* expr, struct timeDelay* delay, struct condition* assignments){
	#ifdef DEBUG_ON 
	printf("[createSequenceExpr] STARTED\n");
	#endif
	struct sequenceExpr* seqExpr = (struct sequenceExpr*)malloc(sizeof(struct sequenceExpr));
	
	seqExpr->expr = expr;
	seqExpr->delay = delay;
	seqExpr->assignments = assignments;
	seqExpr->next = NULL;
	#ifdef DEBUG_ON 
	printf("[createSequenceExpr] CRETED NODE\n");
	#endif
	
	return seqExpr;
}


struct sequenceExpr* addSequenceExprToEOfList(struct sequenceExpr* root, struct sequenceExpr* seqExpr){
	#ifdef DEBUG_ON 
	printf("[addSequenceExprToEOfList] STARTED\n");
	
	printf("seqExpr->delay = %p\n",seqExpr->delay);
	
	if(seqExpr->delay!=NULL){
		printf("LOWER = %f, UPPER = %f\n",seqExpr->delay->lower,seqExpr->delay->upper);
	}
	#endif
	struct sequenceExpr* temp = root;
	
	if(root!=NULL){
		#ifdef DEBUG_ON 
		printf("[addSequenceExprToEOfList] PORV LIST NOT EMPTY\n");
		#endif
		while(temp->next!=NULL){
			temp=temp->next;
		}
		#ifdef DEBUG_ON 
		printf("[addSequenceExprToEOfList] ADDING TO PORV LIST\n");
		#endif
		temp->next = seqExpr;
	} else {
		#ifdef DEBUG_ON 
		printf("[addSequenceExprToEOfList] PORV LIST EMPTY\n");
		printf("[addSequenceExprToEOfList] ADDING TO PORV LIST\n");
		#endif
		root = seqExpr;
		#ifdef DEBUG_ON 
		printf("[addSequenceExprToEOfList] ROOT CHANGED\n");
		#endif
		
	}
	#ifdef DEBUG_ON 
	printf("[addSequenceExprToEOfList] ADDED PORV\n");
	#endif
	return root;
}


/*-------------------TimeDelay----------------*/
// struct timeDelay{
// 	float lower;			//Delay Lower Bound
// 	float upper;			//Delay Upper Bound
// 	int type;			//Eventually (1) or Finite Bounds (0) or Fixed(2)
// };	

struct timeDelay* createTimeDelay(double lower, double upper, int type){
	#ifdef DEBUG_ON 
	printf("[createTimeDelay] STARTED\n");
	#endif
	struct timeDelay* delay = (struct timeDelay*)malloc(sizeof(struct timeDelay));
	
	delay->lower = (float)lower;
	delay->upper = (float)upper;
	delay->type = type;
	#ifdef DEBUG_ON 
	printf("[createTimeDelay] CRETED NODE [%f %f %d]\n",delay->lower,delay->upper,delay->type);
	#endif
	
	return delay;
}


/*-------------------FeatureDefinition----------------*/
/*
 s *truct featureDef{
	 struct identifier* localVars;	//List of Feature Local Variables
	 struct sequenceExpr* seq;	//Sequence Expression - Behaviour to match
	 struct condition* featureAssign;//Feature Computation assignments
 };
 
 struct feature{
	 char name[MAX_STR_LENGTH];			//Feature Name
	 struct identifier* params;	//Feature Parameters
	 struct featureDef* def;		//Feature Definition (Behaviour and Feature Computation)
 };*/

struct featureDef* createFeatureDef(struct identifier* localVars, struct sequenceExpr* seq, struct condition* featureAssign){
	#ifdef DEBUG_ON 
	printf("[createFeatureDef] STARTED\n");
	#endif
	struct featureDef* featureStmt = (struct featureDef*)malloc(sizeof(struct featureDef));
	
	featureStmt->localVars = localVars;
	featureStmt->seq = seq;
	featureStmt->featureAssign = featureAssign;
	#ifdef DEBUG_ON 
	printf("[createFeatureDef] CRETED NODE\n");
	#endif
	
	return featureStmt;
}

/*-------------------Feature----------------*/
/*
 * 
 * struct feature{
 * char name[MAX_STR_LENGTH];			//Feature Name
 * struct identifier* params;	//Feature Parameters
 * struct featureDef* def;		//Feature Definition (Behaviour and Feature Computation)
 };
 */

struct feature* createFeature(char *name, struct identifier* params, struct featureDef* def){
	#ifdef DEBUG_ON 
	printf("[createFeature] STARTED\n");
	#endif
	struct feature* featureStmt = (struct feature*)malloc(sizeof(struct feature));
	
	strcpy(featureStmt->name,name);
	featureStmt->params = params;
	featureStmt->def = def;
	#ifdef DEBUG_ON 
	printf("[createFeature] CRETED NODE\n");
	#endif
	
	return featureStmt;
}

/*--------------------------- Feature Support Methods ------------------------ */

void printPORVDetails(struct feature* featureStmt){
	struct sequenceExpr* seq = featureStmt->def->seq;
	printf("----- ID ----- | ----- PORV -----\n               |                 \n");
	while(seq!=NULL){
		if(seq->expr->event!=NULL){
			if(seq->expr->event->porv!=NULL){
				printf("      %d       | %s %s %s\n",seq->expr->event->porv->id,seq->expr->event->porv->porv->LHS,featureOperatorMap(seq->expr->event->porv->porv->op),seq->expr->event->porv->porv->RHS);
			}
		}
		struct PORVExpression* expr = seq->expr->dnf;
		while(expr!=NULL){
			struct PORV* conjunct = expr->conjunct;
			while(conjunct!=NULL){
				printf("      %d       | %s %s %s\n",conjunct->id,conjunct->porv->LHS,featureOperatorMap(conjunct->porv->op),conjunct->porv->RHS);
				conjunct=conjunct->next;
			}
			expr = expr->next;
		}
		seq = seq->next;
	}
	
}

char* featureOperatorMap(int op){	
	char *p=(char *)malloc(sizeof(char)*3);
	switch(op){
		case 0: sprintf(p,"==");break;
		case 1: sprintf(p,"<=");break;
		case 2: sprintf(p,"=");break;
		case 3: sprintf(p,">=");break;
		case 4: sprintf(p,"<");break;
		case 5: sprintf(p,">");break;
		default:sprintf(p,"==");break;
		
	}
	//printf("%s",p);
	return p;
}

void printFeatureCondition(struct condition* cond){
	if(cond!=NULL){
		printf(" %s %s %s ",cond->LHS,featureOperatorMap(cond->op),cond->RHS);	
	}
	/*if(cond->next!=NULL){
		printf("CAUGHT IT\n");exit(0);
	}*/
}

void printAssignmentList(struct condition* assignments){
	if(assignments!=NULL){
		while(assignments->next!=NULL){
			printFeatureCondition(assignments);
			printf(", ");
			assignments = assignments->next;
		}
		printFeatureCondition(assignments);
	}
}


void printPORV(struct PORV* porv){
	if(porv!=NULL){
		printf("%d ",porv->id);
		//printFeatureCondition(porv->porv);
		//printf(" %s %s %s ",porv->porv->LHS,featureOperatorMap(porv->porv->op),porv->porv->RHS);	
	}
}


void printPORVConjunct(struct PORV* conjunct){
	if(conjunct!=NULL){
		while(conjunct->next!=NULL){
			printPORV(conjunct);
			printf("&&");
			conjunct = conjunct->next;
		}
		printPORV(conjunct);
	}
}

void printEvent(struct eventType* event){
	if(event!=NULL){
		printf(" @");
		switch(event->type){
			case 1: printf("+");break;
			case 2: printf("-");break;
			default:break;
		}
		printf("(");
		printPORV(event->porv);
		printf(") ");
	}
}

void printPORVExpression(struct PORVExpression* porvExpr){
	if(porvExpr!=NULL){
		while(porvExpr->next!=NULL){
			printPORVConjunct(porvExpr->conjunct);
			printf("||");
			porvExpr = porvExpr->next;
		}
		printPORVConjunct(porvExpr->conjunct);
	}	
}

void printExpression(struct expression* expr){
	if(expr!=NULL){
		if(expr->dnf!=NULL){
			printf("(");
			printPORVExpression(expr->dnf);
			printf(")");
			if(expr->event!=NULL){
				printf("&&");
			}
		}
		printEvent(expr->event);
	}
}

void printTimeDelay(struct timeDelay* delay){
	#ifdef DEBUG_ON
		printf("[printTimeDelay] START\n");//delay=NULL;printf("delay = [%s]",delay);
	#endif
	//printf("delay = [%f:%f]",delay->lower,delay->upper);
	if(delay!=NULL){
		printf(" ##");//printf("%d",delay->type);printf("HELLO\n");
		switch(delay->type){
			case 0: printf("[%f:%f] ",delay->lower, delay->upper);
			break;
			case 1: printf("[%f:$] ",delay->lower);
			break;
			case 2: printf("%f ",delay->lower);
			break;
			default:printf("\n--------------UNKNOWN DELAY TYPE-------------\n");
			break;
		}
	}
	
	#ifdef DEBUG_ON
	printf("[printTimeDelay] END\n");
	#endif
}

void printSequenceExpr(struct sequenceExpr* seq){
	printf("\t\t");
	if(seq!=NULL){
		while(seq!=NULL){
			//Print Temporal Seperation
			printTimeDelay(seq->delay);
			
			//Print Sub-sequence Expression
			printExpression(seq->expr);
			
			if(seq->assignments!=NULL){
				printf(", ");
				printAssignmentList(seq->assignments);
			}
			
			seq = seq->next;
		}
	} else {
		printf("\n--------------NO SEQUENCE EXPRESSION-------------\n");
	}
}

void printFeatureDefinition(struct featureDef* def){
	printf("\tbegin\n");
	
	//Print Local Variables
	if(def->localVars!=NULL){
		printf("\t\tvar ");
		struct identifier* var = def->localVars;
		while(var->next!=NULL){
			printf("%s , ",var->name);
			var = var->next;
		}
		printf("%s ;\n",var->name);
	}
	
	//Print Sequence Expression
	if(def->seq!=NULL){
		printSequenceExpr(def->seq);
		
	} else {
		printf("\n--------------NO SEQUENCE EXPRESSION-------------\n");
	}
	
	printf(" |-> ");
	
	//Printf Feature Computation
	printAssignmentList(def->featureAssign);
	
	printf(";\n");
	
	printf("\tend\n");
}

void printFeature(struct feature* featureStmt){
	printf("\n\n------------------------------FEATURE--------------------------------\n\n");
	if(featureStmt != NULL){
		if(featureStmt->name!=NULL){
			printf("feature %s ",featureStmt->name);
			
			// Print Parameters
			if(featureStmt->params!=NULL){
				printf("( ");
				struct identifier* param=featureStmt->params;
				while(param->next!=NULL){
					printf("%s , ",param->name);
					param = param->next;
				}
				printf("%s ) ;\n",param->name);
			}
			
			//Print Feature Body
			if(featureStmt->def!=NULL){
				printFeatureDefinition(featureStmt->def);
				
			} else {
				printf("\n--------------NO FEATURE BODY-------------\n");
			}
			
			
		} else {
			printf("Feature Name is NULL\n");
		}
	}
	printf("\n\n---------------------------------------------------------------------\n\n");
}

char* phOperatorMap(int op){	
	char *p=(char *)malloc(sizeof(char)*3);
	switch(op){
		case 0: sprintf(p,"==");break;
		case 1: sprintf(p,"<=");break;
		case 2: sprintf(p,":=");break;
		case 3: sprintf(p,">=");break;
		case 4: sprintf(p,"<");break;
		case 5: sprintf(p,">");break;
		default:sprintf(p,"==");break;
		
	}
	//printf("%s",p);
	return p;
}




void displayAutomaton(struct phaver* pha/*, struct feature* sysFeature*/){
	struct condition* params=pha->params;
	struct automaton* ha=pha->ha;
	struct identifier* contr_vars=ha->contr_vars;
	struct identifier* synclabs=ha->synclabs;
	struct identifier* var_inputs=ha->var_inputs;
	struct location* loc=ha->locations;
	struct condition* invariant=NULL;
	struct condition* derivative=NULL;
	struct transition* transitions=NULL;
	struct condition* when=NULL;
	struct condition* reset=NULL;
	struct transitionWrapper* incoming = NULL;
	struct initial* init = pha->init;
	struct identifier* init_locs=pha->init->init_locs;
	struct condition* init_conds=pha->init->init_conds;
	
	printf("//--------------PARAMETERS------------------\n");
	while(params!=NULL){
		printf("%s %s %s;\n",params->LHS,":=",params->RHS);
		params=params->next;
	}
	
	printf("//--------------AUTOMATON-------------------\n");
	printf("automaton %s\n",ha->name);
	printf("contr_var: ");
	while(contr_vars!=NULL){
		if(contr_vars->next == NULL){
			printf("%s;\n",contr_vars->name);
		} else printf("%s, ",contr_vars->name);
		contr_vars=contr_vars->next;
	}
	printf("synclabs: ");
	while(synclabs!=NULL){
		if(synclabs->next == NULL){
			printf("%s;\n",synclabs->name);
		} else printf("%s,",synclabs->name);
		synclabs=synclabs->next;
	}
	if(var_inputs!=NULL) printf("var_inputs: ");
	while(var_inputs!=NULL){
		if(var_inputs->next == NULL){
			printf("%s;\n",var_inputs->name);
		} else printf("%s, ",var_inputs->name);
		var_inputs=var_inputs->next;
	}
	printf("//--------------LOCATIONS-------------------\n");
	while(loc!=NULL){
		//printf("//-----------------THIS LOCATION %s VAR_INPUTS--------------\n",loc->requires==0?"DOES NOT REQUIRE":"REQUIRES");
		printf("\nloc %s:\t\t",loc->name);
		printf("while ");
		invariant=loc->invariant;
		while(invariant!=NULL){
			if(invariant->op == -1){
				printf("true");
			} else {
				printf("%s %s %s",invariant->LHS,phOperatorMap(invariant->op),invariant->RHS);
			}
			//printf("%s %s %s",invariant->LHS,phOperatorMap(invariant->op),invariant->RHS);
			if(invariant->next != NULL){
				printf(" & ");
			} else {
				printf("\n\t\t\t");
			}
			invariant=invariant->next;
		}
		printf("\twait {");
			derivative=loc->derivative;
			while(derivative!=NULL){
				printf("%s %s %s",derivative->LHS,phOperatorMap(derivative->op),derivative->RHS);
				//printf("%s == %s",derivative->LHS,derivative->RHS);
				if(derivative->next != NULL){
					printf(" & ");
				} else {
					printf(" };\n\t\t\t");
				}
				derivative=derivative->next;
			}
			
			
			//OUTGOING TRANSITIONS
			transitions = loc->transitions;
			while(transitions!=NULL){
				when = transitions->when;
				reset= transitions->reset;
				
				printf("\n\t\t\twhen ");
				
				while(when!=NULL){
					if(strcasecmp(when->LHS,"true")==0)
						printf("true");
					else 
						printf("%s %s %s",when->LHS,phOperatorMap(when->op),when->RHS);
					
					if(when->next != NULL){
						printf(" & ");
					} else {
						printf("\n\t\t\t");
					}
					when=when->next;
				}
				printf("sync %s do { ",transitions->sync);
				//int flag = 0; char timeLabel[5]; sprintf(timeLabel,"time");	
				while(reset!=NULL){
					/*
					if(flag == 0 && strcmp(reset->RHS,timeLabel)==0)
						flag = 1;
					if (flag==1 && strcmp(reset->RHS,timeLabel)==0) 
						printf("Houston we have a problem in the list\n");
					*/
					printf("%s %s %s",reset->LHS,"==",reset->RHS);
					if(reset->next != NULL){
						printf(" & ");
					} else {
						printf(" }\n\t\t\t");
					}
					reset=reset->next;
				}
				printf("goto %s;\n",transitions->gotoLoc);
				//printf("\n");
				transitions=transitions->next;
			}
			/*
			//INCOMING TRANSITIONS
			incoming = loc->incoming;
			//printf("********************** INCOMING TRANSITIONS *********************");
			while(incoming!=NULL){
				transitions = incoming->trans;
				when = transitions->when;
				reset= transitions->reset;
				printf("\n\t\tFROM : %s",incoming->loc->name);
				printf("\n\t\t\twhen ");
				while(when!=NULL){
					printf("%s %s %s",when->LHS,phOperatorMap(when->op),when->RHS);
					if(when->next != NULL){
						printf(" & ");
					} else {
						printf("\n\t\t\t");
					}
					when=when->next;
				}
				printf("sync %s do { ",transitions->sync);
					
					while(reset!=NULL){
						printf("%s %s %s",reset->LHS,"==",reset->RHS);
						if(reset->next != NULL){
							printf(" & ");
						} else {
							printf(" }\n\t\t\t");
						}
						reset=reset->next;
					}
					printf("goto %s;\n",transitions->gotoLoc);
					printf("\n");
					incoming=incoming->next;
			}*/
			//printf("*****************************************************************\n");
			//printf("\tPORV INVARIANTS"); printPORVConjunct(loc->labels);printf("\n");
			/*
			if(sysFeature!=NULL){
				char* T = "TRUE";
				char* F = "FALSE";
				
				struct sequenceExpr* seq = sysFeature->def->seq;
				printf("----- ID ----- | ----- PORV -----\n               |                 \n");
				
				while(seq!=NULL){
					if(seq->expr->event!=NULL){
						if(seq->expr->event->porv!=NULL){
							printf("      %d       | %s %s %s | %s\n",seq->expr->event->porv->id,seq->expr->event->porv->porv->LHS,featureOperatorMap(seq->expr->event->porv->porv->op),seq->expr->event->porv->porv->RHS,isTruePORV(loc,seq->expr->event->porv)?T:F);
						}
					}
					struct PORVExpression* expr = seq->expr->dnf;
					while(expr!=NULL){
						struct PORV* conjunct = expr->conjunct;
						while(conjunct!=NULL){
							printf("      %d       | %s %s %s | %s\n",conjunct->id,conjunct->porv->LHS,featureOperatorMap(conjunct->porv->op),conjunct->porv->RHS,isTruePORV(loc,conjunct)?T:F);
							conjunct=conjunct->next;
						}
						expr = expr->next;
					}
					seq = seq->next;
				}
			}*/
			/*
			if(sysFeature!=NULL){
				char* T = "TRUE";
				char* F = "FALSE";
				
				struct sequenceExpr* seq = sysFeature->def->seq;
				//printf("----- ID ----- | ----- PORV -----\n               |                 \n");
				
				while(seq!=NULL){
					int flag = 0;
					if(seq->expr->event!=NULL){
						if(seq->expr->event->porv!=NULL){
							flag = isTruePORV(loc,seq->expr->event->porv) ? 1 : 0 ;
							printf("\t\t");printEvent(seq->expr->event);
						}
					}
					struct PORVExpression* expr = seq->expr->dnf;
					while(expr!=NULL){
						printf("\n\t\t\t");printPORVConjunct(expr->conjunct);
						printf("%s\n",isTrueConjunct(loc,expr->conjunct) && flag == 1?T:F);
						expr = expr->next;
					}
					seq = seq->next;
				}
			}*/
			/*if(sysFeature!=NULL){
				char* T = "TRUE";
				char* F = "FALSE";
				
				struct sequenceExpr* seq = sysFeature->def->seq;
				//printf("----- ID ----- | ----- PORV -----\n               |                 \n");
				
				while(seq!=NULL){
					printf("\t\t\t");printExpression(seq->expr);
					printf("\n\t\t\t\t\t\t");
					printf("%s\n",isTrueExpr(loc,seq->expr)==1?T:F);					
					seq = seq->next;
				}
			}
			*/
			loc=loc->next;
			
	}
	//struct identifier* init_locs=pha->init_locs;
	//struct condition* init_conds=pha->init_conds;
	printf("\ninitially: ");
	while(init!=NULL){
		init_locs = init->init_locs;
		init_conds = init->init_conds;
		
		while(init_locs!=NULL){
			printf("%s",init_locs->name);
			if(init_locs->next != NULL){
				printf(" & ");
			} else {
				if(init_conds != NULL)
					printf(" & ");
			}
			init_locs=init_locs->next;
		}
		while(init_conds!=NULL){
			printf("%s %s %s",init_conds->LHS,phOperatorMap(init_conds->op),init_conds->RHS);
			if(init_conds->next != NULL){
				printf(" & ");
			} 
			init_conds=init_conds->next;
		}
		if(init->next!=NULL){
			printf(", ");
		} else printf(";\n");
		init = init->next;
	}
	
	printf("\nend\n");
}


void writeAutomaton(struct phaver* pha, FILE *out){
	struct condition* params=pha->params;
	struct automaton* ha=pha->ha;
	struct identifier* contr_vars=ha->contr_vars;
	struct identifier* synclabs=ha->synclabs;
	struct identifier* var_inputs=ha->var_inputs;
	struct location* loc=ha->locations;
	struct condition* invariant=NULL;
	struct condition* derivative=NULL;
	struct transition* transitions=NULL;
	struct condition* when=NULL;
	struct condition* reset=NULL;
	struct transitionWrapper* incoming = NULL;
	struct initial* init = pha->init;
	struct identifier* init_locs=pha->init->init_locs;
	struct condition* init_conds=pha->init->init_conds;
	
	fprintf(out,"//--------------PARAMETERS------------------\n");
	while(params!=NULL){
		fprintf(out,"%s %s %s;\n",params->LHS,":=",params->RHS);
		params=params->next;
	}
	
	fprintf(out,"//--------------AUTOMATON-------------------\n");
	fprintf(out,"automaton %s\n",ha->name);
	fprintf(out,"contr_var: "); //fprintf(out,"state_var: ");
	while(contr_vars!=NULL){
		if(contr_vars->next == NULL){
			fprintf(out,"%s;\n",contr_vars->name);
		} else fprintf(out,"%s, ",contr_vars->name);
		contr_vars=contr_vars->next;
	}
	fprintf(out,"synclabs: ");
	while(synclabs!=NULL){
		if(synclabs->next == NULL){
			fprintf(out,"%s;\n",synclabs->name);
		} else fprintf(out,"%s,",synclabs->name);
		synclabs=synclabs->next;
	}
	if(var_inputs!=NULL) fprintf(out,"var_inputs: ");
	while(var_inputs!=NULL){
		if(var_inputs->next == NULL){
			fprintf(out,"%s;\n",var_inputs->name);
		} else fprintf(out,"%s, ",var_inputs->name);
		var_inputs=var_inputs->next;
	}
	fprintf(out,"//--------------LOCATIONS-------------------\n");
	while(loc!=NULL){
		//fprintf(out,"//-----------------THIS LOCATION %s VAR_INPUTS--------------\n",loc->requires==0?"DOES NOT REQUIRE":"REQUIRES");
		fprintf(out,"\nloc %s:\t\t",loc->name);
		fprintf(out,"while ");
		invariant=loc->invariant;
		while(invariant!=NULL){
			if(invariant->op == -1){
				fprintf(out,"true");
			} else {
				fprintf(out,"%s %s %s",invariant->LHS,phOperatorMap(invariant->op),invariant->RHS);
			}
			
			if(invariant->next != NULL){
				fprintf(out," & ");
			} else {
				fprintf(out,"\n\t\t\t");
			}
			invariant=invariant->next;
		}
		fprintf(out,"\twait {");
		derivative=loc->derivative;
		while(derivative!=NULL){
			fprintf(out,"%s %s %s",derivative->LHS,phOperatorMap(derivative->op),derivative->RHS);
			//fprintf(out,"%s == %s",derivative->LHS,derivative->RHS);
			if(derivative->next != NULL){
				fprintf(out," & ");
			} else {
				fprintf(out," };\n\t\t\t");
			}
			derivative=derivative->next;
		}


		//OUTGOING TRANSITIONS
		transitions = loc->transitions;
		while(transitions!=NULL){
			when = transitions->when;
			reset= transitions->reset;
			
			fprintf(out,"\n\t\t\twhen ");
			
			while(when!=NULL){
				fprintf(out,"%s %s %s",when->LHS,phOperatorMap(when->op),when->RHS);
				
				if(when->next != NULL){
					fprintf(out," & ");
				} else {
					fprintf(out,"\n\t\t\t");
				}
				when=when->next;
			}
			fprintf(out,"sync %s do { ",transitions->sync);
				//int flag = 0; char timeLabel[5]; sprintf(timeLabel,"time");	
			while(reset!=NULL){
			/*
			if(flag == 0 && strcmp(reset->RHS,timeLabel)==0)
			flag = 1;
			if (flag==1 && strcmp(reset->RHS,timeLabel)==0) 
			printf("Houston we have a problem in the list\n");
			*/
				fprintf(out,"%s %s %s",reset->LHS,"==",reset->RHS);
				if(reset->next != NULL){
					fprintf(out," & ");
				} else {
					fprintf(out," }\n\t\t\t");
				}
				reset=reset->next;
			}
			fprintf(out,"goto %s;\n",transitions->gotoLoc);
			//printf("\n");
			transitions=transitions->next;
		}
		loc=loc->next;
	}
	//struct identifier* init_locs=pha->init_locs;
	//struct condition* init_conds=pha->init_conds;
	fprintf(out,"\ninitially: ");
	while(init!=NULL){
		init_locs = init->init_locs;
		init_conds = init->init_conds;
		
		while(init_locs!=NULL){
			fprintf(out,"%s",init_locs->name);
			if(init_locs->next != NULL){
				fprintf(out," & ");
			} else {
				if(init_conds != NULL)
					fprintf(out," & ");
			}
			init_locs=init_locs->next;
		}
		while(init_conds!=NULL){
			fprintf(out,"%s %s %s",init_conds->LHS,phOperatorMap(init_conds->op),init_conds->RHS);
			if(init_conds->next != NULL){
				fprintf(out," & ");
			} 
			init_conds=init_conds->next;
		}
		if(init->next!=NULL){
			fprintf(out,", ");
		} else fprintf(out,";\n");
		init = init->next;
	}
	
	fprintf(out,"\nend\n");
}


 int writeSpaceEx(struct phaver* HA, char* fileName){
 	int finalID = 0;
	std::map<char*, int> locNametoIDMap;
 	struct condition* params=HA->params;
 	struct condition* params2=HA->params;
 	struct condition* params3=HA->params;
 	struct automaton* ha=HA->ha;
 	struct identifier* contr_vars=ha->contr_vars;
 	struct identifier* contr_vars2=ha->contr_vars;
 	struct identifier* contr_vars3=ha->contr_vars;
 	struct identifier* synclabs=ha->synclabs;
 	struct identifier* synclabs2=ha->synclabs;
 	struct identifier* synclabs3=ha->synclabs;
 	struct identifier* var_inputs=ha->var_inputs;
 	struct location* loc = ha->locations;
 	struct location* loc2 = ha->locations;
 	struct condition* invariant=NULL;
 	struct condition* derivative=NULL;
 	struct transition* transitions=NULL;
 	struct condition* when=NULL;
 	struct condition* resets=NULL;
 	struct transitionWrapper* incoming = NULL;
 	struct initial* init = HA->init;
 	struct identifier* init_locs=HA->init->init_locs;
 	struct condition* init_conds=HA->init->init_conds;
 	struct condition* init_conds2=HA->init->init_conds;
 	struct condition* init_conds3;	
 	struct locationSpaceEx* locSp = (struct locationSpaceEx*)malloc(sizeof(struct locationSpaceEx));
 	struct transitionSpaceEx* transSp = (struct transitionSpaceEx*)malloc(sizeof(struct transitionSpaceEx));
 	struct transitionSpaceEx *transSpPtr, *transtemp;
 	struct locationSpaceEx *locSpPtr, *loctemp;
 	char targetName[MAX_STR_LENGTH];
 	char sourceName[MAX_STR_LENGTH];
 	FILE *fptr;
 	char st[MAX_STR_LENGTH],PHAVerFile[MAX_STR_LENGTH]; //filename[MAX_STR_LENGTH],
 	//strcpy(PHAVerFile, argv[1]);
 	//strncpy(st, PHAVerFile, strlen(PHAVerFile)-4);
 	//printf("St : %s\n", PHAVerFile);
 	//sprintf(filename, "spaceexModel.xml");
 	//sprintf(filename,"%s_%s.xml",argv[1],argv[2]);
 	
 	//printf("filename : %s\n",filename);
 	fptr = fopen(fileName, "w");
 
 	int i=0, l=0;
 	fprintf(fptr, "<?xml version=\"1.0\" encoding=\"iso-8859-1\"?>\n<sspaceex xmlns=\"http://www-verimag.imag.fr/xml-namespaces/sspaceex\" version=\"0.2\" math=\"SpaceEx\">\n\t");
 	//there will only be one component
 	fprintf(fptr, "<component id=\"%s_template\">\n", ha->name);
 
 	while(contr_vars!=NULL)
 	{
 		fprintf(fptr, "\t\t<param name=\"%s\" type=\"real\" dynamics=\"any\" local=\"false\" d1=\"1\" d2=\"1\" />\n",contr_vars->name);
 		#ifdef DEBUG_ON 
 			printf("\t\t<param name=\"%s\" type=\"real\" dynamics=\"any\" local=\"false\" d1=\"1\" d2=\"1\" />\n",contr_vars->name);
 		#endif
 		
 		contr_vars = contr_vars->next;
 	}
 	
 	while(params!=NULL)
 	{
 		fprintf(fptr, "\t\t<param name=\"%s\" type=\"real\" dynamics=\"const\" local=\"false\" d1=\"1\" d2=\"1\" />\n",params->LHS);
 		#ifdef DEBUG_ON 
 			printf("\t\t<param name=\"%s\" type=\"real\" dynamics=\"const\" local=\"false\" d1=\"1\" d2=\"1\" />\n",params->LHS);
 		#endif
 		params = params->next;
 	}
 	
 	while(synclabs!=NULL)
 	{
 		fprintf(fptr, "\t\t<param name=\"%s\" type=\"label\" local=\"false\" />", synclabs->name);
 		#ifdef DEBUG_ON 
 			printf("\t\t<param name=\"%s\" type=\"label\" local=\"false\" />", synclabs->name);
 		#endif
 		synclabs = synclabs->next;
 
 	}
 	//PHAVer locations to SpaceEx locations
 	#ifdef DEBUG_ON 
 		printf("\nhere\n");
 	#endif
 	fprintf(fptr, "\n");
 	locSp->id = 0;
 	transSp->sourceID = 0;
 	transSp->targetID = 0;
 	while(l<5)
 	{
 		locSp->invariants[l] = NULL;
 		locSp->flows[l] = NULL;
 		transSp->label[l] = NULL;
 		transSp->guard[l] = NULL;
 		transSp->assignments[l] = NULL;
 		l++;
 	}
 	locSp->next = NULL;
 	transSp->next = NULL;
 	while(loc!=NULL)
 	{
 
 		i++;
 		
 		while(locSp->next!=NULL)
 		{
 			locSp = locSp->next;
 		}
 		loctemp = (struct locationSpaceEx*)malloc(sizeof(struct locationSpaceEx));
 
 		loctemp->id = i;
 		strcpy(loctemp->name, loc->name);
 
 		fprintf(fptr, "\t\t<location id=\"%d\" name=\"%s\">\n", loctemp->id, loctemp->name);
 		
 		if(strcasecmp(loctemp->name,"final")==0){
			finalID = loctemp->id;
		}
		
 		#ifdef DEBUG_ON 
 		printf("\t\t<location id=\"%d\" name=\"%s\">\n", loctemp->id, loctemp->name);
 		#endif
 		
 		locNametoIDMap[loctemp->name] = loctemp->id;
 		int j=0;
 		invariant = loc->invariant;
 		while(invariant!=NULL)
 		{
 			loctemp->invariants[j] = invariant;
 			invariant = invariant->next;
 			j++;
 		}
 		int k=0;
 		fprintf(fptr, "\t\t\t<invariant>");
 		
 		#ifdef DEBUG_ON 
 		printf("\t\t\t<invariant>");
 		#endif
 		
 		while(loctemp->invariants!=NULL)
 		{
 			if(k>=j) break;
 			/*if(strcmp(SpaceExOpMap(loctemp->invariants[k]->op),"==")==0)
 			{
 				fprintf(fptr, "true");
 				printf("true");
 				loctemp->invariants[k]->op = -99;
 				
 			}*/
 			if(loctemp->invariants[k]->op==-1){
 				fprintf(fptr, "true");
 				
 				#ifdef DEBUG_ON 
 				printf("true");
 				#endif
 				
 				
 			} else {
 				fprintf(fptr, "%s%s%s", loctemp->invariants[k]->LHS, SpaceExOpMap(loctemp->invariants[k]->op), loctemp->invariants[k]->RHS);
 				
 				#ifdef DEBUG_ON 
 				printf("%s%s%s", loctemp->invariants[k]->LHS, SpaceExOpMap(loctemp->invariants[k]->op), loctemp->invariants[k]->RHS);
 				#endif
 				
 				
 			}
 			
 			if(loctemp->invariants[k]->next == NULL)
 			{
 				fprintf(fptr, "</invariant>\n");
 				#ifdef DEBUG_ON 
 				printf("</invariant>\n");
 				#endif
 			}
 			else 
 			{
 				fprintf(fptr, " &amp; ");
 				#ifdef DEBUG_ON 
 				printf(" &amp; ");
 				#endif
 			}
 			k++;
 		}
 
 		int l=0;
 
 		derivative = loc->derivative;
 		while(derivative!=NULL)
 		{
 			loctemp->flows[l] = derivative;
 			derivative = derivative->next;
 			l++;
 		}
 		k=0;
 		fprintf(fptr, "\t\t\t<flow>");
 		
 		#ifdef DEBUG_ON 
 		printf("\t\t\t<flow>");
 		#endif
 		
 		while(loctemp->flows!=NULL)
 		{
 			if(k>=l) break;
 			fprintf(fptr, "%s%s%s", loctemp->flows[k]->LHS, SpaceExOpMap(loctemp->flows[k]->op), loctemp->flows[k]->RHS);
 			
 			#ifdef DEBUG_ON 
 			printf("%s%s%s", loctemp->flows[k]->LHS, SpaceExOpMap(loctemp->flows[k]->op), loctemp->flows[k]->RHS);
 			#endif
 			
 			if(loctemp->flows[k]->next != NULL)
 			{
 				fprintf(fptr, " &amp; ");
 				
 				#ifdef DEBUG_ON 
 				printf(" &amp; ");
 				#endif
 			}
 			else 
 			{
 				fprintf(fptr, "</flow>\n");
 				
 				#ifdef DEBUG_ON 
 				printf("</flow>\n");
 				#endif
 			}
 			k++;
 
 		}
 	
 		loctemp->next = locSp->next;
 		locSp->next = loctemp;
 		fprintf(fptr, "\t\t</location>\n");
 		
 		#ifdef DEBUG_ON 
 		printf("\t\t</location>\n");
 		#endif
 		
 		fflush(fptr);
 		loc = loc->next;
 	} 
 	
 	#ifdef DEBUG_ON 
 	printf("\n\nPrinting Location Transition Map\n\n");
 	#endif
 	
 	while(loc2!=NULL)
 	{
 		int p=0,q=0,r=0,l,m;
 		transitions = loc2->transitions;
 
 		while(transitions!=NULL)
 		{
 			l=0;
 			m=0;
 			
 			#ifdef DEBUG_ON 
 			printf("Transition Not Null\n");
 			#endif
 			
 			transSpPtr = transSp;
 			while(transSpPtr->next!=NULL)
 			{
 				transSpPtr = transSpPtr->next;
 			}
 			
 			transtemp = (struct transitionSpaceEx*)malloc(sizeof(struct transitionSpaceEx));
 			when = transitions->when;
 			
 
 			while(when!=NULL)
 			{
 				transtemp->guard[p] = when;
 				when = when->next;
 				p++;
 				l=p;
 			}
 			p=0;
 			resets = transitions->reset;
 			while(resets!=NULL)
 			{
 				transtemp->assignments[q] = resets;
 				resets = resets->next;
 				q++;
 				m=q;
 			}
 			q=0;
 			strcpy(transtemp->label,transitions->sync);
 			std::map<char* ,int>::iterator it1 = locNametoIDMap.begin();
 			std::map<char* ,int>::iterator it2 = locNametoIDMap.begin();
 			while(it1 != locNametoIDMap.end())
 			{
 				if(strcmp(it1->first, loc2->name)==0)
 				{
 					transtemp->sourceID = it1->second;
 					break;
 				}
 				it1++;
 			}
 			while(it2 != locNametoIDMap.end())
 			{
 				if(strcmp(it2->first, transitions->gotoLoc) ==0)
 				{	
 					transtemp->targetID = it2->second;
 					break;
 				}
 				it2++;
 			}
 
 			
 			fprintf(fptr, "\t\t<transition source=\"%d\" target=\"%d\">\n", transtemp->sourceID,transtemp->targetID);
 			fprintf(fptr, "\t\t\t<label>%s</label>\n", transtemp->label);
 			fprintf(fptr, "\t\t\t<guard>");
 			
 			#ifdef DEBUG_ON 
 				printf("\t\t<transition source=\"%d\" target=\"%d\">\n", transtemp->sourceID,transtemp->targetID);
 				printf("\t\t\t<label>%s</label>\n", transtemp->label);
 				printf("\t\t\t<guard>");
 			#endif
 			
 			r=0;
 			while(transtemp->guard!=NULL)
 			{
 				if(r>=l) break;
 				if(strcasecmp(transtemp->guard[r]->LHS,"true")==0)
					fprintf(fptr, "true");
				else 
					fprintf(fptr, "%s%s%s", transtemp->guard[r]->LHS, SpaceExOpMap(transtemp->guard[r]->op), transtemp->guard[r]->RHS);
 				
 				#ifdef DEBUG_ON 
 				printf("%s%s%s", transtemp->guard[r]->LHS, SpaceExOpMap(transtemp->guard[r]->op), transtemp->guard[r]->RHS);
 				#endif
 				
 				if(transtemp->guard[r]->next != NULL)
 				{
 					fprintf(fptr, " &amp; ");
 					#ifdef DEBUG_ON 
 					printf(" &amp; ");
 					#endif
 				}
 				else 
 				{
 					fprintf(fptr, "</guard>\n");
 					
 					#ifdef DEBUG_ON 
 					printf("</guard>\n");
 					#endif
 				}
 				r++;
 			}
 			r=0;
 			fprintf(fptr, "\t\t\t<assignment>");
 			
 			#ifdef DEBUG_ON 
 			printf("\t\t\t<assignment>");
 			#endif
 			
 			while(transtemp->assignments!=NULL)
 			{
 				char oper[5];
 				if(r>=m) break;
 				if(strcmp(SpaceExOpMap(transtemp->assignments[r]->op), "=") == 0)
 					strcpy(oper, "==");
 				else
 					strcpy(oper, SpaceExOpMap(transtemp->assignments[r]->op));
 				fprintf(fptr, "%s%s%s", transtemp->assignments[r]->LHS, oper, transtemp->assignments[r]->RHS);
 				
 				#ifdef DEBUG_ON 
 				printf("%s%s%s", transtemp->assignments[r]->LHS, oper, transtemp->assignments[r]->RHS);
 				#endif
 				if(transtemp->assignments[r]->next != NULL)
 				{
 					fprintf(fptr, " &amp; ");
 					#ifdef DEBUG_ON 
 					printf(" &amp; ");
 					#endif
 				}
 				else 
 				{
 					fprintf(fptr, "</assignment>");
 					
 					#ifdef DEBUG_ON 
 					printf("</assignment>");
 					#endif
 					
 				}
 				r++;
 			}
 
 			transtemp->next = transSpPtr->next;
 			transSpPtr->next = transtemp;
 			fprintf(fptr, "\n\t\t</transition>\n");
 			#ifdef DEBUG_ON 
 			printf("\n\t\t</transition>\n");
 			#endif
 			transitions = transitions->next;
 		}
 
 		loc2 = loc2->next;
 	}
 
 	fprintf(fptr, "\t</component>\n");
 	fprintf(fptr, "\t<component id=\"%s\">\n", ha->name);
 	
 	#ifdef DEBUG_ON 
 	printf("\t</component>\n");
 	printf("\t<component id=\"%s\">\n", ha->name);
 	#endif
 	
 	while(contr_vars3!=NULL)
 	{
 		fprintf(fptr, "\t\t<param name=\"%s\" type=\"real\" local=\"false\" dynamics=\"any\" controlled=\"true\" d1=\"1\" d2=\"1\" />\n",contr_vars3->name);
 		
 		#ifdef DEBUG_ON 
 		printf("\t\t<param name=\"%s\" type=\"real\" local=\"false\" dynamics=\"any\" controlled=\"true\" d1=\"1\" d2=\"1\" />\n",contr_vars3->name);
 		#endif
 		
 		contr_vars3 = contr_vars3->next;
 	}
 	
 	while(params3!=NULL)
 	{
 		init_conds3=HA->init->init_conds;
 		while(init_conds3!=NULL)
 		{
 			if(strcmp(init_conds3->RHS,params3->LHS)==0)
 			{
 				fprintf(fptr, "\t\t<param name=\"%s\" type=\"real\" local=\"false\" dynamics=\"const\" controlled=\"true\" d1=\"1\" d2=\"1\" />\n", init_conds3->RHS);
 				
 				#ifdef DEBUG_ON 
 				printf("\t\t<param name=\"%s\" type=\"real\" local=\"false\" dynamics=\"const\" controlled=\"true\" d1=\"1\" d2=\"1\" />\n", init_conds3->RHS);
 				#endif
 				
 				break;
 			}
 			init_conds3=init_conds3->next;
 		}
 		params3=params3->next;	
 	}
 	while(synclabs3!=NULL)
 	{
 		fprintf(fptr, "\t\t<param name=\"%s\" type=\"label\" local=\"false\"/>\n", synclabs3->name);
 		
 		#ifdef DEBUG_ON 
 		printf("\t\t<param name=\"%s\" type=\"label\" local=\"false\"/>\n", synclabs3->name);
 		#endif
 		
 		synclabs3 = synclabs3->next;	
 	}
 	fprintf(fptr, "\t\t<bind component=\"%s_template\" as=\"%s_bind\">\n", ha->name, ha->name);
 	
 	#ifdef DEBUG_ON 
 	printf("\t\t<bind component=\"%s_template\" as=\"%s_bind\">\n", ha->name, ha->name);
 	printf("\nPARAMS \n");
 	#endif
 	
 	while(params2!=NULL)
 	{
 		fprintf(fptr, "\t\t\t<map key=\"%s\">%s</map>\n", params2->LHS, params2->RHS);
 		
 		#ifdef DEBUG_ON 
 		printf("\t\t\t<map key=\"%s\">%s</map>\n", params2->LHS, params2->RHS);
 		#endif
 		
 		params2 = params2->next;
 	}
 	
 	#ifdef DEBUG_ON 
 	printf("\nINITIAL CONDS\n");
 	#endif
 	
 	while(contr_vars2!=NULL)
 	{
 		fprintf(fptr, "\t\t\t<map key=\"%s\">%s</map>\n", contr_vars2->name, contr_vars2->name);
 		
 		#ifdef DEBUG_ON 
 		printf("\t\t\t<map key=\"%s\">%s</map>\n", contr_vars2->name, contr_vars2->name);
 		#endif
 		
 		contr_vars2 = contr_vars2->next;
 	}
 	
 	#ifdef DEBUG_ON 
 	printf("\nSYNC LABS \n");
 	#endif
 	
 	while(synclabs2!=NULL)
 	{
 		fprintf(fptr, "\t\t\t<map key=\"%s\">%s</map>\n", synclabs2->name, synclabs2->name);
 		
 		#ifdef DEBUG_ON 
 		printf("\t\t\t<map key=\"%s\">%s</map>\n", synclabs2->name, synclabs2->name);
 		#endif
 		
 		synclabs2 = synclabs2->next;	
 	}
 	fflush(fptr);
 	fprintf(fptr, "\t\t</bind>\n");
 	fprintf(fptr, "\t</component>\n");
 	fprintf(fptr, "</sspaceex>");
 	
 	#ifdef DEBUG_ON 
 	printf("\t\t</bind>\n");
 	printf("\t</component>\n");
 	printf("</sspaceex>");
 	#endif
 	
 	fflush(fptr);
 	
 	#ifdef DEBUG_ON 
 	printf("\nAFTER FLUSHING TO FILE");
 	#endif
 	
 	fflush(stdout);
 	
 	#ifdef DEBUG_ON 
 	printf("\nAFTER FLUSHING STDOUT");
 	#endif
 	
 	fclose(fptr);
 	
 	#ifdef DEBUG_ON 
 	printf("\n--------------SpaceEx XML output is now available--------------\n");  
 	#endif
 	
 	return finalID;
 }


void writeSpaceExConfig(struct phaver* HA,char *fileName, double samplingTime, double timeHorizon, int scenario, char* featureName){
	#ifdef DEBUG_ON 
		printf("[writeSpaceExConfig] STARTED\n");
	#endif
	
	FILE *out = fopen(fileName,"w");
	fprintf(out,"system = %s\n",HA->ha->name);
	//fprintf(out,"initially = \"");
	printSpaceExConfigInitial(HA->ha->name,HA->init,out);
	if(scenario == 0){
		fprintf(out,"scenario = supp\n");
	} else {
		fprintf(out,"scenario = stc\n");
	}
	fprintf(out,"directions = oct\n");
	fprintf(out,"set-aggregation = \"chull\"\n");
	fprintf(out,"sampling-time = %*.*lf\n",DBL_DIG,DBL_MANT_DIG,samplingTime);
	//fprintf(out,"sampling-time = %*.*lf\n",(double)samplingTime);
	fprintf(out,"flowpipe-tolerance = %*.*lf\n",DBL_DIG,DBL_MANT_DIG,samplingTime);//0.001\n");
	fprintf(out,"time-horizon = %lf\n",timeHorizon);
	fprintf(out,"clustering = 100\n");
	fprintf(out,"iter-max = -1\n");
	if(featureName!=NULL){
		fprintf(out,"output-variables = \"%s\"\n",featureName);
	} else {
		fprintf(out,"output-variables = \"");
		struct identifier* var = HA->ha->contr_vars;
		while(var && var->next){
			fprintf(out,"%s,",var->name);
			var = var->next;
		}
		fprintf(out,"%s\"\n",var->name);
	}
	fprintf(out,"output-format = INTV\n");
	fprintf(out,"verbosity = m\n");
	fprintf(out,"output-error = 0\n");
	fprintf(out,"rel-err = 1.0E-12\n");
	fprintf(out,"abs-err = 1.0E-15\n");
	
	fclose(out);
	
	#ifdef DEBUG_ON 
		printf("[writeSpaceExConfig] ENDED\n");
	#endif
}

//-------------------------------OTHER METHODS-------------------------------
void readModelList(struct identifier** list){
	*list = NULL;
	char fileName[]="lib/modelList.txt";
	FILE *modelList = fopen(fileName,"r");
	
	char model[MAX_STR_LENGTH];
	while(fscanf(modelList,"%s",model)!=EOF){
		*list = addToIdentifierList(*list,model);
	}
	
	fclose(modelList);    
}

int displayModelList(struct identifier* list){
	struct identifier* model = list;
	int count = 0;
	
	printf("\n\n---------------Model Library-----------------\n");
	
	while(model!=NULL){
		printf("[%d] %s\n",++count,model->name);
		model = model->next;		
	}
	printf("\n\n----------------------------------------------\n");
	return count;
}

int requestModelChoice(int count){
	int id;
	
	do{
		printf("Enter the ID of the model you wish to generate: ");
		scanf("%d",&id);
	} while(!(id>=0 & id<=count));
	
	if(id == 0) exit(0);
	return id;	
}

int displayModelParameters(struct phaver* HA){
	struct condition* param = HA->params;
	int count=0;
	printf("\n\n---------------Parameter List-----------------\n");
	while(param!=NULL){
		printf("\n");
		printf("[%d] : ",++count);
		printCondition(param);
		param = param->next;
	}
	printf("\n\n----------------------------------------------\n");	
	return count;
}

int requestParamChoice(int count){
	int id;
	
	do{
		printf("Enter the ID of the parameter you wish to edit. If you are satisfied with the value list enter 0. : ");
		scanf("%d",&id);
	} while(!(id>=0 & id<=count));

	return id;	
}

int editParameter(int id, struct condition* params){
	struct condition* param = params;
	int count=1;
	while(count!=id & param!=NULL){
		param=param->next;
		count++;
	}
	
	if(param == NULL){ return -1 ;}
	
	printf("Present Parameter Value: "); printCondition(param);
	
	printf("Suggested Value: ");
	scanf("%s",param->RHS);
	
	printf("Updated Parameter Value: "); printCondition(param);
	
	return id;
}

char* getModelName(int id, struct identifier* list){
	if(list!=NULL){
		struct identifier* model = list;
		int count=1;
		while(count!=id & model!=NULL){
			model = model->next;
			count++;
		}
	
		if(model == NULL){ return NULL ;}
		
		return model->name;
	}
	return NULL;
}

void readFeatureList(struct identifier** list,char* modelName){
	#ifdef DEBUG_ON 
		printf("[readFeatureList] STARTED\n");
	#endif
	
	*list = NULL;
	char fileName[MAX_STR_LENGTH];
	sprintf(fileName,"lib/features/%s/featureList.txt",modelName);
	FILE *featureList = fopen(fileName,"r");
	
	char feature[MAX_STR_LENGTH];
	while(fscanf(featureList,"%s",feature)!=EOF){
		*list = addToIdentifierList(*list,feature);
	}
	
	fclose(featureList);    
	
	#ifdef DEBUG_ON 
		printf("[readFeatureList] ENDED\n");
	#endif
}

int displayFeaturelList(struct identifier* list){
	#ifdef DEBUG_ON 
		printf("[displayFeaturelList] STARTED\n");
	#endif
	
	struct identifier* feature = list;
	int count = 0;
	printf("\n\n---------------Feature Library---------------\n");
	while(feature!=NULL){
		printf("[%d] %s\n",++count,feature->name);
		feature = feature->next;		
	}
	printf("\n\n---------------------------------------------\n");
	#ifdef DEBUG_ON 
		printf("[displayFeaturelList] ENDED\n");
	#endif
	
	return count;
}

int requestFeatureChoice(int count){
	#ifdef DEBUG_ON 
		printf("[requestFeatureChoice] STARTED\n");
	#endif
	
	int id;
	
	do{
		printf("Enter the ID of the feature you wish to compute: ");
		scanf("%d",&id);
	} while(!(id>=0 & id<=count));
	
	if(id == 0){
		#ifdef DEBUG_ON 
			printf("[requestFeatureChoice] ENDED by EXITING PROGRAM\n");
		#endif
		exit(0);
	}
	
	#ifdef DEBUG_ON 
		printf("[requestFeatureChoice] ENDED\n");
	#endif
	
	return id;	
}


char* getFeatureName(int id, struct identifier* list){
	#ifdef DEBUG_ON 
		printf("[getFeatureName] STARTED\n");
	#endif
	
	struct identifier* feature = list;
	int count=1;
	while(count!=id & feature!=NULL){
		feature = feature->next;
		count++;
	}
	
	if(feature == NULL){ return NULL ;}
	
	#ifdef DEBUG_ON 
		printf("[getFeatureName] ENDED\n");
	#endif
	
	return feature->name;
}

char* strToUpper(char* str){
	int len = strlen(str);
	char* newStr = (char*)malloc(sizeof(char)*(len+1));
	
	for(int i=0;i<len;i++){
		newStr[i] = toupper(str[i]);
	}
	newStr[len] = '\0';
	return newStr;
}

struct value* addToValues(struct value* root, double encL, double encR, double timeL, double timeR){
	#ifdef DEBUG_ON
	printf("[addToValues] STARTED\n");
	#endif

	struct value* val = (struct value*)malloc(sizeof(struct value));
	struct value* temp = root;

	val->encL = encL;
	val->encR = encR;
	val->timeL = timeL;
	val->timeR = timeR;
	val->next = NULL;

	#ifdef DEBUG_ON
	printf("[addToValuesstructs] CRETED NODE\n");
	#endif


	if(root!=NULL){
		#ifdef DEBUG_ON
		printf("[addToValues] VALUE LIST NOT EMPTY\n");
		#endif

		while(temp->next!=NULL){
			temp=temp->next;
		}
		#ifdef DEBUG_ON
		printf("[addToValues] VALUE TO CONDITION LIST\n");
		#endif

		temp->next = val;

	} else {
		#ifdef DEBUG_ON
		printf("[addToValues] VALUE LIST EMPTY\n");
		printf("[addToValues] ADDING TO VALUE LIST\n");
		#endif

		root = val;

		#ifdef DEBUG_ON
		printf("[addToValues] ROOT CHANGED\n");
		printf("[addToValues] ROOT = %p, NEXT = %p\n",root,root->next);
		#endif

	}
	

	return root;
}

void freeValueList(struct value* root){
	if(root!=NULL){
		freeValueList(root->next);
		free(root);
	}
}

void freeVar(struct varValue* root){
	if(root!=NULL){
		freeValueList(root->values);
		free(root);
	}
}

int getSpaceExScenario(){
	printf("\n Choose a SpaceEx Scenario: [2 is default]\n\t1. LGG\n\t2. STC\n");
	int scenario = 2;
	scanf("%d",&scenario);
	if(scenario==2)
		return 1;
	return 0;
}

char* trim(char *str) {
	  char *end;

	// Trim leading space
	while(isspace(*str)) str++;

	if(*str == 0)  // All spaces?
		return str;

	// Trim trailing space
	end = str + strlen(str) - 1;
	while(end > str && isspace(*end)) end--;

	// Write new null terminator
	*(end+1) = 0;

	return str;
}

struct interval* createInterval(){
	return createIntervalInit(0.0,0.0,0);
}

struct interval* createIntervalInit(double left, double right, int id){
	struct interval* range = (struct interval*)malloc(sizeof(struct interval));
	range->left = left;
	range->right = right;
	range->id = id;
	return range;
}

int fileCopy(const char* source, const char* dest){
	if(source!=NULL && dest!=NULL){
		pid_t cpPID=fork();
		if(cpPID == 0){
			execlp("cp", "cp", source, dest,(char*)NULL);
			printf("ERROR: FAILED TO COPY %s  to %s\n",source,dest);
			exit(127);
			
		} else {
			waitpid(cpPID,0,0); // wait for child to exit 
			return access( dest, F_OK );
		}
	}
}

//---------------------------SMT EXTENSIONS------------------------------------
char* constructGoal(char* featureName, struct interval* range,int id,int type){
	char* goal = (char*)malloc(sizeof(char)*MAX_STR_LENGTH);
	bzero(goal,sizeof(char)*MAX_STR_LENGTH);
	if(type == 0){
		sprintf(goal,"@%d (and (%s >= %lf) (%s <= %lf));",id,featureName,range->left,featureName,range->right);
		printf("\n%s\n",goal);
	} else if(type > 0) {
		sprintf(goal,"@%d (and (%s >= %lf));",id,featureName,range->left);
		printf("\n%s\n",goal);
	} else if(type < 0){
		sprintf(goal,"@%d (and true (%s <= %lf));",id,featureName,range->right);
		printf("\n%s\n",goal);
	}
	return goal;
}

struct interval* satCheck(char *featureName, int depth, float precision, char* goal){
	// Prepare Goal - Passed as Input
	
	// Prepare DRH with Goal
	
	pid_t cpPID=fork();
	if(cpPID == 0){
		execlp("cp", "cp", "models/drhTemplate.drh", "work/aut.drh",(char*)NULL);
		printf("ERROR: FAILED TO COPY DRH TEMPLATE: work/drhTemplate.drh\n");
		exit(127);
		
	} else {
		waitpid(cpPID,0,0); // wait for child to exit 
		
		FILE* drh = fopen("work/aut.drh","a");
		fprintf(drh,"\n\n");
		fprintf(drh,"goal: \n%s",goal);
		fflush(drh);
		fclose(drh);
		
		// Run dReach on the DRH file
		pid_t dreachPID=fork();
		if(dreachPID == 0){
			char* d = (char*)malloc(sizeof(char)*MAX_STR_LENGTH);
			char* p = (char*)malloc(sizeof(char)*MAX_STR_LENGTH);
			sprintf(d,"%d",depth);
			sprintf(p,"%f",precision);
			
			//Redirecting Output
			//char *satOut = (char*)malloc(sizeof(char)*MAX_STR_LENGTH);
			//sprintf(satOut,"drh.out");
			FILE* drhOut = fopen("drh.out", "w");
			fflush(stdout);
			dup2(fileno(drhOut), 1);
			fclose(drhOut);
			
			
			
			execlp("dReach", "dReach","-k", d,"work/aut.drh","--precision",p,"--visualize",(char*)NULL);
			printf("ERROR: FAILED TO EXECUTE dREACH\n");
			exit(127);
			
		} else {
			printf("\nDo you want to force quit this search?");
			char cinput[MAX_STR_LENGTH]; scanf("%s",cinput);
			if(cinput[0]=='y' || cinput[0] =='Y'){
				kill(dreachPID,SIGTERM);
			}
			waitpid(dreachPID,0,0); // wait for child to exit 
			
			drhOutin = fopen("drh.out","r");
			drhOutparse();
			
			printf("kvalue = %d\n",kValue);
			printf("lvalue = %d\n",lValue);
			/*FILE* jsonOut = fopen("jsonLog.out", "w");
			fflush(jsonOut);
			int stdfd = dup2(fileno(jsonOut), STDOUT_FILENO);
			int errfd = dup2(fileno(jsonOut), STDERR_FILENO);
			fclose(jsonOut);*/
			struct interval* range = extractJSONFeatureInterval(featureName,lValue,kValue);
			if(range==NULL){
				printf("\n Range is Null\n");
			} else {
				#ifdef DEBUG_ON
					printf("[extremeTraceSearch] Non-Null Range [%f,%f]\n",range->left,range->right);
				#endif
				char* oldFileName = (char*)malloc(sizeof(char)*MAX_STR_LENGTH);
				char* newFileName = (char*)malloc(sizeof(char)*MAX_STR_LENGTH);
				sprintf(oldFileName,"work/aut_%d_%d.smt2.json",kValue,lValue);
				sprintf(newFileName,"work/data_%d.json",++traceCount);
				range->id = traceCount;
				
				if(fileCopy(oldFileName,newFileName)!=0){//rename(oldFileName,newFileName)!=0){
					printf("Error Renaming File [%s] to [%s]\n",oldFileName,newFileName);
					exit(0);
				}
				sprintf(oldFileName,"work/aut.drh");
				sprintf(newFileName,"work/aut_%d.drh",traceCount);
				
				if(fileCopy(oldFileName,newFileName)!=0){//rename(oldFileName,newFileName)!=0){
					printf("Error Renaming File [%s] to [%s]\n",oldFileName,newFileName);
					exit(0);
				}
				
				printf("Range = [%lf,%lf]\n",range->left, range->right);
			}
			
			/*dup2(stdfd, STDOUT_FILENO);
			dup2(errfd, STDERR_FILENO);
			close(stdfd);
			close(errfd);*/
			//fprintf(drh,"\n\n");
			return range;
			// Return Answer: SAT - with feature range , or UNSAT - with feature range.
		}
	}
	return NULL;
	
}

struct interval* extractJSONFeatureInterval(char *featureName, int l, int k){
	char* varName = (char*)malloc(sizeof(char)*MAX_STR_LENGTH);
	sprintf(varName,"%s_%d_0",featureName,k);
	
	struct interval* range = NULL;
	
	char* fileName = (char*)malloc(sizeof(char)*MAX_STR_LENGTH);
	sprintf(fileName,"work/aut_%d_%d.smt2.json",k,l);
	//------------------JSON EXTRACT--------------------------
	JsonParser *jsonParser  =  NULL;
	GError *error  =  NULL;
	jsonParser = json_parser_new ();


	json_parser_load_from_file (jsonParser,
	                            fileName,
	                            &error);

	if (error) {
	    g_error_free(error);
	} else {
	    JsonNode *root;
	    root = json_parser_get_root(jsonParser);

	    if(root!=NULL){
	    	#ifdef DEBUG_ON
	    	printf("Root NOT NULL\n");
	    	#endif
	    	JsonObject *object = NULL;
	    	object = json_node_get_object(root);

	    	const gchar* memberName;
	    	JsonNode *memberValue;

	    	JsonObjectIter iter;
	    	json_object_iter_init(&iter,object);

	    	while(json_object_iter_next(&iter, &memberName, &memberValue)){
	    		//There should be a single object at the root named "traces"

	    		#ifdef DEBUG_ON
	    		printf("\nRoot Object Name = %s\n",memberName);
	    		#endif
	    		
	    		if(strcmp((const char*)memberName,"traces")!=0){
	    			#ifdef DEBUG_ON
	    			printf("Skipping this field of the object");
	    			#endif
	    			
	    			continue;
	    		}

	    		JsonArray *stepArray = NULL;
	    		stepArray = json_node_get_array(memberValue);
				
				#ifdef DEBUG_ON
	    		printf("\nListing SMT Unrolled Steps:\n");
				#endif
				
	    		int steps = json_array_get_length(stepArray);
	    		int stepIterator = 0;
	    		JsonNode *stepMember = NULL;

	    		if(steps==0){
	    			#ifdef DEBUG_ON
	    			printf("\nNo Step Array Members\n");
	    			#endif
	    			
	    			return 0;
	    		}

	    		while(stepIterator < steps){
	    			//For each step
	    			stepMember = json_array_get_element(stepArray,stepIterator);
	    			if(stepMember==NULL){
	    				#ifdef DEBUG_ON
	    				printf("\nError: Expected a Step Array Member at this position\n");
	    				#endif
	    				
	    				return 0;
	    			}
	    			
	    			#ifdef DEBUG_ON
	    			printf("\n\t Step %d\n",stepIterator);
	    			#endif
	    			
	    			JsonArray *step =json_node_get_array(stepMember);

	    			#ifdef DEBUG_ON
	    			printf("\n\t Variable Valuations\n");
	    			#endif
	    			
	    			int varCount = json_array_get_length(step);
	    			int varIterator = 0;
	    			JsonNode *var = NULL;

	    			#ifdef DEBUG_ON
	    			printf("\n\t Numebr of Variables: %d\n",varCount);
	    			#endif
	    			
	    			struct varValue* varVal = NULL;
	    			while(varIterator<varCount){
	    				var = json_array_get_element(step,varIterator);

	    				if(var==NULL){
	    					#ifdef DEBUG_ON
	    					printf("\nError: Expected a Variable Valuation Array Member at this position\n");
	    					#endif
	    					
	    					return 0;
	    				}
	    				#ifdef DEBUG_ON
		    			printf("\n\t Variable %d\n",varIterator);
		    			#endif

	    				JsonObject *varObject = json_node_get_object(var);

	    				JsonObjectIter varObjectIter;
	    				json_object_iter_init(&varObjectIter,varObject);

	    				const gchar *varMemberName;
	    				JsonNode *varMemberNode;
	    				//printf("After Initialization\n");fflush(stdout);

	    				varVal = (struct varValue*)malloc(sizeof(struct varValue));
	    				varVal->values = NULL;
	    				while(json_object_iter_next(&varObjectIter,&varMemberName,&varMemberNode)){
	    					//printf("%s : ",varMemberName);

	    					if(strcmp((const char*)varMemberName,"mode")==0){
	    						//int value;
	    						//value = json_node_get_int(varMemberNode);
	    						//printf("%d",value);
	    						varVal->mode = json_node_get_int(varMemberNode);

	    					}

	    					if(strcmp((const char*)varMemberName,"step")==0){
	    						varVal->step = json_node_get_int(varMemberNode);
	    					}

	    					if(strcmp((const char*)varMemberName,"key")==0){
	    						const gchar *key = json_node_get_string(varMemberNode);
	    						//if(strncmp(key,"vc",2)!=0){
	    						//	printf("\"%s\"\n",key);
	    						//	break;
	    						//}
	    						//printf("\"%s\"\n",key);
	    						strcpy(varVal->key,(const char*)key);
	    					}

	    					if(strcmp((const char*)varMemberName,"values")==0){
	    						JsonArray *values = json_node_get_array(varMemberNode);
	    						int valueCount = json_array_get_length(values);
	    						int valueIterator = 0;
	    						JsonNode *valueNode = NULL;
	    						JsonObject *valueObject = NULL;

	    						while(valueIterator < valueCount){
	    							valueNode = json_array_get_element(values,valueIterator);
	    							valueObject = json_node_get_object(valueNode);
	    							JsonObjectIter valueObjectIter;
	    							json_object_iter_init(&valueObjectIter,valueObject);
	    							const gchar* valueMemberName;
	    							JsonNode *valueMemberNode;
	    							double encL,encR,timeL,timeR;
	    							while(json_object_iter_next(&valueObjectIter,&valueMemberName,&valueMemberNode)){
	    								//printf("%s : ",valueMemberName);
	    								JsonArray *range = json_node_get_array(valueMemberNode);
	    								//int rangeIterator = 0;
	    								JsonNode *rangeValueL = json_array_get_element(range,0);
	    								JsonNode *rangeValueR = json_array_get_element(range,1);

	    								//printf("%lf , %lf\n",json_node_get_double(rangeValueL),json_node_get_double(rangeValueR));
	    								if(strcmp((const char*)valueMemberName,"enclosure")==0){
	    									encL = json_node_get_double(rangeValueL);
	    									encR = json_node_get_double(rangeValueR);
	    								} else {
	    									timeL = json_node_get_double(rangeValueL);
	    									timeR = json_node_get_double(rangeValueR);
	    								}

	    							}
	    							varVal->values = addToValues(varVal->values,encL,encR,timeL,timeR);
	    							/*if(varVal->values == NULL){
	    								printf("ITS NULL\n");
	    								exit(0);
	    							} else {
	    								struct value* v = varVal->values;
	    								printf("\n\n");
	    								while(v){

	    									printf("enc:[%lf,%lf] : time:[%lf,%lf]\n",v->encL,v->encR,v->timeL,v->timeR);
	    									v = v->next;
	    								}
	    							}*/
	    							valueIterator++;
	    						}
	    						/*if(varVal->values == NULL){
	    							printf("ITS NULL\n");
	    							exit(0);
	    						} else {
	    							struct value* v = varVal->values;
	    							printf("\n\n");
	    							while(v){

	    								printf("enc:[%lf,%lf] : time:[%lf,%lf]\n",v->encL,v->encR,v->timeL,v->timeR);
	    								v = v->next;
	    							}
	    						}*/
	    						//printf("\nInner Block varValues = %p",varVal->values);
	    					}
	    					//printf("\nOuter Block varValues = %p",varVal->values);
	    					/*if(varVal->values == NULL){
	    						printf("\nITS NULL\n");
	    						exit(0);
	    					} else {
	    						struct value* v = varVal->values;
	    						printf("\n\n");
	    						while(v){

	    							printf("enc:[%lf,%lf] : time:[%lf,%lf]\n",v->encL,v->encR,v->timeL,v->timeR);
	    							v = v->next;
	    						}
	    					}
	    					printf("\n");*/
	    					fflush(stdout);
	    				}
	    				//printf("\nReally Outer Block varValues = %p",varVal->values);
	    				
	    				#ifdef DEBUG_ON
	    				printf("varVal->key : %s\n",varVal->key);
	    				printf("COMPARE: %d\n", strcmp(varVal->key,varName));
	    				#endif
	    				
	    				if(strcmp(varVal->key,varName)==0){
	    					#ifdef DEBUG_ON
	    					printf("PRINTING\n");
	    					#endif
	    					
	    					range = createInterval();
	    					if(varVal->values == NULL){
	    						#ifdef DEBUG_ON
	    						printf("ITS NULL\n");
	    						#endif
	    						exit(0);
	    					}
	    					struct value* v = varVal->values;
	    					while(v){
								#ifdef DEBUG_ON
	    						printf("enc:[%lf,%lf] : time:[%lf,%lf]\n",v->encL,v->encR,v->timeL,v->timeR);
	    						#endif
	    						
	    						range->left = v->encL;
	    						range->right = v->encR;
	    						v = v->next;
	    					}
	    				}
	    				free(varVal);
	    				varIterator++;
	    			}
	    			stepIterator++;
	    		}
	    	}
	    	//printf("JSON: %s\n",json_node_get_string(root));
	    	//printf("JSON: %s\n",json_node_type_name(root));
	    	//printf("JSON: %s\n",json_node_get_value_type(root));
	    }
	}
	
	free(varName);
	free(fileName);
	
	return range;
	
}

/*
 * Searching using SMT - dReach
 */
struct interval* extremeTraceSearch(char* featureName, struct interval* range, double e, int depth, int precision, int dir, int id){
	#ifdef DEBUG_ON
		printf("[extremeTraceSearch] STARTED\n");
	#endif
	if(featureName!=NULL && range!=NULL){
		double left = range->left;
		double right = range->right;
		double mid = left;
		
		//If Precision bound has been met
		if(fabs(left - right)<= 2*e){
			return range;
		}
		
		#ifdef DEBUG_ON
			printf("[extremeTraceSearch] Remembering Given Range\n");
		#endif
		struct interval* givenRange = createIntervalInit(range->left,range->right,id);
		
		
		#ifdef DEBUG_ON
			printf("[extremeTraceSearch] Computing Mid-Point\n");
		#endif
		//Compute the mid-point
		mid = (left + right)/2;
		
		struct interval* goalInterval = createInterval();
		struct interval* satResult = NULL;
		
		if(dir<0){	//LEFT Search - Left Interval
			goalInterval->left = left;
			goalInterval->right = mid;
		} else {	//RIGHT Search - Right Interval
			goalInterval->left = mid;
			goalInterval->right = right;
		}
		
		#ifdef DEBUG_ON
			printf("[extremeTraceSearch] Searching %s in [%f:%f]\n",(dir<0)?"left":"right",goalInterval->left,goalInterval->right);
		#endif
		
		
		#ifdef DEBUG_ON
			printf("[extremeTraceSearch] Calling SatCheck (1)\n");
		#endif
		satResult = satCheck(featureName,depth,precision,constructGoal(featureName, goalInterval,id,0));
		#ifdef DEBUG_ON
			printf("[extremeTraceSearch] Back from SatCheck (1)\n");
		#endif
		
		if(satResult!=NULL){ 
		//--------------------------- If SATISFIABLE then---------------------------------
			if(dir<0){
				givenRange->right = (satResult->left - e);
			} else {
				givenRange->left = (satResult->right + e);
			}
			givenRange->id = satResult->id;
			struct interval* temp = extremeTraceSearch(featureName, givenRange, e, depth, precision, dir, id);
			if(temp) return temp;
			else return satResult;

		} else {
		//------------------------- If NOT SATISFIABLE then------------------------------
			#ifdef DEBUG_ON
				printf("[extremeTraceSearch] Null Range \n");
			#endif
			if(dir<0){
				//LEFT Search - Right Interval
				goalInterval->left = mid;
				goalInterval->right = right;
			} else {
				//RIGHT Search - Left Interval
				goalInterval->left = left;
				goalInterval->right = mid;
			}
			
			#ifdef DEBUG_ON
				printf("[extremeTraceSearch] Calling SatCheck(2)\n");
			#endif
			
			satResult = satCheck(featureName,depth,precision,constructGoal(featureName, goalInterval,id,0));
			
			#ifdef DEBUG_ON
				printf("[extremeTraceSearch] Back from SatCheck(2)\n");
			#endif
			
			if(satResult != NULL) {
				if(dir<0){
					givenRange->left = mid;
					givenRange->right = (satResult->left - e);
				} else {
					givenRange->left = (satResult->right +e);
					givenRange->right = mid;
				}
				givenRange->id = satResult->id;
				struct interval *temp = extremeTraceSearch(featureName, givenRange, e, depth, precision, dir, id);
				if(temp) return temp;
				else return satResult;
			} else 
				return NULL;
		}
	}
	#ifdef DEBUG_ON
		printf("[extremeTraceSearch] ENDED with NULL\n");
	#endif
	return NULL;
}


float timedDiff(struct timeval t0, struct timeval t1){
	return (t1.tv_sec - t0.tv_sec)*1000.0f + (t1.tv_usec - t0.tv_usec)/1000.0f;
}
