#include "lib/crash/crashhandler.hpp"

lib::cache *lib::crash_handler::cache = nullptr;

auto lib::crash_handler::init() -> bool
{
#ifdef USE_GCC_CRASH_HANDLER
	auto result = signal(SIGSEGV, reinterpret_cast<__sighandler_t>(lib::crash_handler::handle));
	return result != nullptr;
#endif
	return false;
}

void lib::crash_handler::set_cache(lib::cache &c)
{
	lib::crash_handler::cache = &c;
}

void lib::crash_handler::log(const lib::crash_info &info)
{
	if (cache != nullptr)
	{
		cache->add_crash(info);
	}
	std::cerr << info.to_string() << std::endl;
}

#ifdef USE_GCC_CRASH_HANDLER
void lib::crash_handler::handle(int signal, struct sigcontext context)
{
	std::array<void *, backtrace_size> trace;
	lib::crash_info info;

	info.signal = signal;
	if (signal == SIGSEGV)
	{
		// TODO: Print this in hex
		info.info = lib::fmt::format("faulty address at {} from {}",
			context.cr2, context.rip);
	}

	auto trace_size = backtrace(trace.data(), backtrace_size);
	trace[1] = (void *) context.rip;
	auto **messages = backtrace_symbols(trace.data(), trace_size);

	info.stack_trace.reserve(trace_size);
	for (auto i = 0; i < trace_size; i++)
	{
		info.stack_trace.emplace_back(messages[i]);
	}

	log(info);
	exit(signal);
}
#endif
