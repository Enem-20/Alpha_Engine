#define COLOR_BUFFER_SIZE 32

#include <glm/vec3.hpp>
#include <rpcndr.h>

struct cbinfo_t
{
	int Name;
	vector3ub Color;
};

struct ColorBuffer_t
{
private:
	int next;
public:
	cbinfo_t Names[COLOR_BUFFER_SIZE];
	void InitNames(void);
	void LoadName(int name, byte* color);
};