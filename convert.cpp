#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <netinet/in.h>

#define NANOSVG_IMPLEMENTATION
#include "nanosvg.h"

int main(void)
{
	NSVGimage* image = nsvgParseFromFile("hokusai.svg", "px", 96);

	for (NSVGshape * shape = image->shapes; shape != NULL; shape = shape->next)
	{
		uint8_t color;
		switch(shape->fill.color)
		{
			case 0xFF800000: // dark blue
			case 0xff6b502d:
			case 0xff201f23:
				color = 1;
				break;
			case 0xffffffff: // white
				color = 2;
				break;
			case 0xff5ac2e6:
			case 0xff337c64: // dark yellow?
				color = 3;
				break;
			default:
				fprintf(stderr, "\nUnknown color %x\n", shape->fill.color);
		}

		printf("{ %d, {", color);

		for (NSVGpath * path = shape->paths; path != NULL; path = path->next)
		{
			for (int i = 0; i < path->npts; i++)
			{
				uint16_t X = path->pts[i * 2];
				uint16_t Y = path->pts[i * 2 + 1];

				printf("%d, %d, ", X, Y);
			}
		}

		printf("}},\n");
	}

	nsvgDelete(image);

	return 0;
}
