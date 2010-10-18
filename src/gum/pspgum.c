/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * Copyright (c) 2005 Jesper Svennevid
 */

#include "gumInternal.h"

#include <string.h>
#include <math.h>

#ifdef F_gumInit
void gumInit(void)
{
}
#endif

#ifdef F_gumCrossProduct
void gumCrossProduct(ScePspFVector3* r, const ScePspFVector3* a, const ScePspFVector3* b)
{
	r->x = (a->y * b->z) - (a->z * b->y);
	r->y = (a->z * b->x) - (a->x * b->z);
	r->z = (a->x * b->y) - (a->y * b->x);
}
#endif

#ifdef F_gumDotProduct
float gumDotProduct(const ScePspFVector3* a, const ScePspFVector3* b)
{
	return (a->x * b->x) + (a->y * b->y) + (a->z * b->z);
}
#endif

#ifdef F_gumFastInverse
void gumFastInverse(ScePspFMatrix4* m, const ScePspFMatrix4* a)
{
	ScePspFMatrix4 t;
	ScePspFVector3 negPos = {-a->w.x,-a->w.y,-a->w.z};

	// transpose rotation

	t.x.x = a->x.x;
	t.x.y = a->y.x;
	t.x.z = a->z.x;
	t.x.w = 0;

	t.y.x = a->x.y;
	t.y.y = a->y.y;
	t.y.z = a->z.y;
	t.y.w = 0;

	t.z.x = a->x.z;
	t.z.y = a->y.z;
	t.z.z = a->z.z;
	t.z.w = 0;

	// compute inverse position

	t.w.x = gumDotProduct(&negPos,(const ScePspFVector3*)&a->x);
	t.w.y = gumDotProduct(&negPos,(const ScePspFVector3*)&a->y);
	t.w.z = gumDotProduct(&negPos,(const ScePspFVector3*)&a->z);
	t.w.w = 1;

	gumLoadMatrix(m,&t);
}
#endif

