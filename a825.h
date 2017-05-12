#ifndef A825_H
#define A825_H

// ARINC825 Logical Communication Channels definitions

#define EEC 0 // Exception Event Channel
#define NOC 2 // Normal Operation Channel
#define DMC 3 // Direct Message Channel
#define NSC 4 // Node Service Channel
#define UDC 5 // User-defined Channel
#define TMC 6 // Test and Maintenance Channel
#define FMC 7 // CAN Base Frame Migration Channel

// ARINC825 Redundancy Channels

#define RCI_A   0 // Redundancy Channel A
#define RCI_B   1 // Redundancy Channel B
#define RCI_C   2 // Redundancy Channel C
#define RCI_D   3 // Redundancy Channel D

// ARINC825 Function Codes

#define MULTICAST_FID           0
#define FLIGHT_STATE_FID        4
#define FLIGHT_CONTROLS_FID     10
#define ENGINE_CONTROLS_FID     11
#define ENGINE_INDICAT_FID      12
#define ELECTR_POWER_FID        13
#define AUTO_FLIGHT_FID         14
#define IMA_FID                 15
#define FUEL_FID                18
#define WINGS_FID               21
#define OIL_FID                 31
#define LAND_GEAR_FID           34
// TO BE CONTINUED



#endif // A825_H
