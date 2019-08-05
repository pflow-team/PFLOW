/**
 * @file ps.h
 * @brief Public header file containing the forward declarations for the PS data structs, and it also contains its API declarations.
 *
 * Note: The functions on below are not defined on header file, but implemented on cpp file:\n
 * PSGetNumGlobalLines(PS ps,PetscInt *Nlines)\n
 * PSGetNumGlobalBuses(PS ps,PetscInt *Nbuses)\n
 * PSGetLineConnectivity(PS ps,PetscInt Nlines,int lineconn[])\n
 */

#ifndef __PS_H
#define __PS_H

#include <constants.h>
#include <common.h>

/**
 * @brief public struct for bus
 */
typedef struct _p_PSBUS* PSBUS;

/**
 * @brief public struct for load
 */
typedef struct _p_PSLOAD* PSLOAD;

/**
 * @brief public struct for gen
 */
typedef struct _p_PSGEN* PSGEN;

/**
 * @brief public struct for line
 */
typedef struct _p_PSLINE *PSLINE;

/**
 * @brief Type of application that the PS is used for
 */
typedef enum {
  APP_NONE,     /**< No application (default) */
  APP_ACPF,     /**< AC Power flow */
}PSApp;


/**
 * @brief power system public struct
 */
typedef struct _p_PS* PS;

/**
 * @brief Struct that hold values for the matrix
 */
typedef struct{
  PetscInt row;
  PetscInt col;
  PetscScalar value;
}MatValues;

/**
 * @brief Reads the MATPOWER data file and populates the PS object
 * @param [in] PS ps - The power system object ps
 * @param [in] const char[] netfile - Name of the power system network data file in MATPOWER data format.
 */
PETSC_EXTERN PetscErrorCode PSReadMatPowerData(PS,const char[]);
/**
 * @brief Reads the PSSE raw data file and populates the PS object
 * @param [in] PS ps - The power system object ps
 * @param [in] const char[] netfile - Name of the power system network data file in PSSE raw data format.
 */
PETSC_EXTERN PetscErrorCode PSReadPSSERawData(PS,const char[]);
/**
 * @brief Creates the PS object
 * @param [in] MPI_Comm mpicomm - the MPI communicator
 * @param [out] PS* psout - The PS object
 */
PETSC_EXTERN PetscErrorCode PSCreate(MPI_Comm,PS*);
/**
 * @brief Destroys the PS object created with PSCreate
 * @param [out] PS* ps - Pointer to PS object to be destroyed
 */
PETSC_EXTERN PetscErrorCode PSDestroy(PS*);
/**
 * @brief Destroys the GEN data struct in PS
 * @param [in] PS ps - The PS object
 */
PETSC_EXTERN PetscErrorCode PSGENDestroy(PS);
/**
 * @brief Increases the reference count of PS to indicate that is being shared by other objects
 * @param [in] PS ps - The PS object
 */
PETSC_EXTERN PetscErrorCode PSIncreaseReferenceCount(PS);
/**
 * @brief Decreases the reference count of PS
 * @param [in] PS ps - The PS object
 */
PETSC_EXTERN PetscErrorCode PSDescreaseReferenceCount(PS);
/**
 * @brief Sets the type of application to be run on the PS object
 * @param [in] PS ps - The PS object
 * @param [in] PSApp psapp - The application (ACPF)
 */
PETSC_EXTERN PetscErrorCode PSSetApplication(PS,PSApp);
/**
 * @brief Sets up the PS object to be ready to be used by the application
 * @param [in] PS ps - The PS object
 * Notes:
 * PSSetUp 
 * i) creates the underlying DMNetwork object
 * ii) distributes the DMNetwork if used in parallel.
 * iii) creates PSBUS,PSBRANCH,PSGEN,PSLOAD objects
 */
PETSC_EXTERN PetscErrorCode PSSetUp(PS);
/**
 * @brief Returns a global vector of the appropriate size and distribution conforming to the distribution of the PS object.
 * @param [in] PS ps - The power system object ps
 * @param [out] Vec* vec - the global vector
 */
PETSC_EXTERN PetscErrorCode PSCreateGlobalVector(PS, Vec*);
/**
 * @brief Returns a distributed matrix of appropriate size that can be used as the Jacobian
 * @param [in] PS ps - The power system object ps
 * @param [out] Mat* mat - the matrix
 * Notes:
 * PSSetUp() must be called before calling this routine.
 */
PETSC_EXTERN PetscErrorCode PSCreateMatrix(PS,Mat*);

/**
 * @brief Returns true if the bus is a ghost bus
 * @param [in] PSBUS PSBUS - The PSBUS object
 * @param [out] PetscBool* ghostbus - TRUE if the bus is a ghost bus
 */
PETSC_EXTERN PetscErrorCode PSBUSIsGhosted(PSBUS,PetscBool*);
/**
 * @brief Gets the number of generators incident at the bus
 * @param [in] PSBUS PSBUS - The PSBUS object
 * @param [out] PetscInt* ngen - number of generators incident at the bus
 */
PETSC_EXTERN PetscErrorCode PSBUSGetNGen(PSBUS,PetscInt*);
/**
 * @brief Gets the generator incident at the bus
 * @param [in] PSBUS PSBUS - The PSBUS object
 * @param [in] PetscInt gen_num - Generator number (0, ..,ngen-1)
 * @param [out] PSGEN* gen - The PSGEN generator object
 */
