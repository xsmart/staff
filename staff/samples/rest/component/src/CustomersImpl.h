// This file generated by staff_codegen
// For more information please visit: http://code.google.com/p/staff/
// Service Implementation

#ifndef _CustomersImpl_h_
#define _CustomersImpl_h_

#include "Customers.h"

namespace samples
{
namespace rest
{

  //! implementation of REST demo: Customers service
  class CustomersImpl: public Customers
  {
  public:
    CustomersImpl();
    virtual ~CustomersImpl();
    virtual int Add(const Customer& rstCustomer);
    virtual void Delete(int nId);
    virtual void Update(const Customer& rstCustomer);
    virtual CustomersList List();
    virtual Customer Get(int nId);

  private:
    CustomersList m_lsCustomers;
    int m_nLastId;
  };
}
}


#endif // _CustomersImpl_h_
