/// ============================================================================
/*
Copyright (C) 1997-2001 Id Software, Inc.				(Quake2)
Copyright (C) 2000 Vasiliou Nikos email <nbasili@ceid.upatras.gr>	(U3D)
Copyright (C) 2000-2002 by Iain Nicholson <iain@delphinus.demon.co.uk>	(libSIMD)
Copyright (C) 2004 Robert Beckebans <trebor_7@users.sourceforge.net>
Please see the file "AUTHORS" for a list of contributors

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/
/// ============================================================================


/// includes ===================================================================
// system -------------------------------------------------------------------
// shared -------------------------------------------------------------------
#include "x_shared.h"
// qrazor-fx ----------------------------------------------------------------
// xreal --------------------------------------------------------------------


const vec3_c		vec3_origin = vec3_c(0, 0, 0);


const matrix_c		matrix_identity = matrix_c(	1, 0, 0, 0, 
							0, 1, 0, 0,
							0, 0, 1, 0,
							0, 0, 0, 1	);
						
const quaternion_c	quat_identity = quaternion_c(0, 0, 0, 1);


const vec4_c	color_black	= vec4_c(0, 0, 0, 1);
const vec4_c	color_red	= vec4_c(1, 0, 0, 1);
const vec4_c	color_green	= vec4_c(0, 1, 0, 1);
const vec4_c	color_blue	= vec4_c(0, 0, 1, 1);
const vec4_c	color_yellow	= vec4_c(1, 1, 0, 1);
const vec4_c	color_magenta	= vec4_c(1, 0, 1, 1);
const vec4_c	color_cyan	= vec4_c(0, 1, 1, 1);
const vec4_c	color_white	= vec4_c(1, 1, 1, 1);
const vec4_c	color_grey_lite	= vec4_c(0.75, 0.75, 0.75, 1);
const vec4_c	color_grey_med	= vec4_c(0.5, 0.5, 0.5, 1);
const vec4_c	color_grey_dark	= vec4_c(0.25, 0.25, 0.25, 1);




float	X_RSqrt(float number)
{
	int i;
	float x2, y;

	if (number == 0.0)
		return 0.0;

	x2 = number * 0.5f;
	y = number;
	i = * (int *) &y;		// evil floating point bit level hacking
	i = 0x5f3759df - (i >> 1);	// what the fuck?
	y = * (float *) &i;
	y = y * (1.5f - (x2 * y * y));	// this can be done a second time

	return y;
}

void	vec3_c::snap()
{
	for(int i=0; i<3; i++)
	{
		if(fabs(_v[i] - 1) < NORMAL_EPSILON)
		{
			clear();
			_v[i] = 1;
			break;
		}
			
		if(fabs(_v[i] - -1) < NORMAL_EPSILON)
		{
			clear();
			_v[i] = -1;
			break;
		}
	}
}
	
const char*	vec3_c::toString() const
{
	return va("(%i %i %i)", (int)_v[0], (int)_v[1], (int)_v[2]);
}




matrix_c::matrix_c()
{
	// DO NOTHING AND SAVE SPEED
}
	
matrix_c::matrix_c(	vec_t m00, vec_t m01, vec_t m02, vec_t m03,
			vec_t m10, vec_t m11, vec_t m12, vec_t m13,
			vec_t m20, vec_t m21, vec_t m22, vec_t m23,
			vec_t m30, vec_t m31, vec_t m32, vec_t m33)
{
	_m[0][0]=m00;	_m[0][1]=m01;	_m[0][2]=m02;	_m[0][3]=m03;
	_m[1][0]=m10;	_m[1][1]=m11;	_m[1][2]=m12;	_m[1][3]=m13;
	_m[2][0]=m20;	_m[2][1]=m21;	_m[2][2]=m22;	_m[2][3]=m23;
	_m[3][0]=m30;	_m[3][1]=m31;	_m[3][2]=m32;	_m[3][3]=m33;
}
	
void	matrix_c::identity()
{
	_m[0][0]=1.0f;	_m[0][1]=0.0f;	_m[0][2]=0.0f;	_m[0][3]=0.0f;
	_m[1][0]=0.0f;	_m[1][1]=1.0f;	_m[1][2]=0.0f;	_m[1][3]=0.0f;
	_m[2][0]=0.0f;	_m[2][1]=0.0f;	_m[2][2]=1.0f;	_m[2][3]=0.0f;
	_m[3][0]=0.0f;	_m[3][1]=0.0f;	_m[3][2]=0.0f;	_m[3][3]=1.0f;
}
	
void	matrix_c::zero()
{
	_m[0][0]=0.0f;	_m[0][1]=0.0f;	_m[0][2]=0.0f;	_m[0][3]=0.0f;
	_m[1][0]=0.0f;	_m[1][1]=0.0f;	_m[1][2]=0.0f;	_m[1][3]=0.0f;
	_m[2][0]=0.0f;	_m[2][1]=0.0f;	_m[2][2]=0.0f;	_m[2][3]=0.0f;
	_m[3][0]=0.0f;	_m[3][1]=0.0f;	_m[3][2]=0.0f;	_m[3][3]=0.0f;
}
	
void	matrix_c::copyTo(matrix_c &out)
{
	out._m[0][0]=_m[0][0];	out._m[0][1]=_m[0][1];	out._m[0][2]=_m[0][2];	out._m[0][3]=_m[0][3];
	out._m[1][0]=_m[1][0];	out._m[1][1]=_m[1][1];	out._m[1][2]=_m[1][2];	out._m[1][3]=_m[1][3];
	out._m[2][0]=_m[2][0];	out._m[2][1]=_m[2][1];	out._m[2][2]=_m[2][2];	out._m[2][3]=_m[2][3];
	out._m[3][0]=_m[3][0];	out._m[3][1]=_m[3][1];	out._m[3][2]=_m[3][2];	out._m[3][3]=_m[3][3];
}
	
void	matrix_c::copyRotateOnly(matrix_c &out)
{
	out._m[0][0]=_m[0][0];	out._m[0][1]=_m[0][1];	out._m[0][2]=_m[0][2];	out._m[0][3]=0.0f;
	out._m[1][0]=_m[1][0];	out._m[1][1]=_m[1][1];	out._m[1][2]=_m[1][2];	out._m[1][3]=0.0f;
	out._m[2][0]=_m[2][0];	out._m[2][1]=_m[2][1];	out._m[2][2]=_m[2][2];	out._m[2][3]=0.0f;
	out._m[3][0]=_m[3][0];	out._m[3][1]=_m[3][1];	out._m[3][2]=_m[3][2];	out._m[3][3]=1.0f;
}
	
void	matrix_c::copyTranslateOnly(matrix_c &out)
{
	out._m[0][0]=1.0f;	out._m[0][1]=0.0f;	out._m[0][2]=0.0f;	out._m[0][3]=_m[0][3];
	out._m[1][0]=0.0f;	out._m[1][1]=1.0f;	out._m[1][2]=0.0f;	out._m[1][3]=_m[1][3];
	out._m[2][0]=0.0f;	out._m[2][1]=0.0f;	out._m[2][2]=1.0f;	out._m[2][3]=_m[2][3];
	out._m[3][0]=0.0f;	out._m[3][1]=0.0f;	out._m[3][2]=0.0f;	out._m[3][3]=1.0f;
}
	
void	matrix_c::copyTranspose(matrix_c &out)
{
	out._m[0][0]=_m[0][0];	out._m[0][1]=_m[1][0];	out._m[0][2]=_m[2][0];	out._m[0][3]=_m[3][0];
	out._m[1][0]=_m[0][1];	out._m[1][1]=_m[1][1];	out._m[1][2]=_m[2][1];	out._m[1][3]=_m[3][1];
	out._m[2][0]=_m[0][2];	out._m[2][1]=_m[1][2];	out._m[2][2]=_m[2][2];	out._m[2][3]=_m[3][2];
	out._m[3][0]=_m[0][3];	out._m[3][1]=_m[1][3];	out._m[3][2]=_m[2][3];	out._m[3][3]=_m[3][3];
}

void	matrix_c::transpose()
{
	matrix_c tmp;
	copyTranspose(tmp);
	tmp.copyTo(*this);
}
	
void	matrix_c::setupXRotation(vec_t deg)
{
	vec_t a = DEGTORAD(deg);
	
	_m[0][0]=1.0f;	_m[0][1]=0.0f;		_m[0][2]=0.0f;		_m[0][3]=0.0f;
	_m[1][0]=0.0f;	_m[1][1]=cos(a);	_m[1][2]=-sin(a);	_m[1][3]=0.0f;
	_m[2][0]=0.0f;	_m[2][1]=sin(a);	_m[2][2]= cos(a);	_m[2][3]=0.0f;
	_m[3][0]=0.0f;	_m[3][1]=0.0f;		_m[3][2]=0.0f;		_m[3][3]=1.0f;
}

void	matrix_c::setupYRotation(vec_t deg)
{
	vec_t a = DEGTORAD(deg);

	_m[0][0]=cos(a);	_m[0][1]=0.0f;		_m[0][2]=sin(a);	_m[0][3]=0.0f;	
	_m[1][0]=0.0f;		_m[1][1]=1.0f;		_m[1][2]=0.0f;		_m[1][3]=0.0f;
	_m[2][0]=-sin(a);	_m[2][1]=0.0f;		_m[2][2]=cos(a);	_m[2][3]=0.0f;
	_m[3][0]=0.0f;		_m[3][1]=0.0f;		_m[3][2]=0.0f;		_m[3][3]=1.0f;
}

void	matrix_c::setupZRotation(vec_t deg)
{
	vec_t a = DEGTORAD(deg);
	
	_m[0][0]=cos(a);	_m[0][1]=-sin(a);	_m[0][2]=0.0f;		_m[0][3]=0.0f;
	_m[1][0]=sin(a);	_m[1][1]= cos(a);	_m[1][2]=0.0f;		_m[1][3]=0.0f;
	_m[2][0]=0.0f;		_m[2][1]=0.0f;		_m[2][2]=1.0f;		_m[2][3]=0.0f;
	_m[3][0]=0.0f;		_m[3][1]=0.0f;		_m[3][2]=0.0f;		_m[3][3]=1.0f;
}

void	matrix_c::setupRotation(vec_t x, vec_t y, vec_t z, vec_t deg)
{
	vec_t len, c, s;
	
	len = x*x+y*y+z*z;
	if(len != 0.0f)
		len = 1.0f / (vec_t)sqrt(len);
	x *= len;
	y *= len;
	z *= len;

	deg *= (vec_t)(-M_PI / 180.0);
	c = (vec_t)cos(deg);
	s = (vec_t)sin(deg);

	_m[0][0]=x*x + c*(1 - x*x);	_m[0][1]=x*y * (1 - c) + z*s;	_m[0][2]=z*x * (1 - c) - y*s;	_m[0][3]=0.0f;
	_m[1][0]=x*y * (1 - c) - z*s;	_m[1][1]=y*y + c * (1 - y*y);	_m[1][2]=y*z * (1 - c) + x*s;	_m[1][3]=0.0f;
	_m[2][0]=z*x * (1 - c) + y*s;	_m[2][1]=y*z * (1 - c) - x*s;	_m[2][2]=z*z + c * (1 - z*z);	_m[2][3]=0.0f;
	_m[3][0]=0.0f;			_m[3][1]=0.0f;			_m[3][2]=0.0f;			_m[3][3]=1.0f;
}
	
void	matrix_c::setupTranslation(vec_t x, vec_t y, vec_t z)
{
	_m[0][0]=1;	_m[0][1]=0;	_m[0][2]=0;	_m[0][3]=x;
	_m[1][0]=0;	_m[1][1]=1;	_m[1][2]=0;	_m[1][3]=y;
	_m[2][0]=0;	_m[2][1]=0;	_m[2][2]=1;	_m[2][3]=z;
	_m[3][0]=0;	_m[3][1]=0;	_m[3][2]=0;	_m[3][3]=1;
}
	
void	matrix_c::setupScale(vec_t x, vec_t y, vec_t z)
{
	_m[0][0]=x;	_m[0][1]=0;	_m[0][2]=0;	_m[0][3]=0;
	_m[1][0]=0;	_m[1][1]=y;	_m[1][2]=0;	_m[1][3]=0;
	_m[2][0]=0;	_m[2][1]=0;	_m[2][2]=z;	_m[2][3]=0;
	_m[3][0]=0;	_m[3][1]=0;	_m[3][2]=0;	_m[3][3]=1;
}

void	matrix_c::fromAngles(vec_t pitch, vec_t yaw, vec_t roll)
{
	double	sr, sp, sy, cr, cp, cy;
		
	sp = X_sin(pitch);
	cp = X_cos(pitch);
	
	sy = X_sin(yaw);
	cy = X_cos(yaw);
	
	sr = X_sin(roll);
	cr = X_cos(roll);

	_m[0][0]=(vec_t)(cp*cy);	_m[0][1]=(vec_t)(sr*sp*cy+cr*-sy);	_m[0][2]=(vec_t)(cr*sp*cy+-sr*-sy);	_m[0][3]= 0;
	_m[1][0]=(vec_t)(cp*sy);	_m[1][1]=(vec_t)(sr*sp*sy+cr*cy);	_m[1][2]=(vec_t)(cr*sp*sy+-sr*cy);	_m[1][3]= 0;
	_m[2][0]=(vec_t)(-sp);		_m[2][1]=(vec_t)(sr*cp);		_m[2][2]=(vec_t)(cr*cp);		_m[2][3]= 0;
	_m[3][0]= 0;			_m[3][1]= 0;				_m[3][2]= 0;				_m[3][3]= 1;
}
	
void	matrix_c::fromVectorsFLU(const vec3_c &forward, const vec3_c &left, const vec3_c &up)
{
	_m[0][0]=forward[0];	_m[0][1]=left[0];	_m[0][2]=up[0];	_m[0][3]=0; 
	_m[1][0]=forward[0];	_m[1][1]=left[0];	_m[1][2]=up[0];	_m[1][3]=0;
	_m[2][0]=forward[0];	_m[2][1]=left[0];	_m[2][2]=up[0];	_m[2][3]=0;
	_m[3][0]=0;		_m[3][1]=0;		_m[3][2]=0;	_m[3][3]=1;
}
	
void	matrix_c::toVectorsFLU(vec3_c &forward, vec3_c &left, vec3_c &up) const
{
	forward[0] = _m[0][0];	// cp*cy;
	forward[1] = _m[1][0];	// cp*sy;
	forward[2] = _m[2][0];	//-sp;
		
	left[0] = _m[0][1];	// sr*sp*cy+cr*-sy;
	left[1] = _m[1][1];	// sr*sp*sy+cr*cy;
	left[2] = _m[2][1];	// sr*cp;

	up[0] = _m[0][2];	// cr*sp*cy+-sr*-sy;
	up[1] = _m[1][2];	// cr*sp*sy+-sr*cy;
	up[2] = _m[2][2];	// cr*cp;
}
	
void	matrix_c::fromVectorsFRU(const vec3_c &forward, const vec3_c &right, const vec3_c &up)
{
	_m[0][0]=forward[0];	_m[0][1]=-right[0];	_m[0][2]=up[0];	_m[0][3]=0;
	_m[1][0]=forward[0];	_m[1][1]=-right[0];	_m[1][2]=up[0];	_m[1][3]=0;
	_m[2][0]=forward[0];	_m[2][1]=-right[0];	_m[2][2]=up[0];	_m[2][3]=0;
	_m[3][0]=0;		_m[3][1]=0;		_m[3][2]=0;	_m[3][3]=1;
}
	
void	matrix_c::toVectorsFRU(vec3_c &forward, vec3_c &right, vec3_c &up) const
{
	forward[0] = _m[0][0];	// cp*cy;
	forward[1] = _m[1][0];	// cp*sy;
	forward[2] = _m[2][0];	//-sp;
		
	right[0] = -_m[0][1];	//-sr*sp*cy+cr*-sy;
	right[1] = -_m[1][1];	//-sr*sp*sy+cr*cy;
	right[2] = -_m[2][1];	//-sr*cp;

	up[0] = _m[0][2];	// cr*sp*cy+-sr*-sy;
	up[1] = _m[1][2];	// cr*sp*sy+-sr*cy;
	up[2] = _m[2][2];	// cr*cp;
}
	
void	matrix_c::fromQuaternion(const quaternion_c &q)
{
	/*
	Assuming that a quaternion has been created in the form:

	Q = |X Y Z W|
	
	Then the quaternion can then be converted into a 4x4 row major rotation
	matrix using the following expression
	
	
         �        2     2                                      �

         � 1 - (2Y  + 2Z )   2XY - 2ZW         2XZ + 2YW       �

         �                                                     �

         �                          2     2                    �

     M = � 2XY + 2ZW         1 - (2X  + 2Z )   2YZ - 2XW       �

         �                                                     �

         �                                            2     2  �

         � 2XZ - 2YW         2YZ + 2XW         1 - (2X  + 2Y ) �

         �                                                     �

	If a 4x4 matrix is required, then the bottom row and right-most column
	may be added.
	*/

	
	double xx = q[0] * q[0];
	double xy = q[0] * q[1];
	double xz = q[0] * q[2];
	double xw = q[0] * q[3];
	
	double yy = q[1] * q[1];
	double yz = q[1] * q[2];
	double yw = q[1] * q[3];
	
	double zz = q[2] * q[2];
	double zw = q[2] * q[3];
	

	_m[0][0]=1-2*(yy+zz);	_m[0][1]=  2*(xy-zw);	_m[0][2]=  2*(xz+yw);	_m[0][3]=0;
	_m[1][0]=  2*(xy+zw);	_m[1][1]=1-2*(xx+zz);	_m[1][2]=  2*(yz-xw);	_m[1][3]=0;
	_m[2][0]=  2*(xz-yw);	_m[2][1]=  2*(yz+xw);	_m[2][2]=1-2*(xx+yy);	_m[2][3]=0;
	_m[3][0]=0;		_m[3][1]=0;		_m[3][2]=0;		_m[3][3]=1;
}
	
