/*=========================================================================

  Program:   Visualization Library
  Module:    PtSetF.cc
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

This file is part of the Visualization Library. No part of this file
or its contents may be copied, reproduced or altered in any way
without the express written consent of the authors.

Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen 1993, 1994 

=========================================================================*/
//
// Abstract class for objects that filter structured datasets
//
#include "PtSetF.hh"

vlPointSetFilter::vlPointSetFilter()
{
  this->Input = NULL;
}

vlPointSetFilter::~vlPointSetFilter()
{
  if ( this->Input != NULL )
    {
    this->Input->UnRegister(this);
    }
}

void vlPointSetFilter::Update()
{
  // make sure input is available
  if ( !this->Input )
    {
    vlErrorMacro(<< "No input!\n");
    return;
    }

  // prevent chasing our tail
  if (this->Updating) return;

  this->Updating = 1;
  this->Input->Update();
  this->Updating = 0;

  if (this->Input->GetMTime() > this->GetMTime() || this->GetMTime() > this->ExecuteTime )
    {
    if ( this->StartMethod ) (*this->StartMethod)(this->StartMethodArg);
    this->Execute();
    this->ExecuteTime.Modified();
    if ( this->EndMethod ) (*this->EndMethod)(this->EndMethodArg);
    }
}

void vlPointSetFilter::PrintSelf(ostream& os, vlIndent indent)
{
  if (this->ShouldIPrint(vlPointSetFilter::GetClassName()))
    {
    vlFilter::PrintSelf(os,indent);

    if ( this->Input )
      {
      os << indent << "Input: (" << this->Input << ")\n";
      }
    else
      {
      os << indent << "Input: (none)\n";
      }
   }
}
