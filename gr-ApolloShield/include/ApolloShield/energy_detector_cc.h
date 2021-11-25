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


#ifndef INCLUDED_APOLLOSHIELD_ENERGY_DETECTOR_CC_H
#define INCLUDED_APOLLOSHIELD_ENERGY_DETECTOR_CC_H

#include <ApolloShield/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace ApolloShield {

    /*!
     * \brief <+description of block+>
     * \ingroup ApolloShield
     *
     */
    class APOLLOSHIELD_API energy_detector_cc : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<energy_detector_cc> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of ApolloShield::energy_detector_cc.
       *
       * To avoid accidental use of raw pointers, ApolloShield::energy_detector_cc's
       * constructor is in a private implementation
       * class. ApolloShield::energy_detector_cc::make is the public interface for
       * creating new instances.
       */
      static sptr make(int size, float threshold, const std::string& tag_key);
    };

  } // namespace ApolloShield
} // namespace gr

#endif /* INCLUDED_APOLLOSHIELD_ENERGY_DETECTOR_CC_H */

