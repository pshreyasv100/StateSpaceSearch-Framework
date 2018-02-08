
#include <stdio.h>
#include <stdlib.h>
#ifndef PUZZLE8
#define PUZZLE8


typedef struct 
{
  int blankRow;    //row index of blank
  int blankCol;    //column index of blank
  int arr[3][3];   //array stores configuration of 8 puzzle in a particular state
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
  NODE * root;
}QUEUE;


/*It uses breadth first through a FIFO Queue.
 The Queue does not accept repeated states (to avoid infinite loops).
  The Queue stores nodes of the search tree 
  and so when a solution is found it can print out the solution by tracing rear up the tree to the first NODE.
 This lends itself to a recursive display algorithm.*/ 


/*production rules for 8 puzzle problem*/
puzzleState  moveLeft(puzzleState state);
puzzleState  moveRight(puzzleState state);
puzzleState  moveUp(puzzleState state);
puzzleState  moveDown(puzzleState state);


puzzleState problem_init();
puzzleState goal_init();

QUEUE *queue_init();
void enqueue(puzzleState state,QUEUE* bfsQ);
void dequeue(QUEUE* bfsQ);
int empty(QUEUE* bfsQ);


NODE* solve(puzzleState state,puzzleState *goal,QUEUE *bfsQ);
void showsolution(NODE * solution);            //to display the final solution

int equals(puzzleState *lhs, puzzleState *rhs);
int isgoal(puzzleState * current,puzzleState * goal);
int  isSolvable(puzzleState *state);
int getInvCount(int arr[3][3]);
void stateprinter(puzzleState *state);

#endif

