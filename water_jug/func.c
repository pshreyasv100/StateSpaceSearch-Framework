
#include "waterjug.h"

int min(int x,int y)
{
  return (x < y)?x:y;
}


int max(int x,int y)
{
  return (x > y)?x:y;
}

int gcd(int m,int n)
{
  while(m!=n)
    {
       (m>n)? (m-=n):(n-=m);
    }
    return m;
}

puzzleState goal_init()
{
  puzzleState goal;
  printf("Enter goal water jug puzzle\n");
  scanf("%d",&goal.jug_A);
  return goal;
}


puzzleState problem_init()
{
  puzzleState init;
  init.jug_A=0;
  init.jug_B=0;
  printf("Enter capacity of jug A ");
  scanf("%d",&init.maxA);
  printf("Enter capacity of jug B (less than A)  ");
  scanf("%d",&init.maxB);
  return init;
}

QUEUE *queue_init()
{
  QUEUE *bfsQ;
  bfsQ = (QUEUE*)malloc(sizeof(QUEUE));
  bfsQ->front = NULL;
  bfsQ->rear = NULL;
  bfsQ->root = NULL;
  return bfsQ;
}

void showsolution(NODE * solution) 
/* Recursive diplay of solution as it has unwound from the solution */
{
  if (solution->parent != NULL)
    showsolution(solution->parent);
	printf(" A = %d B = %d\n",(solution->state).jug_A,(solution->state).jug_B);
}

int isGoal(puzzleState * current,puzzleState * goal)
{
	if (current->jug_A == goal->jug_A)
    return 1;
  return 0;
}



puzzleState fillA(puzzleState state)//
{
	if (state.jug_A<state.maxA)
    {
    state.jug_A=state.maxA;
  }
  return state;
}

puzzleState fillB(puzzleState state)
{
  if (state.jug_B<state.maxB)
    {
      state.jug_B = state.maxB;
    }

 return state;
 }

puzzleState emptyA(puzzleState state)
{
  if (state.jug_A>0)

  {
    state.jug_A =0;
  }
   
 return state;
 }

puzzleState emptyB(puzzleState state)
{
  if (state.jug_B>0)
    {
      state.jug_B =0;
  }
   
 return state;
 }


puzzleState B_to_A(puzzleState state)
{

  int ja = state.jug_A;
  int jb = state.jug_B;
  if (state.jug_B > 0)
  {
    state.jug_A = min((ja + jb), state.maxA);
    state.jug_B = max(0,(ja + jb - state.maxA));
  }
  return state;
}



 puzzleState A_to_B(puzzleState state)
{
  int ja = state.jug_A;
  int jb = state.jug_B;
  if (state.jug_A > 0)
  {
    state.jug_A = max(0 ,ja + jb - state.maxB);
    state.jug_B = min((ja + jb), state.maxB);
  }
  return state;
}

void dequeue(QUEUE *bfsQ)
{
  bfsQ->front = bfsQ->front->next;
}

int empty(QUEUE *bfsQ) {
  return (bfsQ->front==NULL)?1:0;
}

NODE * solve(puzzleState state,puzzleState *goal,QUEUE *bfsQ)
{
 

  enqueue(state ,bfsQ);  
  if (isGoal(&(bfsQ->front->state),goal))
      return bfsQ->front;
  else
    {
      while (!empty(bfsQ))
      {
        if (isGoal(&(bfsQ->front->state),goal))
           return bfsQ->front;
        else 
        { 
        //printf("Printing state of \n");  
        //stateprinter(&(front->state));
        enqueue(fillA(bfsQ->front->state), bfsQ);
        enqueue(fillB(bfsQ->front->state), bfsQ);
        enqueue(emptyA(bfsQ->front->state), bfsQ);
        enqueue(emptyB(bfsQ->front->state), bfsQ);
        enqueue(A_to_B(bfsQ->front->state), bfsQ);
        enqueue(B_to_A(bfsQ->front->state), bfsQ);
        }
       //getchar();
       //printf("-------\n");
       dequeue(bfsQ);   
      }
    }
  }

void enqueue(puzzleState state,QUEUE *bfsQ)
{
  /* Check if state has already been added.... if so do not add.*/ 
  
  NODE * t;

  for(t=bfsQ->root ;t!=NULL; t=t->next)
    if (equals(&state,&(t->state))) return;
  
  NODE * new = (NODE *) malloc(sizeof(NODE));
  new->state = state;
  new->parent = bfsQ->front;
  
  if (bfsQ->front == NULL && bfsQ->rear == NULL) 
  {     
      // Initialize queue
    new->next = NULL;
    bfsQ->front = bfsQ->rear = bfsQ->root = new;
  }
  else
    {
      new->next = NULL;
      bfsQ->rear->next = new;
      bfsQ->rear = new; 
   }
}


int equals(puzzleState *lhs, puzzleState *rhs)// to check if two states are equalss
{
      return ((lhs->jug_A==rhs->jug_A)&&(lhs->jug_B==rhs->jug_B));
}

void stateprinter(puzzleState *state)
{
	printf("A = %d ",state->jug_A);
  printf("B = %d \n",state->jug_B);
}



/* If gcd of n and m does not divide d
 then solution is not possible for given problem*/
int isSolvable(puzzleState *init,puzzleState *goal)
{
  int goal_amt;
  int cap_A,cap_B;
  cap_A = init->maxA;
  cap_B = init->maxB;
  goal_amt = goal->jug_A;
  return ((goal_amt % gcd(cap_A,cap_B))==0); 
} 