void	matrix_c::lerp(const matrix_c &old, const matrix_c &nu, vec_t f)
{
	_m[0][0] = nu._m[0][0] + (old._m[0][0] - nu._m[0][0]) * f;
	_m[0][1] = nu._m[0][1] + (old._m[0][1] - nu._m[0][1]) * f;
	_m[0][2] = nu._m[0][2] + (old._m[0][2] - nu._m[0][2]) * f;
	_m[0][3] = nu._m[0][3] + (old._m[0][3] - nu._m[0][3]) * f;
		
	_m[1][0] = nu._m[1][0] + (old._m[1][0] - nu._m[1][0]) * f;
	_m[1][1] = nu._m[1][1] + (old._m[1][1] - nu._m[1][1]) * f;
	_m[1][2] = nu._m[1][2] + (old._m[1][2] - nu._m[1][2]) * f;
	_m[1][3] = nu._m[1][3] + (old._m[1][3] - nu._m[1][3]) * f;
		
	_m[2][0] = nu._m[2][0] + (old._m[2][0] - nu._m[2][0]) * f;
	_m[2][1] = nu._m[2][1] + (old._m[2][1] - nu._m[2][1]) * f;
	_m[2][2] = nu._m[2][2] + (old._m[2][2] - nu._m[2][2]) * f;
	_m[2][3] = nu._m[2][3] + (old._m[2][3] - nu._m[2][3]) * f;
		
	_m[3][0] = nu._m[3][0] + (old._m[3][0] - nu._m[3][0]) * f;
	_m[3][1] = nu._m[3][1] + (old._m[3][1] - nu._m[3][1]) * f;
	_m[3][2] = nu._m[3][2] + (old._m[3][2] - nu._m[3][2]) * f;
	_m[3][3] = nu._m[3][3] + (old._m[3][3] - nu._m[3][3]) * f;
}
	
