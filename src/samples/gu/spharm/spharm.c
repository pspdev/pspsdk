////////////////////////////////////////////////////////////////////////////////////////
// Spherical Harmonic Surface 
// Copyright (c) 2004,5   adresd <adresd_ps2dev@yahoo.com>
// 
// calculated with each point, as done.
// as drawn re-uses previous strip for making the tri strips, so
// first strip may not be correct first run.
//
// Note that this code is highly unoptimized, but might be useful to learn from or so.
//
#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspdebug.h>
#include <pspge.h>
#include <stdlib.h>
#include <stdio.h>

#include <pspgu.h>
#include <pspgum.h>

#include <math.h>
#include "mt19937.h"

/*
*/

#define PSP_GEVERT_SET(TEX,COL,NORM,VERT,INDEX,TRAN) ((TEX)|(COL<<2)|(NORM<<5)|(VERT<<7)|(INDEX<<11)|(TRAN<<23))


#define PI      (3.14159265358979323846f)
#define TWOPI (PI+PI)

float shift23=(float)(1<<23);
float OOshift23=1.0f/(float)(1<<23);
inline float floorf(float i)
{ // return largest integer that is less than or equal to i
  float k = (float)((int) i);
  if (k <= i) 
    return k;
  else  // if k greater than i
    return k-1.0f;
}
static inline float myLog2(float i)
{
	float LogBodge=0.346607f;
	float x;
	float y;
	x=*(int *)&i;
	x*= OOshift23; //1/pow(2,23);
	x=x-127;

	y=x-floorf(x);
	y=(y-y*y)*LogBodge;
	return x+y;
}
static inline float myPow2(float i)
{
	float PowBodge=0.33971f;
	float x;
	float y=i-floorf(i);
	y=(y-y*y)*PowBodge;

	x=i+127-y;
	x*= shift23; //pow(2,23);
	*(int*)&x=(int)x;
	return x;
}

static inline float mypowf(float a, float b)
{
	return myPow2(b*myLog2(a));
}

static inline float invsqrtf (float x)
{
    float xhalf = 0.5f*x;
    int i = *(int*)&x;
    i = 0x5f3759df - (i >> 1);
    x = *(float*)&i;
    x = x*(1.5f - xhalf*x*x);
    return x;
}

static inline float mysqrtf(float val)
{
  float val2 = invsqrtf(val);
  if (val2 == 0.0f) return 0.0f; // check for div by 0
  return (1.0f / val2);
}

static int mi[8];
static float mf[8];
static float mft[8];

//  Float Vector
typedef struct 
{
	float x, y, z;
} FVec;
//  Short Vector
typedef struct 
{
	short x, y, z;
} SVec;
//  Integer Vector
typedef struct 
{
	int x, y, z;
} IVec;

static inline void FVecMult(FVec *v0, const FVec *v1, const FVec *v2)
{
  v0->x = v1->x * v2->x;
  v0->y = v1->y * v2->y;
  v0->z = v1->z * v2->z;
}
static inline void FVecSub(FVec *v0, const FVec *v1, const FVec *v2)
{
  v0->x = v1->x - v2->x;
  v0->y = v1->y - v2->y;
  v0->z = v1->z - v2->z;
}
static inline void FVecAdd(FVec *v0, const FVec *v1, const FVec *v2)
{
  v0->x = v1->x + v2->x;
  v0->y = v1->y + v2->y;
  v0->z = v1->z + v2->z;
}
static inline void FVecCrossProduct(FVec *v0, const FVec *v1, const FVec *v2)
{
  v0->x = (v1->y * v2->z)   -   (v2->y * v1->z);
  v0->y = (v1->z * v2->x)   -   (v2->z * v1->x);
  v0->z = (v1->x * v2->y)   -   (v2->x * v1->y);
}
static inline void FVecNormalize(FVec *v0, const FVec *v1)
{
  float dist;
  dist = (v1->x * v1->x) + (v1->y * v1->y) + (v1->z * v1->z);
  dist = mysqrtf(dist);
  v0->x = v1->x / dist;
  v0->y = v1->y / dist;
  v0->z = v1->z / dist;
}


