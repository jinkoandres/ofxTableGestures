#include "tuio1.1/InputGestureTuio1.13D.h"
#include <cstring>

using namespace osc;

namespace tuio
{

void InputGestureTuio113D::ReceiveCall(const char * addr, ReceivedMessageArgumentStream & args)
{
    if(!valid)
        return;
    if( strcmp( addr, "/tuio/3Dcur" ) == 0 )
        tuio3Dcur(args);
    if( strcmp( addr, "/tuio/3Dobj" ) == 0 )
        tuio3Dobj(args);
}

void InputGestureTuio113D::tuio3Dcur(ReceivedMessageArgumentStream & args)
{
    const char* cmd;
    args >> cmd;

    if(strcmp(cmd,"set")== 0)
    {
        int32 s_id;
        float xpos, ypos, zpos, xspeed, yspeed, zspeed, maccel;

        args >> s_id >> xpos >> ypos >> zpos >> xspeed >> yspeed >> zspeed >> maccel >> EndMessage;

        if(c_s_ids.find(s_id) == c_s_ids.end())
        {

            TeventTuio11NewFinger3D * e = new TeventTuio11NewFinger3D();
            e->s_id = s_id;
            e->xpos = xpos;
            e->ypos = ypos;
            e->zpos = zpos;
            e->xspeed = xspeed;
            e->yspeed = yspeed;
            e->zspeed = zspeed;
            e->maccel = maccel;
            events.push_back(e);
            c_s_ids.insert(s_id);
        }
        else
        {

            TeventTuio11MoveFinger3D * e = new TeventTuio11MoveFinger3D();
            e->s_id = s_id;
            e->xpos = xpos;
            e->ypos = ypos;
            e->zpos = zpos;
            e->xspeed = xspeed;
            e->yspeed = yspeed;
            e->zspeed = zspeed;
            e->maccel = maccel;
            events.push_back(e);
        }

    }
    else if( strcmp( cmd, "alive" ) == 0 )
    {
        int32 s_id;
        std::set<int32> t(c_s_ids);
        while(!args.Eos())
        {
            args >> s_id;
            t.erase(s_id);
        }
        args >> EndMessage;
        for (std::set<int32>::iterator it = t.begin(); it != t.end(); ++it)
        {
            s_id = *it;
            c_s_ids.erase(s_id);
            TeventTuio11RemoveFinger3D * e = new TeventTuio11RemoveFinger3D();
            e->s_id = s_id;
            events.push_back(e);
        }
    }

}

void InputGestureTuio113D::tuio3Dobj(ReceivedMessageArgumentStream & args)
{
        const char* cmd;
        args >> cmd;

        if(strcmp(cmd,"set")== 0)
        {

            int32 s_id, f_id;
            float xpos, ypos, zpos, aangle, bangle, cangle , xspeed, yspeed, zspeed, aspeed,bspeed,cspeed, maccel, raccel;

            args >> s_id >> f_id >> xpos >> ypos >> zpos >> aangle >> bangle >> cangle >> xspeed >> yspeed >> zspeed >>  aspeed >> bspeed >>cspeed >> maccel >> raccel >> EndMessage;

            if(o_s_ids.find(s_id) == o_s_ids.end())
            {

                TeventTuio11NewObject3D * e = new TeventTuio11NewObject3D();
                e->s_id = s_id;
                e->f_id = f_id;
                e->xpos = xpos;
                e->ypos = ypos;
                e->zpos = zpos;
                e->aangle = aangle;
                e->bangle = bangle;
                e->cangle = cangle;
                e->xspeed = xspeed;
                e->yspeed = yspeed;
                e->zspeed = zspeed;
                e->aspeed = aspeed;
                e->bspeed = bspeed;
                e->cspeed = cspeed;
                e->maccel = maccel;
                e->raccel = raccel;
                events.push_back(e);
                o_s_ids.insert(s_id);
            }
            else
            {

                TeventTuio11MoveObject3D * e = new TeventTuio11MoveObject3D();
                e->s_id = s_id;
                e->f_id = f_id;
                e->xpos = xpos;
                e->ypos = ypos;
                e->zpos = zpos;
                e->aangle = aangle;
                e->bangle = bangle;
                e->cangle = cangle;
                e->xspeed = xspeed;
                e->yspeed = yspeed;
                e->zspeed = zspeed;
                e->aspeed = aspeed;
                e->bspeed = bspeed;
                e->cspeed = cspeed;
                e->maccel = maccel;
                e->raccel = raccel;
                events.push_back(e);
            }

        }
        else if( strcmp( cmd, "alive" ) == 0 )
        {

            int32 s_id;
            std::set<int32> t(o_s_ids);
            while(!args.Eos())
            {
                args >> s_id;
                t.erase(s_id);
            }
            args >> EndMessage;
            for (std::set<int32>::iterator it = t.begin(); it != t.end(); ++it)
            {
                s_id = *it;
                o_s_ids.erase(s_id);
                TeventTuio11RemoveObject3D * e = new TeventTuio11RemoveObject3D();
                e->s_id = s_id;
                events.push_back(e);
            }
        }
}


}
