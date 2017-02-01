

#ifndef MD5_H
#define MD5_H


typedef unsigned long word32;
typedef	unsigned char byte;

#define	BCOPY( s, d, n )	memcpy( d, s, n )
#define	BZERO( d, n )		memset( d, 0, n )
#define BCMP( s, d, n )		memcmp( s, d, n )

struct xMD5Context {
	word32 buf[4];
	word32 bytes[2];
	word32 in[16];
};

#ifdef __cplusplus
extern "C" {
#endif

void xMD5Init(struct xMD5Context *context);
void xMD5Update(struct xMD5Context *context, byte const *buf, unsigned len);
void xMD5Final(byte digest[16], struct xMD5Context *context);
void xMD5Transform(word32 buf[4], word32 const in[16]);

void byteSwap(word32 *buf, unsigned words);
#ifdef __cplusplus
}
#endif

#endif /* !MD5_H */
