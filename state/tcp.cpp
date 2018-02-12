class TCPOctetStream;


class TCPState;

class TCPConnection{
    public:
        TCPConnection();
        void ActiveOpen();
        void PassiveOpen();
        void Close();
        void Send();
        void Acknowledge();
        void Synchronize();
    private:
        friend class TCPState;
        void ChangeState(TCPState*);
    private:
        TCPState* state_;
};

class TCPState{
    public:
        virtual void Transmit(TCPConnection*,TCPOctetStream*);
        virtual void ActiveOpen(TCPConnection*);
        virtual void PassiveOpen(TCPConnection*);
        virtual void Close(TCPConnection*);
        virtual void Synchronize(TCPConnection*);
        virtual void Acknowledge(TCPConnection*);
        virtual void Send(TCPConnection*);
    protected:
        void ChangeState(TCPConnection*,TCPState*);
};

TCPConnection::TCPConnection(){
    state_ = TCPClosed::Instance();
}

void TCPConnection::ChangeState(TCPState* s){
    state_ = s;
}

void TCPConnection::ActiveOpen(){
    state_->ActiveOpen(this);
}

void TCPConnection::PassiveOpen(){
    state_->PassiveOpen(this);
}

void TCPConnection::Acknowledge(){
    state_->Acknowledge(this);
}
void TCPConnection::Close(){
    state_->Close(this);
}
void TCPConnection::Synchronize(){
    state_->Synchronize(this);
}