#ifdef F_gumFullInverse
void gumFullInverse(ScePspFMatrix4* m, const ScePspFMatrix4* a)
{
	ScePspFMatrix4 t;
	float d0,d1,d2,d3;
	float d;

	d0 = a->y.y*a->z.z*a->w.w + a->y.z*a->z.w*a->w.y + a->y.w*a->z.y*a->w.z - a->w.y*a->z.z*a->y.w - a->w.z*a->z.w*a->y.y - a->w.w*a->z.y*a->y.z;
	d1 = a->y.x*a->z.z*a->w.w + a->y.z*a->z.w*a->w.x + a->y.w*a->z.x*a->w.z - a->w.x*a->z.z*a->y.w - a->w.z*a->z.w*a->y.x - a->w.w*a->z.x*a->y.z;
	d2 = a->y.x*a->z.y*a->w.w + a->y.y*a->z.w*a->w.x + a->y.w*a->z.x*a->w.y - a->w.x*a->z.y*a->y.w - a->w.y*a->z.w*a->y.x - a->w.w*a->z.x*a->y.y;
	d3 = a->y.x*a->z.y*a->w.z + a->y.y*a->z.z*a->w.x + a->y.z*a->z.x*a->w.y - a->w.x*a->z.y*a->y.z - a->w.y*a->z.z*a->y.x - a->w.z*a->z.x*a->y.y;
	d = a->x.x*d0 - a->x.y * d1 + a->x.z * d2 - a->x.w * d3;

	if (fabsf(d) < GUM_EPSILON)
	{
		gumLoadIdentity(m);
		return;
	}

	d = 1.0f / d;

	t.x.x =  d * d0;
	t.x.y = -d * (a->x.y*a->z.z*a->w.w + a->x.z*a->z.w*a->w.y + a->x.w*a->z.y*a->w.z - a->w.y*a->z.z*a->x.w - a->w.z*a->z.w*a->x.y - a->w.w*a->z.y*a->x.z);
	t.x.z =  d * (a->x.y*a->y.z*a->w.w + a->x.z*a->y.w*a->w.y + a->x.w*a->y.y*a->w.z - a->w.y*a->y.z*a->x.w - a->w.z*a->y.w*a->x.y - a->w.w*a->y.y*a->x.z);
	t.x.w = -d * (a->x.y*a->y.z*a->z.w + a->x.z*a->y.w*a->z.y + a->x.w*a->y.y*a->z.z - a->z.y*a->y.z*a->x.w - a->z.z*a->y.w*a->x.y - a->z.w*a->y.y*a->x.z);
	
	t.y.x = -d * d1;
	t.y.y =  d * (a->x.x*a->z.z*a->w.w + a->x.z*a->z.w*a->w.x + a->x.w*a->z.x*a->w.z - a->w.x*a->z.z*a->x.w - a->w.z*a->z.w*a->x.x - a->w.w*a->z.x*a->x.z);
	t.y.z = -d * (a->x.x*a->y.z*a->w.w + a->x.z*a->y.w*a->w.x + a->x.w*a->y.x*a->w.z - a->w.x*a->y.z*a->x.w - a->w.z*a->y.w*a->x.x - a->w.w*a->y.x*a->x.z);
	t.y.w =  d * (a->x.x*a->y.z*a->z.w + a->x.z*a->y.w*a->z.x + a->x.w*a->y.x*a->z.z - a->z.x*a->y.z*a->x.w - a->z.z*a->y.w*a->x.x - a->z.w*a->y.x*a->x.z);
	
	t.z.x =  d * d2;
	t.z.y = -d * (a->x.x*a->z.y*a->w.w + a->x.y*a->z.w*a->w.x + a->x.w*a->z.x*a->w.y - a->w.x*a->z.y*a->x.w - a->w.y*a->z.w*a->x.x - a->w.w*a->z.x*a->x.y);
	t.z.z =  d * (a->x.x*a->y.y*a->w.w + a->x.y*a->y.w*a->w.x + a->x.w*a->y.x*a->w.y - a->w.x*a->y.y*a->x.w - a->w.y*a->y.w*a->x.x - a->w.w*a->y.x*a->x.y);
	t.z.w = -d * (a->x.x*a->y.y*a->z.w + a->x.y*a->y.w*a->z.x + a->x.w*a->y.x*a->z.y - a->z.x*a->y.y*a->x.w - a->z.y*a->y.w*a->x.x - a->z.w*a->y.x*a->x.y);
	
	t.w.x = -d * d3;
	t.w.y =  d * (a->x.x*a->z.y*a->w.z + a->x.y*a->z.z*a->w.x + a->x.z*a->z.x*a->w.y - a->w.x*a->z.y*a->x.z - a->w.y*a->z.z*a->x.x - a->w.z*a->z.x*a->x.y);
	t.w.z = -d * (a->x.x*a->y.y*a->w.z + a->x.y*a->y.z*a->w.x + a->x.z*a->y.x*a->w.y - a->w.x*a->y.y*a->x.z - a->w.y*a->y.z*a->x.x - a->w.z*a->y.x*a->x.y);
	t.w.w =  d * (a->x.x*a->y.y*a->z.z + a->x.y*a->y.z*a->z.x + a->x.z*a->y.x*a->z.y - a->z.x*a->y.y*a->x.z - a->z.y*a->y.z*a->x.x - a->z.z*a->y.x*a->x.y);

	gumLoadMatrix(m,&t);
}
#endif

#ifdef F_gumLoadIdentity
void gumLoadIdentity(ScePspFMatrix4* m)
{
  unsigned int i;

  memset(m,0,sizeof(ScePspFMatrix4));

  for (i = 0; i < 4; ++i)
    ((float*)m)[(i << 2)+i] = 1.0f;
}
#endif

#ifdef F_gumLoadMatrix
void gumLoadMatrix(ScePspFMatrix4* r, const ScePspFMatrix4* a)
{
  memcpy(r,a,sizeof(ScePspFMatrix4));
}
#endif

#ifdef F_gumLookAt
void gumLookAt(ScePspFMatrix4* m, ScePspFVector3* eye, ScePspFVector3* center, ScePspFVector3* up)
{
	ScePspFVector3 forward, side, lup,ieye;
	ScePspFMatrix4 t;

	forward.x = center->x - eye->x;
	forward.y = center->y - eye->y;
	forward.z = center->z - eye->z;

	gumNormalize(&forward);

	gumCrossProduct(&side,&forward,up);
	gumNormalize(&side);

	gumCrossProduct(&lup,&side,&forward);
	gumLoadIdentity(&t);

	t.x.x = side.x;
	t.y.x = side.y;
	t.z.x = side.z;

	t.x.y = lup.x;
	t.y.y = lup.y;
	t.z.y = lup.z;

	t.x.z = -forward.x;
	t.y.z = -forward.y;
	t.z.z = -forward.z;

	ieye.x = -eye->x; ieye.y = -eye->y; ieye.z = -eye->z;
	gumMultMatrix(m,m,&t);
	gumTranslate(m,&ieye);
}
#endif

