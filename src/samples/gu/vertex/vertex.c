/*
 * PSP Software Development Kit - https://github.com/pspdev
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <psprtc.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include <pspgu.h>
#include <pspgum.h>

#include "../common/callbacks.h"
#include "../common/menu.h"

PSP_MODULE_INFO("Vertex Speed Sample", 0, 1, 1);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER);

static unsigned int __attribute__((aligned(16))) list[262144];

#define BUF_WIDTH (512)
#define SCR_WIDTH (480)
#define SCR_HEIGHT (272)

// TODO: fix alignments

int getVertexSize(int vertexFormat)
{
	enum
	{
		SIZE,
		WEIGHTS,
		VERTEX,
	};

	static int vertexValues[] =
	{
		4, 0, GU_TEXTURE_BITS, SIZE,	2, 0, 1, 2, 4,
		4, 9, GU_WEIGHT_BITS, WEIGHTS,  1, 0, 1, 2, 4,
		8, 2, GU_COLOR_BITS, SIZE,	1, 0, 0, 0, 0, 2, 2, 2, 4,
		4, 5, GU_NORMAL_BITS, SIZE,	3, 0, 1, 2, 4,
		4, 7, GU_VERTEX_BITS, SIZE,	3, 0, 1, 2, 4,
		0, 11, GU_VERTICES_BITS, VERTEX, 0,
		0, 0, 0,
	};

	int* current = vertexValues;
	int size = 0;

	while (current[0] || current[1] || current[2])
	{
		int currentCount = current[0];
		int currentShift = current[1];
		int currentBits = current[2];
		int mode = current[3];
		int numElements = current[4];

		current += 5;

		switch (mode)
		{
			case SIZE:
			{
				int elementSize = current[(vertexFormat & currentBits) >> currentShift];

				// align
				if (elementSize > 0)
					size = (size + (elementSize-1)) & ~(elementSize-1);

				size += elementSize * numElements;
			}
			break;

			case WEIGHTS:
			{
				int elementSize = current[(vertexFormat & currentBits) >> currentShift];
				int numWeights = ((vertexFormat & GU_WEIGHTS_BITS) >> 14)+1;

				if (elementSize > 0)
					size = (size + (elementSize-1)) & ~(elementSize-1);

				if (numWeights > 1)
					size += numWeights * elementSize;
			}
			break;

			case VERTEX:
			{
				int numVertices = ((vertexFormat & GU_VERTICES_BITS) >> 18);
				if (size > 0)
					size = (size + (4-1)) & ~(4-1);
				size += size * numVertices;
			}
			break;
		}


		current += currentCount;
	}

	// align to size of first element?
	if (size > 0)
		size = (size + (4-1)) & ~(4-1);

	return size;
}

void generateVertexBuffer(int vertexFormat, void* vertices, int batchSize)
{
	int vertexSize = getVertexSize(vertexFormat);
//	int textureOffset = 0;
	int colorOffset = getVertexSize(vertexFormat & (GU_TEXTURE_BITS));
//	int normalOffset = getVertexSize(vertexFormat & (GU_TEXTURE_BITS|GU_COLOR_BITS));
	int vertexOffset = getVertexSize(vertexFormat & (GU_TEXTURE_BITS|GU_COLOR_BITS|GU_NORMAL_BITS));
	float batchScale = 1.0f / batchSize;
	int i;

	char* current = vertices;

	for (i = 0; i < batchSize; ++i)
	{
		memset(current,0,vertexSize);

		// TODO: render something nice
/*
		float x = cosf((i * batchScale) * (GU_PI*2));
		float y = sinf((i * batchScale) * (GU_PI*2));

		switch (vertexFormat & GU_COLOR_BITS)
		{
			case GU_COLOR_5650:
			case GU_COLOR_5551:
			case GU_COLOR_4444:
			{
				unsigned short* color = (unsigned short*)(current + colorOffset);
				*color = i;
			}
			break;

			case GU_COLOR_8888:
			{
				unsigned int* color = (unsigned int*)(current + colorOffset);
				*color = i;
			}
			break;
		}

		switch (vertexFormat & GU_VERTEX_BITS)
		{
			case GU_VERTEX_8BIT:
			{
				char* vertex = (char*)(current + vertexOffset);
				vertex[0] = x * 127.5f;
				vertex[1] = y * 127.5f;
			}
			break;

			case GU_VERTEX_16BIT:
			{
				short* vertex = (short*)(current + vertexOffset);
				vertex[0] = x * 32767.5f;
				vertex[1] = y * 32767.5f; 
			}
			break;

			case GU_VERTEX_32BITF:
			{
				float* vertex = (float*)(current + vertexOffset);
				vertex[0] = x;
				vertex[1] = y;
			}
			break;
		}		
*/
		current = current + vertexSize;
	}
}

