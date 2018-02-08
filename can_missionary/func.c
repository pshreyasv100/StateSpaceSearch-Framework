
#include "cannibals.h"


/*initial state consists of
  -boat on right
  -0 cannibals on left
  -0 missionaries on left*/

puzzleState problem_init()
{
  puzzleState init;
  init.c = 0;
  init.m = 0;
  init.boat = R;
  return init;
}

QUEUE*queue_init()
{
  QUEUE *bfsQ;
  bfsQ = (QUEUE*)malloc(sizeof(QUEUE));
  bfsQ->front = NULL;
  bfsQ->rear = NULL;
  bfsQ->root = NULL;
  return bfsQ;
}


void showsolution(NODE * solution) 
/* Recursive diplay of solution as it has the unwound from the solution */
{
  if (solution->parent != NULL)
    showsolution(solution->parent);
  printf("%d      %d      %c\n",(solution->state).c,(solution->state).m,boatpos((solution->state).boat));
}

char boatpos(int boat)
{
  char ch = boat ? 'L' : 'R';
  return ch; 
}

int forbidden(puzzleState current) {
  if 
    ((current.c > current.m && current.m != 0)||(current.m > current.c && current.m !=3)) 
  {
    return 1;
  }
  return 0;
}

int isGoal(puzzleState * current)
{
  return ((current->c == 3) &&(current->m == 3)&&(current->boat == L));
}

puzzleState suc1(puzzleState state)//move 1 cannibal across left or right if possible
{
  if (state.boat == L) {
    if (state.c > 0) {
      (state.c)--;
      state.boat = R;
    }
  }

  else if (state.boat == R) {
    if ((state.c) < 3) {
      (state.c)++;
      state.boat = L;
    }
  }
  return state;
}

puzzleState suc2(puzzleState state)//move 2 cannibals across left or right
{
  
  if (state.boat == L) {
    if (state.c > 1) {
      (state.c)-=2;
      state.boat = R;
    }
  }
  
  else if (state.boat == R) 
  {
    if ((state.c) < 2) 
    {
      (state.c)+=2;
      state.boat = L;
    }
  }
  
  return state;
  
}

puzzleState suc3(puzzleState state) //move 1 missionary across left or right
{
  
  if (state.boat == L) 
  {
    if (state.m > 0)
     {
      (state.m)--;
      state.boat = R;
    }
  }
  
  else if (state.boat == R) 
  {
    if ((state.m) < 3) 
    {
      (state.m)++;
      state.boat = L;
    }
  }
  return state;
}

puzzleState suc4(puzzleState state)//move 2 missionaries across left or right
{
  if (state.boat == L) 
  {
    if (state.m > 1) 
    {
      (state.m)-=2;
      state.boat = R;
    }
  }
  
  else if (state.boat == R) 
  {
    if ((state.m) < 2) 
    {
      (state.m)+=2;
      state.boat = L;
    }
  }
  
  return state;
}


puzzleState suc5(puzzleState state)//move 1 cannibal and 1 missionary left or right
{
  
  if (state.boat == L)
   {
    if ((state.m > 0) && (state.c > 0)) 
    {
      (state.m)--;
      (state.c)--;
      state.boat = R;
    }
  }
  
  else if (state.boat == R) 
  {
    if ( (state.m) < 3  && (state.c)< 3 ) 
    {
      (state.m)++;
      (state.c)++;
      state.boat = L;
    }
  }
  
  return state;
}


NODE * solve(puzzleState state,QUEUE* bfsQ)
{
  
  enqueue(state ,bfsQ);	
  if (isGoal(&(bfsQ->front->state)))
      return bfsQ->front;
  else
    {
      while (!empty(bfsQ))
      {
        if (isGoal(&(bfsQ->front->state)))
           return bfsQ->front;
    	  else 
         {  
         	//if a given next state is not violating constraints of problem then insert it into Q
    	  if (!forbidden(suc1(bfsQ->front->state)))
            enqueue(suc1(bfsQ->front->state), bfsQ);

    	  if (!forbidden(suc2(bfsQ->front->state)))
            enqueue(suc2(bfsQ->front->state), bfsQ);

    	  if (!forbidden(suc3(bfsQ->front->state)))
            enqueue(suc3(bfsQ->front->state), bfsQ);
    	 
          if (!forbidden(suc4(bfsQ->front->state))) 
            enqueue(suc4(bfsQ->front->state), bfsQ);
    	 
          if (!forbidden(suc5(bfsQ->front->state)))
            enqueue(suc5(bfsQ->front->state), bfsQ);
    	  }
       dequeue(bfsQ);	  
      }
    }
  
}


void dequeue(QUEUE *bfsQ)
{
  bfsQ->front = bfsQ->front->next;
 // return front;
}

int empty(QUEUE *bfsQ) {
  return (bfsQ->front==NULL)?1:0;
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

int equals(puzzleState* lhs, puzzleState* rhs)
{
  return((lhs->c==rhs->c) && (lhs->m==rhs->m) && (lhs->boat==rhs->boat));
}

int isSolvable(puzzleState* init)
{
  return(init->m >= init->c);
}
