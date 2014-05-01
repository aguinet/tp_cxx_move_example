#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utility>
#include <ctype.h>
#include <iostream>

struct String
{
public:
	String():
		_buf(nullptr)
	{ }

	String(const char* s)
	{
		if (s) {
			_buf = strdup(s);
		}
		else {
			_buf = nullptr;
		}
	}

	String(String const& o):
		String(o._buf)
	{ }

#ifdef MOVE_CONSTRUCTOR
	String(String&& o)
	{
		_buf = o._buf;
		o._buf = nullptr;
	}
#endif

	~String()
	{
		if (_buf) {
			free(_buf);
		}
	}

public:
	String to_upper() const
	{
		String ret;
		if (_buf == nullptr) {
			return ret;
		}
		const size_t len = strlen(_buf);
		char* ret_buf = (char*) malloc(len+1);
		ret._buf = ret_buf;
		for (size_t i = 0; i < len; i++) {
			ret_buf[i] = toupper(_buf[i]);
		}
		ret_buf[len] = 0;
		printf("to_upper tmp buf: %p\n", ret_buf);
		return ret;
	}

	const char* c_str() const { return _buf; }

public:
	String& operator=(String const& o)
	{
		if (&o != this) {
			if (_buf) {
				free(_buf);
			}
			if (o._buf != nullptr) {
				_buf = strdup(o._buf);
			}
			else {
				_buf = nullptr;
			}
		}
		return *this;
	}

#ifdef MOVE_CONSTRUCTOR
	String& operator=(String&& o)
	{
		if (&o != this) {
			_buf = o._buf;
			o._buf = nullptr;
		}
		return *this;
	}
#endif

private:
	char* _buf;
};

int main()
{
	String s1("hello");
	printf("s1: %p\n", s1.c_str());

	String scopy(s1);
	printf("scopy: %p\n", scopy.c_str());

	String smove(std::move(s1));
	printf("smove: %p\n", smove.c_str());
	printf("s1: %p\n", s1.c_str());

	String supper_direct = smove.to_upper();
	printf("supper_direct: %p\n", supper_direct.c_str());

	String supper_indirect;
	printf("supper_indirect: %p\n", supper_indirect.c_str());
	supper_indirect = smove.to_upper();
	printf("supper_indirect: %p\n", supper_indirect.c_str());

	return 0;
}
