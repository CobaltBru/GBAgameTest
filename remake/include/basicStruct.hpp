#include <tonc.h>
#include <string.h>

class Object
{
    public:
    VECTOR vertex[512];
    int index[512];
    int v_size;
    int i_size;
    Object(VECTOR ver[],int idx[],int v_size,int i_size);
};

Object::Object(VECTOR ver[],int idx[],int v,int i)
{
    memcpy(vertex, ver, v_size);
    memcpy(index, idx, i_size);
    v_size = v;
    i_size = i;
}