static inline void objgen_spharm_calcnormal(FVec *point1,FVec *point2,FVec *point3,FVec *output)
{
  FVec temp1,temp2,temp3;
  FVecSub(&temp1,point1,point2);
  FVecSub(&temp2,point1,point3);
  
  FVecCrossProduct(&temp3,&temp1,&temp2);
  FVecNormalize(output,&temp3);
}
static inline void objgen_spharm_Evaln(float theta, float phi, FVec *output,float dx,float dy, FVec *normal)
{
   float r,rp,rt,rtemp;
   float sinphi,cosphi,sintheta,costheta;
   float phix, thex;
   FVec t1,t2;
   phix = phi + dx;
   thex = theta + dy;

   sinphi = sinf(phi);
   cosphi = cosf(phi);
   sintheta = sinf(theta);
   costheta = cosf(theta);

   // eval posy,posx
   rt = mypowf(sinf(mf[4]*theta),mf[5]);
   rt += mypowf(cosf(mf[6]*theta),mf[7]);
   rp = mypowf(sinf(mf[0]*phi),mf[1]);
   rp += mypowf(cosf(mf[2]*phi),mf[3]);
   r = rt + rp;
   output->x = r * sinphi * costheta;
   output->y = r * cosphi;
   output->z = r * sinphi * sintheta;
   
   // eval posy+dy,posx
   rtemp = mypowf(sinf(mf[4]*thex),mf[5]);
   rtemp += mypowf(cosf(mf[6]*thex),mf[7]);
   r = rtemp + rp;
   t1.x = r * sinphi * cosf(thex);
   t1.y = r * cosphi;
   t1.z = r * sinphi * sinf(thex);

   // eval posy,posx+dx
   rtemp = mypowf(sinf(mf[0]*phix),mf[1]);
   rtemp += mypowf(cosf(mf[2]*phix),mf[3]);
   r = rt + rtemp;
   sinphi = sinf(phix);
   t2.x = r * sinphi * costheta;
   t2.y = r * cosf(phix);
   t2.z = r * sinphi * sintheta;
   // Calculate normal
   objgen_spharm_calcnormal(output,&t1,&t2,normal);
}
void objgen_spharm_setparam(float v1,float v2,float v3, float v4, float v5, float v6, float v7, float v8)
{
  mf[0] = v1;
  mf[1] = v2;
  mf[2] = v3;
  mf[3] = v4;
  mf[4] = v5;
  mf[5] = v6;
  mf[6] = v7;
  mf[7] = v8;
}
void objgen_spharm_setparamg(float v1,float v2,float v3, float v4, float v5, float v6, float v7, float v8)
{
  mft[0] = v1;
  mft[1] = v2;
  mft[2] = v3;
  mft[3] = v4;
  mft[4] = v5;
  mft[5] = v6;
  mft[6] = v7;
  mft[7] = v8;
}

void objgen_spharm_setparamt(int time,float v1,float v2,float v3, float v4, float v5, float v6, float v7, float v8)
{
  float ftime = (float)time;
  mft[0] = (v1 - mf[0]) / ftime;
  mft[1] = (v2 - mf[1]) / ftime;
  mft[2] = (v3 - mf[2]) / ftime;
  mft[3] = (v4 - mf[3]) / ftime;
  mft[4] = (v5 - mf[4]) / ftime;
  mft[5] = (v6 - mf[5]) / ftime;
  mft[6] = (v7 - mf[6]) / ftime;
  mft[7] = (v8 - mf[7]) / ftime;
}

void objgen_spharm_tick()
{
  mf[0] += mft[0];
  mf[1] += mft[1];
  mf[2] += mft[2];
  mf[3] += mft[3];
  mf[4] += mft[4];
  mf[5] += mft[5];
  mf[6] += mft[6];
  mf[7] += mft[7];
}

void objgen_spharm_setparamc(char *ptr)
{
  int count;
  for (count=0;count<8;count++)
  {
    mi[count] = (int)*(ptr+count);
    mf[count] = (float)mi[count];
  }
}


//  This is for the GU display list
static unsigned int __attribute__((aligned(16))) spharmlist[20*1024];

struct Vertex
{
	float u, v;
	unsigned int color;
  float nx,ny,nz;
	float x,y,z;
};
//  current and previous list
static struct Vertex __attribute__((aligned(16))) vertices[20*1024];
static struct Vertex __attribute__((aligned(16))) vertices2[20*1024];
static struct Vertex __attribute__((aligned(16))) preverts[1024];