// Tr3B - recoded from Tenebrae2 into row major style
matrix_c	matrix_c::affineInverse() const
{
	matrix_c out;
		
	// The rotational part of the matrix is simply the transpose of the original matrix.
	out[0][0]=_m[0][0];	out[0][1]=_m[1][0];	out[0][2]=_m[2][0];
	out[1][0]=_m[0][1];	out[1][1]=_m[1][1];	out[1][2]=_m[2][1];
	out[2][0]=_m[0][2];	out[2][1]=_m[1][2];	out[2][2]=_m[2][2];
	out[3][0] = 0;		out[3][1] = 0;		out[3][2] = 0;		out[3][3] = 1;
		
	// The translation components of the original matrix.
	vec_t tx = _m[0][3];
	vec_t ty = _m[1][3];
	vec_t tz = _m[2][3];
		
	// Rresult = -(Tm * Rm) to get the translation part of the inverse
	out[0][3] = -(_m[0][0]*tx + _m[1][0]*ty + _m[2][0]*tz);
	out[1][3] = -(_m[0][1]*tx + _m[1][1]*ty + _m[2][1]*tz);
	out[2][3] = -(_m[0][2]*tx + _m[1][2]*ty + _m[2][2]*tz);
	
	return out;
}
	
	
const char*	matrix_c::toString() const
{
#if 0
		std::string s;
		s  = _m[0].toString(); s += '\n';
		s += _m[1].toString(); s += '\n';
		s += _m[2].toString(); s += '\n';
		s += _m[3].toString();
		return s.c_str();
#else
		return "";
#endif
}
		
bool	matrix_c::operator == (const matrix_c &m) const
{
	return	(	_m[0][0]==m._m[0][0] && _m[0][1]==m._m[0][1] && _m[0][2]==m._m[0][2] && _m[0][3]==m._m[0][3] &&
			_m[1][0]==m._m[1][0] && _m[1][1]==m._m[1][1] && _m[1][2]==m._m[1][2] && _m[1][3]==m._m[1][3] &&
			_m[2][0]==m._m[2][0] && _m[2][1]==m._m[2][1] && _m[2][2]==m._m[2][2] && _m[2][3]==m._m[2][3] &&
			_m[3][0]==m._m[3][0] && _m[3][1]==m._m[3][1] && _m[3][2]==m._m[3][2] && _m[3][3]==m._m[3][3]	);
}

matrix_c	matrix_c::operator + (const matrix_c &m) const
{
	return matrix_c(	_m[0][0]+m._m[0][0],	_m[0][1]+m._m[0][1],	_m[0][2]+m._m[0][2],	_m[0][3]+m._m[0][3],
				_m[1][0]+m._m[1][0],	_m[1][1]+m._m[1][1],	_m[1][2]+m._m[1][2],	_m[1][3]+m._m[1][3],
				_m[2][0]+m._m[2][0],	_m[2][1]+m._m[2][1],	_m[2][2]+m._m[2][2],	_m[2][3]+m._m[2][3],
				_m[3][0]+m._m[3][0],	_m[3][1]+m._m[3][1],	_m[3][2]+m._m[3][2],	_m[3][3]+m._m[3][3]	);
}

