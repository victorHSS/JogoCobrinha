#ifndef _OBJECT_H_
#define _OBJECT_H_

class Object{
public:
   Object(){}
   ~Object(){}
   virtual void release() = 0;
};

#endif
