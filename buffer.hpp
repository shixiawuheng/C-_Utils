#pragma once
#include <vector>
#include <stdexcept>
#include <cstring>
namespace Utils
{
  class Buffer
  {
  private:
    std::vector<unsigned char> buffer;

  public:
    // 默认构造函数和其它必要构造函数
    Buffer() = default;
    // 接收初始化列表的构造函数
    Buffer(std::initializer_list<unsigned char> initList)
        : buffer(initList)
    {
    }
    Buffer(char *initChar, size_t len) : buffer(initChar, initChar + len)
    {
    }
    // 接收基础类型的加法操作
    template <typename T>
    typename std::enable_if<std::is_arithmetic<T>::value, Buffer>::type
    operator+(const T &value) const
    {
      Buffer result(*this); // 复制当前Buffer实例
      const unsigned char *valuePtr = reinterpret_cast<const unsigned char *>(&value);
      result.buffer.insert(result.buffer.end(), valuePtr, valuePtr + sizeof(T));
      return result;
    }
    // 接收Buffer类型的加法操作
    Buffer operator+(const Buffer &other) const
    {
      Buffer result(*this); // 复制当前Buffer实例
      result.buffer.insert(result.buffer.end(), other.buffer.begin(), other.buffer.end());
      return result;
    }
    // 允许与C字符串相加的operator+
    Buffer operator+(const char *str) const
    {
      if (str == nullptr)
      {
        throw std::invalid_argument("Null pointer provided as string");
      }

      size_t strLength = std::strlen(str);
      Buffer result = *this;
      result.buffer.insert(result.buffer.end(), str, str + strLength);
      return result;
    }

    Buffer operator+(const std::string &str) const
    {
      Buffer result(*this); // 复制当前Buffer实例
      result.buffer.insert(result.buffer.end(), str.begin(), str.end());
      return result;
    }
    // 元素访问操作者
    unsigned char &operator[](size_t index)
    {
      if (index >= buffer.size())
      {
        throw std::out_of_range("Index out of bounds");
      }
      return buffer[index];
    }

    const unsigned char &operator[](size_t index) const
    {
      if (index >= buffer.size())
      {
        throw std::out_of_range("Index out of bounds");
      }
      return buffer[index];
    }

    // 工具函数 (列如 size, data, resize 等)
    size_t size() const
    {
      return buffer.size();
    }

    const unsigned char *data() const
    {
      return buffer.data();
    }

    void resize(size_t newSize)
    {
      buffer.resize(newSize, 0x90);
    }

    // 其他必要的成员函数和操作
    // ...
  };

}