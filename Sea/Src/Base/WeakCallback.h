#ifndef SEA_BASE_WEAKCALLBACK_H_
#define SEA_BASE_WEAKCALLBACK_H_

#include<functional>
#include<memory>

namespace Sea
{

template<typename CLASS, typename... ARGS>
class WeakCallback
{
public:
	WeakCallback(const std::weak_ptr<CLASS>& object,
				const std::function<void(CLASS*, ARGS...)>& function): object_(object), function_(func)
	{

	}
	//default dtor

	void operator()(ARGS&&..args)const  //·Âº¯ÊýÄ£·Â
	{
		std::shared_ptr<CLASS> ptr(object_.lock());
		if (ptr)
		{
			function__(ptr.get(), std::forward<ARGS>(args)...);
		}
	}

private:
	std::weak_ptr<CLASS> object_;
	std::function<void(CLASS*, ARGS...)> function__;
};

template<typename CLASS, typename... ARGS>
WeakCallback<CLASS, ARGS...> makeWeakCallback(const std::shared_ptr<CLASS>& object, void (CLASS::*function)(ARGS)...)
{
	return WeakCallback<CLASS, ARGS...>(object, function);
}

template<typename CLASS, typename...ARGS>
WeakCallback<CLASS, ARGS> makeWeakCallback(const std::shared_ptr<CLASS>& object, void (CLASS::*function)(args)...const)
{
	return WeakCallback<CLASS, ARGS...>(object, function);
}

} //namespace Sea

#endif // !SEA_BASE_WEAKCALLBACK_H_
