#ifndef RAFT_ROLE_CANDIDATE_H
#define RAFT_ROLE_CANDIDATE_H

#include "Role.h"


namespace Raft {
  class Candidate: public Role {
  private:
    boost::thread voteThread;
  public:
    Candidate(std::shared_ptr<RaftServerInfo> _info, 
      std::shared_ptr<RaftServerCluster>_cluster, 
      std::shared_ptr<Rpc::RaftRpcClient> _rpcClient,
      std::shared_ptr<Transformer> _transformer,
      std::fstream &_logScanner);
    void init(Term currentTerm) override;
    bool put(const std::string &key, const std::string &args) override;
    std::pair<bool, std::string> get(const std::string &key) override;
    RequestVoteReply respondRequestVote(const RequestVoteRequest &request) override;
    AppendEntriesReply respondHeartbeat(const AppendEntriesRequest &request) override;
    AppendEntriesReply respondAppendEntries(const Raft::Rpc::RpcAppendEntriesRequest *request) override;
  };
}
#endif
