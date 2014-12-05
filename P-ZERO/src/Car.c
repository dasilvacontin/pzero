
// Car.c

#include "Car.h"
#include "Constants.h"

Car* car_create_with_type(int type) {

	Car car;
	car.type = type;
	car.layer = rot_bitmap_layer_create(mapSprites[type]);
	return &car;

}

void car_logic(Car *car) {

	GPoint &speed = car->speed;

	// Speed increase based on car's direction

	speed.x += DIRXVAL[car->dir];
	speed.y += DIRYVAL[car->dir];

	// Speed limit checks

	if (speed.x < -CAR_MAX_SPEED) speed.x = -CAR_MAX_SPEED;
	else if (CAR_MAX_SPEED < speed.x) speed.x = CAR_MAX_SPEED;

	if (speed.y < -CAR_MAX_SPEED) speed.y = -CAR_MAX_SPEED;
	else if (CAR_MAX_SPEED < speed.y) speed.y = CAR_MAX_SPEED

	// Friction in non-accelerating axes

	if (DIRXVAL[car->dir] == 0) {
 		if (speed.x < 0) speed.x += 1;
 		else if (speed.x > 0) speedx -= 1;
	}

	if (DIRYVAL[car->dir] == 0) {
		if (speed.y < 0) speed.y += 0.5;
		else if (speed.y > 0) speed.y -= 0.5;
	}

	// Increment car position based on car speed

	car->pos.x += speed.x/2;
	car->pos.y += speed.y/2;

}

Layer* car_get_layer(Car *car) {
	return (Layer *)car->layer;
}

void car_set_position(Car *car, int x, int y) {
	car->pos.x = x;
	car->pos.y = y;
}

void car_change_dir(Car *car, int inc) {
	car->dir += inc;
	if (car->dir < 0) car->dir += 4;
	else if (car->dir > 3) car->dir -= 4;
}
