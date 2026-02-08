/*
 * File: meta.c
 *
 * Copyright (C) 2026 Hiroki Mori
 *
 * This file is part of light-play.
 *
 * light-play is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * light-play is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with light-play.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <string.h>

#include "meta.h"

#define BOX_TYPE_NAM  0xA96E616D  // Name of the title
#define BOX_TYPE_ART  0xA9415254  // Name of the artist
#define BOX_TYPE_ALB  0xA9616C62  // Name of the album

struct MetaDataStruct {
        uint8_t metaDataBuffer[1024];
        size_t metaDataBufferSize;
};

typedef struct MetaDataStruct MetaData;

static MetaData album;
static MetaData artist;
static MetaData title;

void m4aFileMetadataHandler(uint32_t boxType, uint8_t *buffer, uint32_t bufferSize, M4AFileMetadataType metadataType)
{
#if 0
int i;
	if (boxType == BOX_TYPE_NAM || boxType == BOX_TYPE_ART ||
	     boxType == BOX_TYPE_ALB) {
		printf("MetaData %08x %d ", boxType, bufferSize);
		for (i =0; i < bufferSize; ++i) {
			putchar(buffer[i]);
		}
		putchar('\n');
	}
#endif

	if (boxType == BOX_TYPE_ALB) {
		album.metaDataBufferSize = bufferSize;
		memcpy(album.metaDataBuffer, buffer, bufferSize);
	}
	if (boxType == BOX_TYPE_ART) {
		artist.metaDataBufferSize = bufferSize;
		memcpy(artist.metaDataBuffer, buffer, bufferSize);
	}
	if (boxType == BOX_TYPE_NAM) {
		title.metaDataBufferSize = bufferSize;
		memcpy(title.metaDataBuffer, buffer, bufferSize);
	}
}

static int cpMetaData(uint8_t *buffer, char *boxtype, MetaData *meta)
{
int i;

	memcpy(buffer, boxtype, 4);
	i = 4;

	buffer[i] = meta->metaDataBufferSize >> 24;
	buffer[i+1] = (meta->metaDataBufferSize  >> 16) & 0xff;
	buffer[i+2] = (meta->metaDataBufferSize  >> 8) & 0xff;
	buffer[i+3] = meta->metaDataBufferSize  & 0xff;
	i += 4;

	memcpy(buffer + i, meta->metaDataBuffer, meta->metaDataBufferSize );
	i += meta->metaDataBufferSize;

	return i;
}

int mkMetaData(uint8_t *buffer)
{
int off;

	off = 8;
	if (album.metaDataBufferSize)
		off += cpMetaData(buffer + off, "asal", &album);
	if (artist.metaDataBufferSize)
		off += cpMetaData(buffer + off, "asar", &artist);
	if (title.metaDataBufferSize)
		off += cpMetaData(buffer + off, "minm", &title);

	return off;
}
