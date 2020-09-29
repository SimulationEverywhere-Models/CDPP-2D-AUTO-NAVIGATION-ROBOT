 #ifndef __Sensor_H
 #define __Sensor_H

 #include "atomic.h"      // class Atomic
 #include "string.h"	  // class String

 class Sensor : public Atomic
 {
   public:
	 Sensor( const std::string &name = "Sensor" );  //Default constructor
	       virtual std::string className() const {  return "Sensor" ;}
	       ~Sensor();

   protected:
	          Model &initFunction();
	          Model &externalFunction( const ExternalMessage & );
	          Model &internalFunction( const InternalMessage & );
	          Model &outputFunction( const InternalMessage & );

   private:
	        const Port &In;
	        Port &Out;
	        Time ProcessTime;
	        int grid[9][9];
	        int robotLocation;
	    	int gridCount;
	    	int spwanNum;
	    	int spwanCount;
	        double variation;
         	enum State{
			            idle,
			            sendVariation,
		              };
		    State state;
 };

#endif   //__Sensor_H
