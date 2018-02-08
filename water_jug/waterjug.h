
#include <stdio.h>
#include <stdlib.h>

#ifndef WATERJUG
#define WATERJUG
typedef struct 
{
  int jug_A;
  int jug_B;
  int maxA;
  int maxB;
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
  NODE * root;      //points to root node of search tree
}QUEUE;

/*It uses breadth first through a FIFO Queue.
 The Queue does not accept repeated states (to avoid infinite loops).
  The Queue stores nodes of the search tree 
  and so when a solution is found it can print out the solution by tracing rear up the tree to the first NODE.
 This lends itself to a recursive display algorithm.*/ 



/*production rules for solving water jug problem*/
puzzleState fillA(puzzleState state);
puzzleState fillB(puzzleState state);
puzzleState emptyA(puzzleState state);
puzzleState emptyB(puzzleState state);
puzzleState B_to_A(puzzleState state);
puzzleState A_to_B(puzzleState state);


int min(int x,int y);
int max(int x,int y);
int gcd(int m,int n);

puzzleState goal_init();
puzzleState problem_init();


QUEUE *queue_init();

void enqueue(puzzleState state,QUEUE *bfsQ);
int empty(QUEUE *bfsQ);
void dequeue(QUEUE *bfsQ);
int equals(puzzleState *lhs, puzzleState *rhs);


NODE * solve(puzzleState init,puzzleState *goal,QUEUE *bfsQ);
void showsolution(NODE * solution);

int isGoal(puzzleState * current,puzzleState * goal);
int  isSolvable(puzzleState *init,puzzleState *goal);
void stateprinter(puzzleState *state);             //can be used to print any state 

#endif



