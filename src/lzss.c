#include <lzss.h>
#include <string.h>
#include <stdlib.h>

/*
	LZSS compression variation
	A flag (byte) that determines if the next 8 bytes are encoded or not
	When all 8 are done a new flag set

	The full understanding of this algorithm wouln't be possible without
	Mr. Michael Dipperstein
*/

int decompress_lzss(uint8_t *dst, uint8_t *src, uint32_t dstlen) {
	uint16_t dictionary_size = 4096;

	uint8_t* dictionary = malloc(dictionary_size);
	if (dictionary == NULL) {
		return -1;
	}

	uint32_t srcIndex = 0;     /* index into src array */
	uint32_t dstIndex = 0;     /* index into dst array */
	uint32_t dictIndex = 0;    /* index into sliding window dictionary */

	do {
		/* flags are the encoded/not encoded bits for the next 8 symbols */
		uint8_t flags = src[srcIndex++];

		for (int i = 0; i < 8; i++) {
			if ((flags & 1) != 0) {
				/* unencoded byte */
				uint8_t unecoded;
				dictionary[dictIndex++ % dictionary_size] = (unecoded = src[srcIndex++]);
				dst[dstIndex++] = unecoded;
			} else {
				/* encoded symbol (2 bytes 12 bits offset and 4 bits length)
				 * minimum length = 3
				 * 18 is added to the offset for an unknown reason
				 */
				int length = (src[srcIndex + 1] & 0xF) + 3;
				int offset = src[srcIndex] +
				             (((src[srcIndex + 1] >> 4) & 0xF) << 8) + 18;

				srcIndex += 2;

				for (int j = 0; j < length; j++) {
					/* decode from dictionary 1 byte at a time
					 * the result is placed at the head of the dictionary and
					 * in the destination array
					 */
					uint8_t decoded;
					dictionary[dictIndex++ % dictionary_size] =
					    (decoded = dictionary[(offset + j) % dictionary_size]);
					dst[dstIndex++] = decoded;
				}
			}

			flags = (uint8_t)(flags >> 1);

			if (dstIndex >= dstlen) {
				/* everything is decoded */
				break;
			}
		}
	} while (dstIndex < dstlen);
	free(dictionary);
	return 0;
}
