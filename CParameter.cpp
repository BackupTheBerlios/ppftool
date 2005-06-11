/* 
 * This file is distributed under the BSD license.
 *
 * Written in 2005 by Mario Mueller (cewlout[at]gmx.de) 
 *
 */
#include "CParameter.h"

CParameter::CParameter(int argc, char **argv)
{
	m_iArgc = argc;
	m_pArgv = argv;
}

CParameter::~CParameter()
{
}

bool CParameter::Evaluate()
{
	return(false);
}

void CParameter::ShowUsage()
{
  printf("Usage: ppftool [OPTION...]\n");
  printf("ppftool is able to create and apply all versions of ppf-patches.\n");
  printf("See www.paradogs.com \n");
  printf("\n");
  printf("Examples:\n");
  printf("  ppftool -a -f -p=patch.ppf -o=binary.bin\n");
  printf("  ppftool -c -p=patch.ppf -o=binary.bin -p=patched.bin -s=\"Text\" -d=id.diz\n");
  printf("  ppftool -c -v=1 -p=patch.ppf -o=binary.bin -p=patched.bin\n");
  printf("\n");
  printf(" Main operation mode:\n");
  printf("  -c, --create              create ppf-file\n");
  printf("  -a, --apply               apply ppf-file\n");
  printf("\n");
  printf(" Files modifiers:\n");
  printf("  -b, --patched=FILE        binary-file in modified state\n");
  printf("  -o, --original=FILE       binary-file in original state\n");
  printf("  -p, --ppf=FILE            ppf-file (output or input)\n");
  printf("  -d, --fileid=FILE         file_id.diz\n");
  printf("\n");
  printf(" Operation modifiers: \n");
  printf("  -f, --force               force patching if needed\n");
  printf("  -v, --use-version=VER     use ppf-version [1/2/3] (default=3)\n");
  printf("  -i, --primodvd-image      binary files are primodvd-files\n");
  printf("  -l, --disable-blockcheck  disables blockcheck\n");
  printf("  -u, --include-undo-data   includes undo-data\n");
  printf("  -s, --description=\"TEXT\"  use \"TEXT\" as short patch-description\n");
  printf("\n");
  printf(" Other options:\n");
  printf("\n");
  printf("  -?, --help                 Give this help list\n");
  printf("      --license              Print license and exit\n");
  printf("      --version              Print program versio\n");

}

