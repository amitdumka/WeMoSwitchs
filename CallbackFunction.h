#ifndef CALLBACKFUNCTION_H
#define CALLBACKFUNCTION_H
 
#include <Arduino.h>


typedef bool (*CallbackFunction) ();


//typedef std::function<bool()> CallbackFunction;
//class CallbackInterface
//{
//public:
//    // The prefix "cbi" is to prevent naming clashes.
//    virtual int cbiCallbackFunction(int) = 0;
//};


////Bounce Method 
//template<class T, class Method, Method m, class ...Params>
//static auto bounce(void *priv, Params... params) ->
//    decltype(((*reinterpret_cast<T *>(priv)).*m)(params...))
//{
//  return ((*reinterpret_cast<T *>(priv)).*m)(params...);
//}
//
///**
//* Convenience macro to simplify bounce statement usage
//*/
//#define BOUNCE(c,m) bounce<c, decltype(&c::m), &c::m>

#endif