matrix_c	matrix_c::operator - (const matrix_c &m) const
{
	return matrix_c(	_m[0][0]-m._m[0][0],	_m[0][1]-m._m[0][1],	_m[0][2]-m._m[0][2],	_m[0][3]-m._m[0][3],
				_m[1][0]-m._m[1][0],	_m[1][1]-m._m[1][1],	_m[1][2]-m._m[1][2],	_m[1][3]-m._m[1][3],
				_m[2][0]-m._m[2][0],	_m[2][1]-m._m[2][1],	_m[2][2]-m._m[2][2],	_m[2][3]-m._m[2][3],
				_m[3][0]-m._m[3][0],	_m[3][1]-m._m[3][1],	_m[3][2]-m._m[3][2],	_m[3][3]-m._m[3][3]	);
}
	
matrix_c	matrix_c::operator * (const matrix_c &m) const
{
	return matrix_c(	_m[0][0]*m._m[0][0] + _m[0][1]*m._m[1][0] + _m[0][2]*m._m[2][0] + _m[0][3]*m._m[3][0]	,
				_m[0][0]*m._m[0][1] + _m[0][1]*m._m[1][1] + _m[0][2]*m._m[2][1] + _m[0][3]*m._m[3][1]	,
				_m[0][0]*m._m[0][2] + _m[0][1]*m._m[1][2] + _m[0][2]*m._m[2][2] + _m[0][3]*m._m[3][2]	,
				_m[0][0]*m._m[0][3] + _m[0][1]*m._m[1][3] + _m[0][2]*m._m[2][3] + _m[0][3]*m._m[3][3]	,
				
				_m[1][0]*m._m[0][0] + _m[1][1]*m._m[1][0] + _m[1][2]*m._m[2][0] + _m[1][3]*m._m[3][0]	,
				_m[1][0]*m._m[0][1] + _m[1][1]*m._m[1][1] + _m[1][2]*m._m[2][1] + _m[1][3]*m._m[3][1]	,
				_m[1][0]*m._m[0][2] + _m[1][1]*m._m[1][2] + _m[1][2]*m._m[2][2] + _m[1][3]*m._m[3][2]	,
				_m[1][0]*m._m[0][3] + _m[1][1]*m._m[1][3] + _m[1][2]*m._m[2][3] + _m[1][3]*m._m[3][3]	,
				
				_m[2][0]*m._m[0][0] + _m[2][1]*m._m[1][0] + _m[2][2]*m._m[2][0] + _m[2][3]*m._m[3][0]	,
				_m[2][0]*m._m[0][1] + _m[2][1]*m._m[1][1] + _m[2][2]*m._m[2][1] + _m[2][3]*m._m[3][1]	,
				_m[2][0]*m._m[0][2] + _m[2][1]*m._m[1][2] + _m[2][2]*m._m[2][2] + _m[2][3]*m._m[3][2]	,
				_m[2][0]*m._m[0][3] + _m[2][1]*m._m[1][3] + _m[2][2]*m._m[2][3] + _m[2][3]*m._m[3][3]	,
					
				_m[3][0]*m._m[0][0] + _m[3][1]*m._m[1][0] + _m[3][2]*m._m[2][0] + _m[3][3]*m._m[3][0]	,
				_m[3][0]*m._m[0][1] + _m[3][1]*m._m[1][1] + _m[3][2]*m._m[2][1] + _m[3][3]*m._m[3][1]	,
				_m[3][0]*m._m[0][2] + _m[3][1]*m._m[1][2] + _m[3][2]*m._m[2][2] + _m[3][3]*m._m[3][2]	,
				_m[3][0]*m._m[0][3] + _m[3][1]*m._m[1][3] + _m[3][2]*m._m[2][3] + _m[3][3]*m._m[3][3]	);
}
	
matrix_c&	matrix_c::operator = (const matrix_c &m)
{
	_m[0][0]=m._m[0][0];	_m[0][1]=m._m[0][1];	_m[0][2]=m._m[0][2];	_m[0][3]=m._m[0][3];
	_m[1][0]=m._m[1][0];	_m[1][1]=m._m[1][1];	_m[1][2]=m._m[1][2];	_m[1][3]=m._m[1][3];
	_m[2][0]=m._m[2][0];	_m[2][1]=m._m[2][1];	_m[2][2]=m._m[2][2];	_m[2][3]=m._m[2][3];
	_m[3][0]=m._m[3][0];	_m[3][1]=m._m[3][1];	_m[3][2]=m._m[3][2];	_m[3][3]=m._m[3][3];
		
	return *this;
}



	
vec_t	quaternion_c::normalize()
{
	vec_t mag = magnitude();
	
	if(mag != 0)
	{
		_q[0] /= mag;
		_q[1] /= mag;
		_q[2] /= mag;
		_q[3] /= mag;
	}
	
	return mag;
}
	
void	quaternion_c::fromAngles(vec_t pitch, vec_t yaw, vec_t roll)
{
#if 0
	double	cr, cp, cy, sr, sp, sy;

	cp = X_cos(pitch / 2.0);
	cy = X_cos(yaw / 2.0);
	cr = X_cos(roll / 2.0);

	sp = X_sin(pitch / 2.0);
	sy = X_sin(yaw / 2.0);
	sr = X_sin(roll / 2.0);

	_q[0] = (float)(sr*cp*cy - cr*sp*sy);
	_q[1] = (float)(cr*sp*cy + sr*cp*sy);
	_q[2] = (float)(cr*cp*sy - sr*sp*cy);
	
	_q[3] = (float)(cr*cp*cy + sr*sp*sy);

	normalize();
#else
	identity();
		
	multiplyRotation(0, 0, 1, yaw);
	multiplyRotation(0, 1, 0, pitch);
	multiplyRotation(1, 0, 0, roll);
		
	normalize();
#endif
}
	
void	quaternion_c::fromMatrix(const matrix_c &m)
{
	float	s;
	float	x, y, z, w;
		
	// calculate the trace
	float trace = 1 + m._m[0][0] + m._m[1][1] + m._m[2][2];
		
	if(trace > 0.00000001)
	{
		s = sqrt(trace) * 2;
		
		x = (m._m[2][1] - m._m[1][2]) / s;
		y = (m._m[0][2] - m._m[2][0]) / s;
		z = (m._m[1][0] - m._m[0][1]) / s;
		w = 0.25 * s;
	}
		
	if(m._m[0][0] > m._m[1][1] && m._m[0][0] > m._m[2][2])
	{	
		// Column 0: 
		s = sqrt(1.0 + m._m[0][0] - m._m[1][1] - m._m[2][2]) * 2;
			
		x = 0.25 * s;
		y = (m._m[1][0] + m._m[0][1]) / s;
		z = (m._m[0][2] + m._m[2][0]) / s;
		w = (m._m[2][1] - m._m[1][2]) / s;
	}
	else if(m._m[1][1] > m._m[2][2])
	{
		// Column 1:
		s = sqrt(1.0 + m._m[1][1] - m._m[0][0] - m._m[2][2]) * 2;
			
		x = (m._m[1][0] + m._m[0][1]) / s;
		y = 0.25 * s;
		z = (m._m[2][1] + m._m[1][2]) / s;
		w = (m._m[0][2] - m._m[2][0]) / s;
	}
	else
	{
		// Column 2:
		s = sqrt(1.0 + m._m[2][2] - m._m[0][0] - m._m[1][1]) * 2;
			
		x = (m._m[0][2] + m._m[2][0]) / s;
		y = (m._m[2][1] + m._m[1][2]) / s;
		y = 0.25 * s;
		w = (m._m[1][0] - m._m[0][1]) / s;
	}
}
	
