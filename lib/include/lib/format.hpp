#pragma once

#include "enum/logtype.hpp"

#include "thirdparty/json.hpp"
#include "thirdparty/filesystem.hpp"

#include <string>

namespace lib
{
	/**
	 * Formatting utilities
	 */
	class fmt
	{
	public:
		/**
		 * Format a string as a string
		 * @param fmt string
		 * @return string
		 */
		template<typename Format>
		static std::string format(const Format &fmt)
		{
			return fmt;
		}

		/**
		 * Format a string with specified arguments as {} in the string
		 * @param fmt string
		 * @param arg Argument to to_string
		 * @param args Arguments to to_string
		 * @return Formatted string
		 */
		template<typename Format, typename Arg, typename... Args>
		static std::string format(const Format &fmt, const Arg &arg, Args &&... args)
		{
			return format(collect(fmt, arg), args...);
		}

		/**
		 * Format time as M:SS
		 * @param ms Milliseconds
		 */
		static std::string time(int ms);

		/**
		 * Format size as B, kB, MB or GB (bytes)
		 * @param bytes Bytes
		 */
		static std::string size(unsigned int bytes);

		/**
		 * Format as k or M
		 * @param count Amount
		 */
		static auto count(unsigned int count) -> std::string;

	private:
		/** Kilo (1 000) */
		static constexpr unsigned int size_k = 1000;
		/** Mega (1 000 000) */
		static constexpr unsigned int size_m = size_k * 1000;
		/** Giga (1 000 000 000) */
		static constexpr unsigned int size_g = size_m * 1000;

		/**
		 * Format string into another string
		 * @param fmt String with {} to replace
		 * @param arg String to replace {} with
		 * @return Formatted string
		 */
		template<typename Format>
		static std::string collect(const Format &fmt, const std::string &arg)
		{
			auto str = std::string(fmt);
			auto index = str.find("{}");
			if (index == std::string::npos)
				return str;

			return str.replace(index, 2, arg);
		}

		/**
		 * Format value into a string
		 * @param fmt String with {} to replace
		 * @param arg Value to replace {} with
		 * @return Formatted string
		 */
		template<typename Format, typename Arg>
		static std::string collect(const Format &fmt, const Arg &arg)
		{
			return collect(fmt, std::to_string(arg));
		}

		/**
		 * Format C-style string into a string
		 * @param fmt String with {} to replace
		 * @param arg C-style string to replace {} with
		 * @return Formatted string
		 */
		template<typename Format>
		static std::string collect(const Format &fmt, const char *arg)
		{
			return collect(fmt, std::string(arg));
		}

		/**
		 * Format bool as "true" or "false"
		 * @param fmt String with {} to replace
		 * @param arg Value to replace {} with
		 * @return Formatted string
		 */
		template<typename Format>
		static std::string collect(const Format &fmt, bool arg)
		{
			return collect(fmt, arg ? "true" : "false");
		}

		/**
		 * Dump JSON as a string
		 * @param fmt String with {} to replace
		 * @param arg JSON to dump
		 * @return Formatted string
		 */
		template<typename Format>
		static std::string collect(const Format &fmt, const nlohmann::json &arg)
		{
			return collect(fmt, arg.dump());
		}

		/**
		 * Format path as string
		 * @param fmt String with {} to replace
		 * @param arg Path
		 * @return Formatted string
		 */
		template<typename Format>
		static auto collect(const Format &fmt, const ghc::filesystem::path &arg) -> std::string
		{
			return collect(fmt, arg.string());
		}
	};
}
