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
}

CPPF::~CPPF()
{
}

bool CPPF::Evaluate()
{

	bool RetVal;

	RetVal=true;
	if(m_pParam->GetParameters().apply==1 && m_pParam->GetParameters().create==1)
	{
		printf("Cannot apply and create the same time.\n");
		RetVal=false;
	}
	else if(m_pParam->GetParameters().apply==0 && m_pParam->GetParameters().create==0)
	{
		printf("Please specify either create or apply.\n");
		RetVal=false;
	}
	else
	{
		//Try to open all files.
	}

	return(RetVal);
}
