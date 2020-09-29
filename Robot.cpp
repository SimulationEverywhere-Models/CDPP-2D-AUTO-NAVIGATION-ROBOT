 #include "Robot.h"
 #include "message.h"       // InternalMessage ....

 Robot::Robot( const std::string &name ) : Atomic( name )
 , In(addInputPort( "In" ))
 , Out(addOutputPort( "Out" ))
 , ProcessTime (00,00,00,00)
 //, ProcessTime2 (00,00,00,10)
 {
 }

 Model &Robot::initFunction()
  {
	cout << "Robot initFunction()" << endl;
	//packetNumber = 0;
	state = sendLocation;
	for(int i = 0; i <= 8; i++){
		for(int j = 0; j <= 8; j++){
			grid[i][j] = 0;
		}
	}
	firstTime = 1;
	robotLocation = 56;
	holdIn(Atomic::active, 0);
	return *this ;
  }

 /*********************************************************/
 Model &Robot::externalFunction( const ExternalMessage &msg )
  {
	cout << "Robot externalFunction() at " << msg.time() << endl;
	if (msg.port() == In ){
		variation = msg.value();
		cout << "		I received variation [" << int(variation)/10 << ","<< int(variation)%10 <<"]  for grids,  at " << msg.time() << endl;
		grid[int(variation)/10][int(variation)%10] = 1;
		state = sendLocation;
		holdIn(Atomic::active, ProcessTime);
	}
	return *this;
  }

 /*********************************************************/
 Model &Robot::internalFunction( const InternalMessage & )
 {
	cout << "Robot internalFunction()" << endl;
	if (state == 0 ) cout << "		The input state is idle" << endl;
	if (state == 1 ) cout << "		The input state is sendLocation" << endl;

	switch (state){

				    case idle:
				    				passivate();
				    				break;

				    case sendLocation:
				    				state = idle;
				    				passivate();
				    				break;
        		  }

	if (state == 0 ) cout << "		The Output state is idle" << endl;
	if (state == 1 ) cout << "		The Output state is sendLocation" << endl;
    return *this;
 }

 /*********************************************************/
 Model &Robot::outputFunction( const InternalMessage &msg )
 {
	 cout << "Robot outputFunction() at " << msg.time() << endl;
	 if (state == sendLocation){
		 //Calculate robotLocation here.
		 if(firstTime == 1) {
			 firstTime = 0;
		 }
		 else {
			 //new location
			 if(		grid[(robotLocation/10 + 1)%9][robotLocation%10] == 1
					 && grid[(robotLocation/10 + 8)%9][robotLocation%10] == 1
					 && grid[robotLocation/10 * 10][(robotLocation%10 + 1)%9] == 1
					 && grid[robotLocation/10 * 10][(robotLocation%10 + 8)%9] == 1) {

				 cout << "		Blocked    " << endl;
			 }
			 else {
				 do{
					 attempt = rand() % 4;
					 switch(attempt) {
										 case 0: nextMove = (robotLocation/10 + 1)%9 * 10 + robotLocation%10;
										 //cout << "		move right    " << endl;
										 break;
										 case 1: nextMove = (robotLocation/10 + 8)%9 * 10 + robotLocation%10;
										 //cout << "		move left    " << endl;
										 break;
										 case 2: nextMove = robotLocation/10 * 10 + (robotLocation%10 + 1)%9;
										 //cout << "		move up    " << endl;
										 break;
										 case 3: nextMove = robotLocation/10 * 10 + (robotLocation%10 + 8)%9;
										 //cout << "		move down    " << endl;
										 break;
					 	 	 	 	 }
				 	 }while(grid[nextMove/10][nextMove%10] == 1);

				 robotLocation = nextMove;
			 }
		 }
		 sendOutput( msg.time(), Out, robotLocation) ;
		 cout << "		I sent robot location [" << robotLocation/10 << ","<< robotLocation%10 <<"]   at " << msg.time() << endl;

		 /************************/
		 cout << "		Current Grids:		" << endl;
		 for(int j = 8; j >= 0; j--){
			 for(int i = 0; i <= 8; i++){
				 if(i * 10 + j == robotLocation) {
					 cout << "R";
				 }
				 else {
					 cout << grid[i][j] << " ";
				 }
			 }
			 cout << "" << endl;
		 }
		 //*/
		 /************************/
	 }
	return *this ;
 }

 /*********************************************************/
 Robot::~Robot()
 {
 }