void	quaternion_c::fromAxisAngle(vec_t x, vec_t y, vec_t z, vec_t deg)
{
	vec3_c	naxis(x, y, z);
	double	sin_a;
	double	cos_a;
	
	naxis.normalize();
	
	sin_a = X_sin(deg/2);
	cos_a = X_cos(deg/2);
	
	_q[0] = naxis[0] * sin_a;
	_q[1] = naxis[1] * sin_a;
	_q[2] = naxis[2] * sin_a;
	_q[3] = cos_a;
}
	
void	quaternion_c::toAxisAngle(vec3_c &axis, float *deg)
{
	float	angle;
	float	scale;
	float	length;
	
	angle = acos(_q[3]);

	scale = Vector3_Length(_q);

	if(scale == 0)
	{
		axis.clear();
		*deg = 0;
	}
	else
	{
		*deg = angle*2;
		axis[0] = _q[0] / scale;
		axis[1] = _q[1] / scale;
		axis[2] = _q[2] / scale;
		length = axis.length();
		
		if(length != 0)
		{
			axis[0] /= length;
			axis[1] /= length;
			axis[2] /= length;
		}
		
		*deg = RADTODEG (*deg);			//give us angle in degrees
	}
}
	
void	quaternion_c::toVectorsFLU(vec3_c &forward, vec3_c &left, vec3_c &up) const
{
	double xx = _q[0] * _q[0];
	double xy = _q[0] * _q[1];
	double xz = _q[0] * _q[2];
	double xw = _q[0] * _q[3];
	
	double yy = _q[1] * _q[1];
	double yz = _q[1] * _q[2];
	double yw = _q[1] * _q[3];
	
	double zz = _q[2] * _q[2];
	double zw = _q[2] * _q[3];
		
	
	forward[0] = 1-2*(yy+zz);	//_m[0][0];	// cp*cy;
	forward[1] =   2*(xy+zw);	//_m[1][0];	// cp*sy;
	forward[2] =   2*(xz-yw);	//_m[2][0];	//-sp;
		
	left[0] =   2*(xy-zw);		//_m[0][1];	// sr*sp*cy+cr*-sy;
	left[1] = 1-2*(xx+zz);		//_m[1][1];	// sr*sp*sy+cr*cy;
	left[2] =   2*(yz+xw);		//_m[2][1];	// sr*cp;

	up[0] =   2*(xz+yw);		//_m[0][2];	// cr*sp*cy+-sr*-sy;
	up[1] =   2*(yz-xw);		//_m[1][2];	// cr*sp*sy+-sr*cy;
	up[2] = 1-2*(xx+yy);		//_m[2][2];	// cr*cp;	
}
	
void	quaternion_c::toVectorsFRU(vec3_c &forward, vec3_c &right, vec3_c &up) const
{
	double xx = _q[0] * _q[0];
	double xy = _q[0] * _q[1];
	double xz = _q[0] * _q[2];
	double xw = _q[0] * _q[3];
	
	double yy = _q[1] * _q[1];
	double yz = _q[1] * _q[2];
	double yw = _q[1] * _q[3];
	
	double zz = _q[2] * _q[2];
	double zw = _q[2] * _q[3];
		
	
	forward[0] = 1-2*(yy+zz);	//_m[0][0];	// cp*cy;
	forward[1] =   2*(xy+zw);	//_m[1][0];	// cp*sy;
	forward[2] =   2*(xz-yw);	//_m[2][0];	//-sp;
		
	right[0] =    -2*(xy-zw);	//_m[0][1];	//-sr*sp*cy+cr*-sy;
	right[1] = -(1-2*(xx+zz));	//_m[1][1];	//-sr*sp*sy+cr*cy;
	right[2] =    -2*(yz+xw);	//_m[2][1];	//-sr*cp;

	up[0] =   2*(xz+yw);		//_m[0][2];	// cr*sp*cy+-sr*-sy;
	up[1] =   2*(yz-xw);		//_m[1][2];	// cr*sp*sy+-sr*cy;
	up[2] = 1-2*(xx+yy);		//_m[2][2];	// cr*cp;
}
	
void	quaternion_c::slerp(const quaternion_c &from, const quaternion_c &to, float t)
{
	/*
	quaternion_c a = q1;
	quaternoin_c b = q2;
	quaternion_c trans = b * a->inverse();
		
	if(trans.w < 0)
		trans.antipodal();
			
	*this = trans.power(f) * *this
	*/
		
	quaternion_c to1;
	double omega, cosom, sinom, scale0, scale1;

	cosom = from[0]*to[0] + from[1]*to[1] + from[2]*to[2] + from[3]*to[3];

	if(cosom < 0.0)
	{
		cosom = -cosom;
		
		to1 = to;
		to1.antipodal();
	}
	else 
	{
		to1 = to;
	}
		
	if((1.0 - cosom) > 0)
	{
		omega = acos(cosom);
		sinom = sin(omega);
		scale0 = sin((1.0 - t) * omega) / sinom;
		scale1 = sin(t * omega) / sinom;
	}
	else
	{
		scale0 = 1.0 - t;
		scale1 = t;
	}

	_q[0] = scale0 * from[0] + scale1 * to1[0];
	_q[1] = scale0 * from[1] + scale1 * to1[1];
	_q[2] = scale0 * from[2] + scale1 * to1[2];
	_q[3] = scale0 * from[3] + scale1 * to1[3];
}
	
const char*	quaternion_c::toString() const
{
	return va("(%i %i %i %i)", (int)_q[0], (int)_q[1], (int)_q[2], (int)_q[3]);
}
	
quaternion_c	quaternion_c::operator * (const quaternion_c &q) const
{
	quaternion_c out;
		
	/* from matrix and quaternion faq
	x = w1x2 + x1w2 + y1z2 - z1y2
	y = w1y2 + y1w2 + z1x2 - x1z2
	z = w1z2 + z1w2 + x1y2 - y1x2
	
	w = w1w2 - x1x2 - y1y2 - z1z2
	*/
		
	out._q[0] = _q[3]*q._q[0] + _q[0]*q._q[3] + _q[1]*q._q[2] - _q[2]*q._q[1];
	out._q[1] = _q[3]*q._q[1] + _q[1]*q._q[3] + _q[2]*q._q[0] - _q[0]*q._q[2];
	out._q[2] = _q[3]*q._q[2] + _q[2]*q._q[3] + _q[0]*q._q[1] - _q[1]*q._q[0];
	
	out._q[3] = _q[3]*q._q[3] - _q[0]*q._q[0] - _q[1]*q._q[1] - _q[2]*q._q[2];

	return out;
}



bool	cbbox_c::lineIntersect(float min1, float max1, float min2, float max2) const
{
	if(min1 <= min2 && min2 <= max1 )
		return true;
	
	if(min1 <= max2 && max2 <= max1 )
		return true;
		
	if(min2 <= min1 && min1 <= max2 )
		return true;
			
	if(min2 <= max1 && max1 <= max2 )
		return true;
		
	return false;
}

bool	cbbox_c::intersect(const cbbox_c &bbox) const
{
#if 1
	return(	_mins[0] <= bbox._maxs[0]	&& 
		_mins[1] <= bbox._maxs[1]	&&
		_mins[2] <= bbox._maxs[2]	&&
		
		_maxs[0] >= bbox._mins[0]	&& 
		_maxs[1] >= bbox._mins[1]	&& 
		_maxs[2] >= bbox._mins[2]	);
#else
	if (	lineIntersect(_mins[0], _maxs[0], bbox._mins[0], bbox._maxs[0])	&&
		lineIntersect(_mins[1], _maxs[1], bbox._mins[1], bbox._maxs[1])	&&
		lineIntersect(_mins[2], _maxs[2], bbox._mins[2], bbox._maxs[2])	)
		return true;
	else
		return false;
#endif
}


