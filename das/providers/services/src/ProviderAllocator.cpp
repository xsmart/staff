/*
 *  Copyright 2012 Utkin Dmitry
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

#include <staff/utils/PluginExport.h>
#include <staff/utils/SharedPtr.h>
#include "Services.h"

namespace staff
{
namespace das
{
  class ProviderAllocatorImpl: public IProviderAllocator
  {
  public:
    virtual PProvider Allocate(const std::string& sName)
    {
      if (sName == "staff.das.Services")
      {
        return PProvider(new ::staff::das::ServicesProvider);
      }
      else
      {
        STAFF_THROW_ASSERT("Can't instantiate provider: " + sName +
                    "\nAvailable providers are:\n"
                    "  staff.das.Services\n"
                    );
      }
    }

    virtual void GetProvidersList(StringList& rlsProvidersList)
    {
      rlsProvidersList.clear();
      rlsProvidersList.push_back("staff.das.Services");
    }
  };
}
}

STAFF_DECLARE_PLUGIN(::staff::das::ProviderAllocatorImpl)

