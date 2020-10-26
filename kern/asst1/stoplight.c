/* 
 * stoplight.c
 *
 * 31-1-2003 : GWA : Stub functions created for CS161 Asst1.
 *
 * NB: You can use any synchronization primitives available to solve
 * the stoplight problem in this file.
 */


/*
 * 
 * Includes
 *
 */

#include <types.h>
#include <lib.h>
#include <test.h>
#include <thread.h>
#include <synch.h>

/*
 *
 * Constants
 *
 */



struct Route {
	int cars; //= 0; throws error, cant have predefined vars in structs
  struct lock *high_p; //threw error until static keywords removed
  struct lock *low_p;
};

/*
 * Number of vehicles created.
 */

#define NVEHICLES 20

/*
 * Variable declarations
 */

struct Route *A;
struct Route *B;
struct Route *C;
static struct lock *AB;
static struct lock *BC;
static struct lock *CA;
static struct lock *getLocks;
static int nvrem;	// Number of vehicles remaining

/*
 *
 * Function Definitions
 *
 */


/*
 * getVehicleType()
 *
 * Arguments:
 * 			int vehicletype: either a 0 or a 1
 *
 * Returns:
 * 			"Car" if 0
 * 			"Truck" if 1
 *
 * Notes:
 * 			Purpose: To print out the type of car as word, rather than a number
 */
const char* getVehicleType(int vehicletype) {
	if (vehicletype == 1) {
		return "Car";
	}
	else {
		return "Truck";
	}
}


/*
 * turnleft()
 *
 * Arguments:
 *      unsigned long vehicledirection: the direction from which the vehicle
 *              approaches the intersection.
 *      unsigned long vehiclenumber: the vehicle id number for printing purposes.
 *
 * Returns:
 *      nothing.
 *
 * Notes:
 *      This function should implement making a left turn through the 
 *      intersection from any direction.
 *      Write and comment this function.
 */



static
void
turnleft(unsigned long vehicledirection,
		unsigned long vehiclenumber,
		unsigned long vehicletype)
{ 
	const char *type = getVehicleType(vehicletype);

	if (vehicledirection == 0) 					// A
	{ 	
		kprintf("Vehicle #%02lu - %5s - from A: approaching the intersection. Destination direction: C\n", vehiclenumber, type);
		
		if(vehicletype == 0){
			lock_acquire(A->low_p);
			while(A->cars > 0){
				thread_yield();
			}
		}
	
		/** Acquire locks*/
		lock_acquire(getLocks);
		lock_acquire(AB);
		lock_acquire(BC);
		kprintf("Vehicle #%02lu - %5s - from A: entering the intersection AB. Destination direction: C\n", vehiclenumber, type);
		lock_release(getLocks);

		if(vehicletype == 1){
			A->cars--;
		}

		/** Release locks: AB -> BC*/
		kprintf("Vehicle #%02lu - %5s - from A: leaving AB and entering BC. Destination direction: C\n", vehiclenumber, type);
		lock_release(AB);
//		kprintf("Vehicle #%02lu - %5s - from A: leaving AB and entering BC. Destination direction: C\n", vehiclenumber, type);


		/** Lock release 2 */
		kprintf("Vehicle #%02lu - %5s - from A: exiting the intersection and arriving at C\n", vehiclenumber, type);
		lock_release(BC);
//		kprintf("Vehicle #%02lu - %5s - from A: exiting the intersection and arriving at C\n", vehiclenumber, type);	

		if(vehicletype == 0){
			lock_release(A->low_p);
		}	
	}

	else if (vehicledirection == 1) 		// B
	{ 
		kprintf("Vehicle #%02lu - %5s - from B: approaching the intersection. Destination direction: A\n", vehiclenumber, type);

		if(vehicletype == 0){
			lock_acquire(B->low_p);
			while(B->cars > 0){
				thread_yield();
			}
		}
				
		/** Acquire locks*/
		lock_acquire(getLocks);
		lock_acquire(BC);
		lock_acquire(CA);
		kprintf("Vehicle #%02lu - %5s - from B: entering the intersection BC. Destination direction: A\n", vehiclenumber, type);
		lock_release(getLocks);

		if(vehicletype == 1){
			B->cars--;
		}
			
		/** Release locks: BC -> CA*/
		kprintf("Vehicle #%02lu - %5s - from B: leaving BC and entering CA. Destination direction: A\n", vehiclenumber, type);
		lock_release(BC);
//		kprintf("Vehicle #%02lu - %5s - from B: leaving BC and entering CA. Destination direction: A\n", vehiclenumber, type);
		
		/** Lock release 2 */
		kprintf("Vehicle #%02lu - %5s - from B: leaving intersection CA and arriving at A\n", vehiclenumber, type);
		lock_release(CA);
//		kprintf("Vehicle #%02lu - %5s - from B: leaving intersection CA and arriving at A\n", vehiclenumber, type);

		if(vehicletype == 0){
			lock_release(B->low_p);
		}
	}

	else 															// C
	{
		kprintf("Vehicle #%02lu - %5s - from C: approaching the intersection. Destination direction: B\n", vehiclenumber, type);

		if(vehicletype == 0){
			lock_acquire(C->low_p);
			while(C->cars > 0){
				thread_yield();
			}
		}
			
		/** Acquire locks*/
		lock_acquire(getLocks);
		lock_acquire(CA);
		lock_acquire(AB);
		kprintf("Vehicle #%02lu - %5s - from C: entering the intersection CA. Destination direction: B\n", vehiclenumber, type);
		lock_release(getLocks);

		if(vehicletype == 1){
			C->cars--;
		}

		/** Release locks: CA -> AB*/
		kprintf("Vehicle #%02lu - %5s - from C: leaving CA and entering AB. Destination direction: B\n", vehiclenumber, type);
		lock_release(CA);
//		kprintf("Vehicle #%02lu - %5s - from C: leaving CA and entering AB. Destination direction: B\n", vehiclenumber, type);

		/** Lock release 2 */
		kprintf("Vehicle #%02lu - %5s - from C: leaving intersection AB and arriving at B\n", vehiclenumber, type);
		lock_release(AB);
//		kprintf("Vehicle #%02lu - %5s - from C: leaving intersection AB and arriving at B\n", vehiclenumber, type);	

		if(vehicletype == 0){
			lock_release(C->low_p);
		}	
	}

}


