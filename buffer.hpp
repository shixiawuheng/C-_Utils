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
    // Ĭ�Ϲ��캯����������Ҫ���캯��
    Buffer() = default;
    // ���ճ�ʼ���б�Ĺ��캯��
    Buffer(std::initializer_list<unsigned char> initList)
        : buffer(initList)
    {
    }
    Buffer(char *initChar, size_t len) : buffer(initChar, initChar + len)
    {
    }
    // ���ջ������͵ļӷ�����
    template <typename T>
    typename std::enable_if<std::is_arithmetic<T>::value, Buffer>::type
    operator+(const T &value) const
    {
      Buffer result(*this); // ���Ƶ�ǰBufferʵ��
      const unsigned char *valuePtr = reinterpret_cast<const unsigned char *>(&value);
      result.buffer.insert(result.buffer.end(), valuePtr, valuePtr + sizeof(T));
      return result;
    }
    // ����Buffer���͵ļӷ�����
    Buffer operator+(const Buffer &other) const
    {
      Buffer result(*this); // ���Ƶ�ǰBufferʵ��
      result.buffer.insert(result.buffer.end(), other.buffer.begin(), other.buffer.end());
      return result;
    }
    // ������C�ַ�����ӵ�operator+
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
      Buffer result(*this); // ���Ƶ�ǰBufferʵ��
      result.buffer.insert(result.buffer.end(), str.begin(), str.end());
      return result;
    }
    // Ԫ�ط��ʲ�����
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

    // ���ߺ��� (���� size, data, resize ��)
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

    // ������Ҫ�ĳ�Ա�����Ͳ���
    // ...
  };

}