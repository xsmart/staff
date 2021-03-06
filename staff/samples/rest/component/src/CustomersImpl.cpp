// This file generated by staff_codegen
// For more information please visit: http://code.google.com/p/staff/
// Service Implementation

#include <staff/common/Exception.h>
#include "CustomersImpl.h"

namespace samples
{
namespace rest
{

CustomersImpl::CustomersImpl():
  m_nLastId(0)
{
}

CustomersImpl::~CustomersImpl()
{
}

int CustomersImpl::Add(const Customer& rstCustomer)
{
  CustomersList::iterator itResult =
          m_lsCustomers.insert(m_lsCustomers.end(), rstCustomer);

  return *itResult->nId = ++m_nLastId;
}

void CustomersImpl::Delete(int nId)
{
  for (CustomersList::iterator itCustomer = m_lsCustomers.begin();
      itCustomer != m_lsCustomers.end(); ++itCustomer)
  {
    if (*itCustomer->nId == nId)
    {
      m_lsCustomers.erase(itCustomer);
      return;
    }
  }

  STAFF_THROW(staff::RemoteException, "Customer with given id does not exists");
}

void CustomersImpl::Update(const Customer& rstCustomer)
{
  STAFF_ASSERT(!rstCustomer.nId.IsNull(), "Customer ID is not set");
  int nId = *rstCustomer.nId;

  for (CustomersList::iterator itCustomer = m_lsCustomers.begin();
      itCustomer != m_lsCustomers.end(); ++itCustomer)
  {
    if (*itCustomer->nId == nId)
    {
      itCustomer->sFirstName = rstCustomer.sFirstName;
      itCustomer->sLastName = rstCustomer.sLastName;
      itCustomer->nYear = rstCustomer.nYear;
      return;
    }
  }

  STAFF_THROW(staff::RemoteException, "Customer with given id does not exists");
}

CustomersList CustomersImpl::List()
{
  return m_lsCustomers;
}

Customer CustomersImpl::Get(int nId)
{
  for (CustomersList::iterator itCustomer = m_lsCustomers.begin();
      itCustomer != m_lsCustomers.end(); ++itCustomer)
  {
    if (*itCustomer->nId == nId)
    {
      return *itCustomer;
    }
  }

  STAFF_THROW(staff::RemoteException, "Customer with given id does not exists");
}


}
}

