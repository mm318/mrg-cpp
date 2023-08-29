#ifndef _RINGBUFFER_H_
#define _RINGBUFFER_H_

#include <vector>
#include <mutex>
#include <condition_variable>


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
    pointer() : m_buffer(nullptr), m_read(false), m_data(nullptr) {}

    pointer(RingBuffer * buffer, bool read) : m_buffer(buffer), m_read(read)
    {
      // should already be locked, ideally assert here that it is already locked
      // std::lock(*get_rw_mutex(), m_buffer->m_idx_mutex)
      m_data = &m_buffer->m_buffer[get_index()];
      get_idx_mutex().unlock();
    }

    pointer(pointer && other)
    {
      m_buffer = other.m_buffer;
      m_read = other.m_read;
      other.m_buffer = nullptr;
    }

    pointer & operator=(pointer && other)
    {
      m_buffer = other.m_buffer;
      m_read = other.m_read;
      other.m_buffer = nullptr;
      return *this;
    }

    ~pointer()
    {
      if (nullptr != m_buffer) {
        {
          std::lock_guard<std::recursive_mutex> lock(get_idx_mutex());

          size_t & idx = get_index();
          ++idx;
          if (idx == m_buffer->m_buffer.size()) {
            idx = 0;
          }

          if (m_buffer->m_read_idx == m_buffer->m_write_idx) {
            if (m_read) {
              m_buffer->m_empty = true;
            } else {
              m_buffer->m_empty = false;
            }
          }
        }
        get_rw_mutex().unlock();
        get_condition_variable().notify_all();
      }
    }

    T * operator->() const
    {
      return m_data;
    }

    T & operator*() const
    {
      return *m_data;
    }

    bool operator==(const T * other) const
    {
      return (m_data == other);
    }

    bool operator!=(const T * other) const
    {
      return (m_data != other);
    }

  private:
    // Disallow copying
    pointer(const pointer &) = delete;
    pointer & operator=(const pointer &) = delete;

    std::recursive_mutex & get_idx_mutex() const
    {
      return m_buffer->m_idx_mutex;
    }

    std::mutex & get_rw_mutex() const
    {
      return (m_read) ? m_buffer->m_read_mutex : m_buffer->m_write_mutex;
    }

    std::condition_variable_any & get_condition_variable() const
    {
      return (m_read) ? m_buffer->m_not_full : m_buffer->m_not_empty;
    }

    size_t & get_index() const
    {
      return (m_read) ? m_buffer->m_read_idx : m_buffer->m_write_idx;
    }

    RingBuffer * m_buffer;
    bool m_read;
    T * m_data;
  };

  bool empty() const
  {
    std::lock_guard<std::recursive_mutex> lock(m_idx_mutex);
    bool result = m_empty && (m_write_idx == m_read_idx);
    return result;
  }

  bool full() const
  {
    std::lock_guard<std::recursive_mutex> lock(m_idx_mutex);
    bool result = !m_empty && (m_write_idx == m_read_idx);
    return result;
  }

  pointer try_get_write_pointer()
  {
    RingBufferScopedLock lock(this, false);
    if (full()) {
      return pointer();
    } else {
      lock.release();
      return pointer(this, false);
    }
  }

  pointer try_get_read_pointer()
  {
    RingBufferScopedLock lock(this, true);
    if (empty()) {
      return pointer();
    } else {
      lock.release();
      return pointer(this, true);
    }
  }

  pointer get_write_pointer()
  {
    RingBufferScopedLock lock(this, false);
    m_not_full.wait(lock, [this]() { return !this->full(); });
    lock.release();
    return pointer(this, false);
  }

  pointer get_read_pointer()
  {
    RingBufferScopedLock lock(this, true);
    m_not_empty.wait(lock, [this]() { return !this->empty(); });
    lock.release();
    return pointer(this, true);
  }

private:
  friend class RingBufferScopedLock;
  friend class pointer;

  class RingBufferScopedLock
  {
  public:
    RingBufferScopedLock(RingBuffer * buffer, bool read) : m_buffer(buffer), m_read(read)
    {
      lock();
    }

    ~RingBufferScopedLock()
    {
      unlock();
    }

    void lock()
    {
      if (nullptr != m_buffer) {
        std::lock(get_idx_mutex(), get_rw_mutex());
      }
    }

    void unlock()
    {
      if (nullptr != m_buffer) {
        get_idx_mutex().unlock();
        get_rw_mutex().unlock();
      }
    }

    void release()
    {
      m_buffer = nullptr;
    }

  private:
    std::recursive_mutex & get_idx_mutex() const
    {
      return m_buffer->m_idx_mutex;
    }

    std::mutex & get_rw_mutex() const
    {
      return (m_read) ? m_buffer->m_read_mutex : m_buffer->m_write_mutex;
    }

    RingBuffer * m_buffer;
    bool m_read;
  };

  std::vector<T> m_buffer;

  size_t m_write_idx; // empty location
  size_t m_read_idx;  // filled location (except when equal to m_write_mutex)
  bool m_empty;

  mutable std::recursive_mutex m_idx_mutex;
  std::mutex m_write_mutex;
  std::mutex m_read_mutex;

  std::condition_variable_any m_not_full;
  std::condition_variable_any m_not_empty;
};

#endif
