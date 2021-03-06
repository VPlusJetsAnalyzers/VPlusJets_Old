/* -*- mode: C++ -*- *********************************************************
 * Project: RooFit                                                           *
 *                                                                           *
 * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/

#ifndef ALPHAFUNCTION
#define ALPHAFUNCTION

#include "RooAbsReal.h"
#include "RooRealProxy.h"
#include "RooAbsReal.h"
 
class alphaFunction : public RooAbsReal {
public:
  alphaFunction() {} ; 
  alphaFunction(const char *name, const char *title,
	      RooAbsReal& _x,
	      RooAbsReal& _sideband,
	      RooAbsReal& _signal);
  alphaFunction(const alphaFunction& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new alphaFunction(*this,newname); }
  inline virtual ~alphaFunction() { }

protected:

  RooRealProxy x ;
  RooRealProxy sideband ;
  RooRealProxy signal ;
  
  Double_t evaluate() const ;

private:

  ClassDef(alphaFunction,1) // Your description goes here...
};
 
#endif