/*
 * turnright()
 *
 * Arguments:
 *      unsigned long vehicledirection: the direction from which the vehicle
 *              approaches the intersection.
 *      unsigned long vehiclenumber: the vehicle id number for printing purposes.
 *
 * Returns:
 *      nothing.
 *
 * Notes:
 *      This function should implement making a right turn through the 
 *      intersection from any direction.
 *      Write and comment this function.
 */

static
void
turnright(unsigned long vehicledirection,
		unsigned long vehiclenumber,
		unsigned long vehicletype)
{
	const char *type = getVehicleType(vehicletype);

	if (vehicledirection == 0) 							// A
	{	
		kprintf("Vehicle #%02lu - %5s - from A: approaching the intersection. Destination direction: B\n", vehiclenumber, type);

		//PRIORITY ALGORITHM
		if(vehicletype == 0){
			//lock_acquire(getLocks);
			lock_acquire(A->low_p);
			while(A->cars > 0){
				thread_yield();
				/*int spl = splhigh();
				thread_sleep(A->low_p);
				splx(spl);*/
			}
		}
			
		/** Acquire lock */
		lock_acquire(AB);
		kprintf("Vehicle #%02lu - %5s - from A: entering the intersection AB. Destination direction: B\n", vehiclenumber, type);
		
		if(vehicletype == 1){
			A->cars--;
		}
	
		/** Release lock */
		kprintf("Vehicle #%02lu - %5s - from A: leaving intersection AB and arriving at B\n", vehiclenumber, type);
		lock_release(AB);
//		kprintf("Vehicle #%02lu - %5s - from A: leaving intersection AB and arriving at B\n", vehiclenumber, type);
		
		if(vehicletype == 0){
			lock_release(A->low_p);
		}
	}
	
	else if (vehicledirection == 1)					// B
	{
		kprintf("Vehicle #%02lu - %5s - from B: approaching the intersection. Destination direction: C\n", vehiclenumber, type);

		if(vehicletype == 0){
			lock_acquire(B->low_p);
			while(B->cars > 0){
				thread_yield();
			}
		}
		
		/** Acquire lock */
		lock_acquire(BC);
		kprintf("Vehicle #%02lu - %5s - from B: entering the intersection BC. Destination direction: C\n", vehiclenumber, type);

		if(vehicletype == 1){
			B->cars--;
		}
			
		/** Release lock */
		kprintf("Vehicle #%02lu - %5s - from B: leaving intersection BC and arriving at C\n", vehiclenumber, type);
		lock_release(BC);
//		kprintf("Vehicle #%02lu - %5s - from B: leaving intersection BC and arriving at C\n", vehiclenumber, type);
	
		if(vehicletype == 0){
			lock_release(B->low_p);
		}		
	}
	
	else																		// C 
	{

		kprintf("Vehicle #%02lu - %5s - from C: approaching the intersection. Destination direction: A\n", vehiclenumber, type);

		if(vehicletype == 0){
			lock_acquire(C->low_p);
			while(C->cars > 0){
				thread_yield();
			}
		}

			
		/** Acquire lock */
		lock_acquire(CA);
		kprintf("Vehicle #%02lu - %5s - from C: entering the intersection CA. Destination direction: A\n", vehiclenumber, type);

		if(vehicletype == 1){
			C->cars--;
		}
			
		/** Release lock */
		kprintf("Vehicle #%02lu - %5s - from C: leaving intersection CA and arriving at A\n", vehiclenumber, type);
		lock_release(CA);
//		kprintf("Vehicle #%02lu - %5s - from C: leaving intersection CA and arriving at A\n", vehiclenumber, type);

		if(vehicletype == 0){
			lock_release(C->low_p);
		}
	}
	
}