bool	cbbox_c::intersect(const vec3_c &origin, const float radius) const
{
#if 1
	return(	_mins[0] <= origin[0] + radius	&& 
		_mins[1] <= origin[1] + radius	&&
		_mins[2] <= origin[2] + radius	&&
		
		_maxs[0] >= origin[0] - radius	&& 
		_maxs[1] >= origin[1] - radius	&& 
		_maxs[2] >= origin[2] - radius	);
#else
	cbbox_c	bbox;
		
	bbox._mins[0] = origin[0] - radius;
	bbox._mins[1] = origin[1] - radius;
	bbox._mins[2] = origin[2] - radius;
		
	bbox._maxs[0] = origin[0] + radius;
	bbox._maxs[1] = origin[1] + radius;
	bbox._mins[2] = origin[2] + radius;

	if (	lineIntersect(_mins[0], _maxs[0], bbox._mins[0], bbox._maxs[0])	&&
		lineIntersect(_mins[1], _maxs[1], bbox._mins[1], bbox._maxs[1])	&&
		lineIntersect(_mins[2], _maxs[2], bbox._mins[2], bbox._maxs[2])	)
		return true;
	else
		return false;
#endif
}

bool	cbbox_c::intersect(vec_t x0, vec_t y0, vec_t z0, vec_t x1, vec_t y1, vec_t z1) const
{
	// an infinite ray would intersect the box but if it is not
	// we must check if the ray is out side the box
	if(x0 > _maxs[0] && x1 > _maxs[0])	return false;
	if(y0 > _maxs[1] && y1 > _maxs[1])	return false;
	if(z0 > _maxs[2] && z1 > _maxs[2])	return false;
	
	if(x0 < _mins[0] && x1 < _mins[0])	return false;
	if(y0 < _mins[1] && y1 < _mins[1])	return false;
	if(z0 < _mins[2] && z1 < _mins[2])	return false;
		
	if(isInside(x0, y0, z0))
		return true;
	
	if(isInside(x1, y1, z1))
		return true;
	
	vec3_c t(x1-x0, y1-y0, z1-z0);
	
	vec_t lent = t.normalize();
	if(lent == 0.0)
		return false;

	vec3_c s((_maxs[0]+_mins[0])/2-x0, (_maxs[1]+_mins[1])/2-y0, (_maxs[2]+_mins[2])/2-z0);

	vec_t plen = t.dotProduct(s);

	// t is the bbox center projection point on the ray
	t.scale(plen);

	if(isInside(t[0]+x0, t[1]+y0, t[2]+z0))
		return true;
		
	return false;
}

float	cbbox_c::radius() const
{
	vec3_c	corner;
	
	corner[0] = fabs(_mins[0]) > fabs(_maxs[0]) ? fabs(_mins[0]) : fabs(_maxs[0]);
	corner[1] = fabs(_mins[1]) > fabs(_maxs[1]) ? fabs(_mins[1]) : fabs(_maxs[1]);
	corner[2] = fabs(_mins[2]) > fabs(_maxs[2]) ? fabs(_mins[2]) : fabs(_maxs[2]);

	return corner.length();
}

void	cbbox_c::addPoint(const vec3_c &v)
{
	if(v[0] < _mins[0])
		_mins[0] = v[0];
		
	if(v[1] < _mins[1])
		_mins[1] = v[1];
		
	if(v[2] < _mins[2])
		_mins[2] = v[2];
	
	
	if(v[0] > _maxs[0])
		_maxs[0] = v[0];
		
	if(v[1] > _maxs[1])
		_maxs[1] = v[1];
		
	if(v[2] > _maxs[2])
		_maxs[2] = v[2];
}

bool 	cbbox_c::isZero() const
{
	if (	_mins[0] == 0 && _mins[1] == 0 && _mins[2] == 0 &&
		_maxs[0] == 0 && _maxs[1] == 0 && _maxs[2] == 0)
		return true;
	else
		return false;
}
	
const char*	cbbox_c::toString() const
{
	return va("(%i %i %i) (%i %i %i)", (int)_mins[0], (int)_mins[1], (int)_mins[2], (int)_maxs[0], (int)_maxs[1], (int)_maxs[2]);
}



void	cplane_c::fromThreePointForm(const vec3_c &v1, const vec3_c &v2, const vec3_c &v3)
{
	vec3_c	v, u;
	vec3_c	normal;
	float	dist;
	
	
	// build directional vectors
	u = v2 - v1;
	v = v3 - v1;
	
	// create normal
	normal.crossProduct(v, u);
	normal.normalize();
	
	// create distance from origin
	dist = v1.dotProduct(normal);
	
	// finally setup the plane
	set(normal, dist);
}

void	cplane_c::setType()
{
	vec_t		ax, ay, az;

	if(_normal[0] >= 1.0 /*|| _normal[0] == -1.0*/)
	{
		_type = PLANE_X;
		return;
	}
	
	if(_normal[1] >= 1.0 /*|| _normal[1] == -1.0*/)
	{
		_type = PLANE_Y;
		return;
	}
	
	if(_normal[2] >= 1.0 /*|| _normal[2] == -1.0*/)
	{
		_type = PLANE_Z;
		return;
	}
	
	ax = fabs(_normal[0]);
	ay = fabs(_normal[1]);
	az = fabs(_normal[2]);
	
	if(ax >= ay && ax >= az)
	{
		_type = PLANE_ANYX;
		return;
	}
	
	if(ay >= ax && ay >= az)
	{
		_type = PLANE_ANYY;
		return;
	}
	
	_type = PLANE_ANYZ;
}

void	cplane_c::setSignBits()
{
	// for fast box on planeside test

	_signbits = 0;
	
	if(_normal[0] < 0)
		_signbits |= 1<<0;
		
	if(_normal[1] < 0)
		_signbits |= 1<<1;
		
	if(_normal[2] < 0)
		_signbits |= 1<<2;
}

void	cplane_c::normalize()
{
	vec_t len = _normal.length();
	
	if(len)
	{
		_normal[0] /= len;
		_normal[1] /= len;
		_normal[2] /= len;
		_dist /= len;
	}
}

