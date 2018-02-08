
#include "8puzzle.h"

puzzleState problem_init()
{
  int i,j;
  puzzleState init;
  printf("Enter initial 8 puzzle configuration\n");//accepting start state of puzzle from user
  for (i=0; i<3 ; ++i)
  {
    for (j=0; j<3; ++j)
    {
      scanf("%d",&init.arr[i][j]);
      if (init.arr[i][j]==0)
      {
        init.blankRow=i;
        init.blankCol=j;
      }
    }
  }
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

puzzleState goal_init()
{
  int i,j;
  puzzleState goal;
  printf("Enter goal state 8 puzzle\n");
  for (i=0; i<3 ; ++i)
  {
    for (j=0; j<3; ++j)
    {
      scanf("%d",&goal.arr[i][j]);
      if (goal.arr[i][j]==0)
      {
        goal.blankRow=i;
        goal.blankCol=j;
      }
  }
  }
  return goal;
}


void showsolution(NODE * solution) 
/* Recursive diplay of solution as it has the unwound from the solution */
{
  if (solution->parent != NULL)
    showsolution(solution->parent);
	
	int i,j,key;
	for (i=0; i<3; ++i)
	{
		for (j=0; j<3 ;++j)
		{
			key = (solution->state).arr[i][j];
			printf("%d |",key);
		}
		printf("\n");
	}
	printf("\n");
}

int isgoal(puzzleState * current,puzzleState * goal)
{
	int i,j,key=0;
	for (i=0; i<3; ++i)
	{
		for (j=0; j<3 ;++j)
		{
			if (current->arr[i][j]!=goal->arr[i][j])
			{
				return 0;
			}
		}
	}
  return 1;
}




puzzleState moveLeft(puzzleState state)//state on moving blank left
{
	
  int b_row,b_col;
  b_row = state.blankRow;
  b_col = state.blankCol;
 
  if (!(state.blankCol-1 < 0)) 
  	{
  	    state.arr[b_row][b_col]=state.arr[b_row][b_col-1]; 
      	state.arr[b_row][b_col-1] =0;
      	state.blankRow = b_row;
      	state.blankCol = b_col-1;
      	//getchar();
      	//stateprinter(&state);
	}
    return state;
 
}

puzzleState moveRight(puzzleState state)//state on moving blank right
{
  int b_row,b_col;
  b_row = state.blankRow;
  b_col = state.blankCol;
  
	if (!(state.blankCol+1 > 2)) 
  	{
  	    state.arr[b_row][b_col]=state.arr[b_row][b_col+1]; 
      	state.arr[b_row][b_col+1] =0;
      	state.blankRow = b_row;
      	state.blankCol = b_col+1;
      	//getchar();
      	//stateprinter(&state);
	}
    return state;
 }

puzzleState moveUp(puzzleState state)//state on moving blank up
{
  int b_row,b_col;
  b_row = state.blankRow;
  b_col = state.blankCol;
  
  if (!(state.blankRow-1 < 0)) 
  	{
  	    state.arr[b_row][b_col]=state.arr[b_row-1][b_col]; 
      	state.arr[b_row-1][b_col] =0;
      	state.blankRow = b_row-1;
      	state.blankCol = b_col;
      	//getchar();
      	//stateprinter(&state);
    }
return state;  
  
}

puzzleState moveDown(puzzleState state)//state on moving  blank down 
{
  int b_row,b_col;
  b_row = state.blankRow;
  b_col = state.blankCol;
  
  if (!(state.blankRow+1 > 2)) 
  	{
  	    state.arr[b_row][b_col]=state.arr[b_row+1][b_col]; 
      	state.arr[b_row+1][b_col] =0;
      	state.blankRow = b_row+1;
      	state.blankCol = b_col;
      	//getchar();
      	//stateprinter(&state);
    }
    return state;
 }



NODE* solve(puzzleState state,puzzleState *goal,QUEUE *bfsQ)
{
  enqueue(state ,bfsQ);	
  if (isgoal(&(bfsQ->front->state),goal))
      return bfsQ->front;
  else
    {
      while (!empty(bfsQ))
      {

       if (isgoal(&(bfsQ->front->state),goal))
           return bfsQ->front;
    	 else 
    	  { 
    	  enqueue(moveLeft(bfsQ->front->state), bfsQ);
    	  enqueue(moveRight(bfsQ->front->state), bfsQ);
    	  enqueue(moveUp(bfsQ->front->state), bfsQ);
    	  enqueue(moveDown(bfsQ->front->state), bfsQ);
    	  }
       dequeue(bfsQ);	  
      }
    }
  }

void dequeue(QUEUE* bfsQ)
{
  bfsQ->front=bfsQ->front->next;
}

int empty(QUEUE* bfsQ) {
  return (bfsQ->front==NULL)?1:0;
}


void enqueue(puzzleState state,QUEUE* bfsQ)
{
  
  /* Check if state has already been added.... if so do not add. */
  NODE * t;
  for(t=bfsQ->root;t!=NULL;t=t->next)
    {
      if (equals(&state,&t->state)) return;
    }
  
  NODE * new = (NODE *) malloc(sizeof(NODE));
  new->state = state;
  new->parent = bfsQ->front;
  
  if (bfsQ->front == NULL && bfsQ->rear == NULL) 
    { 		/* Init */
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

int equals(puzzleState* lhs, puzzleState* rhs)// to check if two states are equal and avoid being added into queue
{
	int i,j,key;
	for (i=0; i<3; ++i)
	{
		for (j=0; j<3 ;++j)
		{
			if (lhs->arr[i][j]!=rhs->arr[i][j] )
			{
				return 0;
			}
		}
  }
	return 1;	
 }

void stateprinter(puzzleState* state)
{
	int i,j,key;
	for (i=0; i<3; ++i)
	{
		for (j=0; j<3 ;++j)
		{
			key =state->arr[i][j];
			printf("%d |",key);
		}
		printf("\n");
	}
	printf("\n");
}


int getInvCount(int arr[3][3])
{

    int temp[9];
    int i,j,k=0;
    for (i=0; i<3; ++i)
    {
      for (j=0; j<3; ++j)
      {
          temp[k++] = arr[i][j];
      }
    }

    int inv_count = 0;
    for (i=0; i<8; i++)
    {
      for (j=i+1; j<9; j++)
      {
       // Value 0 is used for empty space
       if (temp[j] && temp[i] &&  temp[i]>temp[j])
            inv_count++;
      }
    }
    return inv_count;
}
 
/* This function returns true if given 8 puzzle is solvable.
 Count inversions in given 8 puzzle
 return true if inversion count is even otherwise false*/
int  isSolvable(puzzleState* state)
{
  int invCount = getInvCount(state->arr);
  printf("inversion count %d\n",invCount );
  return (invCount%2 == 0);
}
 







