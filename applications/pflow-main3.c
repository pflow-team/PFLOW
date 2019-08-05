static char help[] = "User example calling PFLOW. Reads data in PSSE raw format\n\n";

#include <pflow.h>


int main(int argc,char **argv)
{
  PetscErrorCode ierr;
  PFLOW          pflow;
  char              file[PETSC_MAX_PATH_LEN];
  PetscBool      flg; 

  PetscInitialize(&argc,&argv,"petscopt",help);
  
  /* Create PFLOW object */
  ierr = PFLOWCreate(PETSC_COMM_WORLD,&pflow);CHKERRQ(ierr);

  /* Get network data file from command line */
  ierr = PetscOptionsGetString(NULL,NULL,"-netfile",file,PETSC_MAX_PATH_LEN,&flg);CHKERRQ(ierr);
  /* Read Network Data file */
  if(flg) {
    ierr = PFLOWReadMatPowerData(pflow,file);CHKERRQ(ierr);
  } else {
    ierr = PFLOWReadMatPowerData(pflow,"datafiles/case9mod.m");CHKERRQ(ierr);
  }

  /* Solve */
  ierr = PFLOWSolve(pflow);CHKERRQ(ierr);

  /* Update line flows, Pgen, Qgen, and other parameters */
  ierr = PFLOWPostSolve(pflow);CHKERRQ(ierr);

  /* Trip lines 4-6 and 8-9 so that two islands are created
     Island 1: 1-4-5-7-2-8
     Island 2: 3-9-6
  */
  ierr = PetscPrintf(PETSC_COMM_SELF,"Tripping branch %d -- %d\n",8,9);CHKERRQ(ierr);
  /* Trip a line 8-9 */
   ierr = PFLOWSetLineStatus(pflow,8,9,"1 ",0);CHKERRQ(ierr);

  ierr = PetscPrintf(PETSC_COMM_SELF,"Tripping branch %d -- %d\n",4,6);CHKERRQ(ierr);
  /* Trip a line 4-6 */
  ierr = PFLOWSetLineStatus(pflow,4,6,"1 ",0);CHKERRQ(ierr);

  /* Solve */
  ierr = PFLOWSolve(pflow);CHKERRQ(ierr);

  /* Update line flows, Pgen, Qgen, and other parameters */
  ierr = PFLOWPostSolve(pflow);CHKERRQ(ierr);

  /* Switch OFF generator 3, this will blackout island 2 */
  ierr = PetscPrintf(PETSC_COMM_SELF,"Tripping Generator at bus\n",3);CHKERRQ(ierr);
  ierr = PFLOWSetGenStatus(pflow,3,"1 ",0);CHKERRQ(ierr);

  /* Solve */
  ierr = PFLOWSolve(pflow);CHKERRQ(ierr);

  /* Update line flows, Pgen, Qgen, and other parameters */
  ierr = PFLOWPostSolve(pflow);CHKERRQ(ierr);

  /* Destroy PFLOW object */
  ierr = PFLOWDestroy(&pflow);CHKERRQ(ierr);

  PetscFinalize();
  return 0;
}
  
