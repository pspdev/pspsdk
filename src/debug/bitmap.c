/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 *  bitmap.c - Take a screenshot and save it as a bitmap file
 *
 * Copyright (c) 2025, Francisco Javier Trujillo Mata <fjtrujy@gmail.com>
 *
 */

#include <pspuser.h>
#include <pspdisplay.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BMP_ID "BM"
#define PSP_SCREEN_WIDTH 480
#define PSP_SCREEN_HEIGHT 272
#define PSP_LINE_SIZE 512
#define BMP_RGB_BYTES_PER_PIXEL 3 // BMP format uses 24-bit RGB (3 bytes per pixel)

// Helper function to get pixel depth in bytes for a given format
static int get_pixel_depth(int format)
{
	switch (format)
	{
	case PSP_DISPLAY_PIXEL_FORMAT_565:
	case PSP_DISPLAY_PIXEL_FORMAT_5551:
	case PSP_DISPLAY_PIXEL_FORMAT_4444:
		return 2; // 16-bit formats
	case PSP_DISPLAY_PIXEL_FORMAT_8888:
		return 4; // 32-bit format
	default:
		return 0; // Invalid format
	}
}

struct BitmapHeader
{
	char id[2];
	uint32_t filesize;
	uint32_t reserved;
	uint32_t offset;
	uint32_t headsize;
	uint32_t width;
	uint32_t height;
	uint16_t planes;
	uint16_t bpp;
	uint32_t comp;
	uint32_t bitmapsize;
	uint32_t hres;
	uint32_t vres;
	uint32_t colors;
	uint32_t impcolors;
} __attribute__((packed));

static int fixed_write(int fd, void *data, int len)
{
	int writelen = 0;

	while (writelen < len)
	{
		int ret;

		ret = sceIoWrite(fd, data + writelen, len - writelen);
		if (ret <= 0)
		{
			writelen = -1;
			break;
		}
		writelen += ret;
	}

	return writelen;
}

void write_8888_line(void *frame, void *line_buf, int line)
{
	uint8_t *line_data = line_buf;
	const int pixel_depth = get_pixel_depth(PSP_DISPLAY_PIXEL_FORMAT_8888);
	uint8_t *p = frame + (line * PSP_LINE_SIZE * pixel_depth);
	int i;

	for (i = 0; i < PSP_SCREEN_WIDTH; i++)
	{
		line_data[(i * BMP_RGB_BYTES_PER_PIXEL) + 2] = p[i * pixel_depth];
		line_data[(i * BMP_RGB_BYTES_PER_PIXEL) + 1] = p[(i * pixel_depth) + 1];
		line_data[(i * BMP_RGB_BYTES_PER_PIXEL) + 0] = p[(i * pixel_depth) + 2];
	}
}

void write_5551_line(void *frame, void *line_buf, int line)
{
	uint8_t *line_data = line_buf;
	const int pixel_depth = get_pixel_depth(PSP_DISPLAY_PIXEL_FORMAT_5551);
	uint16_t *p = frame + (line * PSP_LINE_SIZE * pixel_depth);
	int i;

	for (i = 0; i < PSP_SCREEN_WIDTH; i++)
	{
		line_data[(i * BMP_RGB_BYTES_PER_PIXEL) + 2] = (p[i] & 0x1F) << 3;
		line_data[(i * BMP_RGB_BYTES_PER_PIXEL) + 1] = ((p[i] >> 5) & 0x1F) << 3;
		line_data[(i * BMP_RGB_BYTES_PER_PIXEL) + 0] = ((p[i] >> 10) & 0x1F) << 3;
	}
}

