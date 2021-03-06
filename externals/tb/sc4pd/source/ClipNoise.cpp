/* sc4pd 
   ClipNoise, ClipNoise~

   Copyright (c) 2004 Tim Blechmann.

   This code is derived from:
	SuperCollider real time audio synthesis system
    Copyright (c) 2002 James McCartney. All rights reserved.
	http://www.audiosynth.com


   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

   Based on:
     PureData by Miller Puckette and others.
         http://www.crca.ucsd.edu/~msp/software.html
     FLEXT by Thomas Grill
         http://www.parasitaere-kapazitaeten.net/ext
     SuperCollider by James McCartney
         http://www.audiosynth.com
     
   Coded while listening to: Henry Threadgill: Everybodys Mouth's A Book
   
*/

#include "sc4pd.hpp"


/* ------------------------ ClipNoise~ -------------------------------*/

class ClipNoise_ar:
    public sc4pd_dsp
{
    FLEXT_HEADER(ClipNoise_ar,sc4pd_dsp);
    
public:
    ClipNoise_ar(int argc, t_atom *argv);
    
protected:
    virtual void m_signal(int n, t_sample *const *in, t_sample *const *out);

    void m_seed(int i)
    {
	rgen.init(i);
    }
    
private:
    RGen rgen;
    FLEXT_CALLBACK_I(m_seed);
};

FLEXT_LIB_DSP_V("ClipNoise~",ClipNoise_ar);

ClipNoise_ar::ClipNoise_ar(int argc, t_atom *argv)
{
    FLEXT_ADDMETHOD_(0,"seed",m_seed);

    //parse arguments
    AtomList Args(argc,argv);

    rgen.init(timeseed());

    AddOutSignal();
}    


void ClipNoise_ar::m_signal(int n, t_sample *const *in, 
			       t_sample *const *out)
{
    t_sample *nout = *out;

    RGET;

    for (int i = 0; i!= n;++i)
    {
	(*(nout)++) = fcoin(s1, s2, s3);
    }
    
    RPUT;
}


/* ------------------------ ClipNoise ---------------------------------*/

class ClipNoise_kr:
    public flext_base
{
    FLEXT_HEADER(ClipNoise_kr,flext_base);

public:
    ClipNoise_kr(int argc, t_atom *argv);
    
protected:
    void m_perform();

    void m_seed(int i)
    {
	rgen.init(i);
    }
    
private:
    RGen rgen;
    FLEXT_CALLBACK(m_perform);
    FLEXT_CALLBACK_I(m_seed);
};

FLEXT_LIB_V("ClipNoise",ClipNoise_kr);

ClipNoise_kr::ClipNoise_kr(int argc, t_atom *argv)
{
    FLEXT_ADDBANG(0,m_perform);
    FLEXT_ADDMETHOD_(0,"seed",m_seed);
    //parse arguments
    AtomList Args(argc,argv);
    
    rgen.init(timeseed());

    AddOutInt();
}

void ClipNoise_kr::m_perform()
{
    ToOutInt(0,rgen.fcoin());
}
