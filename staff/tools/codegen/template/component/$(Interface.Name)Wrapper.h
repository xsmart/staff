// This file generated by staff_codegen
// For more information please visit: http://code.google.com/p/staff/
// DO NOT EDIT

#ifndef _$(Interface.Name)Wrapper_h_
#define _$(Interface.Name)Wrapper_h_

#include <string>
#include <staff/component/Service.h>

#foreach $(Interface.Classes)
$(Class.OpeningNs)
  class $(Class.Name)Impl;

  //! $(Class.ServiceName) service wrapper
  class $(Class.Name)Wrapper: public staff::CService
  {
  public:
    //!         default constructor
    $(Class.Name)Wrapper();

    //!         initializing constructor
    /*! \param  pComponent - service's component
    */
    $(Class.Name)Wrapper(staff::CComponent* pComponent);

    //!         destructor
    virtual ~$(Class.Name)Wrapper();

    //!         get service name
    /*! \return service name
    */
    const std::string& GetName() const;

    //!         get service description
    /*! \return service description
    */
    const std::string& GetDescr() const;
    
    //!         get service operations
    /*! \return service operations DataObject
    */
    virtual staff::CDataObject GetOperations() const;

    //!         get service description
    /*! \return service description
    */
    virtual staff::CDataObject GetServiceDescription() const;
    
    //!         invoke service operation
    /*! \param  rOperation - service operation
        \param  sID - service session id
        */
    void Invoke(staff::COperation& rOperation, const std::string& sID);

    //!         get service's component
    /*! \return service's component
    */
    const staff::CComponent* GetComponent() const;

    //!         get service's component
    /*! \return service's component
    */
    staff::CComponent* GetComponent();

    //!         get pointer to service implementation(only for local)
    /*! \param  sID - service session id
        \return pointer to service implementation
        */
    void* GetImpl(const std::string& sID);

    //!         get services ids
    /*! \return service ids
        */
    virtual rise::CStringList GetServiceIds() const;

  protected:
    //!         get service implementation
    /*! \param  sID - session id
        \return service implementation
    */
    $(Class.Name)Impl& ServiceImpl(const std::string& sID);
  
  private:
    class $(Class.Name)WrapperImpl;
    $(Class.Name)WrapperImpl* m_pImpl;
  };
$(Class.EndingNs)

#end
#endif // _$(Interface.Name)Wrapper_h_