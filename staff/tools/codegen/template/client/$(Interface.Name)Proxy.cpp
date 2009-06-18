// This file generated by staff_codegen
// DO NOT EDIT

#include <staff/common/Operation.h>
#include <staff/common/Exception.h>
#include <staff/common/Value.h>
#include "$(Interface.Name)Proxy.h"

namespace staff
{
///////////////////////////////////////////////////////////////////////////////////////////////////////
// forward declarations
#foreach $(Interface.Structs)
CDataObject& operator<<(CDataObject& rdoParam, const $(Struct.Name)& rstStruct);
CDataObject& operator>>(CDataObject& rdoParam, $(Struct.Name)& rstStruct);
#end

#foreach $(Interface.Typedefs)
#ifeq($(Typedef.DataType.IsTemplate),1) // для всех контейнеров должен быть сериализатор
CDataObject& operator<<(CDataObject& rdoParam, const $(Typedef.Name)& rtType);
#else // DataType.IsTemplate
#ifneq($(Typedef.DataType.Type),struct)     // !!struct!! structs already have serializator
CDataObject& operator<<(CDataObject& rdoParam, const $(Typedef.Name)& rtType);
#else
\
#ifeqend // ifneq($(Typedef.DataType.Type),struct
#ifeqend // ifeq($(Typedef.DataType.IsTemplate),1)
#ifeq($(Typedef.DataType.IsTemplate),1) // для всех контейнеров должен быть сериализатор
CDataObject& operator>>(CDataObject& rdoParam, $(Typedef.Name)& rtType);
#else // DataType.IsTemplate
#ifneq($(Typedef.DataType.Type),struct)     // !!struct!! structs already have serializator
CDataObject& operator>>(CDataObject& rdoParam, $(Typedef.Name)& rtType);
#else
\
#ifeqend // ifneq($(Typedef.DataType.Type),struct
#ifeqend // ifeq($(Typedef.DataType.IsTemplate),1)
#end // foreach $(Interface.Typedefs)


///////////////////////////////////////////////////////////////////////////////////////////////////////
// struct serializators
#foreach $(Interface.Structs)
CDataObject& operator<<(CDataObject& rdoParam, const $(Struct.Name)& rstStruct)
{
#ifneq($(Struct.Parent),)
  // serialize parent struct
  rdoParam << static_cast<const $(Struct.Parent)&>(rstStruct);

#else
\
#ifeqend
#foreach $(Struct.Members)
  CDataObject tdoParam$(Param.Name)("$(Param.Name)");
#ifeq($(Param.DataType.Type),struct)
  tdoParam$(Param.Name) << rstStruct.$(Param.Name);
#else
#ifeq($(Param.DataType.Type),typedef)
  tdoParam$(Param.Name) << rstStruct.$(Param.Name);
#else
#ifeq($(Param.DataType.Type),dataobject)
  tdoParam$(Param.Name).ApendChild(rstStruct.$(Param.Name));
#else
#ifeq($(Param.DataType.Type),generic)
  tdoParam$(Param.Name).SetValue(rstStruct.$(Param.Name));
#else
#cgerror unknown type of Param.Name: $(Struct.Name)::$(Param.DataType.Name)
#ifeqend
#ifeqend
#ifeqend
#ifeqend
  rdoParam.AppendChild(tdoParam$(Param.Name));
#end
  return rdoParam;
}

#end

///////////////////////////////////////////////////////////////////////////////////////////////////////
// struct deserializators
#foreach $(Interface.Structs)
CDataObject& operator>>(CDataObject& rdoParam, $(Struct.Name)& rstStruct)
{
#ifneq($(Struct.Parent),)
  // deserialize parent struct
  rdoParam >> static_cast<$(Struct.Parent)&>(rstStruct);

#else
\
#ifeqend
#foreach $(Struct.Members)
#ifeq($(Param.DataType.Type),struct)
  rdoParam("$(Param.Name)") >> rstStruct.$(Param.Name);
#else
#ifeq($(Param.DataType.Type),typedef)
  rdoParam("$(Param.Name)") >> rstStruct.$(Param.Name);
#else
#ifeq($(Param.DataType.Type),dataobject)
  rstStruct.$(Param.Name) = *rdoParam("$(Param.Name)").Begin();
#else
#ifeq($(Param.DataType.Name),std::string)
  rstStruct.$(Param.Name) = rdoParam["$(Param.Name)"].AsString();
#else
#ifeq($(Param.DataType.Name),rise::CString)
  rstStruct.$(Param.Name) = rdoParam["$(Param.Name)"].AsString();
#else
  rstStruct.$(Param.Name) = rdoParam["$(Param.Name)"];
#ifeqend
#ifeqend
#ifeqend
#ifeqend
#ifeqend
#end
  return rdoParam;
}

#end

///////////////////////////////////////////////////////////////////////////////////////////////////////
// typedef serializators
#foreach $(Interface.Typedefs)

// $(Typedef.Name)  Typedef.DataType.Type $(Typedef.DataType.Type) $(Typedef.DataType.Name)
#ifeq($(Typedef.DataType.IsTemplate),1) // для всех контейнеров должен быть сериализатор
CDataObject& operator<<(CDataObject& rdoParam, const $(Typedef.Name)& rtType)
{
  for($(Typedef.Name)::const_iterator it = rtType.begin(); it != rtType.end(); ++it)
  {
    CDataObject tdoItem("Item");
#ifeq($(Typedef.DataType.Name),std::map)
    CDataObject tdoItemKey("Key");
    CDataObject tdoItemValue("Value");
    tdoItemKey << it->first;
    tdoItemValue << it->second;
    tdoItem.AppendChild(tdoItemKey);
    tdoItem.AppendChild(tdoItemValue);
#else
    tdoItem << *it;
#ifeqend
    rdoParam.AppendChild(tdoItem);
  }
  return rdoParam;
}
#else // DataType.IsTemplate
#ifneq($(Typedef.DataType.Type),struct)     // !!struct!! structs already have serializator
CDataObject& operator<<(CDataObject& rdoParam, const $(Typedef.Name)& rtType)
{
#ifeq($(Typedef.DataType.Type),generic)    // !!generic!!
  rdoParam.Value() = rtType;
  return rdoParam;
#else
#ifeq($(Typedef.DataType.Type),dataobject) // !!dataobject!! 
  rdoParam.Add(rtType);
  return rdoParam;
#else
#ifeq($(Typedef.DataType.Type),typedef)    // !!typedef!!
  return rdoParam << rtType;
#else
#ifeq($(Typedef.DataType.Type),template)    // !!template!!
  return rdoParam << rtType;
#else
#cgerror "Typedef.DataType.Type = $(Typedef.DataType.Type);"
#ifeqend
#ifeqend
#ifeqend
#ifeqend
}
#ifeqend

#ifeqend // ifeq($(Typedef.DataType.IsTemplate),1)
#end // foreach $(Interface.Typedefs)

///////////////////////////////////////////////////////////////////////////////////////////////////////
// typedef deserializators
#foreach $(Interface.Typedefs)
#ifeq($(Typedef.DataType.Type),struct)     // !!struct!! structs already have deserializator // !!list<struct>!!
#ifeq($(Typedef.DataType.IsTemplate),1)
CDataObject& operator>>(CDataObject& rdoParam, $(Typedef.Name)& rtType)
{
  $(Typedef.DataType.Name) tItem;

  for(CDataObject::Iterator it = rdoParam.Begin(); it != rdoParam.End(); ++it)
  {
    CDataObject tdoItem(*it);
    tdoItem >> tItem;
    rtType.push_back(tItem);
  }
  return rdoParam;
}
#ifeqend
#else                 // !!not_a_struct!!
CDataObject& operator>>(CDataObject& rdoParam, $(Typedef.Name)& rtType)
{
#ifeq($(Typedef.DataType.IsTemplate),1)
// container :: $(Typedef.DataType.Name)
#ifeq($(Typedef.DataType.Type),typedef)
  $(Typedef.DataType.Name) tItem;
#else
#ifeq($(Typedef.DataType.Type),template)
#ifeq($(Typedef.DataType.Name),std::map)
  $(Typedef.DataType.TemplateParams.TemplateParam1) tKey;
  $(Typedef.DataType.TemplateParams.TemplateParam2) tValue;
#else
  $(Typedef.DataType.TemplateParams.TemplateParam1) tItem;
#ifeqend
#ifeqend
#ifeqend
  for(CDataObject::Iterator it = rdoParam.Begin(); it != rdoParam.End(); ++it)
  {
#ifeq($(Typedef.DataType.Type),generic)
    rtType.push_back(it->Value());
#else
#ifeq($(Typedef.DataType.Type),dataobject)
    rtType.push_back(*(it->Begin()));
#else
#ifeq($(Typedef.DataType.Type),typedef)
    CDataObject tdoItem(*it);
    tdoItem >> tItem;
    rtType.push_back(tItem);
#else
#ifeq($(Typedef.DataType.Type),template)
#ifeq($(Typedef.DataType.Name),std::map)
#ifeq($(Typedef.DataType.TemplateParams.TemplateParam1.Type),generic)    // !!generic!!
    tKey = (*it)["Key"];
#else
    (*it)("Key") >> tKey;
#ifeqend
#ifeq($(Typedef.DataType.TemplateParams.TemplateParam2.Type),generic)    // !!generic!!
    tValue = (*it)["Value"];
#else
    (*it)("Value") >> tValue;
#ifeqend
    rtType[ tKey ] = tValue;
#else
#ifeq($(Typedef.DataType.TemplateParams.TemplateParam1.Type),generic)    // !!generic!! //6
    tItem = (*it)["Item"];
#else
    CDataObject tdoItem(*it);
    tdoItem >> tItem;
#ifeqend
    rtType.push_back(tItem);
#ifeqend
#else
#cgerror "Typedef.DataType.Type = $(Typedef.DataType.Type);"
#ifeqend
#ifeqend
#ifeqend
#ifeqend
  }
  return rdoParam;
#else // !!DataType.IsTemplate!!
// not container :: $(Typedef.DataType.Name)
#ifeq($(Typedef.DataType.Type),generic)    // !!generic!!
  rtType = rdoParam.Value();
  return rdoParam;
#else
#ifeq($(Typedef.DataType.Type),dataobject) // !!dataobject!! 
  rtType = *rdoParam.Begin();
  return rdoParam;
#else
#ifeq($(Typedef.DataType.Type),typedef)    // !!typedef!!
  return rdoParam << rtType;
#else
#ifeq($(Typedef.DataType.Type),template)    // !!template!!
  return rdoParam << rtType;
#else
#cgerror "Typedef.DataType.Type = $(Typedef.DataType.Type);"
#ifeqend
#ifeqend
#ifeqend
#ifeqend
#ifeqend
}

#ifeqend
#end
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
// classes implementation

#foreach $(Interface.Classes)
$(Class.OpeningNs)
$(Class.Name)Proxy::$(Class.Name)Proxy()
{
}

void $(Class.Name)Proxy::Init( const rise::CString& sSessionId, const rise::CString& sServiceName, const rise::CString& sHostName, const rise::CString& sHostPort )
{
  m_tClient.Init(sServiceName, sHostName, sHostPort);
  m_tClient.SetSessionId(sSessionId);
}
#foreach $(Class.Members)

$(Member.Return) $(Class.Name)Proxy::$(Member.Name)($(Member.Params))$(Member.Const)
{
  staff::COperation tOperation("$(Member.Name)", "$(Member.Return.NodeName)");
#foreach $(Member.Params)
  staff::CDataObject tdoParam$(Param.Name) = tOperation.Request().CreateChild("$(Param.Name)");
#ifeq($(Param.DataType.Type),generic)    // !!generic!!
  tdoParam$(Param.Name).SetValue($(Param.Name));
#else
#ifeq($(Param.DataType.Type),dataobject) // !!dataobject!! 
  tdoParam$(Param.Name).AppendChild($(Param.Name));
#else
#ifeq($(Param.DataType.Type),struct)     // !!struct!! 
  tdoParam$(Param.Name) << $(Param.Name);
#else
#ifeq($(Param.DataType.Type),typedef)    // !!typedef!!
  tdoParam$(Param.Name) << $(Param.Name);
#else
#ifeq($(Param.DataType.Type),template)    // !!template!!
  tdoParam$(Param.Name) << $(Param.Name);
#else
#cgerror "Param.DataType.Type = $(Param.DataType.Type);"
#ifeqend
#ifeqend
#ifeqend
#ifeqend
#ifeqend
#end

  m_tClient.Invoke(tOperation);
  RISE_ASSERTES(!tOperation.IsFault(), staff::CRemoteException, tOperation.GetFaultString());

#ifeq($(Member.Return.Type),generic)    // !!generic!!
#ifneq($(Member.Return.Name),void)      // !!void!!
  return const_cast<const staff::COperation&>(tOperation).ResultValue();
#else
\
#ifeqend
#else
#ifeq($(Member.Return.Type),dataobject) // !!dataobject!! 
  return tOperation.Result();
#else
#ifeq($(Member.Return.Type),struct)     // !!struct!! 
  $(Member.Return.Name) stReturn;
  tOperation.Result() >> stReturn;
  return stReturn;
#else
#ifeq($(Member.Return.Type),typedef)    // !!typedef!!
  $(Member.Return.Name) tReturn;
  tOperation.Result() >> tReturn;
  return tReturn;
#else
#ifeq($(Member.Return.Type),template)    // !!template!!
  $(Member.Return) tReturn;
  tOperation.Result() >> tReturn;
  return tReturn;
#else
#cgerror "Member.Return.Type = $(Member.Return.Type);"
#ifeqend
#ifeqend
#ifeqend
#ifeqend
#ifeqend
}
#end
$(Class.EndingNs)
#end
