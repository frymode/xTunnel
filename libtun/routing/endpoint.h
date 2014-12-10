#pragma once

#include "endpoint_state.h"
#include "routing/rules/endpoint_rule.h"
#include "data_buffer.h"

namespace xTunnel
{
    class Endpoint
    {
    public:
        typedef AsyncResult<DataBuffer> ReceiveResult;
        typedef function<void(ReceiveResult& res)> ReceiveHandler;

		Endpoint(const EndpointRulePtr& rule, const EndpointState& state = kClosed);
        virtual ~Endpoint() = 0;

		const EndpointRulePtr& rule() const { return _rule; }
        EndpointState state() const { return _state; }
        bool IsActive() const { return _state == kActive; }

        virtual void BeginReceive(const ReceiveHandler& handler) = 0;
        virtual void Send(const char* buf, int size) = 0;
        virtual void Close();

        inline uint64_t total_sent() const { return _sent_bytes.exchange(0); }
        inline uint64_t total_received() const { return _received_bytes.exchange(0); }

    protected:
        inline void AddSent(int bytes)
        {
            _sent_bytes += bytes;
        }

        inline void AddReceived(int bytes)
        {
            _received_bytes += bytes;
        }

		void SetState(const EndpointState& state);
        Mutex _mutex;
	private:
		EndpointRulePtr _rule;

		volatile EndpointState _state;
        mutable atomic<uint64_t> _sent_bytes;
        mutable atomic<uint64_t> _received_bytes;
    };
    
    typedef shared_ptr<Endpoint> EndpointPtr;
}