#define ENABLE_GU
static FVec q;
static FVec n;
void SparmGenList(struct Vertex *vertptr,int xpoints,int ypoints,int color)
{
  int x,y;
  float dx,dy;
  float dx10,dy10;
  float dtx,dty;
  float texx,texy;
  float posx,posy;
  float dcolx,dcoly;
  float colx,coly;
  struct Vertex *verts;
  struct Vertex *prevptr;
  float ypoints2 = ypoints-2;

  dx = PI / (float)(xpoints - 1);
  dy = TWOPI / (float)ypoints2;

  dx10 = dx / 50.0f;
  dy10 = dy / 50.0f;

  dtx = 1.0f / (float)xpoints;
  dty = 1.0f / (float)ypoints2;

  dcolx = 96.0f/(float)xpoints;
  dcoly = 96.0f/(float)ypoints2;

  coly = 0.0f;
  verts = vertptr;

  for (y=0;y<ypoints;y++) {
    //  Setup memory for verts, and previous pointer
    posy = (float)y * dy;
    texy = (float)y * dty;
    prevptr = (struct Vertex *)preverts;
    colx = 0.0f;
    for (x=0;x<xpoints;x++) {
      posx = (float)x * dx;
      texx = (float)x * dtx;
      //  Evaluate the point
      objgen_spharm_Evaln(posy,posx,&q,dy10,dx10,&n);
      q.x *= 40.0f;
      q.y *= 40.0f;
      q.z *= 40.0f;
      //  Add point to our list
      verts->u  = texy;
      verts->v  = texx;
      if (color)
        verts->color = 0xff000020 | (((int)coly)<< 16) | (((int)colx)<<8);
      else
        verts->color = 0xff555555;
      verts->x = q.x;
      verts->y = q.y;
      verts->z = q.z;
      verts->nx = n.x;
      verts->ny = n.y;
      verts->nz = n.z;
      verts++;
#if 0 // slower
      memcpy(verts,prevptr,sizeof(struct Vertex));
      memcpy(prevptr,verts-1,sizeof(struct Vertex));
      verts++;
#else
      //  Add previous point to our list
      verts->u  = prevptr->u;
      verts->v  = prevptr->v;
      verts->color = prevptr->color;
      verts->x = prevptr->x;
      verts->y = prevptr->y;
      verts->z = prevptr->z;
      verts->nx = prevptr->nx;
      verts->ny = prevptr->ny;
      verts->nz = prevptr->nz;
      verts++;
      //  Save this point as previous
      prevptr->u  = texy;
      prevptr->v  = texx;
      if (color)
        prevptr->color = 0xff000020 | (((int)coly)<< 16) | (((int)colx)<<8);
      else
        prevptr->color = 0xff555555;
      prevptr->x = q.x;
      prevptr->y = q.y;
      prevptr->z = q.z;
      prevptr->nx = n.x;
      prevptr->ny = n.y;
      prevptr->nz = n.z;
#endif
      //  Move previous pointer on
      prevptr++;
      colx += dcolx;
    }
    coly += dcoly;
  }
}


extern unsigned char logo2_start[];
extern unsigned char logo3_start[];

unsigned char *logo2_temp;
unsigned char *logo3_temp;

static int rendertype;

ScePspFVector3 columns[4] = { 
      { 0.707f, 0.707f, 0.0f },   // cos(a), sin(a), tx 
      { -0.707f, 0.707f, 0.0f },  // -sin(a), cos(a), ty 
      { 0.86f, 0.5f, 0.0f }, 
      { -0.5f, 0.86f, 0.0f } 
   }; 
static ScePspFVector3 lpos = {0.0f,0.0f,1.0f};
static ScePspFVector3 lpos1 = {0.0f,1.0f,0.0f};
static ScePspFVector3 lpos2 = {1.0f,0.0f,0.0f};

// converts the image and uploads it to vram in one go
#define VRAM_OFFSET ((512*280*4)*3)
// 0x198000
static unsigned int vramaddr = 0;
unsigned char *convertimage(unsigned char *inptr,int size)
{
  // convert our raw image
  // saved as raw. no header .. interleaved and order RGB
  int x;
  unsigned char *input = inptr;
  unsigned char *output,*outptr;
  int tsize = size*size;
  if (vramaddr == 0)
    vramaddr = (0x40000000 | (u32) sceGeEdramGetAddr()) + VRAM_OFFSET;
  outptr = output = (unsigned char *)vramaddr;
  for (x=0;x<tsize;x++) {
    *(outptr++) = *(input++)/2;
    *(outptr++) = *(input++)/2;
    *(outptr++) = *(input++)/2;
    *(outptr++) = 0xff;
  }
  vramaddr += tsize * 4;
  if ((vramaddr & 0xff) != 0)
    vramaddr = (vramaddr & 0xffffff00) + 0x100;
  return output;
}

