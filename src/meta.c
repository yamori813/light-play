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

uint8_t album[1024];
int album_size;
uint8_t artist[1024];
int artist_size;
uint8_t title[1024];
int title_size;

void m4aFileMetadataHandler(uint32_t boxType, uint8_t *buffer, uint32_t bufferSize, M4AFileMetadataType metadataType)
{
int i;

	if (boxType == BOX_TYPE_NAM || boxType == BOX_TYPE_ART ||
	     boxType == BOX_TYPE_ALB) {
		printf("MetaData %08x %d ", boxType, bufferSize);
		for (i =0; i < bufferSize; ++i) {
			putchar(buffer[i]);
		}
		putchar('\n');
	}

	if (boxType == BOX_TYPE_ALB) {
		album_size = bufferSize;
		memcpy(album, buffer, bufferSize);
	}
	if (boxType == BOX_TYPE_ART) {
		artist_size = bufferSize;
		memcpy(artist, buffer, bufferSize);
	}
	if (boxType == BOX_TYPE_NAM) {
		title_size = bufferSize;
		memcpy(title, buffer, bufferSize);
	}
}

static int cpMetaData(uint8_t *buffer, char *boxtype, uint8_t *val, int size)
{
int i;

	i = 0;

	memcpy(buffer, boxtype, 4);
	i += 4;

	buffer[i] = size >> 24;
	buffer[i+1] = (size >> 16) & 0xff;
	buffer[i+2] = (size >> 8) & 0xff;
	buffer[i+3] = size & 0xff;
	i += 4;

	memcpy(buffer + i, val, size);
	i += size;

	return i;
}

int mkMetaData(uint8_t *buffer)
{
int off;

	off = 8;
	if (album_size)
		off += cpMetaData(buffer + off, "asal", album, album_size);
	if (artist_size)
		off += cpMetaData(buffer + off, "asar", artist, artist_size);
	if (title_size)
		off += cpMetaData(buffer + off, "minm", title, title_size);

	return off;
}
