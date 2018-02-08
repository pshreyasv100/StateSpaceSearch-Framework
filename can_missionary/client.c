#include "cannibals.h"

int main()
{ 
  
  puzzleState init;		/* set initial state */
  init = problem_init();
  

  QUEUE * bfsQ;
  bfsQ = queue_init();

  NODE * solution;

  if (isSolvable(&init))
    {
      solution = solve(init,bfsQ);
      printf("Solution to Missionary and Cannibals Problems\n");
      printf("Can    Mis    Boat\n");
      showsolution(solution);
    }
  else
    printf("No solution exists.\n");
  
  return 0;
}

