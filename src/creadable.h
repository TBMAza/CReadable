#ifndef CREADABLE
#define CREADABLE

#define rchar(x) _rchar(#x)
#define rschar(x) _rschar(#x)
#define ruchar(x) _ruchar(#x)

#define rshort(x) _rshort(#x)
#define rushort(x) _rushort(#x)

#define rint(x) _rint(#x)
#define ruint(x) _ruint(#x)

#define rlong(x) _rlong(#x)
#define rlonglong(x) _rlonglong(#x)
#define rulong(x) _rulong(#x)
#define rulonglong(x) _rulonglong(#x)

#define rfloat(x) _rfloat(#x)

#define rdouble(x) _rdouble(#x)
#define rlongdouble(x) _rlongdouble(#x)

char _rchar(char* number);
signed char _rschar(char* number);
unsigned char _ruchar(char* number);

short _rshort(char* number);
unsigned short _rushort(char* number);

int _rint(char* number);
unsigned int _ruint(char* number);

long _rlong(char* number);
long long _rlonglong(char* number);
unsigned long _rulong(char* number);
unsigned long long _rulonglong(char* number);

float _rfloat(char* number);

double _rdouble(char* number);
long double _rlongdouble(char* number);

#endif

