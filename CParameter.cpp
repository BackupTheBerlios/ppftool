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

#include "CParameter.h"

CParameter::CParameter(int argc, char **argv)
{
	m_iArgc = argc;
	m_pArgv = argv;

	memset(&m_Param,0,sizeof(m_Param));
}

CParameter::~CParameter()
{
}

bool CParameter::Evaluate()
{
	bool RetVal;
	int i;

	RetVal=true;

	// No Parameter given?
	if(m_iArgc<=1)
	{
		RetVal=false;
	}
	else
	{
		for(i=1;i<m_iArgc;i++)
		{
			if(strcmp(CREATE_SHORT,m_pArgv[i]) == 0 || strcmp(CREATE_LONG,m_pArgv[i]) == 0)
			{
				m_Param.create+=1;
			}
			else if(strcmp(APPLY_SHORT,m_pArgv[i]) == 0 || strcmp(APPLY_LONG,m_pArgv[i]) == 0)
			{
				m_Param.apply+=1;
			}
			else if(strcmp(HELP_SHORT,m_pArgv[i]) == 0 || strcmp(HELP_LONG,m_pArgv[i]) == 0)
			{
				m_Param.help+=1;
			}
			else if(strcmp(FORCE_SHORT,m_pArgv[i]) == 0 || strcmp(FORCE_LONG,m_pArgv[i]) == 0)
			{
				m_Param.force+=1;
			}
			else if(strcmp(PRIMODVD_SHORT,m_pArgv[i]) == 0 || strcmp(PRIMODVD_LONG,m_pArgv[i]) == 0)
			{
				m_Param.primodvd+=1;
			}
			else if(strcmp(BLOCKCHECK_SHORT,m_pArgv[i]) == 0 || strcmp(BLOCKCHECK_LONG,m_pArgv[i]) == 0)
			{
				m_Param.blockcheck+=1;
			}
			else if(strcmp(UNDODATA_SHORT,m_pArgv[i]) == 0 || strcmp(UNDODATA_LONG,m_pArgv[i]) == 0)
			{
				m_Param.undodata+=1;
			}
			else if(strcmp(LICENSE_LONG,m_pArgv[i]) == 0)
			{
				m_Param.license+=1;
			}
			else if(strcmp(VERSION_LONG,m_pArgv[i]) == 0)
			{
				m_Param.version+=1;
			}
			else
			{
				printf("Unknown Parameter: %s\n",m_pArgv[i]);
				m_Param.unknown+=1;
			}
		}
	}

	// Is an unknwon Parameter given?!
	if(m_Param.unknown >= 1)
	{
		RetVal = false;
	}

	// Any Parameter given two times?
	if(m_Param.apply > 1
	   || m_Param.blockcheck > 1
		 || m_Param.create > 1
		 || m_Param.force > 1
		 || m_Param.help > 1
		 || m_Param.license > 1
		 || m_Param.primodvd > 1
		 || m_Param.undodata > 1
		 || m_Param.version > 1)
	{
		RetVal = false;
	}

	return(RetVal);
}

Parameters CParameter::GetParameters()
{

	return(m_Param);
}


void CParameter::ShowUsage()
{
  printf("Usage: ppftool [OPTION...]\n");
  printf("ppftool is able to create and apply all versions of ppf-patches.\n");
  printf("See www.paradogs.com \n");
  printf("\n");
  printf("Examples:\n");
  printf("  ppftool %s %s %s=patch.ppf %s=binary.bin\n", APPLY_SHORT, FORCE_SHORT, PPF_SHORT, ORIGINAL_SHORT);
  printf("  ppftool %s %s=patch.ppf %s=binary.bin %s=patched.bin %s=\"Text\" %s=id.diz\n", CREATE_SHORT, PPF_SHORT, ORIGINAL_SHORT, BINARY_SHORT, DESCRIPTION_SHORT, FILEID_SHORT);
  printf("  ppftool %s %s=1 %s=patch.ppf %s=binary.bin %s=patched.bin\n", CREATE_SHORT, USEVERSION_SHORT, PPF_SHORT, ORIGINAL_SHORT, BINARY_SHORT);
  printf("\n");
  printf(" Main operation mode:\n");
  printf("  %s, %-21s create ppf-file\n",CREATE_SHORT, CREATE_LONG);
  printf("  %s, %-21s apply ppf-file\n", APPLY_SHORT, APPLY_LONG);
  printf("\n");
  printf(" Files modifiers:\n");
  printf("  %s, %s=FILE        binary-file in modified state\n",BINARY_SHORT, BINARY_LONG);
  printf("  %s, %s=FILE       binary-file in original state\n", ORIGINAL_SHORT, ORIGINAL_LONG);
  printf("  %s, %s=FILE            ppf-file (output or input)\n", PPF_SHORT, PPF_LONG);
  printf("  %s, %s=FILE         file_id.diz\n", FILEID_SHORT, FILEID_LONG);
  printf("\n");
  printf(" Operation modifiers: \n");
  printf("  %s, %-21s force patching if needed\n", FORCE_SHORT, FORCE_LONG);
  printf("  %s, %s=VER     use ppf-version [1/2/3] (default=3)\n", USEVERSION_SHORT, USEVERSION_LONG);
  printf("  %s, %-21s binary files are primodvd-files\n",PRIMODVD_SHORT, PRIMODVD_LONG);
  printf("  %s, %-21s disables blockcheck\n",BLOCKCHECK_SHORT, BLOCKCHECK_LONG);
  printf("  %s, %-21s includes undo-data\n",UNDODATA_SHORT, UNDODATA_LONG);
  printf("  %s, %s=\"TEXT\"  use \"TEXT\" as short patch-description\n", DESCRIPTION_SHORT, DESCRIPTION_LONG);
  printf("\n");
  printf(" Other options:\n");
  printf("\n");
	printf("  %s, %-21s Give this help list\n",HELP_SHORT, HELP_LONG);
  printf("      %-21s Print license and exit\n",LICENSE_LONG);
  printf("      %-21s Print program version\n",VERSION_LONG);

}

