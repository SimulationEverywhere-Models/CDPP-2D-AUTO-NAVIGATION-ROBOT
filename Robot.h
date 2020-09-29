 #ifndef __Robot_H
 #define __Robot_H

 #include "atomic.h"   // class Atomic
 #include "string.h"	  // class String

 class Robot : public Atomic
 {
   public:
	       Robot ( const std::string &name = "Robot" );  //Default constructor
	       virtual std::string className() const {  return "Robot" ;}
	       ~Robot();

   protected:
	          Model &initFunction();
	          Model &externalFunction( const ExternalMessage & );
	          Model &internalFunction( const InternalMessage & );
	          Model &outputFunction( const InternalMessage & );

   private:
	        const Port &In;
	        Port &Out;
	        Time ProcessTime;
         	double variation;
         	int attempt;
         	int nextMove;
         	int grid[9][9];
         	int robotLocation;
         	int firstTime;
         	enum State{
			            idle,
			            sendLocation,
		              };
		    State state;
 };

#endif   //__Robot_H
