#include "8puzzle.h"

int main()
{ 
  
  puzzleState init;
  init = problem_init();		/* set initial state */
 

 puzzleState goal;
 goal = goal_init();
  
 QUEUE* bfsQ;
 bfsQ = queue_init();
  
 NODE* solution=NULL;
 if(isSolvable(&init))
    {
      solution = solve(init,&goal,bfsQ);
      printf("Solution to 8 puzzle problem\n\n");
      showsolution(solution);
    }
    else
      printf("\nNo solution Exists\n");
 
}

