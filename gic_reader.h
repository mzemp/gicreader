#ifndef __GIC_READER_H__
#define __GIC_READER_H__


/*
//  Fortran types (will depend on a platform)
//  Currently ported to: 32/64-bit Linux
*/
#define GIC_REAL        float
#define GIC_INTEGER     int
#define GIC_INTEGER8    long long
#define GIC_RECORD      int          /* ignore non-std g77 for now */


/*
//  Helper classes
*/
struct gicFile
{
  FILE *File;
  int WrongOrder;
};


struct gicManifest
{
  char name[256];
  GIC_REAL OmegaB;
  GIC_REAL OmegaX;
  GIC_REAL OmegaL;
  GIC_REAL OmegaN;
  GIC_REAL h100;
  GIC_REAL DeltaX;
  GIC_REAL nS;
  GIC_REAL sigma8;
  GIC_REAL kPivot;
};


struct gicFileHeader
{
  GIC_REAL     aBegin;
  GIC_REAL     DeltaDC;
  GIC_INTEGER  Nx;
  GIC_INTEGER  Ny;
  GIC_INTEGER  Nz;
  GIC_INTEGER  seed;
  GIC_INTEGER  Nrec;
  GIC_INTEGER8 Ntot;
  GIC_INTEGER  Lmax;
};


struct gicLevelHeader
{
  GIC_INTEGER  L;
  GIC_INTEGER  Lmax;
  GIC_INTEGER8 Nlev;
  GIC_REAL     Mlev;
  GIC_INTEGER  ind;
  GIC_INTEGER  Nx;
};

  
int gicReadManifest(struct gicFile *f, struct gicManifest *manifest);
int gicReadFileHeader(struct gicFile *f, struct gicFileHeader *header);
int gicReadLevelHeader(struct gicFile *f, struct gicLevelHeader *header);
int gicReadFortranRecordReal(struct gicFile *f, int Nrec, GIC_REAL* buffer);
int gicReadFortranRecordIntg(struct gicFile *f, int Nrec, GIC_INTEGER* buffer);

#endif  /* __GIC_READER_H__ */
