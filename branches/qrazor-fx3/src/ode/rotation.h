/*************************************************************************
 *                                                                       *
 * Open Dynamics Engine, Copyright (C) 2001,2002 Russell L. Smith.       *
 * All rights reserved.  Email: russ@q12.org   Web: www.q12.org          *
 *                                                                       *
 * This library is free software; you can redistribute it and/or         *
 * modify it under the terms of EITHER:                                  *
 *   (1) The GNU Lesser General Public License as published by the Free  *
 *       Software Foundation; either version 2.1 of the License, or (at  *
 *       your option) any later version. The text of the GNU Lesser      *
 *       General Public License is included with this library in the     *
 *       file LICENSE.TXT.                                               *
 *   (2) The BSD-style license that is included with this library in     *
 *       the file LICENSE-BSD.TXT.                                       *
 *                                                                       *
 * This library is distributed in the hope that it will be useful,       *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the files    *
 * LICENSE.TXT and LICENSE-BSD.TXT for more details.                     *
 *                                                                       *
 *************************************************************************/

#ifndef _ODE_ROTATION_H_
#define _ODE_ROTATION_H_

#include "common.h"

/*
void dRSetIdentity (dMatrix3 R);

void dRFromAxisAndAngle (dMatrix3 R, vec_t ax, vec_t ay, vec_t az,
			 vec_t angle);

void dRFromEulerAngles (dMatrix3 R, vec_t phi, vec_t theta, vec_t psi);

void dRFrom2Axes (dMatrix3 R, vec_t ax, vec_t ay, vec_t az,
		  vec_t bx, vec_t by, vec_t bz);

void dRFromZAxis (dMatrix3 R, vec_t ax, vec_t ay, vec_t az);
*/

//void dQSetIdentity (dQuaternion q);

//void dQFromAxisAndAngle (dQuaternion q, vec_t ax, vec_t ay, vec_t az, vec_t angle);

/* Quaternion multiplication, analogous to the matrix multiplication routines. */
/* qa = rotate by qc, then qb */
//void dQMultiply0 (dQuaternion qa, const dQuaternion qb, const dQuaternion qc);
/* qa = rotate by qc, then by inverse of qb */
//void dQMultiply1 (dQuaternion qa, const dQuaternion qb, const dQuaternion qc);
/* qa = rotate by inverse of qc, then by qb */
//void dQMultiply2 (dQuaternion qa, const dQuaternion qb, const dQuaternion qc);
/* qa = rotate by inverse of qc, then by inverse of qb */
//void dQMultiply3 (dQuaternion qa, const dQuaternion qb, const dQuaternion qc);

//void	dRfromQ(dMatrix3 R, const quaternion_c &q);
//void dQfromR (dQuaternion q, const dMatrix3 R);
//void dDQfromW (vec_t dq[4], const dVector3 w, const dQuaternion q);

#endif