#ifdef F_gumMultMatrix
void gumMultMatrix(ScePspFMatrix4* result, const ScePspFMatrix4* a, const ScePspFMatrix4* b)
{
	ScePspFMatrix4 t;
	unsigned int i,j,k;
	const float* ma = (const float*)a;
	const float* mb = (const float*)b;
	float* mr = (float*)&t;

	for (i = 0; i < 4; ++i)
	{
		for (j = 0; j < 4; ++j)
		{
			float v = 0.0f;
			for (k = 0; k < 4; ++k)
				v += ma[(k << 2)+j] * mb[(i << 2)+k];
			mr[(i << 2)+j] = v;
                }
        }

	memcpy(result,&t,sizeof(ScePspFMatrix4));
}
#endif

#ifdef F_gumNormalize
void gumNormalize(ScePspFVector3* v)
{
	float l = sqrtf((v->x*v->x) + (v->y*v->y) + (v->z*v->z));
	if (l > GUM_EPSILON)
	{
		float il = 1.0f / l;
		v->x *= il; v->y *= il; v->z *= il;
	}
}
#endif

#ifdef F_gumOrtho
void gumOrtho(ScePspFMatrix4* m, float left, float right, float bottom, float top, float near, float far)
{
	ScePspFMatrix4 t;
	float dx = right-left, dy = top-bottom, dz = far-near;

	gumLoadIdentity(&t);

	t.x.x = 2.0f / dx;
	t.w.x = -(right + left) / dx;
	t.y.y = 2.0f / dy;
	t.w.y = -(top + bottom) / dy;
	t.z.z = -2.0f / dz;
	t.w.z = -(far + near) / dz;

	gumMultMatrix(m,m,&t);
}
#endif

#ifdef F_gumPerspective
void gumPerspective(ScePspFMatrix4* m, float fovy, float aspect, float near, float far)
{
	ScePspFMatrix4 t;
	float angle = (fovy / 2) * (GU_PI/180.0f);
	float cotangent = cosf(angle) / sinf(angle);
	float delta_z = near-far;

	gumLoadIdentity(&t);

	t.x.x = cotangent / aspect;
	t.y.y = cotangent;
	t.z.z = (far + near) / delta_z; // -(far + near) / delta_z
	t.w.z = 2.0f * (far * near) / delta_z; // -2 * (far * near) / delta_z
	t.z.w = -1.0f;
	t.w.w = 0.0f;

	gumMultMatrix(m,m,&t);
}
#endif

#ifdef F_gumRotateX
void gumRotateX(ScePspFMatrix4* m, float angle)
{
	ScePspFMatrix4 t;

	float c = cosf(angle);
	float s = sinf(angle);

	gumLoadIdentity(&t);

	t.y.y = c;
	t.y.z = s;
	t.z.y = -s;
	t.z.z = c;

	gumMultMatrix(m,m,&t);
}
#endif

#ifdef F_gumRotateY
void gumRotateY(ScePspFMatrix4* m, float angle)
{
	ScePspFMatrix4 t;

	float c = cosf(angle);
	float s = sinf(angle);

	gumLoadIdentity(&t);

	t.x.x = c;
	t.x.z = -s;
	t.z.x = s;
	t.z.z = c;

	gumMultMatrix(m,m,&t);
}
#endif

#ifdef F_gumRotateZ
void gumRotateZ(ScePspFMatrix4* m, float angle)
{
	ScePspFMatrix4 t;

	float c = cosf(angle);
	float s = sinf(angle);

	gumLoadIdentity(&t);

	t.x.x = c;
	t.x.y = s;
	t.y.x = -s;
	t.y.y = c;

	gumMultMatrix(m,m,&t);
}
#endif

