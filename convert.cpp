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
		for (NSVGpath * path = shape->paths; path != NULL; path = path->next)
		{
			for (int i = 0; i < path->npts * 2; i++)
			{
				uint16_t coord = path->pts[i];
				fprintf(stderr, "%d, ", coord);
				if (i & 1)
					write(1, &coord, 1);
				else {
					coord = htons(coord);
					write(1, &coord, 2);
				}
			}
		}

		uint8_t color;
		switch(shape->fill.color)
		{
			case 0xFFFFFFFF: // White
				color = 0x80;
				break;
			case 0xffcdb982: // cyan?
				color = 0x81;
				break;
			case 0xffcccccc: // grey
				color = 0x82;
				break;
			case 0xff3b2714:
				color = 0x83;
				break;
			case 0xff201f23:
				color = 0x84;
				break;
			case 0xff2d1414:
				color = 0x85;
				break;
			case 0xff6b502d:
				color = 0x86;
				break;
			case 0xff5ac2e6:
				color = 0x87;
				break;
			case 0xff337c64:
				color = 0x88;
				break;
			case 0xff987350:
				color = 0x89;
				break;
			default:
				fprintf(stderr, "Unknown color %x\n", shape->fill.color);
		}

		write(1, &color, 1);
	}

	nsvgDelete(image);

	return 0;
}
