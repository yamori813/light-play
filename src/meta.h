/*
 * File: meta.h
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

#include "m4afile.h"

void m4aFileMetadataHandler(uint32_t boxType, uint8_t *buffer, uint32_t bufferSize, M4AFileMetadataType metadataType);
int mkMetaData(uint8_t *buffer);
