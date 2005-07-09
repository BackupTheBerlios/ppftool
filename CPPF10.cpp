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

#include "CPPF10.h"

CPPF10::CPPF10(CParameter* param, CEndian* endian) :CPPF(param, endian)
{
}

CPPF10::~CPPF10()
{
}

bool CPPF10::DoPPF()
{
  bool RetVal;

  if(m_pParam->GetParameters().create==1)
  {
    CreatePPF();
  }
  else if(m_pParam->GetParameters().apply==1)
  {
    ApplyPPF();
  }
  
  return(true);
}

void CPPF10::CreatePPF()
{
  OFFT size;
  int position;
  
  if(m_oPatched != m_oOriginal)
  {
    printf("Filesizes of patched and original binary files are not equal");
    return;
  }
  
  WriteHeader();
  SEEK(m_pOriginal,0,SEEK_SET);  
  SEEK(m_pPatched,0,SEEK_SET);  
  
  position=0;
  printf("Writing Patch-Data... ");
  while(GetNext(&size))
  { 
    ExamineChunk(size, position);
    position++;
  }
  
  if(size!=0)
  {
    ExamineChunk(size, position);
  }       
  
  printf("done\n");
}

void CPPF10::ExamineChunk(OFFT amount, int position)
{
  unsigned char found[256];
  unsigned char size;
  int z, pos;
  
  for(int i=0;i<amount;i++)
  {
    if(*((unsigned char*)m_pDataO+i) != *((unsigned char*)m_pDataP+i))
    {
      size=0; z=0;
      pos=CHUNK_SIZE*position+i;
      while(*((unsigned char*)m_pDataO+i) != *((unsigned char*)m_pDataP+i) && i<amount && z < 255)
      {
        found[z++]=*((unsigned char*)m_pDataP+i);
        i++; size++;
      }
      fwrite(&pos,4,1,m_pPPF);
      fwrite(&size,1,1,m_pPPF);
      fwrite(found,size,1,m_pPPF);
    }
  }
  
}

void CPPF10::ApplyPPF()
{
  SEEK(m_pPPF,0,SEEK_SET);
  ReadHeader();
  if(strcmp(m_Header.magic, "PPF10")!=0)
  {
    printf("Patch is no PPF Version 1.0 file");
    return;
  }

  if(m_Header.method!=0)
  {
    printf("Unknown method");
    return;
  }
  
  
}


void CPPF10::ReadHeader()
{
  fread(&m_Header,sizeof(m_Header),1,m_pPPF);  
}

void CPPF10::WriteHeader()
{
  
  printf("Writing PPF-Header... ");
	memset(&m_Header,0x20,sizeof(m_Header));
	strncpy(m_Header.magic,"PPF10",5);
	m_Header.method=0;
	
	strncpy(m_Header.description,m_pParam->GetString(TYPE_DESCRIPTIONNAME),strlen(m_pParam->GetString(TYPE_DESCRIPTIONNAME)));	  
  fwrite(&m_Header,sizeof(m_Header),1,m_pPPF);
  printf("done\n");
}

