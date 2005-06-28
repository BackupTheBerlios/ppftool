/*
 * BSD License
 * Copyright (c) 2005 Mario Mueller (cewlout[at]gmx.de)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <stdio.h>
#include "CEndian.h"
#include "CParameter.h"
#include "CPPF.h"
#include "License.h"

#include <string.h>

#define VERSION "1.0.0"
#define DATE "Jun 27 2005"

int main(int argc, char **argv)
{

	CParameter *param = new CParameter(argc, argv);
	CEndian *endian = new CEndian();
	CPPF *ppf = new CPPF(param, endian);

	// Evaluate parameters given in shell/console, show Usage if something is
	// inconsistent
	if(param->Evaluate() == false && param->GetParameters().unknown >= 1)
	{
		delete(param);
		delete(endian);
		return(-1);
	}
	else if(param->Evaluate() == false && param->GetParameters().unknown == 0)
	{
		param->ShowUsage();
		delete(param);
		delete(endian);
		return(-1);
	}

	// View license
	if(param->GetParameters().license == 1)
	{
		printf("%s",license);
		delete(param);
		delete(endian);
		return(0);
	}

	// View help
	if(param->GetParameters().help == 1)
	{
		param->ShowUsage();
		delete(param);
		delete(endian);
		return(0);
	}

	// View version
	if(param->GetParameters().version == 1)
	{
		printf("Version ........ : %s\n",VERSION);
		printf("Date ........... : %s\n",DATE);
		printf("Compilestamp ... : %s %s\n",__DATE__,__TIME__);
		if(endian->BigEndian()==true)
		{
			printf("Endian Format .. : %s\n","Big Endian");
		}
		else if(endian->LittleEndian()==true)
		{
			printf("Endian Format .. : %s\n","Little Endian");
		}
		delete(param);
		delete(endian);
		return(0);
	}

	// Evaluate CPPF, to go sure everything the user entered in shell is okay
	if(ppf->Evaluate()==false)
	{
		delete(param);
		delete(endian);
		delete(ppf);
		return(-1);
	}


	delete(param);
	delete(endian);
	delete(ppf);
	return(0);
}

