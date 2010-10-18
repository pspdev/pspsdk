#ifndef common_vram_h
#define common_vram_h

#ifdef __cplusplus
extern "C" {
#endif

/*
	The following are a few helperfunctions to help manage vram in gu-examples.
	Do not use for your own code, it's better you manage it in your own way.
*/

/* make a static allocation of vram memory and return pointer relative to vram start */
void* getStaticVramBuffer(unsigned int width, unsigned int height, unsigned int psm);
/* make a static allocation of vram memory and return absolute pointer */
void* getStaticVramTexture(unsigned int width, unsigned int height, unsigned int psm);

// the following is not yet implemented
/*
void beginDynamicVramFrame();
void endDynamicVramFrame();

void* getDynamicVramBuffer(unsigned int width, unsigned int height, unsigned int psm);
void* getDynamicVramTexture(unsigned int width, unsigned int height, unsigned int psm);
*/

#ifdef __cplusplus
}
#endif

#endif
