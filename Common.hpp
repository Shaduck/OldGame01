

FILE *filelog;


BITMAP *buffer;
BITMAP *sfondo;
//BITMAP *textures;
//BITMAP *textarch[2];
RGB color[256];
bool changed;
//RGB colorarch[2][256];

byte MaskText[SPRITETOT];

byte terreno[RESOLUTION_Y+Y_OFFSET+Y2_OFFSET]
				[RESOLUTION_X+X_OFFSET+X2_OFFSET];

byte solid[RESOLUTION_Y+Y_OFFSET+Y2_OFFSET]
				[RESOLUTION_X+X_OFFSET+X2_OFFSET];

