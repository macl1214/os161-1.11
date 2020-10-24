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

/*
 * Number of vehicles created.
 */

#define NVEHICLES 20


// static struct lock A;
// static struct lock B;
// static struct lock C;

static struct lock *AB;
static struct lock *BC;
static struct lock *CA;
static struct lock *priority;
static struct lock *left;

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
		//kprintf("Approaching the intersection from A: %5s, Vehicle Number: %02lu, Destination direction: C\n", type, vehiclenumber);
			
		/** Acquire lock 1*/
		lock_acquire(AB);
		kprintf("Vehicle #%02lu - %5s - from A: entering the intersection CA. Destination direction: C\n", vehiclenumber, type);
		//kprintf("Entering intersection AB: %5s, Vehicle Number: %02lu,  Destination direction: C\n", type, vehiclenumber);
			
		/** Acquire lock 2 and release lock 1*/
		lock_acquire(BC);
		lock_release(AB);
		kprintf("Vehicle #%02lu - %5s - from A: leaving AB and entering BC. Destination direction: C\n", vehiclenumber, type);
		//kprintf("Leaving intersection AB and entering intersection BC: %5s, Vehicle Number: %02lu, Destination direction: C\n", type, vehiclenumber);

		/** Lock release 2 */
		lock_release(BC);
		kprintf("Vehicle #%02lu - %5s - from A: exiting the intersection and arriving at C\n", vehiclenumber, type);
		//kprintf("Leaving intersection BC and exiting through direction C: %5s, Vehicle Number: %02lu\n", type, vehiclenumber);	
	}

	else if (vehicledirection == 1) 		// B
	{ 
		kprintf("Vehicle #%02lu - %5s - from B: approaching the intersection. Destination direction: A\n", vehiclenumber, type);
		//kprintf("Approaching the intersection from B: %5s, Vehicle Number: %02lu, Destination direction: A\n", type, vehiclenumber);
			
		/** Acquire lock 1*/
		lock_acquire(BC);
		kprintf("Vehicle #%02lu - %5s - from B: entering the intersection BC. Destination direction: A\n", vehiclenumber, type);
		//kprintf("Entering intersection BC: %5s, Vehicle Number: %02lu,  Destination direction: A\n", type, vehiclenumber);
			
		/** Acquire lock 2 and release lock 1*/
		lock_acquire(CA);
		lock_release(BC);
		kprintf("Vehicle #%02lu - %5s - from B: leaving BC and entering CA. Destination direction: A\n", vehiclenumber, type);
		//kprintf("Leaving intersection BC and entering intersection CA: %5s, Vehicle Number: %02lu, Destination direction: A\n", type, vehiclenumber);

		/** Lock release 2 */
		lock_release(CA);
		kprintf("Vehicle #%02lu - %5s - from B: leaving intersection CA and arriving at A\n", vehiclenumber, type);
		//kprintf("Leaving intersection CA and exiting through direction A: %5s, Vehicle Number: %02lu\n", type, vehiclenumber);	
	}

	else 															// C
	{
		kprintf("Vehicle #%02lu - %5s - from C: approaching the intersection. Destination direction: B\n", vehiclenumber, type);
		//kprintf("Approaching the intersection from C: %5s, Vehicle Number: %02lu, Destination direction: B\n", type, vehiclenumber);
			
		/** Acquire lock 1*/
		lock_acquire(CA);
		kprintf("Vehicle #%02lu - %5s - from C: entering the intersection CA. Destination direction: B\n", vehiclenumber, type);
		//kprintf("Entering intersection CA: %5s, Vehicle Number: %02lu,  Destination direction: B\n", type, vehiclenumber);
			
		/** Acquire lock 2 and release lock 1*/
		lock_acquire(AB);
		lock_release(CA);
		kprintf("Vehicle #%02lu - %5s - from C: leaving CA and entering AB. Destination direction: B\n", vehiclenumber, type);
		//kprintf("Leaving intersection CA and entering intersection AB: %5s, Vehicle Number: %02lu, Destination direction: A\n", type, vehiclenumber);

		/** Lock release 2 */
		lock_release(AB);
		kprintf("Vehicle #%02lu - %5s - from C: leaving intersection AB and arriving at B\n", vehiclenumber, type);
		//kprintf("Leaving intersection AB and exiting through direction B: %5s, Vehicle Number: %02lu\n", type, vehiclenumber);	
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
	/*
	 * Avoid unused variable warnings.
	 */

//	(void) vehicledirection;
//	(void) vehiclenumber;
//	(void) vehicletype;

	const char *type = getVehicleType(vehicletype);

	if (vehicledirection == 0) 							// A
	{	
		kprintf("Vehicle #%02lu - %5s - from A: approaching the intersection. Destination direction: B\n", vehiclenumber, type);
		//kprintf("Approaching the intersection from A: %5s, Vehicle Number: %02lu, Destination direction: B\n", type, vehiclenumber);
			
		/** Acquire lock */
		lock_acquire(AB);
		kprintf("Vehicle #%02lu - %5s - from A: entering the intersection AB. Destination direction: B\n", vehiclenumber, type);
		//kprintf("Entering intersection AB: %5s, Vehicle Number: %02lu,  Destination direction: B\n", type, vehiclenumber);
			
		/** Release lock */
		lock_release(AB);
		kprintf("Vehicle #%02lu - %5s - from A: leaving intersection AB and arriving at B\n", vehiclenumber, type);
		//kprintf("Leaving intersection AB and exiting through direction B: %5s, Vehicle Number: %02lu\n", type, vehiclenumber);
	}
	
	else if (vehicledirection == 1)					// B
	{
		kprintf("Vehicle #%02lu - %5s - from B: approaching the intersection. Destination direction: C\n", vehiclenumber, type);
		//kprintf("Approaching the intersection from B: %5s, Vehicle Number: %02lu, Destination direction: C\n", type, vehiclenumber);
			
		/** Acquire lock */
		lock_acquire(BC);
		kprintf("Vehicle #%02lu - %5s - from B: entering the intersection BC. Destination direction: C\n", vehiclenumber, type);
		//kprintf("Entering intersection BC: %5s, Vehicle Number: %02lu, Destination direction: C\n", type, vehiclenumber);
			
		/** Release lock */
		lock_release(BC);
		kprintf("Vehicle #%02lu - %5s - from B: leaving intersection BC and arriving at C\n", vehiclenumber, type);
		//kprintf("Leaving intersection BC and exiting through direction C: %5s, Vehicle Number: %02lu\n", type, vehiclenumber);
	}
	
	else																		// C 
	{

		kprintf("Vehicle #%02lu - %5s - from C: approaching the intersection. Destination direction: A\n", vehiclenumber, type);
		//kprintf("Approaching the intersection from C: %5s, Vehicle Number: %02lu, Destination direction: A\n", type, vehiclenumber);
			
		/** Acquire lock */
		lock_acquire(CA);
		kprintf("Vehicle #%02lu - %5s - from C: entering the intersection CA. Destination direction: A\n", vehiclenumber, type);
		//kprintf("Entering intersection CA: %5s, Vehicle Number: %02lu, Destination direction: A\n", type, vehiclenumber);
			
		/** Release lock */
		lock_release(CA);
		kprintf("Vehicle #%02lu - %5s - from C: leaving intersection CA and arriving at A\n", vehiclenumber, type);
		//kprintf("Leaving intersection CA and exiting through direction A: %5s, Vehicle Number: %02lu\n", type, vehiclenumber);

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
//	(void) vehiclenumber;
//	(void) turnleft;
//	(void) turnright;

	/*
	 * vehicledirection is set randomly.
	 */

	vehicledirection = random() % 3;
//	turndirection = random() % 2;
	turndirection = 0;
	vehicletype = random() % 2;

			

	if (turndirection == 0) {
		turnright(vehicledirection, vehiclenumber, vehicletype);
	}
	else {
		turnleft(vehicledirection, vehiclenumber, vehicletype);
	}

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
 	 * Create all locks
 	 */

	AB = lock_create("AB");
	BC = lock_create("BC");
	CA = lock_create("AC");
  left = lock_create("left");
	priority = lock_create("priority");

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

		kprintf("\t\t*****\n\tCar %02d is done!\n\t\t*****\n", index);		

		/*
		 * panic() on error.
		 */

		if (error) {

			panic("approachintersection: thread_fork failed: %5s\n",
					strerror(error)
				 );
		}
	}

	lock_destroy(AB);
	lock_destroy(BC);
	lock_destroy(CA);
	lock_destroy(left);
	lock_destroy(priority);

	return 0;
}
