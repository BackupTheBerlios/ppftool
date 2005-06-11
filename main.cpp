/* 
 * This file is distributed under the BSD license.
 *
 * Written in 2005 by Mario Mueller (cewlout[at]gmx.de) 
 *
 */
#include <stdio.h>
#include "CEndian.h"
#include "CParameter.h"

int main(int argc, char **argv)
{
	CParameter *param = new CParameter(argc, argv);

	// Evaluate parameters given in shell/console
	if(param->Evaluate() == false)
	{
		param->ShowUsage();
	}

	delete(param);
	return(0);
}

