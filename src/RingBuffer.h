#ifndef _RINGBUFFER_H_
#define _RINGBUFFER_H_

#include <vector>
#include <mutex>


template<class T>
class RingBuffer
{
public:
  RingBuffer(size_t buffer_size)
    : m_buffer(buffer_size),
      m_write_idx(0),
      m_read_idx(0),
      m_empty(true) {}

  class pointer
  {
  public:
    pointer() : m_buffer(nullptr) {}

    pointer(RingBuffer * buffer, bool read) : m_buffer(buffer), m_read(read)
    {
      get_mutex()->lock();
    }

    ~pointer()
    {
      if (nullptr != m_buffer) {
        size_t * idx = get_index();
        ++(*idx);
        if (*idx == m_buffer->m_buffer.size()) {
          *idx = 0;
        }
        get_mutex()->unlock();

        std::lock(m_buffer->m_write_mutex, m_buffer->m_read_mutex);
        if (m_buffer->m_read_idx == m_buffer->m_write_idx) {
          if (m_read) {
            m_buffer->m_empty = true;
          } else {
            m_buffer->m_empty = false;
          }
        }
        m_buffer->m_write_mutex.unlock();
        m_buffer->m_read_mutex.unlock();
      }
    }

    T * operator->() const
    {
      return get_data();
    }

    T & operator*() const
    {
      return *get_data();
    }

    bool operator==(const T * other) const
    {
      return (get_data() == other);
    }

    bool operator!=(const T * other) const
    {
      return (get_data() != other);
    }

  private:
    std::mutex * get_mutex() const
    {
      return (m_read) ? &m_buffer->m_read_mutex : &m_buffer->m_write_mutex;
    }

    T * get_data() const
    {
      if (nullptr == m_buffer) {
        return nullptr;
      } else {
        return (m_read) ? &m_buffer->m_buffer[m_buffer->m_read_idx] 
                        : &m_buffer->m_buffer[m_buffer->m_write_idx];
      }
    }

    size_t * get_index() const
    {
      return (m_read) ? &m_buffer->m_read_idx : &m_buffer->m_write_idx;
    }

    RingBuffer * m_buffer;
    bool m_read;
  };

  bool empty() const
  {
    std::lock(m_write_mutex, m_read_mutex);
    bool result = m_empty && (m_write_idx == m_read_idx);
    m_write_mutex.unlock();
    m_read_mutex.unlock();
    return result;
  }

  bool full() const
  {
    std::lock(m_write_mutex, m_read_mutex);
    bool result = !m_empty && (m_write_idx == m_read_idx);
    m_write_mutex.unlock();
    m_read_mutex.unlock();
    return result;
  }

  pointer get_write_pointer()
  {
    if (full()) {
      return pointer();
    } else {
      return pointer(this, false);
    }
  }

  pointer get_read_pointer()
  {
    if (empty()) {
      return pointer();
    } else {
      return pointer(this, true);
    }
  }

private:
  friend class pointer;

  std::vector<T> m_buffer;
  size_t m_write_idx; // empty location
  mutable std::mutex m_write_mutex;
  size_t m_read_idx;  // filled location (except when equal to m_write_mutex)
  mutable std::mutex m_read_mutex;

  bool m_empty;
};

#endif
