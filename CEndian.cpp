/* 
 * This file is distributed under the BSD license.
 *
 * Written in 2005 by Mario Mueller (cewlout[at]gmx.de) 
 *
 */
#include "CEndian.h"

CEndian::CEndian()
{
}

CEndian::~CEndian()
{
}

bool CEndian::LittleEndian()
{
	union
	{
		short value;
		char ch[sizeof(short)];
	} endian_union;

	endian_union.value = 256;	
	return(endian_union.ch[1] == 1);
}

bool CEndian::BigEndian()
{
	return(!LittleEndian());
}

