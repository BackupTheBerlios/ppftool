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

