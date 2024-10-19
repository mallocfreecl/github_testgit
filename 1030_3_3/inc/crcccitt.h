/*
 * crcccitt.h
 *
 *  Created on: Apr 24, 2014
 *      Author: daniel
 */

#ifndef CRCCITT_H_
#define CRCCITT_H_

uint16_t crc16_ccitt(const uint8_t *buf, const uint8_t *end);
void crc16_ccitt_succ(uint16_t *crc, uint8_t elem);
void crc16_ccitt_reset(uint16_t *crc);

#endif /* CRCCITT_H_ */
