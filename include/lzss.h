/*******************************************************************************
*	<lzss.h> - github.com/raphasanori/Setsuna
*	Author: @RaphaSanOri
*	Content: Custom LZSS Compression Declarations
*
*	This file is part of the Setsuna app and it's avaiable through the
*	Custom Victorique BSD License that can be read inside the LICENSE.TXT
*	provided together with this file or in the original repository here:
*	github.com/raphasanori/Setsuna/blob/master/LICENSE.TXT
*/

#include <config.h>

int decompress_lzss(uint8_t *dst, uint8_t *src, uint32_t dstlen);