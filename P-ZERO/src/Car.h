
// Car.h

#include <pebble.h>

typedef struct {

	int type;
	RotBitmapLayer *layer;

	int dir;
	GPoint pos;
	GPoint speed;

} Car;

// Initialisers
Car* car_create_with_type(int type);

// Methods
void car_logic(Car *car);
void car_change_dir(Car *car, int inc)

// Getters/Setters
Layer* car_get_layer(Car *car);
void car_set_position(Car *car, int x, int y);