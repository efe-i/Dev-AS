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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#define TAG_SPACING 3
#define LEN 10240

#include <gnuradio/io_signature.h>
#include "energy_detector_cc_impl.h"
#include <volk/volk.h>

namespace gr {
  namespace ApolloShield {

    energy_detector_cc::sptr
    energy_detector_cc::make(int size, float threshold, const std::string& tag_key)
    {
      return gnuradio::get_initial_sptr
        (new energy_detector_cc_impl(size, threshold, tag_key));
    }

    /*
     * The private constructor
     */
    energy_detector_cc_impl::energy_detector_cc_impl(int size, float threshold, const std::string& tag_key)
      : gr::sync_block("energy_detector_cc",
    		  io_signature::make(1, 1, sizeof(gr_complex)),
			  io_signature::make(1, 1, sizeof(gr_complex))),
		      d_size(size),
		      d_threshold(threshold)
    {
    		std::vector<float> taps;
    		for(int i =0; i< d_size; i++)
    		{
    			taps.push_back(1);
    		}

    		d_fir = new gr::filter::kernel::fir_filter_fff(1, taps);
    		set_history(d_size);

    		d_tag_key = pmt::string_to_symbol(tag_key);
    		ip = new float[LEN];
    		op = new float[LEN];

	        //const int alignment_multiple = volk_get_alignment() / sizeof(float);
	        //set_alignment(std::max(1, alignment_multiple));
    }

    /*
     * Our virtual destructor.
     */
    energy_detector_cc_impl::~energy_detector_cc_impl()
    {
    	delete d_fir;
   	    delete [] ip;
   	    delete [] op;
    }

    int
    energy_detector_cc_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
    	gr::thread::scoped_lock l(d_setlock);

    	const gr_complex *in = (const gr_complex *)input_items[0];
    	gr_complex *out = (gr_complex *)output_items[0];
    	int cnt = -1;

        // Do <+signal processing+>
    	noutput_items = std::min(noutput_items-d_size, LEN-d_size);

    	volk_32fc_magnitude_squared_32f(ip, in, noutput_items);

        //Moving Average Filter

    	d_fir->filterN(op, ip, noutput_items);
    	double np[LEN];

    	for(int i = 0; i < noutput_items; i++)
    	{
    		np[i] = op[i]/(float)d_size;
    		out[i] = in[i];

    	    //Determine Threshold point and Tag output
    		if((np[i] > d_threshold) && (i > cnt))
    		{
    			tag_t tag;
    			tag.offset = nitems_written(0) + i;
    			tag.key = d_tag_key;
    			tag.value = pmt::from_double(np[i]);

    			add_item_tag(0, tag);
    			cnt = i + TAG_SPACING;
    		}
    	}

         return noutput_items;
    }

  } /* namespace ApolloShield */
} /* namespace gr */

