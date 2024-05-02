/**
 *******************************************************************************
 * @version 0.1
 * @date 2021-12-16
 * @copyright Copyright © 2021 by University of Luxembourg
 * @author Hao Cheng
 *******************************************************************************
 */

#ifndef _GFPARITH_H
#define _GFPARITH_H

#include <stdint.h>
#include "intrin.h"

// radix-2^51 for the field elements: 15 * 51-bit = 765-bit
#define NWORDS 15
#define BRADIX 51
#define BMASK 0x7FFFFFFFFFFFFULL

static const uint64_t p751[NWORDS] = {
  0x7FFFFFFFFFFFF, 0x7FFFFFFFFFFFF, 0x7FFFFFFFFFFFF, 0x7FFFFFFFFFFFF,
  0x7FFFFFFFFFFFF, 0x7FFFFFFFFFFFF, 0x7FFFFFFFFFFFF, 0x7C3C547757FFF,
  0x476E3EC968549, 0x352B363427EF9, 0x2619F5BAFA1DB, 0x22E592BA40427,
  0x3ADC668562B50, 0x6381C25213F2F, 0x0001BF975507D, };

static const uint64_t p751p1[NWORDS] = {
  0x0000000000000, 0x0000000000000, 0x0000000000000, 0x0000000000000, 
  0x0000000000000, 0x0000000000000, 0x0000000000000, 0x7C3C547758000, 
  0x476E3EC968549, 0x352B363427EF9, 0x2619F5BAFA1DB, 0x22E592BA40427, 
  0x3ADC668562B50, 0x6381C25213F2F, 0x0001BF975507D, };

static const uint64_t p751x2[NWORDS] = {
  0x7FFFFFFFFFFFE, 0x7FFFFFFFFFFFF, 0x7FFFFFFFFFFFF, 0x7FFFFFFFFFFFF,
  0x7FFFFFFFFFFFF, 0x7FFFFFFFFFFFF, 0x7FFFFFFFFFFFF, 0x7878A8EEAFFFF,
  0x0EDC7D92D0A93, 0x6A566C684FDF3, 0x4C33EB75F43B6, 0x45CB25748084E,
  0x75B8CD0AC56A0, 0x470384A427E5E, 0x00037F2EAA0FB, };

static const uint64_t p751x4[NWORDS] = {
  0x7FFFFFFFFFFFC, 0x7FFFFFFFFFFFF, 0x7FFFFFFFFFFFF, 0x7FFFFFFFFFFFF,
  0x7FFFFFFFFFFFF, 0x7FFFFFFFFFFFF, 0x7FFFFFFFFFFFF, 0x70F151DD5FFFF,
  0x1DB8FB25A1527, 0x54ACD8D09FBE6, 0x1867D6EBE876D, 0x0B964AE90109D,
  0x6B719A158AD41, 0x0E0709484FCBD, 0x0006FE5D541F7, };

static const uint64_t mont_R[NWORDS] = {
  0x0000000004935, 0x0000000000000, 0x0000000000000, 0x0000000000000,  
  0x0000000000000, 0x0000000000000, 0x0000000000000, 0x136C7B32C8000, 
  0x4645918D44FD5, 0x2B98E7D068C98, 0x358DCEF7BEC40, 0x4FA1831DBEF22, 
  0x7722BD3CF247A, 0x65B95D519629A, 0x00012E6C27835, };

static const uint64_t mont_R2[NWORDS] = {
  0x4C1191276B501, 0x0B0D34B229511, 0x72E3FD8EDB010, 0x5CE0CBC6D2828,
  0x47D02FF8820A8, 0x1966544827C3A, 0x71F1EE7FC8149, 0x609FBBDCFFE6B,
  0x4CBAC01F5A7FE, 0x299B961575678, 0x7C1E37997D67B, 0x32A3645EDD616,
  0x2ADB4B9F5ED39, 0x24EB2C434A0E2, 0x0000ABF39813E, }; 

void mp_sub_p2(__m512i *r, const __m512i *a, const __m512i *b);
void mp_sub_p4(__m512i *r, const __m512i *a, const __m512i *b);
void fpadd(__m512i *r, const __m512i *a, const __m512i* b);
void fpsub(__m512i *r, const __m512i *a, const __m512i* b);
void fpneg(__m512i *r);
void fpdiv2(__m512i *r, const __m512i *a);
void fpcorrection(__m512i *r);
void rdc_mont(__m512i *r, const __m512i *a);

void mp_mul_v1(__m512i *r, const __m512i *a, const __m512i *b);
void mp_mul_v2(__m512i *r, const __m512i *a, const __m512i *b);

void mp_sqr(__m512i *r, const __m512i *a);

#define mp_mul mp_mul_v2

#endif