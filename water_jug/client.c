#include "waterjug.h"

int main()
{ 
  int i,j;
  puzzleState init;		
  init = problem_init();   /* set initial state */

 puzzleState goal;
 goal = goal_init();

 QUEUE * bfsQ;
 bfsQ = queue_init();
  
 NODE * solution = NULL;



if(isSolvable(&init,&goal))
{
	solution = solve(init,&goal,bfsQ);
	printf("Solution to waterjug puzzle problem\n\n");
	showsolution(solution);
}
else
printf("\n No solution exists\n");

return 0;
}

