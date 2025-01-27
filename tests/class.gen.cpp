#include "class.gen.h"

void CObject::for_each_var(std::function<void(const member_variable_info&)> fn) const
{
	return pycppgen<std::decay_t<decltype(*this)>>::for_each_var(fn);
}
void CChild::for_each_var(std::function<void(const member_variable_info&)> fn) const
{
	return pycppgen<std::decay_t<decltype(*this)>>::for_each_var(fn);
}
