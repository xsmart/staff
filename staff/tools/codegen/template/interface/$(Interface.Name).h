// This file generated by staff_codegen
// For more information please visit: http://code.google.com/p/staff/

#ifndef _$(Interface.Name)_h_
#define _$(Interface.Name)_h_

\
#var includeList 0
#var includeMap 0
#var includeDataObject 0
\
#foreach $(Interface.Structs)
#ifeq($(Struct.Extern),0)
#foreach $(Struct.Members)
#ifeq($(Param.DataType.Name),list)
#var includeList 1
#ifeqend
#ifeq($(Param.DataType.Name),map)
#var includeMap 1
#ifeqend
#ifeq($(Param.DataType.Type),dataobject)
#var includeDataObject 1
#ifeqend
#end       // foreach Struct.Members
#ifeqend
#end       // foreach Interface.Structs
\
#foreach $(Interface.Typedefs)
#ifeq($(Typedef.Extern),0)
#ifeq($(Typedef.DataType.Name),list)
#var includeList 1
#ifeqend
#ifeq($(Typedef.DataType.Name),map)
#var includeMap 1
#ifeqend
#ifeq($(Typedef.DataType.Type),dataobject)
#var includeDataObject 1
#ifeqend
#ifeqend
#end       // foreach Interface.Typedefs
\
#foreach $(Interface.Classes)
#foreach $(Class.Members)
#foreach $(Member.Params)
#ifeq($(Param.DataType.Name),list)
#var includeList 1
#ifeqend
#ifeq($(Param.DataType.Name),map)
#var includeMap 1
#ifeqend
#ifeq($(Param.DataType.Type),dataobject)
#var includeDataObject 1
#ifeqend
#end // also check return type
#ifeq($(Member.Return.Name),list)
#var includeList 1
#ifeqend
#ifeq($(Member.Return.Name),map)
#var includeMap 1
#ifeqend
#ifeq($(Member.Return.Type),dataobject)
#var includeDataObject 1
#ifeqend
#end
#end       // foreach Interface.Classes
\
\
#ifeq($($includeList),1)
#include <list>
#ifeqend
#ifeq($($includeMap),1)
#include <map>
#ifeqend
#include <staff/common/WsdlTypes.h>
#include <staff/common/IService.h>
#ifeq($($includeDataObject),1)
#include <staff/common/DataObject.h>
#ifeqend
\
#foreach $(Interface.Includes)
#include "$(Include.Name).h"
#end
\
#var sOpeningNs
#var sEndingNs
\
#ifneq($(Interface.TargetNamespace),||http://tempui.org/$(Interface.Classes.*Class.*ServiceNsName))

// *targetNamespace: $(Interface.TargetNamespace)
#ifeqend // tns
\
#ifneq($(Interface.Structs.$Count),0)   //   structs forwarding

#foreach $(Interface.Structs)
#ifeq($(Struct.Extern),0)
\
#var sNewOpeningNs $(Struct.OpeningNs)
#var sNewEndningNs $(Struct.EndingNs)
#ifneq($($sNewOpeningNs),$($sOpeningNs))
$($sEndingNs)
$($sNewOpeningNs)\
#ifeqend   // namespace changed
\
  struct $(Struct.Name);
#ifneq($($sNewOpeningNs),$($sOpeningNs))
#var sOpeningNs $($sNewOpeningNs)
#var sEndingNs $($sNewEndningNs)
#ifeqend  // namespace changed
\
#ifeqend   // extern
#end       // foreach Interface.Structs

#ifeqend   // Interface.Structs.Count = 0
\
\
#ifneq($(Interface.Typedefs.$Count),0)   //  typedefs declaration
#foreach $(Interface.Typedefs)
#ifeq($(Typedef.Extern),0)
#var sNewOpeningNs $(Typedef.OpeningNs)
#var sNewEndningNs $(Typedef.EndingNs)
#ifneq($($sNewOpeningNs),$($sOpeningNs))
$($sEndingNs)
$($sNewOpeningNs)
#ifeqend   // namespace changed
\
  typedef $(Typedef.DataType.UsedTypedef) $(Typedef.Name);\
