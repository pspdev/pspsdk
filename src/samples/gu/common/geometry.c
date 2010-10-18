#include "geometry.h"

#include <pspgu.h>
#include <math.h>

static void generateTorus(unsigned int slices, unsigned int rows, float radius, float thickness, void* vertices, unsigned short* indices, unsigned int size, int texture, int color, int normal, int position)
{
	unsigned int i,j;

	for (j = 0; j < slices; ++j)
	{
		for (i = 0; i < rows; ++i)
		{
			float s = i + 0.5f;
			float t = j;
			float cs,ct,ss,st;
			int offset = 0;

			cs = cosf(s * (2*GU_PI) / slices);
			ct = cosf(t * (2*GU_PI) / rows);
			ss = sinf(s * (2*GU_PI) / slices);
			st = sinf(t * (2*GU_PI) / rows);

			if (texture >= 0)
			{
				float* texcoords = (float*)(((unsigned char*)vertices) + offset);
				texcoords[0] = cs * ct;
				texcoords[1] = cs * st;
				offset += texture;
			}

			if (color >= 0)
			{
				u32* col = (u32*)(((unsigned char*)vertices) + offset);
				unsigned int r = 128 + (cs * ct) * 127;
				unsigned int g = 128 + (cs * st) * 127;
				unsigned int b = 128 + ss * 127;

				*col = (0xff << 24)|(b << 16)|(g << 8)|r;
				offset += color;
			}

			if (normal >= 0)
			{
				float* normals = (float*)(((unsigned char*)vertices) + offset);
				normals[0] = cs * ct;
				normals[1] = cs * st;
				normals[2] = ss;

				offset += normal;
			}

			if (position >= 0)
			{
				float* pos = (float*)(((unsigned char*)vertices) + offset);
				pos[0] = (radius + thickness * cs) * ct;
				pos[1] = (radius + thickness * cs) * st;
				pos[2] = thickness * ss;

				offset += position;
			}      

			vertices = (void*)(((unsigned char*)vertices) + size);
		}
	}

	// TODO: generate degenerates instead, so we can tristrip the torus

	for (j = 0; j < slices; ++j)
	{
		for (i = 0; i < rows; ++i)
		{
			unsigned int i1 = (i+1) % rows;
			unsigned int j1 = (j+1) % slices;

			*indices++ = i + j * rows;
			*indices++ = i1 + j * rows;
			*indices++ = i + j1 * rows;

			*indices++ = i1 + j * rows;
			*indices++ = i1 + j1 * rows;
			*indices++ = i + j1 * rows;
		}
	}
}

void generateTorusTCNP(unsigned int slices, unsigned int rows, float radius, float thickness, TCNPVertex* vertices, unsigned short* indices)
{
	generateTorus(slices,rows,radius,thickness,vertices,indices,sizeof(TCNPVertex), 2 * sizeof(float), sizeof(u32), 3 * sizeof(float), 3 * sizeof(float));
}

void generateTorusTCP(unsigned int slices, unsigned int rows, float radius, float thickness, TCPVertex* vertices, unsigned short* indices)
{
	generateTorus(slices,rows,radius,thickness,vertices,indices,sizeof(TCPVertex), 2 * sizeof(float), sizeof(u32), -1, 3 * sizeof(float));
}

void generateTorusNP(unsigned int slices, unsigned int rows, float radius, float thickness, NPVertex* vertices, unsigned short* indices)
{
	generateTorus(slices,rows,radius,thickness,vertices,indices,sizeof(NPVertex),-1,-1,3 * sizeof(float), 3 * sizeof(float));
}

static void generateGrid(unsigned int columns, unsigned int rows, float width, float depth, void* vertices, unsigned short* indices, unsigned int size, int texture, int color, int normal, int position)
{
	unsigned int i,j;
	float ic = 1.0f / columns;
	float ir = 1.0f / rows;

	for (j = 0; j < rows; ++j)
	{
		for (i = 0; i < columns; ++i)
		{
			int offset = 0;

			if (texture >= 0)
			{
				float* texcoords = (float*)(((unsigned char*)vertices) + offset);
				texcoords[0] = ic * i;
				texcoords[1] = ir * j;
				offset += texture;
			}

			if (color >= 0)
			{
				u32* col = (u32*)(((unsigned char*)vertices) + offset);
				*col = 0xffffffff;
				offset += color;
			}

			if (normal >= 0)
			{
				float* normals = (float*)(((unsigned char*)vertices) + offset);
				normals[0] = 0.0f;
				normals[1] = 1.0f;
				normals[2] = 0.0f;
				offset += normal;
			}

			if (position >= 0)
			{
				float* pos = (float*)(((unsigned char*)vertices) + offset);
				pos[0] = ((ic * i)-0.5f) * width;
				pos[1] = 0.0f;
				pos[2] = ((ir * j)-0.5f) * depth;
				offset += position;
			}

			vertices = (void*)(((unsigned char*)vertices) + size);
		}
	}

	for (j = 0; j < rows-1; ++j)
	{
		for (i = 0; i < columns-1; ++i)
		{
			*indices++ = i + j * columns;
			*indices++ = (i+1) + j * columns;
			*indices++ = i + (j+1) * columns;

			*indices++ = (i+1) + j * columns;
			*indices++ = (i+1) + (j+1) * columns;
			*indices++ = i + (j+1) * columns;
		}
	}
}

void generateGridTCNP(unsigned int columns, unsigned int rows, float width, float depth, TCNPVertex* vertices, unsigned short* indices)
{
	generateGrid(columns,rows,width,depth,vertices,indices,sizeof(TCNPVertex),2 * sizeof(float), sizeof(u32), 3 * sizeof(float), 3 * sizeof(float));
}

void generateGridNP(unsigned int columns, unsigned int rows, float width, float depth, NPVertex* vertices, unsigned short* indices)
{
	generateGrid(columns,rows,width,depth,vertices,indices,sizeof(NPVertex),-1,-1,3 * sizeof(float), 3 * sizeof(float));
}
