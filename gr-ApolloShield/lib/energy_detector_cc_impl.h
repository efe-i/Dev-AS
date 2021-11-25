/* -*- c++ -*- */
/* 
 * Copyright 2021 ApolloShield.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_APOLLOSHIELD_ENERGY_DETECTOR_CC_IMPL_H
#define INCLUDED_APOLLOSHIELD_ENERGY_DETECTOR_CC_IMPL_H

#include <ApolloShield/energy_detector_cc.h>
#include <gnuradio/filter/fir_filter.h>

namespace gr {
  namespace ApolloShield {

    class energy_detector_cc_impl : public energy_detector_cc
    {
     private:
      int d_size;
      float d_threshold;
      pmt::pmt_t d_tag_key;
      gr::filter::kernel::fir_filter_fff *d_fir;
      float *ip;
      float *op;

     public:
      energy_detector_cc_impl(int size, float threshold, const std::string& tag_key);
      ~energy_detector_cc_impl();

      // Where all the action really happens
      int work(int noutput_items,
         gr_vector_const_void_star &input_items,
         gr_vector_void_star &output_items);
    };

  } // namespace ApolloShield
} // namespace gr

#endif /* INCLUDED_APOLLOSHIELD_ENERGY_DETECTOR_CC_IMPL_H */

