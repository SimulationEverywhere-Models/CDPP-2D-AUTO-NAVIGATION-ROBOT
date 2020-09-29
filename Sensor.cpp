 #include "Sensor.h"
 #include "message.h"       // InternalMessage ....

 Sensor::Sensor( const std::string &name ) : Atomic( name )
 , In(addInputPort( "In" ))
 , Out(addOutputPort( "Out" ))
 , ProcessTime (00,00,00,500)
 {
 }

 Model &Sensor::initFunction()
  {
	cout << "Sensor initFunction()" << endl;
	for(int i = 0; i <= 8; i++){
		for(int j = 0; j <= 8; j++){
			grid[i][j] = 0;
		}
	}
	gridCount = 0;
	spwanCount = 1;
    state = idle;
    passivate();
	return *this ;
  }

 /*********************************************************/
 Model &Sensor::externalFunction( const ExternalMessage &msg )
  {
	cout << "Sensor externalFunction() at " << msg.time() << endl;
	if (msg.port() == In ){
		robotLocation = msg.value();
		cout << "		I received Robot Location [" << robotLocation/10 << ","<< robotLocation%10 <<"]   at " << msg.time() << endl;
		state = sendVariation;
		holdIn(Atomic::active, ProcessTime);
	}
	return *this;
  }

 /*********************************************************/
 Model &Sensor::internalFunction( const InternalMessage & )
 {
	cout << "Sensor internalFunction()" << endl;
	if (state == 0 ) cout << "		The input state is idle" << endl;
	if (state == 1 ) cout << "		The input state is sendVariation" << endl;

	switch (state){
				    case idle:
				    				passivate();
									break;
				    case sendVariation:
									state = idle;
									passivate();
									break;
        		  }

	if (state == 0 ) cout << "		The input state is idle" << endl;
	if (state == 1 ) cout << "		The input state is sendVariation" << endl;
    return *this;
 }

 /*********************************************************/
 Model &Sensor::outputFunction( const InternalMessage &msg )
 {
	 cout << "Sensor outputFunction() at " << msg.time() << endl;
	 if (state == sendVariation){
		 //Calculate variation here.
		 spwanNum = rand() % (9 * 9 - gridCount - 1) + 1;
		 for(int i = 0; i <= 8; i++){
			 for(int j = 0; j <= 8; j++){
				 if( grid[i][j] == 0 && !(i == robotLocation/10 && j == robotLocation%10) ) {
					 //spwanCount++;
					 if(spwanNum == spwanCount++) {
						 grid[i][j] = 1;
						 variation = 10 * i + j;
						 gridCount++;
					 }
				 }
			 }
		 }
		 spwanCount = 1;
		 sendOutput( msg.time(), Out, variation) ;
		 cout << "		I sent variation [" << int(variation)/10 << ","<< int(variation)%10 <<"]  for grids,  at " << msg.time() << endl;
	 }
	return *this ;
 }

 /*********************************************************/
 Sensor::~Sensor()
 {
 }

