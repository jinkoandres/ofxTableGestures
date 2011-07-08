#include "InputGestureBasicFingers.hpp"
#include "GraphicDispatcher.hpp"

InputGestureBasicFingers::InputGestureBasicFingers()
{
    registerEvent( InputGestureTuio112D::Instance().removeTuioCursor2D , &InputGestureBasicFingers::removeTuioCursor2D );
    registerEvent( InputGestureTuio112D::Instance().updateTuioCursor2D , &InputGestureBasicFingers::updateTuioCursor2D );
    registerEvent( InputGestureTuio112D::Instance().addTuioCursor2D , &InputGestureBasicFingers::addTuioCursor2D );
}

void InputGestureBasicFingers::addTuioCursor2D(int id, float xpos,float ypos,float xspeed,float yspeed,float maccel)
{
        
        ids.insert(id);
        Graphic * target = GraphicDispatcher::Instance().Collide(ofPoint(xpos,ypos));
        graphic_assignations[id] = target;
        addTuioCursorArgs eventargs;
        eventargs.id = id;
        eventargs.xpos = xpos;
        eventargs.ypos = ypos;
        eventargs.xspeed = xspeed;
        eventargs.yspeed = yspeed;
        eventargs.maccel = maccel;
        eventargs.target = target;
        ofNotifyEvent(addTuioCursor,eventargs);

}

void InputGestureBasicFingers::updateTuioCursor2D(int id, float xpos,float ypos,float xspeed,float yspeed,float maccel)
{

    if(ids.find(id) == ids.end())
    {
        addTuioCursor2D(id,xpos,ypos,xspeed,yspeed,maccel);
        return;
    }
    
    Graphic * target = GraphicDispatcher::Instance().Collide(ofPoint(xpos,ypos));
    
    if(graphic_assignations[id] != target)
    {
        {
            exitTuioCursorArgs eventargs;
            eventargs.id = id;
            eventargs.target = graphic_assignations[id];
            ofNotifyEvent(exitTuioCursor,eventargs);
        }
        graphic_assignations[id] = target;
        {
            enterTuioCursorArgs eventargs;
            eventargs.id = id;
            eventargs.xpos = xpos;
            eventargs.ypos = ypos;
            eventargs.xspeed = xspeed;
            eventargs.yspeed = yspeed;
            eventargs.maccel = maccel;
            eventargs.target = target;
            ofNotifyEvent(enterTuioCursor,eventargs);
        }
    }
    else
    {
        updateTuioCursorArgs eventargs;
        eventargs.id = id;
        eventargs.xpos = xpos;
        eventargs.ypos = ypos;
        eventargs.xspeed = xspeed;
        eventargs.yspeed = yspeed;
        eventargs.maccel = maccel;
        eventargs.target = target;
        ofNotifyEvent(updateTuioCursor,eventargs);
    }

    
}

void InputGestureBasicFingers::removeTuioCursor2D(int id)
{
    if(ids.find(id) != ids.end())
    {
        ids.erase(id);
        removeTuioCursorArgs eventargs;
        eventargs.id = id;
        eventargs.target = graphic_assignations[id];
        ofNotifyEvent(removeTuioCursor,eventargs);
        graphic_assignations.erase(id);

    }
}
