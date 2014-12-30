#include "mvalngbase.h"
#include "string.h"
#include "stdlib.h"

//
//******************************************************************************
//                    MVALNGBASE.CPP
//******************************************************************************
//
//
//********************************************************************************
//
//            Chris Anderson (C) UCLA 1995
//
//
//********************************************************************************
//
//
//********************************************************************************
//                    CONSTRUCTORS
//********************************************************************************
//

#define longNullValue 0

MVAlongBase::MVAlongBase()
{
     dataPointer = newLong(0);
     size        = 0;
}

MVAlongBase::MVAlongBase( const MVAlongBase& A)
{
    if(A.size == 0)
    {dataPointer = newLong(0); size = 0;}
    else
    {
    dataPointer = newLong(A.size);
    size        = A.size;
    long* Aptr;
    long* ptr;
    for(Aptr = A.dataPointer, ptr = dataPointer;
        Aptr < A.dataPointer + A.size; Aptr++, ptr++)
        *ptr = *Aptr;
    }
} 


MVAlongBase::MVAlongBase(long inSize)
{
    dataPointer = newLong(inSize);
    size        = inSize;
}
MVAlongBase::MVAlongBase(long* data, long inSize)
{
    dataPointer = newLong(inSize);
    size        = inSize;
    long* ptr;
    long* dptr;
    for(ptr = dataPointer, dptr = data;dptr < data + inSize;
        ptr++, dptr++)
        *ptr = *dptr;
}
//
//********************************************************************************
//                    DESTRUCTOR
//********************************************************************************
//
MVAlongBase::~MVAlongBase()
{
     deleteLong();
     size  = 0;
}

//
//********************************************************************************
//                 INPUT/OUTPUT
//********************************************************************************
//
ostream&  operator <<(ostream& out_stream, const MVAlongBase& A)
{
    for(long i = 0; i < A.size; i++)
    out_stream  << A.dataPointer[i] << '\n';
    return(out_stream);
}

istream&  operator >>(istream& in, MVAlongBase& A)
{
   MVAlongBase::inputLong(in, A);
   return(in);
}
//
//********************************************************************************
//                    ASSIGNMENT
//********************************************************************************
//
MVAlongBase&  MVAlongBase::operator =( const MVAlongBase& A)
{
    if(dataPointer == 0)
    { dataPointer = newLong(A.size); size  = A.size;}
//
    if(size != A.size)
    {MVAlongBase::sizeError(size, A.size);}
//  
    long* Aptr; long* ptr;
    for(Aptr = A.dataPointer, ptr = dataPointer;
        Aptr < A.dataPointer + A.size; Aptr++, ptr++)
        *ptr = *Aptr;
    return *this;
}
//
//********************************************************************************
//                    MEMBER_FUNCTIONS
//********************************************************************************
//
//
//********************************************************************************
//      Initalize Functions
//********************************************************************************
//
void MVAlongBase::initialize()
{
    deleteLong();
    dataPointer = newLong(0);
    size        = 0;
}

void MVAlongBase::initialize( const MVAlongBase& A)
{
    deleteLong();
    if(A.size == 0)
    {
     dataPointer = newLong(0);
     size        = 0;
    }
    else
    {
    dataPointer = newLong(A.size);
    size        = A.size;
    long* Aptr;
    long* ptr;
    for(Aptr = A.dataPointer, ptr = dataPointer;
        Aptr < A.dataPointer + A.size; Aptr++, ptr++)
        *ptr = *Aptr;
    }
}

void  MVAlongBase::initialize(long inSize)
{
    deleteLong();
    dataPointer = newLong(inSize);
    size        = inSize;
}

void  MVAlongBase::initialize(long* data, long inSize)
{
    deleteLong();
    dataPointer = newLong(inSize);
    size        = inSize;
    long* ptr;
    long* dptr;
    for(ptr = dataPointer, dptr = data;dptr < data + inSize;
        ptr++, dptr++)
        *ptr = *dptr;
}

void  MVAlongBase::copyToArray(long* A) const
{
    long* ptr;
    long* Aptr;
    for(ptr = dataPointer,Aptr = A; ptr < dataPointer + size;
        ptr++, Aptr++)
    *Aptr = *ptr;
}
//
//********************************************************************************
//      Resizing
//********************************************************************************
//
void  MVAlongBase::resizeTo(long n)
{
    MVAlongBase Temp;
    if( n > 0)
    {
        Temp.initialize(*this);
        this->initialize(n);

        long* Tptr;
        long* ptr;

        if(Temp.getSize() < n)
        {
        for(ptr  = dataPointer, Tptr = Temp.getDataPointer();
            Tptr < Temp.getDataPointer() + Temp.getSize();
                           Tptr++, ptr++)
        *ptr = *Tptr;
        }
        else
        {
        for(ptr  = dataPointer, Tptr = Temp.getDataPointer();
            ptr <  dataPointer + n;
                           Tptr++, ptr++)
        *ptr = *Tptr;
        }
    }
    else if(n == 0)
    {
    deleteLong();
    dataPointer = newLong(0);
    size        = 0;
    }
    else
    {MVAlongBase::reSizeError(n);}
};
//
//********************************************************************************
//      Logical Equality and Inequality
//********************************************************************************
//
int  MVAlongBase::operator == (const MVAlongBase& A) const
{
    if(size != A.size) return 0;
    if(size == 0     ) return 1; 
 
    for(long i = 0; i < size ; i++)
    if(dataPointer[i] != A.dataPointer[i]) return 0;

    return 1;
}

