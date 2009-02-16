/*
//  Helper functions for reading GIC files
*/
#include <stdio.h>


#include "gic_reader.h"


/*
//  Helper macros
*/
#define SWAP_BYTES(val) gicSwapBytes((char *)&(val),sizeof(val))


/*
//  Helper functions
*/
void gicSwapBytes(char *buffer, int size)
{
  int i;
  char tmp;
                                                                                
  for(i=0; i<size/2; i++)
    {
      tmp = buffer[i];
      buffer[i] = buffer[size - i - 1];
      buffer[size - i - 1] = tmp;
    }
}


int gicReadRecordHelper(FILE *f, long size, void* buffer, int *wrong_order)
{
  GIC_RECORD s1, s2;

  if(buffer == NULL) return -1;
  if(f == NULL) return -2;

  /*
  //  Detect endiness
  */
  if(fread(&s1,sizeof(GIC_RECORD),1,f) != 1) return 1;
  if(s1 == size)
    {
      *wrong_order = 0;
    }
  else
    {
      *wrong_order = 1;
      SWAP_BYTES(s1);
      if(s1 != size) return 1;
    }

  if(fread(buffer,size,1,f) != 1) return 1;

  if(fread(&s2,sizeof(GIC_RECORD),1,f) != 1) return 1;
  if(wrong_order)
    {
      SWAP_BYTES(s2);
      if(s2 != size) return 1;
    }

  return 0;
}


/*
//  Interface functions
*/
int gicReadManifest(struct gicFile *f, struct gicManifest *manifest)
{
  int i, ret, wrong_order;

  if(f==NULL || manifest == NULL) return -1;

  ret = gicReadRecordHelper(f->File,sizeof(struct gicManifest),manifest,&wrong_order);
  if(ret != 0) return ret;

  f->WrongOrder = wrong_order;

  if(f->WrongOrder)
    {
      SWAP_BYTES(manifest->OmegaB);
      SWAP_BYTES(manifest->OmegaX);
      SWAP_BYTES(manifest->OmegaL);
      SWAP_BYTES(manifest->OmegaN);
      SWAP_BYTES(manifest->h100);
      SWAP_BYTES(manifest->DeltaX);
      SWAP_BYTES(manifest->nS);
      SWAP_BYTES(manifest->sigma8);
      SWAP_BYTES(manifest->kPivot);
    }

  /* Convert the job name */ 
  i = 255;
  while(i>=0 && manifest->name[i] == ' ') i--;
  manifest->name[i+1] = 0;

  return 0;
}


int gicReadFileHeader(struct gicFile *f, struct gicFileHeader *header)
{
  int ret, wrong_order;

  if(f==NULL || header == NULL) return -1;

  ret = gicReadRecordHelper(f->File,sizeof(struct gicFileHeader),header,&wrong_order);
  if(f->WrongOrder != wrong_order) ret = -3;
  if(ret != 0) return ret;

  if(f->WrongOrder)
    {
      SWAP_BYTES(header->aBegin);
      SWAP_BYTES(header->DeltaDC);
      SWAP_BYTES(header->Nx);
      SWAP_BYTES(header->Ny);
      SWAP_BYTES(header->Nz);
      SWAP_BYTES(header->seed);
      SWAP_BYTES(header->Nrec);
      SWAP_BYTES(header->Ntot);
      SWAP_BYTES(header->Lmax);
    }

  return 0;
}


int gicReadLevelHeader(struct gicFile *f, struct gicLevelHeader *header)
{
  int ret, wrong_order;

  if(f==NULL || header == NULL) return -1;

  ret = gicReadRecordHelper(f->File,sizeof(struct gicLevelHeader),header,&wrong_order);
  if(f->WrongOrder != wrong_order) ret = -3;
  if(ret != 0) return ret;

  if(f->WrongOrder)
    {
      SWAP_BYTES(header->L);
      SWAP_BYTES(header->Lmax);
      SWAP_BYTES(header->Nlev);
      SWAP_BYTES(header->Mlev);
      SWAP_BYTES(header->ind);
    }

  return 0;
}


int gicReadFortranRecordReal(struct gicFile *f, int Nrec, GIC_REAL *buffer)
{
  int i, ret, wrong_order;

  if(f==NULL || buffer == NULL) return -1;

  ret = gicReadRecordHelper(f->File,Nrec*sizeof(GIC_REAL),buffer,&wrong_order);
  if(f->WrongOrder != wrong_order) ret = -3;
  if(ret != 0) return ret;

  if(f->WrongOrder)
    {
      for(i=0; i<Nrec; i++) SWAP_BYTES(buffer[i]);
    }

  return 0;
}


int gicReadFortranRecordIntg(struct gicFile *f, int Nrec, GIC_INTEGER* buffer)
{
  int i, ret, wrong_order;

  if(f==NULL || buffer == NULL) return -1;

  ret = gicReadRecordHelper(f->File,Nrec*sizeof(GIC_INTEGER),buffer,&wrong_order);
  if(f->WrongOrder != wrong_order) ret = -3;
  if(ret != 0) return ret;

  if(f->WrongOrder)
    {
      for(i=0; i<Nrec; i++) SWAP_BYTES(buffer[i]);
    }

  return 0;
}

