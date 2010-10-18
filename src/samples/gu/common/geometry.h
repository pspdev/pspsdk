#ifndef common_geometry_h
#define common_geometry_h

#include <psptypes.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
	ScePspFVector2 texture;
	u32 color;
	ScePspFVector3 normal;
	ScePspFVector3 position;
} TCNPVertex; // Texture, Color, Normal, Position
#define TCNP_VERTEX_FORMAT (GU_TEXTURE_32BITF|GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF)

typedef struct
{
	ScePspFVector2 texture;
	u32 color;
	ScePspFVector3 position;
} TCPVertex; // Texture, Color, Position
#define TCP_VERTEX_FORMAT (GU_TEXTURE_32BITF|GU_COLOR_8888|GU_VERTEX_32BITF)

typedef struct
{
	ScePspFVector2 texture;
	ScePspFVector3 position;
} TPVertex; // Texture, Position
#define TP_VERTEX_FORMAT (GU_TEXTURE_32BITF|GU_VERTEX_32BITF)

typedef struct
{
	ScePspFVector3 normal;
	ScePspFVector3 position;
} NPVertex; // Normal, Position
#define NP_VERTEX_FORMAT (GU_NORMAL_32BITF|GU_VERTEX_32BITF)

/*
	torus memory usage

	vertices: slices * rows
	indices: slices * rows
*/
void generateTorusTCNP(unsigned int slices, unsigned int rows, float radius, float thickness, TCNPVertex* vertices, unsigned short* indices);
void generateTorusTCP(unsigned int slices, unsigned int rows, float radius, float thickness, TCPVertex* vertices, unsigned short* indices);
void generateTorusNP(unsigned int slices, unsigned int rows, float radius, float thickness, NPVertex* vertices, unsigned short* indices);

/*
	grid memory usage

	vertices: slices * rows
	indices (slices-1) * (rows-1)
*/
void generateGridTCNP(unsigned int columns, unsigned int rows, float width, float depth, TCNPVertex* vertices, unsigned short* indices);
void generateGridTCP(unsigned int columns, unsigned int rows, float width, float depth, TCPVertex* vertices, unsigned short* indices);
void generateGridNP(unsigned int columns, unsigned int rows, float width, float depth, NPVertex* vertices, unsigned short* indices);

#ifdef __cplusplus
}
#endif

#endif
