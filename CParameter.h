/* 
 * This file is distributed under the BSD license.
 *
 * Written in 2005 by Mario Mueller (cewlout[at]gmx.de) 
 *
 */
#ifndef _CPARAMETER__H
#define _CPARAMETER__H

#include <stdio.h>
#include <string.h>

struct Parameters
{
	int create;
	int apply;
	int help;
	int license;
	int version;
};

class CParameter
{

	public:
		CParameter(int argc, char **argv);
		~CParameter();
		bool Evaluate();
		void ShowUsage();
		Parameters GetParameters();

  private:
		int m_iArgc;
		char** m_pArgv;
		Parameters m_Param;

};

#endif

