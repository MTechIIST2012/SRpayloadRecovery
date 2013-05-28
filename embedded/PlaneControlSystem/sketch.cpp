#include <Arduino.h>
#include  "PlaneController.h"
#include  "ControllerPipe.h"
#include "Plane_E.h"
#include "PathPlanner_E.h"
#include "Communication_E.h"
#include "DataPackets_E.h"

void setup()
{
          PathPlanner_E* pathplanner = new PathPlanner_E();
          ControllerPipe*     controllerpipe  =  new  ControllerPipe();

          // Todo: needs to be modified with the actual instrument set
          Plane_E* plane = new Plane_E(PlaneMeterSet_E(),
                                                                    PlaneControlledObjSet_E(),
                                                                    PlaneSensorSet_E(),
                                                                    pathplanner,
                                                                    controllerpipe);

          // communications
          IPacketFactory_E*  packetFactory = new PacketFactory_E();
          Communication_E* comm = new Communication_E(packetFactory,controllerpipe,100);

          PlaneController::generateInstance(plane,controllerpipe,comm);
	IPlaneController*  planecontroller =  PlaneController::instance();

	planecontroller->setup();
}

void loop()
{
	PlaneController::instance()->loop();
}
