#ifndef __DANET_NETBASE_H
#define __DANET_NETBASE_H

#include <vector>

namespace danet
{
  class netbase;
  typedef unsigned char byte;
  class acceptor;
  class connection;
  typedef std::vector<byte> packet;
}

#include "address.h"
#include "protocol.h"

#include <boost/asio.hpp>

#include <condition_variable>
#include <map>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>


namespace danet
{
  class netbase
  {
  protected:
    typedef unsigned int handle;
    typedef unsigned int user;

    netbase(std::shared_ptr<protocol> pro);
    netbase(const netbase&) = delete;
    netbase(netbase &&nb) = delete;
    ~netbase();

  protected:
    handle listen_at(address *adr, const std::vector<byte>& pwd);
    handle connect_to(address *adr, const std::vector<byte>& pwd);
    void close_resource(handle h);
    void send_message(const std::vector<byte> &v, const std::vector<user> &s);
    void recv_message(std::vector<byte> &v, user &s);
    void send_to_resource(std::shared_ptr<packet> v, handle h);
    std::vector<user> get_users_list();

    boost::asio::io_service & get_service()
    {
      return this->service;
    }

    void io_worker();

  private:
protected:

    friend class connection;
    friend class acceptor;

    //void received(message msg);
    //void accepted(const boost::system::error_code & ec, std::shared_ptr<connection>);
    //void connected(const boost::system::error_code & ec, std::shared_ptr< connection > con);
    //void add_worker(int n);
    //void worker();
    //void add_message(message m);
    //void bconnect(std::string ip, int port);
    //void bconnect(std::string ip, int port, int hid);
    //void inform_ips(std::shared_ptr<connection> c);
    //void suggest_id(std::shared_ptr<connection> c);
    //void recv_ips(message m);

    //int myid = -1;
    //std::vector<std::shared_ptr<connection>> pairs;
    //std::mutex parm;
    //int pairs_count;
    //std::queue<message> rcvq;
    //std::mutex rcvm;
    //std::vector<std::shared_ptr<connection>> unsorted;
    //int state = 0;
    //std::mutex unsm;
    boost::asio::io_service service;
    boost::asio::io_service::work work;
    std::vector<std::thread *> workers;
    std::map<int,std::shared_ptr<acceptor>> acceptors;
    int acceptors_oid = 0;
    std::map<int,std::shared_ptr<connection>> connections;
    int connections_oid = 0;

    std::shared_ptr<danet::protocol> proto;
  };
}

#endif	/* NETMAN_H */

