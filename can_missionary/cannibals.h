
#include <stdio.h>
#include <stdlib.h>

#ifndef CAN_MIS
#define CAN_MIS
#define L 1
#define R 0

typedef struct 
{
  int c;         //# of cannibals on left side(goal side) at given time
  int m;         //#of missionaries on left side(goal side) at given time
  int boat;      //side boat is on at a given time
}puzzleState;

typedef struct
{
  puzzleState state;
  void * parent;
  void * next;
}NODE;


typedef struct 
{
  NODE * front;       
  NODE * rear;
  NODE * root;     //points to the root of search tree
}QUEUE;

/*It uses breadth first through a FIFO Queue.
 The Queue does not accept repeated states (to avoid infinite loops).
  The Queue stores nodes of the search tree 
  and so when a solution is found it can print out the solution by tracing rear up the tree to the first NODE.
 This lends itself to a recursive display algorithm.*/ 

/*production rules for cannibal missionaries puzzle*/

puzzleState  suc1(puzzleState state);
puzzleState  suc2(puzzleState state);
puzzleState  suc3(puzzleState state);
puzzleState  suc4(puzzleState state);
puzzleState  suc5(puzzleState state);

puzzleState problem_init();

/*operations related to queue*/
QUEUE* queue_init();
void enqueue(puzzleState state,QUEUE *bfsQ);
int empty(QUEUE *bfsQ);
void dequeue(QUEUE* bfsQ);


int isSolvable(puzzleState* init);
int isGoal(puzzleState* current);
NODE * solve(puzzleState init,QUEUE *bfsQ);
void showsolution(NODE * solution);
int forbidden(puzzleState current); 
int equals(puzzleState* lhs, puzzleState* rhs);
char boatpos(int boat);

#endif



