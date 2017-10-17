#include <exception>
#include <iostream>
#include <assert.h>

using namespace std;

struct NoScene : public exception {
   const char * what () const throw () {
      return "No scene is currently loaded, please intialise the engine first";
   }
};