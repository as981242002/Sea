#ifndef SEA_BASE_NONCOPYABLE_H_
#define SEA_BASE_NONCOPYABLE_H_

namespace Sea
{

class NonCopyable
{
public:
	NonCopyable() = default;
	~NonCopyable() = default;
	void operator=(const NonCopyable&) = delete;
	NonCopyable(const NonCopyable&) = delete;
private:

};

}


#endif // !SEA_BASE_NONCOPYABLE_H_