/*
 * approachintersection()
 *
 * Arguments: 
 *      void * unusedpointer: currently unused.
 *      unsigned long vehiclenumber: holds vehicle id number.
 *
 * Returns:
 *      nothing.
 *
 * Notes:
 *      Change this function as necessary to implement your solution. These
 *      threads are created by createvehicles().  Each one must choose a direction
 *      randomly: approach the intersection, choose a turn randomly, and then
 *      complete that turn.  The code to choose a direction randomly is
 *      provided, the rest is left to you to implement.  Making a turn
 *      or going straight should be done by calling one of the functions
 *      above.
 *
 * Vehicle Direction:
 * 			0: A
 * 			1: B
 * 			2: C
 *
 * Turn direction:
 * 			0: Right
 * 			1: Left
 *
 * Vehicle type:
 * 			0: Truck
 * 			1: Car
 */

static
void
approachintersection(void * unusedpointer,
		unsigned long vehiclenumber)
{
	int vehicledirection, turndirection, vehicletype;

	/*
	 * Avoid unused variable and function warnings.
	 */

	(void) unusedpointer;

	/*
	 * vehicledirection is set randomly.
	 */

	vehicledirection = random() % 3;
//	vehicledirection = 0;
	turndirection = random() % 2;
//	turndirection = 0;
	vehicletype = random() % 2;

	if(vehicledirection == 0){
		if(vehicletype == 1){
			lock_acquire(getLocks);
			A->cars++;
			lock_release(getLocks);
		}
	}else if(vehicledirection == 1){
		if(vehicletype == 1){
			lock_acquire(getLocks);
			B->cars++;
			lock_release(getLocks);
		}
	}else if(vehicledirection == 2){
		if(vehicletype == 1){
			lock_acquire(getLocks);
			C->cars++;
			lock_release(getLocks);
		}
	}			

	if (turndirection == 0) {
		turnright(vehicledirection, vehiclenumber, vehicletype);
	}
	else {
		turnleft(vehicledirection, vehiclenumber, vehicletype);
    //turnleft(vehicledirection, vehiclenumber, vehicletype);
	}

	/** Keep track of the number of vehicles left to go through the intersection */
	nvrem -= 1;	 
}


/*
 * createvehicles()
 *
 * Arguments:
 *      int nargs: unused.
 *      char ** args: unused.
 *
 * Returns:
 *      0 on success.
 *
 * Notes:
 *      Driver code to start up the approachintersection() threads.  You are
 *      free to modiy this code as necessary for your solution.
 */

int
createvehicles(int nargs,
		char ** args)
{
	int index, error;

	/*
	 * Avoid unused variable warnings.
	 */

	(void) nargs;
	(void) args;
	
  /*
   * Initialize structs
   */
  
	A = kmalloc(sizeof(struct Route));
	B = kmalloc(sizeof(struct Route));
	C = kmalloc(sizeof(struct Route));
  
	/*
 	 * Create all locks
 	 */

	AB = lock_create("AB");
	BC = lock_create("BC");
	CA = lock_create("AC");
  
  A->cars = 0;
	A->high_p = lock_create("high priority");
	A->low_p = lock_create("low priority");
  
  B->cars = 0;
	B->high_p = lock_create("high priority");
	B->low_p = lock_create("low priority");
  
	C->cars = 0;
	C->high_p = lock_create("high priority");
	C->low_p = lock_create("low priority");
	getLocks = lock_create("getLocks");
	nvrem = NVEHICLES;	// Initially 20 vehicles that need to go through the intersection

	/*
	 * Start NVEHICLES approachintersection() threads.
	 */

	for (index = 0; index < NVEHICLES; index++) {

		error = thread_fork("approachintersection thread",
				NULL,
				index,
				approachintersection,
				NULL
				);

		/*
		 * panic() on error.
		 */

		if (error) {

			panic("approachintersection: thread_fork failed: %5s\n",
					strerror(error)
				 );
		}
	}

	/*
	 * Only begin to destroy the locks once all of the vehicles 
	 * have turned and have exited into their destination.
	 *
	 * Loop is used to make sure this happens. 
	 *
	 */

	while (nvrem != 0);	

	lock_destroy(AB);
	lock_destroy(BC);
	lock_destroy(CA);
	lock_destroy(getLocks);
	lock_destroy(A->high_p);
	lock_destroy(A->low_p);
	lock_destroy(B->high_p);
	lock_destroy(B->low_p);
	lock_destroy(C->high_p);
	lock_destroy(C->low_p);

	return 0;
}
