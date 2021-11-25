/* -*- c++ -*- */

#define APOLLOSHIELD_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "ApolloShield_swig_doc.i"

%{
#include "ApolloShield/energy_detector_cc.h"
%}


%include "ApolloShield/energy_detector_cc.h"
GR_SWIG_BLOCK_MAGIC2(ApolloShield, energy_detector_cc);
