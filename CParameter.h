/* 
 * This file is distributed under the BSD license.
 *
 * Written in 2005 by Mario Mueller (cewlout[at]gmx.de) 
 *
 */
#ifndef _CPARAMETER__H
#define _CPARAMETER__H

#include <stdio.h>

class CParameter
{

	public:
		CParameter(int argc, char **argv);
		~CParameter();
		bool Evaluate();
		void ShowUsage();

  private:
		int m_iArgc;
		char** m_pArgv;

};

#endif

