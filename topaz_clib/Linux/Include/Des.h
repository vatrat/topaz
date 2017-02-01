

/* In des.c: */
void dessetkey(unsigned long [16][2],unsigned char *);
void endes(unsigned long [16][2],unsigned char *);
void dedes(unsigned long [16][2],unsigned char *);
extern unsigned long Spbox[8][64];



/* C code only in portable version */

/* Fetch 8 bytes from user's buffer into "left" and "right"
 * in big-endian order
 */
#define	GETBLOCK(block,left,right)\
	left = ((unsigned long)block[0] << 24) | ((unsigned long)block[1] << 16) | ((unsigned long)block[2] << 8) | (unsigned long)block[3];\
	right = ((unsigned long)block[4] << 24) | ((unsigned long)block[5] << 16) | ((unsigned long)block[6] << 8) |	(unsigned long)block[7];

/* Put 8 bytes back into user's buffer in big-endian order */
#define	PUTBLOCK(block,left,right)\
	*block++ = (unsigned char)(left >> 24);\
	*block++ = (unsigned char)(left >> 16);\
	*block++ = (unsigned char)(left >> 8);\
	*block++ = (unsigned char)(left);\
	*block++ = (unsigned char)(right >> 24);\
	*block++ = (unsigned char)(right >> 16);\
	*block++ = (unsigned char)(right >> 8);\
	*block = (unsigned char)(right);

/* Richard Outerbridge's clever initial permutation algorithm
 * (see Schneier p 478)	
 *
 * The convention here is to rotate each half left by 1 bit, i.e.,
 * so that "left" contains permuted input bits 2, 3, 4, ... 1 and
 * "right" contains 33, 34, 35, ... 32 (using origin-1 numbering as
 * in the FIPS). This allows us to avoid one of the two
 * rotates that would otherwise be required in each of the 16 rounds.
 */
#define IPERM(left,right){\
	unsigned long work;\
\
	work = ((left >> 4) ^ right) & 0x0f0f0f0f;\
	right ^= work;\
	left ^= work << 4;\
	work = ((left >> 16) ^ right) & 0xffff;\
	right ^= work;\
	left ^= work << 16;\
	work = ((right >> 2) ^ left) & 0x33333333;\
	left ^= work;\
	right ^= (work << 2);\
	work = ((right >> 8) ^ left) & 0xff00ff;\
	left ^= work;\
	right ^= (work << 8);\
	right = (right << 1) | (right >> 31);\
	work = (left ^ right) & 0xaaaaaaaa;\
	left ^= work;\
	right ^= work;\
	left = (left << 1) | (left >> 31);\
}

/* Inverse permutation, also from Outerbridge via Schneier */
#define	FPERM(left,right){\
	unsigned long work;\
\
	right = (right << 31) | (right >> 1);\
	work = (left ^ right) & 0xaaaaaaaa;\
	left ^= work;\
	right ^= work;\
	left = (left >> 1) | (left  << 31);\
	work = ((left >> 8) ^ right) & 0xff00ff;\
	right ^= work;\
	left ^= work << 8;\
	work = ((left >> 2) ^ right) & 0x33333333;\
	right ^= work;\
	left ^= work << 2;\
	work = ((right >> 16) ^ left) & 0xffff;\
	left ^= work;\
	right ^= work << 16;\
	work = ((right >> 4) ^ left) & 0x0f0f0f0f;\
	left ^= work;\
	right ^= work << 4;\
}

/* Primitive function F.
 * Input is r, subkey array in keys, output is XORed into l.
 * Each round consumes eight 6-bit subkeys, one for
 * each of the 8 S-boxes, 2 longs for each round.
 * Each long contains four 6-bit subkeys, each taking up a byte.
 * The first long contains, from high to low end, the subkeys for
 * S-boxes 1, 3, 5 & 7; the second contains the subkeys for S-boxes
 * 2, 4, 6 & 8 (using the origin-1 S-box numbering in the standard,
 * not the origin-0 numbering used elsewhere in this code)
 * See comments elsewhere about the pre-rotated values of r and Spbox.
 */
#define	F(l,r,s){\
	register unsigned long work;\
