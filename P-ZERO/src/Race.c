
// Race

int map_w = 22;
int map_h = 23;
int mapdata[] = {
   1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  3, 
  12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 14, 
  12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 14, 
  12, 13, 13, 13, 13,  4, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,  5, 13, 13, 13, 14, 
  12, 13, 13, 13, 13, 14, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 12, 13, 13, 13, 14, 
  12, 13, 13, 13, 13, 14, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 12, 13, 13, 13, 14, 
  12, 13, 13, 13, 13, 14, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 30, 12, 13, 13, 18, 14, 
  12, 27, 26, 27, 26, 14,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  3, 12, 13, 13, 13, 14, 
  12, 26, 27, 26, 27, 14, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 14, 12, 13, 13, 13, 14, 
  12, 13, 13, 13, 13, 14, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 14, 12, 13, 13, 13, 14, 
  12, 13, 13, 13, 13, 14, 12, 13, 18,  4, 24, 24,  5, 13, 13, 13, 14, 12, 13, 13, 13, 14, 
  12, 13, 13, 13, 13, 14, 12, 13, 13, 14,  1,  2, 16, 13, 13, 13, 14, 12, 13, 13, 13, 14, 
  12, 13, 13, 13, 13, 14, 12, 13, 13, 14, 12, 13, 13, 13, 13, 13, 14, 12, 18, 13, 13, 14, 
  12, 13, 13, 13, 13, 14, 12, 13, 13, 14, 12, 13, 13, 13, 13, 13, 14, 12, 13, 13, 13, 14, 
  12, 13, 13, 13, 13, 14, 12, 13, 13, 14, 12, 13, 13,  4, 24, 24, 25, 12, 13, 13, 13, 14, 
  12, 13, 13, 13, 13, 14, 12, 13, 13, 14, 12, 13, 13, 14, 30, 30, 30, 12, 13, 13, 13, 14, 
  12,  6, 13, 13, 13, 14, 12, 13, 13, 14, 12, 13, 13, 14, 30, 30, 30, 12, 13, 13, 18, 14, 
  12, 13, 13, 13, 13, 14, 12, 13, 13, 14, 12, 13, 13, 14, 30, 30, 30, 12, 13, 13, 13, 14, 
  12, 13, 13, 13, 13, 15, 16, 13, 13, 14, 12, 13, 13, 14, 30, 30, 30, 12, 13, 13, 13, 14, 
  12, 13, 13, 13, 13, 13, 13, 13, 13, 14, 12, 13, 13, 15,  2,  2,  2, 16, 13, 13, 13, 14, 
  12, 13, 13, 13, 13, 13, 13, 13, 13, 14, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 14, 
  12, 13, 13, 13, 13, 13, 13, 13, 13, 14, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 14, 
  23, 24, 24, 24, 24, 24, 24, 24, 24, 25, 23, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 25, 
};

typedef struct {

	Car *cars[];
	Track* track; 

} Race;

void race_logic_step(Race *race) {

	
	
}