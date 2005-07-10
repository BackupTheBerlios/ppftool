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

#ifndef _CPARAMETER__H
#define _CPARAMETER__H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>


#define APPLY_SHORT "-a"
#define APPLY_LONG "--apply"

#define CREATE_SHORT "-c"
#define CREATE_LONG "--create"

#define HELP_SHORT "-?"
#define HELP_LONG "--help"

#define FORCE_SHORT "-f"
#define FORCE_LONG "--force"

#define PRIMODVD_SHORT "-i"
#define PRIMODVD_LONG "--primodvd-image"

#define BLOCKCHECK_SHORT "-l"
#define BLOCKCHECK_LONG "--disable-blockcheck"

#define UNDODATA_SHORT "-u"
#define UNDODATA_LONG "--include-undo-data"

#define LICENSE_LONG "--license"
#define VERSION_LONG "--version"

#define BINARY_SHORT "-b"
#define BINARY_LONG "--patched"

#define ORIGINAL_SHORT "-o"
#define ORIGINAL_LONG "--original"

#define PPF_SHORT "-p"
#define PPF_LONG "--ppf"

#define FILEID_SHORT "-d"
#define FILEID_LONG "--fileid"

#define USEVERSION_SHORT "-v"
#define USEVERSION_LONG "--use-version"

#define DESCRIPTION_SHORT "-s"
#define DESCRIPTION_LONG "--description"

#define TYPE_BINARYNAME 1
#define TYPE_ORIGINALNAME 2
#define TYPE_PPFNAME 3
#define TYPE_FILEIDNAME 4
#define TYPE_DESCRIPTIONNAME 5

struct Parameters
{
	int create;
	int apply;
	int help;
	int force;
	int primodvd;
	int blockcheck;
	int undodata;
	int license;
	int version;
	int unknown;

	int binary;
	int original;
	int ppf;
	int fileid;
	
	int description;
	int use_version;
};

class CParameter
{

	public:
		CParameter(int argc, char **argv);
		~CParameter();
		bool Evaluate();
		void ShowUsage();
		Parameters GetParameters();
		int GetUseVersion();
		char* GetString(int type);

  private:
		int CheckValueParameter(char *p);
		int m_iArgc;
		char** m_pArgv;
		Parameters m_Param;
		void* m_pOriginalName;
		void* m_pBinaryName;
		void* m_pPPFName;
		void* m_pFileIDName;
		void* m_pDescription;
		char m_pNullDescription[50];
		int m_iUseVersion;
};

#endif