#ifdef F_gumRotateXYZ
void gumRotateXYZ(ScePspFMatrix4* m, const ScePspFVector3* v)
{
	gumRotateX(m,v->x);
	gumRotateY(m,v->y);
	gumRotateZ(m,v->z);
}
#endif

#ifdef F_gumRotateZYX
void gumRotateZYX(ScePspFMatrix4* m, const ScePspFVector3* v)
{
	gumRotateZ(m,v->z);
	gumRotateY(m,v->y);
	gumRotateX(m,v->x);
}
#endif

#ifdef F_gumScale
void gumScale(ScePspFMatrix4* m, const ScePspFVector3* v)
{
	float x,y,z;

	x = v->x; y = v->y; z = v->z;
	m->x.x *= x; m->x.y *= x; m->x.z *= x;
	m->y.x *= y; m->y.y *= y; m->y.z *= y;
	m->z.x *= z; m->z.y *= z; m->z.z *= z;
}
#endif

#ifdef F_gumTranslate
void gumTranslate(ScePspFMatrix4* m, const ScePspFVector3* v)
{
	ScePspFMatrix4 t;

	gumLoadIdentity(&t);
	t.w.x = v->x;
	t.w.y = v->y;
	t.w.z = v->z;

	gumMultMatrix(m,m,&t);
}
#endif

#ifdef F_sceGumDrawArray
void sceGumDrawArray(int prim, int vtype, int count, const void* indices, const void* vertices)
{
  sceGumUpdateMatrix();
  sceGuDrawArray(prim,vtype,count,indices,vertices);
}
#endif

#ifdef F_sceGumDrawArrayN
void sceGumDrawArrayN(int prim, int vtype, int count, int a3, const void* indices, const void* vertices)
{
  sceGumUpdateMatrix();
  sceGuDrawArrayN(prim,vtype,count,a3,indices,vertices);
}
#endif

#ifdef F_sceGumDrawBezier
void sceGumDrawBezier(int vtype, int ucount, int vcount, const void* indices, const void* vertices)
{
  sceGumUpdateMatrix();
  sceGuDrawBezier(vtype,ucount,vcount,indices,vertices);
}
#endif

#ifdef F_sceGumDrawSpline
void sceGumDrawSpline(int vtype, int ucount, int vcount, int uedge, int vedge, const void* indices, const void* vertices)
{
  sceGumUpdateMatrix();
  sceGuDrawSpline(vtype,ucount,vcount,uedge,vedge,indices,vertices);
}
#endif

#ifdef F_sceGumFastInverse
void sceGumFastInverse()
{
	gumFastInverse(gum_current_matrix,gum_current_matrix);
	gum_current_matrix_update = 1;
}
#endif

#ifdef F_sceGumFullInverse
void sceGumFullInverse()
{
	gumFullInverse(gum_current_matrix,gum_current_matrix);
	gum_current_matrix_update = 1;
}
#endif

#ifdef F_sceGumLoadIdentity
void sceGumLoadIdentity(void)
{
	gumLoadIdentity(gum_current_matrix);
	gum_current_matrix_update = 1;
}
#endif

#ifdef F_sceGumLoadMatrix
void sceGumLoadMatrix(const ScePspFMatrix4* m)
{
	memcpy(gum_current_matrix,m,sizeof(ScePspFMatrix4));
	gum_current_matrix_update = 1;
}
#endif

#ifdef F_sceGumLookAt
void sceGumLookAt(ScePspFVector3* eye, ScePspFVector3* center, ScePspFVector3* up)
{
	gumLookAt(gum_current_matrix,eye,center,up);
	gum_current_matrix_update = 1;
}
#endif

#ifdef F_sceGumMatrixMode
void sceGumMatrixMode(int mode)
{
	// switch stack
	gum_matrix_update[gum_current_mode] = gum_current_matrix_update;
	gum_stack_depth[gum_current_mode] = gum_current_matrix;
	gum_current_matrix = gum_stack_depth[mode];
	gum_current_mode = mode;
	gum_current_matrix_update = gum_matrix_update[gum_current_mode];
}
#endif

#ifdef F_sceGumMultMatrix
void sceGumMultMatrix(const ScePspFMatrix4* m)
{
	gumMultMatrix(gum_current_matrix,gum_current_matrix,m);  
	gum_current_matrix_update = 1;
}
#endif

