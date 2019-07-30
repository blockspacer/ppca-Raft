#ifndef RAFT_RAFTSERVER_H
#define RAFT_RAFTSERVER_H

#include <cstdio>
#include <iostream>
#include <functional>
#include <boost/thread/thread.hpp>
#include <boost/thread/lock_factories.hpp>
#include <boost/thread/future.hpp>
#include "defines.h"
#include "Task.h"
#include "Role.h"
#include "Follower.h"
#include "Candidate.h"
#include "Leader.h"
#include "RaftRpc.pb.h"
#include "RaftRpc.grpc.pb.h"
#include "RaftRpcServer.h"
#include "RaftRpcClient.h"

namespace Raft {
  class RaftServer {
  private:
    RaftServerRole currentRole;
    std::shared_ptr<RaftServerCluster> cluster;
    std::shared_ptr<RaftServerInfo> info;
    
    std::shared_ptr<Rpc::RaftRpcServer> rpcServer;
    std::shared_ptr<Rpc::RaftRpcClient> rpcClient;
    
    std::shared_ptr<Transformer> transformer;
    
    std::queue<TaskType> taskQueue;
    std::queue<PutTask> putQueue;
    std::queue<GetTask> getQueue;
    std::queue<RespondRequestVoteTask> respondRequestVoteQueue;
    std::queue<RespondAppendEntriesTask> respondAppendEntriesQueue;
    std::queue<TransformTask> transformQueue;
    boost::mutex queueMutex;
    boost::condition_variable queueCond;
    boost::thread queueThread;

    std::unique_ptr<Role> roles[4];

  public:
    RaftServer(const std::string &fileName);
    void start();
    void shutdown();    
    void executeTask();
    bool put(const std::string &key, const std::string &args);
    std::pair<bool, std::string> get(const std::string &key);
    RequestVoteReply respondRequestVote(const RequestVoteRequest &requset);
    AppendEntriesReply respondAppendEntries(const AppendEntriesRequest &request);
    void transform(RaftServerRole fromRole, RaftServerRole toRole, Term term);
  };
}
#endif
