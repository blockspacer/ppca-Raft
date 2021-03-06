#ifndef RAFT_RPC_RAFTRPCCLIENT_H
#define RAFT_RPC_RAFTRPCCLIENT_H

#include <grpc++/grpc++.h>
#include "RaftRpc.grpc.pb.h"
#include "RaftRpc.pb.h"
#include "defines.h"

namespace Raft {
  namespace Rpc {
    class RaftRpcClient {
    private:
      std::ofstream fout1, fout2, fout3;
      size_t size, localServer;
      const Timer broadcastTimeout;
      std::vector<boost::future<std::pair<bool, RequestVoteReply> > > voteFuture;
      std::vector<boost::future<std::pair<bool, AppendEntriesReply> > > heartbeatFuture;
      std::vector<std::unique_ptr<RaftRpc::Stub> > stubs;
    public:
      RaftRpcClient(std::vector<std::shared_ptr<grpc::Channel> > channels, Timer timeout, const size_t &_localServer, const Address &address);
      std::pair<bool, RequestVoteReply> sendRequestVote(size_t id, const RequestVoteRequest &request);
      std::pair<bool, AppendEntriesReply> sendHeartbeat(size_t id, const AppendEntriesRequest &request);
      std::pair<bool, AppendEntriesReply> sendAppendEntries(size_t id, RpcAppendEntriesRequest rpcRequest);
      std::pair<RaftServerRole, Term> sendRequestVotes(const RequestVoteRequest &request);
      std::pair<RaftServerRole, Term> sendHeartbeats(const AppendEntriesRequest &request);
    };
  }
}

#endif