int  MVAlongBase::operator != (const MVAlongBase& A) const
{
    if(size != A.size) return 1;
    if(size == 0     ) return 0; 
 
    for(long i = 0; i < size ; i++)
    if(dataPointer[i] != A.dataPointer[i]) return 1; 
    
    return 0;
}
//
//********************************************************************************
//                     Input Utility
//********************************************************************************
//
void MVAlongBase::inputLong(istream& in, MVAlongBase& A)
{
//
//  This routine extracts the N values of the
//  "next" sequence of long values in the input stream
//  copies them into the MVAlongBase array A.
//
//  By "next" sequence we mean the set of numbers contained
//  in the stream which are separated by spaces or new-line
//  characters. Any initial character data in the stream is
//  skipped and the end of the sequence is triggered by
//  encountering character data or end of file (EOF).
//
//  If A has a prescribed non-zero size then this routine
//  places the N values into the first N locations of A;
//  the remainder of A's values are untouched.
//
//  If the size of A is less than N an error message is generated.
//
//  If A is of zero size (a null) array, then this routine
//  resizes A to N and copies the data into A.
//
//
    if(in.eof() != 0) return;
    long i;
    char in_char;
    char in_token[128];

    int   long_hit; int   char_hit;
    long  long_count;

    long file_position;

    file_position = in.tellg();
    long_count   = 0;

    in_char = in.get();
    while((in.eof() == 0)&&((in_char == '\n')||(in_char == ' ')))
    {in_char = in.get();}

    long_hit = 0;
    char_hit  = 0;

    while((in.eof() == 0)&&(char_hit == 0))
    {
    //
    //  Digit Processing
    //
    if((48 <= int(in_char)&&(int(in_char) <= 57)))
    {
      long_hit = 1;
      while((in.eof() == 0)&&((in_char != '\n')&& (in_char != ' ')))
      {in_char = in.get();}
      long_count++;
    }
    else
    //
    // Character Processing
    //
    {
      if(long_hit == 1) {in.putback(in_char); char_hit = 1;}
      while((char_hit == 0)&&(in.eof() == 0)&&((in_char != '\n') && (in_char != ' ')))
      {
      if(in_char == '\\') { in_char = in.get();}
      in_char = in.get();
      }
    }

    while((in.eof() == 0)&&((in_char == '\n')||(in_char ==  ' ')))
    {in_char = in.get();}

    }
//
//  Read in the data
//
    if(A.getSize() == 0)
    {A.resizeTo(long_count);}
    else
    {
    if(A.getSize() < long_count)
    {MVAlongBase::inputError( A.getSize(), long_count );}
    }

    in.clear();
    in.seekg(file_position);

    in_char = in.get();
    while((in.eof() == 0)&&((in_char == '\n')||(in_char == ' ')))
    {in_char = in.get();}

    long_hit   = 0;
    long_count = 0;
    while(in.eof() == 0)
    {
    //
    //  Digit Processing
    //
    if((48 <= int(in_char)&&(int(in_char) <= 57)))
    {
      long_hit = 1;
      i         = 0;
      while((in.eof() == 0)&&((in_char != '\n')
                            && (in_char != ' ')))
      {in_token[i] = in_char; in_char = in.get(); i++;}
      in_token[i] = '\0';
      if(strchr(in_token,'.'))
      {
      A[long_count] = long(strtod(in_token,NULL));
      }
      else
      {
      A[long_count] = long(strtol(in_token,NULL,10));
      }
      long_count++;
    }
    else
    //
    // Character Processing
    //
    {
    //
    // Return if have a long_hit followed by a character hit
    //
      if(long_hit == 1) {in.putback(in_char); return;}
      while((in.eof() == 0)&&((in_char != '\n') && (in_char != ' ')))
      {
      if(in_char == '\\') { in_char = in.get();}
      in_char = in.get();
      }
    }

    while((in.eof() == 0)&&((in_char == '\n')||(in_char ==  ' ')))
    {in_char = in.get();}

    }
}
//
//********************************************************************************
//                     newLong (memory allocation)
//********************************************************************************
//
long* MVAlongBase::newLong(long newSize)
{
     long* dataP;
     if(newSize > 0)
     {
        dataP = new long[newSize];
        long* ptr;
        for(ptr = dataP; ptr < dataP + newSize;  ptr++) *ptr = longNullValue;
        return dataP;
     }
     else
     {dataP = 0; return dataP;}
}
void MVAlongBase::deleteLong()
{
     if(dataPointer != 0) delete [] dataPointer;
     dataPointer = 0;
}

//
//********************************************************************************
//                     Error Handling
//********************************************************************************
//
void   MVAlongBase::inputError(long ArraySize, long RequiredSize)
{
    cerr << "MVAlongBase Array of Insufficient Size For >> Operation"
         << endl  << "Array    Size : " << ArraySize
         << endl  << "Required Size : " << RequiredSize << endl;
         exit(1);
}
void   MVAlongBase::indexError(long Index)
{
    cerr << "Index out of range in MVAlongBase.\n";
    cerr << "Offending Index Value = " << Index << endl;
    exit(1);
};
void   MVAlongBase::sizeError(long Lsize, long Rsize)
{
    cerr << "Error : Assignment of unequal sized MVAlongBase \n";
    cerr << "Left Operand : " << Lsize   << endl;
    cerr << "Rght Operand : " << Rsize << endl;
    exit(1);
};
void   MVAlongBase::reSizeError(long size)
{
    cerr << "Error : invalid size for resizing of MVAlongBase \n";
    cerr << "Offending Size  : " << size   << endl;
    exit(1);
};
//
//********************************************************************************
//                     CPP File End
//********************************************************************************
//

  
