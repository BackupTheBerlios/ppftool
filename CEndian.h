/* 
 * This file is distributed under the BSD license.
 *
 * Written in 2005 by Mario Mueller (cewlout[at]gmx.de) 
 *
 */
#ifndef _CENDIAN__H
#define _CENDIAN__H

class CEndian
{

	public:
		CEndian();
		~CEndian();
		bool LittleEndian();
		bool BigEndian();
};

#endif