typedef enum
{
	NoAction,
	TextureMenu,
	ColorMenu,
	NormalMenu,
	VertexMenu,
	WeightMenu,
	NumWeightsMenu,
	NumVerticesMenu,
	IndexBufferMenu,
	IndexFormatMenu,
	IndexMemoryMenu,
	IndexCacheMenu,
	MemoryMenu,
	QuitTrigger
} MenuAction;

int main(int argc, char* argv[])
{
	setupCallbacks();

	// setup GU

	void* fbp0 = guGetStaticVramBuffer(BUF_WIDTH,SCR_HEIGHT,GU_PSM_8888);
	void* fbp1 = guGetStaticVramBuffer(BUF_WIDTH,SCR_HEIGHT,GU_PSM_8888);
	void* zbp = guGetStaticVramBuffer(BUF_WIDTH,SCR_HEIGHT,GU_PSM_4444);

	pspDebugScreenInit();
	sceGuInit();

	sceGuStart(GU_DIRECT,list);
	sceGuDrawBuffer(GU_PSM_8888,fbp0,BUF_WIDTH);
	sceGuDispBuffer(SCR_WIDTH,SCR_HEIGHT,fbp1,BUF_WIDTH);
	sceGuDepthBuffer(zbp,BUF_WIDTH);
	sceGuOffset(2048 - (SCR_WIDTH/2),2048 - (SCR_HEIGHT/2));
	sceGuViewport(2048,2048,SCR_WIDTH,SCR_HEIGHT);
	sceGuDepthRange(65535,0);
	sceGuScissor(0,0,SCR_WIDTH,SCR_HEIGHT);
	sceGuEnable(GU_SCISSOR_TEST);
	sceGuDepthFunc(GU_GEQUAL);
	sceGuEnable(GU_DEPTH_TEST);
	sceGuFrontFace(GU_CW);
	sceGuShadeModel(GU_SMOOTH);
	sceGuEnable(GU_CULL_FACE);
	sceGuEnable(GU_TEXTURE_2D);
	sceGuEnable(GU_CLIP_PLANES);

	sceGuFinish();
	sceGuSync(0,0);

	sceDisplayWaitVblankStart();
	sceGuDisplay(GU_TRUE);

	// allocate vertex buffers

	int maxVertexSize = getVertexSize(GU_TEXTURE_32BITF|GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_WEIGHT_32BITF|GU_WEIGHTS(8)|GU_VERTICES(8));
	int batchSize = 1536; // max size = 608, 608 * 1536 = ~1MB, make sure you don't overrun vram limits if you change this
	void* ramVertexBuffer = malloc(batchSize * maxVertexSize);
	void* vramVertexBuffer = guGetStaticVramTexture(batchSize,maxVertexSize,GU_PSM_T8);

	// allocate index buffers

	void* ramIndexBuffer = malloc(batchSize * sizeof(unsigned short));
	void* vramIndexBuffer = guGetStaticVramTexture(batchSize,sizeof(unsigned short),GU_PSM_T8);

	// run sample

	int val = 0;
	SceCtrlData oldPad;
	memset(&oldPad,0,sizeof(SceCtrlData));

	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(0);

	// create debug menu

	MenuContext* context = initMenu();

	MenuItem* vertexFormatMenu = addMenuItem(context,0,createMenuContainer("Vertex Buffer"),NoAction,0);
	{
		MenuItem* textureMenu = addMenuItem(context,vertexFormatMenu,createMenuContainer("Texture"),NoAction,0);
		{
			addMenuItem(context,textureMenu,createRadioButton("Off",1),TextureMenu,0);
			addMenuItem(context,textureMenu,createRadioButton("8-bit",0),TextureMenu,GU_TEXTURE_8BIT);
			addMenuItem(context,textureMenu,createRadioButton("16-bit",0),TextureMenu,GU_TEXTURE_16BIT);
			addMenuItem(context,textureMenu,createRadioButton("32-bit",0),TextureMenu,GU_TEXTURE_32BITF);
		}

		MenuItem* colorMenu = addMenuItem(context,vertexFormatMenu,createMenuContainer("Color"),NoAction,0);
		{
			addMenuItem(context,colorMenu,createRadioButton("Off",0),ColorMenu,0);
			addMenuItem(context,colorMenu,createRadioButton("5650 (16-bit)",0),ColorMenu,GU_COLOR_5650);
			addMenuItem(context,colorMenu,createRadioButton("5551 (16-bit)",0),ColorMenu,GU_COLOR_5551);
			addMenuItem(context,colorMenu,createRadioButton("4444 (16-bit)",0),ColorMenu,GU_COLOR_4444);
			addMenuItem(context,colorMenu,createRadioButton("8888 (32-bit)",1),ColorMenu,GU_COLOR_8888);
		}

		MenuItem* normalMenu = addMenuItem(context,vertexFormatMenu,createMenuContainer("Normal"),NoAction,0);
		{
			addMenuItem(context,normalMenu,createRadioButton("Off",1),NormalMenu,0);
			addMenuItem(context,normalMenu,createRadioButton("8-bit",0),NormalMenu,GU_NORMAL_8BIT);
			addMenuItem(context,normalMenu,createRadioButton("16-bit",0),NormalMenu,GU_NORMAL_16BIT);
			addMenuItem(context,normalMenu,createRadioButton("32-bit",0),NormalMenu,GU_NORMAL_32BITF);
		}

		MenuItem* vertexMenu = addMenuItem(context,vertexFormatMenu,createMenuContainer("Vertex"),NoAction,0);
		{
			addMenuItem(context,vertexMenu,createRadioButton("Off",0),VertexMenu,0);
			addMenuItem(context,vertexMenu,createRadioButton("8-bit",0),VertexMenu,GU_VERTEX_8BIT);
			addMenuItem(context,vertexMenu,createRadioButton("16-bit",0),VertexMenu,GU_VERTEX_16BIT);
			addMenuItem(context,vertexMenu,createRadioButton("32-bit",1),VertexMenu,GU_VERTEX_32BITF);
		}

		MenuItem* weightMenu = addMenuItem(context,vertexFormatMenu,createMenuContainer("Weight"),NoAction,0);
		{
			addMenuItem(context,weightMenu,createRadioButton("Off",1),WeightMenu,0);
			addMenuItem(context,weightMenu,createRadioButton("8-bit",0),WeightMenu,GU_WEIGHT_8BIT);
			addMenuItem(context,weightMenu,createRadioButton("16-bit",0),WeightMenu,GU_WEIGHT_16BIT);
			addMenuItem(context,weightMenu,createRadioButton("32-bit",0),WeightMenu,GU_WEIGHT_32BITF);
		}

		MenuItem* numWeightsMenu = addMenuItem(context,vertexFormatMenu,createMenuContainer("Num. Weights"),NoAction,0);
		{
			addMenuItem(context,numWeightsMenu,createRadioButton("0",1),NumWeightsMenu,0);
			addMenuItem(context,numWeightsMenu,createRadioButton("2",0),NumWeightsMenu,GU_WEIGHTS(2));
			addMenuItem(context,numWeightsMenu,createRadioButton("3",0),NumWeightsMenu,GU_WEIGHTS(3));
			addMenuItem(context,numWeightsMenu,createRadioButton("4",0),NumWeightsMenu,GU_WEIGHTS(4));
			addMenuItem(context,numWeightsMenu,createRadioButton("5",0),NumWeightsMenu,GU_WEIGHTS(5));
			addMenuItem(context,numWeightsMenu,createRadioButton("6",0),NumWeightsMenu,GU_WEIGHTS(6));
			addMenuItem(context,numWeightsMenu,createRadioButton("7",0),NumWeightsMenu,GU_WEIGHTS(7));
			addMenuItem(context,numWeightsMenu,createRadioButton("8",0),NumWeightsMenu,GU_WEIGHTS(8));
		}

		MenuItem* numVerticesMenu = addMenuItem(context,vertexFormatMenu,createMenuContainer("Num. Vertices"),NoAction,0);
		{
			addMenuItem(context,numVerticesMenu,createRadioButton("1",1),NumVerticesMenu,GU_VERTICES(1));
			addMenuItem(context,numVerticesMenu,createRadioButton("2",0),NumVerticesMenu,GU_VERTICES(2));
			addMenuItem(context,numVerticesMenu,createRadioButton("3",0),NumVerticesMenu,GU_VERTICES(3));
			addMenuItem(context,numVerticesMenu,createRadioButton("4",0),NumVerticesMenu,GU_VERTICES(4));
			addMenuItem(context,numVerticesMenu,createRadioButton("5",0),NumVerticesMenu,GU_VERTICES(5));
			addMenuItem(context,numVerticesMenu,createRadioButton("6",0),NumVerticesMenu,GU_VERTICES(6));
			addMenuItem(context,numVerticesMenu,createRadioButton("7",0),NumVerticesMenu,GU_VERTICES(7));
			addMenuItem(context,numVerticesMenu,createRadioButton("8",0),NumVerticesMenu,GU_VERTICES(8));
		}

		MenuItem* memoryMenu = addMenuItem(context,vertexFormatMenu,createMenuContainer("Memory Location"),NoAction,0);
		{
			addMenuItem(context,memoryMenu,createRadioButton("System RAM",1),MemoryMenu,0);
			addMenuItem(context,memoryMenu,createRadioButton("Video RAM",0),MemoryMenu,1);
		}
	}


	MenuItem* indexBufferMenu = addMenuItem(context,0,createMenuContainer("Index Buffer"),NoAction,0);
	{
		addMenuItem(context,indexBufferMenu,createRadioButton("Disabled",1),IndexBufferMenu,0);
		addMenuItem(context,indexBufferMenu,createRadioButton("Enabled",0),IndexBufferMenu,1);

		MenuItem* indexFormatMenu = addMenuItem(context,indexBufferMenu,createMenuContainer("Format"),NoAction,0);
		{
			addMenuItem(context,indexFormatMenu,createRadioButton("8-bit",0),IndexFormatMenu,GU_INDEX_8BIT);
			addMenuItem(context,indexFormatMenu,createRadioButton("16-bit",1),IndexFormatMenu,GU_INDEX_16BIT);
		}

		MenuItem* indexMemoryMenu = addMenuItem(context,indexBufferMenu,createMenuContainer("Memory Location"),NoAction,0);
		{
			addMenuItem(context,indexMemoryMenu,createRadioButton("System RAM",1),IndexMemoryMenu,0);
			addMenuItem(context,indexMemoryMenu,createRadioButton("Video RAM",0),IndexMemoryMenu,1);
		}

		MenuItem* indexCacheMenu = addMenuItem(context,indexBufferMenu,createMenuContainer("Cache Test Size"),NoAction,0);
		{
			addMenuItem(context,indexCacheMenu,createRadioButton("Disabled",1),IndexCacheMenu,batchSize);
			addMenuItem(context,indexCacheMenu,createRadioButton("4",0),IndexCacheMenu,4);
			addMenuItem(context,indexCacheMenu,createRadioButton("8",0),IndexCacheMenu,8);
			addMenuItem(context,indexCacheMenu,createRadioButton("16",0),IndexCacheMenu,16);
			addMenuItem(context,indexCacheMenu,createRadioButton("32",0),IndexCacheMenu,32);
		}
	}

	addMenuItem(context,0,createTriggerButton("Quit"),QuitTrigger,0);

	unsigned int vertexMask = GU_COLOR_8888|GU_VERTEX_32BITF;
	unsigned int vertexSize = getVertexSize(vertexMask);
	int exitRequested = 0;
	int changed = 1;
	int memorySelection = 0;
	int indexEnabled = 0;
	int indexFormat = GU_INDEX_16BIT;
	int indexCacheSize = batchSize;
	int indexMemory = 0;
	u64 tickCount = 0;
	u32 tickResolution = sceRtcGetTickResolution();
	u32 vertexCount = 0;
	float avgVertexSpeed = 0;
	int batchCount = 1;

	while(running() && !exitRequested)
	{
		SceCtrlData pad;
		if (!sceCtrlPeekBufferPositive(&pad,1))
			pad = oldPad;

		MenuItem* action = handleMenu(context, &pad);
		if (action)
		{
			switch (action->id)
			{
				case TextureMenu:
				{
					vertexMask = (vertexMask & ~GU_TEXTURE_BITS) | action->data;
					changed = 1;
				}
				break;

				case ColorMenu:
				{
					vertexMask = (vertexMask & ~GU_COLOR_BITS) | action->data;
					changed = 1;
				}
				break;

				case NormalMenu:
				{
					vertexMask = (vertexMask & ~GU_NORMAL_BITS) | action->data;
					changed = 1;
				}
				break;

				case VertexMenu:
				{
					vertexMask = (vertexMask & ~GU_VERTEX_BITS) | action->data;
					changed = 1;
				}
				break;

				case WeightMenu:
				{
					vertexMask = (vertexMask & ~GU_WEIGHT_BITS) | action->data;
					changed = 1;
				}
				break;

				case NumWeightsMenu:
				{
					vertexMask = (vertexMask & ~GU_WEIGHTS_BITS) | action->data;
					changed = 1;
				}
				break;

				case NumVerticesMenu:
				{
					vertexMask = (vertexMask & ~GU_VERTICES_BITS) | action->data;
					changed = 1;
				}
				break;

				case IndexBufferMenu:
				{
					indexEnabled = action->data;
					vertexMask = (vertexMask & ~GU_INDEX_BITS) | (indexEnabled ? indexFormat : 0);
					changed = 1;
				}
				break;

				case IndexFormatMenu:
				{
					indexFormat = action->data;
					vertexMask = (vertexMask & ~GU_INDEX_BITS) | (indexEnabled ? indexFormat : 0);
					changed = 1;
				}
				break;

				case IndexCacheMenu:
				{
					indexCacheSize = action->data;
					changed = 1;
				}
				break;

				case IndexMemoryMenu:
				{
					indexMemory = action->data;
					changed = 1;
				}
				break;

				case MemoryMenu:
				{
					memorySelection = action->data;
					changed = 1;
				}
				break;

				case QuitTrigger:
					exitRequested = 1;
				break;

				case NoAction:
				default:
					break;
			}
		}

		if (changed)
		{
			pspDebugScreenSetOffset((int)fbp1);
			pspDebugScreenSetXY((60/2)-(31/2),33/2); // TODO: center?
			pspDebugScreenPrintf("--- Rebuilding buffers ---");

			// re-generate buffers

			generateVertexBuffer(vertexMask,memorySelection ? vramVertexBuffer : ramVertexBuffer,batchSize);
			if (indexEnabled)
			{
				switch (vertexMask & GU_INDEX_BITS)
				{
					case GU_INDEX_8BIT:
					{
						unsigned char* indexBuffer = indexMemory ? vramIndexBuffer : ramIndexBuffer;
						int i;
						for (i = 0; i < batchSize; ++i)
							*indexBuffer++ = (i % indexCacheSize);
					}
					break;

					case GU_INDEX_16BIT:
					{
						unsigned short* indexBuffer = indexMemory ? vramIndexBuffer : ramIndexBuffer;
						int i;
						for (i = 0; i < batchSize; ++i)
							*indexBuffer++ = (i % indexCacheSize);
					}
					break;
				}
			}



			vertexSize = getVertexSize(vertexMask);
			sceKernelDcacheWritebackAll();
			changed = 0;

			vertexCount = 0;
			tickCount = 0;
			avgVertexSpeed = 0;
			batchCount = 1;
		}

		// TODO: additional input processing here

		oldPad = pad;

		sceGuStart(GU_SEND,list);

		// run gu stuff not to be measured

		sceGuStart(GU_DIRECT,list);

		sceGuClearColor(0xff554433);
		sceGuClearDepth(0);
		sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);

		sceGumMatrixMode(GU_PROJECTION);
		sceGumLoadIdentity();
		sceGumPerspective(75.0f,16.0f/9.0f,0.5f,1000.0f);

		sceGumMatrixMode(GU_VIEW);
		sceGumLoadIdentity();

		sceGumMatrixMode(GU_MODEL);
		sceGumLoadIdentity();

		sceGuFinish();
		sceGuSync(0,0);

		// draw cube

		sceGuStart(GU_SEND,list);
		int i;
		for (i = 0; i < batchCount; ++i)
			sceGumDrawArray(GU_POINTS,vertexMask,batchSize,indexMemory ? vramIndexBuffer : ramIndexBuffer,memorySelection ? vramVertexBuffer : ramVertexBuffer);
		sceGuFinish();
		vertexCount += batchSize * batchCount;

		PspGeContext tempGeContext;
		u64 tick1,tick2;
		sceRtcGetCurrentTick(&tick1);
		sceGuSendList(GU_TAIL,list,&tempGeContext);
		sceGuSync(0,0);
		sceRtcGetCurrentTick(&tick2);

		// rescale number of batches if they rendered faster/slower than threshold

		if (((tick2-tick1) < (tickResolution * (1.0f/60.0f) * 0.8f)) || ((tick2-tick1) > (tickResolution * (1.0f/60.0f) * 1.0f)))
		{
			batchCount = (int)((tickResolution * (1.0f/60.0f) * 0.8f) / (((tick2-tick1) / (float)batchCount)));
			batchCount = batchCount > 130 ? 130 : batchCount < 1 ? 1 : batchCount;
		}

		tickCount += (tick2-tick1);
		if (tickCount > tickResolution)
		{
			float timeSpan = tickCount / (float)tickResolution;
			avgVertexSpeed = (vertexCount / timeSpan) / 1000000;

			tickCount = 0;
			vertexCount = 0;
		}

		pspDebugScreenSetOffset((int)fbp0);
		pspDebugScreenSetXY(0,0);
		pspDebugScreenPrintf("Mask: 0x%08x, Size: %u", vertexMask, vertexSize,val);
		if (avgVertexSpeed)
			pspDebugScreenPrintf(", %.2f million vertices / sec.",avgVertexSpeed);
		else
			pspDebugScreenPrintf(", accumulating (%.2f%%)...",100.0f * (tickCount / (float)tickResolution));

		pspDebugScreenSetXY(0,32);
		pspDebugScreenPrintf("This is performance numbers, not real world numbers!");

		renderMenu(context,0,2);

		sceDisplayWaitVblankStart();
		fbp1 = fbp0;
		fbp0 = sceGuSwapBuffers();

		val++;
	}

	sceGuTerm();

	sceKernelExitGame();
	return 0;
}