\
	work = (((r >> 4) | (r << 28)) ^ *keys++);\
	l ^= Spbox[6][work & 0x3f];\
	l ^= Spbox[4][(work >> 8) & 0x3f];\
	l ^= Spbox[2][(work >> 16) & 0x3f];\
	l ^= Spbox[0][(work >> 24) & 0x3f];\
	work = (r ^ *keys);\
	l ^= Spbox[7][work & 0x3f];\
	l ^= Spbox[5][(work >> 8) & 0x3f];\
	l ^= Spbox[3][(work >> 16) & 0x3f];\
	l ^= Spbox[1][(work >> 24) & 0x3f];\
	/* s is either +1 or -3 */\
	keys += s;\
}

#ifdef	UseAssemblyCode	/* CPU386 is defined */

/* Start of fast assembler code for 386/486 */

/* Richard Outerbridge's clever initial permutation
 * algorithm, translated to assembler (see Schneier p 478)	
 * Uses eax as scratch
 *
 * The convention here is *different* from the C version. The final values
 * of "left" and "right" are rotated left by two additional bits so
 * we can avoid the two shifts that would otherwise be required in each
 * round to convert a S-box input to a memory offset for Spbox[].
 */
#define IPERM(left,right)\
	asm {\
	/* work = ((left >> 4) ^ right) & 0x0f0f0f0f */\
	mov eax,left;\
	shr eax,4;\
	xor eax,right;\
	and eax,0f0f0f0fh;\
\
	xor right,eax;	/* right ^= work */\
\
	/* left ^= work << 4 */\
	shl eax,4;\
	xor left,eax;\
\
	/* work = ((left >> 16) ^ right) & 0xffff */\
	mov eax,left;\
	shr eax,16;\
	xor eax,right;\
	and eax,0ffffh;\
\
	xor right,eax;	/* right ^= work */\
\
	/* left ^= work << 16 */\
	shl eax,16;\
	xor left,eax;\
\
	/* work = ((right >> 2) ^ left) & 0x33333333 */\
	mov eax,right;\
	shr eax,2;\
	xor eax,left;\
	and eax,033333333h;\
\
	/* left ^= work */\
	xor left,eax;\
	shl eax,2;\
\
	xor right,eax;	/* right ^= (work << 2) */\
\
	/* work = ((right >> 8) ^ left) & 0xff00ff */\
	mov eax,right;\
	shr eax,8;\
	xor eax,left;\
	and eax,0ff00ffh;\
\
	xor left,eax;	/* left ^= work */\
\
	/* right ^= (work << 8) */\
	shl eax,8;\
	xor right,eax;\
\
	rol right,1;	/* right <<<= 1 */\
\
	/* work = (left ^ right) & 0xaaaaaaaa */\
	mov eax,left;\
	xor eax,right;\
	and eax,0aaaaaaaah;\
\
	xor left,eax;	/* left ^= work */\
	xor right,eax;	/* right ^= work */\
	rol left,3;\
	rol right,2;\
}

/* Inverse permutation
 * Uses eax as scratch
 */
#define	FPERM(left,right)\
	asm {\
	ror left,2;\
	ror right,3;\
\
	/* work = (left ^ right) & 0xaaaaaaaa */\
	mov eax,left;\
	xor eax,right;\
	and eax,0aaaaaaaah;\
\
	xor left,eax;	/* left ^= work */\
	xor right,eax;	/* right ^= work */\
	ror left,1;	/* left >>>= 1 */\
\
	/* work = (left >> 8) ^ right) & 0xff00ff */\
	mov eax,left;\
	shr eax,8;\
	xor eax,right;\
	and eax,0ff00ffh;\
\
	xor right,eax;	/* right ^= work */\
\
	/* left ^= work << 8 */\
	shl eax,8;\
	xor left,eax;\
\
	/* work = ((left >> 2) ^ right) & 0x33333333 */\
	mov eax,left;\
	shr eax,2;\
	xor eax,right;\
	and eax,33333333h;\
\
	xor right,eax;	/* right ^= work */\
\
	/* left ^= work << 2 */\
	shl eax,2;\
	xor left,eax;\
\
	/* work = ((right >> 16) ^ left) & 0xffff */\
	mov eax,right;\
	shr eax,16;\
	xor eax,left;\
	and eax,0ffffh;\
\
	xor left,eax;	/* left ^= work */\
\
	/* right ^= work << 16 */\
	shl eax,16;\
	xor right,eax;\
\
	/* work = ((right >> 4) ^ left) & 0x0f0f0f0f */\
	mov eax,right;\
	shr eax,4;\
	xor eax,left;\
	and eax,0f0f0f0fh;\
\
	xor left,eax;	/* left ^= work */\
\
	/* right ^= work << 4 */\
	shl eax,4;\
	xor right,eax;\
}