#ifneq($(Typedef.Description),)
  //!< $(Typedef.Description)\
#ifeqend

#ifneq($($sNewOpeningNs),$($sOpeningNs))
#var sOpeningNs $($sNewOpeningNs)
#var sEndingNs $($sNewEndningNs)
#ifeqend   // namespace changed
#ifeqend   // extern
#end        // foreach Interface.Typedefs

#ifeqend
\
#ifneq($(Interface.Structs.$Count),0)
\
#foreach $(Interface.Structs)              // structs declaration
#ifeq($(Struct.Extern),0)
\
#var sNewOpeningNs $(Struct.OpeningNs)
#var sNewEndningNs $(Struct.EndingNs)
#ifneq($($sNewOpeningNs),$($sOpeningNs))
$($sEndingNs)
$($sNewOpeningNs)
#ifeqend   // namespace changed
#ifneq($(Struct.Description),)
  //! $(Struct.Description)
#ifeqend
#ifneq($(Struct.Detail),)
  /*! $(Struct.Detail) */
#ifeqend
  struct $(Struct.Name)\
#ifneq($(Struct.ParentName),)
: public $(Struct.ParentUsedName)
#else

#ifeqend
  {
#var bHaveDefaults 0
#foreach $(Struct.Members)
#foreach $(Param.Options)
    // *$($ThisNodeName): $($ThisNodeValue)
#end
#ifneq($(Param.Options.*defaultValue),)
#var bHaveDefaults 1
#ifeqend
    $(Param.DataType.UsedName) $(Param.Name);\
#ifneq($(Param.Description),)
  //!< $(Param.Description)
#else

#ifeqend
#end
#ifeq($($bHaveDefaults),1) // default constructor
#var nDefFirst 0

    $(Struct.Name)():
      \
#foreach $(Struct.Members)
#ifneq($(Param.Options.*defaultValue),)
#ifeq($($nDefFirst),1)
, \
#ifeqend
#var nDefFirst 1
#ifeq($(Param.DataType.Type),string)
$(Param.Name)("$(Param.Options.*defaultValue)")\
#else
#ifeq($(Param.DataType.Name),char)
$(Param.Name)('$(Param.Options.*defaultValue)')\
#else
$(Param.Name)($(Param.Options.*defaultValue))\
#ifeqend
#ifeqend
#ifeqend
#end

    {
    }
#ifeqend
  };

#ifneq($($sNewOpeningNs),$($sOpeningNs))
#var sOpeningNs $($sNewOpeningNs)
#var sEndingNs $($sNewEndningNs)
#ifeqend   // namespace changed
#ifeqend   // extern
#end
#ifeqend
#foreach $(Interface.Classes)

#var sNewOpeningNs $(Class.OpeningNs)
#var sNewEndningNs $(Class.EndingNs)
#ifneq($($sNewOpeningNs),$($sOpeningNs))
$($sEndingNs)
$($sNewOpeningNs)
#ifeqend   // namespace changed
#ifneq($(Class.Description),)
  //! $(Class.Description)
#else
  //!  service $(Class.ServiceNsName)
#ifeqend
#ifneq($(Class.Detail),)
  /*! $(Class.Detail) */
#ifeqend
#foreach $(Class.Options)
  // *$($ThisNodeName): $($ThisNodeValue)
#end
  class $(Class.Name): public staff::IService
  {
  public:
#foreach $(Class.Members)
#ifneq($(Member.$Num),0)

#ifeqend
#ifneq($(Member.Description),)
    //! $(Member.Description)
#ifeqend
#ifneq($(Member.Detail),)
    /*! $(Member.Detail) */
#ifeqend
#foreach $(Member.Options)
    // *$($ThisNodeName): $($ThisNodeValue)
#end
    virtual $(Member.Return.UsedName) $(Member.Name)($(Member.Params))$(Member.Const) = 0;
#end
  };
\
#ifneq($($sNewOpeningNs),$($sOpeningNs))
#var sOpeningNs $($sNewOpeningNs)
#var sEndingNs $($sNewEndningNs)
#ifeqend   // namespace changed

#end
$($sEndingNs)
#endif // _$(Interface.Name)_h_

