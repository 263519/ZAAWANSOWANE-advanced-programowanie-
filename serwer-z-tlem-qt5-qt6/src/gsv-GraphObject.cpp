#include "gsv-GraphObject.hh"
#include <iostream>


using namespace std;




void gsv::GraphObject::PrintObj() const
{
  cout << " Name: " << GetName() << " " << GetParams() << endl;
}