#ifdef F_sceGumOrtho
void sceGumOrtho(float left, float right, float bottom, float top, float near, float far)
{
	register ScePspFMatrix4* t __asm("a0") = GUM_ALIGNED_MATRIX();
	float dx = right-left, dy = top-bottom, dz = far-near;

	memset(t,0,sizeof(ScePspFMatrix4));

	t->x.x = 2.0f / dx;
	t->w.x = -(right + left) / dx;
	t->y.y = 2.0f / dy;
	t->w.y = -(top + bottom) / dy;
	t->z.z = -2.0f / dz;
	t->w.z = -(far + near) / dz;
	t->w.w = 1.0f;

	sceGumMultMatrix(t);
}
#endif

#ifdef F_sceGumPerspective
void sceGumPerspective(float fovy, float aspect, float near, float far)
{
	float angle = (fovy / 2) * (GU_PI/180.0f);
	float cotangent = cosf(angle) / sinf(angle);
	float delta_z = near-far;
	register ScePspFMatrix4* t __asm("a0") = GUM_ALIGNED_MATRIX();

	memset(t,0,sizeof(ScePspFMatrix4));
	t->x.x = cotangent / aspect;
	t->y.y = cotangent;
	t->z.z = (far + near) / delta_z; // -(far + near) / delta_z
	t->w.z = 2.0f * (far * near) / delta_z; // -2 * (far * near) / delta_z
	t->z.w = -1.0f;
	t->w.w = 0.0f;

	sceGumMultMatrix(t);
}
#endif

#ifdef F_sceGumPopMatrix
void sceGumPopMatrix(void)
{
	gum_current_matrix--;
	gum_current_matrix_update = 1;
}
#endif

#ifdef F_sceGumPushMatrix
void sceGumPushMatrix(void)
{
	memcpy(gum_current_matrix+1,gum_current_matrix,sizeof(ScePspFMatrix4));
	gum_current_matrix++;
}
#endif

#ifdef F_sceGumRotateX
void sceGumRotateX(float angle)
{
	gumRotateX(gum_current_matrix,angle);
	gum_current_matrix_update = 1;
}
#endif

#ifdef F_sceGumRotateXYZ
void sceGumRotateXYZ(const ScePspFVector3* v)
{
	sceGumRotateX(v->x);
	sceGumRotateY(v->y);
	sceGumRotateZ(v->z);
}
#endif

#ifdef F_sceGumRotateY
void sceGumRotateY(float angle)
{
	gumRotateY(gum_current_matrix,angle);
	gum_current_matrix_update = 1;
}
#endif

#ifdef F_sceGumRotateZ
void sceGumRotateZ(float angle)
{
	gumRotateZ(gum_current_matrix,angle);
	gum_current_matrix_update = 1;
}
#endif

#ifdef F_sceGumRotateZYX
void sceGumRotateZYX(const ScePspFVector3* v)
{
	sceGumRotateZ(v->z);
	sceGumRotateY(v->y);
	sceGumRotateX(v->x);
}
#endif

#ifdef F_sceGumScale
void sceGumScale(const ScePspFVector3* v)
{
	gumScale(gum_current_matrix,v);
	gum_current_matrix_update = 1;
}
#endif

#ifdef F_sceGumStoreMatrix
void sceGumStoreMatrix(ScePspFMatrix4* m)
{
	memcpy(m,gum_current_matrix,sizeof(ScePspFMatrix4));
}
#endif

#ifdef F_sceGumTranslate
void sceGumTranslate(const ScePspFVector3* v)
{
	gumTranslate(gum_current_matrix,v);
	gum_current_matrix_update = 1;
}
#endif

#ifdef F_sceGumUpdateMatrix
void sceGumUpdateMatrix(void)
{
	gum_stack_depth[gum_current_mode] = gum_current_matrix;
	gum_matrix_update[gum_current_mode] = gum_current_matrix_update;
	gum_current_matrix_update = 0;

	unsigned int i;
	for (i = 0; i < 4; ++i)
	{
		if (gum_matrix_update[i])
		{
			sceGuSetMatrix(i,gum_stack_depth[i]);
			gum_matrix_update[i] = 0;
		}
	}
}
#endif
