
class Send {
private:
public:
    // HcCall 缓冲call
    void BufferCall(uint32_t param);

    // JmCall 加密call
    void EncryptCall(uint32_t param, uint32_t len);

    // FbCall 发包call
    void SendCall();
};