#ifndef __vtkDICOMSequence_h
#define __vtkDICOMSequence_h

#include "vtkDICOMValue.h"

class vtkDICOMSequenceItem;

//! A value that is a sequence of items.
/*!
 *  This is a convenience class for constructing a sequence.
 *  Without this class, a sequence of fixed size can be created
 *  by calling AllocateSequenceData() on a vtkDICOMValue object.
 *  This class adds SetItem() and AddItem() methods to make
 *  construction of a sequence easier.
 */
class vtkDICOMSequence : public vtkDICOMValue
{
public:
  //! Construct a growable sequence with no items.
  vtkDICOMSequence() {
    this->AllocateSequenceData(vtkDICOMVR::SQ, 2);
    this->V->NumberOfValues = 0;
    this->V->VL = 0xffffffff; }

  //! Construct a sequence of fixed size.
  vtkDICOMSequence(unsigned int n) {
    this->AllocateSequenceData(vtkDICOMVR::SQ, n); }

  //! Add an item to the sequence.
  /*!
   *  After calling this method, GetNumberOfValues() will report
   *  the number of items in the sequence, but GetVL() will return
   *  the special value 0xffffffff to indicate that the sequence
   *  is growable, rather than fixed in size.
   */
  void AddItem(const vtkDICOMSequenceItem& item);

  //! Set an item in the sequence.
  /*!
   *  This method can only be used if space as been allocated within
   *  the sequence, e.g. by specifying a size when calling the constructor.
   */
  void SetItem(int i, const vtkDICOMSequenceItem& item);

  //! Use base class copy constructor.
  vtkDICOMSequence(const vtkDICOMSequence& o) : vtkDICOMValue(o) {}

  //! Use base class assignment operator.
  vtkDICOMSequence& operator=(const vtkDICOMSequence& o) {
    *(static_cast<vtkDICOMValue *>(this)) = o; return *this; }

protected:
  //! The Clear method clears the VR, but sequence VR must always be SQ
  void Clear() {}

  //! An empty value doesn't mean the same thing as an empty sequence
  bool IsEmpty() const { return this->vtkDICOMValue::IsEmpty(); }
};

#endif /* __vtkDICOMSequence_h */
