#include "RangesHeaders.hpp"

#if defined (__GNUG__)   || defined(__clang__) 
	# if not (__cpp_lib_constexpr_string > 201911)
	class string
	{
	public:
        constexpr string() = default;
        constexpr string(const char& c) { append(&c, 1); }
        constexpr string(const string & s) { append(s.data(), s.size()); }
        constexpr string& operator=(const string & s)
        {
            reset();
            append(s.data(), s.size());
            return *this;
        }

        constexpr string(string && s) noexcept
            : _data{ std::exchange(s._data, nullptr) }
            , _length{ s._length }
        {}

        constexpr string& operator=(string && s) noexcept
        {
            std::exchange(_data, s._data);
            _length = s._length;
            return *this;
        }

        // a regular std::string is convertible to a string_view or better
        // there is a string_view ctor for a std::string. Make that work
        constexpr operator std::string_view() const noexcept
        {
            return { _data, _length };
        }

        constexpr string(std::string_view d) { append(d.data(), d.size()); }
        constexpr ~string() noexcept { reset(); }

        constexpr string& append(std::string_view d)
        {
            return append(d.data(), d.size());
        }
        constexpr string& append(const string & s)
        {
            return append(s.data(), s.size());
        }
        constexpr string& append(const char* d, std::size_t len)
        {
            const std::size_t needNt{ (len && (d[len - 1] != '\0')) ? 1u : 0u };

            char* tmp = new char[_length + len + needNt]{};
            std::copy_n(_data, _length, tmp);
            std::copy_n(d, len, tmp + _length);
            _length += len;

            delete[] _data;

            _data = tmp;

            return *this;
        }

        constexpr bool operator==(const string & s) const noexcept
        {
            return std::equal(_data, _data + _length, s._data);
        }

        constexpr char* data() { return _data; }
        constexpr char* data() const { return _data; }
        constexpr std::size_t size() const { return _length; }

    private:
        char* _data{};
        std::size_t _length{};

        constexpr void reset()
        {
            delete[] _data;
            _data = nullptr;
            _length = 0;
        }
	
	};
	#else
		using std::string;
	#endif
#else
	using std::string;
#endif