PETSC_EXTERN PetscErrorCode PSBUSGetGen(PSBUS,PetscInt,PSGEN*);
/**
 * @brief Gets the load incident at the bus
 * @param [in] PSBUS PSBUS - The PSBUS object
 * @param [in] PetscInt load_num  - load number (0, ..,nload-1)
 * @param [out] PSLOAD* load - the load PSLOAD object
 */
PETSC_EXTERN PetscErrorCode PSBUSGetLoad(PSBUS,PetscInt,PSLOAD*);
/**
 * @brief Gets the starting location for the variables for this bus in the local vector
 * @param [in] PSBUS PSBUS - The PSBUS object
 * @param [out] PetscInt* loc - the starting location for the variables in the local vector
 */
PETSC_EXTERN PetscErrorCode PSBUSGetVariableLocation(PSBUS,PetscInt*);
/**
 * @brief Gets the starting location for the variables for this bus in the global vector
 * @param [in] PSBUS PSBUS - The PSBUS object
 * @param [out] PetscInt* locglob - the starting location for the variables in the global vector
 */
PETSC_EXTERN PetscErrorCode PSBUSGetVariableGlobalLocation(PSBUS,PetscInt*);
/**
 * @brief Gets the lines connected to this bus
 * @param [in] PSBUS PSBUS - The PSBUS object
 * @param [out] PetscInt* nsupplines - number of support lines
 * @param [out] const PSLINE** supplines - supporting lines
 * Notes:
 * supplines is a PSLINE pointer object with supplines[n] = nth connected line 
 */
PETSC_EXTERN PetscErrorCode PSBUSGetSupportingLines(PSBUS,PetscInt*,const PSLINE**);
/**
 * @brief Adds shunt conductance and susceptance at this bus
 * @param [in] PSBUS PSBUS - The PSBUS object
 * @param [in] PetscScalar Gs - Shunt conductance
 * @param [in] PetscScalar Bs - Shunt susceptance
 */
PETSC_EXTERN PetscErrorCode PSBUSAddShunt(PSBUS,PetscScalar,PetscScalar);

/**
 * @brief Gets the buses connected to the line
 * @param [in] PSLINE line - The line
 * @param [out] const PSBUS** connbuses - Connected buses
 * Notes:
 * connbuses is an PSBUS pointer object with connbuses[0] = From bus and
 * connbuses[1] = To bus
 */
PETSC_EXTERN PetscErrorCode PSLINEGetConnectedBuses(PSLINE,const PSBUS**);
/**
 * @brief Sets the status of the line
 * @param [in] PSLINE line - The line
 * @param [in] PetscInt status - (0 or 1) the status of the line
 */
PETSC_EXTERN PetscErrorCode PSLINESetStatus(PSLINE,PetscInt);
/**
 * @brief Gets the starting location for the variables for this line in the local vector
 * @param [in] PSLINE line - The line
 * @param [out] PetscInt* loc - the starting location for the variables in the local vector
 */
PETSC_EXTERN PetscErrorCode PSLINEGetVariableLocation(PSLINE,PetscInt*);
/**
 * @brief Gets the starting location for the variables for this line in the global vector
 * @param [in] PSLINE line - The line
 * @param [out] PetscInt* locglob - the starting location for the variables in the global vector
 */
PETSC_EXTERN PetscErrorCode PSLINEGetVariableGlobalLocation(PSLINE,PetscInt*);

/**
 * @brief Gets the number of local and global generators in this system
 * @param [in] PS ps - The PS object
 * @param [out] PetscInt* ngen - Number of local generators
 * @param [out] PetscInt* Ngen - Number of global generators
 * Notes:
 * PSSetUp() must be called before a call to PSGetNumGenerators
 */
PETSC_EXTERN PetscErrorCode PSGetNumGenerators(PS,PetscInt*,PetscInt*);

/**
 * @brief Gets the number of global buses in the system
 * @param [in] PS ps - The PS object
 * @param [out] PetscInt *Nbus - Number of global buses
 * Notes:
 * PSSetUp() must be called before a call to PSGetNumGlobalBuses
 */
PETSC_EXTERN PetscErrorCode PSGetNumGlobalBuses(PS,PetscInt*);

PETSC_EXTERN PetscErrorCode PSGENSetStatus(PSGEN,PetscInt);

PETSC_EXTERN PetscErrorCode PSLOADSetStatus(PSLOAD,PetscInt);
/**
 * @brief Sets the generator status and dispatch
 * @param [in] PS ps - the ps object
 * @param [in] PetscInt busnum - the bus number 
 * @param [in] PetscInt gennum - generator number
 * @param [in] PetscInt status - the generator status (0 for OFF, 1 for ON)
 * @param [in] PetscScalar pg - active power dispatch in MW
 * @param [in] PetscScalar qg - reactive power dispatch in MVAr
 * Notes: Must be called before PSSetUp() is called
 */
PETSC_EXTERN PetscErrorCode PSSetGenDispatchandStatus(PS,PetscInt,PetscInt,PetscInt,PetscScalar,PetscScalar);

/**
 * @brief Checks for active ref. bus and sets one if not available
 * @param [in] PS ps - The PS object
 * This routine checks if there is an active ref. 
 * bus (declared in the data file and has active generators).
 * If it is not defined, then the first PV bus is used.
 */
PETSC_EXTERN PetscErrorCode PSCheckandSetRefBus(PS);
#endif

