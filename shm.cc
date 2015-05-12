#include <sys/types.h> 
#include <sys/mman.h>

#include <nan.h>


NAN_METHOD(ReadMemory) {
    NanScope();
    v8::String::AsciiValue name(args[0]->ToString());
    size_t length = args[1]->Uint32Value();

    int fd = shm_open(*name, O_RDONLY, 0);
    if (fd == -1) {
        NanReturnUndefined();
    }

    void *pSharedMemory = mmap((void *)0, length, PROT_READ, MAP_SHARED, fd, 0);
    if (pSharedMemory == MAP_FAILED) {
        NanReturnUndefined();
    }

    v8::Local<v8::Object> buf = NanNewBufferHandle(length);
    memcpy(node::Buffer::Data(buf), pSharedMemory, length);
    munmap(pSharedMemory, length);
    NanReturnValue(buf);
}

void init (v8::Handle<v8::Object> exports) {
    exports->Set(NanNew<v8::String>("read"), 
        NanNew<v8::FunctionTemplate>(ReadMemory)->GetFunction());
}

NODE_MODULE(shm, init)
