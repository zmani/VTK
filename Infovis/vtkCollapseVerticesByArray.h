/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkCollapseVerticesByArray.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkCollapseVerticesByArray - Collapse the graph given a vertex array
//
// .SECTION Description
// vtkCollapseVerticesByArray is a class which collapses the graph using
// a vertex array as the key. So if the graph has vertices sharing common
// traits then this class combines all these vertices into one. This class
// does not perform aggregation on vertex data but allow to do so for edge data.
// Users can choose one or more edge data arrays for aggregation using
// AddAggregateEdgeArray function.
//
// .SECTION Thanks
//

#ifndef __vtkCollapseVerticesByArray_h__
#define __vtkCollapseVerticesByArray_h__

#include "vtkGraphAlgorithm.h"

class vtkCollapseVerticesByArrayInternal;

class VTK_INFOVIS_EXPORT vtkCollapseVerticesByArray : public vtkGraphAlgorithm
{
public:
    static vtkCollapseVerticesByArray* New();
    vtkTypeRevisionMacro(vtkCollapseVerticesByArray, vtkGraphAlgorithm);

    void PrintSelf(ostream &os, vtkIndent indent);

    // Description:
    // Boolean to allow self loops during collapse.
    vtkGetMacro(AllowSelfLoops, bool);
    vtkSetMacro(AllowSelfLoops, bool);
    vtkBooleanMacro(AllowSelfLoops, bool);

    // Description:
    // Add arrays on which aggregation of data is allowed.
    // Default if replaced by the last value.
    void AddAggregateEdgeArray(const char* arrName);


    // Description:
    // Clear the list of arrays on which aggregation was set to allow.
    void ClearAggregateEdgeArray();

    // Description:
    // Set the array using which perform the collapse.
    vtkGetStringMacro(VertexArray);
    vtkSetStringMacro(VertexArray);


protected:

    vtkCollapseVerticesByArray();
   ~vtkCollapseVerticesByArray();

   // Description:
   // Pipeline function.
   virtual int RequestData(vtkInformation* request,
                           vtkInformationVector** inputVector,
                           vtkInformationVector* outputVector);

   // Description:
   // Pipeline funtion.
   virtual int FillOutputPortInformation(int port, vtkInformation* info);


   // Description:
   // Create output graph given all the parameters. Helper function.
   vtkGraph* Create(vtkGraph* inGraph);

   // Description:
   // Helper function.
   void FindEdge(vtkGraph* outGraph, vtkIdType source,
                 vtkIdType target, vtkIdType& edgeId);

private:
  // Description:
  // Not implemented.
  vtkCollapseVerticesByArray(const vtkCollapseVerticesByArray&);
  void operator=(const vtkCollapseVerticesByArray);


protected:
  bool            AllowSelfLoops;
  char*           VertexArray;

  vtkCollapseVerticesByArrayInternal* Internal;
};

#endif // __vtkCollapseVerticesByArray_h__