plane_side_e	cplane_c::onSide(const cbbox_c &bbox, bool use_signbits) const
{	
	// fast axial cases
	if(_type <= PLANE_Z)
	{
		if(_dist <= bbox._mins[_type])
			return SIDE_FRONT;
			
		if(_dist >= bbox._maxs[_type])
			return SIDE_BACK;
				
		return SIDE_CROSS;
	}
		
	// general case
	vec_t dist1;
	vec_t dist2;
	
	if(use_signbits)
	{
		switch(_signbits)
		{
			case 0:
				dist1 = _normal[0]*bbox._maxs[0] + _normal[1]*bbox._maxs[1] + _normal[2]*bbox._maxs[2] - _dist;
				dist2 = _normal[0]*bbox._mins[0] + _normal[1]*bbox._mins[1] + _normal[2]*bbox._mins[2] - _dist;
				break;
		
			case 1:
				dist1 = _normal[0]*bbox._mins[0] + _normal[1]*bbox._maxs[1] + _normal[2]*bbox._maxs[2] - _dist;
				dist2 = _normal[0]*bbox._maxs[0] + _normal[1]*bbox._mins[1] + _normal[2]*bbox._mins[2] - _dist;
				break;
				
			case 2:
				dist1 = _normal[0]*bbox._maxs[0] + _normal[1]*bbox._mins[1] + _normal[2]*bbox._maxs[2] - _dist;
				dist2 = _normal[0]*bbox._mins[0] + _normal[1]*bbox._maxs[1] + _normal[2]*bbox._mins[2] - _dist;
				break;
				
			case 3:
				dist1 = _normal[0]*bbox._mins[0] + _normal[1]*bbox._mins[1] + _normal[2]*bbox._maxs[2] - _dist;
				dist2 = _normal[0]*bbox._maxs[0] + _normal[1]*bbox._maxs[1] + _normal[2]*bbox._mins[2] - _dist;
				break;
			
			case 4:
				dist1 = _normal[0]*bbox._maxs[0] + _normal[1]*bbox._maxs[1] + _normal[2]*bbox._mins[2] - _dist;
				dist2 = _normal[0]*bbox._mins[0] + _normal[1]*bbox._mins[1] + _normal[2]*bbox._maxs[2] - _dist;
				break;
		
			case 5:
				dist1 = _normal[0]*bbox._mins[0] + _normal[1]*bbox._maxs[1] + _normal[2]*bbox._mins[2] - _dist;
				dist2 = _normal[0]*bbox._maxs[0] + _normal[1]*bbox._mins[1] + _normal[2]*bbox._maxs[2] - _dist;
				break;
			
			case 6:
				dist1 = _normal[0]*bbox._maxs[0] + _normal[1]*bbox._mins[1] + _normal[2]*bbox._mins[2] - _dist;
				dist2 = _normal[0]*bbox._mins[0] + _normal[1]*bbox._maxs[1] + _normal[2]*bbox._maxs[2] - _dist;
				break;
				
			case 7:
				dist1 = _normal[0]*bbox._mins[0] + _normal[1]*bbox._mins[1] + _normal[2]*bbox._mins[2] - _dist;
				dist2 = _normal[0]*bbox._maxs[0] + _normal[1]*bbox._maxs[1] + _normal[2]*bbox._maxs[2] - _dist;
				break;
		
			default:
				dist1 = dist2 = 0;		// shut up compiler
				assert(0);
				break;
		}
	}
	else
	{
		vec3_c	corners[2];
	
		corners[0][0] = (_normal[0] < 0) ? bbox._mins[0] : bbox._maxs[0];
		corners[0][1] = (_normal[1] < 0) ? bbox._mins[1] : bbox._maxs[1];
		corners[0][2] = (_normal[2] < 0) ? bbox._mins[2] : bbox._maxs[2];
	
		corners[1][0] = (_normal[0] < 0) ? bbox._maxs[0] : bbox._mins[0];
		corners[1][1] = (_normal[1] < 0) ? bbox._maxs[1] : bbox._mins[1];
		corners[1][2] = (_normal[2] < 0) ? bbox._maxs[2] : bbox._mins[2];
		
		dist1 = _normal.dotProduct(corners[0]) - _dist;
		dist2 = _normal.dotProduct(corners[1]) - _dist;
	}

	bool front = (dist1 >= 0);
	
	if(dist2 < 0)
	{
		if(front)
			return SIDE_CROSS;
		else
			return SIDE_BACK;
	}
		
	return SIDE_FRONT;
}

	
	
const char*	cplane_c::toString() const
{
	return va("(%i %i %i %i)", (int)_normal[0], (int)_normal[1], (int)_normal[2], (int)_dist);
}
	
bool	cplane_c::operator == (const cplane_c &p) const
{
#if 1
		if(	fabs(p._normal[0] - _normal[0]) < NORMAL_EPSILON
			&& fabs(p._normal[1] - _normal[1]) < NORMAL_EPSILON
			&& fabs(p._normal[2] - _normal[2]) < NORMAL_EPSILON
			&& fabs(p._dist - _dist) < DIST_EPSILON )
			return true;
#else
		if(	p._normal[0] == _normal[0]
			&& p._normal[1] == _normal[1]
			&& p._normal[2] == _normal[2]
			&& p._dist == dist)
			return true;
#endif
		return false;
}





void 	Vector3_MakeNormalVectors(const vec3_c &forward, vec3_c &right, vec3_c &up)
{
	float		d;

	// this rotate and negat guarantees a vector
	// not colinear with the original
	right[1] = -forward[0];
	right[2] = forward[1];
	right[0] = forward[2];

	d = right.dotProduct(forward);
	vec3_c f = forward;
	f *= -d;
	right += f;
	//right.normalizeFast();
	right.normalize();
	up.crossProduct(right, forward);
}



void 	Vector3_ProjectOnPlane(vec3_c &dst, const vec3_c &p, const vec3_c &normal)
{
	float d;
	vec3_c n;
	float inv_denom;

	inv_denom = 1.0F / normal.dotProduct(normal);

	d = normal.dotProduct(p) * inv_denom;

	n = normal;
	n *= inv_denom;
	n *= d;
	
	dst = p - n;
}


void 	Vector3_Perpendicular(vec3_c &dst, const vec3_c &src)
{
	int	pos;
	int i;
	float minelem = 1.0F;
	vec3_c tempvec;

	//
	// find the smallest magnitude axially aligned vector
	//
	for(pos=0, i=0; i < 3; i++)
	{
		if(fabs( src[i] ) < minelem )
		{
			pos = i;
			minelem = fabs(src[i]);
		}
	}
	
	tempvec.clear();

	tempvec[pos] = 1.0;

	//
	// project the point onto the plane defined by src
	//
	Vector3_ProjectOnPlane(dst, tempvec, src);

	//
	// normalize the result
	//
	dst.normalize();
}

void	Vector3_ToAngles(const vec3_c &value1, vec3_c &angles)
{
	float	forward;
	float	yaw, pitch;
	
	if (value1[1] == 0 && value1[0] == 0)
	{
		yaw = 0;
		if (value1[2] > 0)
			pitch = 90;
		else
			pitch = 270;
	}
	else
	{
		if (value1[0])
			yaw = (int) (atan2(value1[1], value1[0]) * 180 / M_PI);
		else if (value1[1] > 0)
			yaw = 90;
		else
			yaw = -90;
		if (yaw < 0)
			yaw += 360;

		forward = sqrt (value1[0]*value1[0] + value1[1]*value1[1]);
		pitch = (int) (atan2(value1[2], forward) * 180 / M_PI);
		if (pitch < 0)
			pitch += 360;
	}

	angles[PITCH] = -pitch;
	angles[YAW] = yaw;
	angles[ROLL] = 0;
}



/*
=============
VectorToString

This is just a convenience function
for printing vectors
=============
*/
char*	Vector3_String(const vec3_t v)
{
	return va("(%i %i %i)", (int)v[0], (int)v[1], (int)v[2]);
}




static int	Curve_TestFlatness(int maxflat, vec4_t point0, vec4_t point1, vec4_t point2)
{
	vec3_t		v1, v2, v3;
	vec3_t		t, n;
	float		dist, d, len;
	int			ft0, ft1;
	
	Vector3_Subtract(point2, point0, n);
	len = Vector3_Normalize(n);
	
	if (!len)
		return 0;
	
	Vector3_Subtract(point1, point0, t);
	d = -Vector3_DotProduct(t, n);
	Vector3_MA(t, d, n, t);
	dist = Vector3_Length(t);
	
	if(fabs (dist) <= maxflat)
		return 0;
	
	Vector3_Average(point1, point0, v1);
	Vector3_Average(point2, point1, v2);
	Vector3_Average(v1, v2, v3);
	
	ft0 = Curve_TestFlatness(maxflat, point0, v1, v3);
	ft1 = Curve_TestFlatness(maxflat, v3, v2, point2);
	
	return 1 + (int)floor(X_max(ft0, ft1) + 0.5f);
}

