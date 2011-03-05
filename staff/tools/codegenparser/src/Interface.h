/*
 *  Copyright 2011 Utkin Dmitry
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */
 
/* 
 *  This file is part of the WSF Staff project.
 *  Please, visit http://code.google.com/p/staff for more information.
 */

#ifndef _INTERFACE_H_
#define _INTERFACE_H_

#include <string>
#include <list>
#include <map>

namespace staff
{
namespace codegen
{
  typedef std::list<std::string> TStringList; //!< string list
  typedef std::map<std::string, std::string> TStringMap; //!< string map

  //! data type
  struct SDataType
  {
    enum EDataType  //! data type enum
    {
      EUnknown,     //!<  unknown
      EGeneric,     //!<  generic(supported by staff)
      EString,      //!<  string type
      EDataObject,  //!<  DataObject
      EEnum,        //!<  enum
      EStruct,      //!<  struct
      ETypedef,     //!<  typedef
      ETemplate     //!<  template container (list, map, etc)
    };

    bool                    bIsConst;    //!<  const type
    bool                    bIsRef;      //!<  reference type
    EDataType               eType;       //!<  data type enum
    std::string             sNodeName;   //!<  SOAP node name
    std::string             sUsedName;   //!<  name as used
    std::string             sName;       //!<  type name (int, string, etc.)
    std::string             sNamespace;  //!<  namespace
    std::list<SDataType>    lsParams;    //!<  template parameters

    //! default constructor
    /*! non-const, not a ref, Generic datatype */
    SDataType();
  };

  //!  parameter
  struct SParam
  {
    SDataType    stDataType;  //!<  param data type
    std::string  sName;       //!<  param name
    std::string  sDescr;      //!<  param description
    std::string  sDetail;     //!<  detailed description
    TStringMap   mOptions;    //!<  param metacomments options
  };

  //!  service operation
  struct SMember
  {
    SParam             stReturn;       //!<  return type
    std::string        sName;          //!<  operation name
    std::list<SParam>  lsParamList;    //!<  parameters
    bool               bIsConst;       //!<  operation is const
    std::string        sDescr;         //!<  operation description
    std::string        sDetail;        //!<  detailed description
    bool               bIsAsynch;      //!<  operation is asynchronous(client)
    TStringMap         mOptions;       //!<  member metacomments options

    SMember();
  };


  //! base type for data types
  struct SBaseType
  {
    //!< base type enum
    enum EType
    {
      EUnknown = 0, //!< unknown/unintialized
      EEnum    = 1, //!< type is enum
      EStruct  = 2, //!< type is struct
      ETypedef = 4, //!< type is typedef
      EAny = EEnum|EStruct|ETypedef //!< any type
    };

    EType               eType;          //!<  type
    std::string         sName;          //!<  name
    std::string         sNamespace;     //!<  namespace
    std::string         sOwnerName;     //!<  owner struct name in format StructName[::SubType]
    std::string         sDescr;         //!<  service description
    std::string         sDetail;        //!<  detailed description
    bool                bExtern;        //!<  imported from other interface
    bool                bForward;       //!<  is forward declaration
    TStringMap          mOptions;       //!<  metacomments options

    SBaseType();
  };

  //! enum
  struct SEnum: public SBaseType
  {
    //! enum member
    struct SEnumMember
    {
      std::string sName;   //!<  enum member name
      std::string sValue;  //!<  enum member value (optional)
    };

    std::list<SEnumMember>  lsMember;     //!<  members

    SEnum();
  };

  //! struct
  struct SStruct: public SBaseType
  {
    std::string         sParentName;      //!<  parent struct name (with namespace as used)
    std::string         sParentNamespace; //!<  parent struct namespace (actual)
    std::list<SParam>   lsMember;         //!<  struct fields
    std::list<SStruct>  lsStruct;         //!<  sub struct list
    std::list<SEnum>    lsEnum;           //!<  sub enum list

    SStruct();
  };

  //! typedef
  struct STypedef: public SBaseType
  {
    SDataType           stDataType;     //!<  defined data type

    STypedef();
  };

  //! service class
  struct SClass: public SBaseType
  {
    TStringList         lsModules;      //!<  axis2/c modules list to engage
    std::list<SMember>  lsMember;       //!<  service operations
  };

  //! include info
  struct SInclude
  {
    std::string sInterfaceName;      //!<  interface name
    std::string sNamespace;          //!<  interface namespace
    std::string sFileName;           //!<  file name
    std::string sTargetNs;           //!<  target namespace
  };

  //! service interface
  struct SInterface
  {
    std::string           sName;          //!<  interface name, based on input filename
    std::string           sNamespace;     //!<  interface main namespace
    std::string           sFileName;      //!<  input filename
    std::string           sTargetNs;      //!<  target namespace
    std::list<SInclude>   lsInclude;      //!<  included files
    std::list<SEnum>      lsEnum;         //!<  enum list
    std::list<STypedef>   lsTypedef;      //!<  typedef list
    std::list<SStruct>    lsStruct;       //!<  struct list
    std::list<SClass>     lsClass;        //!<  service classes list
  };

  //! project
  struct SProject
  {
    std::string            sName;         //!<  project name
    std::string            sNamespace;    //!<  component namespace
    std::list<SInterface>  lsInterfaces;  //!<  interface list
  };
}
}

#endif // _INTERFACE_H_