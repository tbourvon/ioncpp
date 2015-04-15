#ifndef ION_UTF8STRING_H
#define ION_UTF8STRING_H

#include <string>

namespace ion {

typedef char32_t utfchar;

class utf8string {
public:
    typedef typename std::string::size_type size_type;

    class const_iterator {
    public:
        typedef utfchar value_type;
        typedef typename std::string::difference_type difference_type;
        typedef utfchar* pointer;
        typedef utfchar& reference;
        typedef std::bidirectional_iterator_tag iterator_category;

        const_iterator(std::string::const_iterator itr) : m_ptr(itr) {}

        const_iterator& operator=(const_iterator itr) {
            m_ptr = itr.m_ptr;
            return *this;
        }

        bool operator==(const const_iterator& itr) const {
            return m_ptr == itr.m_ptr;
        }
        bool operator!=(const const_iterator& itr) const {
            return !(*this == itr);
        }

        const_iterator& operator++() {
            next();
            return *this;
        }
        const_iterator operator++(int) {
            const_iterator itr = *this;
            next();
            return itr;
        }
        const_iterator& operator--() {
            previous();
            return *this;
        }
        const_iterator operator--(int) {
            const_iterator itr = *this;
            previous();
            return itr;
        }

        utfchar operator*() const {
            utfchar ch = 0;
            for (int8_t i = 0, len = utf8string::char_length(*m_ptr); i < len; ++i)
                ch += (unsigned char)*(m_ptr + i) << (i * 8);
            return ch;
        }

    private:
        std::string::const_iterator m_ptr;

        void next() {
            m_ptr += utf8string::char_length(*m_ptr);
        }

        void previous() {
            do
                --m_ptr;
            while ((*m_ptr >> 6) == 0b10);
        }
    };

    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    utf8string() : m_string("") {}
    utf8string(const std::string& str) : m_string(str) {}
    utf8string(const char* data) : m_string(data) {}

    std::string string() const {
        return m_string;
    }

    utf8string& operator=(const char* data) {
        m_string = data;
        return *this;
    }

    const_iterator begin() const {
        return cbegin();
    }
    const_iterator cbegin() const {
        return const_iterator(m_string.cbegin());
    }
    const_iterator end() const {
        return cend();
    }
    const_iterator cend() const {
        return const_iterator(m_string.cend());
    }
    const_reverse_iterator rbegin() const {
        return crbegin();
    }
    const_reverse_iterator crbegin() const {
        return const_reverse_iterator(cend());
    }
    const_reverse_iterator rend() const {
        return crend();
    }
    const_reverse_iterator crend() const {
        return const_reverse_iterator(cbegin());
    }

    utfchar front() const {
        utfchar ch = 0;
        for (int8_t i = 0, len = utf8string::char_length(m_string[0]); i < len; ++i)
            ch += (unsigned char)m_string[i] << (i * 8);
        return ch;
    }

    utfchar back() const {
        utfchar ch = 0;
        size_type len = m_string.length();
        char c = m_string[--len];
        do
            ch = (ch >> 8) + ((unsigned char)c << 24);
        while (((c = m_string[--len]) >> 6) == 0b10);
        return ch;
    }
    void push_back(utfchar ch) {
        m_string.append((char*)&ch);
    }
    void pop_back() {
        size_t len = m_string.length();
        char c = m_string[--len];
        do
            m_string.pop_back();
        while (((c = m_string[--len]) >> 6) == 0b10);
    }

    void swap(utf8string& str) {
        m_string.swap(str.m_string);
    }
    size_type size() {
        return std::distance(begin(), end());
    }
    size_type max_size() {
        return m_string.max_size();
    }

    bool empty() {
        return m_string.empty();
    }

    bool begins_with(const utf8string& str) {
        return m_string.compare(0, str.m_string.length(), str.m_string) == 0;
    }

    utf8string& operator+=(utfchar rhs) {
        push_back(rhs);
        return *this;
    }

    utf8string& operator+=(const utf8string& rhs) {
        m_string += rhs.m_string;
        return *this;
    }

    friend std::ostream& operator<< (std::ostream& out, const utf8string &str) {
        out << str.m_string;
        return out;
    }

    static int8_t char_length(unsigned char ch) {
        if (ch < 128)
            return 1;
        else if ((ch >> 5) == 0b110)
            return 2;
        else if ((ch >> 4) == 0b1110)
            return 3;
        else if ((ch >> 3) == 0b11110)
            return 4;
        else
            return 1;
    }

private:
    std::string m_string {""};
};

inline utf8string operator+(utf8string str1, const utf8string& str2) {
    str1 += str2;
    return str1;
}

inline utf8string operator+(utf8string str, utfchar ch) {
    str += ch;
    return str;
}

inline bool operator==(const utf8string& str1, const utf8string& str2) {
    return str1.string() == str2.string();
}

inline bool operator!=(const utf8string& str1, const utf8string& str2) {
    return !(str1 == str2);
}

inline bool operator<(const utf8string& str1, const utf8string& str2) {
    return str1.string() < str2.string();
}

} // namespace ion

namespace std {
    template<>
    struct hash<ion::utf8string> {
        typedef ion::utf8string argument_type;
        typedef std::size_t result_type;

        result_type operator()(argument_type const& str) const {
            return std::hash<std::string>()(str.string());
        }

    };
}

#endif // ION_UTF8STRING_H