void write_565_line(void *frame, void *line_buf, int line)
{
	uint8_t *line_data = line_buf;
	const int pixel_depth = get_pixel_depth(PSP_DISPLAY_PIXEL_FORMAT_565);
	uint16_t *p = frame + (line * PSP_LINE_SIZE * pixel_depth);
	int i;

	for (i = 0; i < PSP_SCREEN_WIDTH; i++)
	{
		line_data[(i * BMP_RGB_BYTES_PER_PIXEL) + 2] = (p[i] & 0x1F) << 3;
		line_data[(i * BMP_RGB_BYTES_PER_PIXEL) + 1] = ((p[i] >> 5) & 0x3F) << 2;
		line_data[(i * BMP_RGB_BYTES_PER_PIXEL) + 0] = ((p[i] >> 11) & 0x1F) << 3;
	}
}

void write_4444_line(void *frame, void *line_buf, int line)
{
	uint8_t *line_data = line_buf;
	const int pixel_depth = get_pixel_depth(PSP_DISPLAY_PIXEL_FORMAT_4444);
	uint16_t *p = frame + (line * PSP_LINE_SIZE * pixel_depth);
	int i;

	for (i = 0; i < PSP_SCREEN_WIDTH; i++)
	{
		line_data[(i * BMP_RGB_BYTES_PER_PIXEL) + 2] = (p[i] & 0xF) << 4;
		line_data[(i * BMP_RGB_BYTES_PER_PIXEL) + 1] = ((p[i] >> 4) & 0xF) << 4;
		line_data[(i * BMP_RGB_BYTES_PER_PIXEL) + 0] = ((p[i] >> 8) & 0xF) << 4;
	}
}

int bitmapWrite(void *frame_addr, int format, const char *file)
{
	struct BitmapHeader bmp;
	uint8_t line_buf[PSP_SCREEN_WIDTH * BMP_RGB_BYTES_PER_PIXEL]; // Stack buffer for one line of RGB data
	int fd;
	int line;

	// Initialize header
	memset(&bmp, 0, sizeof(struct BitmapHeader));
	memcpy(bmp.id, BMP_ID, sizeof(bmp.id));
	bmp.filesize = PSP_SCREEN_WIDTH * PSP_SCREEN_HEIGHT * BMP_RGB_BYTES_PER_PIXEL + sizeof(struct BitmapHeader);
	bmp.offset = sizeof(struct BitmapHeader);
	bmp.headsize = 0x28;
	bmp.width = PSP_SCREEN_WIDTH;
	bmp.height = PSP_SCREEN_HEIGHT;
	bmp.planes = 1;
	bmp.bpp = BMP_RGB_BYTES_PER_PIXEL * 8; // Convert bytes to bits
	bmp.bitmapsize = PSP_SCREEN_WIDTH * PSP_SCREEN_HEIGHT * BMP_RGB_BYTES_PER_PIXEL;
	bmp.hres = 2834;
	bmp.vres = 2834;

	fd = sceIoOpen(file, PSP_O_WRONLY | PSP_O_CREAT | PSP_O_TRUNC, 0777);
	if (fd < 0)
	{
		return -1;
	}

	// Write header first
	if (fixed_write(fd, &bmp, sizeof(struct BitmapHeader)) != sizeof(struct BitmapHeader))
	{
		sceIoClose(fd);
		return -1;
	}

	// Process and write each line (from bottom to top as required by BMP format)
	for (line = PSP_SCREEN_HEIGHT - 1; line >= 0; line--)
	{
		switch (format)
		{
		case PSP_DISPLAY_PIXEL_FORMAT_565:
			write_565_line(frame_addr, line_buf, line);
			break;
		case PSP_DISPLAY_PIXEL_FORMAT_5551:
			write_5551_line(frame_addr, line_buf, line);
			break;
		case PSP_DISPLAY_PIXEL_FORMAT_4444:
			write_4444_line(frame_addr, line_buf, line);
			break;
		case PSP_DISPLAY_PIXEL_FORMAT_8888:
			write_8888_line(frame_addr, line_buf, line);
			break;
		}

		if (fixed_write(fd, line_buf, sizeof(line_buf)) != sizeof(line_buf))
		{
			sceIoClose(fd);
			return -1;
		}
	}

	sceIoClose(fd);
	return 0;
}
