 #include <modeladm.h>
 #include <mainsimu.h>

 #include "Sensor.h"    //New libraries Should be copied.
 #include "Robot.h"


 void MainSimulator::registerNewAtomics()
 {
   SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Sensor>() , "Sensor" ) ;
   SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Robot>() , "Robot" ) ;
 }
