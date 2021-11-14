/* arpa/inet.h - Functions for converting IP addresses between strings and numbers */

#ifndef _ARPA_INET_H_
#define _ARPA_INET_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <netinet/in.h>

in_addr_t sceNetInetInetAddr(const char *ip);
int sceNetInetInetAton(const char *ip, struct in_addr *in);
const char* sceNetInetInetNtop(int af, const void *src, char *dst, socklen_t cnt);
int sceNetInetInetPton(int af, const char *src, void *dst);

char *inet_ntoa(struct in_addr in);
#define inet_addr sceNetInetInetAddr
#define inet_aton sceNetInetInetAton
#define inet_ntop sceNetInetInetNtop
#define inet_pton sceNetInetInetPton

#ifdef __cplusplus
}
#endif
#endif /* _ARPA_INET_H_ */
