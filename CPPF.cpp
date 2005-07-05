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

#include "CPPF.h"

CPPF::CPPF(CParameter* param, CEndian *endian)
{
	m_pParam = param;
	m_pEndian = endian;
	m_pOriginal=NULL;
	m_pPatched=NULL;
	m_pPPF=NULL;
	m_pFileID=NULL;
}

CPPF::~CPPF()
{
	CloseAll();
}

bool CPPF::Evaluate()
{

	bool RetVal;

	RetVal=true;
	if(m_pParam->GetParameters().apply==1 && m_pParam->GetParameters().create==1)
	{
		printf("Cannot apply and create the same time\n");
		RetVal=false;
	}
	else if(m_pParam->GetParameters().apply==0 && m_pParam->GetParameters().create==0)
	{
		printf("Please specify either create or apply\n");
		RetVal=false;
	}
	else
	{
		RetVal = OpenAll();
	}

	return(RetVal);
}

bool CPPF::OpenAll()
{
	bool RetVal;

	RetVal=true;
	
	if(m_pParam->GetString(TYPE_ORIGINALNAME) != NULL)
	{
		m_pOriginal=fopen(m_pParam->GetString(TYPE_ORIGINALNAME),"rb+");
		if(m_pOriginal==NULL)
		{
			printf("Cannot open file \"%s\"\n",m_pParam->GetString(TYPE_ORIGINALNAME));
			RetVal=false;
		}
	}

	if(m_pParam->GetString(TYPE_BINARYNAME) != NULL)
	{
		m_pPatched=fopen(m_pParam->GetString(TYPE_BINARYNAME),"rb");
		if(m_pPatched==NULL)
		{
			printf("Cannot open file \"%s\"\n",m_pParam->GetString(TYPE_BINARYNAME));
			RetVal=false;
		}
	}

	if(m_pParam->GetString(TYPE_FILEIDNAME) != NULL)
	{
		m_pFileID=fopen(m_pParam->GetString(TYPE_FILEIDNAME),"rb");
		if(m_pFileID==NULL)
		{
			printf("Cannot open file \"%s\"\n",m_pParam->GetString(TYPE_FILEIDNAME));
			RetVal=false;
		}
	}
/*
	if(m_pParam->GetString(TYPE_PPFNAME) != NULL)
	{
		m_pPPF=fopen(m_pParam->GetString(TYPE_PPFNAME),"rb");
		if(m_pPPF==NULL)
		{
			printf("Cannot open file \"%s\"\n",m_pParam->GetString(TYPE_PPFNAME));
			RetVal=false;
		}
	}
*/

	return(RetVal);
}

void CPPF::CloseAll()
{
	if(m_pOriginal!=NULL)
	{
		fclose(m_pOriginal);
	}

	if(m_pPatched!=NULL)
	{
		fclose(m_pPatched);
	}

	if(m_pFileID!=NULL)
	{
		fclose(m_pFileID);
	}

	if(m_pPPF!=NULL)
	{
		fclose(m_pPPF);
	}

}
