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
	m_pBinaryName=NULL;
	m_pOriginalName=NULL;
	m_pPPFName=NULL;
	m_pFileIDName=NULL;
	m_pDescription=NULL;
	m_iUseVersion=0;
}

CParameter::~CParameter()
{
	if(m_pBinaryName!=NULL)
	{
		free(m_pBinaryName);
	}

	if(m_pOriginalName!=NULL)
	{
		free(m_pOriginalName);
	}

	if(m_pPPFName!=NULL)
	{
		free(m_pPPFName);
	}

	if(m_pFileIDName!=NULL)
	{
		free(m_pFileIDName);
	}

	if(m_pDescription!=NULL)
	{
		free(m_pDescription);
	}

}

bool CParameter::Evaluate()
{
	bool RetVal;
	int i;

	RetVal=true;

	// Parameterstructure reset.
	memset(&m_Param,0,sizeof(m_Param));

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
				int ret = CheckValueParameter(m_pArgv[i]);

				if(ret==1)
				{
					printf("Unknown Parameter: %s\n",m_pArgv[i]);
					m_Param.unknown+=1;
				}
				else if(ret==2)
				{
					m_Param.unknown+=1;
				}
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
		 || m_Param.version > 1
		 || m_Param.binary > 1
		 || m_Param.original > 1
		 || m_Param.ppf > 1
		 || m_Param.fileid > 1)
	{
		RetVal = false;
	}

	return(RetVal);
}

int CParameter::CheckValueParameter(char *p)
{
	int RetVal;
	char* value;
	int idx;

	RetVal=0;
	idx=(int)strcspn(p,"=");

	if(idx==strlen(p)) 
	{
		RetVal=1;
	}
	else
	{
		value = strchr(p,'=')+1;
		p[idx]=0x00;
		if(strcmp(BINARY_SHORT,p) == 0 || strcmp(BINARY_LONG,p) == 0)
		{
			m_Param.binary+=1;
			if(m_pBinaryName!=NULL)
			{
				free(m_pBinaryName);
				m_pBinaryName=NULL;
			}
			m_pBinaryName = malloc(strlen(value)+2);
			if(m_pBinaryName!=NULL)
			{
				memset(m_pBinaryName,0,strlen(value)+2);
				strcpy((char*)m_pBinaryName,value);
			}
			else
			{
				printf("Internal error at %s, contact author\n",p);
				RetVal=2;
			}
		}
		else if(strcmp(PPF_SHORT,p) == 0 || strcmp(PPF_LONG,p) == 0)
		{
			m_Param.ppf+=1;
			if(m_pPPFName!=NULL)
			{
				free(m_pPPFName);
				m_pPPFName=NULL;
			}
			m_pPPFName = malloc(strlen(value)+2);
			if(m_pPPFName!=NULL)
			{
				memset(m_pPPFName,0,strlen(value)+2);
				strcpy((char*)m_pPPFName,value);
			}
			else
			{
				printf("Internal error at %s, contact author\n",p);
				RetVal=2;
			}
		}
		else if(strcmp(FILEID_SHORT,p) == 0 || strcmp(FILEID_LONG,p) == 0)
		{
			m_Param.fileid+=1;
			if(m_pFileIDName!=NULL)
			{
				free(m_pFileIDName);
				m_pFileIDName=NULL;
			}
			m_pFileIDName = malloc(strlen(value)+2);
			if(m_pFileIDName!=NULL)
			{
				memset(m_pFileIDName,0,strlen(value)+2);
				strcpy((char*)m_pFileIDName,value);
			}
			else
			{
				printf("Internal error at %s, contact author\n",p);
				RetVal=2;
			}
		}
		else if(strcmp(ORIGINAL_SHORT,p) == 0 || strcmp(ORIGINAL_LONG,p) == 0)
		{
			m_Param.original+=1;
			if(m_pOriginalName!=NULL)
			{
				free(m_pOriginalName);
				m_pOriginalName=NULL;
			}
			m_pOriginalName = malloc(strlen(value)+2);
			if(m_pOriginalName!=NULL)
			{
				memset(m_pOriginalName,0,strlen(value)+2);
				strcpy((char*)m_pOriginalName,value);
			}
			else
			{
				printf("Internal error at %s, contact author\n",p);
				RetVal=2;
			}
		}
		else if(strcmp(DESCRIPTION_SHORT,p) == 0 || strcmp(DESCRIPTION_LONG,p) == 0)
		{
			m_Param.description+=1;
			if(m_pDescription!=NULL)
			{
				free(m_pDescription);
				m_pDescription=NULL;
			}
			m_pDescription = malloc(strlen(value)+2);
			if(m_pDescription!=NULL)
			{
				memset(m_pDescription,0,strlen(value)+2);
				strcpy((char*)m_pDescription,value);
			}
			else
			{
				printf("Internal error at %s, contact author\n",p);
				RetVal=2;
			}
		}
		else if(strcmp(USEVERSION_SHORT,p) == 0 || strcmp(USEVERSION_LONG,p) == 0)
		{
			m_Param.use_version+=1;
			m_iUseVersion=atoi(value);
			if(m_iUseVersion==0)
			{
				printf("Unknown Version: %s\n",value);
				RetVal=2;
			}
		}
		else
		{
			RetVal=1;
		}
		p[idx]='=';
	}

	return(RetVal);
}


Parameters CParameter::GetParameters()
{
	return(m_Param);
}

int CParameter::GetUseVersion()
{
	return(m_iUseVersion);
}

char* CParameter::GetString(int type)
{
	char* RetVal;

	switch(type)
	{
		case TYPE_BINARYNAME:
			RetVal = (char*)m_pBinaryName;
			break;
		case TYPE_ORIGINALNAME:
			RetVal = (char*)m_pOriginalName;
			break;
		case TYPE_PPFNAME:
			RetVal = (char*)m_pPPFName;
			break;
		case TYPE_FILEIDNAME:
			RetVal = (char*)m_pFileIDName;
			break;
		case TYPE_DESCRIPTIONNAME:
			RetVal = (char*)m_pDescription;
			break;
		default:
			RetVal=NULL;
			break;
	}
	return(RetVal);
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

