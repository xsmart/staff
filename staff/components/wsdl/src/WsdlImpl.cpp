// This file generated by staff_codegen
// For more information please visit: http://code.google.com/p/staff/
// Service Implementation

#include <fstream>
#include <strstream>
#include <rise/common/Log.h>
#include <rise/common/ExceptionTemplate.h>
#include <staff/common/Runtime.h>
#include <staff/common/Operation.h>
#include <staff/common/Attribute.h>
#include <staff/common/MessageContext.h>
#include "WsdlImpl.h"

namespace staff
{
namespace wsdl
{

void WsdlImpl::Get(const std::string& sComponent, const std::string& sFile, COperation& rOperation)
{
  const std::string& sHost = rOperation.GetMessageContext().GetPropertyValue("HttpHost");

  // check filename
  RISE_ASSERTS(sFile.find_first_of("/\\") == std::string::npos, "Invalid filename");
  RISE_ASSERTS(sComponent.find_first_of("/\\") == std::string::npos, "Invalid component");

  // path to file
  const std::string& sFilePath = staff::CRuntime::Inst().GetComponentHome(sComponent) +
                                     RISE_PATH_SEPARATOR + sFile;

  std::ifstream ifsWsdlFile(sFilePath.c_str());
  RISE_ASSERTS(ifsWsdlFile.good(), "Can't open [" + sFilePath + "]");

  staff::CDataObject tdoWsdl;

  std::stringstream ssWsdl;
  ssWsdl << ifsWsdlFile.rdbuf();
  tdoWsdl.FromString(ssWsdl.str());

  // finding service url..
  staff::CDataObject::Iterator itService = tdoWsdl.FindChildByLocalName("service");
  if (itService != tdoWsdl.End())
  {
    staff::CDataObject tdoService = *itService;
    for (staff::CDataObject::Iterator itPort = tdoService.Begin(); itPort != tdoService.End(); ++itPort)
    {
      if (itPort->GetLocalName() == "port")
      {
        staff::CDataObject tdoPort = *itPort;
        staff::CDataObject::Iterator itAddress = tdoPort.FindChildByLocalName("address");
        if (itAddress != tdoPort.End())
        {
          staff::CDataObject tdoAddress = *itAddress;
          staff::CDataObject::AttributeIterator itAttrLocation =
              tdoAddress.FindAttributeByLocalName("location");
          if (itAttrLocation != tdoAddress.AttributeEnd())
          {
            // modyfying location
            std::string sLocation = itAttrLocation->GetText();

            std::string::size_type nPosBegin = sLocation.find("://");
            if (nPosBegin != std::string::npos)
            {
              nPosBegin += 3;

              std::string::size_type nPosEnd = sLocation.find('/', nPosBegin);
              if (nPosEnd != std::string::npos)
              {
                sLocation.replace(nPosBegin, nPosEnd - nPosBegin, sHost);
                itAttrLocation->SetText(sLocation);
              }
              else
              {
                rise::LogWarning() << "Can't find host end in wsdl";
              }
            }
            else
            {
              rise::LogWarning() << "Can't find protocol specification in wsdl";
            }

          }
        }
      }
    }
  }

  rOperation.SetResponse(tdoWsdl);
}


}
}

