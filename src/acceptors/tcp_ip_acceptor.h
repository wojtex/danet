/*
 * Danet (Distributed Asynchronous Network)
 * This file is a part of danet library.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * For a list of authors see AUTHORS file.
 */

#ifndef __DANET_TCP_IP_ACCEPTOR_H
#define	__DANET_TCP_IP_ACCEPTOR_H

#include "netbase.h"
#include "address_ip_tcp.h"
#include "acceptor.h"

#include <memory>
#include <string>

namespace danet
{
  namespace ip
  {
    namespace tcp
    {
      /**
       * Represents TCP/IP acceptor
       */
      class acceptor : public danet::acceptor
      {
        friend class danet::ip::tcp::address;
      public:
        virtual ~acceptor();
      protected:
        /**
         * Creates acceptor based od an address.
         * @param adr The address
         */
        acceptor(const danet::ip::tcp::address &adr);

        virtual bool run(netbase *nb);
        virtual std::shared_ptr<danet::address> get_address();

        /**
         * Makes the acceptor starts accepting connections.
         */
        void accept();

        /**
         * Invoked when a connection has been accepted.
         * @param ec Error code
         * @param con Pointer to the connection
         */
        void on_accept(const boost::system::error_code & ec, std::shared_ptr<danet::ip::tcp::connection> con);

        /**
         * The address associated to acceptor.
         */
        danet::ip::tcp::address adr;

        /**
         * Pointer to Boost Asio Acceptor object.
         */
        boost::asio::ip::tcp::acceptor *acc = nullptr;
      };
    }
  }
}

#endif

