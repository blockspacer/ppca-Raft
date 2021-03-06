#ifndef RAFT_ROLE_ROLE_H
#define RAFT_ROLE_ROLE_H

#include <cstdio>
#include <iostream>
#include "defines.h"
#include "Transformer.h"
#include "RaftRpcClient.h"
#include "RaftRpcServer.h"
#include "RaftRpc.pb.h"
#include "RaftRpc.grpc.pb.h"

namespace Raft {
  class Role {
  protected:
    std::fstream &logScanner;
    std::shared_ptr<RaftServerInfo> info;
    std::shared_ptr<RaftServerCluster> cluster;
    std::shared_ptr<Rpc::RaftRpcClient> rpcClient;
    std::shared_ptr<Transformer> transformer;
  public:
    std::ofstream fout;
    Role(std::shared_ptr<RaftServerInfo> _info, 
      std::shared_ptr<RaftServerCluster>_cluster, 
      std::shared_ptr<Rpc::RaftRpcClient> _rpcClient,
      std::shared_ptr<Transformer> _transformer,
      std::fstream &_logScanner);
    virtual void init(Term currentTerm) = 0;
    virtual bool put(const std::string &key, const std::string &args) = 0;
    virtual std::pair<bool, std::string> get(const std::string &key) = 0;
    virtual RequestVoteReply respondRequestVote(const RequestVoteRequest &request) = 0;
    virtual AppendEntriesReply respondHeartbeat(const AppendEntriesRequest &request) = 0;
    virtual AppendEntriesReply respondAppendEntries(const Raft::Rpc::RpcAppendEntriesRequest *request) = 0;
  };
} 

#endif