/* Primitive function F. Input is r, output is XORed into l.
 * Subkeys are taken from the array pointed to by es:si.
 * eax and ebx are scratch, ebx is assumed to be initialized to 0.
 *
 * There's an important difference between this version and the portable C
 * version: here, each subkey is LEFT JUSTIFIED within a byte, i.e., left
 * shifted 2 bits. This lets us avoid the two left shifts we'd otherwise have
 * to do here to get double word indexes for addressing each S-box (an array
 * of 4-byte longs). Several other places in the code take this into account:
 *
 * the initial permutation left-shifts r and l by two additional bits
 * (for a total of three);
 *
 * the values in Spbox[] generated by gensp.c are also shifted left by
 * two additional bits (for a total of three);
 *
 * setkey() left shifts each key schedule byte left by two places.
 *
 * Since this code is executed 16 times in every DES encrypt or decrypt
 * operation, it is very time-critical. It has been very heavily
 * optimized for the 486.
 */
#define	F(l,r,s)\
	asm {\
	/* eax = ((r >>> 4) ^ *keys++) & 0xfcfcfcfc */\
	mov eax,r;\
	ror eax,4;\
	xor eax,[es:si];\
	add si,4;\
	and eax,0fcfcfcfch;\
\
	/* eax now contains four S-box offsets all ready for use */\
	mov bl,al;\
	xor l,dword ptr Spbox[bx+6*256] ; /* l ^= Spbox[6][al] */\
	mov bl,ah;\
	xor l,dword ptr Spbox[bx+4*256] ; /* l ^= Spbox[4][al] */\
	ror eax,16;\
	mov bl,al;\
	xor l,dword ptr Spbox[bx+2*256] ; /* l ^= Spbox[2][al] */\
	mov bl,ah;\
	xor l,dword ptr Spbox[bx+0*256] ; /* l ^= Spbox[0][al] */\
\
	/* eax = (r ^ *keys) & 0xfcfcfcfc */\
	mov eax,r;\
	xor eax,[es:si];\
	/* keys++ or keys -= 3 depending on value of s */\
	add si,s;\
	and eax,0fcfcfcfch;\
\
	/* eax now contains four S-box offsets all ready for use */\
	mov bl,al;\
 	xor l,dword ptr Spbox[bx+7*256] ; /* l ^= Spbox[7][al] */\
	mov bl,ah;\
 	xor l,dword ptr Spbox[bx+5*256] ; /* l ^= Spbox[5][al] */\
	ror eax,16;\
	mov bl,al;\
 	xor l,dword ptr Spbox[bx+3*256] ; /* l ^= Spbox[3][al] */\
	mov bl,ah;\
 	xor l,dword ptr Spbox[bx+1*256] ; /* l ^= Spbox[1][al] */\
}

/* Fetch 8 bytes from user's buffer in "block" and place in ecx and edx,
 * in big-endian order. Uses es, si.
 */
#define	GETBLOCK(block)\
	asm {\
	/* There's a very nice BSWAP\
	 * instruction that executes in only 1 cycle, but it is only\
	 * available on the 486. :-(\
	 */\
	les si,block;		/* es:si = block */\
	mov ecx,[es:si];	/* ecx = *block++ */\
	add si,4;\
	xchg cl,ch;		/* bswap ecx */\
	rol ecx,16;\
	xchg cl,ch;\
	mov edx,[es:si];	/* edx = *block */\
	xchg dl,dh;		/* bswap edx */\
	rol edx,16;\
	xchg dl,dh;\
	}

/* Write ecx and edx into user's buffer "block" in big-endian order
 * Uses es, si
 */
#define PUTBLOCK(block)\
	asm {\
	les si,block;\
	xchg dl,dh;		/* bswap edx */\
	rol edx,16;\
	xchg dl,dh;\
	mov [es:si],edx;\
	add si,4;\
	xchg cl,ch;		/* bswap ecx */\
	rol ecx,16;\
	xchg cl,ch;\
	mov [es:si],ecx;\
	}
#endif

