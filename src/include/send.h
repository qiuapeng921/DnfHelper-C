
class Send {
private:
public:
    // HcCall 缓冲call
    static void BufferCall(ULONG64 param);

    // JmCall 加密call
    static void EncryptCall(ULONG64 param, int len);

    // FbCall 发包call
    static void SendCall();
};