void	Curve_GetFlatness(int maxflat, vec4_c *points, int *mesh_cp, int *flat)
{
	int			i, p;
	int			u, v;
	
	flat[0] = flat[1] = 0;
	
	for(v=0; v<mesh_cp[1]-1; v += 2)
	{
		for(u=0; u<mesh_cp[0]-1; u += 2)
		{
			p = v * mesh_cp[0] + u;
			
			i = Curve_TestFlatness(maxflat, points[p], points[p+1], points[p+2]);
			flat[0] = X_max(flat[0], i);
			
			i = Curve_TestFlatness(maxflat, points[p+mesh_cp[0]], points[p+mesh_cp[0]+1], points[p+mesh_cp[0]+2]);
			flat[0] = X_max(flat[0], i);
			
			i = Curve_TestFlatness(maxflat, points[p+2*mesh_cp[0]], points[p+2*mesh_cp[0]+1], points[p+2*mesh_cp[0]+2]);
			flat[0] = X_max(flat[0], i);
			
			
			
			i = Curve_TestFlatness(maxflat, points[p], points[p+mesh_cp[0]], points[p+2*mesh_cp[0]]);
			flat[1] = X_max (flat[1], i);
			
			i = Curve_TestFlatness(maxflat, points[p+1], points[p+mesh_cp[0]+1], points[p+2*mesh_cp[0]+1]);
			flat[1] = X_max(flat[1], i);
			
			i = Curve_TestFlatness(maxflat, points[p+2], points[p+mesh_cp[0]+2], points[p+2*mesh_cp[0]+2]);
			flat[1] = X_max(flat[1], i);
			
			
		}
	}
}


static void	Curve_EvalQuadricBezier(float t, vec4_t point0, vec4_t point1, vec4_t point2, vec4_t outa)
{
	float qt = t * t;
	float dt = 2.0f * t;
	float tt;
	
	vec4_c	tmp;
	vec4_c	out;
	
	tt = 1.0f - dt + qt;
	out = point0;
	out.scale(tt);
		
	
	tt = dt - 2.0f * qt;
	tmp = point1;
	tmp.scale(tt);
	out += tmp;
	
	tmp = point2;
	tmp.scale(qt);
	out += tmp;
	
	out.copyTo(outa);
}

void	Curve_EvalQuadricBezierPatch(vec4_c *points, int *mesh_cp, int *tess, vec4_c *out)
{
	int		patches_num[2];
	int		tess_num[2];
	
	int		index[3];
	int		dstpitch;
	
	int		i, u, v, x, y;
	
	float	s, t, step[2];
	
	vec4_c*	tvec, pv[3][3], v1, v2, v3;
	
	patches_num[0] = mesh_cp[0] / 2;
	patches_num[1] = mesh_cp[1] / 2;
	
	dstpitch = patches_num[0] * tess[0] + 1;
	
	step[0] = 1.0f / (float)tess[0];
	step[1] = 1.0f / (float)tess[1];
	
	for(v=0; v<patches_num[1]; v++)
	{
		// last patch has one more row
		if(v < patches_num[1] - 1)
			tess_num[1] = tess[1];
		else
			tess_num[1] = tess[1] + 1;
		
		
		for(u=0; u<patches_num[0]; u++)
		{
			// last patch has one more column
			if(u < patches_num[0] - 1)
				tess_num[0] = tess[0];
			else
				tess_num[0] = tess[0] + 1;
			
			index[0] = (v * mesh_cp[0] + u) * 2;
			index[1] = index[0] + mesh_cp[0];
			index[2] = index[1] + mesh_cp[0];
			
			// current 3x3 patch control points
			for(i=0; i<3; i++)
			{
				Vector4_Copy(points[index[0]+i], pv[i][0]);
				Vector4_Copy(points[index[1]+i], pv[i][1]);
				Vector4_Copy(points[index[2]+i], pv[i][2]);
			}
			
			t = 0.0f;
			tvec = out + v * tess[1] * dstpitch + u * tess[0];
			
			for(y=0; y<tess_num[1]; y++, t += step[1])
			{
				Curve_EvalQuadricBezier(t, pv[0][0], pv[0][1], pv[0][2], v1);
				Curve_EvalQuadricBezier(t, pv[1][0], pv[1][1], pv[1][2], v2);
				Curve_EvalQuadricBezier(t, pv[2][0], pv[2][1], pv[2][2], v3);
				
				s = 0.0f;
				
				for(x=0; x<tess_num[0]; x++, s += step[0])
				{
					Curve_EvalQuadricBezier (s, v1, v2, v3, tvec[x]);
				}
				
				tvec += dstpitch;
			}
		}
	}
}


void 	RotatePointAroundVector(vec3_c &dst, const vec3_c &dir, const vec3_c &point, vec_t degrees)
{
	// Tr3B - make it simpler and faster
	matrix_c	m;
	matrix_c	im;
	matrix_c	zrot;
	matrix_c	tmpmat;
	matrix_c	rot;
	
	vec3_c	vr, vup, vf;

	vf = dir;
	Vector3_Perpendicular(vr, vf);
	vup.crossProduct(vr, vf);

#if 1
	m[0][0] = vr[0];	m[0][1] = vup[0];	m[0][2] = vf[0];	m[0][3]=0;
	m[1][0] = vr[1];	m[1][1] = vup[1];	m[1][2] = vf[1];	m[1][3]=0;
	m[2][0] = vr[2];	m[2][1] = vup[2];	m[2][2] = vf[2];	m[2][3]=0;
	m[3][0] = 0;		m[3][1] = 0;		m[3][2] = 0;		m[3][3]=1;
#else
	//m.identity();
	m[0] = vf;
	m[1] = vr;	m[1].negate();
	m[2] = vup;
#endif
	
	m.copyTranspose(im);

	zrot.setupZRotation(degrees);
	
	tmpmat = m * zrot;
	rot = tmpmat * im;
	
	dst = rot * point;
}



void 	Angles_ToVectors(const vec3_c &angles, vec3_c &forward, vec3_c &right, vec3_c &up)
{
	matrix_c	matrix;
	
	matrix.fromAngles(angles);
	matrix.toVectorsFRU(forward, right, up);
}


void 	Angles_ToVectorsFLU(const vec3_c &angles, vec3_c &forward, vec3_c &left, vec3_c &up)
{
	matrix_c	matrix;
	
	matrix.fromAngles(angles);
	matrix.toVectorsFLU(forward, left, up);
}






	
float	 LerpAngle(float a2, float a1, float frac)
{
	if (a1 - a2 > 180)
		a1 -= 360;
	if (a1 - a2 < -180)
		a1 += 360;
	return a2 + frac * (a1 - a2);
}


float	anglemod(float a)
{
#if 0
	if (a >= 0)
		a -= 360*(int)(a/360);
	else
		a += 360*( 1 + (int)(-a/360) );
#endif
	a = (360.0/65536) * ((int)(a*(65536/360.0)) & 65535);
	return a;
}


float	CalcFOV(float fov_x, float width, float height)
{
	float	a;
	float	x;

	//if(fov_x < 1 || fov_x > 179)
	//	cgi.Com_Error(ERR_DROP, "CalcFOV: bad field of view: %f", fov_x);
	
	X_clamp(fov_x, 1, 179);

	x = width/tan(fov_x/360*M_PI);

	a = atan (height/x);

	a = a*360/M_PI;

	return a;
}


float	X_frand()
{
	return (rand()&32767)* (1.0/32767);
}

float	X_crand()
{
	return (rand()&32767)* (2.0/32767) - 1;
}

