/*

    TSIframework . Framework for Taller de Sistemes Interactius I
    Universitat Pompeu Fabra

    Copyright (c) 2009 Carles F. Julià <carles.fernandez@upf.edu>

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use,
    copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following
    conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.

*/
#ifndef TUIOAPP_H_INCLUDED
#define TUIOAPP_H_INCLUDED

#define TRegistraCallback(T,TE) Base::getEP()[Singleton<TE>::Instance().name] = new Callback<T>(this,&T::EP_##TE )
#define TEventHandler(en) void EP_##en (TEvent * evt)


#include "EventQueue.h"
#include "tuioinput.h"
#include "InputGesture.h"

namespace tuio
{

class GenericCallback
{
public:
    virtual void run(TEvent * )=0;
};


//from http://stackoverflow.com/questions/1284014/callback-in-c-template-member#answer-1284047
template<typename C>
class Callback : public GenericCallback
{
      public:
  // constructs a callback to a method in the context of a given object
  Callback(C* object, void (C::*method)(TEvent *))
    : o(object),m(method) {}
  // calls the method
  void run(TEvent * te) {
    (o ->* m) (te);
  }
  private:
  // container for the pointer to method
    C* o;
    void (C::*m)(TEvent *);
};


class VoidClass{};

typedef std::vector<GenericCallback * > eventprocessorsType;

template< class Base = VoidClass>
class tuioApp : public Base
{
private:
    eventprocessorsType eventprocessors;
public:

    tuioApp()
    {
        ///TODO: better sizing
        eventprocessors.resize(100,NULL);
    }

    void processTevent(TEvent * te)
    {
        if (eventprocessors[te->name])
            eventprocessors[te->name]->run(te);
    }

    eventprocessorsType & getEP()
    {
        return eventprocessors;
    }
};

class InputGesture;

void registerMeToInputGestureManager(InputGesture * IG);

}
#endif // TUIOAPP_H_INCLUDED