#define GU_UV_MAP     0
#define GU_PROJ_MAP   1
#define GU_ENV_MAP  2
void set_rendermode(int mode, int *color)
{
  int textured = 0;
  int lit = 0;
  int color2 = 0;
  int envmap = 0;

  //  Initial Setup
  sceGuShadeModel(1);
	sceGuEnable(GU_CLIP_PLANES);
	sceGuDisable(GU_CULL_FACE);
  sceGuDepthFunc(GU_GEQUAL);
  sceGuEnable(GU_DEPTH_TEST);
  sceGuDisable(GU_TEXTURE_2D);
  sceGuDisable(GU_LIGHTING);
  sceGuDisable(GU_LIGHT0);
  sceGuDisable(GU_LIGHT1);
  sceGuDisable(GU_LIGHT2);
  sceGuDisable(GU_LIGHT3);

  switch(mode) {
    default:
    case 0: //  Linestrips, no texture, colored and lit
      color2 = 1;
      break;
    case 1: //  Plain colors, no texture
      color2 = 1;
      break;
    case 2: //  Plain, lit, no texture
      lit = 1;
      break;
    case 3: //  Textured
      textured = 1;
      sceGuTexMapMode(GU_UV_MAP,0,0);
      break;
    case 4: //  Textured, colored, no lights
      color2 = 1;
      textured = 1;
      sceGuTexMapMode(GU_UV_MAP,0,0);
      break;
    case 5: //  Textured, lit
      textured = 1;
      lit = 1;
      sceGuTexMapMode(GU_UV_MAP,0,0);
      break;
    case 6: //  Textured, envmap
      textured = 1;
      envmap = 1;
      break;
    case 7: //  Textured, envmap
      textured = 2;
      envmap = 1;
      break;
    case 8: //  Textured, envmap, vertex colors
      color2 = 1;
      textured = 2;
      envmap = 1;
      break;
    case 9: //  Linestrips, no texture, colored and lit
      textured = 2;
      envmap = 1;
      break;
  }
  if (envmap == 1) {
    sceGuEnable(GU_LIGHTING);
    sceGuEnable(GU_LIGHT0);
    sceGuEnable(GU_LIGHT1);
    sceGuEnable(GU_LIGHT2);
    sceGuEnable(GU_LIGHT3);
    sceGuLight( 0, GU_DIRECTIONAL, GU_DIFFUSE, &columns[0] ); 
    sceGuLight( 1, GU_DIRECTIONAL, GU_DIFFUSE, &columns[1] ); 
    sceGuLight( 2, GU_DIRECTIONAL, GU_DIFFUSE, &columns[2] ); 
    sceGuLight( 3, GU_DIRECTIONAL, GU_DIFFUSE, &columns[3] ); 

    sceGuTexProjMapMode( 0 ); 
    sceGuTexMapMode( GU_ENV_MAP, 0, 1 ); // rotate envmap 45 degrees 
  }
  if (lit == 1) {
    //  lighting
    sceGuEnable(GU_LIGHTING);
    sceGuEnable(GU_LIGHT0);
    sceGuLight(0,GU_DIRECTIONAL,GU_DIFFUSE_AND_SPECULAR,&lpos);
    sceGuLightColor(0,GU_DIFFUSE,0xff00a000);
    sceGuLightColor(0,GU_SPECULAR,0xff00ff00);
    sceGuLightAtt(0,0.0f,1.0f,0.0f);

    sceGuEnable(GU_LIGHT1);
    sceGuLight(1,GU_DIRECTIONAL,GU_DIFFUSE_AND_SPECULAR,&lpos1);
    sceGuLightColor(1,GU_DIFFUSE,0xff0000a0);
    sceGuLightColor(1,GU_SPECULAR,0xff0000ff);
    sceGuLightAtt(1,0.0f,1.0f,0.0f);
  
    sceGuEnable(GU_LIGHT2);
    sceGuLight(2,GU_DIRECTIONAL,GU_DIFFUSE_AND_SPECULAR,&lpos2);
    sceGuLightColor(2,GU_DIFFUSE,0xffa00000);
    sceGuLightColor(2,GU_SPECULAR,0xffff0000);
    sceGuLightAtt(2,0.0f,1.0f,0.0f);

    sceGuSpecular(12.0f);
    sceGuAmbient(0xff101010);
  }
  if (textured != 0) {
    //  textures
    sceGuEnable(GU_TEXTURE_2D);
	  sceGuTexMode(GU_PSM_8888,0,0,0);
    if (textured == 1) sceGuTexImage(0,128,128,128,logo2_temp);
    else if (textured == 2) sceGuTexImage(0,256,256,256,logo3_temp);
	  sceGuTexFunc(GU_TFX_ADD,GU_TCC_RGB);
	  sceGuTexFilter(GU_LINEAR,GU_LINEAR);
	  sceGuTexScale(1.0f,1.0f);
	  sceGuTexOffset(0.0f,0.0f);
	  sceGuAmbientColor(0xff101010);
    sceGuTexSync();
  }
  *color = color2;
}


#define TIME_LEN 100
#define TIME_PAUSE 100
void SpharmGenTest(int rendermode)
{
  static int inited = 0;
  static int resx = 20; // up/dpwn
  static int resy = 24; // round
  static int count = TIME_LEN+TIME_PAUSE;
  static int objtype = -1;
  static int odd = 0;

  static int initial = 0;
  int color;

  if (initial == 0) {
    objgen_spharm_setparam(1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f);
    objgen_spharm_setparamg(0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f);
    initial = 1;
    sgenrand(12345);
    logo2_temp = convertimage(logo2_start,128);
    logo3_temp = convertimage(logo3_start,256);
  }


  // Start list
  sceGuStart(0,(unsigned int *)spharmlist);

  set_rendermode(rendermode,&color);

  {
    int y;
    //1int index = ((resx*2)-1);
    int index = (resx*2);
    int primtype = 4;
    if (rendermode == 0) primtype = 2;
    else if (rendermode == 9) primtype = 2;
    int index2 = index;
    if (odd) {
      for (y=1;y<resy;y++) 
        sceGumDrawArray(primtype,PSP_GEVERT_SET(3,7,3,3,0,0),index2,0,&vertices[y * index]);
    } else {
       for (y=1;y<resy;y++) 
        sceGumDrawArray(primtype,PSP_GEVERT_SET(3,7,3,3,0,0),index2,0,&vertices2[y * index]);
    }
  }
  sceKernelDcacheWritebackAll();
  sceGuFinish();

  if (count > (TIME_LEN+TIME_PAUSE)) {
    inited = 0;
  }
  if (count <= TIME_LEN ) objgen_spharm_tick();
  count++;

  if (inited == 0) {
    inited = 1;
    objtype++;
    // default
    switch(objtype)
    {
    case 0:
      break;
    case 1:
      objgen_spharm_setparamt(TIME_LEN,40.0f,1.0f,40.0f,1.0f,1.0f,1.0f,1.0f,1.0f);
      break;
    case 2:
      objgen_spharm_setparamt(TIME_LEN,20.0f,2.0f,20.0f,1.0f,1.0f,1.0f,1.0f,1.0f);
      break;
    case 3:
      objgen_spharm_setparamt(TIME_LEN,10.0f,2.0f,1.0f,2.0f,3.0f,2.0f,3.0f,2.0f);
      break;
    case 4:
      objgen_spharm_setparamt(TIME_LEN,4.0f,2.0f,2.0f,2.0f,3.0f,2.0f,3.0f,2.0f);
      break;
    case 5:
      objgen_spharm_setparamt(TIME_LEN,2.0f,4.0f,1.0f,2.0f,1.0f,2.0f,1.0f,4.0f);
      break;
    case 6:
      objgen_spharm_setparamt(TIME_LEN,1.0f,6.0f,1.0f,3.0f,1.0f,3.0f,1.0f,6.0f);
      break;
    case 7:
      objgen_spharm_setparamt(TIME_LEN,6.0f,3.0f,6.0f,3.0f,2.0f,3.0f,2.0f,3.0f);
      break;

#define RAND_MULT 30.0f
    case 8: {
      // random object
      static float t1,t2,t3,t4,t5,t6,t7,t8;
      t1 = genrand() * 6.0f;  t1 = floorf(t1);
      t2 = genrand() * 6.0f;  if (t2 == 0.0f) t2 += 0.02f;
      t3 = genrand() * 6.0f;  t3 = floorf(t3);
      t4 = genrand() * 6.0f;  if (t4 == 0.0f) t4 += 0.02f;
      t5 = genrand() * 6.0f;  t5 = floorf(t5);
      t6 = genrand() * 6.0f;  if (t6 == 0.0f) t6 += 0.02f;
      t7 = genrand() * 6.0f;  t7 = floorf(t7);
      t8 = genrand() * 6.0f;  if (t8 == 0.0f) t8 += 0.02f;

      objgen_spharm_setparamt(TIME_LEN,t1,t2,t3,t4,t5,t6,t7,t8);
      objtype--;// make sure we end up back in same spot
      //objtype = 6; // make sure we end up back in same spot
            } break;
    default:  // none found, so move to next one, and trigger re-gen
      objtype == 0;
      inited = 0;
      break;
    }
    count = 0;
  }

  if (odd) {
    SparmGenList(vertices2,resx,resy,color);
    odd = 0;
  }  else {
    SparmGenList(vertices,resx,resy,color);
    odd = 1;
  }
}

